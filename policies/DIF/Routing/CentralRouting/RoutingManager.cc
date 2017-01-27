#include "DIF/Routing/CentralRouting/RoutingManager.h"
#include "Common/Utils.h"

#include <array>

Register_Class(RoutingManager);

void RoutingManager::onPolicyInit() {
    statusSeq = 0;
    myA = 0;

    in_timer = new cMessage("In-zone update timer");
    in_updateInterval = par("in_updateInterval");


    in_sincro_timer = new cMessage("In-zone sincro timer");
    in_sincro_updateInterval = par("in_sincro_updateInterval");


    out_sincro_timer = new cMessage("Out-zone sincro timer");
    out_sincro_updateInterval = par("out_sincro_updateInterval");


    toout_sincro_timer = new cMessage("To Out-zone sincro timer");
    toout_sincro_updateInterval = par("toout_sincro_updateInterval");


    exceptions_timer = new cMessage("Exceptions timer");
    exceptions_timer_updateInterval = par("exceptions_timer_updateInterval");


    start_timer = new cMessage("Start update timer");
    double start_Time = par("start_Time");
    if(start_Time < 0.0) { start_Time = 0.0; }
    scheduleAt(simTime() + start_Time, start_timer);

    f = par("fabrics").longValue();
    p = par("pods").longValue();
    s = par("spines").longValue();
    t = par("tors").longValue();

    current_sent = 0;
    exception_in_seq = 0;


    DM = new unsigned char * [f+t];

    for (addr_t i = 0; i < (f+t); i++) {
        DM[i] = new unsigned char [f+t];
    }

    for (addr_t i = 0; i < f; i++) {
        DM[i][i] = 0;
        for (addr_t j = i+1; j < f; j++) {
            DM[i][j] = 2;
            DM[j][i] = 2;
        }
        for (addr_t j = 0; j < t; j++) {
            addr_t j2 = j+f;
            DM[i][j2] = 1;
            DM[j2][i] = 1;
        }
    }

}

void RoutingManager::setMyA(const addr_t & a) {
    if(myA != 0) { error("Never should be called more than once!!"); }
    myA = a;
    myZone = getZone(myA);
    inzone.setId(getIdentifier(myA));
    myZoneStat.zone = myZone;

    incrementInKnown = getIdentifier(myA) - 200;

    for(addr_t d = 0; d < p; d++) {
        if(d+f == myZone) { continue; }
        addr_t podMan = getAddr(d+f, 255);
        Address podAdd(getRawAddr_t(podMan).c_str(), myAddress.getDifName().getName().c_str());
        auto & info = externalPods[podMan];
        info.addr = podAdd;
    }
}

void RoutingManager::addAddr(const addr_t & a) {
    inzone.addAddress(a);
}

void RoutingManager::addMasterNei(const addr_t & a, const Address & m) {
    masters[a].addr = m;
    masters[a].status = true;

    //Add sincronization!!
}
void RoutingManager::removeMasterNei(const addr_t & a) {
    masters[a].status = false;
}

void RoutingManager::addNei(const addr_t &a, const Address &addr,
        const bool &samezone, const elink_t &link) {
    neiInfo & info = neis[a];
    info.addr = addr;
    info.samezone = samezone;
    info.link = link;
}

void RoutingManager::onFlow(addr_t a) {
    neiInfo & info = neis[a];
    info.status = true;
    if (info.samezone) {
        sendUpdates();
    }
}

void RoutingManager::offFlow(addr_t a) {
    neiInfo & info = neis[a];
    info.status = false;
    if (info.samezone) {
        inzone.removeFrom(a);
        sendUpdates();
    }
}

void RoutingManager::sendUpdates() {
    auto update = inzone.getRTUpdate();
    for (auto info : neis) {
        if (info.second.samezone && info.second.status) {
            RUpdate * up = new RUpdate();
            up->setDestination(info.second.addr);
            up->entries = update;

            sendUpdate(up);
        }
    }
}

void RoutingManager::handleMessage(cMessage * msg) {
    if(msg == in_timer) {
           sendUpdates();
           return;
    }
    if(msg == in_sincro_timer) {
           sendInzoneSincro();
           return;
    }
    if(msg == out_sincro_timer) {
           sendOutzoneSincro();
           return;
    }
    if(msg == toout_sincro_timer) {
           sendtoOut();
           return;
    }
    if(msg == exceptions_timer) {
        computeExceptions();
        sendExceptions();
           return;
    }


    if(msg == start_timer) {
            delete start_timer;
            start_timer = nullptr;
            //Send start message to neis
            for(auto nei : neis) {
                if(! nei.second.status) { continue; }
                RStart * rup = new RStart();
                rup->zone = myZone;
                rup->setDestination(nei.second.addr);
                sendUpdate(rup);
            }
            return;
    }

    delete msg;
}

