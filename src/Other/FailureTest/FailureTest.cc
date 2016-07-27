#include "FailureTest.h"

FailureTest * FailureTest::instance = nullptr;

Define_Module(FailureTest);


void FailureTest::initialize() {
    FailureTest::instance = this;


    killTimer = new cMessage("Kill Time");
    resurrectTimer = new cMessage("Resurrect Time");


    c = par("amount").longValue();
    double tK = par("killAt").doubleValue();
    double tR = par("resurrectAt").doubleValue();

    if(c > 0 && tK > simTime().dbl()) {
        scheduleAt(tK, killTimer);
        if(tK < tR) {
            scheduleAt(tR, resurrectTimer);
        }
    }
}

void FailureTest::finish(){
    cancelAndDelete(killTimer);
    cancelAndDelete(resurrectTimer);
}

void FailureTest::handleMessage(cMessage * msg) {
    if(msg == killTimer) {
        if(alive.size() <= c) {
            cout << "Kill all"<<endl;
            for(auto & link : alive) {
                for(auto m : link2Nodes[link]) {
                    m->killLink(link);
                }
                dead.insert(link);
            }
            dead.clear();
        } else {
            cout << "Kill "<< c <<endl;
            for(unsigned int i = 0; i < c ; i++) {
                auto it = alive.begin();
                advance(it, intuniform(0, alive.size()));
                string link = *it;
                for(auto m : link2Nodes[link]) {
                    m->killLink(link);
                }
                dead.insert(link);
                alive.erase(link);
            }
        }
    } else if (msg == resurrectTimer) {
        for(auto & link : dead) {
            for(auto m : link2Nodes[link]) {
                m->resurrectLink(link);
            }
            alive.insert(link);
        }
        dead.clear();
    }
}

void FailureTest::registerLink(const string & link, FailureNode * owner) {
    alive.insert(link);
    link2Nodes[link].push_back(owner);
}
