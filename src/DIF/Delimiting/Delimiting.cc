//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
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
/**
 * @file Delimiting.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jul 31, 2014
 * @brief
 * @detail
 */

#include "Delimiting.h"

Define_Module(Delimiting);

Delimiting::Delimiting()
{
  // TODO Auto-generated constructor stub

}


void Delimiting::handleMessage(cMessage* msg){
  if(msg->isSelfMessage()){
    //self-message
  }else{
    if(msg->arrivedOn("efcpModuleIo$i")){
      processMsgFromFAI((CDAPMessage*)(msg));
    }else if(msg->arrivedOn("efcpiIo$i")){
      handleMsgFromEfcpi((Data*)(msg));
    }else{
      //A2 panic!
    }


  }


}

void Delimiting::processMsgFromFAI(CDAPMessage* msg){

  /*
   * 1. Create new SDU and put msg to this new SDU.
   * 2. Check if SDU.size < (MAXPDUSIZE - header)
   *  2a partition it creating multiple SDUFrag and put them into some vector
   * 3. Go through Data vector and send them to EFCPI
   */

  SDU* sdu = new SDU();
  sdu->addUserData(msg);

  //TODO A1 handle multiple gates -> change to cGate*
  send(sdu, "efcpiIo$o", 0);
}

void Delimiting::handleMsgFromEfcpi(Data* msg){

  SDU* sdu = (SDU*) msg;
  std::vector<CDAPMessage*> &msgVector = sdu->getMUserData();
  CDAPMessage* cdap = msgVector.front();
  send(cdap, "efcpModuleIo$o");
}

Delimiting::~Delimiting()
{
  // TODO Auto-generated destructor stub
}

