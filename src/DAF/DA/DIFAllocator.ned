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

package rina.src.DAF.DA;

module DIFAllocator
{
    parameters:
    	@display("i=misc/node,green;bgb=487,206");
    	xml configData = default(xml("<DA><NeighborTable/><NamingTable/><SearchTable/><Directory/></DA>"));
    submodules:
        namingInformation: NamingInformation {
            parameters:
            	@display("p=80,143");
            	daConfigData = configData;
        }
        neighborTable: NeighborTable {
            parameters:
	            @display("p=403,143");
	            daConfigData = configData;
        }
        directory: Directory {
            parameters:
    	        @display("p=193,143");
    	        daConfigData = configData;
        }
        searchTable: SearchTable {
            parameters:
	            @display("p=300,143");
	            daConfigData = configData;
        }
        da: DA {
            parameters:        
	            @display("p=247,52");
        }
}
