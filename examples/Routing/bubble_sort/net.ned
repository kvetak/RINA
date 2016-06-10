package rina.examples.Routing.bubble_sort;

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
N12:NetTestRouter { @display("p=650,50"); }
N13:NetTestRouter { @display("p=50,100"); }
N14:NetTestRouter { @display("p=100,100"); }
N15:NetTestRouter { @display("p=150,100"); }
N16:NetTestRouter { @display("p=200,100"); }
N17:NetTestRouter { @display("p=250,100"); }
N18:NetTestRouter { @display("p=300,100"); }
N19:NetTestRouter { @display("p=350,100"); }
N20:NetTestRouter { @display("p=400,100"); }
N21:NetTestRouter { @display("p=450,100"); }
N22:NetTestRouter { @display("p=500,100"); }
N23:NetTestRouter { @display("p=550,100"); }
N24:NetTestRouter { @display("p=600,100"); }
N25:NetTestRouter { @display("p=650,100"); }
N26:NetTestRouter { @display("p=50,150"); }
N27:NetTestRouter { @display("p=100,150"); }
N28:NetTestRouter { @display("p=150,150"); }
N29:NetTestRouter { @display("p=200,150"); }
N30:NetTestRouter { @display("p=250,150"); }
N31:NetTestRouter { @display("p=300,150"); }
N32:NetTestRouter { @display("p=350,150"); }
N33:NetTestRouter { @display("p=400,150"); }
N34:NetTestRouter { @display("p=450,150"); }
N35:NetTestRouter { @display("p=500,150"); }
N36:NetTestRouter { @display("p=550,150"); }
N37:NetTestRouter { @display("p=600,150"); }
N38:NetTestRouter { @display("p=650,150"); }
N39:NetTestRouter { @display("p=50,200"); }
N40:NetTestRouter { @display("p=100,200"); }
N41:NetTestRouter { @display("p=150,200"); }
N42:NetTestRouter { @display("p=200,200"); }
N43:NetTestRouter { @display("p=250,200"); }
N44:NetTestRouter { @display("p=300,200"); }
N45:NetTestRouter { @display("p=350,200"); }
N46:NetTestRouter { @display("p=400,200"); }
N47:NetTestRouter { @display("p=450,200"); }
N48:NetTestRouter { @display("p=500,200"); }
N49:NetTestRouter { @display("p=550,200"); }
N50:NetTestRouter { @display("p=600,200"); }
N51:NetTestRouter { @display("p=650,200"); }
N52:NetTestRouter { @display("p=50,250"); }
N53:NetTestRouter { @display("p=100,250"); }
N54:NetTestRouter { @display("p=150,250"); }
N55:NetTestRouter { @display("p=200,250"); }
N56:NetTestRouter { @display("p=250,250"); }
N57:NetTestRouter { @display("p=300,250"); }
N58:NetTestRouter { @display("p=350,250"); }
N59:NetTestRouter { @display("p=400,250"); }
N60:NetTestRouter { @display("p=450,250"); }
N61:NetTestRouter { @display("p=500,250"); }
N62:NetTestRouter { @display("p=550,250"); }
N63:NetTestRouter { @display("p=600,250"); }
N64:NetTestRouter { @display("p=650,250"); }
N65:NetTestRouter { @display("p=50,300"); }
N66:NetTestRouter { @display("p=100,300"); }
N67:NetTestRouter { @display("p=150,300"); }
N68:NetTestRouter { @display("p=200,300"); }
N69:NetTestRouter { @display("p=250,300"); }
N70:NetTestRouter { @display("p=300,300"); }
N71:NetTestRouter { @display("p=350,300"); }
N72:NetTestRouter { @display("p=400,300"); }
N73:NetTestRouter { @display("p=450,300"); }
N74:NetTestRouter { @display("p=500,300"); }
N75:NetTestRouter { @display("p=550,300"); }
N76:NetTestRouter { @display("p=600,300"); }
N77:NetTestRouter { @display("p=650,300"); }
N78:NetTestRouter { @display("p=50,350"); }
N79:NetTestRouter { @display("p=100,350"); }
N80:NetTestRouter { @display("p=150,350"); }
N81:NetTestRouter { @display("p=200,350"); }
N82:NetTestRouter { @display("p=250,350"); }
N83:NetTestRouter { @display("p=300,350"); }
N84:NetTestRouter { @display("p=350,350"); }
N85:NetTestRouter { @display("p=400,350"); }
N86:NetTestRouter { @display("p=450,350"); }
N87:NetTestRouter { @display("p=500,350"); }
N88:NetTestRouter { @display("p=550,350"); }
N89:NetTestRouter { @display("p=600,350"); }
N90:NetTestRouter { @display("p=650,350"); }
N91:NetTestRouter { @display("p=50,400"); }
N92:NetTestRouter { @display("p=100,400"); }
N93:NetTestRouter { @display("p=150,400"); }
N94:NetTestRouter { @display("p=200,400"); }
N95:NetTestRouter { @display("p=250,400"); }
N96:NetTestRouter { @display("p=300,400"); }
N97:NetTestRouter { @display("p=350,400"); }
N98:NetTestRouter { @display("p=400,400"); }
N99:NetTestRouter { @display("p=450,400"); }
N100:NetTestRouter { @display("p=500,400"); }
N101:NetTestRouter { @display("p=550,400"); }
N102:NetTestRouter { @display("p=600,400"); }
N103:NetTestRouter { @display("p=650,400"); }
N104:NetTestRouter { @display("p=50,450"); }
N105:NetTestRouter { @display("p=100,450"); }
N106:NetTestRouter { @display("p=150,450"); }
N107:NetTestRouter { @display("p=200,450"); }
N108:NetTestRouter { @display("p=250,450"); }
N109:NetTestRouter { @display("p=300,450"); }
N110:NetTestRouter { @display("p=350,450"); }
N111:NetTestRouter { @display("p=400,450"); }
N112:NetTestRouter { @display("p=450,450"); }
N113:NetTestRouter { @display("p=500,450"); }
N114:NetTestRouter { @display("p=550,450"); }
N115:NetTestRouter { @display("p=600,450"); }
N116:NetTestRouter { @display("p=650,450"); }
N117:NetTestRouter { @display("p=50,500"); }
N118:NetTestRouter { @display("p=100,500"); }
N119:NetTestRouter { @display("p=150,500"); }
listener: NetTestListener;

