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
    SDU *sdu = new SDU();
    sdu->setUserData(&buffer[offset], size);

    sduQ.push_back(sdu);

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




  //invoke SDU protection so we don't have to bother with it afterwards
  for(std::vector<SDU*>::iterator it = sduQ.begin(); it != sduQ.end(); ++it){
    sduProtection(*it);
  }

  SDU *sdu = NULL;
  DataTransferPDU* genPDU = dataPDU->dup();
  while (!sduQ.empty())
  {
    //genPDU is full so create new PDU and start filling
    if (genPDU->getPduLen() >= this->state.getMaxFlowPduSize())
    {
      //TODO A2 what else to do before sending?
      //what about formating SDUDelimitersFlags in userData?
      genPDU->putDelimitFlags();

      //put genPDU to generatedPDUs
      generatedPDUs.push_back(genPDU);
      DataTransferPDU* genPDU = dataPDU->dup();
      //set DRF(false) -> not needed (false is default)
      //      genPDU->setFlags(genPDU->getFlags() && )
      genPDU->setSeqNum(this->state.getNextSeqNumToSend());
      this->state.incNextSeqNumToSend();
    }

    /*
     * This method fetches next sdu if current one has been put to some PDU(s) (offset = size)
     */
    this->getSDUFromQ(sdu);

    /* if the rest of the SDU is bigger than empty space in PDU then */
    unsigned int copySize = 0;
    unsigned int pduRestSize = state.getMaxFlowSduSize() - genPDU->getPduLen();
    if(sdu->getRestSize() >= (pduRestSize)){
      copySize = pduRestSize;
//      genPDU->addUserData(sdu->getUserData(pduRestSize), pduRestSize);
      //now we can break since the PDU should be full
//      break;
    }else{
      copySize = sdu->getRestSize();
//      genPDU->addUserData(sdu->getUserData(sdu->getRestSize()), sdu->getRestSize());

    }

    genPDU->addUserData(sdu->getUserData(copySize), copySize);





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
/**
 * This method
 * @para
 */

void DTP::getSDUFromQ(SDU *sdu)
{
  if(sdu == NULL){
    sdu = sduQ.front();
    sduQ.erase(sduQ.begin());
    return;
  }

}