bool RoutingManager::processUpdate(IntRoutingUpdate * update) {
    if (RException * up = dynamic_cast<RException *>(update)) {
        // Received new exceptions ack
        addr_t src = parseRawAddr(up->getSource().getIpcAddress().getName());

        addr_t src_id = getIdentifier(src);
        if(src_id < f) {
            seqId_t & src_sq = fabs[src_id].lastReceived;
            if(src_sq < up->seqId) {
                src_sq = up->seqId;
            }
        } else {
            seqId_t & src_sq = tors[src_id-f].lastReceived;
            if(src_sq < up->seqId) {
                src_sq = up->seqId;
            }
        }
        return r_stat != 0;
    }

    if (RUpdate * up = dynamic_cast<RUpdate *>(update)) {
        if( inzone.receiveChanges(up->entries.src, up->entries.entries) ) {
            if(!in_timer->isScheduled()) {
                scheduleAt(simTime() + in_updateInterval, in_timer);
            }
        }
        r_stat |= R_INZONE_CHANGES;
        return r_stat != 0;
    }


    if (ROutSincro * up = dynamic_cast<ROutSincro *>(update)) {
        if(up->received) {
            //Ack
        } else {
            for(auto & e : up->outStats) {
                zone_stat_t & zs = e.second;
                zone_stat_t & cs = outStats[zs.zone];
                if(zs.seqId > cs.seqId) {
                    cs = zs;
                }
            }

            exception_seq++;
        }

        return r_stat != 0;
    }

    if (RZoneStatus * up = dynamic_cast<RZoneStatus *>(update)) {
        if(up->received) {
            //Ack
        } else {
            zone_stat_t & zs = up->stat;
            zone_stat_t & cs = outStats[zs.zone];
            if(zs.seqId > cs.seqId) {
                cs = zs;
                /** Sincronize **/
                if(!out_sincro_timer->isScheduled()) {
                    scheduleAt(simTime() + out_sincro_updateInterval, out_sincro_timer);
                }
                /** END sincronize **/

                /** Compute and send exceptions **/
                if(!exceptions_timer->isScheduled()) {
                    scheduleAt(simTime() + exceptions_timer_updateInterval, exceptions_timer);
                }
                /** END exceptions **/
            }

            RZoneStatus * res = new RZoneStatus();
            res->setDestination(up->getSource());
            res->received = true;
            res->stat.zone = zs.zone;
            res->stat.seqId = zs.seqId;
            sendUpdate(res);

            exception_seq++;
        }

        return r_stat != 0;
    }

    if (RStatus * up = dynamic_cast<RStatus *>(update)) {
        // Received status update
        addr_t z = getZone(up->status.node_addr);
        if(z == myZone) {
            if(inzone_status[up->status.node_addr].seqId >= up->status.seqId) {
                return r_stat != 0;
            }

            inzone_status[up->status.node_addr] = up->status;
        } else {
            if(outzone_status[up->status.node_addr].seqId >=up->status.seqId) {
                return r_stat != 0;
            }

            outzone_status[up->status.node_addr] = up->status;
        }

        computeZone();

        /** Sincronize **/
        if(!in_sincro_timer->isScheduled()) {
            scheduleAt(simTime() + in_sincro_updateInterval, in_sincro_timer);
        }
        /** END sincronize **/

        /** Inform other pods **/
        if(!toout_sincro_timer->isScheduled()) {
            scheduleAt(simTime() + toout_sincro_updateInterval, toout_sincro_timer);
        }
        /** END Inform **/

        /** Compute and send exceptions **/
        if(!exceptions_timer->isScheduled()) {
            scheduleAt(simTime() + exceptions_timer_updateInterval, exceptions_timer);
        }
        /** END exceptions **/


        RStatus * res = new RStatus();
        res->setDestination(up->getSource());
        res->received = true;
        res->status.node_addr = up->status.node_addr;
        res->status.seqId = up->status.seqId;
        sendUpdate(res);

        exception_seq++;

        return r_stat != 0;
    }

    if (RSincro * up = dynamic_cast<RSincro *>(update)) {
        // Received status sincro update
        auto & m = masters[up->sender];
        if(up->received) {
            //is ack
            if(m.last_acked < up->update_seq) {
                m.last_acked = up->update_seq;
            }
        } else {
            //update message
            if(m.last_acked >= up->update_seq) { return r_stat != 0; }
            m.last_sent = up->update_seq;

            bool changes = false;
            bool inchanges = false;
            for(auto & e : up->inzone_status) {
                if(e.second.seqId > inzone_status[e.first].seqId) {
                    changes = true;
                    inchanges = true;
                    inzone_status[e.first] = e.second;
                }
            }

            for(auto & e : up->outzone_status) {
                if(e.second.seqId > outzone_status[e.first].seqId) {
                    changes = true;
                    outzone_status[e.first] = e.second;
                    //Outs without problems should be cleaned over time
                }
            }

            if(changes && exception_in_seq >= up->exception_in_seq) {
                if (exception_in_seq == up->exception_in_seq) {
                    //"Random" increment
                    exception_in_seq += incrementInKnown;
                }
                if(!in_sincro_timer->isScheduled()) {
                    scheduleAt(simTime() + in_sincro_updateInterval, in_sincro_timer);
                }
            } else {
                //ACK
                RSincro * res = new RSincro();
                res->setDestination(up->getSource());
                res->received = true;
                res->sender = myA;
                res->update_seq = up->update_seq;
                res->exception_in_seq = exception_in_seq;
                sendUpdate(res);
            }

            if(inchanges) {
                computeZone();
            }

            if(changes && exception_in_seq >= up->exception_in_seq) {
                //Compute exceptions
                if(!exceptions_timer->isScheduled()) {
                    scheduleAt(simTime() + exceptions_timer_updateInterval, exceptions_timer);
                }
            }

            if(inchanges && exception_in_seq >= up->exception_in_seq) {
                //Inform other pods
                if(!toout_sincro_timer->isScheduled()) {
                    scheduleAt(simTime() + toout_sincro_updateInterval, toout_sincro_timer);
                }
            }

            exception_seq++;
        }

        return r_stat != 0;
    }

    return r_stat != 0 ;
}

