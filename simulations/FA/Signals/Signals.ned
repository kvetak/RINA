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

package rina.simulations.FA.Signals;

import rina.CS.Host1AP;


//
// TODO Auto-generated network
//
network Signals
{
    @display("bgb=433,167");
    submodules:
        host2: Host1AP {
            @display("p=285,77");
        }
        host1: Host1AP {
            @display("p=105,77");
        }
    connections:
        host1.medium <--> host2.medium;
}
