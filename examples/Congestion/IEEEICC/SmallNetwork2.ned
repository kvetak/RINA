//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package rina.examples.Congestion.IEEEICC;

import ned.DatarateChannel;
import rina.src.CS.*;


network SmallNetworkPar
{
    @display("bgb=586,372");
    double ldelay @unit(s) = default(0.1s);
    double lber = default(0.0);
    types:
        channel SlowP extends DatarateChannel
        {
            parameters:
                datarate = 2Mbps;
                per = 0;
        }
        channel NormalP extends DatarateChannel
        {
            parameters:
                datarate = 10Mbps;
                per = 0;
        }
        channel HighSpeedP extends DatarateChannel
        {
            parameters:
                datarate = 20Mbps;
                per = 0;
        }
    submodules:
        host1: Host1AP {
            @display("p=92,83");
        }
        host2: Host1AP {
            @display("p=92,252");
        }
        //        host3: Host1AP {
        //            @display("p=275,83");
        //        }
        host4: Host1AP {
            @display("p=473,83");
        }
        host5: Host1AP {
            @display("p=473,252");
        }
        router1: InteriorRouter3Int {
            @display("p=166,165");
        }
        router2: InteriorRouter2Int {
            @display("p=275,165");
        }
        router3: InteriorRouter3Int {
            @display("p=388,165");
        }

    connections:
//        router1.medium[0] <--> host1.medium;
//        router1.medium[1] <--> host2.medium;
//        router1.medium[2] <--> router2.medium[0];
//        router2.medium[1] <--> router3.medium[0];
////        router2.medium[2] <--> host3.medium;
//        router3.medium[1] <--> host4.medium;
//        router3.medium[2] <--> host5.medium;

        router1.medium[0] <--> NormalP {  delay = ldelay; ber = 0; } <--> host1.medium;
        router1.medium[1] <--> NormalP {  delay = ldelay; ber = 0; } <--> host2.medium;
        router1.medium[2] <--> HighSpeedP {  delay = ldelay; ber = 0; } <--> router2.medium[0];
        router2.medium[1] <--> HighSpeedP {  delay = ldelay; ber = 0; } <--> router3.medium[0];
        //        router2.medium[2] <--> host3.medium;
        router3.medium[1] <--> NormalP {  delay = ldelay; ber = 0; } <--> host4.medium;
        router3.medium[2] <--> SlowP {  delay = ldelay; ber = lber; } <--> host5.medium;
}

network SmallNetworkAgg
{
    @display("bgb=586,372");
    double ldelay @unit(s) = default(0.1s);
    double lber = default(0.0);
    types:
        channel SlowP extends DatarateChannel
        {
            parameters:
                datarate = 3Mbps;
                per = 0;
        }
        channel NormalP extends DatarateChannel
        {
            parameters:
                datarate = 10Mbps;
                per = 0;
        }
        channel HighSpeedP extends DatarateChannel
        {
            parameters:
                datarate = 20Mbps;
                per = 0;
        }
    submodules:
        host11: Host1AP {
            @display("p=115,80");
        }
        host12: Host1AP {
            @display("p=115,143");
        }
        host13: Host1AP {
            @display("p=115,204");
        }
        host14: Host1AP {
            @display("p=115,265");
        }
        host15: Host1AP {
            @display("p=115,325");
        }
        host21: Host1AP {
            @display("p=461,80");
        }
        host22: Host1AP {
            @display("p=461,143");
        }
        host23: Host1AP {
            @display("p=461,204");
        }
        host24: Host1AP {
            @display("p=461,265");
        }
        host25: Host1AP {
            @display("p=461,325");
        }
        router1: InteriorRouterNInt {
            @display("p=234,165");
        }
        router2: InteriorRouterNInt {
            @display("p=350,165");
        }

    connections:
        router1.medium++ <--> SlowP {  delay = ldelay; ber = 0; } <--> host11.medium;
        router1.medium++ <--> SlowP {  delay = ldelay; ber = 0; } <--> host12.medium;
        router1.medium++ <--> SlowP {  delay = ldelay; ber = 0; } <--> host13.medium;
        router1.medium++ <--> SlowP {  delay = ldelay; ber = 0; } <--> host14.medium;
        router1.medium++ <--> SlowP {  delay = ldelay; ber = 0; } <--> host15.medium;
        router1.medium++ <--> NormalP {  delay = ldelay; ber = 0; } <--> router2.medium++;
        router2.medium++ <--> SlowP {  delay = ldelay; ber = 0; } <--> host21.medium;
        router2.medium++ <--> SlowP {  delay = ldelay; ber = 0; } <--> host22.medium;
        router2.medium++ <--> SlowP {  delay = ldelay; ber = 0; } <--> host23.medium;
        router2.medium++ <--> SlowP {  delay = ldelay; ber = 0; } <--> host24.medium;
        router2.medium++ <--> SlowP {  delay = ldelay; ber = 0; } <--> host25.medium;
}

