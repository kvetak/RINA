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
#include "PDUFTGInfo.h"
#include "RMTPort.h"
#include "Utils.h"

#include "PrefPDUFTGUpdate.h"

Define_Module(PrefDistanceVectorPolicy);

//
// Class constructor/destructors stuff.
//

PrefDistanceVectorPolicy::PrefDistanceVectorPolicy()
{
    updateT = 0;
}

PrefDistanceVectorPolicy::~PrefDistanceVectorPolicy(){}

//
// Class procedures.
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

        PDUFTGInfo * i = *it;

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
                // Add the entry in the table.
                if(table.addOrReplaceEntry(
                        e->getDestAddr().getIpcAddress().getName(),
                        e->getDestAddr().getIpcAddress().getName(),
                        1, e->getQosId()
                        )){
                    fwt->addEntry(e->getDestAddr().getIpcAddress().getName(), e->getQosId(), e->getPort());
                }
                if(table.addOrReplaceEntry(
                        e->getDestAddr().getIpcAddress().getName(),
                        getNAddr(e->getDestAddr()),
                        1, e->getQosId()
                        )){
                    fwt->addEntryIfNot(getNAddr(e->getDestAddr()), e->getQosId(), e->getPort());
                }
            }
        }

        if(rem)
        {
            // Remove this information from our network state.
            netState->remove(i);
        }
    }
}


PDUFTGInfo * PrefDistanceVectorPolicy::flowExists(Address addr, unsigned short qos){
    return flowExists(addr.getIpcAddress().getName(), qos);
}

