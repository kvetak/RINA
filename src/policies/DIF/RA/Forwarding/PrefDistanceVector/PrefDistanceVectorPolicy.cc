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
                fwt->addEntry(e->getDestAddr().getIpcAddress().getName(), e->getQosId(), e->getPort());

                std::string naddr =  getNAddr(e->getDestAddr());
                if(table.addOrReplaceEntry(
                        e->getDestAddr().getIpcAddress().getName(),
                        naddr,
                        1, e->getQosId(),
                        naddr != e->getDestAddr().getIpcAddress().getName()
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


    if(showNetState)
    {
        nstm->getDisplayString().setTagArg("t", 0, table.prepareFriendlyNetState().c_str());
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
                fwdtg->signalForwardingInfoUpdate(prepareFSUpdate(info->getDestAddr()));
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
    // Display active policy name.
    PDUFTGPolicy::initialize();


    any = par("any").stdstringValue();
    std::string del = par("delimiter").stdstringValue();
    if(del.length() > 0 && del.at(0)!= ' '){
        delimiter = del.at(0);
    } else {
        delimiter = '.';
    }

    thisIPCAddr = fwdtg->getIpcAddress().getIpcAddress().getName();
    thisIPCAddrParsed = split(thisIPCAddr, delimiter);
    table.setIm(thisIPCAddr);

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

    // Will show the fwd table in the simulation?
    showNetState = par("netStateVisible").boolValue();
    // Where will the report be seen?
    nstm = check_and_cast<cModule *>
        (getModuleByPath(par("netStateMod").stringValue()));

    if(showNetState)
    {
        // Put the report on the desired position.
        nstm->getDisplayString().setTagArg(
            "t", 1, par("netStateAlign").stringValue());
    }


}

void PrefDistanceVectorPolicy::finish(){

    if( par("showAtEnd").boolValue()){
        EV << "Node " << fwdtg->getIpcAddress()<<endl;
        EV << "Routing table:"<< endl;
        EV << table.prepareFriendlyNetState() <<endl;
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
    if(addr.getDifName() == fwdtg->getIpcAddress().getDifName() && !(addr == fwdtg->getIpcAddress()))
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


        table.addQoS(qos);
        // Add the entry in the table.
      //  if(table.addOrReplaceEntry(addr.getIpcAddress().getName(), addr.getIpcAddress().getName(), 1, qos)){
            fwt->addEntry(addr.getIpcAddress().getName(), qos, port);
      //  }

        std::string naddr = getNAddr(addr);
        if(table.addOrReplaceEntry( naddr, addr.getIpcAddress().getName(), 1, qos, !neighbour(addr.getIpcAddress().getName()))){
            fwt->addEntryIfNot(naddr, qos, port);
        }

        // Debug the actual state of the network.
        pduftg_debug(fwdtg->getIpcAddress().info() << "> " <<
            fwdtg->netInfo());



        if(showNetState)
        {
            nstm->getDisplayString().setTagArg("t", 0, table.prepareFriendlyNetState().c_str());
        }
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
        nAddr.append(*itS);

        if(*itS != *itM){
            break;
        }

        itS++;
        itM++;
        first = false;
    }
    return nAddr;
}

bool PrefDistanceVectorPolicy::im(const std::string &addr){
    std::vector<std::string> addrParsed = split(addr, delimiter);

    std::vector<std::string>::iterator itS = addrParsed.begin();
    std::vector<std::string>::iterator itM = thisIPCAddrParsed.begin();

    while(itS != addrParsed.end() && itM != thisIPCAddrParsed.end()){
        if(*itS != *itM){
            return false;
        }

        itS++;
        itM++;
    }
    return itS == addrParsed.end();
}

bool PrefDistanceVectorPolicy::neighbour(const std::string &addr){
    std::vector<std::string> addrParsed = split(addr, delimiter);

    std::vector<std::string>::iterator itS = addrParsed.begin();
    std::vector<std::string>::iterator itM = thisIPCAddrParsed.begin();




    while(itS != addrParsed.end() && itM != thisIPCAddrParsed.end()){
        if((itM+1) == thisIPCAddrParsed.end()){
            return true;
        }
        if(*itS != *itM){
            return false;
        }

        itS++;
        itM++;
    }
    return itM == thisIPCAddrParsed.end();
}

std::string PrefDistanceVectorPolicy::getNAddr(const Address &addr){
    return getNAddr(addr.getIpcAddress().getName());
}

void PrefDistanceVectorPolicy::mergeForwardingInfo(PDUFTGUpdate * info)
{
    std::string nextH = info->getSource().getIpcAddress().getName();

    PrefPDUFTGUpdate * update = (PrefPDUFTGUpdate*) info;

    for(updatesListIterator it = update->entriesBegin(); it != update->entriesEnd(); it++){
        EV << "At "<<fwdtg->getIpcAddress()<< ", I'm : "<<it->dst << " == " <<im(it->dst) << endl;
        if(im(it->dst)){
            continue;
        } else {
            EV << "Add entry?" << endl;
        }
        std::string pDst = getNAddr(it->dst);
        // Add the entry in the table.
        if(table.addOrReplaceEntry(pDst, nextH, it->metric+1, it->qos, !neighbour(it->dst))){
            std::string nextH = table.getNextHop(pDst, it->qos);
            if(nextH!=""){
                fwt->addEntry(pDst, it->qos, fwt->lookup(nextH, it->qos));
            } else {
                fwt->remove(pDst, it->qos);
            }
        }
    }

    // Debug the actual state of the network.
    pduftg_debug(fwdtg->getIpcAddress().info() << "> " << fwdtg->netInfo());


    if(showNetState)
    {
        nstm->getDisplayString().setTagArg("t", 0, table.prepareFriendlyNetState().c_str());
    }
}

PDUFTGUpdate * PrefDistanceVectorPolicy::prepareFSUpdate(Address destination)
{
    PrefPDUFTGUpdate * ret = new PrefPDUFTGUpdate(fwdtg->getIpcAddress(), destination);
    ret->setUpdates(
            table.getUpdates(destination.getIpcAddress().getName(),
                    //im(destination.getIpcAddress().getName())
                    neighbour(destination.getIpcAddress().getName())
                    ));
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

