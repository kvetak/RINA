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

package rina.playground.UPC.Scheduling.TreeCongestion;
import ned.DatarateChannel;
import rina.src.CS.Host1AP;
import rina.src.CS.HostNAP;
import rina.src.CS.InteriorRouterNInt;

network TreeCongestion {
	submodules:
		router_1 : InteriorRouterNInt;
		router_2 : InteriorRouterNInt;
		hostS_0 : HostNAP;
		hostS_1 : HostNAP;
		hostS_2 : HostNAP;
		hostS_3 : HostNAP;
		hostR_0_0 : Host1AP;
		hostR_0_1 : Host1AP;
		hostR_0_2 : Host1AP;
		hostR_0_3 : Host1AP;
		hostR_1_0 : Host1AP;
		hostR_1_1 : Host1AP;
		hostR_1_2 : Host1AP;
		hostR_1_3 : Host1AP;
		hostR_2_0 : Host1AP;
		hostR_2_1 : Host1AP;
		hostR_2_2 : Host1AP;
		hostR_2_3 : Host1AP;
		hostR_3_0 : Host1AP;
		hostR_3_1 : Host1AP;
		hostR_3_2 : Host1AP;
		hostR_3_3 : Host1AP;
	connections:
		router_1.medium++ <--> DatarateChannel {  datarate = 1600Mbps; } <--> router_2.medium++;
		hostS_0.medium <--> DatarateChannel {  datarate = 300Mbps; } <--> router_1.medium++;
		hostS_1.medium <--> DatarateChannel {  datarate = 300Mbps; } <--> router_1.medium++;
		hostS_2.medium <--> DatarateChannel {  datarate = 300Mbps; } <--> router_1.medium++;
		hostS_3.medium <--> DatarateChannel {  datarate = 300Mbps; } <--> router_1.medium++;
		hostR_0_0.medium <--> router_2.medium++;
		hostR_0_1.medium <--> router_2.medium++;
		hostR_0_2.medium <--> router_2.medium++;
		hostR_0_3.medium <--> router_2.medium++;
		hostR_1_0.medium <--> router_2.medium++;
		hostR_1_1.medium <--> router_2.medium++;
		hostR_1_2.medium <--> router_2.medium++;
		hostR_1_3.medium <--> router_2.medium++;
		hostR_2_0.medium <--> router_2.medium++;
		hostR_2_1.medium <--> router_2.medium++;
		hostR_2_2.medium <--> router_2.medium++;
		hostR_2_3.medium <--> router_2.medium++;
		hostR_3_0.medium <--> router_2.medium++;
		hostR_3_1.medium <--> router_2.medium++;
		hostR_3_2.medium <--> router_2.medium++;
		hostR_3_3.medium <--> router_2.medium++;
}
