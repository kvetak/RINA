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

package rina.examples.Routing.DistributedCloudsLS;

import rina.src.CS.*;
import rina.src.DAF.IRM.ConnectionTable;
import rina.src.DIF.EFCP.DTCP.*;
import rina.src.CS.VIFIBNodeGL1;
import rina.src.CS.VIFIBNodeGL2;
import rina.src.CS.VIFIBNode;

network DistributedCloudsLS
{
    @display("bgb=1299,929");

    submodules:

        VIFIBN1: VIFIBNode {
            @display("p=475,216");
        }
        VIFIBN2: VIFIBNode {
            @display("p=374,216");
        }
        VIFIBN3: VIFIBNode {
            @display("p=401,144");
        }
        VIFIBN4: VIFIBNode {
            @display("p=312,172");
        }
        VIFIBN5: VIFIBNode {
            @display("p=215,229");
        }
        VIFIBN6: VIFIBNode {
            @display("p=274,241");
        }
        VIFIBN7: VIFIBNode {
            @display("p=173,298");
        }
        VIFIBN8: VIFIBNode {
            @display("p=258,120");
        }
        VIFIBN9: VIFIBNode {
            @display("p=312,98");
        }
        VIFIBN10: VIFIBNode {
            @display("p=173,157");
        }
        VIFIBN11: VIFIBNode {
            @display("p=297,314");
        }
        VIFIBN12: VIFIBNode {
            @display("p=446,30");
        }
        VIFIBN13: VIFIBNode {
            @display("p=337,24");
        }
        VIFIBN14: VIFIBNode {
            @display("p=475,320");
        }
        VIFIBN15: VIFIBNode {
            @display("p=127,226");
        }
        VIFIBN16: VIFIBNode {
            @display("p=543,83");
        }
        VIFIBN17: VIFIBNode {
            @display("p=417,277");
        }
        VIFIBN18: VIFIBNode {
            @display("p=66,51");
        }
        VIFIBN19: VIFIBNode {
            @display("p=73,213");
        }
        VIFIBN20: VIFIBNode {
            @display("p=159,44");
        }
        VIFIBN21: VIFIBNode {
            @display("p=37,144");
        }
        VIFIBN22: VIFIBNode {
            @display("p=239,335");
        }
        VIFIBN23: VIFIBNode {
            @display("p=109,335");
        }
        VIFIBN24: VIFIBNode {
            @display("p=417,376");
        }
        VIFIBN25: VIFIBNode {
            @display("p=357,348");
        }
        VIFIBN26: VIFIBNode {
            @display("p=268,51");
        }
        VIFIBN27: VIFIBNode {
            @display("p=452,121");
        }
        VIFIBN28: VIFIBNode {
            @display("p=509,157");
        }
        VIFIBN29: VIFIBNode {
            @display("p=29,279");
        }


        VIFIBN30: VIFIBNode {
            @display("p=886,287");
        }
        VIFIBN31: VIFIBNode {
            @display("p=867,216");
        }
        VIFIBN32: VIFIBNode {
            @display("p=922,182");
        }
        VIFIBN33: VIFIBNode {
            @display("p=972,121");
        }
        VIFIBN34: VIFIBNode {
            @display("p=965,47");
        }
        VIFIBN35: VIFIBNode {
            @display("p=1040,47");
        }
        VIFIBN36: VIFIBNode {
            @display("p=867,30");
        }
        VIFIBN37: VIFIBNode {
            @display("p=1124,121");
        }
        VIFIBN38: VIFIBNode {
            @display("p=1136,24");
        }
        VIFIBN39: VIFIBNode {
            @display("p=1047,121");
        }
        VIFIBN40: VIFIBNode {
            @display("p=1196,107");
        }
        VIFIBN41: VIFIBNode {
            @display("p=874,130");
        }
        VIFIBN42: VIFIBNode {
            @display("p=1165,329");
        }
        VIFIBN43: VIFIBNode {
            @display("p=1258,298");
        }
        VIFIBN44: VIFIBNode {
            @display("p=972,287");
        }
        VIFIBN45: VIFIBNode {
            @display("p=809,329");
        }
        VIFIBN46: VIFIBNode {
            @display("p=1267,194");
        }
        VIFIBN47: VIFIBNode {
            @display("p=1001,213");
        }
        VIFIBN48: VIFIBNode {
            @display("p=1001,376");
        }
        VIFIBN49: VIFIBNode {
            @display("p=1100,226");
        }
        VIFIBN50: VIFIBNode {
            @display("p=1100,314");
        }
        VIFIBN51: VIFIBNode {
            @display("p=912,81");
        }
        VIFIBN52: VIFIBNode {
            @display("p=825,88");
        }
        VIFIBN53: VIFIBNode {
            @display("p=1258,84");
        }
        VIFIBN54: VIFIBNode {
            @display("p=1194,242");
        }
        VIFIBN55: VIFIBNode {
            @display("p=1030,298");
        }
        VIFIBN56: VIFIBNode {
            @display("p=775,157");
        }
        VIFIBN57: VIFIBNode {
            @display("p=1150,182");
        }
        VIFIBN58: VIFIBNode {
            @display("p=941,357");
        }
        VIFIBN59: VIFIBNode {
            @display("p=843,609");
        }
        VIFIBN60: VIFIBNode {
            @display("p=893,546");
        }
        VIFIBN61: VIFIBNode {
            @display("p=825,696");
        }
        VIFIBN62: VIFIBNode {
            @display("p=893,696");
        }
        VIFIBN63: VIFIBNode {
            @display("p=815,768");
        }
        VIFIBN64: VIFIBNode {
            @display("p=746,780");
        }
        VIFIBN65: VIFIBNode {
            @display("p=872,798");
        }
        VIFIBN66: VIFIBNode {
            @display("p=1076,646");
        }
        VIFIBN67: VIFIBNode {
            @display("p=1150,523");
        }
        VIFIBN68: VIFIBNode {
            @display("p=1052,853");
        }
        VIFIBN69: VIFIBNode {
            @display("p=874,870");
        }
        VIFIBN70: VIFIBNode {
            @display("p=781,618");
        }
        VIFIBN71: VIFIBNode {
            @display("p=1223,798");
        }
        VIFIBN72: VIFIBNode {
            @display("p=1069,546");
        }
        VIFIBN73: VIFIBNode {
            @display("p=1136,597");
        }
        VIFIBN74: VIFIBNode {
            @display("p=912,618");
        }
        VIFIBN75: VIFIBNode {
            @display("p=980,533");
        }
        VIFIBN76: VIFIBNode {
            @display("p=1088,780");
        }
        VIFIBN77: VIFIBNode {
            @display("p=1151,680");
        }
        VIFIBN78: VIFIBNode {
            @display("p=1151,833");
        }
        VIFIBN79: VIFIBNode {
            @display("p=1215,665");
        }
        VIFIBN80: VIFIBNode {
            @display("p=930,749");
        }
        VIFIBN81: VIFIBNode {
            @display("p=941,853");
        }
        VIFIBN82: VIFIBNode {
            @display("p=1018,615");
        }
        VIFIBN83: VIFIBNode {
            @display("p=1009,722");
        }
        VIFIBN84: VIFIBNode {
            @display("p=1144,749");
        }
        VIFIBN85: VIFIBNode {
            @display("p=746,703");
        }
        VIFIBN86: VIFIBNode {
            @display("p=1244,733");
        }
        VIFIBN87: VIFIBNode {
            @display("p=1206,560");
        }
        VIFIBN88: VIFIBNode {
            @display("p=417,514");
        }
        VIFIBN89: VIFIBNode {
            @display("p=434,566");
        }
        VIFIBN90: VIFIBNode {
            @display("p=437,652");
        }
        VIFIBN91: VIFIBNode {
            @display("p=317,689");
        }
        VIFIBN92: VIFIBNode {
            @display("p=245,680");
        }
        VIFIBN93: VIFIBNode {
            @display("p=109,715");
        }
        VIFIBN94: VIFIBNode {
            @display("p=177,733");
        }
        VIFIBN95: VIFIBNode {
            @display("p=215,798");
        }
        VIFIBN96: VIFIBNode {
            @display("p=73,844");
        }
        VIFIBN97: VIFIBNode {
            @display("p=303,749");
        }
        VIFIBN98: VIFIBNode {
            @display("p=81,646");
        }
        VIFIBN99: VIFIBNode {
            @display("p=538,733");
        }
        VIFIBN100: VIFIBNode {
            @display("p=215,496");
        }
        VIFIBN101: VIFIBNode {
            @display("p=268,551");
        }
        VIFIBN102: VIFIBNode {
            @display("p=374,812");
        }
        VIFIBN103: VIFIBNode {
            @display("p=344,546");
        }
        VIFIBN104: VIFIBNode {
            @display("p=297,618");
        }
        VIFIBN105: VIFIBNode {
            @display("p=274,833");
        }
        VIFIBN106: VIFIBNode {
            @display("p=366,870");
        }
        VIFIBN107: VIFIBNode {
            @display("p=495,812");
        }
        VIFIBN108: VIFIBNode {
            @display("p=446,870");
        }
        VIFIBN109: VIFIBNode {
            @display("p=29,775");
        }
        VIFIBN110: VIFIBNode {
            @display("p=179,858");
        }
        VIFIBN111: VIFIBNode {
            @display("p=193,634");
        }
        VIFIBN112: VIFIBNode {
            @display("p=102,570");
        }
        VIFIBN113: VIFIBNode {
            @display("p=386,749");
        }
        VIFIBN114: VIFIBNode {
            @display("p=525,597");
        }
        VIFIBN115: VIFIBNode {
            @display("p=188,570");
        }
        VIFIBN116: VIFIBNode {
            @display("p=446,740");
        }

        VIFIBNGL1: VIFIBNodeGL1 {
            @display("p=557,292");
        }
        VIFIBNGL2: VIFIBNodeGL2 {
            @display("p=781,264");
        }
        VIFIBNGL3: VIFIBNodeGL2 {
            @display("p=746,546");
        }
        VIFIBNGL4: VIFIBNodeGL1 {
            @display("p=495,485");
        }

    connections:
		//Group 1 Connections
        VIFIBN2.medium[0] <--> VIFIBN3.medium[0];
        VIFIBN3.medium[1] <--> VIFIBN4.medium[0];
        VIFIBN4.medium[1] <--> VIFIBN5.medium[0];
        VIFIBN5.medium[1] <--> VIFIBN7.medium[0];
        VIFIBN8.medium[0] <--> VIFIBN9.medium[0];
        VIFIBN8.medium[1] <--> VIFIBN10.medium[0];
        VIFIBN10.medium[1] <--> VIFIBN18.medium[0];
        VIFIBN15.medium[1] <--> VIFIBN18.medium[1];
        VIFIBN19.medium[0] <--> VIFIBN21.medium[0];
        VIFIBN7.medium[1] <--> VIFIBN22.medium[0];
        VIFIBN29.medium[0] <--> VIFIBN19.medium[1];
        VIFIBN23.medium[0] <--> VIFIBN22.medium[1];
        VIFIBN25.medium[0] <--> VIFIBN24.medium[0];
        VIFIBN25.medium[1] <--> VIFIBN11.medium[0];
        VIFIBN6.medium[0] <--> VIFIBN11.medium[1];
        VIFIBN1.medium[0] <--> VIFIBN17.medium[1];
        VIFIBN14.medium[1] <--> VIFIBN24.medium[1];
        VIFIBN12.medium[0] <--> VIFIBN13.medium[0];
        VIFIBN27.medium[0] <--> VIFIBN12.medium[1];
        VIFIBN26.medium[0] <--> VIFIBN13.medium[1];
        VIFIBN20.medium[0] <--> VIFIBN26.medium[1];
        VIFIBN16.medium[0] <--> VIFIBN27.medium[1];
        VIFIBN20.medium[1] <--> VIFIBN21.medium[1];

        VIFIBN1.medium[1] <--> VIFIBNGL1.medium[0];
        VIFIBN2.medium[1] <--> VIFIBNGL1.medium[1];



		//Group 2 Connections
        VIFIBNGL2.medium[0] <--> VIFIBN30.medium[0];
        VIFIBNGL2.medium[1] <--> VIFIBN31.medium[0];


        VIFIBN31.medium[1] <--> VIFIBN32.medium[0];
        VIFIBN32.medium[1] <--> VIFIBN33.medium[0];
        VIFIBN33.medium[1] <--> VIFIBN34.medium[0];
        VIFIBN34.medium[1] <--> VIFIBN35.medium[0];
        VIFIBN37.medium[0] <--> VIFIBN38.medium[0];
        VIFIBN37.medium[1] <--> VIFIBN39.medium[0];
        VIFIBN39.medium[1] <--> VIFIBN47.medium[0];
        VIFIBN44.medium[0] <--> VIFIBN48.medium[0];
        VIFIBN36.medium[0] <--> VIFIBN51.medium[0];
        VIFIBN58.medium[0] <--> VIFIBN48.medium[1];
        VIFIBN52.medium[0] <--> VIFIBN56.medium[0];
        VIFIBN52.medium[1] <--> VIFIBN51.medium[1];
        VIFIBN54.medium[0] <--> VIFIBN53.medium[0];
        VIFIBN54.medium[1] <--> VIFIBN40.medium[0];
        VIFIBN35.medium[1] <--> VIFIBN40.medium[1];

        VIFIBN46.medium[0] <--> VIFIBN43.medium[0];
        VIFIBN53.medium[1] <--> VIFIBN46.medium[1];
        VIFIBN56.medium[1] <--> VIFIBN41.medium[1];
        VIFIBN42.medium[0] <--> VIFIBN57.medium[0];
        VIFIBN50.medium[0] <--> VIFIBN42.medium[1];
        VIFIBN49.medium[1] <--> VIFIBN55.medium[1];
        VIFIBN44.medium[1] <--> VIFIBN30.medium[1];
        VIFIBN59.medium[0] <--> VIFIBNGL3.medium[0];
        VIFIBN60.medium[0] <--> VIFIBNGL3.medium[1];
        VIFIBN61.medium[0] <--> VIFIBN62.medium[0];
        VIFIBN63.medium[0] <--> VIFIBN65.medium[0];
        VIFIBN63.medium[1] <--> VIFIBN64.medium[0];
        VIFIBN66.medium[1] <--> VIFIBN62.medium[1];
        VIFIBN114.medium[0] <--> VIFIBN68.medium[0];
        VIFIBN68.medium[1] <--> VIFIBN76.medium[0];
        VIFIBN73.medium[0] <--> VIFIBN77.medium[0];
        VIFIBN73.medium[1] <--> VIFIBN76.medium[1];
        VIFIBN65.medium[1] <--> VIFIBN80.medium[0];
        VIFIBN81.medium[0] <--> VIFIBN77.medium[1];
        VIFIBN81.medium[1] <--> VIFIBN80.medium[1];
        VIFIBN83.medium[0] <--> VIFIBN82.medium[0];
        VIFIBN83.medium[1] <--> VIFIBN69.medium[0];
        VIFIBN64.medium[1] <--> VIFIBN69.medium[1];
        VIFIBN60.medium[1] <--> VIFIBN75.medium[0];
        VIFIBN82.medium[1] <--> VIFIBN75.medium[1];
        VIFIBN70.medium[0] <--> VIFIBN61.medium[1];
        VIFIBN85.medium[1] <--> VIFIBN70.medium[1];
        VIFIBN71.medium[0] <--> VIFIBN86.medium[0];
        VIFIBN84.medium[1] <--> VIFIBN71.medium[1];
        VIFIBN78.medium[0] <--> VIFIBN86.medium[1];
        VIFIBN74.medium[0] <--> VIFIBN59.medium[1];
        VIFIBN78.medium[1] <--> VIFIBN79.medium[1];



		//Group 4 Connections
        VIFIBNGL4.medium[0] <--> VIFIBN88.medium[0];
        VIFIBNGL4.medium[1] <--> VIFIBN89.medium[0];
        VIFIBN89.medium[1] <--> VIFIBN90.medium[0];
        VIFIBN90.medium[1] <--> VIFIBN91.medium[0];
        VIFIBN91.medium[1] <--> VIFIBN92.medium[0];
        VIFIBN92.medium[1] <--> VIFIBN93.medium[0];
        VIFIBN95.medium[0] <--> VIFIBN96.medium[0];
        VIFIBN97.medium[0] <--> VIFIBN105.medium[0];
        VIFIBN102.medium[1] <--> VIFIBN105.medium[1];
        VIFIBN106.medium[0] <--> VIFIBN108.medium[0];
        VIFIBN107.medium[0] <--> VIFIBN97.medium[1];
        VIFIBN113.medium[0] <--> VIFIBN95.medium[1];
        VIFIBN94.medium[1] <--> VIFIBN109.medium[0];
        VIFIBN110.medium[0] <--> VIFIBN106.medium[1];
        VIFIBN110.medium[1] <--> VIFIBN109.medium[1];
        VIFIBN112.medium[0] <--> VIFIBN111.medium[0];
        VIFIBN112.medium[1] <--> VIFIBN98.medium[0];
        VIFIBN93.medium[1] <--> VIFIBN98.medium[1];
        VIFIBN104.medium[0] <--> VIFIBN101.medium[0];
        VIFIBN111.medium[1] <--> VIFIBN104.medium[1];
        VIFIBN100.medium[0] <--> VIFIBN115.medium[0];
        VIFIBN103.medium[0] <--> VIFIBN88.medium[1];
        VIFIBN107.medium[1] <--> VIFIBN108.medium[1];


        //Connections between the groups
        VIFIBNGL2.medium[2] <--> VIFIBNGL1.medium[2];
        VIFIBNGL3.medium[2] <--> VIFIBNGL4.medium[2];
        VIFIBNGL2.medium[3] <--> VIFIBNGL3.medium[3];
        //     VIFIBN6.medium[1] <--> VIFIBN7.medium[1];
        VIFIBNGL2.medium[4] <--> VIFIBNGL4.medium[3];
        VIFIBNGL3.medium[4] <--> VIFIBNGL1.medium[3];
        VIFIBN55.medium[0] <--> VIFIBN45.medium[1];
        VIFIBNGL3.medium[5] <--> VIFIBN58.medium[1];
        VIFIBNGL1.medium[4] <--> VIFIBN99.medium[1];


        VIFIBN67.medium[1] <--> VIFIBN72.medium[0];
        VIFIBN72.medium[1] <--> VIFIBN50.medium[1];
        VIFIBN29.medium[1] <--> VIFIBN23.medium[1];
        VIFIBNGL1.medium[5] <--> VIFIBN14.medium[0];
        VIFIBN28.medium[0] <--> VIFIBN16.medium[1];
        VIFIBN45.medium[0] <--> VIFIBN38.medium[1];
        VIFIBN47.medium[1] <--> VIFIBNGL2.medium[5];
        VIFIBNGL2.medium[6] <--> VIFIBN41.medium[0];
        VIFIBN36.medium[1] <--> VIFIBN28.medium[1];
        VIFIBN49.medium[0] <--> VIFIBN57.medium[1];
        VIFIBN74.medium[1] <--> VIFIBN84.medium[0];
        VIFIBN79.medium[0] <--> VIFIBN87.medium[0];
        VIFIBN87.medium[1] <--> VIFIBN67.medium[0];
        VIFIBNGL3.medium[6] <--> VIFIBN85.medium[0];
        VIFIBN103.medium[1] <--> VIFIBN113.medium[1];
        VIFIBN96.medium[1] <--> VIFIBN94.medium[0];
        VIFIBN101.medium[1] <--> VIFIBN115.medium[1];
        VIFIBN102.medium[0] <--> VIFIBN116.medium[1];
        VIFIBN116.medium[0] <--> VIFIBN99.medium[0];
        VIFIBNGL4.medium[4] <--> VIFIBN100.medium[1];
        VIFIBNGL1.medium[6] <--> VIFIBNGL4.medium[5];
        VIFIBNGL4.medium[6] <--> VIFIBN114.medium[1];
        VIFIBN66.medium[0] <--> VIFIBN43.medium[1];
        VIFIBN15.medium[0] <--> VIFIBN17.medium[0];
        VIFIBN9.medium[1] <--> VIFIBN6.medium[1];
}
