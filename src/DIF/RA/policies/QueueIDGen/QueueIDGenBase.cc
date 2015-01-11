//
// Copyright � 2014 PRISTINE Consortium (http://ict-pristine.eu)
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

#include <QueueIDGen/QueueIDGenBase.h>

Define_Module(QueueIDGenBase);

void QueueIDGenBase::initialize()
{
    // display active policy name
    cDisplayString& disp = getDisplayString();
    disp.setTagArg("t", 1, "t");
    disp.setTagArg("t", 0, getClassName());

    onPolicyInit();
}

void QueueIDGenBase::onPolicyInit()
{
}

void QueueIDGenBase::handleMessage(cMessage *msg)
{
}

std::string QueueIDGenBase::generateID(PDU_Base* pdu)
{
    return std::string("");
}

std::string QueueIDGenBase::generateID(Flow* flow)
{
    return std::string("");
}

