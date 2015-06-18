#include "IntPDUFG.h"
#include <vector>

IntPDUFG::IntPDUFG(){}

IntPDUFG::~ IntPDUFG(){}

void IntPDUFG::initialize(){
    // Display active policy name.
    cDisplayString& disp = getDisplayString();
    disp.setTagArg("t", 1, "t");
    disp.setTagArg("t", 0, getClassName());

    //Set Forwarding policy
    fwd = check_and_cast<IntPDUForwarding *>
        (getModuleByPath("^.^.relayAndMux.pduForwardingPolicy"));
    onPolicyInit();
}

PDUFGNeighbor * IntPDUFG::getNextNeighbor(const Address &destination, const std::string& qos){

    RMTPorts ports = fwd->lookup(destination, qos);
    if(ports.size() >= 0){
        for(RMTPorts::iterator it = ports.begin(); it != ports.end(); it++){
            RMTPort * p = (*it);
            for(EIter it2 = neiState.begin(); it2 != neiState.end(); ++it2 ){
                PDUFGNeighbor * e = (*it2);
                // Found the port used for the forwarding table; so it's the next neighbor.
                if(p == e->getPort()){
                        return e;
                }
            }
        }
    }

    return NULL;
}

void IntPDUFG::insertFlowInfo(Address addr, QoSCube qos, RMTPort * port) {
    EV << "New flow -> <" << addr << " , " << qos.getQosId() << "> at " << port->getFullPath()<<endl;

    //Insert Flow into neighbour state
    neiState.push_back(new PDUFGNeighbor(addr, qos.getQosId(), port));

    // Inform child policy of changes
    insertedFlow(addr, qos, port);
}

void IntPDUFG::removeFlowInfo(RMTPort * port)
{
    for(EIter it = neiState.begin(); it != neiState.end(); ++it )
    {
        PDUFGNeighbor * e = (*it);
        if(port == e->getPort()) {
            Address addr = e->getDestAddr();

            // Remove flow from neighbour state
            neiState.erase(it);

            // Inform child policy of changes
            removedFlow(addr, port);
            return;
        }
    }
}