network SmallNetwork2
{
    @display("bgb=586,372");
    submodules:
        host1: Host1AP {
            @display("p=92,83");
        }
        host2: Host1AP {
            @display("p=92,252");
        }
        //        host3: Host1AP {
        //            @display("p=275,83");
        //        }
        host4: Host1AP {
            @display("p=473,83");
        }
        host5: Host1AP {
            @display("p=473,252");
        }
        router1: InteriorRouter3Int {
            @display("p=166,165");
        }
        router2: InteriorRouter2Int {
            @display("p=275,165");
        }
        router3: InteriorRouter3Int {
            @display("p=388,165");
        }

    connections:
//        router1.medium[0] <--> host1.medium;
//        router1.medium[1] <--> host2.medium;
//        router1.medium[2] <--> router2.medium[0];
//        router2.medium[1] <--> router3.medium[0];
////        router2.medium[2] <--> host3.medium;
//        router3.medium[1] <--> host4.medium;
//        router3.medium[2] <--> host5.medium;

        router1.medium[0] <--> NormalPath <--> host1.medium;
        router1.medium[1] <--> NormalPath <--> host2.medium;
        router1.medium[2] <--> HighSpeedPath <--> router2.medium[0];
        router2.medium[1] <--> HighSpeedPath <--> router3.medium[0];
        //        router2.medium[2] <--> host3.medium;
        router3.medium[1] <--> NormalPath <--> host4.medium;
        router3.medium[2] <--> SlowPath <--> host5.medium;
}

network SmallNetwork3
{
    @display("bgb=586,372");
    submodules:
        host1: Host1AP {
            @display("p=92,83");
        }
        host2: Host1AP {
            @display("p=92,252");
        }
        //        host3: Host1AP {
        //            @display("p=275,83");
        //        }
        host4: Host1AP {
            @display("p=473,83");
        }
        host5: Host1AP {
            @display("p=473,252");
        }
        router1: InteriorRouter3Int {
            @display("p=166,165");
        }
        router2: InteriorRouter2Int {
            @display("p=275,165");
        }
        router3: InteriorRouter3Int {
            @display("p=388,165");
        }

    connections:
//        router1.medium[0] <--> host1.medium;
//        router1.medium[1] <--> host2.medium;
//        router1.medium[2] <--> router2.medium[0];
//        router2.medium[1] <--> router3.medium[0];
////        router2.medium[2] <--> host3.medium;
//        router3.medium[1] <--> host4.medium;
//        router3.medium[2] <--> host5.medium;

        router1.medium[0] <--> NormalPath <--> host1.medium;
        router1.medium[1] <--> NormalPath <--> host2.medium;
        router1.medium[2] <--> HighSpeedPath <--> router2.medium[0];
        router2.medium[1] <--> SlowPath <--> router3.medium[0];
        //        router2.medium[2] <--> host3.medium;
        router3.medium[1] <--> NormalPath <--> host4.medium;
        router3.medium[2] <--> NormalPath <--> host5.medium;
}

network SmallNetwork4
{
    @display("bgb=586,372");
    submodules:
        host1: Host1AP {
            @display("p=92,83");
        }
        host2: Host1AP {
            @display("p=92,252");
        }
        //        host3: Host1AP {
        //            @display("p=275,83");
        //        }
        host4: Host1AP {
            @display("p=473,83");
        }
        host5: Host1AP {
            @display("p=473,252");
        }
        router1: InteriorRouter3Int {
            @display("p=166,165");
        }
        router2: InteriorRouter2Int {
            @display("p=275,165");
        }
        router3: InteriorRouter3Int {
            @display("p=388,165");
        }

    connections:
//        router1.medium[0] <--> host1.medium;
//        router1.medium[1] <--> host2.medium;
//        router1.medium[2] <--> router2.medium[0];
//        router2.medium[1] <--> router3.medium[0];
////        router2.medium[2] <--> host3.medium;
//        router3.medium[1] <--> host4.medium;
//        router3.medium[2] <--> host5.medium;

        router1.medium[0] <--> NormalPath <--> host1.medium;
        router1.medium[1] <--> NormalPath <--> host2.medium;
        router1.medium[2] <--> SlowPath <--> router2.medium[0];
        router2.medium[1] <--> HighSpeedPath <--> router3.medium[0];
        //        router2.medium[2] <--> host3.medium;
        router3.medium[1] <--> NormalPath <--> host4.medium;
        router3.medium[2] <--> NormalPath <--> host5.medium;
}

channel NormalPath extends DatarateChannel
{
    parameters:
        datarate = 10Mbps;
        delay = 25ms; // 10m
        per = 0;
        ber = 0;
}

channel HighSpeedPath extends DatarateChannel
{
    parameters:
        datarate = 20Mbps;
        delay = 25ms; // 10m
        per = 0;
        ber = 0;
}

channel SlowPath extends DatarateChannel
{
    parameters:
        datarate = 2Mbps;
        delay = 25ms; // 10m
        per = 0;
        ber = 0;
}

channel ErroneousPath extends DatarateChannel
{
    parameters:
        datarate = 1Mbps;
        delay = 1ms; // 10m
        per = 0.00;
        ber = 0.000001;
}
