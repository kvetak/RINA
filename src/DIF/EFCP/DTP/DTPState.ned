//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package rina.src.DIF.EFCP.DTP;


simple DTPState
{
    @display("i=block/subqueue");
    
    int maxSDUSize @unit(B) = default(1500B);
    int maxPDUSize @unit(B) = default(1500B);
    
//    bool rxPresent = default(true);
//    bool winBased = default(true);
//    bool rateBased = default(false);
    
    double rtt @unit(s) = default(2s);
    double mpl @unit(s) = default(50s);
    
}
