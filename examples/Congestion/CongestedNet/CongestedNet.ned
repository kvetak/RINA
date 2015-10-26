// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

package rina.examples.Congestion.CongestedNet;
import ned.DatarateChannel;
import rina.src.CS.Host1AP;
import rina.src.CS.HostNAP;
import rina.src.CS.InteriorRouterNInt;
import rina.src.DAF.AE.AEConstant.AEConstantListener;
import rina.src.DAF.AE.AEConstant.AEConstantServer;


network CongestedNet
{
    @display("bgb=1030,707");
    types:
        channel CH1 extends DatarateChannel
        {
            datarate = 1*9*300Mbps;
        }
        channel CH2 extends DatarateChannel
        {
            datarate = 2*9*300Mbps;
        }
        channel CH3 extends DatarateChannel
        {
            datarate = 3*9*300Mbps;
        }
        channel CH4 extends DatarateChannel
        {
            datarate = 4*9*300Mbps;
        }
        channel CH5 extends DatarateChannel
        {
            datarate = 5*9*300Mbps;
        }
        channel CH6 extends DatarateChannel
        {
            datarate = 6*9*300Mbps;
        }
        channel CHS extends DatarateChannel
        {
            datarate = 20*9*300Mbps;
        }


    submodules:
        router_1: InteriorRouterNInt {
            @display("p=176,174");
        }
        router_2: InteriorRouterNInt {
            @display("p=291,317");
        }
        router_3: InteriorRouterNInt {
            @display("p=202,430");
        }
        router_4: InteriorRouterNInt {
            @display("p=591,324");
        }
        router_5: InteriorRouterNInt {
            @display("p=498,378");
        }
        router_6: InteriorRouterNInt {
            @display("p=723,271");
        }
        router_7: InteriorRouterNInt {
            @display("p=846,232");
        }
        router_8: InteriorRouterNInt {
            @display("p=668,456");
        }
        router_9: InteriorRouterNInt {
            @display("p=819,346");
        }
        router_a: InteriorRouterNInt {
            @display("p=509,558");
        }
        serverA_1: HostNAP {
            @display("p=108,89");
        }
        serverA_2: HostNAP {
            @display("p=668,540");
        }
        serverA_3: HostNAP {
            @display("p=855,158");
        }
        clientB_1: HostNAP {
            @display("p=380,293");
        }
        clientB_2: HostNAP {
            @display("p=173,501");
        }
        clientB_3: HostNAP {
            @display("p=588,254");
        }
        clientB_4: HostNAP {
            @display("p=421,438");
        }
        clientB_5: HostNAP {
            @display("p=723,180");
        }
        clientB_6: HostNAP {
            @display("p=438,626");
        }
        clientB_7: HostNAP {
            @display("p=846,430");
        }
        
        listener: AEConstantListener {
            @display("p=377,73");
        }
    connections:
        router_1.medium++ <--> CH3 <--> router_2.medium++;
        router_1.medium++ <--> CH3 <--> router_3.medium++;
        router_1.medium++ <--> CH5 <--> router_4.medium++;

        router_2.medium++ <--> CH1 <--> router_3.medium++;
        router_2.medium++ <--> CH3 <--> router_5.medium++;

        router_3.medium++ <--> CH4 <--> router_a.medium++;

        router_4.medium++ <--> CH4 <--> router_5.medium++;
        router_4.medium++ <--> CH6 <--> router_6.medium++;
        router_4.medium++ <--> CH4 <--> router_8.medium++;

        router_5.medium++ <--> CH1 <--> router_a.medium++;

        router_6.medium++ <--> CH5 <--> router_7.medium++;
        router_6.medium++ <--> CH2 <--> router_9.medium++;

        router_7.medium++ <--> CH3 <--> router_9.medium++;

        router_8.medium++ <--> CH4 <--> router_9.medium++;
        router_8.medium++ <--> CH5 <--> router_a.medium++;

        serverA_1.medium <--> CHS <--> router_1.medium++;
        serverA_2.medium <--> CHS <--> router_8.medium++;
        clientB_2.medium <--> CHS <--> router_3.medium++;
        clientB_1.medium <--> CHS <--> router_2.medium++;
        clientB_6.medium <--> CHS <--> router_a.medium++;
        clientB_4.medium <--> CHS <--> router_5.medium++;
        clientB_3.medium <--> CHS <--> router_4.medium++;
        clientB_5.medium <--> CHS <--> router_6.medium++;
        serverA_3.medium <--> CHS <--> router_7.medium++;
        clientB_7.medium <--> CHS <--> router_9.medium++;
}
