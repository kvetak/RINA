package rina.policies.DIF.Routing.DCRouting;

import rina.src.DIF.Routing.IntRouting;

moduleinterface iDC_Routing extends IntRouting
{
    parameters:
        @display("i=block/socket");
        
		//Mandatory signal to implement
        @signal[Routing-Update](type=IntRoutingUpdate?); 
        
        bool printAtEnd;
        bool printMyLinks;
        bool printFullTable;
        bool printKoList;
        bool printNotOptimal;
        
        int pods;
        int torXpod;
        int fabricXpod;
        int spineXfabric;
        int edgeSets;
        
        double starttime;
        double updateWait;
        double expiration;
}