void RoutingManager::sendInzoneSincro() {
    current_sent++;
    exception_in_seq++;
    bool resend = false;
    for(auto & e : masters) {
        if(! e.second.status ) { continue; }
        RSincro * rs = new RSincro();
        rs->setDestination(e.second.addr);
        rs->sender = myA;
        rs->update_seq = current_sent;
        rs->exception_in_seq = exception_in_seq;
        rs->inzone_status = inzone_status;
        rs->outzone_status = outzone_status;

        sendUpdate(rs);

        resend = true;
    }
    if(resend) {
        //start timer for resending!!
    }
}

void RoutingManager::sendOutzoneSincro() {
    exception_in_seq++;
    bool resend = false;
    for(auto & e : masters) {
        if(! e.second.status ) { continue; }
        ROutSincro * rs = new ROutSincro();
        rs->setDestination(e.second.addr);
        rs->sender = myA;
        rs->exception_in_seq = exception_in_seq;

        rs->outStats = outStats;

        sendUpdate(rs);

        resend = true;
    }
    if(resend) {
        //start timer for resending!!
    }
}

void RoutingManager::sendtoOut() {
    myZoneStat.seqId = exception_in_seq;

    for(auto & p : externalPods) {
        RZoneStatus * exmsg = new RZoneStatus();
        exmsg->setDestination(p.second.addr);
        exmsg->stat = myZoneStat;

        sendUpdate(exmsg);
    }
}