connections:
N0.medium++ <-->  N3.medium++;
N0.medium++ <-->  N12.medium++;
N0.medium++ <-->  N50.medium++;
N0.medium++ <-->  N52.medium++;
N1.medium++ <-->  N5.medium++;
N1.medium++ <-->  N52.medium++;
N1.medium++ <-->  N68.medium++;
N1.medium++ <-->  N119.medium++;
N2.medium++ <-->  N8.medium++;
N2.medium++ <-->  N62.medium++;
N2.medium++ <-->  N66.medium++;
N2.medium++ <-->  N114.medium++;
N3.medium++ <-->  N23.medium++;
N3.medium++ <-->  N102.medium++;
N3.medium++ <-->  N113.medium++;
N4.medium++ <-->  N7.medium++;
N4.medium++ <-->  N53.medium++;
N4.medium++ <-->  N67.medium++;
N4.medium++ <-->  N85.medium++;
N5.medium++ <-->  N27.medium++;
N5.medium++ <-->  N37.medium++;
N5.medium++ <-->  N105.medium++;
N7.medium++ <-->  N47.medium++;
N7.medium++ <-->  N77.medium++;
N7.medium++ <-->  N102.medium++;
N7.medium++ <-->  N113.medium++;
N8.medium++ <-->  N47.medium++;
N8.medium++ <-->  N56.medium++;
N8.medium++ <-->  N69.medium++;
N9.medium++ <-->  N17.medium++;
N9.medium++ <-->  N32.medium++;
N9.medium++ <-->  N51.medium++;
N10.medium++ <-->  N20.medium++;
N10.medium++ <-->  N34.medium++;
N10.medium++ <-->  N45.medium++;
N10.medium++ <-->  N80.medium++;
N11.medium++ <-->  N39.medium++;
N11.medium++ <-->  N72.medium++;
N11.medium++ <-->  N74.medium++;
N11.medium++ <-->  N114.medium++;
N12.medium++ <-->  N35.medium++;
N12.medium++ <-->  N53.medium++;
N12.medium++ <-->  N65.medium++;
N12.medium++ <-->  N85.medium++;
N13.medium++ <-->  N48.medium++;
N13.medium++ <-->  N58.medium++;
N13.medium++ <-->  N73.medium++;
N14.medium++ <-->  N16.medium++;
N14.medium++ <-->  N68.medium++;
N14.medium++ <-->  N92.medium++;
N16.medium++ <-->  N40.medium++;
N16.medium++ <-->  N41.medium++;
N16.medium++ <-->  N48.medium++;
N17.medium++ <-->  N47.medium++;
N17.medium++ <-->  N64.medium++;
N17.medium++ <-->  N77.medium++;
N17.medium++ <-->  N110.medium++;
N18.medium++ <-->  N24.medium++;
N18.medium++ <-->  N74.medium++;
N18.medium++ <-->  N108.medium++;
N19.medium++ <-->  N46.medium++;
N19.medium++ <-->  N66.medium++;
N19.medium++ <-->  N71.medium++;
N20.medium++ <-->  N33.medium++;
N20.medium++ <-->  N50.medium++;
N20.medium++ <-->  N115.medium++;
N20.medium++ <-->  N119.medium++;
N21.medium++ <-->  N44.medium++;
N21.medium++ <-->  N94.medium++;
N21.medium++ <-->  N115.medium++;
N21.medium++ <-->  N119.medium++;
N22.medium++ <-->  N36.medium++;
N22.medium++ <-->  N72.medium++;
N23.medium++ <-->  N45.medium++;
N23.medium++ <-->  N81.medium++;
N24.medium++ <-->  N30.medium++;
N24.medium++ <-->  N72.medium++;
N25.medium++ <-->  N50.medium++;
N25.medium++ <-->  N90.medium++;
N25.medium++ <-->  N101.medium++;
N26.medium++ <-->  N84.medium++;
N26.medium++ <-->  N92.medium++;
N27.medium++ <-->  N32.medium++;
N27.medium++ <-->  N51.medium++;
N27.medium++ <-->  N57.medium++;
N27.medium++ <-->  N85.medium++;
N28.medium++ <-->  N43.medium++;
N28.medium++ <-->  N57.medium++;
N28.medium++ <-->  N79.medium++;
N28.medium++ <-->  N106.medium++;
N29.medium++ <-->  N52.medium++;
N29.medium++ <-->  N59.medium++;
N29.medium++ <-->  N97.medium++;
N30.medium++ <-->  N59.medium++;
N30.medium++ <-->  N87.medium++;
N30.medium++ <-->  N97.medium++;
N30.medium++ <-->  N117.medium++;
N31.medium++ <-->  N67.medium++;
N31.medium++ <-->  N88.medium++;
N31.medium++ <-->  N96.medium++;
N31.medium++ <-->  N103.medium++;
N32.medium++ <-->  N60.medium++;
N32.medium++ <-->  N65.medium++;
N32.medium++ <-->  N84.medium++;
N33.medium++ <-->  N49.medium++;
N33.medium++ <-->  N90.medium++;
N33.medium++ <-->  N91.medium++;
N33.medium++ <-->  N111.medium++;
N34.medium++ <-->  N71.medium++;
N34.medium++ <-->  N116.medium++;
N35.medium++ <-->  N42.medium++;
N35.medium++ <-->  N58.medium++;
N35.medium++ <-->  N63.medium++;
N36.medium++ <-->  N75.medium++;
N36.medium++ <-->  N104.medium++;
N36.medium++ <-->  N112.medium++;
N37.medium++ <-->  N64.medium++;
N37.medium++ <-->  N104.medium++;
N37.medium++ <-->  N110.medium++;
N38.medium++ <-->  N44.medium++;
N38.medium++ <-->  N80.medium++;
N38.medium++ <-->  N94.medium++;
N39.medium++ <-->  N81.medium++;
N39.medium++ <-->  N92.medium++;
N39.medium++ <-->  N97.medium++;
N40.medium++ <-->  N63.medium++;
N40.medium++ <-->  N66.medium++;
N40.medium++ <-->  N93.medium++;
N41.medium++ <-->  N94.medium++;
N41.medium++ <-->  N98.medium++;
N42.medium++ <-->  N76.medium++;
N42.medium++ <-->  N88.medium++;
N42.medium++ <-->  N96.medium++;
N43.medium++ <-->  N76.medium++;
N43.medium++ <-->  N92.medium++;
N43.medium++ <-->  N97.medium++;
N44.medium++ <-->  N68.medium++;
N44.medium++ <-->  N98.medium++;
N44.medium++ <-->  N119.medium++;
N45.medium++ <-->  N46.medium++;
N45.medium++ <-->  N82.medium++;
N45.medium++ <-->  N112.medium++;
N46.medium++ <-->  N86.medium++;
N46.medium++ <-->  N105.medium++;
N47.medium++ <-->  N99.medium++;
N47.medium++ <-->  N104.medium++;
N48.medium++ <-->  N78.medium++;
N48.medium++ <-->  N106.medium++;
N49.medium++ <-->  N87.medium++;
N50.medium++ <-->  N52.medium++;
N50.medium++ <-->  N68.medium++;
N51.medium++ <-->  N69.medium++;
N51.medium++ <-->  N73.medium++;
N51.medium++ <-->  N102.medium++;
N52.medium++ <-->  N58.medium++;
N53.medium++ <-->  N75.medium++;
N53.medium++ <-->  N112.medium++;
N55.medium++ <-->  N56.medium++;
N55.medium++ <-->  N61.medium++;
N56.medium++ <-->  N79.medium++;
N56.medium++ <-->  N90.medium++;
N56.medium++ <-->  N101.medium++;
N56.medium++ <-->  N106.medium++;
N57.medium++ <-->  N62.medium++;
N57.medium++ <-->  N74.medium++;
N57.medium++ <-->  N108.medium++;
N57.medium++ <-->  N114.medium++;
N58.medium++ <-->  N76.medium++;
N58.medium++ <-->  N87.medium++;
N59.medium++ <-->  N64.medium++;
N59.medium++ <-->  N112.medium++;
N60.medium++ <-->  N111.medium++;
N61.medium++ <-->  N100.medium++;
N61.medium++ <-->  N113.medium++;
N62.medium++ <-->  N72.medium++;
N62.medium++ <-->  N75.medium++;
N62.medium++ <-->  N114.medium++;
N63.medium++ <-->  N76.medium++;
N63.medium++ <-->  N84.medium++;
N63.medium++ <-->  N88.medium++;
N64.medium++ <-->  N103.medium++;
N64.medium++ <-->  N118.medium++;
N65.medium++ <-->  N98.medium++;
N65.medium++ <-->  N118.medium++;
N66.medium++ <-->  N85.medium++;
N67.medium++ <-->  N75.medium++;
N67.medium++ <-->  N104.medium++;
N68.medium++ <-->  N118.medium++;
N69.medium++ <-->  N116.medium++;
N71.medium++ <-->  N96.medium++;
N72.medium++ <-->  N86.medium++;
N72.medium++ <-->  N99.medium++;
N72.medium++ <-->  N100.medium++;
N72.medium++ <-->  N105.medium++;
N73.medium++ <-->  N91.medium++;
N73.medium++ <-->  N106.medium++;
N75.medium++ <-->  N96.medium++;
N75.medium++ <-->  N111.medium++;
N76.medium++ <-->  N98.medium++;
N79.medium++ <-->  N107.medium++;
N80.medium++ <-->  N82.medium++;
N80.medium++ <-->  N93.medium++;
N80.medium++ <-->  N109.medium++;
N81.medium++ <-->  N95.medium++;
N82.medium++ <-->  N86.medium++;
N83.medium++ <-->  N99.medium++;
N83.medium++ <-->  N105.medium++;
N84.medium++ <-->  N89.medium++;
N85.medium++ <-->  N91.medium++;
N85.medium++ <-->  N103.medium++;
N85.medium++ <-->  N111.medium++;
N85.medium++ <-->  N118.medium++;
N86.medium++ <-->  N108.medium++;
N88.medium++ <-->  N89.medium++;
N89.medium++ <-->  N110.medium++;
N90.medium++ <-->  N108.medium++;
N91.medium++ <-->  N95.medium++;
N91.medium++ <-->  N109.medium++;
N92.medium++ <-->  N102.medium++;
N93.medium++ <-->  N116.medium++;
N95.medium++ <-->  N115.medium++;
N97.medium++ <-->  N101.medium++;
N97.medium++ <-->  N107.medium++;
N101.medium++ <-->  N117.medium++;
N102.medium++ <-->  N107.medium++;
N102.medium++ <-->  N117.medium++;
N103.medium++ <-->  N109.medium++;
N105.medium++ <-->  N116.medium++;
N109.medium++ <-->  N113.medium++;
N111.medium++ <-->  N115.medium++;
N112.medium++ <-->  N117.medium++;

}