PDUFTGInfo * PrefDistanceVectorPolicy::flowExists(std::string addr, unsigned short qos)
{
    for(NIter it = fwdtg->getNetworkState()->begin(); it != fwdtg->getNetworkState()->end(); ++it )
    {
        PDUFTGInfo * fsi = *it;
        if(fsi->getDestination() == addr &&fsi->getQoSID() == qos) {
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
                        prepareFSUpdate(info->getDestAddr())
                );
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

    thisIPCAddr = fwdtg->getIpcAddress().getIpcAddress().getName();
    thisIPCAddrParsed = split(thisIPCAddr, delimiter);


    // Display active policy name.
    PDUFTGPolicy::initialize();

    // Default timeout 30 seconds.
    setUpdateTimeout(30);

    // Start the forwarding update timer routine.
    scheduleAt(
        simTime() + getUpdateTimeout(),
        new cMessage("FwdTimerInit", PDUFTG_SELFMSG_FSUPDATE));

    // Set forwarding table
    fwt = dynamic_cast<PrefixPDUForwardingTable * >(fwdtg->getForwardingTable());
    if(!fwt){
        EV << "Invalid FWTable "<<fwdtg->getForwardingTable()->getFullName()<<" for PrefDistanceVectorPolicy" << endl;
        endSimulation();
    } else {
        fwt->setDelimiter(delimiter);
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
        PDUFTGInfo * flowInfo = flowExists(addr.getIpcAddress().getName(), qos);

        // Flow present? Strange!!!
        if(flowInfo)
        {
            pduftg_debug("Flow for " << addr << " already present!");
        }

        flowInfo = new PDUFTGInfo(
            fwdtg->getIpcAddress(),
            addr,
            qos,
            1);

        // Update the network state too.
        fwdtg->getNetworkState()->push_back(flowInfo);

        // Insert what you consider a neighbor.
        fwdtg->insertNeighbor(addr, qos, port);

        // Add the entry in the table.
        if(table.addOrReplaceEntry(addr.getIpcAddress().getName(), addr.getIpcAddress().getName(), 1, qos)){
            fwt->addEntry(addr.getIpcAddress().getName(), qos, port);
        }
        if(table.addOrReplaceEntry(addr.getIpcAddress().getName(), getNAddr(addr), 1, qos)){
            fwt->addEntryIfNot(getNAddr(addr), qos, port);
        }

        // Debug the actual state of the network.
        pduftg_debug(fwdtg->getIpcAddress().info() << "> " <<
            fwdtg->netInfo());
    }
}

std::string PrefDistanceVectorPolicy::getNAddr(const std::string &addr){
    std::vector<std::string> addrParsed = split(addr, delimiter);

    std::vector<std::string>::iterator itS = addrParsed.begin();
    std::vector<std::string>::iterator itM = thisIPCAddrParsed.begin();

    std::string nAddr = "";
    char d[2] = {delimiter, 0};

    bool first = true;

    while(itS != addrParsed.end() && itM != thisIPCAddrParsed.end()){
        if(!first){
            nAddr.append(d);
        }
        nAddr.append(*itM);

        if(*itS != *itM){
            break;
        }

        itS++;
        itM++;
    }
    if(itS != addrParsed.end() && itM == thisIPCAddrParsed.end()){
        return addr;
    }
    return nAddr;
}

std::string PrefDistanceVectorPolicy::getNAddr(const Address &addr){
    return getNAddr(addr.getIpcAddress().getName());
}

void PrefDistanceVectorPolicy::mergeForwardingInfo(PDUFTGUpdate * info)
{
    PrefPDUFTGUpdate * update = (PrefPDUFTGUpdate*) info;
    for(updatesListIterator it = update->entriesBegin(); it != update->entriesEnd(); it++){

    }
/*
    NetworkState * arrived = info->getInfo();

    // Scan the arrived informations.
    for(NIter i = arrived->begin(); i != arrived->end(); ++i)
    {
        PrefPDUFTGUpdate * eval = (PrefPDUFTGUpdate*)(*i);

        // Do not consider info over yourself.
        if(eval->getDestination() == thisIPCAddr){
            continue;
        }

        // Consider only the common prefix range as addr
        std::string dstAddr = getNAddr(eval->getDestination());

        // Info here are stored with us as source.
        PDUFTGInfo * info = flowExists(dstAddr, eval->getQoSID());


        // We already have such information.
        if(!info || eval->getMetric() + 1 >= info->getMetric()){
            continue;
        }

        removeFlow(dstAddr, eval->getQoSID());

        // It's a better metric; pass through this sender from now on...
        PDUFTGNeighbor * en = fwdtg->neighborExists(info->getSource());
        if(!en) {
            EV << "Could not reach " << eval->getDestination() << " from " << thisIPCAddr << "???\n";
            continue;
        }

        RMTPort * p = en->getPort();
        PDVPInfo * newi = new PDVPInfo(
                dstAddr,
                eval->getQoSID(),
                eval->getMetric() + 1
            );


        // Insert the entry into the tables.
        fwdtg->getNetworkState()->push_back(newi);
        fwt->addEntry(dstAddr, eval->getQoSID(), p);

    }
*/
    // Debug the actual state of the network.
    pduftg_debug(fwdtg->getIpcAddress().info() << "> " << fwdtg->netInfo());
}

PDUFTGUpdate * PrefDistanceVectorPolicy::prepareFSUpdate(Address destination)
{
    PrefPDUFTGUpdate * ret = new PrefPDUFTGUpdate(fwdtg->getIpcAddress(), destination);
    ret->setUpdates(table.getUpdates(destination.getIpcAddress().getName()));
    return ret;
}

void PrefDistanceVectorPolicy::removeFlow(std::string addr, unsigned short qos)
{
    // Select the info with your information evaluation procedure.
    PDUFTGInfo * netinfo = flowExists(addr, qos);

    if(!netinfo)
    {
        fwdtg->getNetworkState()->remove(netinfo);
    }

    qosAddrList changes = table.remove(addr, qos);

    for(qosAddrListIterator it = changes.begin(); it != changes.end(); it++){
        std::string nextH = table.getNextHop(it->second, it->first);
        RMTPort * port  = NULL;
        if(nextH != ""){
            PDUFTGNeighbor *n = fwdtg->neighborExists(Address(it->second.c_str(), fwdtg->getIpcAddress().getDifName().getName().c_str()));
            if(n != NULL){
                port = n->getPort();
            }
        }
        if(port!= NULL) {
            fwt->addEntryIfNot(it->second, it->first, port);
        } else {
            fwt->remove(it->second, it->first);
        }
    }
}
void PrefDistanceVectorPolicy::removeFlow(Address addr, unsigned short qos)
{
    removeFlow(addr.getIpcAddress().getName(), qos);
}


void PrefDistanceVectorPolicy::setUpdateTimeout(unsigned int sec)
{
    updateT = sec;
}
