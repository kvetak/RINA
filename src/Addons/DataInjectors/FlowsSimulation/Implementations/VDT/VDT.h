#pragma once

#include "Addons/DataInjectors/FlowsSimulation/Inj_t.h"
#include "Addons/DataInjectors/FlowsSimulation/Flows/sender_t.h"
#include "Addons/DataInjectors/FlowsSimulation/Flows/client_t.h"
#include "Addons/DataInjectors/FlowsSimulation/Flows/server_t.h"

class VDT : public Inj_t {
public :

    //Receive data from other node
    virtual void receiveData(const string & _src, const string & _qos, shared_ptr<Flow_Data> data);

    //Request finalized
    void requestComplete(Flow_t * app, simtime_t requestedAt);

    //Receive self messages
    virtual void handleMessage(cMessage *msg);

    //Prepare flows and more
    virtual void postInitialize();

    //At the end
    virtual void finish();

    //Voice flows parameters
    string V_QOS;
    unsigned int V_PDUSize_min;         // Headers included
    unsigned int V_PDUSize_max;         // Headers included
    double V_AVG_FlowRate;
    double V_ON_Duration_AVG;
    double V_ON_Duration_VAR;
    double V_OFF_Duration_AVG;
    double V_OFF_Duration_VAR;
    double V_Interval;

    //Data request flows parameters
    string D_QOS;
    unsigned int D_Request_PDUSize;     // Headers included
    unsigned int D_Data_PDUSize;        // Headers included
    double D_AVG_FlowRate;
    double D_ON_FlowRate;
    double D_OFF_Duration_AVG;
    double D_OFF_Duration_VAR;
    double D_Interval;
    unsigned int D_RequestSize;

    //Transfer flows parameters
    string T_QOS;
    unsigned int T_Request_PDUSize;     // Headers included
    unsigned int T_Data_PDUSize;        // Headers included
    double T_AVG_FlowRate;
    unsigned int T_WINDOW_MAX;
    unsigned int T_WINDOW_UPDATE;
    double T_Interval;


    //Flows
    map<int, sender_t *> senders;
    map<string, map<int, client_t *> > clients;
    map<string, map<int, server_t *> > servers;

};
