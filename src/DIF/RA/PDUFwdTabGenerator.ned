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

package rina.DIF.RA;

//
// TODO auto-generated module
//
simple PDUFwdTabGenerator
{
    @display("i=block/network2");
    
    // The target module where you want to see the network state report. 
    // The default is the IPC which contains the PDUFTG.
    string netStateMod = default("^.^.");
    // Want to show a visual report during simulation?
    bool netStateVisible = default(false);
}
