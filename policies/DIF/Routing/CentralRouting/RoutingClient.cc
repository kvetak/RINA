#include "DIF/Routing/CentralRouting/RoutingClient.h"

Register_Class(RoutingClient);

void RoutingClient::onPolicyInit() {
    started = false;

    in_timer = new cMessage("In-zone update timer");
    in_updateInterval = par("in_updateInterval");

    status_timer = new cMessage("Status timer");
    status_updateInterval = par("status_updateInterval").doubleValue();

    re_status_timer = new cMessage("Re-Status timer**");
    re_status_updateInterval = par("re_status_updateInterval").doubleValue();
}

void RoutingClient::finish() {


    if(in_timer != nullptr) { cancelAndDelete(in_timer); }
    if(status_timer != nullptr) { cancelAndDelete(status_timer); }
    if(re_status_timer != nullptr) { cancelAndDelete(re_status_timer); }


    if(par("printAtEnd").boolValue()) {
        cout << hex;
        cout << "Client "<< myAddress << endl;
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

void RoutingClient::setMyA(const addr_t & a) {
    myA = a;
    st.node_addr = myA;
    inzone.setId(getIdentifier(myA));
}

void RoutingClient::setMasterAddr(const Address & m) {
    master = m;
}

void RoutingClient::addNei(const addr_t &a, const Address &addr, const bool &samezone, const elink_t &link) {
    neiInfo & info = neis[a];
    info.addr = addr;
    info.samezone = samezone;
    info.link = link;
}

void RoutingClient::onFlow(addr_t a) {
    neiInfo & info = neis[a];
    info.status = true;
    if (info.samezone) {
        sendUpdates();
    }
    if (started) {
        informStatus();
    }

    r_stat |= R_INZONE_CHANGES;
}

void RoutingClient::offFlow(addr_t a) {
    neiInfo & info = neis[a];
    info.status = false;
    if (info.samezone) {
        inzone.removeFrom(getIdentifier(a) );
        sendUpdates();
    }
    if (started) {
        informStatus();
    }

    r_stat |= R_INZONE_CHANGES;
}

void RoutingClient::sendUpdates() {
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

void RoutingClient::informStatus() {
    if(! started ) { return; }

    st.fails.clear();
    for(auto nei : neis) {
        if(! nei.second.status) {
            st.fails.insert(nei.second.link);
        }
    }
    st.seqId++;

    if(!status_timer->isScheduled()) {
        scheduleAt(simTime() + status_updateInterval, status_timer);
    }
}

void RoutingClient::sendInformStatus() {

    if(status_timer->isScheduled()) {
        cancelEvent(status_timer);
    }

    if(re_status_timer->isScheduled()) {
        cancelEvent(re_status_timer);
    }

    //Send update to random manager
    RStatus * up = new RStatus();
    up->setDestination(master);
    up->status = st;
    up->received = false;
    sendUpdate(up);
    if(re_status_timer->isScheduled()) {
        scheduleAt(simTime() + re_status_updateInterval, re_status_timer);
    }
}

void RoutingClient::handleMessage(cMessage * msg) {
    if(msg == in_timer) {
        sendUpdates();
        return;
    }

    if(msg == status_timer || msg == re_status_timer) {
        sendInformStatus();
        return;
    }

    delete msg;
}

bool RoutingClient::processUpdate(IntRoutingUpdate * update) {
    if (RException * up = dynamic_cast<RException *>(update)) {
        // Received new exceptions
        v1 = up->v1;
        v2 = up->v2;
        ex = up->ex;
        r_stat |= R_EXCEPTIONS_CHANGES;

        RException * res = new RException();
        res->setDestination(up->getSource());
        res->received = true;
        res->seqId = up->seqId;
        sendUpdate(res);

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

    if (RStatus * up = dynamic_cast<RStatus *>(update)) {
        // Received ack of status update -> cancel re-send if correct
        if(st.seqId == up->status.seqId) {
            if(re_status_timer->isScheduled()){
                cancelEvent(re_status_timer);
            }
        }
        return r_stat != 0;
    }


    if (RStart * up = dynamic_cast<RStart *>(update)) {
        // Start sending status updates
        if (!started) {
            started = true;
            // Broadcast start msg
            for(auto nei : neis) {
                if(! nei.second.status) { continue; }
                RStart * rup = new RStart();
                rup->zone = up->zone;
                rup->setDestination(nei.second.addr);
                sendUpdate(rup);
            }
        }
        return r_stat != 0;
    }

    return r_stat != 0 ;
}
