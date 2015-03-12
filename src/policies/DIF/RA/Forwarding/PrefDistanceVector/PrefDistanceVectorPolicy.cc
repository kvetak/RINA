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



addrInfo::addrInfo(std::string _addr){
    parent = false;
    son = false;
    neighbour = false;
    addr = _addr;
    commonPrefix = "";
    prefSize = 0;
    storedAddr = "";
}

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

                addrInfo inA = parseAddr(e->getDestAddr().getIpcAddress().getName()) ;
                bool stored = false;
                if(inA.parent){
                    stored = table.addOrReplaceParent(e->getDestAddr().getIpcAddress().getName(),1, e->getQosId());
                } else if(inA.son){
                    stored = table.addOrReplaceSon(inA.storedAddr, e->getDestAddr().getIpcAddress().getName(),1, e->getQosId());
                } else if(inA.neighbour){
                    stored = table.addOrReplaceNeighbour(inA.storedAddr, e->getDestAddr().getIpcAddress().getName(),1, e->getQosId());
                } else {
                    stored = table.addOrReplaceRand(inA.storedAddr, e->getDestAddr().getIpcAddress().getName(),1, e->getQosId(), inA.prefSize);
                }
                if(stored) {
                    fwt->addEntryIfNot(inA.storedAddr, e->getQosId(), e->getPort());
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

unsigned int PrefDistanceVectorPolicy::getForcedUpdateTimeout()
{
    return updateFT;
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

            if(lastUpdate+getUpdateTimeout() > simTime()){
                scheduleAt(
                        lastUpdate + getUpdateTimeout(),
                    new cMessage("UpdateRequested", PDUFTG_SELFMSG_FSUPDATE));
                break;
            }

            if(forcedUpdateProgramed){
                scheduleAt(
                    simTime() + getUpdateTimeout(),
                    new cMessage("UpdateRequested", PDUFTG_SELFMSG_FSUPDATE));
                break;

            }

            n = fwdtg->getNeighborhoodState();

            for(EIter it = n->begin(); it != n->end(); ++it)
            {
                PDUFTGNeighbor * info = (*it);

                // Finally send the update.
                fwdtg->signalForwardingInfoUpdate(prepareFSUpdate(info->getDestAddr()));
            }

            lastUpdate = simTime();

            scheduleAt(
                simTime() + getUpdateTimeout(),
                new cMessage("UpdateRequested", PDUFTG_SELFMSG_FSUPDATE));

            break;
        case PDUFTG_SELFMSG_FSUPDATEFORCE:
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
            lastUpdate = simTime();
            forcedUpdateProgramed = false;

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
    thisIPCAddrOPref = join(thisIPCAddrParsed, thisIPCAddrParsed.size()-1, delimiter);
    table.setIm(thisIPCAddr);

    // Default timeout 30 seconds.
    setUpdateTimeout(60);
    setForcedUpdateTimeout(1);
    forcedUpdateProgramed = false;

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

void PrefDistanceVectorPolicy::ForceUpdate(){
    Enter_Method_Silent();
    if(forcedUpdateProgramed){
        return;
    }

    // Start the forwarding update timer routine.
    scheduleAt(
        simTime() + getForcedUpdateTimeout(),
        new cMessage("FwdTimerForced", PDUFTG_SELFMSG_FSUPDATEFORCE));
    forcedUpdateProgramed = true;
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

        addrInfo inA = parseAddr(addr.getIpcAddress().getName()) ;

        address2Qos[inA.addr].insert(qos);
        qosAddr2Port[qosAddr(qos, inA.addr)] = port;

        table.addQoS(qos);
        // Add the entry in the table.
        fwt->addEntry(inA.addr, qos, port);

        bool stored = false;
        if(inA.parent){
            stored = table.addOrReplaceParent(addr.getIpcAddress().getName(),1, qos);
        } else if(inA.son){
            stored = table.addOrReplaceSon(inA.storedAddr, addr.getIpcAddress().getName(),1, qos);
        } else if(inA.neighbour){
            stored = table.addOrReplaceNeighbour(inA.storedAddr, addr.getIpcAddress().getName(),1, qos);
        } else {
            stored = table.addOrReplaceRand(inA.storedAddr, addr.getIpcAddress().getName(),1, qos, inA.prefSize);
        }
        if(stored) {
            fwt->addEntryIfNot(inA.storedAddr, qos, port);
        }

        // Debug the actual state of the network.
        pduftg_debug(fwdtg->getIpcAddress().info() << "> " <<
            fwdtg->netInfo());

        ForceUpdate();
        /*
        scheduleAt(
            simTime() + getUpdateTimeout(),
            new cMessage("FwdTimerInit", PDUFTG_SELFMSG_FSUPDATE));
        */

        if(showNetState)
        {
            nstm->getDisplayString().setTagArg("t", 0, table.prepareFriendlyNetState().c_str());
        }
    }

}

void PrefDistanceVectorPolicy::mergeForwardingInfo(PDUFTGUpdate * info)
{

    std::string nextH = info->getSource().getIpcAddress().getName();

    PrefPDUFTGUpdate * update = (PrefPDUFTGUpdate*) info;

    std::string src = info->getSource().getIpcAddress().getName();
    bool changes = false;

    for(updatesListIterator it = update->entriesBegin(); it != update->entriesEnd(); it++){
        //EV << "At "<<fwdtg->getIpcAddress()<< ", I'm : "<<it->dst << " == " <<im(it->dst) << endl;
        if(it->dst == thisIPCAddr){
            continue;
        }

        addrInfo inA = parseAddr(it->dst);
    //    EV << "Entry " << inA.addr << " ("<< inA.storedAddr<<")"<<endl;

        if(address2Qos[src].find(it->qos) == address2Qos[src].end()){
            continue;
        }

        bool stored = false;
        std::string nextH = "";
        if(inA.parent){
            stored = table.addOrReplaceParent(src,it->metric+1, it->qos);
            if(stored){
                nextH = table.getNextHopParent(it->qos);
            }
        } else if(inA.son){
            stored = table.addOrReplaceSon(inA.storedAddr, src,it->metric+1, it->qos);
            if(stored){
                nextH = table.getNextHopSon(inA.storedAddr, it->qos);
            }
        } else if(inA.neighbour){
            stored = table.addOrReplaceNeighbour(inA.storedAddr, src,it->metric+1, it->qos);
            if(stored){
                nextH = table.getNextHopNeighbour(inA.storedAddr, it->qos);
            }
        } else {
            if(inA.storedAddr!= "") {
                stored = table.addOrReplaceRand(inA.storedAddr, src,it->metric+1, it->qos, inA.prefSize);
                if(stored){
                    nextH = table.getNextHopRand(inA.storedAddr, it->qos);
                }
            }
        }
        if(stored) {
            replaceOrRemoveFwtEntry(inA.storedAddr, nextH, it->qos);
            changes = true;
        }
    }

    if(changes){
        ForceUpdate();
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

    std::string dst = destination.getIpcAddress().getName();

    addrInfo inA = parseAddr(destination.getIpcAddress().getName());

    for(std::set<unsigned short>::iterator it = address2Qos[dst].begin(); it != address2Qos[dst].end(); it++){
        unsigned short qos = *it;
        if(inA.son){
            ret->addEntry(qos, "", 0);
            ret->addEntries(table.getUpdatesSon(inA.addr, qos));
            ret->addEntries(table.getUpdatesRand(inA.addr, inA.storedAddr, qos, inA.prefSize));
        } else if(inA.parent){
            ret->addEntries(table.getUpdatesNeighbour(inA.addr, qos));
            ret->addEntries(table.getUpdatesRand(inA.addr, inA.storedAddr, qos, inA.prefSize));
        } else if(inA.neighbour){
            ret->addEntries(table.getUpdatesParent(inA.addr, thisIPCAddrOPref, qos));
            ret->addEntries(table.getUpdatesNeighbour(inA.addr, qos));
            ret->addEntries(table.getUpdatesRand(inA.addr, inA.storedAddr, qos, inA.prefSize));
        } else {
            ret->addEntry(qos, thisIPCAddr, 0);
            ret->addEntries(table.getUpdatesRand(inA.addr, inA.storedAddr, qos, inA.prefSize));
        }
    }

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

    address2Qos[addr].erase(qos);
    qosAddr2Port.erase(qosAddr(qos, addr));

    AddrList changes;

    changes = table.removeSons(addr, qos);
    for(AddrListIterator it = changes.begin(); it != changes.end(); it++){
        replaceOrRemoveFwtEntry(*it, table.getNextHopSon(*it, qos), qos);
    }
    changes = table.removeNeighbours(addr, qos);
    for(AddrListIterator it = changes.begin(); it != changes.end(); it++){
        replaceOrRemoveFwtEntry(*it, table.getNextHopNeighbour(*it, qos), qos);
    }
    changes = table.removeParent(addr, qos);
    for(AddrListIterator it = changes.begin(); it != changes.end(); it++){
        replaceOrRemoveFwtEntry(*it, table.getNextHopParent(qos), qos);
    }
    changes = table.removeRand(addr, qos);
    for(AddrListIterator it = changes.begin(); it != changes.end(); it++){
        replaceOrRemoveFwtEntry(*it, table.getNextHopRand(*it, qos), qos);
    }


}

void PrefDistanceVectorPolicy::replaceOrRemoveFwtEntry(std::string dst, std::string nextH, unsigned short qos){

    RMTPort * port  = NULL;
    if(nextH != ""){
        qosAddr qa = qosAddr(qos, nextH);
        if(qosAddr2Port.find(qa) != qosAddr2Port.end()){
            port = qosAddr2Port[qosAddr(qos, nextH)];
        }
    }

    if(port!= NULL) {
        fwt->addEntryIfNot(dst, qos, port);
    } else {
        fwt->remove(dst, qos);
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
void PrefDistanceVectorPolicy::setForcedUpdateTimeout(unsigned int sec)
{
    updateFT = sec;
}



addrInfo PrefDistanceVectorPolicy::parseAddr(std::string addr){
    addrInfo info(addr);


    std::vector<std::string> addrParsed = split(addr, delimiter);

    if(addr!= "" && addrParsed.size() == thisIPCAddrParsed.size() - 1 && isPrefix(addr, thisIPCAddr)){
        info.parent = true;
        info.commonPrefix = addr;
        return info;
    }
    if(isPrefix(thisIPCAddr, addr)){
        info.son = true;
        info.commonPrefix = thisIPCAddr;
        if(addrParsed.size() == thisIPCAddrParsed.size()+1){
            info.storedAddr = addr;
        } else {
            info.storedAddr = join(addrParsed, thisIPCAddrParsed.size()+1, delimiter);
        }
        return info;
    }

    if((thisIPCAddrOPref != addr) && isPrefix(thisIPCAddrOPref, addr)){
        info.neighbour = true;
        info.commonPrefix = thisIPCAddrOPref;
        info.storedAddr = join(addrParsed, thisIPCAddrParsed.size(), delimiter);
        return info;
    }

    std::vector<std::string>::iterator itS = addrParsed.begin();
    std::vector<std::string>::iterator itM = thisIPCAddrParsed.begin();

    info.prefSize = 0;
    while(itS != addrParsed.end() && itM != thisIPCAddrParsed.end()){
        if(*itS == *itM){
            info.prefSize++;
        } else {
            break;
        }
    }
    if(info.prefSize > 0){
        info.commonPrefix = join(addrParsed, info.prefSize, delimiter);
    }
    info.storedAddr = join(addrParsed, info.prefSize+1, delimiter);


    return info;
}
