void RoutingManager::computeZone() {

    map<addr_t, set<addr_t> > tor_fails;
    map<addr_t, set<addr_t> > fab_down_fails;
    map<addr_t, set<addr_t> > fab_up_fails;

    for(auto &e : inzone_status) {
        for(auto & fail : e.second.fails) {
            addr_t src = getESrc(fail);
            addr_t dst = getEDst(fail);
            if(getZone(src) == myZone) {
                tor_fails[dst].insert(src);
                fab_down_fails[src].insert(dst);
            } else {
                fab_up_fails[dst].insert(src);
            }
        }
    }

    myZoneStat.downFabs.clear();
    myZoneStat.problemsAtFabs.clear();
    myZoneStat.probToRtoFabDistance.clear();

    for(auto & e : fab_up_fails) {
        if(e.second.size()>= s) {
            myZoneStat.downFabs.insert(e.first);
        } else {
            auto & fabprob = myZoneStat.problemsAtFabs[e.first];
            for(auto & fail : e.second) {
                fabprob.insert(fail);
            }
        }
    }

    for(auto & e : fab_down_fails) {
        if(e.second.size()>= t) {
            myZoneStat.downFabs.insert(e.first);
            myZoneStat.problemsAtFabs.erase(e.first);
        }
    }


    //Check if there is need to compute inzone DM
    bool req = false;
    for(auto & e : tor_fails) {
        if(! subAddrSet(e.second, myZoneStat.downFabs)) {
            req = true;
        }
    }
    if(req) {
        for(addr_t i = 0; i < f; i++) {
            for(addr_t j = 0; j < i; j++) {
                DM[i][j] = 16;
                DM[j][i] = 16;
            }
            for(addr_t j = f; j < f+t; j++) {
                DM[i][j] = 1;
                DM[j][i] = 1;
            }
            DM[i][i] = 0;
        }

        for(addr_t i = f+1; i < f+t; i++) {
            for(addr_t j = f; j < i; j++) {
                DM[i][j] = 16;
                DM[j][i] = 16;
            }
            DM[i][i] = 0;
        }

        for(auto & e : tor_fails) {
            for(auto & fail : e.second) {
                addr_t a = getIdentifier(e.first);
                addr_t b = getIdentifier(fail);
                DM[a][b] = 16;
                DM[b][a] = 16;
            }
        }

        iterateDM(DM, f+t, 16);

        for(auto & e : tor_fails) {
            if(! subAddrSet(e.second, myZoneStat.downFabs)) {
                addr_t id = getIdentifier(e.first);
                myZoneStat.probToRtoFabDistance[e.first] =
                        vector<unsigned char>(DM[id],DM[id] + f);
            }
        }
    }
}

void RoutingManager::finish() {

    if(in_timer != nullptr) { cancelAndDelete(in_timer); }
    if(start_timer != nullptr) { cancelAndDelete(start_timer); }
    if(in_sincro_timer != nullptr) { cancelAndDelete(in_sincro_timer); }
    if(out_sincro_timer != nullptr) { cancelAndDelete(out_sincro_timer); }
    if(toout_sincro_timer != nullptr) { cancelAndDelete(toout_sincro_timer); }
    if(exceptions_timer != nullptr) { cancelAndDelete(exceptions_timer); }
    if(DM != nullptr) {
        for(addr_t i= 0; i< (t+f); i++) {
            delete[] DM[i];
        }
        delete[] DM;
    }

    if(par("printAtEnd").boolValue()) {
        cout << hex;
        cout << "Manager "<< myAddress << endl;

        cout << "\tManagers:"<<endl;
        for(auto & e : masters) {
            cout << "\t\tAddress "<< e.second.addr
                    << " : " << (e.second.status? "ON":"OFF")
                    << " : last ack " << e.second.last_acked
                    << " : last sent " << e.second.last_sent
                    <<endl;
        }


        cout << "\tIn Zone:"<<endl;
        for(auto & e : inzone_status) {
            cout << "\t\tNode "<< e.first<<endl;
            for(auto & f : e.second.fails) {
                cout << "\t\t\tFailed link "<< f <<endl;
            }
        }

        cout << "\tOut Zone:"<<endl;
        for(auto & e : outzone_status) {
            cout << "\t\tNode "<< e.first<<endl;
            for(auto & f : e.second.fails) {
                cout << "\t\t\tFailed link "<< f <<endl;
            }
        }

        cout << "\tOthers RT:"<<endl;
        for(auto e : outStats) {
            cout << "\t\t"<<e.first<<endl;
            cout << "\t\t-DOWN fabs"<<endl;
            for(auto q : e.second.downFabs) {
                cout << "\t\t\t"<< q<<endl;
            }

            cout << "\t\t-Problem fabs"<<endl;
            for(auto q : e.second.problemsAtFabs) {
                cout << "\t\t\t"<< q.first << " :";
                for(auto k : q.second) {
                    cout << " "<< k;
                }
                cout << endl;
            }

            cout << "\t\t-Distance to prob ToRs"<<endl;
            for(auto q : e.second.probToRtoFabDistance) {
                cout << "\t\t\t"<< q.first << " :" ;
                for(auto k : q.second) {
                    cout << " "<< (int) k;
                }
                cout << endl;
            }

        }

        cout << "\tZone RT:"<<endl;
        for(auto e : inzone.neiState) {
            cout << "\t\t"<<e.first<<endl;
            if(!e.second.op1.empty()) {
                cout << "\t\t\tOp 1 ("<<(int)e.second.m1<<") :";
                for(auto d : e.second.op1) {
                    cout << " "<< d;
                }
                cout << endl;
            }
            if(!e.second.op2.empty()) {
                cout << "\t\t\tOp 2 ("<<(int)e.second.m2<<") :";
                for(auto d : e.second.op2) {
                    cout << " "<< d;
                }
                cout << endl;
            }

        }
        cout << dec;
    }
}


