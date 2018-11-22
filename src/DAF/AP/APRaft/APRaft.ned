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

package rina.src.DAF.AP.APRaft;
import rina.src.DAF.AP.AP;
import rina.src.DAF.AP.APInst;

//
// TODO auto-generated module
//
simple APRaft extends AP like APInst
{
    parameters:
        @class(APRaft);
        
        int startAt @unit(s) = default(-1s);
        int stopAt  @unit(s) = default(-1s);
        int pingAt  @unit(s) = default(0s);
        double interval @unit(s) = default(1s);

        string dstApName = default("AppERROR");
        string dstApInstance = default("0");
        string dstAeName = default("AERaft");
        string dstAeInstance = default("-1");
}