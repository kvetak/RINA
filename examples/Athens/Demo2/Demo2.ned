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

package rina.examples.Athens.Demo2;

import rina.src.CS.Host1AP;
import rina.src.CS.InteriorRouter2Int;


//
// TODO Auto-generated network
//
network Demo2
{
    @display("bgb=403,219");
    submodules:
        hostA: Host1AP {
            @display("p=44,73");
        }
        hostB: Host1AP {
            @display("p=242,82");
        }
        switch: InteriorRouter2Int {
            @display("p=147,145");
        }
    connections:
        hostA.medium <--> switch.medium[0];
        hostB.medium <--> switch.medium[1];

}
