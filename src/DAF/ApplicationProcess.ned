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

package rina.DAF;

import rina.DAF.DA.DIFAllocator;
import rina.DAF.IRM.IRM;


module ApplicationProcess
{
    @display("bgb=337,139;i=misc/node,yellow,30");
    submodules:
        irm: IRM {
            @display("p=99,64");
        }
        difAllocator: DIFAllocator {
            @display("p=213,64");
        }
}
