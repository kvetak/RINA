#include "Addons/Actions/FailureSimulation/FailureSimulation.h"

FailureSimulation * FailureSimulation::instance = nullptr;

Define_Module(FailureSimulation);

void FailureSimulation::initialize() {
    FailureSimulation::instance = this;

    killTimer = new cMessage("Kill Time");
    resurrectTimer = new cMessage("Resurrect Time");

    c = par("amount").longValue();
    double tK = par("killAt").doubleValue();
    double tR = par("resurrectAt").doubleValue();
    interKill = par("interKill").doubleValue();
    if (c > 0 && tK > simTime().dbl()) {
        scheduleAt(tK, killTimer);
        if (tK < tR) {
            scheduleAt(tR, resurrectTimer);
        }
    }
}

void FailureSimulation::finish() {
    cancelAndDelete(killTimer);
    cancelAndDelete(resurrectTimer);
}

void FailureSimulation::handleMessage(cMessage * msg) {
    if (msg == killTimer) {
        if (alive.empty() || c < 0) {
            endSimulation();
            return;
        }
        auto it = alive.begin();
        advance(it, omnetpp::intuniform(omnetpp::getEnvir()->getRNG(0), 0, alive.size()));
        string link = *it;
        for (auto m : link2Nodes[link]) {
            m->killLink(link);
        }
        dead.insert(link);
        alive.erase(link);

        c--;
        if (c > 0) {
            scheduleAt(simTime() + interKill, killTimer);
        }
    } else if (msg == resurrectTimer) {
        for (auto & link : dead) {
            for (auto m : link2Nodes[link]) {
                m->resurrectLink(link);
            }
            alive.insert(link);
        }
        dead.clear();
    }
}

void FailureSimulation::registerLink(const string & link, FailureNode * owner) {
    alive.insert(link);
    link2Nodes[link].push_back(owner);
}
