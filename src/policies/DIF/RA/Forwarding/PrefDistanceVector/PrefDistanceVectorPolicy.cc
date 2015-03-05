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

// Author: Kewin Rausch (kewin.rausch@create-net.org)

#include "PrefDistanceVectorPolicy.h"
#include "PDUFwdTabGenerator.h"
#include "PDUFTGUpdate.h"
#include "PDVPInfo.h"

Define_Module(PrefDistanceVectorPolicy);

//
// Class constructor/destructors stuff.
//

PrefDistanceVectorPolicy::PrefDistanceVectorPolicy()
{
    updateT = 0;
}

PrefDistanceVectorPolicy::~PrefDistanceVectorPolicy()
{
    // Do nothing...
}

//
// Class procedures sorted by name.
//

void PrefDistanceVectorPolicy::computeForwardingTable()
{
    if(!fwdtg)
    {
        return;
    }

    NetworkState * netState = fwdtg->getNetworkState();
    NeighborState * neiState = fwdtg->getNeighborhoodState();

    // So, when we need to build up the forwarding table from scratch then
    // we start from our neighbors alone.
    //

    // Maintain only information about the neighborhood.
    for(NIter it = netState->begin(); it != netState->end(); ++it )
    {
        bool rem = false;

        PDVPInfo * i = (PDVPInfo *)(*it);

        for(EIter et = neiState->begin(); et != neiState->end(); ++et )
        {
            PDUFTGNeighbor * e = (*et);

            // It's not a neighbor.
            if(!(e->getDestAddr() == i->getDestination()))
            {
                rem = true;
                break;
            }
            // It's a neighbor! Repopulate the forwarding table.
            else
            {
            //    fwt->insert(e->getDestAddr(), e->getQosId(), e->getPort());
            }
        }

        if(rem)
        {
            // Remove this information from our network state.
            netState->remove(i);
        }
    }
}

PDUFTGInfo * PrefDistanceVectorPolicy::flowExists(Address addr, unsigned short qos)
{
    for(NIter it = fwdtg->getNetworkState()->begin(); it != fwdtg->getNetworkState()->end(); ++it )
    {
        PDVPInfo * fsi = (PDVPInfo * )(*it);

        // Equal condition; same source reach same destination with same qos constrain.
        if(fsi->getDestination() == addr &&
            fsi->getQoSID() == qos)
        {
            return fsi;
        }
    }

    return NULL;
}

unsigned int PrefDistanceVectorPolicy::getUpdateTimeout()
{
    return updateT;
}

void PrefDistanceVectorPolicy::handleMessage(cMessage *msg)
{
    NeighborState * n;

    if(msg->isSelfMessage())
    {
        switch(msg->getKind())
        {
        case PDUFTG_SELFMSG_FSUPDATE:
            /* Stop condition. */
            if(getUpdateTimeout() == 0)
            {
                break;
            }

            n = fwdtg->getNeighborhoodState();

            for(EIter it = n->begin(); it != n->end(); ++it)
            {
                PDUFTGNeighbor * info = (*it);

                // Finally send the update.
                fwdtg->signalForwardingInfoUpdate(
                    new PDUFTGUpdate(
                        fwdtg->getIpcAddress(),
                        info->getDestAddr(),
                        fwdtg->getNetworkState()));
            }

            scheduleAt(
                simTime() + getUpdateTimeout(),
                new cMessage("UpdateRequested", PDUFTG_SELFMSG_FSUPDATE));

            break;
        default:
            break;
        }

        delete msg;
    }
}

void PrefDistanceVectorPolicy::initialize()
{
    any = par("any").stdstringValue();
    std::string del = par("delimiter").stdstringValue();
    if(del.length() > 0 && del.at(0)!= ' '){
        delimiter = del.at(0);
    } else {
        delimiter = '.';
    }
    thisIPCAddrParsed = split(fwdtg->getIpcAddress().getIpcAddress().getName(), delimiter);


    // Display active policy name.
    PDUFTGPolicy::initialize();

    // Default timeout 30 seconds.
    setUpdateTimeout(30);

    // Start the forwarding update timer routine.
    scheduleAt(
        simTime() + getUpdateTimeout(),
        new cMessage("FwdTimerInit", PDUFTG_SELFMSG_FSUPDATE));


    fwt = dynamic_cast<PrefixPDUForwardingTable * >(fwdtg->getForwardingTable());
    if(!fwt){
        EV << "Invalid FWTable "<<fwdtg->getForwardingTable()->getFullName()<<" for PrefDistanceVectorPolicy" << endl;
        endSimulation();
    }
}

