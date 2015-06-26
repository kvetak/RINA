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

package rina.examples.Routing.DC;

import rina.src.CS.DC_VM;
import rina.src.CS.DC_Server;
import rina.src.CS.DC_TOR;
import rina.src.CS.DC_AS;
import rina.src.CS.DC_CR;

network DC
{
    @display("bgb=1000,250");

    submodules:

        CR0 : DC_CR {
            @display("p=825.000000,100.000000");
        }

        AS1 : DC_AS {
            @display("p=550.000000,50.000000");
        }

        AS2 : DC_AS {
            @display("p=550.000000,175.000000");
        }

        TOR3 : DC_TOR {
            @display("p=450.000000,50.000000");
        }

        TOR4 : DC_TOR {
            @display("p=450.000000,175.000000");
        }

        SRV5 : DC_Server {
            @display("p=200.000000,25.000000");
        }

        SRV6 : DC_Server {
            @display("p=200.000000,150.000000");
        }

        VM7 : DC_VM {
            @display("p=100.000000,25.000000");
        }

        VM8 : DC_VM {
            @display("p=100.000000,150.000000");
        }


    connections:

        CR0.medium++ <--> AS1.medium++;
        AS1.medium++ <--> AS2.medium++;
        AS1.medium++ <--> TOR3.medium++;
        AS2.medium++ <--> TOR4.medium++;
        TOR3.medium++ <--> SRV5.medium++;
        TOR4.medium++ <--> SRV6.medium++;
        SRV5.medium++ <--> VM7.medium;
        SRV6.medium++ <--> VM8.medium;
}
