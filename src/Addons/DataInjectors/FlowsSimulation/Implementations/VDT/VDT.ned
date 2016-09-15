package rina.src.Addons.DataInjectors.FlowsSimulation.Implementations.VDT;

import rina.src.Addons.DataInjectors.Infection_t;

simple VDT like Infection_t {
    parameters:
        string infectedIPC;
        
        string nodes = default("");
        
        double ini = default(10); // start sending at
        double fin = default(20); // stop sending at
       	
       	int headers_size = default(40); //B
       
       	string V_QOS = default("A");
       	int V_PDUSize_min	 	= default(100); 	// Headers included
       	int V_PDUSize_max 		= default(400); 	// Headers included
       	double V_AVG_FlowRate  = default(1000.0); 	// (kbps)
       	double V_ON_Duration_AVG = default(1/3);	// s
       	double V_ON_Duration_VAR = default(0.1);	// s
       	double V_OFF_Duration_AVG = default(2/3);	// s
       	double V_OFF_Duration_VAR = default(0.2);	// s
       
       	string D_QOS = default("B");
       	int D_Request_PDUSize	= default(100); 	// Headers included
       	int D_Data_PDUSize 		= default(1500); 	// Headers included
       	double D_AVG_FlowRate  = default(1000.0); 	// (kbps)
       	double D_ON_FlowRate = default(1500.0);	// s
       	double D_OFF_Duration_AVG = default(1.0);	// s
       	double D_OFF_Duration_VAR = default(0.2);	// s
       	
       	string T_QOS = default("C");
       	int T_Request_PDUSize	= default(100); 	// Headers included
       	int T_Data_PDUSize 		= default(1500); 	// Headers included
       	double T_AVG_FlowRate  = default(1000.0); 	// (kbps)
       	int T_WINDOW_MAX = default(1000);	// PDUs
       	int T_WINDOW_UPDATE = default(100);	// PDUs
       	
       	double aktT = default(0.1);
       	
       	xml data = default(xml("<data/>"));
        
    gates:
        inout g;
}
