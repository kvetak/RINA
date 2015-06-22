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

package rina.policies.DIF.RMT.Monitor.WeightedFairQMonitor;

simple WeightedFairQMonitor like IntRMTQMonitorPolicy 
{
    parameters:
        @display("i=block/socket");
        @class(FWQ::WeightedFairQMonitor);
        
        int defBW = default(100);
        int stopQAt = default(3);
        int restartQAt = default(1);
}
