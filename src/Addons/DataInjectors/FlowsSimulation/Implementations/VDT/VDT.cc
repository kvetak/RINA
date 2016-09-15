#include "VDT.h"
#include "VDT_Listener.h"

Define_Module(VDT);

void VDT::receiveData(const string & _src, const string & _qos, shared_ptr<Flow_Data> data) {
    Enter_Method_Silent();

    if(shared_ptr<sender_d> d = dynamic_pointer_cast < sender_d > (data)) {
        // Received Data from sender
        VDT_Listener::instance->voiceRecv(_src, src, _qos, d->flow, simTime() - d->t0);

    } else if(shared_ptr<client_d> d = dynamic_pointer_cast < client_d > (data)) {
        // Received Data from client -> server

        VDT_Listener::instance->requestRecv(_src, src, _qos, d->flow, simTime() - d->t0);

        server_t * app = servers[_src][d->flow];
        if(app == nullptr) {
            app = new server_t(d->flow, _src, _qos);
            app->at.f = app;
            app->rt.f = app;
            app->st.f = app;
            app->kt.f = app;
            servers[_src][d->flow] = app;
        }
        app->receive(this, d);
    } else if(shared_ptr<server_d> d = dynamic_pointer_cast < server_d > (data)) {
        // Received Data from server -> client

        VDT_Listener::instance->dataRecv(_src, src, _qos, d->flow, simTime() - d->t0);

        client_t * app = clients[_src][d->flow];
        if(app == nullptr) { error("Received data for unknown server."); }
        app->receive(this, d, simTime().dbl() > finT);
    }
}

void VDT::requestComplete(Flow_t * app, simtime_t requestedAt) {
    VDT_Listener::instance->requestEnd(src, app->dstAddr, app->QoS, app->flowId, simTime() - requestedAt);
}

void VDT::handleMessage(cMessage *msg) {
    Enter_Method_Silent();
    if(Flow_timer * t = dynamic_cast<Flow_timer *>(msg)) {
        PDU_Req r;
        switch(t->type) {
            case action : r = t->f->act(this, simTime() > finT);  break;
            case retrans : r = t->f->ret(this, simTime() > finT);  break;
            case selRetrans : r = t->f->sret(this, simTime() > finT);  break;
            case ackTime : r = t->f->ack(this, simTime() > finT);  break;
            default : error("Nil timer");
        }
        if(r.data != nullptr) {
            send(genPDU(r), "g$o");

            if(dynamic_cast < sender_d *> (r.data)) {
                // Sent Voice Data
                VDT_Listener::instance->voiceSent(src, r.f->dstAddr, r.f->QoS, r.f->flowId);
            } else if(dynamic_cast < client_d *> (r.data)) {
                // Sent data
                VDT_Listener::instance->requestSent(src, r.f->dstAddr, r.f->QoS, r.f->flowId);
            } else if(dynamic_cast < server_d *> (r.data)) {
                // Sent request
                VDT_Listener::instance->dataSent(src, r.f->dstAddr, r.f->QoS, r.f->flowId);
            }
        }
    }
}

