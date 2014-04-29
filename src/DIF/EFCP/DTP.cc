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

DTP::DTP()
{
  // TODO Auto-generated constructor stub

}
DTP::~DTP()
{
  // TODO Auto-generated destructor stub
}

void DTP::setConnId(const ConnectionId& connId)
{
  this->connId = connId;
}

void DTP::handleMessage(cMessage *msg)
{

}

bool DTP::write(int portId, unsigned char* buffer, int len)
{

  cancelEvent(this->senderInactivity);

  this->delimit(buffer, len);
  /* Now the data from buffer are copied to SDUs so we can free the memory */
  free(buffer);

  this->generatePDUs();

  return true;
}

/**
 * Delimits @param len bytes of buffer into User-data parts and put them on generated PDU
 * @param buffer pointer to incoming data buffer
 * @param len size of incoming data
 * @return number of created SDUs
 */
int DTP::delimit(unsigned char *buffer, unsigned int len)
{

  unsigned int offset = 0, size = 0, counter = 0;

  do
  {
    if (len - offset > state.getMaxFlowSduSize())
    {
      size = state.getMaxFlowSduSize();
    }
    else
    {
      size = len;
    }
    SDU sdu;
    sdu.setUserData(&buffer[offset], size);

    sduQ.push(sdu);

    offset += size;
    counter++;

  } while (offset < len);

  //TODO A1 If len is zero then create empty SDU?
//  if(len == 0){
//    SDU sdu;
//    sduQ.push(sdu);
//    counter = 1;
//  }
  return counter;
}

/**
 * This method takes all SDUs from sduQ and generates PDUs by adding appropriate header content
 */
void DTP::generatePDUs()
{

  DataTransferPDU* dataPDU = new DataTransferPDU();


  dataPDU->setConnId((const ConnectionId) (*connId.dup()));
  //setDestAddr... APN
  //setSrcAddr ... APN


  SDU sdu;
  while(!sduQ.empty()){
      sdu = sduQ.front();
      sduQ.pop();
      DataTransferPDU* genPDU = dataPDU->dup();
      //set DRF(false) -> not needed (false is default)
//      genPDU->setFlags(genPDU->getFlags() && )
      genPDU->setSeqNum(this->state.getNextSeqNumToSend());
      this->state.incNextSeqNumToSend();

      //invoke SDU protection
      sduProtection(&sdu);

      unsigned int offset = 0, size = 0, counter = 0;

       do
       {
         if (sdu.getSize() - offset > state.getMaxFlowSduSize())
         {
           size = state.getMaxFlowSduSize();
         }
         else
         {
           size = sdu.getSize();
         }
//         SDU sdu;
//         sdu.setUserData(&buffer[offset], size);

         sduQ.push(sdu);

         offset += size;
         counter++;

       } while (offset < sdu.getSize());



  }
  //flags

  //pduLen

}

/**
 * This method calls specified function to perform SDU protection.
 * SDU size will probably change because of the added CRC or whatnot.
 * @param sdu is the SDU being protected eg added CRC or otherwise
 */
void DTP::sduProtection(SDU *sdu){


}


