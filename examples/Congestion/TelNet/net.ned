package rina.examples.Congestion.TelNet;

import ned.DatarateChannel;
import rina.src.Other.Infection.T2InfectedRouter;
import rina.src.Other.Infection.IListener;
import rina.src.DAF.AE.AEConstant.AEConstantListener;

network net {
submodules:
N0:T2InfectedRouter { @display("p=50,150"); }
N1:T2InfectedRouter { @display("p=450,80"); }
N2:T2InfectedRouter { @display("p=780,240"); }
N3:T2InfectedRouter { @display("p=250,390"); }
N4:T2InfectedRouter { @display("p=550,670"); }
N5:T2InfectedRouter { @display("p=830,600"); }
N6:T2InfectedRouter { @display("p=1130,100"); }
N7:T2InfectedRouter { @display("p=1300,300"); }
N8:T2InfectedRouter { @display("p=1930,300"); }
N9:T2InfectedRouter { @display("p=1640,450"); }
N10:T2InfectedRouter { @display("p=2080,500"); }
N11:T2InfectedRouter { @display("p=1900,470"); }
N12:T2InfectedRouter { @display("p=2300,500"); }
N13:T2InfectedRouter { @display("p=2450,350"); }
N14:T2InfectedRouter { @display("p=1810,800"); }
N15:T2InfectedRouter { @display("p=1500,800"); }
N16:T2InfectedRouter { @display("p=1510,1070"); }
N17:T2InfectedRouter { @display("p=1310,1000"); }
N18:T2InfectedRouter { @display("p=1300,580"); }
N19:T2InfectedRouter { @display("p=1130,750"); }
N20:T2InfectedRouter { @display("p=1300,650"); }
N21:T2InfectedRouter { @display("p=1090,930"); }
N22:T2InfectedRouter { @display("p=1010,850"); }
N23:T2InfectedRouter { @display("p=910,720"); }
N24:T2InfectedRouter { @display("p=810,810"); }
N25:T2InfectedRouter { @display("p=1530,1300"); }
N26:T2InfectedRouter { @display("p=1050,1170"); }
N27:T2InfectedRouter { @display("p=640,1010"); }
N28:T2InfectedRouter { @display("p=350,1250"); }
N29:T2InfectedRouter { @display("p=730,1480"); }
N30:T2InfectedRouter { @display("p=1010,1600"); }
N31:T2InfectedRouter { @display("p=1320,1450"); }
N32:T2InfectedRouter { @display("p=1110,1860"); }
N33:T2InfectedRouter { @display("p=600,1910"); }
N34:T2InfectedRouter { @display("p=420,1660"); }
listener: IListener;

connections:
N0.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.624ms; } <--> N1.medium++;
N0.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 2.942ms; } <--> N2.medium++;
N0.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.25ms; } <--> N3.medium++;
N1.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.467ms; } <--> N2.medium++;
N1.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 2.721ms; } <--> N6.medium++;
N2.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.454ms; } <--> N5.medium++;
N3.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.641ms; } <--> N4.medium++;
N3.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 2.467ms; } <--> N5.medium++;
N4.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.976ms; } <--> N22.medium++;
N4.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.407ms; } <--> N27.medium++;
N4.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 2.454ms; } <--> N28.medium++;
N5.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 2.332ms; } <--> N6.medium++;
N5.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.882ms; } <--> N18.medium++;
N5.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.342ms; } <--> N19.medium++;
N6.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.05ms; } <--> N7.medium++;
N7.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 2.52ms; } <--> N8.medium++;
N7.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.486ms; } <--> N9.medium++;
N7.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.12ms; } <--> N18.medium++;
N8.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.306ms; } <--> N9.medium++;
N8.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.0ms; } <--> N10.medium++;
N8.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.682ms; } <--> N12.medium++;
N9.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.556ms; } <--> N14.medium++;
N9.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.456ms; } <--> N18.medium++;
N10.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 729.932us; } <--> N11.medium++;
N10.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 880.0us; } <--> N12.medium++;
N10.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.614ms; } <--> N14.medium++;
N12.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 848.528us; } <--> N13.medium++;
N12.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 2.298ms; } <--> N14.medium++;
N14.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.24ms; } <--> N15.medium++;
N14.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.614ms; } <--> N16.medium++;
N15.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.081ms; } <--> N16.medium++;
N15.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.103ms; } <--> N17.medium++;
N15.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.493ms; } <--> N19.medium++;
N16.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 847.585us; } <--> N17.medium++;
N16.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 923.472us; } <--> N25.medium++;
N17.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 923.472us; } <--> N21.medium++;
N17.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.488ms; } <--> N25.medium++;
N17.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.243ms; } <--> N26.medium++;
N18.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 961.665us; } <--> N19.medium++;
N19.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 788.923us; } <--> N20.medium++;
N19.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 737.564us; } <--> N21.medium++;
N19.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 624.82us; } <--> N22.medium++;
N21.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 452.548us; } <--> N22.medium++;
N21.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.828ms; } <--> N27.medium++;
N22.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 656.049us; } <--> N23.medium++;
N22.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 815.843us; } <--> N24.medium++;
N23.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 538.145us; } <--> N24.medium++;
N25.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.032ms; } <--> N31.medium++;
N26.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.76ms; } <--> N27.medium++;
N26.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.727ms; } <--> N30.medium++;
N27.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.506ms; } <--> N28.medium++;
N27.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.914ms; } <--> N29.medium++;
N28.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.777ms; } <--> N29.medium++;
N28.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.664ms; } <--> N34.medium++;
N29.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.219ms; } <--> N30.medium++;
N29.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.797ms; } <--> N33.medium++;
N29.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.434ms; } <--> N34.medium++;
N30.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.378ms; } <--> N31.medium++;
N30.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.114ms; } <--> N32.medium++;
N31.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.843ms; } <--> N32.medium++;
N32.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 2.05ms; } <--> N33.medium++;
N33.medium++ <--> DatarateChannel {  datarate = 100.0Gbps;  delay = 1.232ms; } <--> N34.medium++;

}
