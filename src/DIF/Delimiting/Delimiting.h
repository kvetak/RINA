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
 * @file Delimiting.h
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jul 31, 2014
 * @brief
 * @detail
 */

#ifndef DELIMITING_H_
#define DELIMITING_H_

#include <omnetpp.h>
#include "CDAPMessage_m.h"
#include "SDU.h"
//#include <csimplemodule.h>

#define DELIMITING_MODULE_NAME "delimiting"

class Delimiting : public cSimpleModule
{
  private:
    void processMsgFromFAI(mCDAPMessage* msg);
  public:
    Delimiting();
    virtual ~Delimiting();

  protected:
    virtual void handleMessage(cMessage *msg);


};

#endif /* DELIMITING_H_ */
