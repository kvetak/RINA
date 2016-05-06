package rina.examples.LB.DDC1;
import ned.DatarateChannel;
import rina.src.CS.Host1AP;
import rina.src.CS.Server1AP;
import rina.src.CS.HostNAP;
import rina.src.CS.HostNAPNAE;
import rina.src.DAF.AE.AEData.AEData;
import rina.src.Other.FlowsListener.FlowListener;
import rina.src.Other.Infection.InfectedDCRouter;
import rina.src.Other.Infection.InfectedISP;
import rina.src.Other.myListener.myListener;

network DDC1
{
    @display("bgb=3109,642");
    types:
    submodules:

        T_0_0: InfectedDCRouter {
            @display("p=49,470");
        }

        T_0_1: InfectedDCRouter {
            @display("p=110,470");
        }

        T_0_2: InfectedDCRouter {
            @display("p=170,470");
        }

        T_0_3: InfectedDCRouter {
            @display("p=240,470");
        }

        T_1_0: InfectedDCRouter {
            @display("p=330,470");
        }

        T_1_1: InfectedDCRouter {
            @display("p=400,470");
        }

        T_1_2: InfectedDCRouter {
            @display("p=459,470");
        }

        T_1_3: InfectedDCRouter {
            @display("p=524,470");
        }

        T_2_0: InfectedDCRouter {
            @display("p=620,470");
        }

        T_2_1: InfectedDCRouter {
            @display("p=684,470");
        }

        T_2_2: InfectedDCRouter {
            @display("p=754,470");
        }

        T_2_3: InfectedDCRouter {
            @display("p=820,470");
        }

        T_3_0: InfectedDCRouter {
            @display("p=946,470");
        }

        T_3_1: InfectedDCRouter {
            @display("p=1011,470");
        }

        T_3_2: InfectedDCRouter {
            @display("p=1075,470");
        }

        T_3_3: InfectedDCRouter {
            @display("p=1140,470");
        }

        A_0_0: InfectedDCRouter {
            @display("p=90,370");
        }

        A_0_1: InfectedDCRouter {
            @display("p=150,370");
        }

        A_0_2: InfectedDCRouter {
            @display("p=210,370");
        }

        A_1_0: InfectedDCRouter {
            @display("p=350,370");
        }

        A_1_1: InfectedDCRouter {
            @display("p=410,370");
        }

        A_1_2: InfectedDCRouter {
            @display("p=485,370");
        }

        A_2_0: InfectedDCRouter {
            @display("p=635,370");
        }

        A_2_1: InfectedDCRouter {
            @display("p=715,370");
        }

        A_2_2: InfectedDCRouter {
            @display("p=781,370");
        }

        A_3_0: InfectedDCRouter {
            @display("p=916,370");
        }

        A_3_1: InfectedDCRouter {
            @display("p=985,370");
        }

        A_3_2: InfectedDCRouter {
            @display("p=1064,370");
        }

        Sp_0_0: InfectedDCRouter {
            @display("p=180,270");
        }

        Sp_0_1: InfectedDCRouter {
            @display("p=261,270");
        }

        Sp_1_0: InfectedDCRouter {
            @display("p=506,262");
        }

        Sp_1_1: InfectedDCRouter {
            @display("p=604,262");
        }

        Sp_2_0: InfectedDCRouter {
            @display("p=870,270");
        }

        Sp_2_1: InfectedDCRouter {
            @display("p=946,270");
        }

        I_0: InfectedISP {
            @display("p=227,170");
        }

        I_1: InfectedISP {
            @display("p=530,170");
        }

        I_2: InfectedISP {
            @display("p=904,170");
        }

        flowListener: FlowListener {
            @display("p=1029,170");
        }

        S_0_0_0: Server1AP {
            @display("p=30,570");
        }

        S_0_0_1: Server1AP {
            @display("p=60,570");
        }

        S_0_1_0: Server1AP {
            @display("p=100,570");
        }

        S_0_1_1: Server1AP {
            @display("p=130,570");
        }

        S_0_2_0: Server1AP {
            @display("p=170,570");
        }

        S_0_2_1: Server1AP {
            @display("p=200,570");
        }

        S_0_3_0: Server1AP {
            @display("p=240,570");
        }

        S_0_3_1: Server1AP {
            @display("p=270,570");
        }

        S_1_0_0: Server1AP {
            @display("p=330,570");
        }

        S_1_0_1: Server1AP {
            @display("p=360,570");
        }

        S_1_1_0: Server1AP {
            @display("p=400,570");
        }

        S_1_1_1: Server1AP {
            @display("p=430,570");
        }

        S_1_2_0: Server1AP {
            @display("p=470,570");
        }

        S_1_2_1: Server1AP {
            @display("p=500,570");
        }

        S_1_3_0: Server1AP {
            @display("p=540,570");
        }

        S_1_3_1: Server1AP {
            @display("p=570,570");
        }

        S_2_0_0: Server1AP {
            @display("p=630,570");
        }

        S_2_0_1: Server1AP {
            @display("p=660,570");
        }

        S_2_1_0: Server1AP {
            @display("p=700,570");
        }

        S_2_1_1: Server1AP {
            @display("p=730,570");
        }

        S_2_2_0: Server1AP {
            @display("p=770,570");
        }

        S_2_2_1: Server1AP {
            @display("p=800,570");
        }

        S_2_3_0: Server1AP {
            @display("p=840,570");
        }

        S_2_3_1: Server1AP {
            @display("p=870,570");
        }

        S_3_0_0: Server1AP {
            @display("p=930,570");
        }

        S_3_0_1: Server1AP {
            @display("p=960,570");
        }

        S_3_1_0: Server1AP {
            @display("p=1000,570");
        }

        S_3_1_1: Server1AP {
            @display("p=1030,570");
        }

        S_3_2_0: Server1AP {
            @display("p=1070,570");
        }

        S_3_2_1: Server1AP {
            @display("p=1100,570");
        }

        S_3_3_0: Server1AP {
            @display("p=1140,570");
        }

        S_3_3_1: Server1AP {
            @display("p=1170,570");
        }

        C_0_0: Host1AP {
            @display("p=30,70");
        }

        C_0_1: Host1AP {
            @display("p=60,70");
        }

        C_0_2: Host1AP {
            @display("p=90,70");
        }

        C_0_3: Host1AP {
            @display("p=120,70");
        }

        C_0_4: Host1AP {
            @display("p=150,70");
        }

        C_0_5: Host1AP {
            @display("p=180,70");
        }

        C_0_6: Host1AP {
            @display("p=210,70");
        }

        C_0_7: Host1AP {
            @display("p=240,70");
        }

        C_0_8: Host1AP {
            @display("p=270,70");
        }

        C_0_9: Host1AP {
            @display("p=300,70");
        }

        C_1_0: Host1AP {
            @display("p=350,70");
        }

        C_1_1: Host1AP {
            @display("p=380,70");
        }

        C_1_2: Host1AP {
            @display("p=410,70");
        }

        C_1_3: Host1AP {
            @display("p=440,70");
        }

        C_1_4: Host1AP {
            @display("p=470,70");
        }

        C_1_5: Host1AP {
            @display("p=500,70");
        }

        C_1_6: Host1AP {
            @display("p=530,70");
        }

        C_1_7: Host1AP {
            @display("p=560,70");
        }

        C_1_8: Host1AP {
            @display("p=590,70");
        }

        C_1_9: Host1AP {
            @display("p=620,70");
        }

        C_2_0: Host1AP {
            @display("p=670,70");
        }

        C_2_1: Host1AP {
            @display("p=700,70");
        }

        C_2_2: Host1AP {
            @display("p=739,70");
        }

        C_2_3: Host1AP {
            @display("p=770,70");
        }

        C_2_4: Host1AP {
            @display("p=809,70");
        }

        C_2_5: Host1AP {
            @display("p=850,70");
        }

        C_2_6: Host1AP {
            @display("p=883,70");
        }

        C_2_7: Host1AP {
            @display("p=916,70");
        }

        C_2_8: Host1AP {
            @display("p=952,70");
        }

        C_2_9: Host1AP {
            @display("p=991,70");
        }

        mListener: myListener {
            @display("p=1030,237");
        }
    connections:
        T_0_0.medium++ <--> TA_Link <--> A_0_0.medium++;
        T_0_1.medium++ <--> TA_Link <--> A_0_0.medium++;
        T_0_2.medium++ <--> TA_Link <--> A_0_0.medium++;
        T_0_3.medium++ <--> TA_Link <--> A_0_0.medium++;
        T_0_0.medium++ <--> TA_Link <--> A_0_1.medium++;
        T_0_1.medium++ <--> TA_Link <--> A_0_1.medium++;
        T_0_2.medium++ <--> TA_Link <--> A_0_1.medium++;
        T_0_3.medium++ <--> TA_Link <--> A_0_1.medium++;
        T_0_0.medium++ <--> TA_Link <--> A_0_2.medium++;
        T_0_1.medium++ <--> TA_Link <--> A_0_2.medium++;
        T_0_2.medium++ <--> TA_Link <--> A_0_2.medium++;
        T_0_3.medium++ <--> TA_Link <--> A_0_2.medium++;
        T_1_0.medium++ <--> TA_Link <--> A_1_0.medium++;
        T_1_1.medium++ <--> TA_Link <--> A_1_0.medium++;
        T_1_2.medium++ <--> TA_Link <--> A_1_0.medium++;
        T_1_3.medium++ <--> TA_Link <--> A_1_0.medium++;
        T_1_0.medium++ <--> TA_Link <--> A_1_1.medium++;
        T_1_1.medium++ <--> TA_Link <--> A_1_1.medium++;
        T_1_2.medium++ <--> TA_Link <--> A_1_1.medium++;
        T_1_3.medium++ <--> TA_Link <--> A_1_1.medium++;
        T_1_0.medium++ <--> TA_Link <--> A_1_2.medium++;
        T_1_1.medium++ <--> TA_Link <--> A_1_2.medium++;
        T_1_2.medium++ <--> TA_Link <--> A_1_2.medium++;
        T_1_3.medium++ <--> TA_Link <--> A_1_2.medium++;
        T_2_0.medium++ <--> TA_Link <--> A_2_0.medium++;
        T_2_1.medium++ <--> TA_Link <--> A_2_0.medium++;
        T_2_2.medium++ <--> TA_Link <--> A_2_0.medium++;
        T_2_3.medium++ <--> TA_Link <--> A_2_0.medium++;
        T_2_0.medium++ <--> TA_Link <--> A_2_1.medium++;
        T_2_1.medium++ <--> TA_Link <--> A_2_1.medium++;
        T_2_2.medium++ <--> TA_Link <--> A_2_1.medium++;
        T_2_3.medium++ <--> TA_Link <--> A_2_1.medium++;
        T_2_0.medium++ <--> TA_Link <--> A_2_2.medium++;
        T_2_1.medium++ <--> TA_Link <--> A_2_2.medium++;
        T_2_2.medium++ <--> TA_Link <--> A_2_2.medium++;
        T_2_3.medium++ <--> TA_Link <--> A_2_2.medium++;
        T_3_0.medium++ <--> TA_Link <--> A_3_0.medium++;
        T_3_1.medium++ <--> TA_Link <--> A_3_0.medium++;
        T_3_2.medium++ <--> TA_Link <--> A_3_0.medium++;
        T_3_3.medium++ <--> TA_Link <--> A_3_0.medium++;
        T_3_0.medium++ <--> TA_Link <--> A_3_1.medium++;
        T_3_1.medium++ <--> TA_Link <--> A_3_1.medium++;
        T_3_2.medium++ <--> TA_Link <--> A_3_1.medium++;
        T_3_3.medium++ <--> TA_Link <--> A_3_1.medium++;
        T_3_0.medium++ <--> TA_Link <--> A_3_2.medium++;
        T_3_1.medium++ <--> TA_Link <--> A_3_2.medium++;
        T_3_2.medium++ <--> TA_Link <--> A_3_2.medium++;
        T_3_3.medium++ <--> TA_Link <--> A_3_2.medium++;
        A_0_0.medium++ <--> ASp_Link <--> Sp_0_0.medium++;
        A_0_0.medium++ <--> ASp_Link <--> Sp_0_1.medium++;
        A_1_0.medium++ <--> ASp_Link <--> Sp_0_0.medium++;
        A_1_0.medium++ <--> ASp_Link <--> Sp_0_1.medium++;
        A_2_0.medium++ <--> ASp_LinkFar { @display("ls=red"); } <--> Sp_0_0.medium++;
        A_2_0.medium++ <--> ASp_LinkFar { @display("ls=red"); } <--> Sp_0_1.medium++;
        A_3_0.medium++ <--> ASp_LinkFar { @display("ls=red"); } <--> Sp_0_0.medium++;
        A_3_0.medium++ <--> ASp_LinkFar { @display("ls=red"); } <--> Sp_0_1.medium++;
        A_0_1.medium++ <--> ASp_LinkFar { @display("ls=red"); } <--> Sp_1_0.medium++;
        A_0_1.medium++ <--> ASp_LinkFar { @display("ls=red"); } <--> Sp_1_1.medium++;
        A_1_1.medium++ <--> ASp_LinkFar { @display("ls=red"); } <--> Sp_1_0.medium++;
        A_1_1.medium++ <--> ASp_LinkFar { @display("ls=red"); } <--> Sp_1_1.medium++;
        A_2_1.medium++ <--> ASp_LinkFar { @display("ls=red"); } <--> Sp_1_0.medium++;
        A_2_1.medium++ <--> ASp_LinkFar { @display("ls=red"); } <--> Sp_1_1.medium++;
        A_3_1.medium++ <--> ASp_LinkFar { @display("ls=red"); } <--> Sp_1_0.medium++;
        A_3_1.medium++ <--> ASp_LinkFar { @display("ls=red"); } <--> Sp_1_1.medium++;
        A_0_2.medium++ <--> ASp_LinkFar { @display("ls=red"); } <--> Sp_2_0.medium++;
        A_0_2.medium++ <--> ASp_LinkFar { @display("ls=red"); } <--> Sp_2_1.medium++;
        A_1_2.medium++ <--> ASp_LinkFar { @display("ls=red"); } <--> Sp_2_0.medium++;
        A_1_2.medium++ <--> ASp_LinkFar { @display("ls=red"); } <--> Sp_2_1.medium++;
        A_2_2.medium++ <--> ASp_Link <--> Sp_2_0.medium++;
        A_2_2.medium++ <--> ASp_Link <--> Sp_2_1.medium++;
        A_3_2.medium++ <--> ASp_Link <--> Sp_2_0.medium++;
        A_3_2.medium++ <--> ASp_Link <--> Sp_2_1.medium++;
        I_0.medium++ <--> SpI_Link <--> Sp_0_0.medium++;
        I_0.medium++ <--> SpI_Link <--> Sp_0_1.medium++;
        I_1.medium++ <--> SpI_Link <--> Sp_1_0.medium++;
        I_1.medium++ <--> SpI_Link <--> Sp_1_1.medium++;
        I_2.medium++ <--> SpI_Link <--> Sp_2_0.medium++;
        I_2.medium++ <--> SpI_Link <--> Sp_2_1.medium++;
        I_0.medium++ <--> IC_Link <--> C_0_0.medium;
        I_0.medium++ <--> IC_Link1 <--> C_0_1.medium;
        I_0.medium++ <--> IC_Link2 <--> C_0_2.medium;
        I_0.medium++ <--> IC_Link3 <--> C_0_3.medium;
        I_0.medium++ <--> IC_Link4 <--> C_0_4.medium;
        I_0.medium++ <--> IC_Link5 <--> C_0_5.medium;
        I_0.medium++ <--> IC_Link6 <--> C_0_6.medium;
        I_0.medium++ <--> IC_Link7 <--> C_0_7.medium;
        I_0.medium++ <--> IC_Link8 <--> C_0_8.medium;
        I_0.medium++ <--> IC_Link9 <--> C_0_9.medium;
        I_1.medium++ <--> IC_Link <--> C_1_0.medium;
        I_1.medium++ <--> IC_Link1 <--> C_1_1.medium;
        I_1.medium++ <--> IC_Link2 <--> C_1_2.medium;
        I_1.medium++ <--> IC_Link3 <--> C_1_3.medium;
        I_1.medium++ <--> IC_Link4 <--> C_1_4.medium;
        I_1.medium++ <--> IC_Link5 <--> C_1_5.medium;
        I_1.medium++ <--> IC_Link6 <--> C_1_6.medium;
        I_1.medium++ <--> IC_Link7 <--> C_1_7.medium;
        I_1.medium++ <--> IC_Link8 <--> C_1_8.medium;
        I_1.medium++ <--> IC_Link9 <--> C_1_9.medium;
        I_2.medium++ <--> IC_Link <--> C_2_0.medium;
        I_2.medium++ <--> IC_Link1 <--> C_2_1.medium;
        I_2.medium++ <--> IC_Link2 <--> C_2_2.medium;
        I_2.medium++ <--> IC_Link3 <--> C_2_3.medium;
        I_2.medium++ <--> IC_Link4 <--> C_2_4.medium;
        I_2.medium++ <--> IC_Link5 <--> C_2_5.medium;
        I_2.medium++ <--> IC_Link6 <--> C_2_6.medium;
        I_2.medium++ <--> IC_Link7 <--> C_2_7.medium;
        I_2.medium++ <--> IC_Link8 <--> C_2_8.medium;
        I_2.medium++ <--> IC_Link9 <--> C_2_9.medium;
        S_0_0_0.medium <--> ST_Link <--> T_0_0.medium++;
        S_0_0_1.medium <--> ST_Link <--> T_0_0.medium++;
        S_0_1_0.medium <--> ST_Link <--> T_0_1.medium++;
        S_0_1_1.medium <--> ST_Link <--> T_0_1.medium++;
        S_0_2_0.medium <--> ST_Link <--> T_0_2.medium++;
        S_0_2_1.medium <--> ST_Link <--> T_0_2.medium++;
        S_0_3_0.medium <--> ST_Link <--> T_0_3.medium++;
        S_0_3_1.medium <--> ST_Link <--> T_0_3.medium++;
        S_1_0_0.medium <--> ST_Link <--> T_1_0.medium++;
        S_1_0_1.medium <--> ST_Link <--> T_1_0.medium++;
        S_1_1_0.medium <--> ST_Link <--> T_1_1.medium++;
        S_1_1_1.medium <--> ST_Link <--> T_1_1.medium++;
        S_1_2_0.medium <--> ST_Link <--> T_1_2.medium++;
        S_1_2_1.medium <--> ST_Link <--> T_1_2.medium++;
        S_1_3_0.medium <--> ST_Link <--> T_1_3.medium++;
        S_1_3_1.medium <--> ST_Link <--> T_1_3.medium++;
        S_2_0_0.medium <--> ST_Link <--> T_2_0.medium++;
        S_2_0_1.medium <--> ST_Link <--> T_2_0.medium++;
        S_2_1_0.medium <--> ST_Link <--> T_2_1.medium++;
        S_2_1_1.medium <--> ST_Link <--> T_2_1.medium++;
        S_2_2_0.medium <--> ST_Link <--> T_2_2.medium++;
        S_2_2_1.medium <--> ST_Link <--> T_2_2.medium++;
        S_2_3_0.medium <--> ST_Link <--> T_2_3.medium++;
        S_2_3_1.medium <--> ST_Link <--> T_2_3.medium++;
        S_3_0_0.medium <--> ST_Link <--> T_3_0.medium++;
        S_3_0_1.medium <--> ST_Link <--> T_3_0.medium++;
        S_3_1_0.medium <--> ST_Link <--> T_3_1.medium++;
        S_3_1_1.medium <--> ST_Link <--> T_3_1.medium++;
        S_3_2_0.medium <--> ST_Link <--> T_3_2.medium++;
        S_3_2_1.medium <--> ST_Link <--> T_3_2.medium++;
        S_3_3_0.medium <--> ST_Link <--> T_3_3.medium++;
        S_3_3_1.medium <--> ST_Link <--> T_3_3.medium++;
}
channel ST_Link extends DatarateChannel
{
    parameters:
        datarate = 10Gbps;
        delay = 100us;
        per = 0.1; //10^-12
        ber = 0.1; //10^-12
}
channel TA_Link extends DatarateChannel
{
    parameters:
        datarate = 10Gbps;
        delay = 1ms;
        per = 0.000000000001; //10^-12
        ber = 0.000000000001; //10^-12
}
channel ASp_Link extends DatarateChannel
{
    parameters:
        datarate = 10Gbps;
        delay = 3ms;
        per = 0.000000000001; //10^-12
        ber = 0.000000000001; //10^-12
}

