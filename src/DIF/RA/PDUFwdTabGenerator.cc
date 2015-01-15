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
 * @file PDUFwdTabGenerator.cc
 * @author Tomas Hykel (xhykel01@stud.fit.vutbr.cz), Kewin Rausch(kewin.rausch@create-net.org)
 * @brief PDU forwarding (routing) table generator.
 * @detail Responds to various events happening inside the IPC process
 *         by adding, removing and editing entries in the forwarding table.
 */

// HOWTO Read: Procedures are sorted by name.

#include "PDUFwdTabGenerator.h"
#include "StaticRoutingPolicy.h"
#include "DistanceVectorPolicy.h"

#ifdef PDUFTG_PRIVATE_DEBUG
std::ofstream pduftg_debug_file;
#endif

Define_Module(PDUFwdTabGenerator);

void PDUFwdTabGenerator::finish()
{
#ifdef PDUFTG_PRIVATE_DEBUG
    pduftg_debug_file.flush();
    pduftg_debug_file.close();
#endif
}

PDUForwardingTable * PDUFwdTabGenerator::getForwardingTable()
{
    return fwTable;
}

Address PDUFwdTabGenerator::getIpcAddress()
{
    return ipcAddr;
}

NeighborState * PDUFwdTabGenerator::getNeighborhoodState()
{
    return &neiState;
}

NetworkState * PDUFwdTabGenerator::getNetworkState()
{
    return &netState;
}

PDUForwardingTableEntry * PDUFwdTabGenerator::getNextNeighbor(Address destination, unsigned short qos)
{
    RMTPort * p = getForwardingTable()->lookup(destination, qos);

    if(p)
    {
        for(EIter it = neiState.begin(); it != neiState.end(); ++it )
        {
            PDUForwardingTableEntry * e = (*it);

            // Found the port used for the forwarding table; so it's the next neighbor.
            if(!strcmp(p->info().c_str(), e->getPort()->info().c_str()))
            {
                return e;
            }
        }
    }
    else
    {
        pduftg_debug(ipcAddr.info() <<
            "Neighbor to reach " << destination << " cannot be found.\n");
    }

    return NULL;
}

NM1FlowTable * PDUFwdTabGenerator::getNM1FlowTable()
{
    return flTable;
}

void PDUFwdTabGenerator::handleUpdateMessage(FSUpdateInfo * info)
{
    if(fwdPolicy)
    {
        // Let the policy decide what to do here.
        fwdPolicy->mergeForwardingInfo(info);
    }
    else
    {
        pduftg_debug(ipcAddr.info() <<
            "> PDUFTG Error: no forwarding policy selected!\n");
    }

    // Show the status of the forwarding table?
    if(showNetState)
    {
        nstm->getDisplayString().setTagArg("t", 0, prepareFriendlyNetState().c_str());
    }
}

void PDUFwdTabGenerator::handleMessage(cMessage * msg)
{

}

void PDUFwdTabGenerator::initialize()
{
    // IPCProcess module.
    cModule * ipcModule = getParentModule()->getParentModule();

    fwdPolicy = check_and_cast<PDUFTGPolicy *>
        (getModuleByPath("^.PDUFTGPolicy"));
    fwTable   = check_and_cast<PDUForwardingTable *>
        (getModuleByPath("^.pduForwardingTable"));
    flTable   = check_and_cast<NM1FlowTable *>
        (getModuleByPath("^.nm1FlowTable"));

    ipcAddr   = Address(
        ipcModule->par("ipcAddress").stringValue(),
        ipcModule->par("difName").stringValue());

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

    // Initializes the input/output of the module.
    initializeSignalsAndListeners();

#ifdef PDUFTG_PRIVATE_DEBUG
    if(!pduftg_debug_file.is_open())
    {
        pduftg_debug_file.open("pduftg.log");
    }
#endif
}

void PDUFwdTabGenerator::initializeSignalsAndListeners()
{
    cModule* catcher1 = this->getParentModule()->getParentModule();

    // Signal emitters; there will be part of our outputs.
    sigPDUFTGFwdInfoUpdate = registerSignal(SIG_PDUFTG_FwdInfoUpdate);

    // Signal receivers; there will be part of our inputs.
    lisInfoRecv = new LisPDUFTGFwdInfoRecv(this);
    catcher1->subscribe(SIG_RIBD_ForwardingUpdateReceived, lisInfoRecv);
}

void PDUFwdTabGenerator::insertFlowInfo(Address addr, unsigned short qos, RMTPort * port)
{


    // Is a policy defined?
    if(fwdPolicy)
    {
        fwdPolicy->insertNewFlow(addr, qos, port);
    }
    // What to do if no policy has been set?
    else
    {
        pduftg_debug(ipcAddr.info() <<
            "> PDUFTG Error: no forwarding policy selected!\n");
    }

    // Show the status of the forwarding table?
    if(showNetState)
    {
        nstm->getDisplayString().setTagArg("t", 0, prepareFriendlyNetState().c_str());
    }
}

