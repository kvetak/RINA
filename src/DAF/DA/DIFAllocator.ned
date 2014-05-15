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

package rina.DAF.DA;

module DIFAllocator
{
    @display("i=block/classifier2;bgb=443,148");
    submodules:
        namingInformation: NamingInformation {
            @display("p=75,61");
        }
        neighborTable: NeighborTable {
            @display("p=266,61");
        }
        directory: Directory {
            @display("p=357,61");
        }
        searchTable: SearchTable {
            @display("p=170,61");
        }
}
