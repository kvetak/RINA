#include "DIF/Routing/PortsLoadRouting/PortsLoadLS/PortsLoadLS.h"

Register_Class(PortsLoadLS);

void PortsLoadLS::insertFlow(
        const Address &addr,
        const std::string &dst,
        const std::string &qos,
        const unsigned short &metric,
        bool sendUpdate)
{
    // Update/insert the entry.
    neig[qos][addr] = metric;
    // It's a change, mate!
    lastChanges[qos].insert(myAddr);

    // Guess it's some sort of unique id.
    secId++;

    linksU * myEntry = &(netState[qos][myAddr]);
    myEntry->sId = secId;
    myEntry->links[dst] = metric;

    if(sendUpdate)
    {
        // Schedule the update, bro'!
        scheduleUpdate();
    }
}

void PortsLoadLS::removeFlow(
        const Address &addr,
        const std::string &dst,
        const std::string &qos,
        bool sendUpdate)
{
    neig[qos].erase(addr);

    if(neig[qos].size() <= 0)
    {
        neig.erase(qos);
    }

    // It's a change, mate!
    lastChanges[qos].insert(myAddr);

    // Guess it's some sort of unique id.
    secId++;

    linksU * myEntry = &(netState[qos][myAddr]);
    myEntry->sId = secId;
    myEntry->links.erase(dst);

    if(sendUpdate)
    {
        // Schedule the update, bro'!
        scheduleUpdate();
    }
}


void PortsLoadLS::scheduleUpdate()
{
    Enter_Method_Silent();

    if(!scheduledUpdate)
    {
        scheduledUpdate = true;
        scheduleAt(simTime() + updateTimeout, new cMessage("Time2Update"));
    }
}


//Get Changes
entries2Next PortsLoadLS::getChanges()
{
    entries2Next ret;
    for(
            linksStColIt qosIt = netState.begin();
            qosIt != netState.end();
            qosIt++)
    {
        std::string qos = qosIt->first;
        TreeNode t = constructTree(qosIt->second);

        for(TreeNodeIt it = t.chl.begin(); it != t.chl.end(); it++)
        {
            ret[qosPaddr(qos, (*it)->addr)] = (*it)->addr;
            addRecursive(ret, qos, (*it)->addr, *it);
        }
    }

    entries2Next t = ret;

    for(entries2NextIt tIt = table.begin(); tIt != table.end(); tIt++)
    {
        if (ret[tIt->first]  == tIt->second){
            ret.erase(tIt->first);
        }
    }

    table = t;

    return ret;
}

entries2Next PortsLoadLS::getAll(){
    entries2Next ret;

    for(
            linksStColIt qosIt = netState.begin();
            qosIt != netState.end();
            qosIt++)
    {
        std::string qos = qosIt->first;
        TreeNode t = constructTree(qosIt->second);

        for(TreeNodeIt it = t.chl.begin(); it != t.chl.end(); it++)
        {
            ret[qosPaddr(qos, (*it)->addr)] = (*it)->addr;
            addRecursive(ret, qos, (*it)->addr, *it);
        }
    }

    table = ret;
    return table;
}

