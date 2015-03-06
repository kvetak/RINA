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

#include "PDUFTGUpdate.h"

PDUFTGUpdate::PDUFTGUpdate()
{

}

PDUFTGUpdate::PDUFTGUpdate(Address from, Address to, std::list<PDUFTGInfo *> * info)
{
    setSource(from);
    setDestination(to);
    setInfo(info);
}

PDUFTGUpdate::~PDUFTGUpdate()
{
    disposeInfo();
}

void PDUFTGUpdate::disposeInfo()
{
    /* Removes any previously allocated info. */
    if(info)
    {
        delete info;
        info = NULL;
    }
}

/* Getters. */

Address PDUFTGUpdate::getDestination()
{
    return dstAddr;
}
Address PDUFTGUpdate::getSource()
{
    return srcAddr;
}

std::list<PDUFTGInfo *> *  PDUFTGUpdate::getInfo()
{
    return info;
}


/* Setters. */

void PDUFTGUpdate::setDestination(Address addr)
{
    dstAddr = addr;
}

void PDUFTGUpdate::setInfo(std::list<PDUFTGInfo *> *  info)
{
    this->info = new std::list<PDUFTGInfo *>();

    for(std::list<PDUFTGInfo *>::iterator it = info->begin(); it != info->end(); ++it)
    {
        PDUFTGInfo * i = (*it);

        this->info->push_back(
            new PDUFTGInfo(
                i->getSource(),
                i->getDestination(),
                i->getQoSID(),
                i->getMetric()));
    }
}

void PDUFTGUpdate::setSource(Address addr)
{
    srcAddr = addr;
}
