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

package rina.src.DAF.RIB.RAFT;

//
// TODO auto-generated module
//
module Raft
{
    submodules:
        raft: RAFT {
            @display("p=138,85;i=block/fork");
            //enrolConfigData = configData;
        }

        raftLog: RAFTLog {
            @display("p=82,189;i=block/table2");
        }

        raftFsm: RAFTFSM {
            @display("p=190,189;i=block/cogwheel");
        }
}
