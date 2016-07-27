#include "ONOFInj.h"

#include "sender_t.h"
#include "client_t.h"
#include "server_t.h"

#include "OFInfectionComparator.h"
#include "OFStaticGenerator.h"
#include "InjListener.h"



int voice_f::min_pdu_len = 100;
int voice_f::max_pdu_len = 300;
double voice_f::interval = 0.02;
double voice_f::idle_time = 9.0;
double voice_f::burst_time = 3.0;

double client_t::ackT = 0.1;
int video_f::request_size = 50;
double video_f::idle_time = 9.0;
int video_f::request_len = 2000;
double video_f::request_interval = 0.01;

double server_t::ackT = 0.1;
int server_t::pdu_size = 1350;

Define_Module(ONOFInj);

Inj_PDU * ONOFInj::genPDU(const pduReq & req) {
    Inj_PDU * pdu = new Inj_PDU();
    connID.setQoSId(req.f->QoS);
    connID.setSrcCepId(req.f->flowId);
    pdu->setConnId(connID);
    pdu->setSrcAddr(srcAddr);
    pdu->setSrcApn(srcAddr.getApn());
    dstAddr = Address(req.f->dstAddr.c_str(), dif.c_str());
    pdu->setDstAddr(dstAddr);
    pdu->setDstApn(dstAddr.getApn());
    pdu->xdata = shared_ptr < Inj_data > (req.data);
    pdu->setByteLength(pdu->xdata->len + header);
    return pdu;
}


void ONOFInj::initialize() {
    //Init ini/fin times
    double iniT = par("ini").doubleValue();
    if (iniT < 0 || par("infectedIPC").stdstringValue() == "") { return; }
    fin = par("fin").doubleValue();

    //Get IPCP
    cModule * ipc = this->getParentModule()->getSubmodule(par("infectedIPC").stringValue());
    if (ipc == nullptr) { return; }

    //Connect to RMT
    cModule * rmt = ipc->getSubmodule("relayAndMux")->getSubmodule("rmt");
    rmt->addGate("infGate", cGate::INOUT, false);
    cGate * modIn = rmt->gateHalf("infGate", cGate::INPUT);
    cGate * modOut = rmt->gateHalf("infGate", cGate::OUTPUT);
    cGate * In = gateHalf("g", cGate::INPUT);
    cGate * Out = gateHalf("g", cGate::OUTPUT);
    modOut->connectTo(In);
    Out->connectTo(modIn);

    //Conect comparator
    cModule *ac = ipc->getSubmodule("resourceAllocator")->getSubmodule( "addressComparator");
    if (OFInfectionComparator * oac = dynamic_cast<OFInfectionComparator*>(ac)) { oac->p = this; }

    //Conect pdufwgen
    cModule *fwdg = ipc->getSubmodule("resourceAllocator")->getSubmodule( "pduFwdGenerator");
    if (OFStaticGenerator::OFStaticGenerator * ofwdg = dynamic_cast<OFStaticGenerator::OFStaticGenerator*>(fwdg)) { ofwdg->inj = this; }

    //Init node info
    dif = ipc->par("difName").stdstringValue();
    src = ipc->par("ipcAddress").stdstringValue();
    srcAddr = Address(src.c_str(), dif.c_str());
    dstAddr = Address("", dif.c_str());
    nextFlowId = 0;
    connID.setDstCepId(-1);
    header = par("header_size").longValue();
    received = 0;
    sent = 0;
    sentAct = 0;
    sentRet = 0;
    sentSRt = 0;
    sentActk = 0;

    scheduleAt(iniT, &iniFlows);
}

void ONOFInj::handleMessage(cMessage *msg) {
    Enter_Method_Silent();
    if(strcmp("MonitorMsg", msg->getName())==0){
        MonitorMsg * monMsg = dynamic_cast<MonitorMsg *>(msg);
        if(monMsg->type.compare("ACK")==0){
            if(senders.count(monMsg->ackInfo.flowID)>0){
                scheduleAt( simTime(), &(senders[monMsg->ackInfo.flowID]->at));
            }
            else{
                string nodes_raw = par("nodes").stdstringValue();
                vector<string> nodes = split(nodes_raw, ' ');
                for (const string & n : nodes) {
                    if(clients[n].count(monMsg->ackInfo.flowID)>0)
                    {
                        scheduleAt( simTime(), &(clients[n][monMsg->ackInfo.flowID]->at));
                    }
                }
            }
        }
        else if(monMsg->type.compare("NACK")==0){
            //msgDataBase.erase(monMsg->ackInfo.flowID);
        }

    }
    else{
        if(msg == &iniFlows) { startFlows(); }
        else if(actTimer * t = dynamic_cast<actTimer *>(msg)) {
            pduReq r = t->f->act(this, simTime() > fin);
            if(r.data != nullptr) { send(genPDU(r), "g$o"); sent++; sentAct++; }
        } else if(retransTimer * t = dynamic_cast<retransTimer *>(msg)) {
            pduReq r = t->f->ret(this, simTime() > fin);
            if(r.data != nullptr) { send(genPDU(r), "g$o"); sent++; sentRet++; }
        } else if(selretransTimer * t = dynamic_cast<selretransTimer *>(msg)) {
            pduReq r = t->f->sret(this, simTime() > fin);
            if(r.data != nullptr) { send(genPDU(r), "g$o"); sent++; sentSRt++; }
        } else if(ackTimer * t = dynamic_cast<ackTimer *>(msg)) {
            pduReq r = t->f->ack(this, simTime() > fin);
            if(r.data != nullptr) { send(genPDU(r), "g$o"); sent++; sentActk++; }
        } else {
            cout << "Unknown message received"<< endl;
        }
    }
}
void ONOFInj::finish() {
    cout << src << endl;
    cout << " received " << received << endl;
    cout << " sent " << sent << endl;
    cout << sentAct<<" - "<<sentRet<<" - "<<sentSRt<<" - "<<sentActk<<endl;


    for(auto a : senders) {
        cancelEvent(&(a.second->at));
        delete a.second;
    }
    for(auto a : clients) { for (auto b : a.second) {
        cancelEvent(&(b.second->at));
        cancelEvent(&(b.second->rt));
        cancelEvent(&(b.second->kt));
        delete b.second;
    } }
    for(auto a : servers) { for (auto b : a.second) {
        cancelEvent(&(b.second->at));
        cancelEvent(&(b.second->rt));
        cancelEvent(&(b.second->kt));
        cancelEvent(&(b.second->st));
        delete b.second;
    } }
}