void PDUFwdTabGenerator::insertNeighbor(Address addr, short unsigned qos, RMTPort * p)
{
    //EV << "INSN " << addr << " this ipc " << ipcAddr;

    // As for network informations, we're interested only on IPC located on
    // our same layer. We must not know of N+1 or N-1 IPCs.
    //
    if(addr.getDifName() == ipcAddr.getDifName())
    {
        neiState.push_back(new PDUForwardingTableEntry(addr, qos, p));
    }
}

void PDUFwdTabGenerator::insertNetInfo(Address dest, short unsigned int qos, RMTPort * port, unsigned int metric)
{
    // Filter the flows created through RA; we're interested in the information about our
    // DIF, not on the ones of the others(N+1 or N-1).
    //
    if(dest.getDifName() == ipcAddr.getDifName())
    {
        FSInfo * i = netInfoExists(dest, qos);

        // Not already existing in our Flow list.
        if(!i)
        {
            i = new FSInfo(
                // From...
                ipcAddr,
                // ... to ...
                dest,
                // ... with QoS ...
                qos,
                // ... and metric.
                metric);

            // Just push it in the list.
            netState.push_back(i);
        }
    }
}

std::string PDUFwdTabGenerator::neiInfo()
{
    std::stringstream os;

    os << "Neighbors counts: " << neiState.size() << "\n";

    for(EIter it = neiState.begin(); it != neiState.end(); ++it )
    {
        PDUForwardingTableEntry * e = (*it);

        os << "Neighbor " << e->getDestAddr() << endl;

        os << "\n";
    }

    return os.str();
}

std::string PDUFwdTabGenerator::netInfo()
{
    std::stringstream os;

    os << "Network state counts: " << netState.size() << "\n";

    for(NIter it = netState.begin(); it != netState.end(); ++it )
    {
        FSInfo * fsi = (*it);
        NM1FlowTableItem * p = flTable->findFlowByDstApni(fsi->getDestination().getApname().getName(), fsi->getQoSID());

        os << "[From: " << fsi->getSource() << " to: " << fsi->getDestination() << " qos: " << fsi->getQoSID() << " hops: " << fsi->getMetric();

        if(p)
        {
            RMTQueue* o = p->getRmtPort()->getOutputQueues().front();

            os << " through port " << o->info() << " (is neighbor)";
        }

        os << "]\n";
    }

    return os.str();
}

PDUForwardingTableEntry * PDUFwdTabGenerator::neighborExists(Address addr)
{
    for(EIter it = neiState.begin(); it != neiState.end(); ++it )
    {
        PDUForwardingTableEntry * e = (*it);

        if(e->getDestAddr() == addr)
        {
            return e;
        }
    }

    return NULL;
}

FSInfo * PDUFwdTabGenerator::netInfoExists(Address dest, unsigned short qos)
{
    for(NIter it = netState.begin(); it != netState.end(); ++it )
    {
        FSInfo * fsi = (*it);

        // Equal condition; same source reach same destination with same qos constrain.
        if(fsi->getDestination() == dest && fsi->getQoSID() == qos)
        {
            return fsi;
        }
    }

    return NULL;
}

void PDUFwdTabGenerator::publishPolicy(PDUFTGPolicy * p)
{
    unpublishPolicy();

    fwdPolicy = p;
    // Recomputes the policy according to the new policy.
    fwdPolicy->computeForwardingTable();
}

std::string PDUFwdTabGenerator::prepareFriendlyNetState()
{
    std::stringstream os;

    for(NIter it = netState.begin(); it != netState.end(); ++it )
    {
        FSInfo * fsi = (*it);

        os << fsi->getDestination() << ", " << fsi->getMetric() << endl;
    }

    return os.str();
}

void PDUFwdTabGenerator::unpublishPolicy()
{
    // Clean the forwarding table; we'll regenerate it during the apply of a new policy.
    fwTable->clean();

    // Release the resources.
    delete fwdPolicy;
    fwdPolicy = NULL;
}

void PDUFwdTabGenerator::removeFlowInfo(RMTPort * port)
{
    for(EIter it = neiState.begin(); it != neiState.end(); ++it )
    {
        PDUForwardingTableEntry * e = (*it);

        if(port == e->getPort())
        {
            // Signal the removing of the flow at the policy, first.
            fwdPolicy->removeFlow(e->getDestAddr(), e->getQosId());

            // Remove the entries previously registered.
            removeNeiInfo(e->getDestAddr());
            removeNetInfo(netInfoExists(e->getDestAddr(), e->getQosId()));

            return;
        }
    }
}

void PDUFwdTabGenerator::removeNeiInfo(Address addr)
{
    for(EIter it = neiState.begin(); it != neiState.end(); ++it )
    {
        PDUForwardingTableEntry * e = (*it);

        if(e->getDestAddr() == addr)
        {
            neiState.erase(it);
        }
    }
}

void PDUFwdTabGenerator::removeNetInfo(FSInfo * info)
{
    netState.remove(info);
}

void PDUFwdTabGenerator::reportBubbleInfo(const char * message)
{
    nstm->bubble(message);
}

void PDUFwdTabGenerator::signalForwardingInfoUpdate(FSUpdateInfo * info)
{
    pduftg_debug(ipcAddr.info() <<
        "> Signal an update to " << info->getDestination() << "\n");

    // Emit the signal. RIBd shall be there to listen...
    emit(sigPDUFTGFwdInfoUpdate, info);
}
