#include "FullPathMonitor.h"
#include <iostream>
#include <fstream>


Define_Module(FullPathMonitor::FullPathMonitor);

namespace FullPathMonitor {

    void FullPathMonitor::initialize(){

    }
    void FullPathMonitor::handleMessage(cMessage * msg){

        MultipathStructs::MonitorMsg * monMsg = dynamic_cast<MultipathStructs::MonitorMsg *>(msg);
        if(monMsg->type.compare("Register_Node"))
        {

        }
        else if(monMsg->type.compare("Monitoring_Param")){
            //Codigo
        }
        else if(monMsg->type.compare("Rsv_Req")){
            //Codigo
        }
        else if(monMsg->type.compare("Free_Req")){
            //Codigo
        }
        else if(monMsg->type.compare("Ack")){
            //Codigo
        }
        else{
            EV << "Incorrect Message" << endl;
        }
//        EV << "Mensaje recibido" << endl;
//        cModule *targetModule = getModuleByPath("InfectedMultipathFatTree.AS1.relayIpc.relayAndMux.rmt");
//        MonitorMsg *msg2 = new MonitorMsg("MonitorMsg");
//        msg2->setType("ack");
//        take(msg2);
//        sendDirect(msg2, targetModule, "radioIn");

    }
    void FullPathMonitor::finish(){

    }
}