TreeNode PortsLoadLS::constructTree(linksSt &ls)
{
    TreeNode t(myAddr, 0);
    aMap added;
    added[myAddr] = 0;

    wMap waiting;
    aMap * links = &(ls[myAddr].links);

    for(linksIt it = links->begin(); it !=links->end(); it++)
    {
        waiting[it->first] = psT(&t, it->second);
    }

    while(!waiting.empty())
    {
        unsigned short min = UINT16_MAX;
        addrList mins;

        for (wMapIt it = waiting.begin(); it != waiting.end(); it++)
        {
            if(it->second.metric < min)
            {
                min = it->second.metric;
                mins.clear();
            }
            if(it->second.metric == min)
            {
                mins.push_back(it->first);
            }
        }

        while(!mins.empty())
        {
            std::string addr = mins.back();
            mins.pop_back();

            psT ps = waiting[addr];
            waiting.erase(addr);

            TreeNode * nt = new TreeNode(addr, ps.metric);
            ps.p->chl.insert(nt);

            added[addr] = ps.metric;

            links = &(ls[addr].links);

            for(linksIt it = links->begin(); it !=links->end(); it++)
            {
                std::string daddr = it->first;

                if(added.find(daddr) == added.end())
                {
                    wMapIt eI = waiting.find(daddr);

                    if(eI == waiting.end())
                    {
                        waiting[daddr] = psT(nt, ps.metric + it->second);

                    }
                    else if(eI->second.metric > ps.metric + it->second)
                    {
                        eI->second.metric = ps.metric + it->second;
                        eI->second.p = nt;
                    }
                }
            }
        }
    }

    return t;
}
void PortsLoadLS::addRecursive(
        entries2Next &ret,
        const std::string &qos,
        const std::string &next, TreeNode * t)
{
    for(TreeNodeIt it = t->chl.begin(); it != t->chl.end(); it++)
    {
        ret[qosPaddr(qos, (*it)->addr)] = next;
        addRecursive(ret, qos, next, *it);
    }
}

bool PortsLoadLS::processUpdate(IntRoutingUpdate * update)
{
    PortsLoadRU * up = dynamic_cast<PortsLoadRU *>(update);

    std::string qos = up->getQoS();
    linksSt * st = &(netState[qos]);

    // Not of the type we desire.
    if(!up)
    {
        return false;
    }

    for(linksStIt it = up->entriesBegin(); it != up->entriesEnd(); it++)
    {
        std::string node = it->first;

        if((*st)[node].sId < it->second.sId){
            (*st)[node] = it->second;
            lastChanges[qos].insert(node);
        }
    }

    if(!lastChanges.empty())
    {
        scheduleUpdate();
        return true;
    }

    return false;
}

// Called after initialize
void PortsLoadLS::onPolicyInit()
{
    myAddr = par("myAddr").stdstringValue();

    if(myAddr == "")
    {
        myAddr = myAddress.getIpcAddress().getName();
    }

    updateTimeout = par("updateTimeout");

    scheduledUpdate = false;

    infMetric = 32;
    secId = 1;
}


void PortsLoadLS::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage())
    {
        //Iterate all Qos
        for(qosNeighMetricIt it = neig.begin(); it!= neig.end(); it++)
        {
            //get Changes per QoS;
            linksSt _entries = getChangedEntries(it->first);

            //iterate all Qos->Neighbour
            for(
                    neighMetricIt it2 = it->second.begin();
                    it2 != it->second.end();
                    it2++)
            {
                //New Update to QoS + Neighbour
                PortsLoadRU * update = new PortsLoadRU(it2->first, it->first);

                //Add entries
                update->setEntries(_entries);

                //And send
                sendUpdate(update);
            }
        }

        lastChanges.clear();
        scheduledUpdate = false;
    }
    delete msg;
}

linksSt PortsLoadLS::getChangedEntries (const std::string &qos)
{
    linksSt ret;
    addrSet * set = &lastChanges[qos];

    for(addrSetIt it = set->begin(); it != set->end(); it++)
    {
        ret.insert(linksStEntry(*it, netState[qos][*it]));
    }

    return ret;
}


void PortsLoadLS::finish()
{
    IntRouting::finish();

    EV << "I'm "<< myAddr<<endl;

    for(
            linksStColIt qosIt = netState.begin();
            qosIt != netState.end();
            qosIt++)
    {
        EV << "  QoS " << qosIt->first<<endl;
        TreeNode t = constructTree(qosIt->second);

        for(TreeNodeIt it = t.chl.begin(); it != t.chl.end(); it++)
        {
            printTreeNode(*it, (*it)->addr);
        }

    }
}

void PortsLoadLS::printTreeNode(TreeNode *t, const std::string &next)
{
    EV<<"    " << t->addr << " -> "<<next << " ("<<t->metric<<") "
            << " c: "<< t->chl.size() << endl;

    for(TreeNodeIt it = t->chl.begin(); it != t->chl.end(); it++)
    {
        printTreeNode(*it, next);
    }
}
