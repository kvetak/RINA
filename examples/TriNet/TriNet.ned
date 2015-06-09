package rina.examples.TriNet;

import ned.DatarateChannel;
import rina.src.CS.HostNAP;
import rina.src.CS.InteriorRouter2Int;
import rina.src.CS.InteriorRouter3Int;


network TriNet
{
    @display("bgb=325,256");
    submodules:
        A: InteriorRouter2Int {
            @display("p=96,118");
        }
        B: InteriorRouter2Int {
            @display("p=170,45");
        }
        C: InteriorRouter2Int {
            @display("p=170,198");
        }
        D: InteriorRouter2Int {
            @display("p=239,118");
        }
    connections allowunconnected:
        A.medium[0] <--> B.medium[0];
        A.medium[1] <--> C.medium[0];
        
        B.medium[1] <--> D.medium[0];
        C.medium[1] <--> D.medium[1];

}
