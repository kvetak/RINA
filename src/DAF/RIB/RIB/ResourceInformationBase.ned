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

package rina.src.DAF.RIB.RIB;

import rina.src.DAF.RIB.RIB.RIB;

module ResourceInformationBase
{
    parameters:
        @display("i=block/buffer2;bgb=250,250");

    gates:
        inout southIo;

    submodules:

        rib: RIB {
            parameters:
                @display("p=125,100;i=block/buffer2");
        }

    connections allowunconnected:
}