void PrefDistanceVectorPolicy::insertNewFlow(Address addr, short unsigned int qos, RMTPort * port)
{
    // Callable from other modules.
    Enter_Method("insertNewFlow()");

    if(!fwdtg)
    {
        return;
    }

    // We're interested in flows to element of my DIF.
    if(addr.getDifName() == fwdtg->getIpcAddress().getDifName())
    {
        PDVPInfo * flowInfo;

        flowInfo = (PDVPInfo *)flowExists(addr, qos);

        // Flow present? Strange!!!
        if(flowInfo)
        {
            pduftg_debug("Flow for " << addr << " already present!");
        }

        flowInfo = new PDVPInfo(
            fwdtg->getIpcAddress(),
            addr,
            qos,
            1);

        // Update the network state too.
        fwdtg->getNetworkState()->push_back(flowInfo);

        Address nAddr = getNAddr(addr);
        // Insert what you consider a neighbor.
        fwdtg->insertNeighbor(nAddr, qos, port);

        // Add the entry in the table.
        //fwt->insert(nAddr, qos, port);

        // Debug the actual state of the network.
        pduftg_debug(fwdtg->getIpcAddress().info() << "> " <<
            fwdtg->netInfo());
    }
}


Address PrefDistanceVectorPolicy::getNAddr(const Address &addr){
    Address r = addr;
    std::vector<std::string> addrParsed = split(addr.getIpcAddress().getName(), delimiter);

    std::vector<std::string>::iterator itS = addrParsed.begin();
    std::vector<std::string>::iterator itM = thisIPCAddrParsed.begin();

    std::string nAddr = "";
    char d[2] = {delimiter, 0};

    while(itS != addrParsed.end() && itM != thisIPCAddrParsed.end()){
        nAddr.append(*itM);
        nAddr.append(d);
        if(*itS != *itM){
            break;
        }
        itS++;
        itM++;
    }
    nAddr.append(any);

    return Address(nAddr.c_str(), addr.getDifName().getName().c_str());

}

void PrefDistanceVectorPolicy::mergeForwardingInfo(PDUFTGUpdate * info)
{
    NetworkState * arrived = info->getInfo();

    // Scan the arrived informations.
    for(NIter i = arrived->begin(); i != arrived->end(); ++i)
    {
        bool insert = false;

        PDVPInfo * eval = (PDVPInfo *)(*i);
        // Info here are stored with us as source.
        PDVPInfo * info = (PDVPInfo *)flowExists(
            eval->getDestination(),
            eval->getQoSID());

        // Do not consider info over yourself.
        if(eval->getDestination().getApname().getName() ==
            fwdtg->getIpcAddress().getApname().getName())
        {
            continue;
        }

        // We already have such information.
        if(info)
        {
            // It's a better metric?
            if(eval->getMetric() + 1 < info->getMetric())
            {
             //   fwt->remove(info->getDestination(), info->getQoSID());
                removeFlow(eval->getDestination(), eval->getQoSID());

                insert = true;
            }
        }
        else
        // The info does not exists.
        {
            insert = true;
        }

        if(insert)
        {
            // It's a better metric; pass through this sender from now on...
            PDUFTGNeighbor * en = fwdtg->neighborExists(eval->getSource());

            if(!en)
            {
                EV << "Could not reach " << eval->getDestination() << " from " << fwdtg->getIpcAddress().getApname().getName() << "???\n";
                continue;
            }

            RMTPort * p = en->getPort();
            PDVPInfo * newi = new PDVPInfo(
                fwdtg->getIpcAddress(),
                eval->getDestination(),
                eval->getQoSID(),
                eval->getMetric() + 1);

            // Insert the entry into the tables.
            fwdtg->getNetworkState()->push_back(newi);
     //       fwt->insert(eval->getDestination(), eval->getQoSID(), p);
        }
    }

    // Debug the actual state of the network.
    pduftg_debug(fwdtg->getIpcAddress().info() << "> " <<
        fwdtg->netInfo());
}

PDUFTGUpdate * PrefDistanceVectorPolicy::prepareFSUpdate(Address destination)
{
    PDUFTGUpdate * ret = new PDUFTGUpdate();
    Address a = fwdtg->getIpcAddress();

    ret->setSource(a);
    ret->setDestination(destination);
    ret->setInfo(fwdtg->getNetworkState());

    return ret;
}

void PrefDistanceVectorPolicy::removeFlow(Address addr, unsigned short qos)
{
    // Select the info with your information evaluation procedure.
    PDUFTGInfo * netinfo = flowExists(addr, qos);

    if(!netinfo)
    {
        fwdtg->getNetworkState()->remove(netinfo);
    }
}


void PrefDistanceVectorPolicy::setUpdateTimeout(unsigned int sec)
{
    updateT = sec;
}



std::vector<std::string> &PrefDistanceVectorPolicy::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> PrefDistanceVectorPolicy::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
