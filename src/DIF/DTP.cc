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

#include "DTP.h"

DTP::DTP() {
    // TODO Auto-generated constructor stub

}
DTP::~DTP() {
    // TODO Auto-generated destructor stub
}

void DTP::handleMessage(cMessage *msg){

}

bool DTP::write(int portId, unsigned char* buffer, int len) {

    cancelEvent(this->senderInactivity);

    this->delimit(buffer, len);

    this->encapsulate();

    return true;
}


/**
 * Delimits @param len bytes of buffer into User-data parts and put them on generated PDU
 * @param buffer pointer to incoming data buffer
 * @param len size of incoming data
 * @return number of created SDUs
 */
int DTP::delimit(unsigned char *buffer, int len){

    int offset = 0, size = 0, counter = 0;

    unsigned char * sdu;
    while (offset < len) {
        if (len - offset > state.getMaxFlowSduSize()) {
            size = state.getMaxFlowSduSize();

        } else {
            size = len;
        }
        sdu = new unsigned char[size];
        memcpy(sdu, buffer, size);
        //put sdu somewhere
        sduQ.push(sdu);

        offset += size;
        counter++;

    }
    return counter;
}



void DTP::encapsulate(){

}
