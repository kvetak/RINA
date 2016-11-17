//
// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

import rina.policies.DIF.RMT.Monitor.IntRMTQMonitorPolicy;

package rina.policies.DIF.RMT.Monitor.QTAMux;

simple QTAMonitor like IntRMTQMonitorPolicy 
{
    parameters:
        @display("i=block/socket");
        @class(QTAMux::QTAMonitor);
        
        double defRate = default(1.0);
        xml shapersData = default(xml("<shapersData/>"));
        xml muxData = default(xml("<muxData/>"));
        xml ecnData = default(xml("<ecnData/>"));
        
        
        string nodeName = default("");
        bool printAtEnd = default(false);
        
        bool recordStats = default(false);
        bool saveStats = default(false);
        bool pdu_IO = default(false);
        bool data_IO = default(false);
        bool pdu_IOi = default(false);
        bool data_IOi = default(false);
        bool pdu_in_IO = default(false);
        bool data_in_IO = default(false);
        bool pdu_in_IOi = default(false);
        bool data_in_IOi = default(false);
        double record_interval = default(0.1);	//s
        double first_interval = default(0.0); 	//s
        double last_interval = default(10.0); 	//s
}
