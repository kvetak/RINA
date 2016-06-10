package rina.examples.Routing.Barabasi_Albert;

import rina.src.Other.NetTest.NetTestRouter;
import rina.src.Other.NetTest.NetTestListener;

network net {
submodules:
N0:NetTestRouter { @display("p=50,50"); }
N1:NetTestRouter { @display("p=100,50"); }
N2:NetTestRouter { @display("p=150,50"); }
N3:NetTestRouter { @display("p=200,50"); }
N4:NetTestRouter { @display("p=250,50"); }
N5:NetTestRouter { @display("p=300,50"); }
N6:NetTestRouter { @display("p=350,50"); }
N7:NetTestRouter { @display("p=400,50"); }
N8:NetTestRouter { @display("p=450,50"); }
N9:NetTestRouter { @display("p=500,50"); }
N10:NetTestRouter { @display("p=550,50"); }
N11:NetTestRouter { @display("p=600,50"); }
N12:NetTestRouter { @display("p=50,100"); }
N13:NetTestRouter { @display("p=100,100"); }
N14:NetTestRouter { @display("p=150,100"); }
N15:NetTestRouter { @display("p=200,100"); }
N16:NetTestRouter { @display("p=250,100"); }
N17:NetTestRouter { @display("p=300,100"); }
N18:NetTestRouter { @display("p=350,100"); }
N19:NetTestRouter { @display("p=400,100"); }
N20:NetTestRouter { @display("p=450,100"); }
N21:NetTestRouter { @display("p=500,100"); }
N22:NetTestRouter { @display("p=550,100"); }
N23:NetTestRouter { @display("p=600,100"); }
N24:NetTestRouter { @display("p=50,150"); }
N25:NetTestRouter { @display("p=100,150"); }
N26:NetTestRouter { @display("p=150,150"); }
N27:NetTestRouter { @display("p=200,150"); }
N28:NetTestRouter { @display("p=250,150"); }
N29:NetTestRouter { @display("p=300,150"); }
N30:NetTestRouter { @display("p=350,150"); }
N31:NetTestRouter { @display("p=400,150"); }
N32:NetTestRouter { @display("p=450,150"); }
N33:NetTestRouter { @display("p=500,150"); }
N34:NetTestRouter { @display("p=550,150"); }
N35:NetTestRouter { @display("p=600,150"); }
N36:NetTestRouter { @display("p=50,200"); }
N37:NetTestRouter { @display("p=100,200"); }
N38:NetTestRouter { @display("p=150,200"); }
N39:NetTestRouter { @display("p=200,200"); }
N40:NetTestRouter { @display("p=250,200"); }
N41:NetTestRouter { @display("p=300,200"); }
N42:NetTestRouter { @display("p=350,200"); }
N43:NetTestRouter { @display("p=400,200"); }
N44:NetTestRouter { @display("p=450,200"); }
N45:NetTestRouter { @display("p=500,200"); }
N46:NetTestRouter { @display("p=550,200"); }
N47:NetTestRouter { @display("p=600,200"); }
N48:NetTestRouter { @display("p=50,250"); }
N49:NetTestRouter { @display("p=100,250"); }
N50:NetTestRouter { @display("p=150,250"); }
N51:NetTestRouter { @display("p=200,250"); }
N52:NetTestRouter { @display("p=250,250"); }
N53:NetTestRouter { @display("p=300,250"); }
N54:NetTestRouter { @display("p=350,250"); }
N55:NetTestRouter { @display("p=400,250"); }
N56:NetTestRouter { @display("p=450,250"); }
N57:NetTestRouter { @display("p=500,250"); }
N58:NetTestRouter { @display("p=550,250"); }
N59:NetTestRouter { @display("p=600,250"); }
N60:NetTestRouter { @display("p=50,300"); }
N61:NetTestRouter { @display("p=100,300"); }
N62:NetTestRouter { @display("p=150,300"); }
N63:NetTestRouter { @display("p=200,300"); }
N64:NetTestRouter { @display("p=250,300"); }
N65:NetTestRouter { @display("p=300,300"); }
N66:NetTestRouter { @display("p=350,300"); }
N67:NetTestRouter { @display("p=400,300"); }
N68:NetTestRouter { @display("p=450,300"); }
N69:NetTestRouter { @display("p=500,300"); }
N70:NetTestRouter { @display("p=550,300"); }
N71:NetTestRouter { @display("p=600,300"); }
N72:NetTestRouter { @display("p=50,350"); }
N73:NetTestRouter { @display("p=100,350"); }
N74:NetTestRouter { @display("p=150,350"); }
N75:NetTestRouter { @display("p=200,350"); }
N76:NetTestRouter { @display("p=250,350"); }
N77:NetTestRouter { @display("p=300,350"); }
N78:NetTestRouter { @display("p=350,350"); }
N79:NetTestRouter { @display("p=400,350"); }
N80:NetTestRouter { @display("p=450,350"); }
N81:NetTestRouter { @display("p=500,350"); }
N82:NetTestRouter { @display("p=550,350"); }
N83:NetTestRouter { @display("p=600,350"); }
N84:NetTestRouter { @display("p=50,400"); }
N85:NetTestRouter { @display("p=100,400"); }
N86:NetTestRouter { @display("p=150,400"); }
N87:NetTestRouter { @display("p=200,400"); }
N88:NetTestRouter { @display("p=250,400"); }
N89:NetTestRouter { @display("p=300,400"); }
N90:NetTestRouter { @display("p=350,400"); }
N91:NetTestRouter { @display("p=400,400"); }
N92:NetTestRouter { @display("p=450,400"); }
N93:NetTestRouter { @display("p=500,400"); }
N94:NetTestRouter { @display("p=550,400"); }
N95:NetTestRouter { @display("p=600,400"); }
N96:NetTestRouter { @display("p=50,450"); }
N97:NetTestRouter { @display("p=100,450"); }
N98:NetTestRouter { @display("p=150,450"); }
N99:NetTestRouter { @display("p=200,450"); }
listener: NetTestListener;

connections:
N0.medium++ <-->  N8.medium++;
N0.medium++ <-->  N9.medium++;
N0.medium++ <-->  N18.medium++;
N0.medium++ <-->  N23.medium++;
N0.medium++ <-->  N60.medium++;
N1.medium++ <-->  N8.medium++;
N1.medium++ <-->  N9.medium++;
N1.medium++ <-->  N10.medium++;
N1.medium++ <-->  N12.medium++;
N1.medium++ <-->  N13.medium++;
N1.medium++ <-->  N14.medium++;
N1.medium++ <-->  N16.medium++;
N1.medium++ <-->  N20.medium++;
N1.medium++ <-->  N21.medium++;
N1.medium++ <-->  N22.medium++;
N1.medium++ <-->  N23.medium++;
N1.medium++ <-->  N26.medium++;
N1.medium++ <-->  N35.medium++;
N1.medium++ <-->  N36.medium++;
N1.medium++ <-->  N42.medium++;
N1.medium++ <-->  N43.medium++;
N1.medium++ <-->  N46.medium++;
N1.medium++ <-->  N48.medium++;
N1.medium++ <-->  N50.medium++;
N1.medium++ <-->  N58.medium++;
N1.medium++ <-->  N66.medium++;
N1.medium++ <-->  N83.medium++;
N1.medium++ <-->  N85.medium++;
N2.medium++ <-->  N8.medium++;
N2.medium++ <-->  N9.medium++;
N2.medium++ <-->  N10.medium++;
N2.medium++ <-->  N11.medium++;
N2.medium++ <-->  N12.medium++;
N2.medium++ <-->  N13.medium++;
N2.medium++ <-->  N15.medium++;
N2.medium++ <-->  N16.medium++;
N2.medium++ <-->  N20.medium++;
N2.medium++ <-->  N27.medium++;
N2.medium++ <-->  N31.medium++;
N2.medium++ <-->  N41.medium++;
N2.medium++ <-->  N43.medium++;
N2.medium++ <-->  N50.medium++;
N2.medium++ <-->  N57.medium++;
N2.medium++ <-->  N58.medium++;
N2.medium++ <-->  N62.medium++;
N2.medium++ <-->  N76.medium++;
N2.medium++ <-->  N80.medium++;
N2.medium++ <-->  N86.medium++;
N3.medium++ <-->  N8.medium++;
N3.medium++ <-->  N9.medium++;
N3.medium++ <-->  N10.medium++;
N3.medium++ <-->  N11.medium++;
N3.medium++ <-->  N12.medium++;
N3.medium++ <-->  N15.medium++;
N3.medium++ <-->  N16.medium++;
N3.medium++ <-->  N18.medium++;
N3.medium++ <-->  N24.medium++;
N3.medium++ <-->  N25.medium++;
N3.medium++ <-->  N28.medium++;
N3.medium++ <-->  N33.medium++;
N3.medium++ <-->  N34.medium++;
N3.medium++ <-->  N35.medium++;
N3.medium++ <-->  N39.medium++;
N3.medium++ <-->  N40.medium++;
N3.medium++ <-->  N51.medium++;
N3.medium++ <-->  N53.medium++;
N3.medium++ <-->  N57.medium++;
N3.medium++ <-->  N65.medium++;
N3.medium++ <-->  N72.medium++;
N3.medium++ <-->  N76.medium++;
N3.medium++ <-->  N78.medium++;
N3.medium++ <-->  N90.medium++;
N3.medium++ <-->  N95.medium++;
N3.medium++ <-->  N98.medium++;
N3.medium++ <-->  N99.medium++;
N4.medium++ <-->  N8.medium++;
N4.medium++ <-->  N9.medium++;
N4.medium++ <-->  N10.medium++;
N4.medium++ <-->  N11.medium++;
N4.medium++ <-->  N14.medium++;
N4.medium++ <-->  N17.medium++;
N4.medium++ <-->  N25.medium++;
N4.medium++ <-->  N42.medium++;
N4.medium++ <-->  N52.medium++;
N4.medium++ <-->  N92.medium++;
N5.medium++ <-->  N8.medium++;
N6.medium++ <-->  N8.medium++;
N6.medium++ <-->  N9.medium++;
N6.medium++ <-->  N10.medium++;
N6.medium++ <-->  N11.medium++;
N6.medium++ <-->  N12.medium++;
N6.medium++ <-->  N30.medium++;
N6.medium++ <-->  N75.medium++;
N6.medium++ <-->  N88.medium++;
N7.medium++ <-->  N8.medium++;
N7.medium++ <-->  N9.medium++;
N7.medium++ <-->  N10.medium++;
N7.medium++ <-->  N11.medium++;
N7.medium++ <-->  N12.medium++;
N7.medium++ <-->  N13.medium++;
N7.medium++ <-->  N17.medium++;
N7.medium++ <-->  N23.medium++;
N7.medium++ <-->  N29.medium++;
N7.medium++ <-->  N31.medium++;
N7.medium++ <-->  N38.medium++;
N7.medium++ <-->  N39.medium++;
N7.medium++ <-->  N40.medium++;
N7.medium++ <-->  N43.medium++;
N7.medium++ <-->  N45.medium++;
N7.medium++ <-->  N46.medium++;
N7.medium++ <-->  N52.medium++;
N7.medium++ <-->  N58.medium++;
N7.medium++ <-->  N60.medium++;
N7.medium++ <-->  N62.medium++;
N7.medium++ <-->  N63.medium++;
N7.medium++ <-->  N70.medium++;
N7.medium++ <-->  N74.medium++;
N7.medium++ <-->  N76.medium++;
N7.medium++ <-->  N77.medium++;
N7.medium++ <-->  N83.medium++;
N7.medium++ <-->  N84.medium++;
N7.medium++ <-->  N85.medium++;
N7.medium++ <-->  N90.medium++;
N7.medium++ <-->  N93.medium++;
N7.medium++ <-->  N95.medium++;
N7.medium++ <-->  N99.medium++;
N8.medium++ <-->  N9.medium++;
N8.medium++ <-->  N10.medium++;
N8.medium++ <-->  N11.medium++;
N8.medium++ <-->  N12.medium++;
N8.medium++ <-->  N13.medium++;
N8.medium++ <-->  N14.medium++;
N8.medium++ <-->  N15.medium++;
N8.medium++ <-->  N16.medium++;
N8.medium++ <-->  N19.medium++;
N8.medium++ <-->  N21.medium++;
N8.medium++ <-->  N22.medium++;
N8.medium++ <-->  N29.medium++;
N8.medium++ <-->  N33.medium++;
N8.medium++ <-->  N36.medium++;
N8.medium++ <-->  N41.medium++;
N8.medium++ <-->  N42.medium++;
N8.medium++ <-->  N47.medium++;
N8.medium++ <-->  N50.medium++;
N8.medium++ <-->  N53.medium++;
N8.medium++ <-->  N72.medium++;
N8.medium++ <-->  N80.medium++;
N8.medium++ <-->  N85.medium++;
N8.medium++ <-->  N97.medium++;
N8.medium++ <-->  N98.medium++;
N9.medium++ <-->  N10.medium++;
N9.medium++ <-->  N11.medium++;
N9.medium++ <-->  N12.medium++;
N9.medium++ <-->  N13.medium++;
N9.medium++ <-->  N14.medium++;
N9.medium++ <-->  N15.medium++;
N9.medium++ <-->  N17.medium++;
N9.medium++ <-->  N18.medium++;
N9.medium++ <-->  N19.medium++;
N9.medium++ <-->  N21.medium++;
N9.medium++ <-->  N22.medium++;
N9.medium++ <-->  N24.medium++;
N9.medium++ <-->  N25.medium++;
N9.medium++ <-->  N26.medium++;
N9.medium++ <-->  N27.medium++;
N9.medium++ <-->  N28.medium++;
N9.medium++ <-->  N29.medium++;
N9.medium++ <-->  N33.medium++;
N9.medium++ <-->  N34.medium++;
N9.medium++ <-->  N35.medium++;
N9.medium++ <-->  N37.medium++;
N9.medium++ <-->  N40.medium++;
N9.medium++ <-->  N43.medium++;
N9.medium++ <-->  N45.medium++;
N9.medium++ <-->  N47.medium++;
N9.medium++ <-->  N49.medium++;
N9.medium++ <-->  N51.medium++;
N9.medium++ <-->  N53.medium++;
N9.medium++ <-->  N58.medium++;
N9.medium++ <-->  N59.medium++;
N9.medium++ <-->  N69.medium++;
N9.medium++ <-->  N77.medium++;
N9.medium++ <-->  N81.medium++;
N9.medium++ <-->  N82.medium++;
N9.medium++ <-->  N83.medium++;
N9.medium++ <-->  N87.medium++;
N9.medium++ <-->  N91.medium++;
N9.medium++ <-->  N92.medium++;
N9.medium++ <-->  N94.medium++;
N10.medium++ <-->  N11.medium++;
N10.medium++ <-->  N12.medium++;
N10.medium++ <-->  N13.medium++;
N10.medium++ <-->  N14.medium++;
N10.medium++ <-->  N16.medium++;
N10.medium++ <-->  N17.medium++;
N10.medium++ <-->  N19.medium++;
N10.medium++ <-->  N20.medium++;
N10.medium++ <-->  N21.medium++;
N10.medium++ <-->  N22.medium++;
N10.medium++ <-->  N24.medium++;
N10.medium++ <-->  N27.medium++;
N10.medium++ <-->  N29.medium++;
N10.medium++ <-->  N30.medium++;
N10.medium++ <-->  N31.medium++;
N10.medium++ <-->  N33.medium++;
N10.medium++ <-->  N36.medium++;
N10.medium++ <-->  N38.medium++;
N10.medium++ <-->  N41.medium++;
N10.medium++ <-->  N42.medium++;
N10.medium++ <-->  N47.medium++;
N10.medium++ <-->  N49.medium++;
N10.medium++ <-->  N53.medium++;
N10.medium++ <-->  N55.medium++;
N10.medium++ <-->  N56.medium++;
N10.medium++ <-->  N62.medium++;
N10.medium++ <-->  N63.medium++;
N10.medium++ <-->  N64.medium++;
N10.medium++ <-->  N67.medium++;
N10.medium++ <-->  N68.medium++;
N10.medium++ <-->  N70.medium++;
N10.medium++ <-->  N71.medium++;
N10.medium++ <-->  N82.medium++;
N10.medium++ <-->  N83.medium++;
N10.medium++ <-->  N85.medium++;
N10.medium++ <-->  N87.medium++;
N10.medium++ <-->  N89.medium++;
N10.medium++ <-->  N90.medium++;
N10.medium++ <-->  N91.medium++;
N10.medium++ <-->  N93.medium++;
N10.medium++ <-->  N95.medium++;
N10.medium++ <-->  N96.medium++;
N11.medium++ <-->  N13.medium++;
N11.medium++ <-->  N14.medium++;
N11.medium++ <-->  N15.medium++;
N11.medium++ <-->  N16.medium++;
N11.medium++ <-->  N18.medium++;
N11.medium++ <-->  N19.medium++;
N11.medium++ <-->  N20.medium++;
N11.medium++ <-->  N21.medium++;
N11.medium++ <-->  N23.medium++;
N11.medium++ <-->  N25.medium++;
N11.medium++ <-->  N26.medium++;
N11.medium++ <-->  N28.medium++;
N11.medium++ <-->  N30.medium++;
N11.medium++ <-->  N32.medium++;
N11.medium++ <-->  N38.medium++;
N11.medium++ <-->  N40.medium++;
N11.medium++ <-->  N51.medium++;
N11.medium++ <-->  N61.medium++;
N11.medium++ <-->  N62.medium++;
N11.medium++ <-->  N65.medium++;
N11.medium++ <-->  N80.medium++;
N11.medium++ <-->  N82.medium++;
N11.medium++ <-->  N83.medium++;
N11.medium++ <-->  N88.medium++;
N11.medium++ <-->  N93.medium++;
N11.medium++ <-->  N95.medium++;
N11.medium++ <-->  N97.medium++;
N12.medium++ <-->  N13.medium++;
N12.medium++ <-->  N14.medium++;
N12.medium++ <-->  N15.medium++;
N12.medium++ <-->  N17.medium++;
N12.medium++ <-->  N18.medium++;
N12.medium++ <-->  N19.medium++;
N12.medium++ <-->  N20.medium++;
N12.medium++ <-->  N22.medium++;
N12.medium++ <-->  N23.medium++;
N12.medium++ <-->  N25.medium++;
N12.medium++ <-->  N27.medium++;
N12.medium++ <-->  N28.medium++;
N12.medium++ <-->  N32.medium++;
N12.medium++ <-->  N39.medium++;
N12.medium++ <-->  N40.medium++;
N12.medium++ <-->  N42.medium++;
N12.medium++ <-->  N44.medium++;
N12.medium++ <-->  N45.medium++;
N12.medium++ <-->  N48.medium++;
N12.medium++ <-->  N49.medium++;
N12.medium++ <-->  N51.medium++;
N12.medium++ <-->  N58.medium++;
N12.medium++ <-->  N60.medium++;
N12.medium++ <-->  N64.medium++;
N12.medium++ <-->  N67.medium++;
N12.medium++ <-->  N71.medium++;
N12.medium++ <-->  N73.medium++;
N12.medium++ <-->  N79.medium++;
N12.medium++ <-->  N81.medium++;
N12.medium++ <-->  N86.medium++;
N12.medium++ <-->  N95.medium++;
N13.medium++ <-->  N14.medium++;
N13.medium++ <-->  N15.medium++;
N13.medium++ <-->  N16.medium++;
N13.medium++ <-->  N17.medium++;
N13.medium++ <-->  N19.medium++;
N13.medium++ <-->  N20.medium++;
N13.medium++ <-->  N21.medium++;
N13.medium++ <-->  N22.medium++;
N13.medium++ <-->  N26.medium++;
N13.medium++ <-->  N28.medium++;
N13.medium++ <-->  N29.medium++;
N13.medium++ <-->  N35.medium++;
N13.medium++ <-->  N37.medium++;
N13.medium++ <-->  N39.medium++;
N13.medium++ <-->  N41.medium++;
N13.medium++ <-->  N44.medium++;
N13.medium++ <-->  N53.medium++;
N13.medium++ <-->  N54.medium++;
N13.medium++ <-->  N57.medium++;
N13.medium++ <-->  N59.medium++;
N13.medium++ <-->  N64.medium++;
N13.medium++ <-->  N67.medium++;
N13.medium++ <-->  N69.medium++;
N13.medium++ <-->  N83.medium++;
N13.medium++ <-->  N84.medium++;
N13.medium++ <-->  N91.medium++;
N13.medium++ <-->  N98.medium++;
N14.medium++ <-->  N15.medium++;
N14.medium++ <-->  N16.medium++;
N14.medium++ <-->  N17.medium++;
N14.medium++ <-->  N18.medium++;
N14.medium++ <-->  N20.medium++;
N14.medium++ <-->  N21.medium++;
N14.medium++ <-->  N23.medium++;
N14.medium++ <-->  N24.medium++;
N14.medium++ <-->  N26.medium++;
N14.medium++ <-->  N28.medium++;
N14.medium++ <-->  N30.medium++;
N14.medium++ <-->  N31.medium++;
N14.medium++ <-->  N32.medium++;
N14.medium++ <-->  N33.medium++;
N14.medium++ <-->  N36.medium++;
N14.medium++ <-->  N37.medium++;
N14.medium++ <-->  N45.medium++;
N14.medium++ <-->  N51.medium++;
N14.medium++ <-->  N52.medium++;
N14.medium++ <-->  N55.medium++;
N14.medium++ <-->  N60.medium++;
N14.medium++ <-->  N61.medium++;
N14.medium++ <-->  N62.medium++;
N14.medium++ <-->  N63.medium++;
N14.medium++ <-->  N65.medium++;
N14.medium++ <-->  N67.medium++;
N14.medium++ <-->  N78.medium++;
N14.medium++ <-->  N81.medium++;
N14.medium++ <-->  N88.medium++;
N14.medium++ <-->  N90.medium++;
N14.medium++ <-->  N96.medium++;
N15.medium++ <-->  N17.medium++;
N15.medium++ <-->  N18.medium++;
N15.medium++ <-->  N19.medium++;
N15.medium++ <-->  N21.medium++;
N15.medium++ <-->  N24.medium++;
N15.medium++ <-->  N30.medium++;
N15.medium++ <-->  N32.medium++;
N15.medium++ <-->  N36.medium++;
N15.medium++ <-->  N37.medium++;
N15.medium++ <-->  N38.medium++;
N15.medium++ <-->  N50.medium++;
N15.medium++ <-->  N51.medium++;
N15.medium++ <-->  N54.medium++;
N15.medium++ <-->  N55.medium++;
N15.medium++ <-->  N56.medium++;
N15.medium++ <-->  N59.medium++;
N15.medium++ <-->  N61.medium++;
N15.medium++ <-->  N68.medium++;
N15.medium++ <-->  N90.medium++;
N15.medium++ <-->  N92.medium++;
N16.medium++ <-->  N22.medium++;
N16.medium++ <-->  N27.medium++;
N16.medium++ <-->  N31.medium++;
N16.medium++ <-->  N32.medium++;
N16.medium++ <-->  N38.medium++;
N16.medium++ <-->  N47.medium++;
N16.medium++ <-->  N54.medium++;
N16.medium++ <-->  N59.medium++;
N16.medium++ <-->  N63.medium++;
N16.medium++ <-->  N65.medium++;
N16.medium++ <-->  N74.medium++;
N16.medium++ <-->  N79.medium++;
N17.medium++ <-->  N18.medium++;
N17.medium++ <-->  N19.medium++;
N17.medium++ <-->  N24.medium++;
N17.medium++ <-->  N26.medium++;
N17.medium++ <-->  N36.medium++;
N17.medium++ <-->  N40.medium++;
N17.medium++ <-->  N43.medium++;
N17.medium++ <-->  N74.medium++;
N17.medium++ <-->  N90.medium++;
N17.medium++ <-->  N94.medium++;
N18.medium++ <-->  N20.medium++;
N18.medium++ <-->  N25.medium++;
N18.medium++ <-->  N27.medium++;
N18.medium++ <-->  N68.medium++;
N18.medium++ <-->  N82.medium++;
N18.medium++ <-->  N96.medium++;
N19.medium++ <-->  N22.medium++;
N19.medium++ <-->  N24.medium++;
N19.medium++ <-->  N25.medium++;
N19.medium++ <-->  N26.medium++;
N19.medium++ <-->  N27.medium++;
N19.medium++ <-->  N30.medium++;
N19.medium++ <-->  N32.medium++;
N19.medium++ <-->  N34.medium++;
N19.medium++ <-->  N42.medium++;
N19.medium++ <-->  N52.medium++;
N19.medium++ <-->  N55.medium++;
N19.medium++ <-->  N58.medium++;
N19.medium++ <-->  N66.medium++;
N19.medium++ <-->  N77.medium++;
N19.medium++ <-->  N83.medium++;
N19.medium++ <-->  N89.medium++;
N20.medium++ <-->  N23.medium++;
N20.medium++ <-->  N24.medium++;
N20.medium++ <-->  N25.medium++;
N20.medium++ <-->  N29.medium++;
N20.medium++ <-->  N31.medium++;
N20.medium++ <-->  N39.medium++;
N20.medium++ <-->  N47.medium++;
N20.medium++ <-->  N48.medium++;
N20.medium++ <-->  N54.medium++;
N20.medium++ <-->  N79.medium++;
N20.medium++ <-->  N80.medium++;
N20.medium++ <-->  N91.medium++;
N20.medium++ <-->  N98.medium++;
N21.medium++ <-->  N23.medium++;
N21.medium++ <-->  N28.medium++;
N21.medium++ <-->  N29.medium++;
N21.medium++ <-->  N34.medium++;
N21.medium++ <-->  N44.medium++;
N21.medium++ <-->  N49.medium++;
N21.medium++ <-->  N57.medium++;
N21.medium++ <-->  N69.medium++;
N21.medium++ <-->  N70.medium++;
N21.medium++ <-->  N80.medium++;
N21.medium++ <-->  N85.medium++;
N22.medium++ <-->  N30.medium++;
N22.medium++ <-->  N33.medium++;
N22.medium++ <-->  N35.medium++;
N22.medium++ <-->  N37.medium++;
N22.medium++ <-->  N40.medium++;
N22.medium++ <-->  N41.medium++;
N22.medium++ <-->  N64.medium++;
N22.medium++ <-->  N65.medium++;
N22.medium++ <-->  N70.medium++;
N22.medium++ <-->  N73.medium++;
N22.medium++ <-->  N75.medium++;
N22.medium++ <-->  N78.medium++;
N22.medium++ <-->  N80.medium++;
N22.medium++ <-->  N81.medium++;
N22.medium++ <-->  N96.medium++;
N22.medium++ <-->  N97.medium++;
N23.medium++ <-->  N28.medium++;
N23.medium++ <-->  N34.medium++;
N23.medium++ <-->  N68.medium++;
N23.medium++ <-->  N76.medium++;
N23.medium++ <-->  N84.medium++;
N23.medium++ <-->  N90.medium++;
N24.medium++ <-->  N27.medium++;
N24.medium++ <-->  N29.medium++;
N24.medium++ <-->  N44.medium++;
N24.medium++ <-->  N46.medium++;
N24.medium++ <-->  N52.medium++;
N24.medium++ <-->  N54.medium++;
N24.medium++ <-->  N56.medium++;
N24.medium++ <-->  N77.medium++;
N24.medium++ <-->  N89.medium++;
N25.medium++ <-->  N26.medium++;
N25.medium++ <-->  N30.medium++;
N25.medium++ <-->  N31.medium++;
N25.medium++ <-->  N35.medium++;
N25.medium++ <-->  N36.medium++;
N25.medium++ <-->  N38.medium++;
N25.medium++ <-->  N40.medium++;
N25.medium++ <-->  N41.medium++;
N25.medium++ <-->  N45.medium++;
N25.medium++ <-->  N47.medium++;
N25.medium++ <-->  N48.medium++;
N25.medium++ <-->  N51.medium++;
N25.medium++ <-->  N55.medium++;
N25.medium++ <-->  N96.medium++;
N25.medium++ <-->  N97.medium++;
N26.medium++ <-->  N31.medium++;
N26.medium++ <-->  N41.medium++;
N26.medium++ <-->  N42.medium++;
N26.medium++ <-->  N51.medium++;
N26.medium++ <-->  N59.medium++;
N26.medium++ <-->  N62.medium++;
N26.medium++ <-->  N67.medium++;
N26.medium++ <-->  N68.medium++;
N26.medium++ <-->  N85.medium++;
N26.medium++ <-->  N94.medium++;
N26.medium++ <-->  N98.medium++;
N27.medium++ <-->  N33.medium++;
N27.medium++ <-->  N34.medium++;
N27.medium++ <-->  N35.medium++;
N27.medium++ <-->  N38.medium++;
N27.medium++ <-->  N46.medium++;
N27.medium++ <-->  N47.medium++;
N27.medium++ <-->  N54.medium++;
N27.medium++ <-->  N58.medium++;
N27.medium++ <-->  N60.medium++;
N27.medium++ <-->  N66.medium++;
N27.medium++ <-->  N67.medium++;
N27.medium++ <-->  N70.medium++;
N27.medium++ <-->  N76.medium++;
N27.medium++ <-->  N81.medium++;
N28.medium++ <-->  N32.medium++;
N28.medium++ <-->  N33.medium++;
N28.medium++ <-->  N43.medium++;
N28.medium++ <-->  N45.medium++;
N28.medium++ <-->  N88.medium++;
N28.medium++ <-->  N91.medium++;
N29.medium++ <-->  N32.medium++;
N29.medium++ <-->  N37.medium++;
N29.medium++ <-->  N39.medium++;
N29.medium++ <-->  N44.medium++;
N29.medium++ <-->  N61.medium++;
N29.medium++ <-->  N63.medium++;
N29.medium++ <-->  N64.medium++;
N29.medium++ <-->  N73.medium++;
N30.medium++ <-->  N35.medium++;
N30.medium++ <-->  N43.medium++;
N30.medium++ <-->  N50.medium++;
N30.medium++ <-->  N56.medium++;
N30.medium++ <-->  N61.medium++;
N30.medium++ <-->  N91.medium++;
N30.medium++ <-->  N92.medium++;
N30.medium++ <-->  N93.medium++;
N31.medium++ <-->  N46.medium++;
N31.medium++ <-->  N49.medium++;
N31.medium++ <-->  N59.medium++;
N31.medium++ <-->  N89.medium++;
N31.medium++ <-->  N90.medium++;
N32.medium++ <-->  N34.medium++;
N32.medium++ <-->  N37.medium++;
N32.medium++ <-->  N38.medium++;
N32.medium++ <-->  N39.medium++;
N32.medium++ <-->  N42.medium++;
N32.medium++ <-->  N46.medium++;
N32.medium++ <-->  N48.medium++;
N32.medium++ <-->  N49.medium++;
N32.medium++ <-->  N50.medium++;
N32.medium++ <-->  N68.medium++;
N32.medium++ <-->  N97.medium++;
N33.medium++ <-->  N34.medium++;
N33.medium++ <-->  N36.medium++;
N33.medium++ <-->  N39.medium++;
N33.medium++ <-->  N47.medium++;
N33.medium++ <-->  N62.medium++;
N33.medium++ <-->  N63.medium++;
N33.medium++ <-->  N69.medium++;
N33.medium++ <-->  N72.medium++;
N33.medium++ <-->  N77.medium++;
N34.medium++ <-->  N48.medium++;
N34.medium++ <-->  N50.medium++;
N34.medium++ <-->  N55.medium++;
N34.medium++ <-->  N56.medium++;
N34.medium++ <-->  N60.medium++;
N34.medium++ <-->  N61.medium++;
N34.medium++ <-->  N63.medium++;
N34.medium++ <-->  N69.medium++;
N34.medium++ <-->  N73.medium++;
N34.medium++ <-->  N75.medium++;
N34.medium++ <-->  N84.medium++;
N34.medium++ <-->  N86.medium++;
N34.medium++ <-->  N88.medium++;
N35.medium++ <-->  N37.medium++;
N35.medium++ <-->  N45.medium++;
N35.medium++ <-->  N50.medium++;
N35.medium++ <-->  N60.medium++;
N35.medium++ <-->  N62.medium++;
N35.medium++ <-->  N67.medium++;
N35.medium++ <-->  N72.medium++;
N35.medium++ <-->  N75.medium++;
N36.medium++ <-->  N44.medium++;
N36.medium++ <-->  N75.medium++;
N36.medium++ <-->  N79.medium++;
N36.medium++ <-->  N87.medium++;
N37.medium++ <-->  N49.medium++;
N37.medium++ <-->  N53.medium++;
N37.medium++ <-->  N63.medium++;
N37.medium++ <-->  N82.medium++;
N37.medium++ <-->  N84.medium++;
N37.medium++ <-->  N91.medium++;
N38.medium++ <-->  N41.medium++;
N38.medium++ <-->  N49.medium++;
N38.medium++ <-->  N52.medium++;
N38.medium++ <-->  N66.medium++;
N39.medium++ <-->  N44.medium++;
N39.medium++ <-->  N56.medium++;
N39.medium++ <-->  N64.medium++;
N39.medium++ <-->  N67.medium++;
N39.medium++ <-->  N74.medium++;
N39.medium++ <-->  N76.medium++;
N39.medium++ <-->  N94.medium++;
N39.medium++ <-->  N95.medium++;
N40.medium++ <-->  N43.medium++;
N40.medium++ <-->  N44.medium++;
N40.medium++ <-->  N45.medium++;
N40.medium++ <-->  N52.medium++;
N40.medium++ <-->  N54.medium++;
N40.medium++ <-->  N56.medium++;
N40.medium++ <-->  N57.medium++;
N40.medium++ <-->  N59.medium++;
N40.medium++ <-->  N65.medium++;
N40.medium++ <-->  N77.medium++;
N40.medium++ <-->  N79.medium++;
N40.medium++ <-->  N97.medium++;
N41.medium++ <-->  N48.medium++;
N41.medium++ <-->  N59.medium++;
N41.medium++ <-->  N71.medium++;
N42.medium++ <-->  N46.medium++;
N42.medium++ <-->  N48.medium++;
N42.medium++ <-->  N53.medium++;
N42.medium++ <-->  N55.medium++;
N42.medium++ <-->  N64.medium++;
N42.medium++ <-->  N75.medium++;
N42.medium++ <-->  N78.medium++;
N42.medium++ <-->  N82.medium++;
N43.medium++ <-->  N56.medium++;
N43.medium++ <-->  N61.medium++;
N43.medium++ <-->  N64.medium++;
N43.medium++ <-->  N73.medium++;
N43.medium++ <-->  N88.medium++;
N43.medium++ <-->  N89.medium++;
N43.medium++ <-->  N95.medium++;
N44.medium++ <-->  N55.medium++;
N44.medium++ <-->  N68.medium++;
N44.medium++ <-->  N69.medium++;
N44.medium++ <-->  N75.medium++;
N44.medium++ <-->  N78.medium++;
N44.medium++ <-->  N85.medium++;
N44.medium++ <-->  N86.medium++;
N44.medium++ <-->  N89.medium++;
N44.medium++ <-->  N96.medium++;
N45.medium++ <-->  N46.medium++;
N45.medium++ <-->  N60.medium++;
N45.medium++ <-->  N66.medium++;
N45.medium++ <-->  N69.medium++;
N45.medium++ <-->  N75.medium++;
N45.medium++ <-->  N87.medium++;
N45.medium++ <-->  N92.medium++;
N46.medium++ <-->  N70.medium++;
N47.medium++ <-->  N58.medium++;
N47.medium++ <-->  N66.medium++;
N47.medium++ <-->  N84.medium++;
N47.medium++ <-->  N99.medium++;
N48.medium++ <-->  N69.medium++;
N48.medium++ <-->  N71.medium++;
N48.medium++ <-->  N73.medium++;
N48.medium++ <-->  N74.medium++;
N48.medium++ <-->  N76.medium++;
N48.medium++ <-->  N78.medium++;
N48.medium++ <-->  N95.medium++;
N49.medium++ <-->  N52.medium++;
N49.medium++ <-->  N54.medium++;
N49.medium++ <-->  N57.medium++;
N49.medium++ <-->  N79.medium++;
N49.medium++ <-->  N93.medium++;
N49.medium++ <-->  N94.medium++;
N49.medium++ <-->  N99.medium++;
N50.medium++ <-->  N53.medium++;
N50.medium++ <-->  N68.medium++;
N50.medium++ <-->  N93.medium++;
N50.medium++ <-->  N97.medium++;
N51.medium++ <-->  N57.medium++;
N51.medium++ <-->  N72.medium++;
N51.medium++ <-->  N86.medium++;
N52.medium++ <-->  N61.medium++;
N52.medium++ <-->  N66.medium++;
N53.medium++ <-->  N65.medium++;
N53.medium++ <-->  N87.medium++;
N54.medium++ <-->  N73.medium++;
N55.medium++ <-->  N57.medium++;
N55.medium++ <-->  N66.medium++;
N55.medium++ <-->  N77.medium++;
N55.medium++ <-->  N81.medium++;
N56.medium++ <-->  N92.medium++;
N57.medium++ <-->  N81.medium++;
N57.medium++ <-->  N85.medium++;
N57.medium++ <-->  N87.medium++;
N58.medium++ <-->  N72.medium++;
N58.medium++ <-->  N74.medium++;
N58.medium++ <-->  N92.medium++;
N59.medium++ <-->  N93.medium++;
N59.medium++ <-->  N98.medium++;
N60.medium++ <-->  N83.medium++;
N60.medium++ <-->  N84.medium++;
N60.medium++ <-->  N96.medium++;
N61.medium++ <-->  N88.medium++;
N62.medium++ <-->  N71.medium++;
N62.medium++ <-->  N72.medium++;
N62.medium++ <-->  N99.medium++;
N63.medium++ <-->  N65.medium++;
N63.medium++ <-->  N71.medium++;
N63.medium++ <-->  N77.medium++;
N63.medium++ <-->  N96.medium++;
N64.medium++ <-->  N80.medium++;
N67.medium++ <-->  N70.medium++;
N67.medium++ <-->  N74.medium++;
N67.medium++ <-->  N82.medium++;
N67.medium++ <-->  N87.medium++;
N68.medium++ <-->  N70.medium++;
N68.medium++ <-->  N71.medium++;
N68.medium++ <-->  N79.medium++;
N68.medium++ <-->  N81.medium++;
N68.medium++ <-->  N82.medium++;
N69.medium++ <-->  N78.medium++;
N70.medium++ <-->  N71.medium++;
N71.medium++ <-->  N72.medium++;
N71.medium++ <-->  N73.medium++;
N71.medium++ <-->  N76.medium++;
N71.medium++ <-->  N92.medium++;
N72.medium++ <-->  N74.medium++;
N72.medium++ <-->  N78.medium++;
N72.medium++ <-->  N79.medium++;
N72.medium++ <-->  N86.medium++;
N72.medium++ <-->  N94.medium++;
N72.medium++ <-->  N99.medium++;
N73.medium++ <-->  N89.medium++;
N76.medium++ <-->  N86.medium++;
N77.medium++ <-->  N94.medium++;
N78.medium++ <-->  N80.medium++;
N78.medium++ <-->  N84.medium++;
N78.medium++ <-->  N87.medium++;
N78.medium++ <-->  N91.medium++;
N79.medium++ <-->  N94.medium++;
N81.medium++ <-->  N88.medium++;
N83.medium++ <-->  N86.medium++;
N87.medium++ <-->  N98.medium++;
N88.medium++ <-->  N89.medium++;
N91.medium++ <-->  N93.medium++;
N93.medium++ <-->  N98.medium++;
N94.medium++ <-->  N97.medium++;
N95.medium++ <-->  N99.medium++;
N98.medium++ <-->  N99.medium++;

}
