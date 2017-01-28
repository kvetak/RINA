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



package rina.examples.Routing.BigDC;

import ned.DatarateChannel;
import rina.src.CS.InteriorRouterNInt;

network BigDC
{
    @display("bgb=14400,500");
	submodules:
		T_0_0: InteriorRouterNInt {
            @display("p=75,400");
        }
		T_0_1: InteriorRouterNInt {
            @display("p=135,400");
        }
		T_0_2: InteriorRouterNInt {
            @display("p=195,400");
        }
		T_0_3: InteriorRouterNInt {
            @display("p=255,400");
        }
		T_0_4: InteriorRouterNInt {
            @display("p=315,400");
        }
		T_1_0: InteriorRouterNInt {
            @display("p=435,400");
        }
		T_1_1: InteriorRouterNInt {
            @display("p=495,400");
        }
		T_1_2: InteriorRouterNInt {
            @display("p=555,400");
        }
		T_1_3: InteriorRouterNInt {
            @display("p=615,400");
        }
		T_1_4: InteriorRouterNInt {
            @display("p=675,400");
        }
		T_2_0: InteriorRouterNInt {
            @display("p=795,400");
        }
		T_2_1: InteriorRouterNInt {
            @display("p=855,400");
        }
		T_2_2: InteriorRouterNInt {
            @display("p=915,400");
        }
		T_2_3: InteriorRouterNInt {
            @display("p=975,400");
        }
		T_2_4: InteriorRouterNInt {
            @display("p=1035,400");
        }
		T_3_0: InteriorRouterNInt {
            @display("p=1155,400");
        }
		T_3_1: InteriorRouterNInt {
            @display("p=1215,400");
        }
		T_3_2: InteriorRouterNInt {
            @display("p=1275,400");
        }
		T_3_3: InteriorRouterNInt {
            @display("p=1335,400");
        }
		T_3_4: InteriorRouterNInt {
            @display("p=1395,400");
        }
		T_4_0: InteriorRouterNInt {
            @display("p=1515,400");
        }
		T_4_1: InteriorRouterNInt {
            @display("p=1575,400");
        }
		T_4_2: InteriorRouterNInt {
            @display("p=1635,400");
        }
		T_4_3: InteriorRouterNInt {
            @display("p=1695,400");
        }
		T_4_4: InteriorRouterNInt {
            @display("p=1755,400");
        }
		T_5_0: InteriorRouterNInt {
            @display("p=1875,400");
        }
		T_5_1: InteriorRouterNInt {
            @display("p=1935,400");
        }
		T_5_2: InteriorRouterNInt {
            @display("p=1995,400");
        }
		T_5_3: InteriorRouterNInt {
            @display("p=2055,400");
        }
		T_5_4: InteriorRouterNInt {
            @display("p=2115,400");
        }
		T_6_0: InteriorRouterNInt {
            @display("p=2235,400");
        }
		T_6_1: InteriorRouterNInt {
            @display("p=2295,400");
        }
		T_6_2: InteriorRouterNInt {
            @display("p=2355,400");
        }
		T_6_3: InteriorRouterNInt {
            @display("p=2415,400");
        }
		T_6_4: InteriorRouterNInt {
            @display("p=2475,400");
        }
		T_7_0: InteriorRouterNInt {
            @display("p=2595,400");
        }
		T_7_1: InteriorRouterNInt {
            @display("p=2655,400");
        }
		T_7_2: InteriorRouterNInt {
            @display("p=2715,400");
        }
		T_7_3: InteriorRouterNInt {
            @display("p=2775,400");
        }
		T_7_4: InteriorRouterNInt {
            @display("p=2835,400");
        }
		T_8_0: InteriorRouterNInt {
            @display("p=2955,400");
        }
		T_8_1: InteriorRouterNInt {
            @display("p=3015,400");
        }
		T_8_2: InteriorRouterNInt {
            @display("p=3075,400");
        }
		T_8_3: InteriorRouterNInt {
            @display("p=3135,400");
        }
		T_8_4: InteriorRouterNInt {
            @display("p=3195,400");
        }
		T_9_0: InteriorRouterNInt {
            @display("p=3315,400");
        }
		T_9_1: InteriorRouterNInt {
            @display("p=3375,400");
        }
		T_9_2: InteriorRouterNInt {
            @display("p=3435,400");
        }
		T_9_3: InteriorRouterNInt {
            @display("p=3495,400");
        }
		T_9_4: InteriorRouterNInt {
            @display("p=3555,400");
        }
		T_10_0: InteriorRouterNInt {
            @display("p=3675,400");
        }
		T_10_1: InteriorRouterNInt {
            @display("p=3735,400");
        }
		T_10_2: InteriorRouterNInt {
            @display("p=3795,400");
        }
		T_10_3: InteriorRouterNInt {
            @display("p=3855,400");
        }
		T_10_4: InteriorRouterNInt {
            @display("p=3915,400");
        }
		T_11_0: InteriorRouterNInt {
            @display("p=4035,400");
        }
		T_11_1: InteriorRouterNInt {
            @display("p=4095,400");
        }
		T_11_2: InteriorRouterNInt {
            @display("p=4155,400");
        }
		T_11_3: InteriorRouterNInt {
            @display("p=4215,400");
        }
		T_11_4: InteriorRouterNInt {
            @display("p=4275,400");
        }
		T_12_0: InteriorRouterNInt {
            @display("p=4395,400");
        }
		T_12_1: InteriorRouterNInt {
            @display("p=4455,400");
        }
		T_12_2: InteriorRouterNInt {
            @display("p=4515,400");
        }
		T_12_3: InteriorRouterNInt {
            @display("p=4575,400");
        }
		T_12_4: InteriorRouterNInt {
            @display("p=4635,400");
        }
		T_13_0: InteriorRouterNInt {
            @display("p=4755,400");
        }
		T_13_1: InteriorRouterNInt {
            @display("p=4815,400");
        }
		T_13_2: InteriorRouterNInt {
            @display("p=4875,400");
        }
		T_13_3: InteriorRouterNInt {
            @display("p=4935,400");
        }
		T_13_4: InteriorRouterNInt {
            @display("p=4995,400");
        }
		T_14_0: InteriorRouterNInt {
            @display("p=5115,400");
        }
		T_14_1: InteriorRouterNInt {
            @display("p=5175,400");
        }
		T_14_2: InteriorRouterNInt {
            @display("p=5235,400");
        }
		T_14_3: InteriorRouterNInt {
            @display("p=5295,400");
        }
		T_14_4: InteriorRouterNInt {
            @display("p=5355,400");
        }
		T_15_0: InteriorRouterNInt {
            @display("p=5475,400");
        }
		T_15_1: InteriorRouterNInt {
            @display("p=5535,400");
        }
		T_15_2: InteriorRouterNInt {
            @display("p=5595,400");
        }
		T_15_3: InteriorRouterNInt {
            @display("p=5655,400");
        }
		T_15_4: InteriorRouterNInt {
            @display("p=5715,400");
        }
		T_16_0: InteriorRouterNInt {
            @display("p=5835,400");
        }
		T_16_1: InteriorRouterNInt {
            @display("p=5895,400");
        }
		T_16_2: InteriorRouterNInt {
            @display("p=5955,400");
        }
		T_16_3: InteriorRouterNInt {
            @display("p=6015,400");
        }
		T_16_4: InteriorRouterNInt {
            @display("p=6075,400");
        }
		T_17_0: InteriorRouterNInt {
            @display("p=6195,400");
        }
		T_17_1: InteriorRouterNInt {
            @display("p=6255,400");
        }
		T_17_2: InteriorRouterNInt {
            @display("p=6315,400");
        }
		T_17_3: InteriorRouterNInt {
            @display("p=6375,400");
        }
		T_17_4: InteriorRouterNInt {
            @display("p=6435,400");
        }
		T_18_0: InteriorRouterNInt {
            @display("p=6555,400");
        }
		T_18_1: InteriorRouterNInt {
            @display("p=6615,400");
        }
		T_18_2: InteriorRouterNInt {
            @display("p=6675,400");
        }
		T_18_3: InteriorRouterNInt {
            @display("p=6735,400");
        }
		T_18_4: InteriorRouterNInt {
            @display("p=6795,400");
        }
		T_19_0: InteriorRouterNInt {
            @display("p=6915,400");
        }
		T_19_1: InteriorRouterNInt {
            @display("p=6975,400");
        }
		T_19_2: InteriorRouterNInt {
            @display("p=7035,400");
        }
		T_19_3: InteriorRouterNInt {
            @display("p=7095,400");
        }
		T_19_4: InteriorRouterNInt {
            @display("p=7155,400");
        }
		T_20_0: InteriorRouterNInt {
            @display("p=7275,400");
        }
		T_20_1: InteriorRouterNInt {
            @display("p=7335,400");
        }
		T_20_2: InteriorRouterNInt {
            @display("p=7395,400");
        }
		T_20_3: InteriorRouterNInt {
            @display("p=7455,400");
        }
		T_20_4: InteriorRouterNInt {
            @display("p=7515,400");
        }
		T_21_0: InteriorRouterNInt {
            @display("p=7635,400");
        }
		T_21_1: InteriorRouterNInt {
            @display("p=7695,400");
        }
		T_21_2: InteriorRouterNInt {
            @display("p=7755,400");
        }
		T_21_3: InteriorRouterNInt {
            @display("p=7815,400");
        }
		T_21_4: InteriorRouterNInt {
            @display("p=7875,400");
        }
		T_22_0: InteriorRouterNInt {
            @display("p=7995,400");
        }
		T_22_1: InteriorRouterNInt {
            @display("p=8055,400");
        }
		T_22_2: InteriorRouterNInt {
            @display("p=8115,400");
        }
		T_22_3: InteriorRouterNInt {
            @display("p=8175,400");
        }
		T_22_4: InteriorRouterNInt {
            @display("p=8235,400");
        }
		T_23_0: InteriorRouterNInt {
            @display("p=8355,400");
        }
		T_23_1: InteriorRouterNInt {
            @display("p=8415,400");
        }
		T_23_2: InteriorRouterNInt {
            @display("p=8475,400");
        }
		T_23_3: InteriorRouterNInt {
            @display("p=8535,400");
        }
		T_23_4: InteriorRouterNInt {
            @display("p=8595,400");
        }
		T_24_0: InteriorRouterNInt {
            @display("p=8715,400");
        }
		T_24_1: InteriorRouterNInt {
            @display("p=8775,400");
        }
		T_24_2: InteriorRouterNInt {
            @display("p=8835,400");
        }
		T_24_3: InteriorRouterNInt {
            @display("p=8895,400");
        }
		T_24_4: InteriorRouterNInt {
            @display("p=8955,400");
        }
		T_25_0: InteriorRouterNInt {
            @display("p=9075,400");
        }
		T_25_1: InteriorRouterNInt {
            @display("p=9135,400");
        }
		T_25_2: InteriorRouterNInt {
            @display("p=9195,400");
        }
		T_25_3: InteriorRouterNInt {
            @display("p=9255,400");
        }
		T_25_4: InteriorRouterNInt {
            @display("p=9315,400");
        }
		T_26_0: InteriorRouterNInt {
            @display("p=9435,400");
        }
		T_26_1: InteriorRouterNInt {
            @display("p=9495,400");
        }
		T_26_2: InteriorRouterNInt {
            @display("p=9555,400");
        }
		T_26_3: InteriorRouterNInt {
            @display("p=9615,400");
        }
		T_26_4: InteriorRouterNInt {
            @display("p=9675,400");
        }
		T_27_0: InteriorRouterNInt {
            @display("p=9795,400");
        }
		T_27_1: InteriorRouterNInt {
            @display("p=9855,400");
        }
		T_27_2: InteriorRouterNInt {
            @display("p=9915,400");
        }
		T_27_3: InteriorRouterNInt {
            @display("p=9975,400");
        }
		T_27_4: InteriorRouterNInt {
            @display("p=10035,400");
        }
		T_28_0: InteriorRouterNInt {
            @display("p=10155,400");
        }
		T_28_1: InteriorRouterNInt {
            @display("p=10215,400");
        }
		T_28_2: InteriorRouterNInt {
            @display("p=10275,400");
        }
		T_28_3: InteriorRouterNInt {
            @display("p=10335,400");
        }
		T_28_4: InteriorRouterNInt {
            @display("p=10395,400");
        }
		T_29_0: InteriorRouterNInt {
            @display("p=10515,400");
        }
		T_29_1: InteriorRouterNInt {
            @display("p=10575,400");
        }
		T_29_2: InteriorRouterNInt {
            @display("p=10635,400");
        }
		T_29_3: InteriorRouterNInt {
            @display("p=10695,400");
        }
		T_29_4: InteriorRouterNInt {
            @display("p=10755,400");
        }
		T_30_0: InteriorRouterNInt {
            @display("p=10875,400");
        }
		T_30_1: InteriorRouterNInt {
            @display("p=10935,400");
        }
		T_30_2: InteriorRouterNInt {
            @display("p=10995,400");
        }
		T_30_3: InteriorRouterNInt {
            @display("p=11055,400");
        }
		T_30_4: InteriorRouterNInt {
            @display("p=11115,400");
        }
		T_31_0: InteriorRouterNInt {
            @display("p=11235,400");
        }
		T_31_1: InteriorRouterNInt {
            @display("p=11295,400");
        }
		T_31_2: InteriorRouterNInt {
            @display("p=11355,400");
        }
		T_31_3: InteriorRouterNInt {
            @display("p=11415,400");
        }
		T_31_4: InteriorRouterNInt {
            @display("p=11475,400");
        }
		T_32_0: InteriorRouterNInt {
            @display("p=11595,400");
        }
		T_32_1: InteriorRouterNInt {
            @display("p=11655,400");
        }
		T_32_2: InteriorRouterNInt {
            @display("p=11715,400");
        }
		T_32_3: InteriorRouterNInt {
            @display("p=11775,400");
        }
		T_32_4: InteriorRouterNInt {
            @display("p=11835,400");
        }
		T_33_0: InteriorRouterNInt {
            @display("p=11955,400");
        }
		T_33_1: InteriorRouterNInt {
            @display("p=12015,400");
        }
		T_33_2: InteriorRouterNInt {
            @display("p=12075,400");
        }
		T_33_3: InteriorRouterNInt {
            @display("p=12135,400");
        }
		T_33_4: InteriorRouterNInt {
            @display("p=12195,400");
        }
		T_34_0: InteriorRouterNInt {
            @display("p=12315,400");
        }
		T_34_1: InteriorRouterNInt {
            @display("p=12375,400");
        }
		T_34_2: InteriorRouterNInt {
            @display("p=12435,400");
        }
		T_34_3: InteriorRouterNInt {
            @display("p=12495,400");
        }
		T_34_4: InteriorRouterNInt {
            @display("p=12555,400");
        }
		T_35_0: InteriorRouterNInt {
            @display("p=12675,400");
        }
		T_35_1: InteriorRouterNInt {
            @display("p=12735,400");
        }
		T_35_2: InteriorRouterNInt {
            @display("p=12795,400");
        }
		T_35_3: InteriorRouterNInt {
            @display("p=12855,400");
        }
		T_35_4: InteriorRouterNInt {
            @display("p=12915,400");
        }
		T_36_0: InteriorRouterNInt {
            @display("p=13035,400");
        }
		T_36_1: InteriorRouterNInt {
            @display("p=13095,400");
        }
		T_36_2: InteriorRouterNInt {
            @display("p=13155,400");
        }
		T_36_3: InteriorRouterNInt {
            @display("p=13215,400");
        }
		T_36_4: InteriorRouterNInt {
            @display("p=13275,400");
        }
		T_37_0: InteriorRouterNInt {
            @display("p=13395,400");
        }
		T_37_1: InteriorRouterNInt {
            @display("p=13455,400");
        }
		T_37_2: InteriorRouterNInt {
            @display("p=13515,400");
        }
		T_37_3: InteriorRouterNInt {
            @display("p=13575,400");
        }
		T_37_4: InteriorRouterNInt {
            @display("p=13635,400");
        }
		T_38_0: InteriorRouterNInt {
            @display("p=13755,400");
        }
		T_38_1: InteriorRouterNInt {
            @display("p=13815,400");
        }
		T_38_2: InteriorRouterNInt {
            @display("p=13875,400");
        }
		T_38_3: InteriorRouterNInt {
            @display("p=13935,400");
        }
		T_38_4: InteriorRouterNInt {
            @display("p=13995,400");
        }
		T_39_0: InteriorRouterNInt {
            @display("p=14115,400");
        }
		T_39_1: InteriorRouterNInt {
            @display("p=14175,400");
        }
		T_39_2: InteriorRouterNInt {
            @display("p=14235,400");
        }
		T_39_3: InteriorRouterNInt {
            @display("p=14295,400");
        }
		T_39_4: InteriorRouterNInt {
            @display("p=14355,400");
        }

		F_0_0: InteriorRouterNInt {
            @display("p=81.030150753769,300");
        }
		F_0_1: InteriorRouterNInt {
            @display("p=153.09045226131,300");
        }
		F_0_2: InteriorRouterNInt {
            @display("p=225.15075376884,300");
        }
		F_0_3: InteriorRouterNInt {
            @display("p=297.21105527638,300");
        }
		F_1_0: InteriorRouterNInt {
            @display("p=441.33165829146,300");
        }
		F_1_1: InteriorRouterNInt {
            @display("p=513.391959799,300");
        }
		F_1_2: InteriorRouterNInt {
            @display("p=585.45226130653,300");
        }
		F_1_3: InteriorRouterNInt {
            @display("p=657.51256281407,300");
        }
		F_2_0: InteriorRouterNInt {
            @display("p=801.63316582915,300");
        }
		F_2_1: InteriorRouterNInt {
            @display("p=873.69346733668,300");
        }
		F_2_2: InteriorRouterNInt {
            @display("p=945.75376884422,300");
        }
		F_2_3: InteriorRouterNInt {
            @display("p=1017.8140703518,300");
        }
		F_3_0: InteriorRouterNInt {
            @display("p=1161.9346733668,300");
        }
		F_3_1: InteriorRouterNInt {
            @display("p=1233.9949748744,300");
        }
		F_3_2: InteriorRouterNInt {
            @display("p=1306.0552763819,300");
        }
		F_3_3: InteriorRouterNInt {
            @display("p=1378.1155778894,300");
        }
		F_4_0: InteriorRouterNInt {
            @display("p=1522.2361809045,300");
        }
		F_4_1: InteriorRouterNInt {
            @display("p=1594.2964824121,300");
        }
		F_4_2: InteriorRouterNInt {
            @display("p=1666.3567839196,300");
        }
		F_4_3: InteriorRouterNInt {
            @display("p=1738.4170854271,300");
        }
		F_5_0: InteriorRouterNInt {
            @display("p=1882.5376884422,300");
        }
		F_5_1: InteriorRouterNInt {
            @display("p=1954.5979899497,300");
        }
		F_5_2: InteriorRouterNInt {
            @display("p=2026.6582914573,300");
        }
		F_5_3: InteriorRouterNInt {
            @display("p=2098.7185929648,300");
        }
		F_6_0: InteriorRouterNInt {
            @display("p=2242.8391959799,300");
        }
		F_6_1: InteriorRouterNInt {
            @display("p=2314.8994974874,300");
        }
		F_6_2: InteriorRouterNInt {
            @display("p=2386.959798995,300");
        }
		F_6_3: InteriorRouterNInt {
            @display("p=2459.0201005025,300");
        }
		F_7_0: InteriorRouterNInt {
            @display("p=2603.1407035176,300");
        }
		F_7_1: InteriorRouterNInt {
            @display("p=2675.2010050251,300");
        }
		F_7_2: InteriorRouterNInt {
            @display("p=2747.2613065327,300");
        }
		F_7_3: InteriorRouterNInt {
            @display("p=2819.3216080402,300");
        }
		F_8_0: InteriorRouterNInt {
            @display("p=2963.4422110553,300");
        }
		F_8_1: InteriorRouterNInt {
            @display("p=3035.5025125628,300");
        }
		F_8_2: InteriorRouterNInt {
            @display("p=3107.5628140704,300");
        }
		F_8_3: InteriorRouterNInt {
            @display("p=3179.6231155779,300");
        }
		F_9_0: InteriorRouterNInt {
            @display("p=3323.743718593,300");
        }
		F_9_1: InteriorRouterNInt {
            @display("p=3395.8040201005,300");
        }
		F_9_2: InteriorRouterNInt {
            @display("p=3467.864321608,300");
        }
		F_9_3: InteriorRouterNInt {
            @display("p=3539.9246231156,300");
        }
		F_10_0: InteriorRouterNInt {
            @display("p=3684.0452261307,300");
        }
		F_10_1: InteriorRouterNInt {
            @display("p=3756.1055276382,300");
        }
		F_10_2: InteriorRouterNInt {
            @display("p=3828.1658291457,300");
        }
		F_10_3: InteriorRouterNInt {
            @display("p=3900.2261306533,300");
        }
		F_11_0: InteriorRouterNInt {
            @display("p=4044.3467336683,300");
        }
		F_11_1: InteriorRouterNInt {
            @display("p=4116.4070351759,300");
        }
		F_11_2: InteriorRouterNInt {
            @display("p=4188.4673366834,300");
        }
		F_11_3: InteriorRouterNInt {
            @display("p=4260.527638191,300");
        }
		F_12_0: InteriorRouterNInt {
            @display("p=4404.648241206,300");
        }
		F_12_1: InteriorRouterNInt {
            @display("p=4476.7085427136,300");
        }
		F_12_2: InteriorRouterNInt {
            @display("p=4548.7688442211,300");
        }
		F_12_3: InteriorRouterNInt {
            @display("p=4620.8291457286,300");
        }
		F_13_0: InteriorRouterNInt {
            @display("p=4764.9497487437,300");
        }
		F_13_1: InteriorRouterNInt {
            @display("p=4837.0100502513,300");
        }
		F_13_2: InteriorRouterNInt {
            @display("p=4909.0703517588,300");
        }
		F_13_3: InteriorRouterNInt {
            @display("p=4981.1306532663,300");
        }
		F_14_0: InteriorRouterNInt {
            @display("p=5125.2512562814,300");
        }
		F_14_1: InteriorRouterNInt {
            @display("p=5197.3115577889,300");
        }
		F_14_2: InteriorRouterNInt {
            @display("p=5269.3718592965,300");
        }
		F_14_3: InteriorRouterNInt {
            @display("p=5341.432160804,300");
        }
		F_15_0: InteriorRouterNInt {
            @display("p=5485.5527638191,300");
        }
		F_15_1: InteriorRouterNInt {
            @display("p=5557.6130653266,300");
        }
		F_15_2: InteriorRouterNInt {
            @display("p=5629.6733668342,300");
        }
		F_15_3: InteriorRouterNInt {
            @display("p=5701.7336683417,300");
        }
		F_16_0: InteriorRouterNInt {
            @display("p=5845.8542713568,300");
        }
		F_16_1: InteriorRouterNInt {
            @display("p=5917.9145728643,300");
        }
		F_16_2: InteriorRouterNInt {
            @display("p=5989.9748743719,300");
        }
		F_16_3: InteriorRouterNInt {
            @display("p=6062.0351758794,300");
        }
		F_17_0: InteriorRouterNInt {
            @display("p=6206.1557788945,300");
        }
		F_17_1: InteriorRouterNInt {
            @display("p=6278.216080402,300");
        }
		F_17_2: InteriorRouterNInt {
            @display("p=6350.2763819095,300");
        }
		F_17_3: InteriorRouterNInt {
            @display("p=6422.3366834171,300");
        }
		F_18_0: InteriorRouterNInt {
            @display("p=6566.4572864322,300");
        }
		F_18_1: InteriorRouterNInt {
            @display("p=6638.5175879397,300");
        }
		F_18_2: InteriorRouterNInt {
            @display("p=6710.5778894472,300");
        }
		F_18_3: InteriorRouterNInt {
            @display("p=6782.6381909548,300");
        }
		F_19_0: InteriorRouterNInt {
            @display("p=6926.7587939698,300");
        }
		F_19_1: InteriorRouterNInt {
            @display("p=6998.8190954774,300");
        }
		F_19_2: InteriorRouterNInt {
            @display("p=7070.8793969849,300");
        }
		F_19_3: InteriorRouterNInt {
            @display("p=7142.9396984925,300");
        }
		F_20_0: InteriorRouterNInt {
            @display("p=7287.0603015075,300");
        }
		F_20_1: InteriorRouterNInt {
            @display("p=7359.1206030151,300");
        }
		F_20_2: InteriorRouterNInt {
            @display("p=7431.1809045226,300");
        }
		F_20_3: InteriorRouterNInt {
            @display("p=7503.2412060302,300");
        }
		F_21_0: InteriorRouterNInt {
            @display("p=7647.3618090452,300");
        }
		F_21_1: InteriorRouterNInt {
            @display("p=7719.4221105528,300");
        }
		F_21_2: InteriorRouterNInt {
            @display("p=7791.4824120603,300");
        }
		F_21_3: InteriorRouterNInt {
            @display("p=7863.5427135678,300");
        }
		F_22_0: InteriorRouterNInt {
            @display("p=8007.6633165829,300");
        }
		F_22_1: InteriorRouterNInt {
            @display("p=8079.7236180905,300");
        }
		F_22_2: InteriorRouterNInt {
            @display("p=8151.783919598,300");
        }
		F_22_3: InteriorRouterNInt {
            @display("p=8223.8442211055,300");
        }
		F_23_0: InteriorRouterNInt {
            @display("p=8367.9648241206,300");
        }
		F_23_1: InteriorRouterNInt {
            @display("p=8440.0251256281,300");
        }
		F_23_2: InteriorRouterNInt {
            @display("p=8512.0854271357,300");
        }
		F_23_3: InteriorRouterNInt {
            @display("p=8584.1457286432,300");
        }
		F_24_0: InteriorRouterNInt {
            @display("p=8728.2663316583,300");
        }
		F_24_1: InteriorRouterNInt {
            @display("p=8800.3266331658,300");
        }
		F_24_2: InteriorRouterNInt {
            @display("p=8872.3869346734,300");
        }
		F_24_3: InteriorRouterNInt {
            @display("p=8944.4472361809,300");
        }
		F_25_0: InteriorRouterNInt {
            @display("p=9088.567839196,300");
        }
		F_25_1: InteriorRouterNInt {
            @display("p=9160.6281407035,300");
        }
		F_25_2: InteriorRouterNInt {
            @display("p=9232.6884422111,300");
        }
		F_25_3: InteriorRouterNInt {
            @display("p=9304.7487437186,300");
        }
		F_26_0: InteriorRouterNInt {
            @display("p=9448.8693467337,300");
        }
		F_26_1: InteriorRouterNInt {
            @display("p=9520.9296482412,300");
        }
		F_26_2: InteriorRouterNInt {
            @display("p=9592.9899497487,300");
        }
		F_26_3: InteriorRouterNInt {
            @display("p=9665.0502512563,300");
        }
		F_27_0: InteriorRouterNInt {
            @display("p=9809.1708542714,300");
        }
		F_27_1: InteriorRouterNInt {
            @display("p=9881.2311557789,300");
        }
		F_27_2: InteriorRouterNInt {
            @display("p=9953.2914572864,300");
        }
		F_27_3: InteriorRouterNInt {
            @display("p=10025.351758794,300");
        }
		F_28_0: InteriorRouterNInt {
            @display("p=10169.472361809,300");
        }
		F_28_1: InteriorRouterNInt {
            @display("p=10241.532663317,300");
        }
		F_28_2: InteriorRouterNInt {
            @display("p=10313.592964824,300");
        }
		F_28_3: InteriorRouterNInt {
            @display("p=10385.653266332,300");
        }
		F_29_0: InteriorRouterNInt {
            @display("p=10529.773869347,300");
        }
		F_29_1: InteriorRouterNInt {
            @display("p=10601.834170854,300");
        }
		F_29_2: InteriorRouterNInt {
            @display("p=10673.894472362,300");
        }
		F_29_3: InteriorRouterNInt {
            @display("p=10745.954773869,300");
        }
		F_30_0: InteriorRouterNInt {
            @display("p=10890.075376884,300");
        }
		F_30_1: InteriorRouterNInt {
            @display("p=10962.135678392,300");
        }
		F_30_2: InteriorRouterNInt {
            @display("p=11034.195979899,300");
        }
		F_30_3: InteriorRouterNInt {
            @display("p=11106.256281407,300");
        }
		F_31_0: InteriorRouterNInt {
            @display("p=11250.376884422,300");
        }
		F_31_1: InteriorRouterNInt {
            @display("p=11322.43718593,300");
        }
		F_31_2: InteriorRouterNInt {
            @display("p=11394.497487437,300");
        }
		F_31_3: InteriorRouterNInt {
            @display("p=11466.557788945,300");
        }
		F_32_0: InteriorRouterNInt {
            @display("p=11610.67839196,300");
        }
		F_32_1: InteriorRouterNInt {
            @display("p=11682.738693467,300");
        }
		F_32_2: InteriorRouterNInt {
            @display("p=11754.798994975,300");
        }
		F_32_3: InteriorRouterNInt {
            @display("p=11826.859296482,300");
        }
		F_33_0: InteriorRouterNInt {
            @display("p=11970.979899497,300");
        }
		F_33_1: InteriorRouterNInt {
            @display("p=12043.040201005,300");
        }
		F_33_2: InteriorRouterNInt {
            @display("p=12115.100502513,300");
        }
		F_33_3: InteriorRouterNInt {
            @display("p=12187.16080402,300");
        }
		F_34_0: InteriorRouterNInt {
            @display("p=12331.281407035,300");
        }
		F_34_1: InteriorRouterNInt {
            @display("p=12403.341708543,300");
        }
		F_34_2: InteriorRouterNInt {
            @display("p=12475.40201005,300");
        }
		F_34_3: InteriorRouterNInt {
            @display("p=12547.462311558,300");
        }
		F_35_0: InteriorRouterNInt {
            @display("p=12691.582914573,300");
        }
		F_35_1: InteriorRouterNInt {
            @display("p=12763.64321608,300");
        }
		F_35_2: InteriorRouterNInt {
            @display("p=12835.703517588,300");
        }
		F_35_3: InteriorRouterNInt {
            @display("p=12907.763819095,300");
        }
		F_36_0: InteriorRouterNInt {
            @display("p=13051.884422111,300");
        }
		F_36_1: InteriorRouterNInt {
            @display("p=13123.944723618,300");
        }
		F_36_2: InteriorRouterNInt {
            @display("p=13196.005025126,300");
        }
		F_36_3: InteriorRouterNInt {
            @display("p=13268.065326633,300");
        }
		F_37_0: InteriorRouterNInt {
            @display("p=13412.185929648,300");
        }
		F_37_1: InteriorRouterNInt {
            @display("p=13484.246231156,300");
        }
		F_37_2: InteriorRouterNInt {
            @display("p=13556.306532663,300");
        }
		F_37_3: InteriorRouterNInt {
            @display("p=13628.366834171,300");
        }
		F_38_0: InteriorRouterNInt {
            @display("p=13772.487437186,300");
        }
		F_38_1: InteriorRouterNInt {
            @display("p=13844.547738693,300");
        }
		F_38_2: InteriorRouterNInt {
            @display("p=13916.608040201,300");
        }
		F_38_3: InteriorRouterNInt {
            @display("p=13988.668341709,300");
        }
		F_39_0: InteriorRouterNInt {
            @display("p=14132.788944724,300");
        }
		F_39_1: InteriorRouterNInt {
            @display("p=14204.849246231,300");
        }
		F_39_2: InteriorRouterNInt {
            @display("p=14276.909547739,300");
        }
		F_39_3: InteriorRouterNInt {
            @display("p=14348.969849246,300");
        }

		S_0_0: InteriorRouterNInt {
            @display("p=211.74418604651,200");
        }
		S_0_1: InteriorRouterNInt {
            @display("p=545.23255813953,200");
        }
		S_0_2: InteriorRouterNInt {
            @display("p=878.72093023256,200");
        }
		S_0_3: InteriorRouterNInt {
            @display("p=1212.2093023256,200");
        }
		S_0_4: InteriorRouterNInt {
            @display("p=1545.6976744186,200");
        }
		S_0_5: InteriorRouterNInt {
            @display("p=1879.1860465116,200");
        }
		S_0_6: InteriorRouterNInt {
            @display("p=2212.6744186047,200");
        }
		S_0_7: InteriorRouterNInt {
            @display("p=2546.1627906977,200");
        }
		S_0_8: InteriorRouterNInt {
            @display("p=2879.6511627907,200");
        }
		S_0_9: InteriorRouterNInt {
            @display("p=3213.1395348837,200");
        }
		S_1_0: InteriorRouterNInt {
            @display("p=3880.1162790698,200");
        }
		S_1_1: InteriorRouterNInt {
            @display("p=4213.6046511628,200");
        }
		S_1_2: InteriorRouterNInt {
            @display("p=4547.0930232558,200");
        }
		S_1_3: InteriorRouterNInt {
            @display("p=4880.5813953488,200");
        }
		S_1_4: InteriorRouterNInt {
            @display("p=5214.0697674419,200");
        }
		S_1_5: InteriorRouterNInt {
            @display("p=5547.5581395349,200");
        }
		S_1_6: InteriorRouterNInt {
            @display("p=5881.0465116279,200");
        }
		S_1_7: InteriorRouterNInt {
            @display("p=6214.5348837209,200");
        }
		S_1_8: InteriorRouterNInt {
            @display("p=6548.023255814,200");
        }
		S_1_9: InteriorRouterNInt {
            @display("p=6881.511627907,200");
        }
		S_2_0: InteriorRouterNInt {
            @display("p=7548.488372093,200");
        }
		S_2_1: InteriorRouterNInt {
            @display("p=7881.976744186,200");
        }
		S_2_2: InteriorRouterNInt {
            @display("p=8215.4651162791,200");
        }
		S_2_3: InteriorRouterNInt {
            @display("p=8548.9534883721,200");
        }
		S_2_4: InteriorRouterNInt {
            @display("p=8882.4418604651,200");
        }
		S_2_5: InteriorRouterNInt {
            @display("p=9215.9302325581,200");
        }
		S_2_6: InteriorRouterNInt {
            @display("p=9549.4186046512,200");
        }
		S_2_7: InteriorRouterNInt {
            @display("p=9882.9069767442,200");
        }
		S_2_8: InteriorRouterNInt {
            @display("p=10216.395348837,200");
        }
		S_2_9: InteriorRouterNInt {
            @display("p=10549.88372093,200");
        }
		S_3_0: InteriorRouterNInt {
            @display("p=11216.860465116,200");
        }
		S_3_1: InteriorRouterNInt {
            @display("p=11550.348837209,200");
        }
		S_3_2: InteriorRouterNInt {
            @display("p=11883.837209302,200");
        }
		S_3_3: InteriorRouterNInt {
            @display("p=12217.325581395,200");
        }
		S_3_4: InteriorRouterNInt {
            @display("p=12550.813953488,200");
        }
		S_3_5: InteriorRouterNInt {
            @display("p=12884.302325581,200");
        }
		S_3_6: InteriorRouterNInt {
            @display("p=13217.790697674,200");
        }
		S_3_7: InteriorRouterNInt {
            @display("p=13551.279069767,200");
        }
		S_3_8: InteriorRouterNInt {
            @display("p=13884.76744186,200");
        }
		S_3_9: InteriorRouterNInt {
            @display("p=14218.255813953,200");
        }

		E_0_0: InteriorRouterNInt {
            @display("p=343.75,100");
        }
		E_0_1: InteriorRouterNInt {
            @display("p=941.25,100");
        }
		E_0_2: InteriorRouterNInt {
            @display("p=1538.75,100");
        }
		E_0_3: InteriorRouterNInt {
            @display("p=2136.25,100");
        }
		E_1_0: InteriorRouterNInt {
            @display("p=3331.25,100");
        }
		E_1_1: InteriorRouterNInt {
            @display("p=3928.75,100");
        }
		E_1_2: InteriorRouterNInt {
            @display("p=4526.25,100");
        }
		E_1_3: InteriorRouterNInt {
            @display("p=5123.75,100");
        }
		E_2_0: InteriorRouterNInt {
            @display("p=6318.75,100");
        }
		E_2_1: InteriorRouterNInt {
            @display("p=6916.25,100");
        }
		E_2_2: InteriorRouterNInt {
            @display("p=7513.75,100");
        }
		E_2_3: InteriorRouterNInt {
            @display("p=8111.25,100");
        }
		E_3_0: InteriorRouterNInt {
            @display("p=9306.25,100");
        }
		E_3_1: InteriorRouterNInt {
            @display("p=9903.75,100");
        }
		E_3_2: InteriorRouterNInt {
            @display("p=10501.25,100");
        }
		E_3_3: InteriorRouterNInt {
            @display("p=11098.75,100");
        }
		E_4_0: InteriorRouterNInt {
            @display("p=12293.75,100");
        }
		E_4_1: InteriorRouterNInt {
            @display("p=12891.25,100");
        }
		E_4_2: InteriorRouterNInt {
            @display("p=13488.75,100");
        }
		E_4_3: InteriorRouterNInt {
            @display("p=14086.25,100");
        }

       
    connections:
		T_0_0.medium++ <--> TF_Link <-->  F_0_0.medium++;
		T_0_0.medium++ <--> TF_Link <-->  F_0_1.medium++;
		T_0_0.medium++ <--> TF_Link <-->  F_0_2.medium++;
		T_0_0.medium++ <--> TF_Link <-->  F_0_3.medium++;
		T_0_1.medium++ <--> TF_Link <-->  F_0_0.medium++;
		T_0_1.medium++ <--> TF_Link <-->  F_0_1.medium++;
		T_0_1.medium++ <--> TF_Link <-->  F_0_2.medium++;
		T_0_1.medium++ <--> TF_Link <-->  F_0_3.medium++;
		T_0_2.medium++ <--> TF_Link <-->  F_0_0.medium++;
		T_0_2.medium++ <--> TF_Link <-->  F_0_1.medium++;
		T_0_2.medium++ <--> TF_Link <-->  F_0_2.medium++;
		T_0_2.medium++ <--> TF_Link <-->  F_0_3.medium++;
		T_0_3.medium++ <--> TF_Link <-->  F_0_0.medium++;
		T_0_3.medium++ <--> TF_Link <-->  F_0_1.medium++;
		T_0_3.medium++ <--> TF_Link <-->  F_0_2.medium++;
		T_0_3.medium++ <--> TF_Link <-->  F_0_3.medium++;
		T_0_4.medium++ <--> TF_Link <-->  F_0_0.medium++;
		T_0_4.medium++ <--> TF_Link <-->  F_0_1.medium++;
		T_0_4.medium++ <--> TF_Link <-->  F_0_2.medium++;
		T_0_4.medium++ <--> TF_Link <-->  F_0_3.medium++;
		T_1_0.medium++ <--> TF_Link <-->  F_1_0.medium++;
		T_1_0.medium++ <--> TF_Link <-->  F_1_1.medium++;
		T_1_0.medium++ <--> TF_Link <-->  F_1_2.medium++;
		T_1_0.medium++ <--> TF_Link <-->  F_1_3.medium++;
		T_1_1.medium++ <--> TF_Link <-->  F_1_0.medium++;
		T_1_1.medium++ <--> TF_Link <-->  F_1_1.medium++;
		T_1_1.medium++ <--> TF_Link <-->  F_1_2.medium++;
		T_1_1.medium++ <--> TF_Link <-->  F_1_3.medium++;
		T_1_2.medium++ <--> TF_Link <-->  F_1_0.medium++;
		T_1_2.medium++ <--> TF_Link <-->  F_1_1.medium++;
		T_1_2.medium++ <--> TF_Link <-->  F_1_2.medium++;
		T_1_2.medium++ <--> TF_Link <-->  F_1_3.medium++;
		T_1_3.medium++ <--> TF_Link <-->  F_1_0.medium++;
		T_1_3.medium++ <--> TF_Link <-->  F_1_1.medium++;
		T_1_3.medium++ <--> TF_Link <-->  F_1_2.medium++;
		T_1_3.medium++ <--> TF_Link <-->  F_1_3.medium++;
		T_1_4.medium++ <--> TF_Link <-->  F_1_0.medium++;
		T_1_4.medium++ <--> TF_Link <-->  F_1_1.medium++;
		T_1_4.medium++ <--> TF_Link <-->  F_1_2.medium++;
		T_1_4.medium++ <--> TF_Link <-->  F_1_3.medium++;
		T_2_0.medium++ <--> TF_Link <-->  F_2_0.medium++;
		T_2_0.medium++ <--> TF_Link <-->  F_2_1.medium++;
		T_2_0.medium++ <--> TF_Link <-->  F_2_2.medium++;
		T_2_0.medium++ <--> TF_Link <-->  F_2_3.medium++;
		T_2_1.medium++ <--> TF_Link <-->  F_2_0.medium++;
		T_2_1.medium++ <--> TF_Link <-->  F_2_1.medium++;
		T_2_1.medium++ <--> TF_Link <-->  F_2_2.medium++;
		T_2_1.medium++ <--> TF_Link <-->  F_2_3.medium++;
		T_2_2.medium++ <--> TF_Link <-->  F_2_0.medium++;
		T_2_2.medium++ <--> TF_Link <-->  F_2_1.medium++;
		T_2_2.medium++ <--> TF_Link <-->  F_2_2.medium++;
		T_2_2.medium++ <--> TF_Link <-->  F_2_3.medium++;
		T_2_3.medium++ <--> TF_Link <-->  F_2_0.medium++;
		T_2_3.medium++ <--> TF_Link <-->  F_2_1.medium++;
		T_2_3.medium++ <--> TF_Link <-->  F_2_2.medium++;
		T_2_3.medium++ <--> TF_Link <-->  F_2_3.medium++;
		T_2_4.medium++ <--> TF_Link <-->  F_2_0.medium++;
		T_2_4.medium++ <--> TF_Link <-->  F_2_1.medium++;
		T_2_4.medium++ <--> TF_Link <-->  F_2_2.medium++;
		T_2_4.medium++ <--> TF_Link <-->  F_2_3.medium++;
		T_3_0.medium++ <--> TF_Link <-->  F_3_0.medium++;
		T_3_0.medium++ <--> TF_Link <-->  F_3_1.medium++;
		T_3_0.medium++ <--> TF_Link <-->  F_3_2.medium++;
		T_3_0.medium++ <--> TF_Link <-->  F_3_3.medium++;
		T_3_1.medium++ <--> TF_Link <-->  F_3_0.medium++;
		T_3_1.medium++ <--> TF_Link <-->  F_3_1.medium++;
		T_3_1.medium++ <--> TF_Link <-->  F_3_2.medium++;
		T_3_1.medium++ <--> TF_Link <-->  F_3_3.medium++;
		T_3_2.medium++ <--> TF_Link <-->  F_3_0.medium++;
		T_3_2.medium++ <--> TF_Link <-->  F_3_1.medium++;
		T_3_2.medium++ <--> TF_Link <-->  F_3_2.medium++;
		T_3_2.medium++ <--> TF_Link <-->  F_3_3.medium++;
		T_3_3.medium++ <--> TF_Link <-->  F_3_0.medium++;
		T_3_3.medium++ <--> TF_Link <-->  F_3_1.medium++;
		T_3_3.medium++ <--> TF_Link <-->  F_3_2.medium++;
		T_3_3.medium++ <--> TF_Link <-->  F_3_3.medium++;
		T_3_4.medium++ <--> TF_Link <-->  F_3_0.medium++;
		T_3_4.medium++ <--> TF_Link <-->  F_3_1.medium++;
		T_3_4.medium++ <--> TF_Link <-->  F_3_2.medium++;
		T_3_4.medium++ <--> TF_Link <-->  F_3_3.medium++;
		T_4_0.medium++ <--> TF_Link <-->  F_4_0.medium++;
		T_4_0.medium++ <--> TF_Link <-->  F_4_1.medium++;
		T_4_0.medium++ <--> TF_Link <-->  F_4_2.medium++;
		T_4_0.medium++ <--> TF_Link <-->  F_4_3.medium++;
		T_4_1.medium++ <--> TF_Link <-->  F_4_0.medium++;
		T_4_1.medium++ <--> TF_Link <-->  F_4_1.medium++;
		T_4_1.medium++ <--> TF_Link <-->  F_4_2.medium++;
		T_4_1.medium++ <--> TF_Link <-->  F_4_3.medium++;
		T_4_2.medium++ <--> TF_Link <-->  F_4_0.medium++;
		T_4_2.medium++ <--> TF_Link <-->  F_4_1.medium++;
		T_4_2.medium++ <--> TF_Link <-->  F_4_2.medium++;
		T_4_2.medium++ <--> TF_Link <-->  F_4_3.medium++;
		T_4_3.medium++ <--> TF_Link <-->  F_4_0.medium++;
		T_4_3.medium++ <--> TF_Link <-->  F_4_1.medium++;
		T_4_3.medium++ <--> TF_Link <-->  F_4_2.medium++;
		T_4_3.medium++ <--> TF_Link <-->  F_4_3.medium++;
		T_4_4.medium++ <--> TF_Link <-->  F_4_0.medium++;
		T_4_4.medium++ <--> TF_Link <-->  F_4_1.medium++;
		T_4_4.medium++ <--> TF_Link <-->  F_4_2.medium++;
		T_4_4.medium++ <--> TF_Link <-->  F_4_3.medium++;
		T_5_0.medium++ <--> TF_Link <-->  F_5_0.medium++;
		T_5_0.medium++ <--> TF_Link <-->  F_5_1.medium++;
		T_5_0.medium++ <--> TF_Link <-->  F_5_2.medium++;
		T_5_0.medium++ <--> TF_Link <-->  F_5_3.medium++;
		T_5_1.medium++ <--> TF_Link <-->  F_5_0.medium++;
		T_5_1.medium++ <--> TF_Link <-->  F_5_1.medium++;
		T_5_1.medium++ <--> TF_Link <-->  F_5_2.medium++;
		T_5_1.medium++ <--> TF_Link <-->  F_5_3.medium++;
		T_5_2.medium++ <--> TF_Link <-->  F_5_0.medium++;
		T_5_2.medium++ <--> TF_Link <-->  F_5_1.medium++;
		T_5_2.medium++ <--> TF_Link <-->  F_5_2.medium++;
		T_5_2.medium++ <--> TF_Link <-->  F_5_3.medium++;
		T_5_3.medium++ <--> TF_Link <-->  F_5_0.medium++;
		T_5_3.medium++ <--> TF_Link <-->  F_5_1.medium++;
		T_5_3.medium++ <--> TF_Link <-->  F_5_2.medium++;
		T_5_3.medium++ <--> TF_Link <-->  F_5_3.medium++;
		T_5_4.medium++ <--> TF_Link <-->  F_5_0.medium++;
		T_5_4.medium++ <--> TF_Link <-->  F_5_1.medium++;
		T_5_4.medium++ <--> TF_Link <-->  F_5_2.medium++;
		T_5_4.medium++ <--> TF_Link <-->  F_5_3.medium++;
		T_6_0.medium++ <--> TF_Link <-->  F_6_0.medium++;
		T_6_0.medium++ <--> TF_Link <-->  F_6_1.medium++;
		T_6_0.medium++ <--> TF_Link <-->  F_6_2.medium++;
		T_6_0.medium++ <--> TF_Link <-->  F_6_3.medium++;
		T_6_1.medium++ <--> TF_Link <-->  F_6_0.medium++;
		T_6_1.medium++ <--> TF_Link <-->  F_6_1.medium++;
		T_6_1.medium++ <--> TF_Link <-->  F_6_2.medium++;
		T_6_1.medium++ <--> TF_Link <-->  F_6_3.medium++;
		T_6_2.medium++ <--> TF_Link <-->  F_6_0.medium++;
		T_6_2.medium++ <--> TF_Link <-->  F_6_1.medium++;
		T_6_2.medium++ <--> TF_Link <-->  F_6_2.medium++;
		T_6_2.medium++ <--> TF_Link <-->  F_6_3.medium++;
		T_6_3.medium++ <--> TF_Link <-->  F_6_0.medium++;
		T_6_3.medium++ <--> TF_Link <-->  F_6_1.medium++;
		T_6_3.medium++ <--> TF_Link <-->  F_6_2.medium++;
		T_6_3.medium++ <--> TF_Link <-->  F_6_3.medium++;
		T_6_4.medium++ <--> TF_Link <-->  F_6_0.medium++;
		T_6_4.medium++ <--> TF_Link <-->  F_6_1.medium++;
		T_6_4.medium++ <--> TF_Link <-->  F_6_2.medium++;
		T_6_4.medium++ <--> TF_Link <-->  F_6_3.medium++;
		T_7_0.medium++ <--> TF_Link <-->  F_7_0.medium++;
		T_7_0.medium++ <--> TF_Link <-->  F_7_1.medium++;
		T_7_0.medium++ <--> TF_Link <-->  F_7_2.medium++;
		T_7_0.medium++ <--> TF_Link <-->  F_7_3.medium++;
		T_7_1.medium++ <--> TF_Link <-->  F_7_0.medium++;
		T_7_1.medium++ <--> TF_Link <-->  F_7_1.medium++;
		T_7_1.medium++ <--> TF_Link <-->  F_7_2.medium++;
		T_7_1.medium++ <--> TF_Link <-->  F_7_3.medium++;
		T_7_2.medium++ <--> TF_Link <-->  F_7_0.medium++;
		T_7_2.medium++ <--> TF_Link <-->  F_7_1.medium++;
		T_7_2.medium++ <--> TF_Link <-->  F_7_2.medium++;
		T_7_2.medium++ <--> TF_Link <-->  F_7_3.medium++;
		T_7_3.medium++ <--> TF_Link <-->  F_7_0.medium++;
		T_7_3.medium++ <--> TF_Link <-->  F_7_1.medium++;
		T_7_3.medium++ <--> TF_Link <-->  F_7_2.medium++;
		T_7_3.medium++ <--> TF_Link <-->  F_7_3.medium++;
		T_7_4.medium++ <--> TF_Link <-->  F_7_0.medium++;
		T_7_4.medium++ <--> TF_Link <-->  F_7_1.medium++;
		T_7_4.medium++ <--> TF_Link <-->  F_7_2.medium++;
		T_7_4.medium++ <--> TF_Link <-->  F_7_3.medium++;
		T_8_0.medium++ <--> TF_Link <-->  F_8_0.medium++;
		T_8_0.medium++ <--> TF_Link <-->  F_8_1.medium++;
		T_8_0.medium++ <--> TF_Link <-->  F_8_2.medium++;
		T_8_0.medium++ <--> TF_Link <-->  F_8_3.medium++;
		T_8_1.medium++ <--> TF_Link <-->  F_8_0.medium++;
		T_8_1.medium++ <--> TF_Link <-->  F_8_1.medium++;
		T_8_1.medium++ <--> TF_Link <-->  F_8_2.medium++;
		T_8_1.medium++ <--> TF_Link <-->  F_8_3.medium++;
		T_8_2.medium++ <--> TF_Link <-->  F_8_0.medium++;
		T_8_2.medium++ <--> TF_Link <-->  F_8_1.medium++;
		T_8_2.medium++ <--> TF_Link <-->  F_8_2.medium++;
		T_8_2.medium++ <--> TF_Link <-->  F_8_3.medium++;
		T_8_3.medium++ <--> TF_Link <-->  F_8_0.medium++;
		T_8_3.medium++ <--> TF_Link <-->  F_8_1.medium++;
		T_8_3.medium++ <--> TF_Link <-->  F_8_2.medium++;
		T_8_3.medium++ <--> TF_Link <-->  F_8_3.medium++;
		T_8_4.medium++ <--> TF_Link <-->  F_8_0.medium++;
		T_8_4.medium++ <--> TF_Link <-->  F_8_1.medium++;
		T_8_4.medium++ <--> TF_Link <-->  F_8_2.medium++;
		T_8_4.medium++ <--> TF_Link <-->  F_8_3.medium++;
		T_9_0.medium++ <--> TF_Link <-->  F_9_0.medium++;
		T_9_0.medium++ <--> TF_Link <-->  F_9_1.medium++;
		T_9_0.medium++ <--> TF_Link <-->  F_9_2.medium++;
		T_9_0.medium++ <--> TF_Link <-->  F_9_3.medium++;
		T_9_1.medium++ <--> TF_Link <-->  F_9_0.medium++;
		T_9_1.medium++ <--> TF_Link <-->  F_9_1.medium++;
		T_9_1.medium++ <--> TF_Link <-->  F_9_2.medium++;
		T_9_1.medium++ <--> TF_Link <-->  F_9_3.medium++;
		T_9_2.medium++ <--> TF_Link <-->  F_9_0.medium++;
		T_9_2.medium++ <--> TF_Link <-->  F_9_1.medium++;
		T_9_2.medium++ <--> TF_Link <-->  F_9_2.medium++;
		T_9_2.medium++ <--> TF_Link <-->  F_9_3.medium++;
		T_9_3.medium++ <--> TF_Link <-->  F_9_0.medium++;
		T_9_3.medium++ <--> TF_Link <-->  F_9_1.medium++;
		T_9_3.medium++ <--> TF_Link <-->  F_9_2.medium++;
		T_9_3.medium++ <--> TF_Link <-->  F_9_3.medium++;
		T_9_4.medium++ <--> TF_Link <-->  F_9_0.medium++;
		T_9_4.medium++ <--> TF_Link <-->  F_9_1.medium++;
		T_9_4.medium++ <--> TF_Link <-->  F_9_2.medium++;
		T_9_4.medium++ <--> TF_Link <-->  F_9_3.medium++;
		T_10_0.medium++ <--> TF_Link <-->  F_10_0.medium++;
		T_10_0.medium++ <--> TF_Link <-->  F_10_1.medium++;
		T_10_0.medium++ <--> TF_Link <-->  F_10_2.medium++;
		T_10_0.medium++ <--> TF_Link <-->  F_10_3.medium++;
		T_10_1.medium++ <--> TF_Link <-->  F_10_0.medium++;
		T_10_1.medium++ <--> TF_Link <-->  F_10_1.medium++;
		T_10_1.medium++ <--> TF_Link <-->  F_10_2.medium++;
		T_10_1.medium++ <--> TF_Link <-->  F_10_3.medium++;
		T_10_2.medium++ <--> TF_Link <-->  F_10_0.medium++;
		T_10_2.medium++ <--> TF_Link <-->  F_10_1.medium++;
		T_10_2.medium++ <--> TF_Link <-->  F_10_2.medium++;
		T_10_2.medium++ <--> TF_Link <-->  F_10_3.medium++;
		T_10_3.medium++ <--> TF_Link <-->  F_10_0.medium++;
		T_10_3.medium++ <--> TF_Link <-->  F_10_1.medium++;
		T_10_3.medium++ <--> TF_Link <-->  F_10_2.medium++;
		T_10_3.medium++ <--> TF_Link <-->  F_10_3.medium++;
		T_10_4.medium++ <--> TF_Link <-->  F_10_0.medium++;
		T_10_4.medium++ <--> TF_Link <-->  F_10_1.medium++;
		T_10_4.medium++ <--> TF_Link <-->  F_10_2.medium++;
		T_10_4.medium++ <--> TF_Link <-->  F_10_3.medium++;
		T_11_0.medium++ <--> TF_Link <-->  F_11_0.medium++;
		T_11_0.medium++ <--> TF_Link <-->  F_11_1.medium++;
		T_11_0.medium++ <--> TF_Link <-->  F_11_2.medium++;
		T_11_0.medium++ <--> TF_Link <-->  F_11_3.medium++;
		T_11_1.medium++ <--> TF_Link <-->  F_11_0.medium++;
		T_11_1.medium++ <--> TF_Link <-->  F_11_1.medium++;
		T_11_1.medium++ <--> TF_Link <-->  F_11_2.medium++;
		T_11_1.medium++ <--> TF_Link <-->  F_11_3.medium++;
		T_11_2.medium++ <--> TF_Link <-->  F_11_0.medium++;
		T_11_2.medium++ <--> TF_Link <-->  F_11_1.medium++;
		T_11_2.medium++ <--> TF_Link <-->  F_11_2.medium++;
		T_11_2.medium++ <--> TF_Link <-->  F_11_3.medium++;
		T_11_3.medium++ <--> TF_Link <-->  F_11_0.medium++;
		T_11_3.medium++ <--> TF_Link <-->  F_11_1.medium++;
		T_11_3.medium++ <--> TF_Link <-->  F_11_2.medium++;
		T_11_3.medium++ <--> TF_Link <-->  F_11_3.medium++;
		T_11_4.medium++ <--> TF_Link <-->  F_11_0.medium++;
		T_11_4.medium++ <--> TF_Link <-->  F_11_1.medium++;
		T_11_4.medium++ <--> TF_Link <-->  F_11_2.medium++;
		T_11_4.medium++ <--> TF_Link <-->  F_11_3.medium++;
		T_12_0.medium++ <--> TF_Link <-->  F_12_0.medium++;
		T_12_0.medium++ <--> TF_Link <-->  F_12_1.medium++;
		T_12_0.medium++ <--> TF_Link <-->  F_12_2.medium++;
		T_12_0.medium++ <--> TF_Link <-->  F_12_3.medium++;
		T_12_1.medium++ <--> TF_Link <-->  F_12_0.medium++;
		T_12_1.medium++ <--> TF_Link <-->  F_12_1.medium++;
		T_12_1.medium++ <--> TF_Link <-->  F_12_2.medium++;
		T_12_1.medium++ <--> TF_Link <-->  F_12_3.medium++;
		T_12_2.medium++ <--> TF_Link <-->  F_12_0.medium++;
		T_12_2.medium++ <--> TF_Link <-->  F_12_1.medium++;
		T_12_2.medium++ <--> TF_Link <-->  F_12_2.medium++;
		T_12_2.medium++ <--> TF_Link <-->  F_12_3.medium++;
		T_12_3.medium++ <--> TF_Link <-->  F_12_0.medium++;
		T_12_3.medium++ <--> TF_Link <-->  F_12_1.medium++;
		T_12_3.medium++ <--> TF_Link <-->  F_12_2.medium++;
		T_12_3.medium++ <--> TF_Link <-->  F_12_3.medium++;
		T_12_4.medium++ <--> TF_Link <-->  F_12_0.medium++;
		T_12_4.medium++ <--> TF_Link <-->  F_12_1.medium++;
		T_12_4.medium++ <--> TF_Link <-->  F_12_2.medium++;
		T_12_4.medium++ <--> TF_Link <-->  F_12_3.medium++;
		T_13_0.medium++ <--> TF_Link <-->  F_13_0.medium++;
		T_13_0.medium++ <--> TF_Link <-->  F_13_1.medium++;
		T_13_0.medium++ <--> TF_Link <-->  F_13_2.medium++;
		T_13_0.medium++ <--> TF_Link <-->  F_13_3.medium++;
		T_13_1.medium++ <--> TF_Link <-->  F_13_0.medium++;
		T_13_1.medium++ <--> TF_Link <-->  F_13_1.medium++;
		T_13_1.medium++ <--> TF_Link <-->  F_13_2.medium++;
		T_13_1.medium++ <--> TF_Link <-->  F_13_3.medium++;
		T_13_2.medium++ <--> TF_Link <-->  F_13_0.medium++;
		T_13_2.medium++ <--> TF_Link <-->  F_13_1.medium++;
		T_13_2.medium++ <--> TF_Link <-->  F_13_2.medium++;
		T_13_2.medium++ <--> TF_Link <-->  F_13_3.medium++;
		T_13_3.medium++ <--> TF_Link <-->  F_13_0.medium++;
		T_13_3.medium++ <--> TF_Link <-->  F_13_1.medium++;
		T_13_3.medium++ <--> TF_Link <-->  F_13_2.medium++;
		T_13_3.medium++ <--> TF_Link <-->  F_13_3.medium++;
		T_13_4.medium++ <--> TF_Link <-->  F_13_0.medium++;
		T_13_4.medium++ <--> TF_Link <-->  F_13_1.medium++;
		T_13_4.medium++ <--> TF_Link <-->  F_13_2.medium++;
		T_13_4.medium++ <--> TF_Link <-->  F_13_3.medium++;
		T_14_0.medium++ <--> TF_Link <-->  F_14_0.medium++;
		T_14_0.medium++ <--> TF_Link <-->  F_14_1.medium++;
		T_14_0.medium++ <--> TF_Link <-->  F_14_2.medium++;
		T_14_0.medium++ <--> TF_Link <-->  F_14_3.medium++;
		T_14_1.medium++ <--> TF_Link <-->  F_14_0.medium++;
		T_14_1.medium++ <--> TF_Link <-->  F_14_1.medium++;
		T_14_1.medium++ <--> TF_Link <-->  F_14_2.medium++;
		T_14_1.medium++ <--> TF_Link <-->  F_14_3.medium++;
		T_14_2.medium++ <--> TF_Link <-->  F_14_0.medium++;
		T_14_2.medium++ <--> TF_Link <-->  F_14_1.medium++;
		T_14_2.medium++ <--> TF_Link <-->  F_14_2.medium++;
		T_14_2.medium++ <--> TF_Link <-->  F_14_3.medium++;
		T_14_3.medium++ <--> TF_Link <-->  F_14_0.medium++;
		T_14_3.medium++ <--> TF_Link <-->  F_14_1.medium++;
		T_14_3.medium++ <--> TF_Link <-->  F_14_2.medium++;
		T_14_3.medium++ <--> TF_Link <-->  F_14_3.medium++;
		T_14_4.medium++ <--> TF_Link <-->  F_14_0.medium++;
		T_14_4.medium++ <--> TF_Link <-->  F_14_1.medium++;
		T_14_4.medium++ <--> TF_Link <-->  F_14_2.medium++;
		T_14_4.medium++ <--> TF_Link <-->  F_14_3.medium++;
		T_15_0.medium++ <--> TF_Link <-->  F_15_0.medium++;
		T_15_0.medium++ <--> TF_Link <-->  F_15_1.medium++;
		T_15_0.medium++ <--> TF_Link <-->  F_15_2.medium++;
		T_15_0.medium++ <--> TF_Link <-->  F_15_3.medium++;
		T_15_1.medium++ <--> TF_Link <-->  F_15_0.medium++;
		T_15_1.medium++ <--> TF_Link <-->  F_15_1.medium++;
		T_15_1.medium++ <--> TF_Link <-->  F_15_2.medium++;
		T_15_1.medium++ <--> TF_Link <-->  F_15_3.medium++;
		T_15_2.medium++ <--> TF_Link <-->  F_15_0.medium++;
		T_15_2.medium++ <--> TF_Link <-->  F_15_1.medium++;
		T_15_2.medium++ <--> TF_Link <-->  F_15_2.medium++;
		T_15_2.medium++ <--> TF_Link <-->  F_15_3.medium++;
		T_15_3.medium++ <--> TF_Link <-->  F_15_0.medium++;
		T_15_3.medium++ <--> TF_Link <-->  F_15_1.medium++;
		T_15_3.medium++ <--> TF_Link <-->  F_15_2.medium++;
		T_15_3.medium++ <--> TF_Link <-->  F_15_3.medium++;
		T_15_4.medium++ <--> TF_Link <-->  F_15_0.medium++;
		T_15_4.medium++ <--> TF_Link <-->  F_15_1.medium++;
		T_15_4.medium++ <--> TF_Link <-->  F_15_2.medium++;
		T_15_4.medium++ <--> TF_Link <-->  F_15_3.medium++;
		T_16_0.medium++ <--> TF_Link <-->  F_16_0.medium++;
		T_16_0.medium++ <--> TF_Link <-->  F_16_1.medium++;
		T_16_0.medium++ <--> TF_Link <-->  F_16_2.medium++;
		T_16_0.medium++ <--> TF_Link <-->  F_16_3.medium++;
		T_16_1.medium++ <--> TF_Link <-->  F_16_0.medium++;
		T_16_1.medium++ <--> TF_Link <-->  F_16_1.medium++;
		T_16_1.medium++ <--> TF_Link <-->  F_16_2.medium++;
		T_16_1.medium++ <--> TF_Link <-->  F_16_3.medium++;
		T_16_2.medium++ <--> TF_Link <-->  F_16_0.medium++;
		T_16_2.medium++ <--> TF_Link <-->  F_16_1.medium++;
		T_16_2.medium++ <--> TF_Link <-->  F_16_2.medium++;
		T_16_2.medium++ <--> TF_Link <-->  F_16_3.medium++;
		T_16_3.medium++ <--> TF_Link <-->  F_16_0.medium++;
		T_16_3.medium++ <--> TF_Link <-->  F_16_1.medium++;
		T_16_3.medium++ <--> TF_Link <-->  F_16_2.medium++;
		T_16_3.medium++ <--> TF_Link <-->  F_16_3.medium++;
		T_16_4.medium++ <--> TF_Link <-->  F_16_0.medium++;
		T_16_4.medium++ <--> TF_Link <-->  F_16_1.medium++;
		T_16_4.medium++ <--> TF_Link <-->  F_16_2.medium++;
		T_16_4.medium++ <--> TF_Link <-->  F_16_3.medium++;
		T_17_0.medium++ <--> TF_Link <-->  F_17_0.medium++;
		T_17_0.medium++ <--> TF_Link <-->  F_17_1.medium++;
		T_17_0.medium++ <--> TF_Link <-->  F_17_2.medium++;
		T_17_0.medium++ <--> TF_Link <-->  F_17_3.medium++;
		T_17_1.medium++ <--> TF_Link <-->  F_17_0.medium++;
		T_17_1.medium++ <--> TF_Link <-->  F_17_1.medium++;
		T_17_1.medium++ <--> TF_Link <-->  F_17_2.medium++;
		T_17_1.medium++ <--> TF_Link <-->  F_17_3.medium++;
		T_17_2.medium++ <--> TF_Link <-->  F_17_0.medium++;
		T_17_2.medium++ <--> TF_Link <-->  F_17_1.medium++;
		T_17_2.medium++ <--> TF_Link <-->  F_17_2.medium++;
		T_17_2.medium++ <--> TF_Link <-->  F_17_3.medium++;
		T_17_3.medium++ <--> TF_Link <-->  F_17_0.medium++;
		T_17_3.medium++ <--> TF_Link <-->  F_17_1.medium++;
		T_17_3.medium++ <--> TF_Link <-->  F_17_2.medium++;
		T_17_3.medium++ <--> TF_Link <-->  F_17_3.medium++;
		T_17_4.medium++ <--> TF_Link <-->  F_17_0.medium++;
		T_17_4.medium++ <--> TF_Link <-->  F_17_1.medium++;
		T_17_4.medium++ <--> TF_Link <-->  F_17_2.medium++;
		T_17_4.medium++ <--> TF_Link <-->  F_17_3.medium++;
		T_18_0.medium++ <--> TF_Link <-->  F_18_0.medium++;
		T_18_0.medium++ <--> TF_Link <-->  F_18_1.medium++;
		T_18_0.medium++ <--> TF_Link <-->  F_18_2.medium++;
		T_18_0.medium++ <--> TF_Link <-->  F_18_3.medium++;
		T_18_1.medium++ <--> TF_Link <-->  F_18_0.medium++;
		T_18_1.medium++ <--> TF_Link <-->  F_18_1.medium++;
		T_18_1.medium++ <--> TF_Link <-->  F_18_2.medium++;
		T_18_1.medium++ <--> TF_Link <-->  F_18_3.medium++;
		T_18_2.medium++ <--> TF_Link <-->  F_18_0.medium++;
		T_18_2.medium++ <--> TF_Link <-->  F_18_1.medium++;
		T_18_2.medium++ <--> TF_Link <-->  F_18_2.medium++;
		T_18_2.medium++ <--> TF_Link <-->  F_18_3.medium++;
		T_18_3.medium++ <--> TF_Link <-->  F_18_0.medium++;
		T_18_3.medium++ <--> TF_Link <-->  F_18_1.medium++;
		T_18_3.medium++ <--> TF_Link <-->  F_18_2.medium++;
		T_18_3.medium++ <--> TF_Link <-->  F_18_3.medium++;
		T_18_4.medium++ <--> TF_Link <-->  F_18_0.medium++;
		T_18_4.medium++ <--> TF_Link <-->  F_18_1.medium++;
		T_18_4.medium++ <--> TF_Link <-->  F_18_2.medium++;
		T_18_4.medium++ <--> TF_Link <-->  F_18_3.medium++;
		T_19_0.medium++ <--> TF_Link <-->  F_19_0.medium++;
		T_19_0.medium++ <--> TF_Link <-->  F_19_1.medium++;
		T_19_0.medium++ <--> TF_Link <-->  F_19_2.medium++;
		T_19_0.medium++ <--> TF_Link <-->  F_19_3.medium++;
		T_19_1.medium++ <--> TF_Link <-->  F_19_0.medium++;
		T_19_1.medium++ <--> TF_Link <-->  F_19_1.medium++;
		T_19_1.medium++ <--> TF_Link <-->  F_19_2.medium++;
		T_19_1.medium++ <--> TF_Link <-->  F_19_3.medium++;
		T_19_2.medium++ <--> TF_Link <-->  F_19_0.medium++;
		T_19_2.medium++ <--> TF_Link <-->  F_19_1.medium++;
		T_19_2.medium++ <--> TF_Link <-->  F_19_2.medium++;
		T_19_2.medium++ <--> TF_Link <-->  F_19_3.medium++;
		T_19_3.medium++ <--> TF_Link <-->  F_19_0.medium++;
		T_19_3.medium++ <--> TF_Link <-->  F_19_1.medium++;
		T_19_3.medium++ <--> TF_Link <-->  F_19_2.medium++;
		T_19_3.medium++ <--> TF_Link <-->  F_19_3.medium++;
		T_19_4.medium++ <--> TF_Link <-->  F_19_0.medium++;
		T_19_4.medium++ <--> TF_Link <-->  F_19_1.medium++;
		T_19_4.medium++ <--> TF_Link <-->  F_19_2.medium++;
		T_19_4.medium++ <--> TF_Link <-->  F_19_3.medium++;
		T_20_0.medium++ <--> TF_Link <-->  F_20_0.medium++;
		T_20_0.medium++ <--> TF_Link <-->  F_20_1.medium++;
		T_20_0.medium++ <--> TF_Link <-->  F_20_2.medium++;
		T_20_0.medium++ <--> TF_Link <-->  F_20_3.medium++;
		T_20_1.medium++ <--> TF_Link <-->  F_20_0.medium++;
		T_20_1.medium++ <--> TF_Link <-->  F_20_1.medium++;
		T_20_1.medium++ <--> TF_Link <-->  F_20_2.medium++;
		T_20_1.medium++ <--> TF_Link <-->  F_20_3.medium++;
		T_20_2.medium++ <--> TF_Link <-->  F_20_0.medium++;
		T_20_2.medium++ <--> TF_Link <-->  F_20_1.medium++;
		T_20_2.medium++ <--> TF_Link <-->  F_20_2.medium++;
		T_20_2.medium++ <--> TF_Link <-->  F_20_3.medium++;
		T_20_3.medium++ <--> TF_Link <-->  F_20_0.medium++;
		T_20_3.medium++ <--> TF_Link <-->  F_20_1.medium++;
		T_20_3.medium++ <--> TF_Link <-->  F_20_2.medium++;
		T_20_3.medium++ <--> TF_Link <-->  F_20_3.medium++;
		T_20_4.medium++ <--> TF_Link <-->  F_20_0.medium++;
		T_20_4.medium++ <--> TF_Link <-->  F_20_1.medium++;
		T_20_4.medium++ <--> TF_Link <-->  F_20_2.medium++;
		T_20_4.medium++ <--> TF_Link <-->  F_20_3.medium++;
		T_21_0.medium++ <--> TF_Link <-->  F_21_0.medium++;
		T_21_0.medium++ <--> TF_Link <-->  F_21_1.medium++;
		T_21_0.medium++ <--> TF_Link <-->  F_21_2.medium++;
		T_21_0.medium++ <--> TF_Link <-->  F_21_3.medium++;
		T_21_1.medium++ <--> TF_Link <-->  F_21_0.medium++;
		T_21_1.medium++ <--> TF_Link <-->  F_21_1.medium++;
		T_21_1.medium++ <--> TF_Link <-->  F_21_2.medium++;
		T_21_1.medium++ <--> TF_Link <-->  F_21_3.medium++;
		T_21_2.medium++ <--> TF_Link <-->  F_21_0.medium++;
		T_21_2.medium++ <--> TF_Link <-->  F_21_1.medium++;
		T_21_2.medium++ <--> TF_Link <-->  F_21_2.medium++;
		T_21_2.medium++ <--> TF_Link <-->  F_21_3.medium++;
		T_21_3.medium++ <--> TF_Link <-->  F_21_0.medium++;
		T_21_3.medium++ <--> TF_Link <-->  F_21_1.medium++;
		T_21_3.medium++ <--> TF_Link <-->  F_21_2.medium++;
		T_21_3.medium++ <--> TF_Link <-->  F_21_3.medium++;
		T_21_4.medium++ <--> TF_Link <-->  F_21_0.medium++;
		T_21_4.medium++ <--> TF_Link <-->  F_21_1.medium++;
		T_21_4.medium++ <--> TF_Link <-->  F_21_2.medium++;
		T_21_4.medium++ <--> TF_Link <-->  F_21_3.medium++;
		T_22_0.medium++ <--> TF_Link <-->  F_22_0.medium++;
		T_22_0.medium++ <--> TF_Link <-->  F_22_1.medium++;
		T_22_0.medium++ <--> TF_Link <-->  F_22_2.medium++;
		T_22_0.medium++ <--> TF_Link <-->  F_22_3.medium++;
		T_22_1.medium++ <--> TF_Link <-->  F_22_0.medium++;
		T_22_1.medium++ <--> TF_Link <-->  F_22_1.medium++;
		T_22_1.medium++ <--> TF_Link <-->  F_22_2.medium++;
		T_22_1.medium++ <--> TF_Link <-->  F_22_3.medium++;
		T_22_2.medium++ <--> TF_Link <-->  F_22_0.medium++;
		T_22_2.medium++ <--> TF_Link <-->  F_22_1.medium++;
		T_22_2.medium++ <--> TF_Link <-->  F_22_2.medium++;
		T_22_2.medium++ <--> TF_Link <-->  F_22_3.medium++;
		T_22_3.medium++ <--> TF_Link <-->  F_22_0.medium++;
		T_22_3.medium++ <--> TF_Link <-->  F_22_1.medium++;
		T_22_3.medium++ <--> TF_Link <-->  F_22_2.medium++;
		T_22_3.medium++ <--> TF_Link <-->  F_22_3.medium++;
		T_22_4.medium++ <--> TF_Link <-->  F_22_0.medium++;
		T_22_4.medium++ <--> TF_Link <-->  F_22_1.medium++;
		T_22_4.medium++ <--> TF_Link <-->  F_22_2.medium++;
		T_22_4.medium++ <--> TF_Link <-->  F_22_3.medium++;
		T_23_0.medium++ <--> TF_Link <-->  F_23_0.medium++;
		T_23_0.medium++ <--> TF_Link <-->  F_23_1.medium++;
		T_23_0.medium++ <--> TF_Link <-->  F_23_2.medium++;
		T_23_0.medium++ <--> TF_Link <-->  F_23_3.medium++;
		T_23_1.medium++ <--> TF_Link <-->  F_23_0.medium++;
		T_23_1.medium++ <--> TF_Link <-->  F_23_1.medium++;
		T_23_1.medium++ <--> TF_Link <-->  F_23_2.medium++;
		T_23_1.medium++ <--> TF_Link <-->  F_23_3.medium++;
		T_23_2.medium++ <--> TF_Link <-->  F_23_0.medium++;
		T_23_2.medium++ <--> TF_Link <-->  F_23_1.medium++;
		T_23_2.medium++ <--> TF_Link <-->  F_23_2.medium++;
		T_23_2.medium++ <--> TF_Link <-->  F_23_3.medium++;
		T_23_3.medium++ <--> TF_Link <-->  F_23_0.medium++;
		T_23_3.medium++ <--> TF_Link <-->  F_23_1.medium++;
		T_23_3.medium++ <--> TF_Link <-->  F_23_2.medium++;
		T_23_3.medium++ <--> TF_Link <-->  F_23_3.medium++;
		T_23_4.medium++ <--> TF_Link <-->  F_23_0.medium++;
		T_23_4.medium++ <--> TF_Link <-->  F_23_1.medium++;
		T_23_4.medium++ <--> TF_Link <-->  F_23_2.medium++;
		T_23_4.medium++ <--> TF_Link <-->  F_23_3.medium++;
		T_24_0.medium++ <--> TF_Link <-->  F_24_0.medium++;
		T_24_0.medium++ <--> TF_Link <-->  F_24_1.medium++;
		T_24_0.medium++ <--> TF_Link <-->  F_24_2.medium++;
		T_24_0.medium++ <--> TF_Link <-->  F_24_3.medium++;
		T_24_1.medium++ <--> TF_Link <-->  F_24_0.medium++;
		T_24_1.medium++ <--> TF_Link <-->  F_24_1.medium++;
		T_24_1.medium++ <--> TF_Link <-->  F_24_2.medium++;
		T_24_1.medium++ <--> TF_Link <-->  F_24_3.medium++;
		T_24_2.medium++ <--> TF_Link <-->  F_24_0.medium++;
		T_24_2.medium++ <--> TF_Link <-->  F_24_1.medium++;
		T_24_2.medium++ <--> TF_Link <-->  F_24_2.medium++;
		T_24_2.medium++ <--> TF_Link <-->  F_24_3.medium++;
		T_24_3.medium++ <--> TF_Link <-->  F_24_0.medium++;
		T_24_3.medium++ <--> TF_Link <-->  F_24_1.medium++;
		T_24_3.medium++ <--> TF_Link <-->  F_24_2.medium++;
		T_24_3.medium++ <--> TF_Link <-->  F_24_3.medium++;
		T_24_4.medium++ <--> TF_Link <-->  F_24_0.medium++;
		T_24_4.medium++ <--> TF_Link <-->  F_24_1.medium++;
		T_24_4.medium++ <--> TF_Link <-->  F_24_2.medium++;
		T_24_4.medium++ <--> TF_Link <-->  F_24_3.medium++;
		T_25_0.medium++ <--> TF_Link <-->  F_25_0.medium++;
		T_25_0.medium++ <--> TF_Link <-->  F_25_1.medium++;
		T_25_0.medium++ <--> TF_Link <-->  F_25_2.medium++;
		T_25_0.medium++ <--> TF_Link <-->  F_25_3.medium++;
		T_25_1.medium++ <--> TF_Link <-->  F_25_0.medium++;
		T_25_1.medium++ <--> TF_Link <-->  F_25_1.medium++;
		T_25_1.medium++ <--> TF_Link <-->  F_25_2.medium++;
		T_25_1.medium++ <--> TF_Link <-->  F_25_3.medium++;
		T_25_2.medium++ <--> TF_Link <-->  F_25_0.medium++;
		T_25_2.medium++ <--> TF_Link <-->  F_25_1.medium++;
		T_25_2.medium++ <--> TF_Link <-->  F_25_2.medium++;
		T_25_2.medium++ <--> TF_Link <-->  F_25_3.medium++;
		T_25_3.medium++ <--> TF_Link <-->  F_25_0.medium++;
		T_25_3.medium++ <--> TF_Link <-->  F_25_1.medium++;
		T_25_3.medium++ <--> TF_Link <-->  F_25_2.medium++;
		T_25_3.medium++ <--> TF_Link <-->  F_25_3.medium++;
		T_25_4.medium++ <--> TF_Link <-->  F_25_0.medium++;
		T_25_4.medium++ <--> TF_Link <-->  F_25_1.medium++;
		T_25_4.medium++ <--> TF_Link <-->  F_25_2.medium++;
		T_25_4.medium++ <--> TF_Link <-->  F_25_3.medium++;
		T_26_0.medium++ <--> TF_Link <-->  F_26_0.medium++;
		T_26_0.medium++ <--> TF_Link <-->  F_26_1.medium++;
		T_26_0.medium++ <--> TF_Link <-->  F_26_2.medium++;
		T_26_0.medium++ <--> TF_Link <-->  F_26_3.medium++;
		T_26_1.medium++ <--> TF_Link <-->  F_26_0.medium++;
		T_26_1.medium++ <--> TF_Link <-->  F_26_1.medium++;
		T_26_1.medium++ <--> TF_Link <-->  F_26_2.medium++;
		T_26_1.medium++ <--> TF_Link <-->  F_26_3.medium++;
		T_26_2.medium++ <--> TF_Link <-->  F_26_0.medium++;
		T_26_2.medium++ <--> TF_Link <-->  F_26_1.medium++;
		T_26_2.medium++ <--> TF_Link <-->  F_26_2.medium++;
		T_26_2.medium++ <--> TF_Link <-->  F_26_3.medium++;
		T_26_3.medium++ <--> TF_Link <-->  F_26_0.medium++;
		T_26_3.medium++ <--> TF_Link <-->  F_26_1.medium++;
		T_26_3.medium++ <--> TF_Link <-->  F_26_2.medium++;
		T_26_3.medium++ <--> TF_Link <-->  F_26_3.medium++;
		T_26_4.medium++ <--> TF_Link <-->  F_26_0.medium++;
		T_26_4.medium++ <--> TF_Link <-->  F_26_1.medium++;
		T_26_4.medium++ <--> TF_Link <-->  F_26_2.medium++;
		T_26_4.medium++ <--> TF_Link <-->  F_26_3.medium++;
		T_27_0.medium++ <--> TF_Link <-->  F_27_0.medium++;
		T_27_0.medium++ <--> TF_Link <-->  F_27_1.medium++;
		T_27_0.medium++ <--> TF_Link <-->  F_27_2.medium++;
		T_27_0.medium++ <--> TF_Link <-->  F_27_3.medium++;
		T_27_1.medium++ <--> TF_Link <-->  F_27_0.medium++;
		T_27_1.medium++ <--> TF_Link <-->  F_27_1.medium++;
		T_27_1.medium++ <--> TF_Link <-->  F_27_2.medium++;
		T_27_1.medium++ <--> TF_Link <-->  F_27_3.medium++;
		T_27_2.medium++ <--> TF_Link <-->  F_27_0.medium++;
		T_27_2.medium++ <--> TF_Link <-->  F_27_1.medium++;
		T_27_2.medium++ <--> TF_Link <-->  F_27_2.medium++;
		T_27_2.medium++ <--> TF_Link <-->  F_27_3.medium++;
		T_27_3.medium++ <--> TF_Link <-->  F_27_0.medium++;
		T_27_3.medium++ <--> TF_Link <-->  F_27_1.medium++;
		T_27_3.medium++ <--> TF_Link <-->  F_27_2.medium++;
		T_27_3.medium++ <--> TF_Link <-->  F_27_3.medium++;
		T_27_4.medium++ <--> TF_Link <-->  F_27_0.medium++;
		T_27_4.medium++ <--> TF_Link <-->  F_27_1.medium++;
		T_27_4.medium++ <--> TF_Link <-->  F_27_2.medium++;
		T_27_4.medium++ <--> TF_Link <-->  F_27_3.medium++;
		T_28_0.medium++ <--> TF_Link <-->  F_28_0.medium++;
		T_28_0.medium++ <--> TF_Link <-->  F_28_1.medium++;
		T_28_0.medium++ <--> TF_Link <-->  F_28_2.medium++;
		T_28_0.medium++ <--> TF_Link <-->  F_28_3.medium++;
		T_28_1.medium++ <--> TF_Link <-->  F_28_0.medium++;
		T_28_1.medium++ <--> TF_Link <-->  F_28_1.medium++;
		T_28_1.medium++ <--> TF_Link <-->  F_28_2.medium++;
		T_28_1.medium++ <--> TF_Link <-->  F_28_3.medium++;
		T_28_2.medium++ <--> TF_Link <-->  F_28_0.medium++;
		T_28_2.medium++ <--> TF_Link <-->  F_28_1.medium++;
		T_28_2.medium++ <--> TF_Link <-->  F_28_2.medium++;
		T_28_2.medium++ <--> TF_Link <-->  F_28_3.medium++;
		T_28_3.medium++ <--> TF_Link <-->  F_28_0.medium++;
		T_28_3.medium++ <--> TF_Link <-->  F_28_1.medium++;
		T_28_3.medium++ <--> TF_Link <-->  F_28_2.medium++;
		T_28_3.medium++ <--> TF_Link <-->  F_28_3.medium++;
		T_28_4.medium++ <--> TF_Link <-->  F_28_0.medium++;
		T_28_4.medium++ <--> TF_Link <-->  F_28_1.medium++;
		T_28_4.medium++ <--> TF_Link <-->  F_28_2.medium++;
		T_28_4.medium++ <--> TF_Link <-->  F_28_3.medium++;
		T_29_0.medium++ <--> TF_Link <-->  F_29_0.medium++;
		T_29_0.medium++ <--> TF_Link <-->  F_29_1.medium++;
		T_29_0.medium++ <--> TF_Link <-->  F_29_2.medium++;
		T_29_0.medium++ <--> TF_Link <-->  F_29_3.medium++;
		T_29_1.medium++ <--> TF_Link <-->  F_29_0.medium++;
		T_29_1.medium++ <--> TF_Link <-->  F_29_1.medium++;
		T_29_1.medium++ <--> TF_Link <-->  F_29_2.medium++;
		T_29_1.medium++ <--> TF_Link <-->  F_29_3.medium++;
		T_29_2.medium++ <--> TF_Link <-->  F_29_0.medium++;
		T_29_2.medium++ <--> TF_Link <-->  F_29_1.medium++;
		T_29_2.medium++ <--> TF_Link <-->  F_29_2.medium++;
		T_29_2.medium++ <--> TF_Link <-->  F_29_3.medium++;
		T_29_3.medium++ <--> TF_Link <-->  F_29_0.medium++;
		T_29_3.medium++ <--> TF_Link <-->  F_29_1.medium++;
		T_29_3.medium++ <--> TF_Link <-->  F_29_2.medium++;
		T_29_3.medium++ <--> TF_Link <-->  F_29_3.medium++;
		T_29_4.medium++ <--> TF_Link <-->  F_29_0.medium++;
		T_29_4.medium++ <--> TF_Link <-->  F_29_1.medium++;
		T_29_4.medium++ <--> TF_Link <-->  F_29_2.medium++;
		T_29_4.medium++ <--> TF_Link <-->  F_29_3.medium++;
		T_30_0.medium++ <--> TF_Link <-->  F_30_0.medium++;
		T_30_0.medium++ <--> TF_Link <-->  F_30_1.medium++;
		T_30_0.medium++ <--> TF_Link <-->  F_30_2.medium++;
		T_30_0.medium++ <--> TF_Link <-->  F_30_3.medium++;
		T_30_1.medium++ <--> TF_Link <-->  F_30_0.medium++;
		T_30_1.medium++ <--> TF_Link <-->  F_30_1.medium++;
		T_30_1.medium++ <--> TF_Link <-->  F_30_2.medium++;
		T_30_1.medium++ <--> TF_Link <-->  F_30_3.medium++;
		T_30_2.medium++ <--> TF_Link <-->  F_30_0.medium++;
		T_30_2.medium++ <--> TF_Link <-->  F_30_1.medium++;
		T_30_2.medium++ <--> TF_Link <-->  F_30_2.medium++;
		T_30_2.medium++ <--> TF_Link <-->  F_30_3.medium++;
		T_30_3.medium++ <--> TF_Link <-->  F_30_0.medium++;
		T_30_3.medium++ <--> TF_Link <-->  F_30_1.medium++;
		T_30_3.medium++ <--> TF_Link <-->  F_30_2.medium++;
		T_30_3.medium++ <--> TF_Link <-->  F_30_3.medium++;
		T_30_4.medium++ <--> TF_Link <-->  F_30_0.medium++;
		T_30_4.medium++ <--> TF_Link <-->  F_30_1.medium++;
		T_30_4.medium++ <--> TF_Link <-->  F_30_2.medium++;
		T_30_4.medium++ <--> TF_Link <-->  F_30_3.medium++;
		T_31_0.medium++ <--> TF_Link <-->  F_31_0.medium++;
		T_31_0.medium++ <--> TF_Link <-->  F_31_1.medium++;
		T_31_0.medium++ <--> TF_Link <-->  F_31_2.medium++;
		T_31_0.medium++ <--> TF_Link <-->  F_31_3.medium++;
		T_31_1.medium++ <--> TF_Link <-->  F_31_0.medium++;
		T_31_1.medium++ <--> TF_Link <-->  F_31_1.medium++;
		T_31_1.medium++ <--> TF_Link <-->  F_31_2.medium++;
		T_31_1.medium++ <--> TF_Link <-->  F_31_3.medium++;
		T_31_2.medium++ <--> TF_Link <-->  F_31_0.medium++;
		T_31_2.medium++ <--> TF_Link <-->  F_31_1.medium++;
		T_31_2.medium++ <--> TF_Link <-->  F_31_2.medium++;
		T_31_2.medium++ <--> TF_Link <-->  F_31_3.medium++;
		T_31_3.medium++ <--> TF_Link <-->  F_31_0.medium++;
		T_31_3.medium++ <--> TF_Link <-->  F_31_1.medium++;
		T_31_3.medium++ <--> TF_Link <-->  F_31_2.medium++;
		T_31_3.medium++ <--> TF_Link <-->  F_31_3.medium++;
		T_31_4.medium++ <--> TF_Link <-->  F_31_0.medium++;
		T_31_4.medium++ <--> TF_Link <-->  F_31_1.medium++;
		T_31_4.medium++ <--> TF_Link <-->  F_31_2.medium++;
		T_31_4.medium++ <--> TF_Link <-->  F_31_3.medium++;
		T_32_0.medium++ <--> TF_Link <-->  F_32_0.medium++;
		T_32_0.medium++ <--> TF_Link <-->  F_32_1.medium++;
		T_32_0.medium++ <--> TF_Link <-->  F_32_2.medium++;
		T_32_0.medium++ <--> TF_Link <-->  F_32_3.medium++;
		T_32_1.medium++ <--> TF_Link <-->  F_32_0.medium++;
		T_32_1.medium++ <--> TF_Link <-->  F_32_1.medium++;
		T_32_1.medium++ <--> TF_Link <-->  F_32_2.medium++;
		T_32_1.medium++ <--> TF_Link <-->  F_32_3.medium++;
		T_32_2.medium++ <--> TF_Link <-->  F_32_0.medium++;
		T_32_2.medium++ <--> TF_Link <-->  F_32_1.medium++;
		T_32_2.medium++ <--> TF_Link <-->  F_32_2.medium++;
		T_32_2.medium++ <--> TF_Link <-->  F_32_3.medium++;
		T_32_3.medium++ <--> TF_Link <-->  F_32_0.medium++;
		T_32_3.medium++ <--> TF_Link <-->  F_32_1.medium++;
		T_32_3.medium++ <--> TF_Link <-->  F_32_2.medium++;
		T_32_3.medium++ <--> TF_Link <-->  F_32_3.medium++;
		T_32_4.medium++ <--> TF_Link <-->  F_32_0.medium++;
		T_32_4.medium++ <--> TF_Link <-->  F_32_1.medium++;
		T_32_4.medium++ <--> TF_Link <-->  F_32_2.medium++;
		T_32_4.medium++ <--> TF_Link <-->  F_32_3.medium++;
		T_33_0.medium++ <--> TF_Link <-->  F_33_0.medium++;
		T_33_0.medium++ <--> TF_Link <-->  F_33_1.medium++;
		T_33_0.medium++ <--> TF_Link <-->  F_33_2.medium++;
		T_33_0.medium++ <--> TF_Link <-->  F_33_3.medium++;
		T_33_1.medium++ <--> TF_Link <-->  F_33_0.medium++;
		T_33_1.medium++ <--> TF_Link <-->  F_33_1.medium++;
		T_33_1.medium++ <--> TF_Link <-->  F_33_2.medium++;
		T_33_1.medium++ <--> TF_Link <-->  F_33_3.medium++;
		T_33_2.medium++ <--> TF_Link <-->  F_33_0.medium++;
		T_33_2.medium++ <--> TF_Link <-->  F_33_1.medium++;
		T_33_2.medium++ <--> TF_Link <-->  F_33_2.medium++;
		T_33_2.medium++ <--> TF_Link <-->  F_33_3.medium++;
		T_33_3.medium++ <--> TF_Link <-->  F_33_0.medium++;
		T_33_3.medium++ <--> TF_Link <-->  F_33_1.medium++;
		T_33_3.medium++ <--> TF_Link <-->  F_33_2.medium++;
		T_33_3.medium++ <--> TF_Link <-->  F_33_3.medium++;
		T_33_4.medium++ <--> TF_Link <-->  F_33_0.medium++;
		T_33_4.medium++ <--> TF_Link <-->  F_33_1.medium++;
		T_33_4.medium++ <--> TF_Link <-->  F_33_2.medium++;
		T_33_4.medium++ <--> TF_Link <-->  F_33_3.medium++;
		T_34_0.medium++ <--> TF_Link <-->  F_34_0.medium++;
		T_34_0.medium++ <--> TF_Link <-->  F_34_1.medium++;
		T_34_0.medium++ <--> TF_Link <-->  F_34_2.medium++;
		T_34_0.medium++ <--> TF_Link <-->  F_34_3.medium++;
		T_34_1.medium++ <--> TF_Link <-->  F_34_0.medium++;
		T_34_1.medium++ <--> TF_Link <-->  F_34_1.medium++;
		T_34_1.medium++ <--> TF_Link <-->  F_34_2.medium++;
		T_34_1.medium++ <--> TF_Link <-->  F_34_3.medium++;
		T_34_2.medium++ <--> TF_Link <-->  F_34_0.medium++;
		T_34_2.medium++ <--> TF_Link <-->  F_34_1.medium++;
		T_34_2.medium++ <--> TF_Link <-->  F_34_2.medium++;
		T_34_2.medium++ <--> TF_Link <-->  F_34_3.medium++;
		T_34_3.medium++ <--> TF_Link <-->  F_34_0.medium++;
		T_34_3.medium++ <--> TF_Link <-->  F_34_1.medium++;
		T_34_3.medium++ <--> TF_Link <-->  F_34_2.medium++;
		T_34_3.medium++ <--> TF_Link <-->  F_34_3.medium++;
		T_34_4.medium++ <--> TF_Link <-->  F_34_0.medium++;
		T_34_4.medium++ <--> TF_Link <-->  F_34_1.medium++;
		T_34_4.medium++ <--> TF_Link <-->  F_34_2.medium++;
		T_34_4.medium++ <--> TF_Link <-->  F_34_3.medium++;
		T_35_0.medium++ <--> TF_Link <-->  F_35_0.medium++;
		T_35_0.medium++ <--> TF_Link <-->  F_35_1.medium++;
		T_35_0.medium++ <--> TF_Link <-->  F_35_2.medium++;
		T_35_0.medium++ <--> TF_Link <-->  F_35_3.medium++;
		T_35_1.medium++ <--> TF_Link <-->  F_35_0.medium++;
		T_35_1.medium++ <--> TF_Link <-->  F_35_1.medium++;
		T_35_1.medium++ <--> TF_Link <-->  F_35_2.medium++;
		T_35_1.medium++ <--> TF_Link <-->  F_35_3.medium++;
		T_35_2.medium++ <--> TF_Link <-->  F_35_0.medium++;
		T_35_2.medium++ <--> TF_Link <-->  F_35_1.medium++;
		T_35_2.medium++ <--> TF_Link <-->  F_35_2.medium++;
		T_35_2.medium++ <--> TF_Link <-->  F_35_3.medium++;
		T_35_3.medium++ <--> TF_Link <-->  F_35_0.medium++;
		T_35_3.medium++ <--> TF_Link <-->  F_35_1.medium++;
		T_35_3.medium++ <--> TF_Link <-->  F_35_2.medium++;
		T_35_3.medium++ <--> TF_Link <-->  F_35_3.medium++;
		T_35_4.medium++ <--> TF_Link <-->  F_35_0.medium++;
		T_35_4.medium++ <--> TF_Link <-->  F_35_1.medium++;
		T_35_4.medium++ <--> TF_Link <-->  F_35_2.medium++;
		T_35_4.medium++ <--> TF_Link <-->  F_35_3.medium++;
		T_36_0.medium++ <--> TF_Link <-->  F_36_0.medium++;
		T_36_0.medium++ <--> TF_Link <-->  F_36_1.medium++;
		T_36_0.medium++ <--> TF_Link <-->  F_36_2.medium++;
		T_36_0.medium++ <--> TF_Link <-->  F_36_3.medium++;
		T_36_1.medium++ <--> TF_Link <-->  F_36_0.medium++;
		T_36_1.medium++ <--> TF_Link <-->  F_36_1.medium++;
		T_36_1.medium++ <--> TF_Link <-->  F_36_2.medium++;
		T_36_1.medium++ <--> TF_Link <-->  F_36_3.medium++;
		T_36_2.medium++ <--> TF_Link <-->  F_36_0.medium++;
		T_36_2.medium++ <--> TF_Link <-->  F_36_1.medium++;
		T_36_2.medium++ <--> TF_Link <-->  F_36_2.medium++;
		T_36_2.medium++ <--> TF_Link <-->  F_36_3.medium++;
		T_36_3.medium++ <--> TF_Link <-->  F_36_0.medium++;
		T_36_3.medium++ <--> TF_Link <-->  F_36_1.medium++;
		T_36_3.medium++ <--> TF_Link <-->  F_36_2.medium++;
		T_36_3.medium++ <--> TF_Link <-->  F_36_3.medium++;
		T_36_4.medium++ <--> TF_Link <-->  F_36_0.medium++;
		T_36_4.medium++ <--> TF_Link <-->  F_36_1.medium++;
		T_36_4.medium++ <--> TF_Link <-->  F_36_2.medium++;
		T_36_4.medium++ <--> TF_Link <-->  F_36_3.medium++;
		T_37_0.medium++ <--> TF_Link <-->  F_37_0.medium++;
		T_37_0.medium++ <--> TF_Link <-->  F_37_1.medium++;
		T_37_0.medium++ <--> TF_Link <-->  F_37_2.medium++;
		T_37_0.medium++ <--> TF_Link <-->  F_37_3.medium++;
		T_37_1.medium++ <--> TF_Link <-->  F_37_0.medium++;
		T_37_1.medium++ <--> TF_Link <-->  F_37_1.medium++;
		T_37_1.medium++ <--> TF_Link <-->  F_37_2.medium++;
		T_37_1.medium++ <--> TF_Link <-->  F_37_3.medium++;
		T_37_2.medium++ <--> TF_Link <-->  F_37_0.medium++;
		T_37_2.medium++ <--> TF_Link <-->  F_37_1.medium++;
		T_37_2.medium++ <--> TF_Link <-->  F_37_2.medium++;
		T_37_2.medium++ <--> TF_Link <-->  F_37_3.medium++;
		T_37_3.medium++ <--> TF_Link <-->  F_37_0.medium++;
		T_37_3.medium++ <--> TF_Link <-->  F_37_1.medium++;
		T_37_3.medium++ <--> TF_Link <-->  F_37_2.medium++;
		T_37_3.medium++ <--> TF_Link <-->  F_37_3.medium++;
		T_37_4.medium++ <--> TF_Link <-->  F_37_0.medium++;
		T_37_4.medium++ <--> TF_Link <-->  F_37_1.medium++;
		T_37_4.medium++ <--> TF_Link <-->  F_37_2.medium++;
		T_37_4.medium++ <--> TF_Link <-->  F_37_3.medium++;
		T_38_0.medium++ <--> TF_Link <-->  F_38_0.medium++;
		T_38_0.medium++ <--> TF_Link <-->  F_38_1.medium++;
		T_38_0.medium++ <--> TF_Link <-->  F_38_2.medium++;
		T_38_0.medium++ <--> TF_Link <-->  F_38_3.medium++;
		T_38_1.medium++ <--> TF_Link <-->  F_38_0.medium++;
		T_38_1.medium++ <--> TF_Link <-->  F_38_1.medium++;
		T_38_1.medium++ <--> TF_Link <-->  F_38_2.medium++;
		T_38_1.medium++ <--> TF_Link <-->  F_38_3.medium++;
		T_38_2.medium++ <--> TF_Link <-->  F_38_0.medium++;
		T_38_2.medium++ <--> TF_Link <-->  F_38_1.medium++;
		T_38_2.medium++ <--> TF_Link <-->  F_38_2.medium++;
		T_38_2.medium++ <--> TF_Link <-->  F_38_3.medium++;
		T_38_3.medium++ <--> TF_Link <-->  F_38_0.medium++;
		T_38_3.medium++ <--> TF_Link <-->  F_38_1.medium++;
		T_38_3.medium++ <--> TF_Link <-->  F_38_2.medium++;
		T_38_3.medium++ <--> TF_Link <-->  F_38_3.medium++;
		T_38_4.medium++ <--> TF_Link <-->  F_38_0.medium++;
		T_38_4.medium++ <--> TF_Link <-->  F_38_1.medium++;
		T_38_4.medium++ <--> TF_Link <-->  F_38_2.medium++;
		T_38_4.medium++ <--> TF_Link <-->  F_38_3.medium++;
		T_39_0.medium++ <--> TF_Link <-->  F_39_0.medium++;
		T_39_0.medium++ <--> TF_Link <-->  F_39_1.medium++;
		T_39_0.medium++ <--> TF_Link <-->  F_39_2.medium++;
		T_39_0.medium++ <--> TF_Link <-->  F_39_3.medium++;
		T_39_1.medium++ <--> TF_Link <-->  F_39_0.medium++;
		T_39_1.medium++ <--> TF_Link <-->  F_39_1.medium++;
		T_39_1.medium++ <--> TF_Link <-->  F_39_2.medium++;
		T_39_1.medium++ <--> TF_Link <-->  F_39_3.medium++;
		T_39_2.medium++ <--> TF_Link <-->  F_39_0.medium++;
		T_39_2.medium++ <--> TF_Link <-->  F_39_1.medium++;
		T_39_2.medium++ <--> TF_Link <-->  F_39_2.medium++;
		T_39_2.medium++ <--> TF_Link <-->  F_39_3.medium++;
		T_39_3.medium++ <--> TF_Link <-->  F_39_0.medium++;
		T_39_3.medium++ <--> TF_Link <-->  F_39_1.medium++;
		T_39_3.medium++ <--> TF_Link <-->  F_39_2.medium++;
		T_39_3.medium++ <--> TF_Link <-->  F_39_3.medium++;
		T_39_4.medium++ <--> TF_Link <-->  F_39_0.medium++;
		T_39_4.medium++ <--> TF_Link <-->  F_39_1.medium++;
		T_39_4.medium++ <--> TF_Link <-->  F_39_2.medium++;
		T_39_4.medium++ <--> TF_Link <-->  F_39_3.medium++;

		F_0_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_0_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_0_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_0_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_0_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_0_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_0_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_0_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_0_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_0_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_0_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_0_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_0_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_0_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_0_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_0_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_0_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_0_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_0_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_0_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_0_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_0_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_0_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_0_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_0_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_0_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_0_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_0_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_0_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_0_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_0_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_0_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_0_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_0_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_0_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_0_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_0_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_0_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_0_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_0_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_1_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_1_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_1_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_1_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_1_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_1_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_1_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_1_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_1_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_1_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_1_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_1_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_1_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_1_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_1_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_1_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_1_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_1_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_1_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_1_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_1_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_1_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_1_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_1_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_1_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_1_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_1_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_1_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_1_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_1_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_1_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_1_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_1_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_1_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_1_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_1_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_1_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_1_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_1_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_1_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_2_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_2_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_2_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_2_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_2_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_2_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_2_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_2_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_2_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_2_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_2_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_2_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_2_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_2_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_2_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_2_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_2_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_2_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_2_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_2_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_2_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_2_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_2_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_2_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_2_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_2_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_2_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_2_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_2_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_2_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_2_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_2_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_2_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_2_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_2_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_2_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_2_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_2_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_2_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_2_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_3_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_3_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_3_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_3_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_3_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_3_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_3_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_3_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_3_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_3_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_3_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_3_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_3_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_3_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_3_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_3_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_3_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_3_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_3_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_3_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_3_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_3_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_3_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_3_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_3_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_3_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_3_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_3_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_3_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_3_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_3_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_3_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_3_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_3_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_3_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_3_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_3_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_3_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_3_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_3_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_4_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_4_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_4_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_4_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_4_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_4_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_4_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_4_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_4_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_4_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_4_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_4_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_4_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_4_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_4_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_4_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_4_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_4_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_4_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_4_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_4_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_4_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_4_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_4_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_4_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_4_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_4_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_4_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_4_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_4_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_4_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_4_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_4_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_4_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_4_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_4_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_4_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_4_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_4_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_4_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_5_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_5_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_5_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_5_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_5_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_5_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_5_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_5_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_5_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_5_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_5_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_5_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_5_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_5_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_5_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_5_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_5_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_5_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_5_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_5_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_5_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_5_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_5_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_5_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_5_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_5_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_5_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_5_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_5_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_5_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_5_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_5_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_5_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_5_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_5_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_5_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_5_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_5_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_5_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_5_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_6_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_6_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_6_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_6_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_6_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_6_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_6_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_6_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_6_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_6_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_6_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_6_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_6_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_6_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_6_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_6_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_6_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_6_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_6_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_6_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_6_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_6_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_6_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_6_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_6_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_6_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_6_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_6_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_6_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_6_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_6_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_6_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_6_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_6_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_6_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_6_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_6_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_6_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_6_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_6_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_7_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_7_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_7_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_7_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_7_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_7_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_7_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_7_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_7_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_7_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_7_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_7_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_7_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_7_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_7_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_7_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_7_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_7_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_7_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_7_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_7_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_7_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_7_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_7_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_7_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_7_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_7_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_7_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_7_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_7_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_7_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_7_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_7_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_7_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_7_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_7_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_7_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_7_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_7_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_7_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_8_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_8_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_8_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_8_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_8_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_8_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_8_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_8_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_8_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_8_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_8_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_8_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_8_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_8_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_8_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_8_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_8_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_8_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_8_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_8_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_8_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_8_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_8_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_8_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_8_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_8_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_8_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_8_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_8_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_8_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_8_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_8_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_8_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_8_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_8_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_8_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_8_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_8_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_8_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_8_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_9_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_9_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_9_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_9_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_9_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_9_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_9_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_9_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_9_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_9_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_9_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_9_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_9_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_9_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_9_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_9_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_9_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_9_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_9_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_9_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_9_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_9_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_9_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_9_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_9_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_9_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_9_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_9_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_9_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_9_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_9_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_9_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_9_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_9_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_9_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_9_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_9_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_9_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_9_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_9_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_10_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_10_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_10_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_10_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_10_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_10_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_10_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_10_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_10_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_10_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_10_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_10_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_10_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_10_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_10_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_10_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_10_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_10_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_10_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_10_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_10_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_10_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_10_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_10_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_10_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_10_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_10_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_10_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_10_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_10_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_10_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_10_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_10_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_10_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_10_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_10_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_10_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_10_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_10_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_10_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_11_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_11_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_11_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_11_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_11_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_11_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_11_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_11_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_11_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_11_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_11_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_11_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_11_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_11_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_11_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_11_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_11_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_11_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_11_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_11_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_11_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_11_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_11_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_11_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_11_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_11_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_11_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_11_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_11_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_11_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_11_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_11_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_11_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_11_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_11_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_11_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_11_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_11_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_11_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_11_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_12_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_12_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_12_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_12_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_12_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_12_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_12_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_12_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_12_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_12_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_12_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_12_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_12_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_12_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_12_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_12_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_12_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_12_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_12_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_12_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_12_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_12_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_12_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_12_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_12_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_12_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_12_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_12_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_12_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_12_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_12_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_12_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_12_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_12_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_12_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_12_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_12_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_12_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_12_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_12_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_13_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_13_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_13_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_13_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_13_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_13_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_13_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_13_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_13_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_13_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_13_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_13_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_13_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_13_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_13_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_13_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_13_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_13_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_13_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_13_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_13_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_13_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_13_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_13_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_13_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_13_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_13_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_13_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_13_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_13_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_13_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_13_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_13_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_13_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_13_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_13_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_13_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_13_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_13_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_13_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_14_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_14_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_14_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_14_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_14_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_14_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_14_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_14_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_14_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_14_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_14_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_14_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_14_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_14_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_14_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_14_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_14_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_14_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_14_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_14_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_14_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_14_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_14_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_14_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_14_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_14_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_14_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_14_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_14_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_14_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_14_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_14_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_14_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_14_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_14_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_14_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_14_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_14_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_14_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_14_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_15_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_15_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_15_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_15_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_15_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_15_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_15_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_15_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_15_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_15_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_15_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_15_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_15_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_15_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_15_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_15_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_15_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_15_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_15_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_15_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_15_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_15_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_15_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_15_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_15_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_15_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_15_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_15_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_15_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_15_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_15_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_15_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_15_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_15_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_15_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_15_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_15_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_15_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_15_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_15_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_16_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_16_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_16_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_16_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_16_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_16_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_16_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_16_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_16_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_16_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_16_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_16_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_16_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_16_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_16_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_16_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_16_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_16_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_16_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_16_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_16_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_16_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_16_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_16_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_16_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_16_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_16_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_16_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_16_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_16_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_16_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_16_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_16_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_16_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_16_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_16_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_16_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_16_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_16_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_16_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_17_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_17_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_17_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_17_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_17_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_17_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_17_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_17_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_17_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_17_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_17_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_17_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_17_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_17_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_17_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_17_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_17_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_17_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_17_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_17_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_17_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_17_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_17_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_17_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_17_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_17_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_17_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_17_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_17_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_17_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_17_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_17_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_17_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_17_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_17_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_17_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_17_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_17_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_17_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_17_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_18_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_18_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_18_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_18_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_18_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_18_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_18_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_18_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_18_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_18_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_18_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_18_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_18_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_18_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_18_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_18_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_18_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_18_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_18_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_18_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_18_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_18_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_18_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_18_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_18_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_18_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_18_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_18_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_18_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_18_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_18_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_18_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_18_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_18_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_18_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_18_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_18_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_18_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_18_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_18_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_19_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_19_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_19_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_19_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_19_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_19_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_19_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_19_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_19_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_19_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_19_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_19_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_19_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_19_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_19_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_19_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_19_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_19_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_19_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_19_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_19_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_19_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_19_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_19_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_19_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_19_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_19_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_19_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_19_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_19_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_19_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_19_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_19_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_19_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_19_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_19_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_19_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_19_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_19_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_19_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_20_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_20_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_20_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_20_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_20_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_20_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_20_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_20_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_20_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_20_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_20_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_20_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_20_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_20_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_20_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_20_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_20_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_20_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_20_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_20_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_20_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_20_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_20_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_20_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_20_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_20_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_20_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_20_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_20_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_20_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_20_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_20_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_20_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_20_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_20_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_20_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_20_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_20_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_20_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_20_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_21_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_21_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_21_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_21_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_21_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_21_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_21_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_21_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_21_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_21_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_21_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_21_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_21_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_21_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_21_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_21_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_21_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_21_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_21_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_21_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_21_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_21_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_21_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_21_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_21_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_21_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_21_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_21_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_21_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_21_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_21_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_21_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_21_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_21_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_21_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_21_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_21_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_21_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_21_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_21_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_22_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_22_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_22_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_22_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_22_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_22_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_22_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_22_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_22_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_22_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_22_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_22_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_22_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_22_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_22_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_22_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_22_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_22_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_22_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_22_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_22_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_22_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_22_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_22_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_22_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_22_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_22_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_22_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_22_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_22_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_22_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_22_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_22_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_22_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_22_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_22_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_22_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_22_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_22_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_22_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_23_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_23_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_23_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_23_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_23_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_23_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_23_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_23_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_23_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_23_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_23_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_23_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_23_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_23_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_23_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_23_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_23_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_23_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_23_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_23_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_23_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_23_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_23_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_23_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_23_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_23_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_23_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_23_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_23_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_23_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_23_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_23_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_23_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_23_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_23_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_23_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_23_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_23_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_23_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_23_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_24_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_24_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_24_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_24_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_24_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_24_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_24_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_24_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_24_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_24_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_24_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_24_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_24_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_24_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_24_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_24_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_24_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_24_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_24_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_24_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_24_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_24_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_24_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_24_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_24_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_24_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_24_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_24_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_24_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_24_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_24_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_24_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_24_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_24_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_24_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_24_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_24_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_24_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_24_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_24_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_25_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_25_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_25_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_25_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_25_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_25_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_25_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_25_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_25_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_25_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_25_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_25_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_25_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_25_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_25_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_25_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_25_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_25_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_25_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_25_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_25_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_25_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_25_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_25_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_25_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_25_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_25_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_25_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_25_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_25_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_25_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_25_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_25_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_25_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_25_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_25_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_25_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_25_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_25_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_25_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_26_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_26_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_26_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_26_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_26_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_26_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_26_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_26_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_26_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_26_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_26_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_26_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_26_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_26_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_26_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_26_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_26_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_26_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_26_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_26_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_26_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_26_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_26_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_26_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_26_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_26_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_26_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_26_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_26_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_26_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_26_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_26_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_26_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_26_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_26_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_26_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_26_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_26_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_26_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_26_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_27_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_27_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_27_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_27_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_27_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_27_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_27_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_27_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_27_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_27_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_27_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_27_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_27_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_27_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_27_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_27_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_27_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_27_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_27_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_27_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_27_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_27_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_27_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_27_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_27_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_27_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_27_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_27_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_27_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_27_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_27_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_27_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_27_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_27_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_27_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_27_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_27_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_27_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_27_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_27_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_28_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_28_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_28_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_28_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_28_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_28_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_28_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_28_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_28_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_28_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_28_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_28_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_28_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_28_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_28_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_28_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_28_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_28_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_28_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_28_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_28_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_28_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_28_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_28_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_28_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_28_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_28_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_28_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_28_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_28_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_28_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_28_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_28_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_28_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_28_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_28_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_28_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_28_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_28_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_28_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_29_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_29_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_29_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_29_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_29_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_29_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_29_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_29_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_29_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_29_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_29_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_29_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_29_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_29_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_29_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_29_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_29_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_29_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_29_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_29_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_29_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_29_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_29_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_29_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_29_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_29_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_29_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_29_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_29_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_29_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_29_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_29_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_29_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_29_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_29_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_29_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_29_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_29_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_29_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_29_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_30_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_30_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_30_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_30_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_30_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_30_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_30_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_30_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_30_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_30_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_30_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_30_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_30_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_30_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_30_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_30_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_30_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_30_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_30_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_30_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_30_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_30_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_30_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_30_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_30_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_30_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_30_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_30_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_30_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_30_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_30_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_30_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_30_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_30_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_30_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_30_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_30_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_30_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_30_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_30_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_31_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_31_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_31_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_31_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_31_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_31_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_31_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_31_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_31_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_31_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_31_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_31_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_31_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_31_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_31_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_31_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_31_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_31_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_31_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_31_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_31_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_31_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_31_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_31_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_31_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_31_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_31_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_31_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_31_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_31_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_31_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_31_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_31_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_31_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_31_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_31_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_31_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_31_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_31_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_31_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_32_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_32_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_32_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_32_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_32_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_32_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_32_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_32_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_32_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_32_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_32_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_32_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_32_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_32_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_32_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_32_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_32_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_32_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_32_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_32_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_32_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_32_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_32_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_32_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_32_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_32_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_32_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_32_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_32_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_32_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_32_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_32_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_32_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_32_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_32_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_32_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_32_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_32_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_32_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_32_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_33_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_33_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_33_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_33_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_33_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_33_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_33_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_33_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_33_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_33_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_33_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_33_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_33_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_33_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_33_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_33_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_33_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_33_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_33_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_33_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_33_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_33_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_33_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_33_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_33_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_33_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_33_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_33_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_33_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_33_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_33_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_33_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_33_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_33_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_33_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_33_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_33_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_33_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_33_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_33_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_34_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_34_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_34_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_34_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_34_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_34_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_34_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_34_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_34_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_34_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_34_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_34_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_34_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_34_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_34_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_34_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_34_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_34_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_34_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_34_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_34_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_34_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_34_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_34_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_34_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_34_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_34_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_34_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_34_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_34_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_34_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_34_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_34_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_34_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_34_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_34_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_34_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_34_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_34_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_34_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_35_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_35_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_35_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_35_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_35_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_35_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_35_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_35_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_35_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_35_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_35_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_35_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_35_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_35_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_35_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_35_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_35_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_35_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_35_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_35_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_35_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_35_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_35_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_35_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_35_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_35_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_35_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_35_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_35_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_35_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_35_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_35_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_35_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_35_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_35_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_35_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_35_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_35_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_35_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_35_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_36_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_36_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_36_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_36_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_36_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_36_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_36_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_36_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_36_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_36_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_36_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_36_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_36_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_36_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_36_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_36_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_36_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_36_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_36_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_36_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_36_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_36_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_36_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_36_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_36_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_36_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_36_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_36_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_36_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_36_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_36_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_36_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_36_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_36_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_36_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_36_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_36_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_36_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_36_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_36_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_37_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_37_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_37_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_37_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_37_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_37_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_37_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_37_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_37_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_37_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_37_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_37_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_37_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_37_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_37_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_37_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_37_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_37_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_37_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_37_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_37_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_37_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_37_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_37_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_37_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_37_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_37_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_37_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_37_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_37_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_37_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_37_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_37_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_37_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_37_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_37_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_37_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_37_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_37_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_37_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_38_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_38_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_38_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_38_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_38_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_38_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_38_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_38_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_38_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_38_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_38_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_38_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_38_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_38_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_38_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_38_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_38_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_38_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_38_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_38_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_38_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_38_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_38_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_38_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_38_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_38_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_38_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_38_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_38_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_38_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_38_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_38_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_38_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_38_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_38_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_38_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_38_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_38_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_38_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_38_3.medium++ <--> FS_Link <-->  S_3_9.medium++;
		F_39_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_39_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_39_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_39_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_39_0.medium++ <--> FS_Link <-->  S_0_4.medium++;
		F_39_0.medium++ <--> FS_Link <-->  S_0_5.medium++;
		F_39_0.medium++ <--> FS_Link <-->  S_0_6.medium++;
		F_39_0.medium++ <--> FS_Link <-->  S_0_7.medium++;
		F_39_0.medium++ <--> FS_Link <-->  S_0_8.medium++;
		F_39_0.medium++ <--> FS_Link <-->  S_0_9.medium++;
		F_39_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_39_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_39_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_39_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_39_1.medium++ <--> FS_Link <-->  S_1_4.medium++;
		F_39_1.medium++ <--> FS_Link <-->  S_1_5.medium++;
		F_39_1.medium++ <--> FS_Link <-->  S_1_6.medium++;
		F_39_1.medium++ <--> FS_Link <-->  S_1_7.medium++;
		F_39_1.medium++ <--> FS_Link <-->  S_1_8.medium++;
		F_39_1.medium++ <--> FS_Link <-->  S_1_9.medium++;
		F_39_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_39_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_39_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_39_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_39_2.medium++ <--> FS_Link <-->  S_2_4.medium++;
		F_39_2.medium++ <--> FS_Link <-->  S_2_5.medium++;
		F_39_2.medium++ <--> FS_Link <-->  S_2_6.medium++;
		F_39_2.medium++ <--> FS_Link <-->  S_2_7.medium++;
		F_39_2.medium++ <--> FS_Link <-->  S_2_8.medium++;
		F_39_2.medium++ <--> FS_Link <-->  S_2_9.medium++;
		F_39_3.medium++ <--> FS_Link <-->  S_3_0.medium++;
		F_39_3.medium++ <--> FS_Link <-->  S_3_1.medium++;
		F_39_3.medium++ <--> FS_Link <-->  S_3_2.medium++;
		F_39_3.medium++ <--> FS_Link <-->  S_3_3.medium++;
		F_39_3.medium++ <--> FS_Link <-->  S_3_4.medium++;
		F_39_3.medium++ <--> FS_Link <-->  S_3_5.medium++;
		F_39_3.medium++ <--> FS_Link <-->  S_3_6.medium++;
		F_39_3.medium++ <--> FS_Link <-->  S_3_7.medium++;
		F_39_3.medium++ <--> FS_Link <-->  S_3_8.medium++;
		F_39_3.medium++ <--> FS_Link <-->  S_3_9.medium++;

		E_0_0.medium++ <--> ES_Link <-->  S_0_0.medium++;
		E_0_0.medium++ <--> ES_Link <-->  S_0_1.medium++;
		E_0_0.medium++ <--> ES_Link <-->  S_0_2.medium++;
		E_0_0.medium++ <--> ES_Link <-->  S_0_3.medium++;
		E_0_0.medium++ <--> ES_Link <-->  S_0_4.medium++;
		E_0_0.medium++ <--> ES_Link <-->  S_0_5.medium++;
		E_0_0.medium++ <--> ES_Link <-->  S_0_6.medium++;
		E_0_0.medium++ <--> ES_Link <-->  S_0_7.medium++;
		E_0_0.medium++ <--> ES_Link <-->  S_0_8.medium++;
		E_0_0.medium++ <--> ES_Link <-->  S_0_9.medium++;
		E_0_1.medium++ <--> ES_Link <-->  S_1_0.medium++;
		E_0_1.medium++ <--> ES_Link <-->  S_1_1.medium++;
		E_0_1.medium++ <--> ES_Link <-->  S_1_2.medium++;
		E_0_1.medium++ <--> ES_Link <-->  S_1_3.medium++;
		E_0_1.medium++ <--> ES_Link <-->  S_1_4.medium++;
		E_0_1.medium++ <--> ES_Link <-->  S_1_5.medium++;
		E_0_1.medium++ <--> ES_Link <-->  S_1_6.medium++;
		E_0_1.medium++ <--> ES_Link <-->  S_1_7.medium++;
		E_0_1.medium++ <--> ES_Link <-->  S_1_8.medium++;
		E_0_1.medium++ <--> ES_Link <-->  S_1_9.medium++;
		E_0_2.medium++ <--> ES_Link <-->  S_2_0.medium++;
		E_0_2.medium++ <--> ES_Link <-->  S_2_1.medium++;
		E_0_2.medium++ <--> ES_Link <-->  S_2_2.medium++;
		E_0_2.medium++ <--> ES_Link <-->  S_2_3.medium++;
		E_0_2.medium++ <--> ES_Link <-->  S_2_4.medium++;
		E_0_2.medium++ <--> ES_Link <-->  S_2_5.medium++;
		E_0_2.medium++ <--> ES_Link <-->  S_2_6.medium++;
		E_0_2.medium++ <--> ES_Link <-->  S_2_7.medium++;
		E_0_2.medium++ <--> ES_Link <-->  S_2_8.medium++;
		E_0_2.medium++ <--> ES_Link <-->  S_2_9.medium++;
		E_0_3.medium++ <--> ES_Link <-->  S_3_0.medium++;
		E_0_3.medium++ <--> ES_Link <-->  S_3_1.medium++;
		E_0_3.medium++ <--> ES_Link <-->  S_3_2.medium++;
		E_0_3.medium++ <--> ES_Link <-->  S_3_3.medium++;
		E_0_3.medium++ <--> ES_Link <-->  S_3_4.medium++;
		E_0_3.medium++ <--> ES_Link <-->  S_3_5.medium++;
		E_0_3.medium++ <--> ES_Link <-->  S_3_6.medium++;
		E_0_3.medium++ <--> ES_Link <-->  S_3_7.medium++;
		E_0_3.medium++ <--> ES_Link <-->  S_3_8.medium++;
		E_0_3.medium++ <--> ES_Link <-->  S_3_9.medium++;
		E_1_0.medium++ <--> ES_Link <-->  S_0_0.medium++;
		E_1_0.medium++ <--> ES_Link <-->  S_0_1.medium++;
		E_1_0.medium++ <--> ES_Link <-->  S_0_2.medium++;
		E_1_0.medium++ <--> ES_Link <-->  S_0_3.medium++;
		E_1_0.medium++ <--> ES_Link <-->  S_0_4.medium++;
		E_1_0.medium++ <--> ES_Link <-->  S_0_5.medium++;
		E_1_0.medium++ <--> ES_Link <-->  S_0_6.medium++;
		E_1_0.medium++ <--> ES_Link <-->  S_0_7.medium++;
		E_1_0.medium++ <--> ES_Link <-->  S_0_8.medium++;
		E_1_0.medium++ <--> ES_Link <-->  S_0_9.medium++;
		E_1_1.medium++ <--> ES_Link <-->  S_1_0.medium++;
		E_1_1.medium++ <--> ES_Link <-->  S_1_1.medium++;
		E_1_1.medium++ <--> ES_Link <-->  S_1_2.medium++;
		E_1_1.medium++ <--> ES_Link <-->  S_1_3.medium++;
		E_1_1.medium++ <--> ES_Link <-->  S_1_4.medium++;
		E_1_1.medium++ <--> ES_Link <-->  S_1_5.medium++;
		E_1_1.medium++ <--> ES_Link <-->  S_1_6.medium++;
		E_1_1.medium++ <--> ES_Link <-->  S_1_7.medium++;
		E_1_1.medium++ <--> ES_Link <-->  S_1_8.medium++;
		E_1_1.medium++ <--> ES_Link <-->  S_1_9.medium++;
		E_1_2.medium++ <--> ES_Link <-->  S_2_0.medium++;
		E_1_2.medium++ <--> ES_Link <-->  S_2_1.medium++;
		E_1_2.medium++ <--> ES_Link <-->  S_2_2.medium++;
		E_1_2.medium++ <--> ES_Link <-->  S_2_3.medium++;
		E_1_2.medium++ <--> ES_Link <-->  S_2_4.medium++;
		E_1_2.medium++ <--> ES_Link <-->  S_2_5.medium++;
		E_1_2.medium++ <--> ES_Link <-->  S_2_6.medium++;
		E_1_2.medium++ <--> ES_Link <-->  S_2_7.medium++;
		E_1_2.medium++ <--> ES_Link <-->  S_2_8.medium++;
		E_1_2.medium++ <--> ES_Link <-->  S_2_9.medium++;
		E_1_3.medium++ <--> ES_Link <-->  S_3_0.medium++;
		E_1_3.medium++ <--> ES_Link <-->  S_3_1.medium++;
		E_1_3.medium++ <--> ES_Link <-->  S_3_2.medium++;
		E_1_3.medium++ <--> ES_Link <-->  S_3_3.medium++;
		E_1_3.medium++ <--> ES_Link <-->  S_3_4.medium++;
		E_1_3.medium++ <--> ES_Link <-->  S_3_5.medium++;
		E_1_3.medium++ <--> ES_Link <-->  S_3_6.medium++;
		E_1_3.medium++ <--> ES_Link <-->  S_3_7.medium++;
		E_1_3.medium++ <--> ES_Link <-->  S_3_8.medium++;
		E_1_3.medium++ <--> ES_Link <-->  S_3_9.medium++;
		E_2_0.medium++ <--> ES_Link <-->  S_0_0.medium++;
		E_2_0.medium++ <--> ES_Link <-->  S_0_1.medium++;
		E_2_0.medium++ <--> ES_Link <-->  S_0_2.medium++;
		E_2_0.medium++ <--> ES_Link <-->  S_0_3.medium++;
		E_2_0.medium++ <--> ES_Link <-->  S_0_4.medium++;
		E_2_0.medium++ <--> ES_Link <-->  S_0_5.medium++;
		E_2_0.medium++ <--> ES_Link <-->  S_0_6.medium++;
		E_2_0.medium++ <--> ES_Link <-->  S_0_7.medium++;
		E_2_0.medium++ <--> ES_Link <-->  S_0_8.medium++;
		E_2_0.medium++ <--> ES_Link <-->  S_0_9.medium++;
		E_2_1.medium++ <--> ES_Link <-->  S_1_0.medium++;
		E_2_1.medium++ <--> ES_Link <-->  S_1_1.medium++;
		E_2_1.medium++ <--> ES_Link <-->  S_1_2.medium++;
		E_2_1.medium++ <--> ES_Link <-->  S_1_3.medium++;
		E_2_1.medium++ <--> ES_Link <-->  S_1_4.medium++;
		E_2_1.medium++ <--> ES_Link <-->  S_1_5.medium++;
		E_2_1.medium++ <--> ES_Link <-->  S_1_6.medium++;
		E_2_1.medium++ <--> ES_Link <-->  S_1_7.medium++;
		E_2_1.medium++ <--> ES_Link <-->  S_1_8.medium++;
		E_2_1.medium++ <--> ES_Link <-->  S_1_9.medium++;
		E_2_2.medium++ <--> ES_Link <-->  S_2_0.medium++;
		E_2_2.medium++ <--> ES_Link <-->  S_2_1.medium++;
		E_2_2.medium++ <--> ES_Link <-->  S_2_2.medium++;
		E_2_2.medium++ <--> ES_Link <-->  S_2_3.medium++;
		E_2_2.medium++ <--> ES_Link <-->  S_2_4.medium++;
		E_2_2.medium++ <--> ES_Link <-->  S_2_5.medium++;
		E_2_2.medium++ <--> ES_Link <-->  S_2_6.medium++;
		E_2_2.medium++ <--> ES_Link <-->  S_2_7.medium++;
		E_2_2.medium++ <--> ES_Link <-->  S_2_8.medium++;
		E_2_2.medium++ <--> ES_Link <-->  S_2_9.medium++;
		E_2_3.medium++ <--> ES_Link <-->  S_3_0.medium++;
		E_2_3.medium++ <--> ES_Link <-->  S_3_1.medium++;
		E_2_3.medium++ <--> ES_Link <-->  S_3_2.medium++;
		E_2_3.medium++ <--> ES_Link <-->  S_3_3.medium++;
		E_2_3.medium++ <--> ES_Link <-->  S_3_4.medium++;
		E_2_3.medium++ <--> ES_Link <-->  S_3_5.medium++;
		E_2_3.medium++ <--> ES_Link <-->  S_3_6.medium++;
		E_2_3.medium++ <--> ES_Link <-->  S_3_7.medium++;
		E_2_3.medium++ <--> ES_Link <-->  S_3_8.medium++;
		E_2_3.medium++ <--> ES_Link <-->  S_3_9.medium++;
		E_3_0.medium++ <--> ES_Link <-->  S_0_0.medium++;
		E_3_0.medium++ <--> ES_Link <-->  S_0_1.medium++;
		E_3_0.medium++ <--> ES_Link <-->  S_0_2.medium++;
		E_3_0.medium++ <--> ES_Link <-->  S_0_3.medium++;
		E_3_0.medium++ <--> ES_Link <-->  S_0_4.medium++;
		E_3_0.medium++ <--> ES_Link <-->  S_0_5.medium++;
		E_3_0.medium++ <--> ES_Link <-->  S_0_6.medium++;
		E_3_0.medium++ <--> ES_Link <-->  S_0_7.medium++;
		E_3_0.medium++ <--> ES_Link <-->  S_0_8.medium++;
		E_3_0.medium++ <--> ES_Link <-->  S_0_9.medium++;
		E_3_1.medium++ <--> ES_Link <-->  S_1_0.medium++;
		E_3_1.medium++ <--> ES_Link <-->  S_1_1.medium++;
		E_3_1.medium++ <--> ES_Link <-->  S_1_2.medium++;
		E_3_1.medium++ <--> ES_Link <-->  S_1_3.medium++;
		E_3_1.medium++ <--> ES_Link <-->  S_1_4.medium++;
		E_3_1.medium++ <--> ES_Link <-->  S_1_5.medium++;
		E_3_1.medium++ <--> ES_Link <-->  S_1_6.medium++;
		E_3_1.medium++ <--> ES_Link <-->  S_1_7.medium++;
		E_3_1.medium++ <--> ES_Link <-->  S_1_8.medium++;
		E_3_1.medium++ <--> ES_Link <-->  S_1_9.medium++;
		E_3_2.medium++ <--> ES_Link <-->  S_2_0.medium++;
		E_3_2.medium++ <--> ES_Link <-->  S_2_1.medium++;
		E_3_2.medium++ <--> ES_Link <-->  S_2_2.medium++;
		E_3_2.medium++ <--> ES_Link <-->  S_2_3.medium++;
		E_3_2.medium++ <--> ES_Link <-->  S_2_4.medium++;
		E_3_2.medium++ <--> ES_Link <-->  S_2_5.medium++;
		E_3_2.medium++ <--> ES_Link <-->  S_2_6.medium++;
		E_3_2.medium++ <--> ES_Link <-->  S_2_7.medium++;
		E_3_2.medium++ <--> ES_Link <-->  S_2_8.medium++;
		E_3_2.medium++ <--> ES_Link <-->  S_2_9.medium++;
		E_3_3.medium++ <--> ES_Link <-->  S_3_0.medium++;
		E_3_3.medium++ <--> ES_Link <-->  S_3_1.medium++;
		E_3_3.medium++ <--> ES_Link <-->  S_3_2.medium++;
		E_3_3.medium++ <--> ES_Link <-->  S_3_3.medium++;
		E_3_3.medium++ <--> ES_Link <-->  S_3_4.medium++;
		E_3_3.medium++ <--> ES_Link <-->  S_3_5.medium++;
		E_3_3.medium++ <--> ES_Link <-->  S_3_6.medium++;
		E_3_3.medium++ <--> ES_Link <-->  S_3_7.medium++;
		E_3_3.medium++ <--> ES_Link <-->  S_3_8.medium++;
		E_3_3.medium++ <--> ES_Link <-->  S_3_9.medium++;
		E_4_0.medium++ <--> ES_Link <-->  S_0_0.medium++;
		E_4_0.medium++ <--> ES_Link <-->  S_0_1.medium++;
		E_4_0.medium++ <--> ES_Link <-->  S_0_2.medium++;
		E_4_0.medium++ <--> ES_Link <-->  S_0_3.medium++;
		E_4_0.medium++ <--> ES_Link <-->  S_0_4.medium++;
		E_4_0.medium++ <--> ES_Link <-->  S_0_5.medium++;
		E_4_0.medium++ <--> ES_Link <-->  S_0_6.medium++;
		E_4_0.medium++ <--> ES_Link <-->  S_0_7.medium++;
		E_4_0.medium++ <--> ES_Link <-->  S_0_8.medium++;
		E_4_0.medium++ <--> ES_Link <-->  S_0_9.medium++;
		E_4_1.medium++ <--> ES_Link <-->  S_1_0.medium++;
		E_4_1.medium++ <--> ES_Link <-->  S_1_1.medium++;
		E_4_1.medium++ <--> ES_Link <-->  S_1_2.medium++;
		E_4_1.medium++ <--> ES_Link <-->  S_1_3.medium++;
		E_4_1.medium++ <--> ES_Link <-->  S_1_4.medium++;
		E_4_1.medium++ <--> ES_Link <-->  S_1_5.medium++;
		E_4_1.medium++ <--> ES_Link <-->  S_1_6.medium++;
		E_4_1.medium++ <--> ES_Link <-->  S_1_7.medium++;
		E_4_1.medium++ <--> ES_Link <-->  S_1_8.medium++;
		E_4_1.medium++ <--> ES_Link <-->  S_1_9.medium++;
		E_4_2.medium++ <--> ES_Link <-->  S_2_0.medium++;
		E_4_2.medium++ <--> ES_Link <-->  S_2_1.medium++;
		E_4_2.medium++ <--> ES_Link <-->  S_2_2.medium++;
		E_4_2.medium++ <--> ES_Link <-->  S_2_3.medium++;
		E_4_2.medium++ <--> ES_Link <-->  S_2_4.medium++;
		E_4_2.medium++ <--> ES_Link <-->  S_2_5.medium++;
		E_4_2.medium++ <--> ES_Link <-->  S_2_6.medium++;
		E_4_2.medium++ <--> ES_Link <-->  S_2_7.medium++;
		E_4_2.medium++ <--> ES_Link <-->  S_2_8.medium++;
		E_4_2.medium++ <--> ES_Link <-->  S_2_9.medium++;
		E_4_3.medium++ <--> ES_Link <-->  S_3_0.medium++;
		E_4_3.medium++ <--> ES_Link <-->  S_3_1.medium++;
		E_4_3.medium++ <--> ES_Link <-->  S_3_2.medium++;
		E_4_3.medium++ <--> ES_Link <-->  S_3_3.medium++;
		E_4_3.medium++ <--> ES_Link <-->  S_3_4.medium++;
		E_4_3.medium++ <--> ES_Link <-->  S_3_5.medium++;
		E_4_3.medium++ <--> ES_Link <-->  S_3_6.medium++;
		E_4_3.medium++ <--> ES_Link <-->  S_3_7.medium++;
		E_4_3.medium++ <--> ES_Link <-->  S_3_8.medium++;
		E_4_3.medium++ <--> ES_Link <-->  S_3_9.medium++;

}


channel TF_Link extends DatarateChannel {
    parameters:
        datarate = 1Gbps;
        delay = 0;
        per = 0;
        ber = 0;
}

channel FS_Link extends DatarateChannel {
    parameters:
        datarate = 10Gbps;
        delay = 0;
        per = 0;
        ber = 0;
}

channel ES_Link extends DatarateChannel {
    parameters:
        datarate = 10Gbps;
        delay = 0;
        per = 0.00;
        ber = 0.0;
}

