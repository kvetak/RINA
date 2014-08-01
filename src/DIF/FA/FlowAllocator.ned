package rina.DIF.FA;

import rina.DIF.NSM.NameSpaceManager;


module FlowAllocator
{
    parameters:
        @display("i=block/fork;bgb=590,410");
        int numOfAPs;
                
    gates:
        inout appIo[numOfAPs];
//        inout efcpIo[] @loose;
    
    submodules:
        fa: FA {
            @display("p=114,84");
            numOfAPs = numOfAPs;
        }

        nameSpaceManager: NameSpaceManager {
            @display("p=447,84");
        }
        
        faiTable: FAITable {
            @display("p=283,84");
        }
        
    connections:
        for i = 0 .. numOfAPs - 1 {
            appIo[i] <--> fa.appIo[i];        
        }   
        
}