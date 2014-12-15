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

/* Author: Kewin Rausch (kewin.rausch@create-net.org) */

#ifndef __RINA_PDUFTGLISTENERS_H
#define __RINA_PDUFTGLISTENERS_H

//Standard libraries
#include <omnetpp.h>

class PDUFwdTabGenerator;

/* Base listener for every PDU Forwarding Generator module signal. */
class PDUFTGListener :
        public cListener
{
  public:
    PDUFTGListener(PDUFwdTabGenerator * generator);
    virtual ~PDUFTGListener();

    virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj)
    {
        EV << "Signal to PDUFTG initiated by " << src->getFullPath() << endl;
    }
  protected:
    PDUFwdTabGenerator * fwdtg;
};

/* Listener for forwarding info messages.  */
class LisPDUFTGFwdInfoRecv :
        public PDUFTGListener
{
  public:
    LisPDUFTGFwdInfoRecv(PDUFwdTabGenerator * generator) : PDUFTGListener(generator) {};

    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

#endif /* __RINA_PDUFTGLISTENERS_H */
