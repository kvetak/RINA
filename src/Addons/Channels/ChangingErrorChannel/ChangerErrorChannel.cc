#include "Addons/Channels/ChangingErrorChannel/ChangerErrorChannel.h"

map<string, vector<ChangingErrorChannel *> > ChangerErrorChannel::channels =
        map<string, vector<ChangingErrorChannel *> >();

Define_Module(ChangerErrorChannel);

void ChangerErrorChannel::initialize() {
    double problemsAt = par("problemsAt").doubleValue();
    if(problemsAt > 0) {
        scheduleAt(problemsAt, new cMessage("change BER"));
    }
}

void ChangerErrorChannel::finish() {}

void ChangerErrorChannel::registerChannel(ChangingErrorChannel * chan, string name) {
    channels[name].push_back(chan);
}

void ChangerErrorChannel::handleMessage(cMessage * msg) {
    if(ChangerErrorChannel::channels.empty()) {
        delete msg;
        return;
    }

    double newBer = par("newBer").doubleValue();
    if(newBer < 0.0 ) { newBer = 0.0; }
    if(newBer > 1.0 ) { newBer = 1.0; }

    double newDataRate = par("newDataRate").doubleValue();
    if(newDataRate < 0.0 ) { newDataRate = 0.0; }

    auto it = ChangerErrorChannel::channels.begin();
    if(it->second.empty()) {
        ChangerErrorChannel::channels.erase(it);
        scheduleAt(simTime(), msg);
    } else {
        auto chanIt = it->second.begin();
        (*chanIt)->setDatarate(newDataRate);
        (*chanIt)->setBitErrorRate(newBer);

        it->second.erase(chanIt);
        if(it->second.empty()) {
            ChangerErrorChannel::channels.erase(it);
        }
        scheduleAt(simTime()+par("changeEach").doubleValue(), msg);
    }
}
