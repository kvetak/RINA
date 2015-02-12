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

package rina.DIF.EFCP;

simple EFCP
{
    parameters:
        @display("i=block/fork");
        bool pduDroppingEnabled = default(false);
        
        string ecnPolicy = default("");
        string rcvrFCPolicy = default("");
        string rcvrAckPolicy = default("");
        string receivingFCPolicy = default("");
        string sendingAckPolicy = default("");
        string lostControlPDUPolicy = default("");
        string rcvrControlAckPolicy = default("");
        string senderAckPolicy = default("");
        string fcOverrunPolicy = default("");
        string noOverridePeakPolicy = default("");
        string txControlPolicy = default("");
        string noRateSlowDownPolicy = default("");
        string reconcileFCPolicy = default("");
        string rateReductionPolicy = default("");
        
        string rcvrInactivityPolicy = default("");
  		string senderInactivityPolicy = default("");
  		string initialSeqNumPolicy = default("");
  		string rttEstimatorPolicy = default("");
  		
  		double rtt @unit(s) = default(2s);
  		double mpl @unit(s) = default(50s);
        

        
}
