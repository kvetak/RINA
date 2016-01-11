//
// Copyright © 2014 - 2015 PRISTINE Consortium (http://ict-pristine.eu)
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

import rina.policies.DIF.RMT.Monitor.IntRMTQMonitorPolicy;

package rina.policies.DIF.RMT.Monitor.ModularMonitor;

module ModularMonitor like IntRMTQMonitorPolicy
{
    parameters:
        @display("i=block/socket");
        @class(ModularMonitor::ModularMonitor);
        string inputOutSubModule_Type = default("MM_Simple_Out");
        string inputDropSubModule_Type = default("MM_Simple_Drop");
        string outputOutSubModule_Type = default("MM_Simple_Out");
        string outputDropSubModule_Type = default("MM_Simple_Drop");
        
        bool signal = default(true);

    submodules:

        inputOutSubModule: <inputOutSubModule_Type> like Int_MM_Out_Module {
            @display("p=108,56");
        }
        inputDropSubModule: <inputDropSubModule_Type> like Int_MM_Drop_Module {
            @display("p=108,156");
        }
        outputOutSubModule: <outputOutSubModule_Type> like Int_MM_Out_Module {
            @display("p=278,56");
        }
        outputDropSubModule: <outputDropSubModule_Type> like Int_MM_Drop_Module {
            @display("p=278,156");
        }
}
