package rina.DIF.FA;

import rina.DIF.NSM.NameSpaceManager;


module FlowAllocator
{
    parameters:
        @display("i=block/fork;bgb=590,410");
                
    gates:
    
    submodules:
        fa: FA {
            @display("p=114,84");
        }

        nameSpaceManager: NameSpaceManager {
            @display("p=447,84");
        }
        
        faiTable: FAITable {
            @display("p=283,84");
        }
        
    connections:
  
        
}