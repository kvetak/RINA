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

#include "FSUpdateInfo.h"

FSUpdateInfo::FSUpdateInfo()
{

}

FSUpdateInfo::FSUpdateInfo(Address from, Address to, std::list<FSInfo *> * info)
{
    setSource(from);
    setDestination(to);
    setInfo(info);
}

FSUpdateInfo::~FSUpdateInfo()
{
    disposeInfo();
}

void FSUpdateInfo::disposeInfo()
{
    /* Removes any previously allocated info. */
    if(info)
    {
        for(std::list<FSInfo *>::iterator it = info->begin(); it != info->end(); ++it)
        {
            FSInfo * i = (*it);

            info->remove(i);
            delete i;
        }

        delete info;
        info = NULL;
    }
}

/* Getters. */

Address FSUpdateInfo::getDestination()
{
    return dstAddr;
}

std::list<FSInfo *> *  FSUpdateInfo::getInfo()
{
    return info;
}

Address FSUpdateInfo::getSource()
{
    return srcAddr;
}

/* Setters. */

void FSUpdateInfo::setDestination(Address addr)
{
    dstAddr = addr;
}

void FSUpdateInfo::setInfo(std::list<FSInfo *> *  info)
{
    this->info = new std::list<FSInfo *>();

    for(std::list<FSInfo *>::iterator it = info->begin(); it != info->end(); ++it)
    {
        FSInfo * i = (*it);

        this->info->push_back(
            new FSInfo(
                i->getSource(),
                i->getDestination(),
                i->getQoSID(),
                i->getMetric()));
    }
}

void FSUpdateInfo::setSource(Address addr)
{
    srcAddr = addr;
}
