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

package rina.src.DAF.AE;

import rina.src.Common.Test;
import rina.src.DAF.CDAP.CommonDistributedApplicationProtocol;


module ApplicationEntity
{
    parameters:
        @display("i=block/socket;bgb=276,216");
        string aeType = default("AE");
    gates:
        inout aeIo;
                
    submodules:
        commonDistributedApplicationProtocol: CommonDistributedApplicationProtocol {
            @display("p=135,145");
        }
        iae: <aeType> like IAE {
            @display("p=135,48");
        }
    connections allowunconnected:
}
