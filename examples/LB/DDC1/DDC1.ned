package rina.examples.LB.DDC1;
import rina.src.CS.Host1AP;
import rina.src.CS.Server1AP;
import rina.src.CS.HostNAP;
import rina.src.CS.HostNAPNAE;
import rina.src.DAF.AE.AEData.AEData;
import rina.src.Other.FlowsListener.FlowListener;
import rina.src.Other.Infection.InfectedDCRouter;
import rina.src.Other.Infection.InfectedISP;
network DDC1
{
    @display("bgb=3109,642");
    submodules:

        T_0_0: InfectedDCRouter {
            @display("p=30,470");
        }

        T_0_1: InfectedDCRouter {
            @display("p=110,470");
        }

        T_0_2: InfectedDCRouter {
            @display("p=195,470");
        }

        T_0_3: InfectedDCRouter {
            @display("p=275,470");
        }

        T_1_0: InfectedDCRouter {
            @display("p=420,470");
        }

        T_1_1: InfectedDCRouter {
            @display("p=502,470");
        }

        T_1_2: InfectedDCRouter {
            @display("p=581,470");
        }

        T_1_3: InfectedDCRouter {
            @display("p=649,470");
        }

        T_2_0: InfectedDCRouter {
            @display("p=795,470");
        }

        T_2_1: InfectedDCRouter {
            @display("p=853,470");
        }

        T_2_2: InfectedDCRouter {
            @display("p=912,470");
        }

        T_2_3: InfectedDCRouter {
            @display("p=971,470");
        }

        A_0_0: InfectedDCRouter {
            @display("p=71,370");
        }

        A_0_1: InfectedDCRouter {
            @display("p=149,370");
        }

        A_0_2: InfectedDCRouter {
            @display("p=234,370");
        }

        A_1_0: InfectedDCRouter {
            @display("p=459,384");
        }

        A_1_1: InfectedDCRouter {
            @display("p=536,384");
        }

        A_1_2: InfectedDCRouter {
            @display("p=610,384");
        }

        A_2_0: InfectedDCRouter {
            @display("p=801,384");
        }

        A_2_1: InfectedDCRouter {
            @display("p=873,384");
        }

        A_2_2: InfectedDCRouter {
            @display("p=939,384");
        }

        Sp_0_0: InfectedDCRouter {
            @display("p=100,170");
        }

        Sp_0_1: InfectedDCRouter {
            @display("p=160,170");
        }

        Sp_1_0: InfectedDCRouter {
            @display("p=470,170");
        }

        Sp_1_1: InfectedDCRouter {
            @display("p=530,170");
        }

        Sp_2_0: InfectedDCRouter {
            @display("p=840,170");
        }

        Sp_2_1: InfectedDCRouter {
            @display("p=900,170");
        }

        flowListener: FlowListener {
            @display("p=234,54");
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
            @display("p=251,570");
        }

        S_0_3_1: Server1AP {
            @display("p=280,570");
        }

        S_1_0_0: Server1AP {
            @display("p=379,570");
        }

        S_1_0_1: Server1AP {
            @display("p=415,570");
        }

        S_1_1_0: Server1AP {
            @display("p=459,570");
        }

        S_1_1_1: Server1AP {
            @display("p=493,570");
        }

        S_1_2_0: Server1AP {
            @display("p=530,570");
        }

        S_1_2_1: Server1AP {
            @display("p=570,570");
        }

        S_1_3_0: Server1AP {
            @display("p=610,570");
        }

        S_1_3_1: Server1AP {
            @display("p=649,570");
        }

        S_2_0_0: Server1AP {
            @display("p=712,570");
        }

        S_2_0_1: Server1AP {
            @display("p=751,570");
        }

        S_2_1_0: Server1AP {
            @display("p=790,570");
        }

        S_2_1_1: Server1AP {
            @display("p=829,570");
        }

        S_2_2_0: Server1AP {
            @display("p=873,570");
        }

        S_2_2_1: Server1AP {
            @display("p=917,570");
        }

        S_2_3_0: Server1AP {
            @display("p=966,570");
        }

        S_2_3_1: Server1AP {
            @display("p=1005,570");
        }
        I_0: InfectedISP {
            @display("p=122,73");
        }
        I_1: InfectedISP {
            @display("p=502,57");
        }
        I_2: InfectedISP {
            @display("p=873,65");
        }
    connections:
        T_0_0.medium++ <--> A_0_0.medium++;
        T_0_1.medium++ <--> A_0_0.medium++;
        T_0_2.medium++ <--> A_0_0.medium++;
        T_0_3.medium++ <--> A_0_0.medium++;
        T_0_0.medium++ <--> A_0_1.medium++;
        T_0_1.medium++ <--> A_0_1.medium++;
        T_0_2.medium++ <--> A_0_1.medium++;
        T_0_3.medium++ <--> A_0_1.medium++;
        T_0_0.medium++ <--> A_0_2.medium++;
        T_0_1.medium++ <--> A_0_2.medium++;
        T_0_2.medium++ <--> A_0_2.medium++;
        T_0_3.medium++ <--> A_0_2.medium++;
        T_1_0.medium++ <--> A_1_0.medium++;
        T_1_1.medium++ <--> A_1_0.medium++;
        T_1_2.medium++ <--> A_1_0.medium++;
        T_1_3.medium++ <--> A_1_0.medium++;
        T_1_0.medium++ <--> A_1_1.medium++;
        T_1_1.medium++ <--> A_1_1.medium++;
        T_1_2.medium++ <--> A_1_1.medium++;
        T_1_3.medium++ <--> A_1_1.medium++;
        T_1_0.medium++ <--> A_1_2.medium++;
        T_1_1.medium++ <--> A_1_2.medium++;
        T_1_2.medium++ <--> A_1_2.medium++;
        T_1_3.medium++ <--> A_1_2.medium++;
        T_2_0.medium++ <--> A_2_0.medium++;
        T_2_1.medium++ <--> A_2_0.medium++;
        T_2_2.medium++ <--> A_2_0.medium++;
        T_2_3.medium++ <--> A_2_0.medium++;
        T_2_0.medium++ <--> A_2_1.medium++;
        T_2_1.medium++ <--> A_2_1.medium++;
        T_2_2.medium++ <--> A_2_1.medium++;
        T_2_3.medium++ <--> A_2_1.medium++;
        T_2_0.medium++ <--> A_2_2.medium++;
        T_2_1.medium++ <--> A_2_2.medium++;
        T_2_2.medium++ <--> A_2_2.medium++;
        T_2_3.medium++ <--> A_2_2.medium++;
        A_0_0.medium++ <--> Sp_0_0.medium++;
        A_0_0.medium++ <--> Sp_0_1.medium++;
        A_1_0.medium++ <--> Sp_0_0.medium++;
        A_1_0.medium++ <--> Sp_0_1.medium++;
        A_2_0.medium++ <--> Sp_0_0.medium++;
        A_2_0.medium++ <--> Sp_0_1.medium++;
        A_0_1.medium++ <--> Sp_1_0.medium++;
        A_0_1.medium++ <--> Sp_1_1.medium++;
        A_1_1.medium++ <--> Sp_1_0.medium++;
        A_1_1.medium++ <--> Sp_1_1.medium++;
        A_2_1.medium++ <--> Sp_1_0.medium++;
        A_2_1.medium++ <--> Sp_1_1.medium++;
        A_0_2.medium++ <--> Sp_2_0.medium++;
        A_0_2.medium++ <--> Sp_2_1.medium++;
        A_1_2.medium++ <--> Sp_2_0.medium++;
        A_1_2.medium++ <--> Sp_2_1.medium++;
        A_2_2.medium++ <--> Sp_2_0.medium++;
        A_2_2.medium++ <--> Sp_2_1.medium++;
        S_0_0_0.medium <--> T_0_0.medium++;
        S_0_0_1.medium <--> T_0_0.medium++;
        S_0_1_0.medium <--> T_0_1.medium++;
        S_0_1_1.medium <--> T_0_1.medium++;
        S_0_2_0.medium <--> T_0_2.medium++;
        S_0_2_1.medium <--> T_0_2.medium++;
        S_0_3_0.medium <--> T_0_3.medium++;
        S_0_3_1.medium <--> T_0_3.medium++;
        S_1_0_0.medium <--> T_1_0.medium++;
        S_1_0_1.medium <--> T_1_0.medium++;
        S_1_1_0.medium <--> T_1_1.medium++;
        S_1_1_1.medium <--> T_1_1.medium++;
        S_1_2_0.medium <--> T_1_2.medium++;
        S_1_2_1.medium <--> T_1_2.medium++;
        S_1_3_0.medium <--> T_1_3.medium++;
        S_1_3_1.medium <--> T_1_3.medium++;
        S_2_0_0.medium <--> T_2_0.medium++;
        S_2_0_1.medium <--> T_2_0.medium++;
        S_2_1_0.medium <--> T_2_1.medium++;
        S_2_1_1.medium <--> T_2_1.medium++;
        S_2_2_0.medium <--> T_2_2.medium++;
        S_2_2_1.medium <--> T_2_2.medium++;
        S_2_3_0.medium <--> T_2_3.medium++;
        S_2_3_1.medium <--> T_2_3.medium++;
        Sp_0_0.medium++ <--> I_0.medium++;
        Sp_0_1.medium++ <--> I_0.medium++;
        Sp_1_0.medium++ <--> I_1.medium++;
        Sp_1_1.medium++ <--> I_1.medium++;
        Sp_2_0.medium++ <--> I_2.medium++;
        Sp_2_1.medium++ <--> I_2.medium++;
}