channel ASp_LinkFar extends DatarateChannel
{
    parameters:
        datarate = 10Gbps;
        delay = 3ms;
        per = 0.000000000001; //10^-12
        ber = 0.000000000001; //10^-12
        //datarate = 100Mbps;
        //delay = 100ms;
        //per = 0.000000001; //10^-12
        //ber = 0.000000001; //10^-12
}

channel SpI_Link extends DatarateChannel
{
    parameters:
        datarate = 1Gbps;
        delay = 6ms;
        per = 0.000000001; //10^-9
        ber = 0.000000001; //10^-9
}
channel IC_Link extends DatarateChannel
{
    parameters:
        datarate = 1Gbps;
        delay = 10ms;
        per = 0.000001; //10^-6
        ber = 0.000001; //10^-6
}
channel IC_Link1 extends DatarateChannel
{
    parameters:
        datarate = 100Mbps;
        delay = 100ms;
        per = 0.000001; //10^-6
        ber = 0.000001; //10^-6
}
channel IC_Link2 extends DatarateChannel
{
    parameters:
        datarate = 10Mbps;
        delay = 100ms;
        per = 0.000001; //10^-6
        ber = 0.000001; //10^-6
}
channel IC_Link3 extends DatarateChannel
{
    parameters:
        datarate = 50Mbps;
        delay = 50ms;
        per = 0.000001; //10^-6
        ber = 0.000001; //10^-6
}
channel IC_Link4 extends DatarateChannel
{
    parameters:
        datarate = 80Mbps;
        delay = 80ms;
        per = 0.000001; //10^-6
        ber = 0.000001; //10^-6
}
channel IC_Link5 extends DatarateChannel
{
    parameters:
        datarate = 5Mbps;
        delay = 100ms;
        per = 0.000001; //10^-6
        ber = 0.000001; //10^-6
}
channel IC_Link6 extends DatarateChannel
{
    parameters:
        datarate = 2Mbps;
        delay = 200ms;
        per = 0.000001; //10^-6
        ber = 0.000001; //10^-6
}
channel IC_Link7 extends DatarateChannel
{
    parameters:
        datarate = 10Mbps;
        delay = 100ms;
        per = 0.000001; //10^-6
        ber = 0.000001; //10^-6
}
channel IC_Link8 extends DatarateChannel
{
    parameters:
        datarate = 20Mbps;
        delay = 20ms;
        per = 0.000001; //10^-6
        ber = 0.000001; //10^-6
}
channel IC_Link9 extends DatarateChannel
{
    parameters:
        datarate = 30Mbps;
        delay = 30ms;
        per = 0.000001; //10^-6
        ber = 0.000001; //10^-6
}