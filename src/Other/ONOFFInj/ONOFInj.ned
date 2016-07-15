package rina.src.Other.ONOFFInj;

simple ONOFInj {
    parameters:
        string infectedIPC;
        
        string nodes = default("");
        
        double ini = default(10); // start sending at
        double fin= default(20); // stop sending at
       	
       	int header_size = default(80); //B
       
       	string voice_qos = default("A");
       	int voice_flows = default(0);
       	int voice_min_pdu_len = default(100);
       	int voice_max_pdu_len = default(300);
       	double voice_interval = default(0.01);
       	double voice_idle_time = default(9.0);
       	double voice_burst_time = default(3.0);
       	
       	string client_qos = default("B");
       	int client_flows = default(0);
       	int client_pdu_len = default(20);
       	int client_min_data = default(2000);
       	int client_max_data = default(2000);
       	double client_min_rate = default(500);
       	double client_max_rate = default(1000);
       	double client_idle_time = default(5.0);
       	
       	double dropProb = default(1.1);
       	double aktT = default(0.1);
        
    gates:
        inout g;
}
