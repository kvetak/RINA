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

#ifndef DTP_H_
#define DTP_H_

#include <omnetpp.h>
#include <queue>

#include "DTPState.h"
#include "DTPTimers_m.h"

class DTP : public cSimpleModule {
private:
    DTPState state; //state of this data-transfer

    std::queue<unsigned char *> sduQ; //SDUs generated from delimiting

    InactivityTimer* senderInactivity;
public:
    DTP();
    virtual ~DTP();


    bool read(int portId, unsigned char * buffer, int len);
    bool readImmediate(int portId, unsigned char* buffer, int len);
    bool write(int portId, unsigned char *buffer, int len);

    /** Delimits  content of buffer */
    int delimit(unsigned char *buffer, int len);

    /** Encapsulate all SDUs from sduQ into PDUs and put them in generated_PDU Queue */
    void encapsulate();

protected:
    virtual void handleMessage(cMessage *msg);

};

#endif /* DTP_H_ */
