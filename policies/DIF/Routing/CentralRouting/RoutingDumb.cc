#include "DIF/Routing/CentralRouting/RoutingDumb.h"

Register_Class(RoutingDumb);

void RoutingDumb::onPolicyInit() {
    status_timer = new cMessage("Status timer");
    status_updateInterval = par("status_updateInterval").doubleValue();

    re_status_timer = new cMessage("Re-Status timer");
    re_status_updateInterval = par("re_status_updateInterval").doubleValue();

    st.seqId = 0;
}


void RoutingDumb::finish() {

    if(status_timer != nullptr) { cancelAndDelete(status_timer); }
    if(re_status_timer != nullptr) { cancelAndDelete(re_status_timer); }
}

void RoutingDumb::setMyA(const addr_t & a) {
    myA = a;
    st.node_addr = myA;
}


void RoutingDumb::addNei(const addr_t &a, const Address &addr, const Address &manager, const elink_t &link) {
    neiInfo_dumb & info = neis[a];
    info.addr = addr;
    info.master = manager;
    info.link = link;
    info.zone = getZone(a);
}

void RoutingDumb::onFlow(addr_t a) {
    neiInfo_dumb & info = neis[a];
    info.status = true;

    if(info.started) {
        informStatus();
    }
}

void RoutingDumb::offFlow(addr_t a) {
    neiInfo_dumb & info = neis[a];
    info.status = false;

    if(info.started) {
        informStatus();
    }
}

void RoutingDumb::informStatus() {
    st.fails.clear();
    for(auto & nei : neis) {
        if(nei.second.started && ! nei.second.status) {
            st.fails.insert(nei.second.link);
        }
    }

    if(!status_timer->isScheduled()) {
        scheduleAt(simTime() + status_updateInterval, status_timer);
    }
}

void RoutingDumb::sendInformStatus() {
    if(status_timer->isScheduled()) {
        cancelEvent(status_timer);
    }
    if(re_status_timer->isScheduled()) {
        cancelEvent(re_status_timer);
    }

    if(st.seqId > 0 || !st.fails.empty()) {
        st.seqId++;
        for(auto & nei : neis) {
            if(nei.second.started && nei.second.status) {
                //Send update to all alive neis
                RStatus * up = new RStatus();
                up->setDestination(nei.second.master);
                up->status = st;
                up->received = false;
                sendUpdate(up);
            }
        }

        scheduleAt(simTime() + re_status_updateInterval, re_status_timer);
    }
}

void RoutingDumb::resendInformStatus() {
    bool reschedule =false;
    for(auto & nei : neis) {
        if(nei.second.started && nei.second.status && nei.second.last_ack < st.seqId) {
            //Send update to all alive neis
            RStatus * up = new RStatus();
            up->setDestination(nei.second.master);
            up->status = st;
            up->received = false;
            sendUpdate(up);
            reschedule = true;
        }
    }
    if(reschedule) {
        scheduleAt(simTime() + re_status_updateInterval, re_status_timer);
    }
}

void RoutingDumb::handleMessage(cMessage * msg) {

    if(msg == status_timer) {
            sendInformStatus();
            return;
    }

    if(msg == re_status_timer) {
            resendInformStatus();
            return;
    }

    delete msg;
}

bool RoutingDumb::processUpdate(IntRoutingUpdate * update) {
    if (RStatus * up = dynamic_cast<RStatus *>(update)) {
        // Received ack of status update
        Address src = up->getSource();
        addr_t srcA = parseRawAddr(src.getIpcAddress().getName());
        addr_t srcZ = getZone(srcA);
        for(auto & nei : neis) {
            if(nei.second.zone == srcZ) {
                nei.second.last_ack = up->status.seqId;
            }
        }
        return r_stat != 0;
    }

    if (RStart * up = dynamic_cast<RStart *>(update)) {
        // Received start from zone
        for(auto & nei : neis) {
            if(nei.second.zone == up->zone) {
                nei.second.started = true;
            }
        }
        informStatus();

        return r_stat != 0;
    }

    return r_stat != 0 ;
}
