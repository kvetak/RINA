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

package rina.src.DAF;

//import rina.src.DAF.AE.ApplicationEntity;

module ApplicationProcessNAE
{
    parameters:
        @display("i=misc/node,#FFFF80");
        int numOfAE = default(1);
        string apName = default("App");
        string apInstance = default("0");
    
    gates:
        inout southIo[];
        
    submodules:

        //applicationEntity[numOfAE]: ApplicationEntity {
        //    @display("p=112,81,r,150");
        //}
    
    connections allowunconnected:
}