void ONOFInj::receiveData(const string & _src, const string & _qos, shared_ptr<Inj_data> data) {
    Enter_Method_Silent();

    if(uniform(0.0,1.0)> par("dropProb").doubleValue()) { return; }

    received++;

    if(shared_ptr<sender_d> d = dynamic_pointer_cast < sender_d > (data)) {
        // Received Data from sender
        InjListener::instance->voiceReceived(_src, src, d->flow, simTime() - d->t0);

    } else if(shared_ptr<client_d> d = dynamic_pointer_cast < client_d > (data)) {
        // Received Data from client -> server
        server_t * app = servers[_src][d->flow];
        if(app == nullptr) {
            app = createServer(_src, _qos, d->flow);
            servers[_src][d->flow] = app;
        }
        app->receive(this, d);
    } else if(shared_ptr<server_d> d = dynamic_pointer_cast < server_d > (data)) {
        // Received Data from server -> client
        client_t * app = clients[_src][d->flow];
        if(app == nullptr) {
            cout << "Received data for unknown app"<< endl;
        }
        app->receive(this, d, simTime().dbl() > fin);
    }
}

server_t * ONOFInj::createServer(string dst, string qos, int flow) {
    server_t * app = new server_t(flow, dst, qos);
    app->at.f = app;
    app->rt.f = app;
    app->st.f = app;
    app->kt.f = app;
    return app;
}

void ONOFInj::startFlows() {
    string nodes_raw = par("nodes").stdstringValue();
    vector<string> nodes = split(nodes_raw, ' ');

    for (const string & n : nodes) {
        if (n == "" || n == src) { continue; }
        for (int i = 0; i < par("voice_flows").longValue(); i++) {
            voice_f * f = new voice_f(nextFlowId, n, par("voice_qos").stdstringValue());
            f->at.f = f;
            senders[nextFlowId] = f;


            MonitorMsg* Monmsg = new MonitorMsg();
            Monmsg->type = "Rsv_Req";
            Monmsg->rsv_ReqInfo.flowId = nextFlowId;
            Monmsg->rsv_ReqInfo.nodeIdDst = f->dstAddr;
            Monmsg->rsv_ReqInfo.nodeIdOrg = srcAddr.getIpcAddress().getName();
            Monmsg->rsv_ReqInfo.qos = f->QoS;
            cModule *targetModule = getModuleByPath("fullPathMonitor");
            take(Monmsg);
            sendDirect(Monmsg, simTime() + uniform(0.0, voice_f::idle_time + voice_f::burst_time), 0, targetModule, "radioIn");

            //scheduleAt( simTime() + uniform(0.0, voice_f::idle_time + voice_f::burst_time), &f->at);
            nextFlowId++;
        }
        for (int i = 0; i < par("client_flows").longValue(); i++) {
            video_f * f = new video_f(nextFlowId, n, par("client_qos").stdstringValue());
            f->at.f = f;
            f->rt.f = f;
            f->kt.f = f;
            clients[n][nextFlowId] = f;

            f->setNextUntil();
            f->setNextRate();

            MonitorMsg* Monmsg = new MonitorMsg();
            Monmsg->type = "Rsv_Req";
            Monmsg->rsv_ReqInfo.flowId = nextFlowId;
            Monmsg->rsv_ReqInfo.nodeIdDst = f->dstAddr;
            Monmsg->rsv_ReqInfo.nodeIdOrg = srcAddr.getIpcAddress().getName();
            Monmsg->rsv_ReqInfo.qos = f->QoS;
            cModule *targetModule = getModuleByPath("fullPathMonitor");
            take(Monmsg);
            sendDirect(Monmsg, uniform(0.0, video_f::idle_time), 0, targetModule, "radioIn");

            nextFlowId++;
            //scheduleAt( simTime() + uniform(0.0, video_f::idle_time), &f->at);
        }
    }
}
