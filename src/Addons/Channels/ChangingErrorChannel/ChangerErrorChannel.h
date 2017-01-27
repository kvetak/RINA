#pragma once

#include <omnetpp.h>

#include <vector>
#include "Addons/Channels/ChangingErrorChannel/ChangingErrorChannel.h"

using namespace std;

class ChangerErrorChannel : public cSimpleModule {
public:
    void initialize();
    void finish();

    static void registerChannel(ChangingErrorChannel * chan, string name);

    void handleMessage(cMessage * msg);


protected:
    static map<string, vector<ChangingErrorChannel *> > channels;
};