void VDT::postInitialize() {
// Voice parameters initialization
    V_QOS = par("V_QOS").stdstringValue();
    V_PDUSize_min = par("V_PDUSize_min").longValue();
    V_PDUSize_max = par("V_PDUSize_max").longValue();
    V_AVG_FlowRate = par("V_AVG_FlowRate").doubleValue()*1000.0/8.0;
    V_ON_Duration_AVG = par("V_ON_Duration_AVG").doubleValue();
    V_ON_Duration_VAR = par("V_ON_Duration_VAR").doubleValue();
    V_OFF_Duration_AVG = par("V_OFF_Duration_AVG").doubleValue();
    V_OFF_Duration_VAR = par("V_OFF_Duration_VAR").doubleValue();
    V_Interval = ((V_PDUSize_min + V_PDUSize_max) / 2.0)
            * ((V_ON_Duration_AVG + V_OFF_Duration_AVG) / V_ON_Duration_AVG)
            / V_AVG_FlowRate;


// Data request parameters initialization
    D_QOS = par("D_QOS").stdstringValue();
    D_Request_PDUSize = par("D_Request_PDUSize").longValue();
    D_Data_PDUSize = par("D_Data_PDUSize").longValue();
    D_AVG_FlowRate = par("D_AVG_FlowRate").doubleValue()*1000.0/8.0;
    D_ON_FlowRate = par("D_ON_FlowRate").doubleValue()*1000.0/8.0;
    D_OFF_Duration_AVG = par("D_OFF_Duration_AVG").doubleValue();
    D_OFF_Duration_VAR = par("D_OFF_Duration_VAR").doubleValue();
    D_Interval = D_Data_PDUSize / D_ON_FlowRate;
    D_RequestSize = (int)ceil(D_AVG_FlowRate * D_OFF_Duration_AVG / D_Data_PDUSize);


// Transfer parameters initialization
    T_QOS = par("T_QOS").stdstringValue();
    T_Request_PDUSize = par("T_Request_PDUSize").longValue();
    T_Data_PDUSize = par("T_Data_PDUSize").longValue();
    T_AVG_FlowRate = par("T_AVG_FlowRate").doubleValue()*1000.0/8.0;
    T_WINDOW_MAX = par("T_WINDOW_MAX").longValue();
    T_WINDOW_UPDATE = par("T_WINDOW_UPDATE").longValue();
    T_Interval = T_Data_PDUSize / T_AVG_FlowRate;


// XML :: Read Flows <src == src, dst, V, D, T>
    cXMLElement* Xml = par("data").xmlValue();
    if(Xml == nullptr) { return; }

    int fid = 0;

    cXMLElementList flowsXML = Xml->getChildrenByTagName("set");
    for (cXMLElement * n : flowsXML) {
        string s_src = n->getAttribute("src");
        if (s_src != src) { continue; }

        string s_dst = n->getAttribute("dst");
        if (s_dst == "" || s_dst == src) { continue; }

        unsigned int s_V = atoi(n->getAttribute("V"));
        unsigned int s_D = atoi(n->getAttribute("D"));
        unsigned int s_T = atoi(n->getAttribute("T"));

        for(unsigned int i = 0; i < s_V; i++) {
            cout << "flow :: " << fid <<endl;
            voice_c * f = new voice_c(fid, s_dst, V_QOS,
                    V_PDUSize_min - headers, V_PDUSize_max - headers, V_Interval,
                    V_OFF_Duration_AVG - V_OFF_Duration_VAR, V_OFF_Duration_AVG + V_OFF_Duration_VAR,
                    V_ON_Duration_AVG - V_ON_Duration_VAR, V_ON_Duration_AVG + V_ON_Duration_VAR);
            f->at.f = f;
            senders[fid] = f;
            fid++;
            scheduleAt( iniT + uniform(0.0, V_OFF_Duration_AVG), &f->at);
        }

        if(s_D % 2 == 1) {
            video_c * f = new video_c(fid, s_dst, D_QOS,
                    D_Request_PDUSize - headers, D_Data_PDUSize - headers, D_RequestSize,
                    D_Interval, D_OFF_Duration_AVG);
            f->at.f = f;
            f->rt.f = f;
            f->kt.f = f;
            clients[s_dst][fid] = f;
            fid++;
            scheduleAt( iniT + uniform(0.0, D_OFF_Duration_AVG), &f->at);
        }
        for(unsigned int i = 1; i < s_D; i+=2) {
            double R = uniform(0.0, D_OFF_Duration_VAR);

            video_c * f = new video_c(fid, s_dst, D_QOS,
                    D_Request_PDUSize - headers, D_Data_PDUSize - headers, D_RequestSize,
                    D_Interval, D_OFF_Duration_AVG + R);
            f->at.f = f;
            f->rt.f = f;
            f->kt.f = f;
            clients[s_dst][fid] = f;
            fid++;
            scheduleAt( iniT + uniform(0.0, D_OFF_Duration_AVG), &f->at);

            f = new video_c(fid, s_dst, D_QOS,
                    D_Request_PDUSize - headers, D_Data_PDUSize - headers, D_RequestSize,
                    D_Interval, D_OFF_Duration_AVG - R);
            f->at.f = f;
            f->rt.f = f;
            f->kt.f = f;
            clients[s_dst][fid] = f;
            fid++;
            scheduleAt( iniT + uniform(0.0, D_OFF_Duration_AVG), &f->at);
        }

        for(unsigned int i = 0; i < s_T; i++) {
            data_c * f = new data_c(fid, s_dst, T_QOS,
                    T_Request_PDUSize - headers, T_Data_PDUSize - headers,
                    T_Interval, T_WINDOW_MAX, T_WINDOW_UPDATE);
            f->at.f = f;
            f->rt.f = f;
            f->kt.f = f;
            clients[s_dst][fid] = f;
            fid++;
            scheduleAt( iniT + uniform(0.0, T_Interval), &f->at);
        }
    }
}

void VDT::finish() {
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