void RoutingManager::computeExceptions() {
    if(exception_seq == last_exception_seq) {
        return;
    }
    last_exception_seq = exception_seq;
    /**
     * Available info :
     *  inzone_status + myZoneStat
     *  outzone_status + outStats
     *  DM
     *  (f + t + s + p)
    **/

    tors = vector<ToR_info_t>(t);
    fabs = vector<Fab_info_t>(f);

    unsigned int disconnected_fabs_down = 0;
    unsigned int disconnected_fabs_up = 0;
    unsigned int disconnected_tors = 0;

    set<addr_t> problematic_tors;

    // Init Fabrics
    for(addr_t i = 0; i < f; i++) {
        Fab_info_t & info = fabs[i];
        info.a = getAddr(myZone, i);

        info.v1 = vector<bool>(t, true);
        info.v2 = vector<bool>(s, true);


        // Check connection between fabric node and tors
        info.connectedDown = t;
        for(addr_t j = 0; j< t; j++) {
            addr_t j2 = j+f;
            if(DM[i][j2] != 1) {
                info.v1[j] = false;
                info.connectedDown--;
            }
        }
        if(info.connectedDown <= 0) {
            info.disconnectedDown = true;
            disconnected_fabs_down++;
        }

        // Check connection between fabric node and spines
        for(auto & fail : myZoneStat.problemsAtFabs[info.a]) {
            addr_t fz = getZone(fail);
            if(fz != myZone) {                      // Problem reaching a spine
                addr_t fi = getIdentifier(fail);
                info.v2[fi] = false;
                info.problemsUp++;
            }
        }
        if(info.problemsUp >= s) {
            info.disconnectedUp = true;
            disconnected_fabs_up++;
        }
    }

    // Init ToRs
    for(addr_t i = 0; i < t; i++) {
        ToR_info_t & info = tors[i];
        info.a = getAddr(myZone, i+f);

        info.v1 = vector<bool>(f, true);
        info.v2 = vector<bool>(f, true);

        //Check if ToR has problems reaching some fabrics or connected fabric has problems
        for(addr_t j = 0 ; j < f; j++) {
            if(DM[i+f][j] > 1) {
                info.problems++;
                info.v1[j] = false;
                info.v2[j] = false;
            } else {
                if(fabs[j].connectedDown <= 1) {
                    info.v1[j] = false;
                }
                if(fabs[j].disconnectedUp) {
                    info.v2[j] = false;
                }
            }
        }
        if(info.problems >= f) {
            info.disconnected = true;
            disconnected_tors++;
        }
        if(info.problems > disconnected_fabs_down) {
            problematic_tors.insert(i+f);
        }

    }


    //Compute in-Pod exceptions
    // SRC:ToR
    for(addr_t i = 0; i< t; i++){
        ToR_info_t & info = tors[i];
        addr_t i2 = i+f;

        if(info.disconnected) {
            continue;           // Already disconnected
        }

        // DST:Fabric
        if(info.problems > 0) {
            for(addr_t j = 0; j< f; j++){
                if(DM[i2][j] > 1) {
                    //Compute exception SRC:DST
                    e_t e;
                    e.a = fabs[j].a;
                    vector<bool> t(f,false);
                    unsigned char td = DM[i2][j] - 1; // Target distance
                    for(addr_t k = 0; k< f; k++){
                        if(j != k && DM[k][j] == td) {
                            e.valid.push_back(k);
                            t[k] = true;
                        }
                    }
                    if(t != info.v1) {
                        info.ex.push_back(e);
                    }
                }
            }
        }

        //DST:ToR
        for(auto &j : problematic_tors) {
            if(i2 == j) {
                continue;       // Same ToR
            }
            //Compute exception SRC:DST
            unsigned char td = DM[i2][j] - 1; // Target distance
            if(td >= 15) {      // Unreachable
                e_t e;
                e.a = tors[j-f].a;
                info.ex.push_back(e);
            } else {
                //Check fabrics that reach it with the expected distance from the v1 group
                vector<bool> valids = info.v1;
                for(addr_t k = 0; k < f; k++) {
                    if(DM[k][j] != td) {
                        valids[k] = false;
                    }
                }
                if(valids != info.v1) {
                    e_t e;
                    e.a = tors[j-f].a;
                    for(addr_t k = 0; k < f; k++) {
                        if(valids[k]) {
                            e.valid.push_back(k);
                        }
                    }
                    info.ex.push_back(e);
                }
            }
        }
    }
    // SRC:Fabric
    for(addr_t i = 0; i< f; i++){
        Fab_info_t & info = fabs[i];
        if(info.disconnectedDown) {
            continue;           // Already disconnected
        }

        //DST:ToR
        for(auto &j : problematic_tors) {
            if(DM[i][j] != 1) {
                //Compute exception SRC:DST
                vector<bool> valids = info.v1;
                unsigned char td = DM[i][j] - 1; // Target distance

                for(addr_t k = 0; k < t; k++) {
                    if(td != DM[j][k+f]) {
                        valids[k] = false;
                    }
                }

                if(valids != info.v1) {
                    e_t e;
                    e.a = tors[j-f].a;
                    for(addr_t k = 0; k < f; k++) {
                        if(valids[k]) {
                            e.valid.push_back(k);
                        }
                    }
                    info.ex.push_back(e);
                }
            }
        }

        // DST:Fabric
        for(addr_t j = 0; j< f; j++){
            if(i == j) {
                continue;           // Same node
            }
            if(DM[i][j] != 2) {
                //Compute exception SRC:DST
                vector<bool> valids = info.v1;
                unsigned char td = DM[i][j] - 1; // Target distance

                for(addr_t k = 0; k < t; k++) {
                    if(td != DM[j][k+f]) {
                        valids[k] = false;
                    }
                }

                if(valids != info.v1) {
                    e_t e;
                    e.a = fabs[j].a;
                    for(addr_t k = 0; k < f; k++) {
                        if(valids[k]) {
                            e.valid.push_back(k);
                        }
                    }
                    info.ex.push_back(e);
                }
            }
        }
    }

    //Compute out-Pod exceptions

    set<addr_t> problematicPod;
    set<addr_t> problematicPod_Fabs;
    set<addr_t> problematicPod_Tors;
    map<addr_t, set<addr_t> > problematicPod_extra;

    //Compute Pods with problems
    for(auto &st : outStats) {
        addr_t pd = st.first;
        if(pd == myZone) {
            continue;
        }
        zone_stat_t & zs = st.second;
        if(!zs.downFabs.empty() || !zs.problemsAtFabs.empty()) {
            problematicPod.insert(pd);
            problematicPod_Fabs.insert(pd);
        }
        if(!zs.probToRtoFabDistance.empty()) {
            problematicPod.insert(pd);
            problematicPod_Tors.insert(pd);
        }
    }
    for(auto &n : outzone_status) {
        for(auto & fail : n.second.fails) {
            addr_t pd = getZone(fail);
            if(pd !=  myZone) {
                continue;
            }
            problematicPod.insert(pd);
            problematicPod_Fabs.insert(pd);
            problematicPod_extra[pd].insert(n.first);
        }
    }

    for(auto &pd : problematicPod) {
        zone_stat_t & zs = outStats[pd];

        //Check reachability at fabrics
        bool reachableAllValids = true;
        bool reachable = true;

        bool hasToRproblems = problematicPod_Tors.find(pd) != problematicPod_Tors.end();
        vector< vector<bool> >reachFromTor;

        vector<bool> reachableFabs (f, true);

        if(problematicPod_Fabs.find(pd) != problematicPod_Fabs.end()) {
            reachable = false;

            //Compute exceptions to reach Pod
            for(addr_t i = 0; i < f; i++) {
                Fab_info_t & info = fabs[i];
                if(info.disconnectedUp) {
                    reachableFabs[i] = false;
                    continue;           //Already disconnected
                }

                addr_t df = getAddr(pd, i);
                if(zs.downFabs.find(df) != zs.downFabs.end()) {
                    // Destination fabric is disconnected up or down
                    e_t e;
                    e.a = getAddr(pd, 0);
                    e.m = 8;       /// Check that if the mask for Pod is 16
                    info.ex.push_back(e);

                    reachableAllValids = false;
                    reachableFabs[i] = false;
                } else {
                    vector<bool> valids = info.v2;
                    if(zs.problemsAtFabs.find(df) != zs.problemsAtFabs.end()) {
                        // Destination fabric has problems
                        for(auto & fail : zs.problemsAtFabs[df]) {
                            valids[getIdentifier(fail)] = false;
                        }
                    }

                            //**Should be preparsed and done well...
                    for(auto &n : outzone_status) {
                        if(getZone(n.first) == i) {
                            for(auto & fail : n.second.fails) {
                                if(getZone(fail) == pd) {
                                    valids[getIdentifier(fail)] = false;
                                }
                            }
                        }
                    }

                    if(valids != info.v2) {
                        e_t e;
                        e.a = getAddr(pd, 0);
                        e.m = 8;       /// Check that if the mask for Pod is 16
                        for(addr_t k = 0; k < s; k++) {
                            if(valids[k]) {
                                e.valid.push_back(k+t);
                            }
                        }
                        info.ex.push_back(e);

                        if(e.valid.empty()) {
                            reachableAllValids = false;
                            reachableFabs[i] = false;
                        }

                    }

                }
                reachable |= reachableFabs[i];
            }
            if(!reachable) {                    // Not reachable by any node
                for(addr_t i = 0; i < t; i++) {
                    ToR_info_t & info = tors[i];
                    e_t e;
                    e.a = getAddr(pd, 0);
                    e.m = 8;       /// Check that if the mask for Pod is 16
                    info.ex.push_back(e);
                }

            } else  if(!reachableAllValids) {   //If not reachable by all live fabrics v2
                reachFromTor = vector< vector<bool> >(t);
                // For each ToR, exception using fabrics in reachableFabs and DM[tor][fab] == min
                for(addr_t i = 0; i < t; i++) {
                    ToR_info_t & info = tors[i];
                    addr_t t2 = i+f;

                    if(info.disconnected) {
                        continue;           // Already disconnected
                    }

                    if(info.v2 != reachableFabs) {
                        e_t e;
                        e.a = getAddr(pd, 0);
                        e.m = 8;       /// Check that if the mask for Pod is 16

                        reachFromTor[i] = vector<bool>(f, false);
                        vector<bool> & tmp = reachFromTor[i];
                        //Check for fabrics both connected and that reach the dst
                        for(addr_t k = 0; k < f; k++) {
                            if(reachableFabs[k] && info.v2[k]) {
                                e.valid.push_back(k);
                                tmp[k] = true;
                            }
                        }

                        //If there are no shared fabrics, search the nearest to valid ones
                        if(e.valid.empty()) {

                            unsigned char d = 16;
                            // Compute the best distance to a valid fabric
                            for(addr_t k = 0; k < f; k++) {
                                if(DM[t2][k] != 1) {
                                    continue;       // Not a connected fabric
                                }
                                for(addr_t q = 0; q < f; q++) {
                                    if(k==q || !reachableFabs[q]) {
                                        continue;   // Same node or not an useful fabric
                                    }
                                    unsigned char d2 = DM[k][q];
                                    if(d > d2) {
                                        d = d2;
                                    }
                                }
                            }
                            if(d < 16) {
                                // Compute the best distance to a valid fabric
                                for(addr_t k = 0; k < f; k++) {
                                    if(DM[t2][k] != 1) {
                                        continue;       // Not a connected fabric
                                    }
                                    for(addr_t q = 0; q < f; q++) {
                                        if(k==q || !reachableFabs[q]) {
                                            continue;   // Same node or not an useful fabric
                                        }
                                        if(DM[k][q] == d) {
                                            e.valid.push_back(k);
                                            tmp[k] = true;
                                        }
                                    }
                                }
                            }
                        }

                        info.ex.push_back(e);
                    }
                }
            }
        }

        if(reachable && hasToRproblems) {
            //Compute exceptions to ToRs

            for(auto & j : zs.probToRtoFabDistance) {
                vector<unsigned char> fabD(f, 16);
                vector<unsigned char> torD(t, 16);


                //Compute distance {fabric->fabric}-d1->ToR, 16 = unreachable
                for(addr_t i = 0; i< f; i++) {
                    if(reachableFabs[i]) {
                        fabD[i] = j.second[i];
                    }
                }

                //Reachability from ToRs
                // ToR -d2-> {fabric -> fabric} -d1-> ToR (Minimize d1+d2)
                for(addr_t i = 0; i < t; i++) {
                    addr_t i2 = i+f;

                    unsigned char d = 16;

                    //Compute target distance
                    for(addr_t k = 0; k < f; k++) {
                        if(DM[i2][k] != 1) {
                            continue;       // Non-reachable fabric
                        }
                        for(addr_t q = 0; q < f; q++) {
                            if(fabD[q] >= 16) {
                                continue;   // Same node or unreachable dst
                            }
                            unsigned char d2 = DM[k][q] + fabD[q];

                            if(d > d2) {
                                d = d2;
                            }
                        }
                    }
                    torD[i] = d+1;

                    ToR_info_t & info = tors[i];
                    e_t e;
                    e.a = j.first;

                    vector<bool> cur = info.v2;
                    if(!reachFromTor.empty() && !reachFromTor[i].empty()) {
                        cur = reachFromTor[i];
                    }

                    vector<bool> tmp(f, false);
                    // If reachable, search valid fabs
                    if(d < 16) {
                        for(addr_t k = 0; k < f; k++) {
                            if(DM[i2][k] != 1) {
                                continue;       // Non-reachable fabric
                            }
                            for(addr_t q = 0; q < f; q++) {
                                if(fabD[q] >= 16) {
                                    continue;   // Same node or unreachable dst
                                }
                                if(DM[k][q] + fabD[q] == d) {
                                    e.valid.push_back(k);
                                    tmp[k] = true;
                                }
                            }
                        }
                    } // Else unreachable

                    if(tmp != cur) {
                        info.ex.push_back(e);
                    }
                }

                //Reachability from fabrics
                // {fabric -> fabric} -d1-> ToR,
                // {fabric -> ToR} -d2-> {fabric -> fabric} -d3-> ToR
                // if(d1 <= d2 +d3), use d1, else use d2+d3, case base, d1 <= 3
                for(addr_t i = 0; i < f; i++) {
                    if(fabD[i] <= 3) {
                        continue;
                    }
                    unsigned char d = fabD[i]-1;
                    bool useTor = false;
                    for(addr_t k = 0; k < t; k++) {
                        if(DM[i][k+f] != 1) {
                            continue;
                        }
                        if(torD[k] < d) {
                            d = torD[k];
                            useTor = true;
                        }
                    }
                    if(useTor) {
                        Fab_info_t & info = fabs[i];
                        e_t e;
                        e.a = j.first;
                        for(addr_t k = 0; k < t; k++) {
                            if(DM[i][k+f] != 1) {
                                continue;
                            }
                            if(torD[k] == d) {
                                e.valid.push_back(k);
                            }
                        }
                        info.ex.push_back(e);
                    }
                }
            }
        }
    }

    //Quick exceptions to reach spines from ToRs with problems
    for(addr_t i = 0; i< t; i++) {
        ToR_info_t & info = tors[i];
        if(info.problems <= 0) {
            continue;
        }
        for(addr_t j = 0; j < f; j++) {
            if(info.v2[j]) {
                continue;
            }

            addr_t i2 = i+f;

            e_t e;
            e.a = getAddr(j, 0);
            e.m = 8;

            //Search replacement to reach spine j
            unsigned char td = DM[i2][j] - 1;
            for(addr_t k = 0; k < f; k++) {
                if(k == j) {
                    continue;
                }
                if(DM[k][j] == td) {
                    e.valid.push_back(k);
                }
            }

            info.ex.push_back(e);
        }
    }

}


void RoutingManager::sendExceptions() {
    bool retry = false;
    for(auto d : tors) {
        if(d.lastReceived < exception_seq) {
            Address dstA = Address(getRawAddr_t(d.a).c_str(), myAddress.getDifName().getName().c_str());

            RException * ex = new RException();
            ex->setDestination(dstA);

            ex->seqId = exception_seq;
            ex->v1 = d.v1;
            ex->v2 = d.v2;
            ex->ex = d.ex;

            sendUpdate(ex);
            retry = true;
        }
    }

    for(auto d : fabs) {
        if(d.lastReceived < exception_seq) {
            Address dstA = Address(getRawAddr_t(d.a).c_str(), myAddress.getDifName().getName().c_str());

            RException * ex = new RException();
            ex->setDestination(dstA);

            ex->seqId = exception_seq;
            ex->v1 = d.v1;
            ex->v2 = d.v2;
            ex->ex = d.ex;

            sendUpdate(ex);
            retry = true;
        }
    }

    if(retry && !exceptions_timer->isScheduled()) {
        scheduleAt(simTime()+exceptions_timer_updateInterval, exceptions_timer);
    }
}
