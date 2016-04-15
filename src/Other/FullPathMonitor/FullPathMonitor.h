#pragma once
#include <omnetpp.h>
#include <iostream>
#include <fstream>

#include "MultipathStructs.h"

namespace FullPathMonitor {

    using namespace std;

    class FullPathMonitor  : public cSimpleModule {

    public:

        void initialize();
        void finish();

    private:

        void handleMessage(cMessage * msg);


    };
}
