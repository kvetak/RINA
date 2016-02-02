package rina.policies.DIF.Routing.DCRouting;


simple Edge_Routing like iDC_Routing
{
    parameters:
        @class(NSPSimpleDC::Edge_Routing);
        
        bool printAtEnd = default(false);
        
        bool printMyLinks = default(false);
        bool printFullTable = default(false);
        bool printKoList = default(false);
        bool printNotOptimal = default(false);
        
        int pods;
        int torXpod;
        int fabricXpod;
        int spineXfabric;
        int edgeSets;
        
        double starttime = default(10);
        double updateWait = default(0.1);
        double expiration = default(10);
}
