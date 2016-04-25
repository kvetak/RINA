#include "T2Infection.h"

#include "DataTransferPDU.h"
#include "InfectionSignals.h"

using namespace std;

namespace T2Infection {

    Define_Module(T2Infection);


    Flow::Flow(string DIF, string SRC, string DST, string QoS):
        srcAddr(Address(SRC.c_str(), DIF.c_str())),
        dstAddr(Address(DST.c_str(), DIF.c_str())),
        mark (false), listening (false),
        minWtXbit(0), maxWtXbit(0),
        minPdusize(0), maxPduSize(0),
        secNum(0) {
            connID.setSrcCepId(-1);
            connID.setDstCepId(-1);
            connID.setQoSId(QoS);
    }

    void Flow::setCepId(int id) { connID.setSrcCepId(id); }
    void Flow::iniRate(double _avgWtXbit, double var) {
        avgWtXbit = _avgWtXbit;
        minWtXbit = avgWtXbit*(1.0-var);
        maxWtXbit = avgWtXbit*(1.0+var);
    }
    void Flow::iniPduSize(unsigned int min, unsigned int max) {
        minPdusize = min;
        maxPduSize = max;
    }

    void Flow::markStatus(bool status) { mark = status; }
    void Flow::listenStatus(bool status) { listening = status; }

    pduT Flow::getPDU() {
        int size = intuniform(minPdusize, maxPduSize)/8;
        int bitSize = size*8 + 88;

        pduT ret;
        ret.wT = bitSize * uniform(minWtXbit, maxWtXbit);    // Waiting time till next Pdu
        //ret.wT = bitSize * avgWtXbit;////////////////////////////////

        ret.sig = mark && listening;                    // Signal Pdu?

        InfectedDataTransferPDU * pdu = new InfectedDataTransferPDU( ret.sig, connID.getSrcCepId());
        pdu->setConnId(connID);
        pdu->setSrcAddr(srcAddr);
        pdu->setDstAddr(dstAddr);
        pdu->setSrcApn(srcAddr.getApn());
        pdu->setDstApn(dstAddr.getApn());
        pdu->setSeqNum(secNum);

        UserDataField * ud = new UserDataField();
        ud->setCompleteSDU(true);
        ud->setNoLength(false);
        ud->setSduSeqNumPresent(true);
        ud->setSduSeqNum(secNum);
        pdu->encapsulate(ud);
        pdu->setByteLength(size);
        pdu->setHopCount(0);

        ret.pdu = pdu;

        secNum++;
        return ret;
    }

    double Flow::randomWait(){
        return (double)maxPduSize * uniform(0.0, maxWtXbit);    // Waiting time till next Pdu
    }

    commMsg::commMsg(Flow * _f) : f(_f) {}

    void T2Infection::initialize() {
        double iniT = par("iniTime").doubleValue();
        double finT = par("finTime").doubleValue();
        double miniT = par("markIniT").doubleValue();
        double mfinT = par("markFinT").doubleValue();
        timer = nullptr;
        data = 0;

        if(iniT<0 || finT <= iniT || par("infectedIPC").stdstringValue() == "") { return; }

        cXMLElement* Xml = NULL;
        if (par("data").xmlValue() != NULL && par("data").xmlValue()->hasChildren()){
            Xml = par("data").xmlValue();
        } else { return; }

        mod = this->getParentModule()->getSubmodule(par("infectedIPC").stringValue());
        if(mod==NULL) { return; }
        rmt = mod->getSubmodule("relayAndMux")->getSubmodule("rmt");

        rmt->addGate("infGate", cGate::INOUT, false);
        cGate * modIn = rmt->gateHalf("infGate", cGate::INPUT);
        cGate * modOut = rmt->gateHalf("infGate", cGate::OUTPUT);

        cGate * In = gateHalf("g", cGate::INPUT);
        cGate * Out = gateHalf("g", cGate::OUTPUT);

        modOut->connectTo(In);
        Out->connectTo(modIn);

        string DIF = mod->par("difName");
        string SRC = mod->par("ipcAddress");

        double rateMult = par("rateMult").doubleValue();
        wtXbit = 1.0/par("inRate").doubleValue()/rateMult;
      //  cout << "mult : " << rateMult<<endl;

        string dQoS = par("defaultQoS").stdstringValue();

        int dPduS = par("pduSize").longValue();
        double dPduV = par("pduVar").doubleValue();
        if(dPduV < 0.0 ) { dPduV = 0; }
        if(dPduV > 1.0 ) { dPduV = 1; }

        double drateVar = par("rateVar").doubleValue();
        int dnFlows = par("nFlows").longValue();

        int cCepId = 1;

        cXMLElementList flowsXML = Xml->getChildrenByTagName("flowSet");
        for(cXMLElement * n : flowsXML) {
            string DST = n->getAttribute("dstAddr");
            if (DST == "") { error("Error parsing Infected flow. Its dstAddr is missing!"); }
            if(DST == SRC) { continue; }

            string QoS = dQoS;
            if (n->getAttribute("qos")) { QoS = n->getAttribute("qos"); }

            Flow f(DIF, SRC, DST, QoS);

            if(n->getAttribute("rate") == nullptr) { error("Error parsing Infected flow. Its rateis missing!"); }
            double rate = atol(n->getAttribute("rate"));
            if(rate <= 0) { continue; }

            double avgRateVar = 0.0;
            if(n->getAttribute("avgRateVar") != nullptr) {
                avgRateVar = atof(n->getAttribute("avgRateVar"));
                if(avgRateVar < 0) { error("Error parsing Infected flow. Its avgRateVar < 0"); }
                if(avgRateVar >= 1) { error("Error parsing Infected flow. Its avgRateVar >= 1"); }
            }

            int nFlows = dnFlows;
            if(n->getAttribute("nFlows") != nullptr) {
                nFlows = atoi(n->getAttribute("nFlows"));
                if(nFlows <= 0) { error("Error parsing Infected flow. Its nFlows <= 0"); }
            }
            rate /= nFlows;

            double rateVar = drateVar;
            if(n->getAttribute("rateVar") != nullptr) {
                rateVar = atof(n->getAttribute("rateVar"));
                if(rateVar < 0.0 || rateVar > 1.0) { error("Error parsing Infected flow. 0 > rateVar | rateVar > 1"); }
            }

            int PduS = dPduS;
            if(n->getAttribute("PduS") != nullptr) {
                PduS = atoi(n->getAttribute("PduS"));
                if(PduS <= 0) { error("Error parsing Infected flow. Its PduS <= 0"); }
            }
            double PduV = dPduV;
            if(n->getAttribute("PduV") != nullptr) {
                PduS = atof(n->getAttribute("PduV"));
                if(PduV < 0.0 || PduV > 1.0) { error("Error parsing Infected flow. 0 > PduV | PduV > 1"); }
            }
            if(dPduV < 0.0 ) { dPduV = 0; }
            if(dPduV > 1.0 ) { dPduV = 1; }
            f.iniPduSize(PduS * (1-dPduV), PduS * (1+dPduV));

            bool listening = (n->getAttribute("listen") != nullptr);
            if(listening) { f.markStatus(true); }


            rate *= rateMult;
            double wtXbit = 1.0 / rate;

            //rateVar = 0.0;////////////////////////////////
            if(nFlows%2 == 1) {
                f.iniRate(wtXbit, rateVar);
                if(listening) {
                    f.setCepId(cCepId++);
                    f.markStatus(true);
                }
                flows.push_back(f);

                nFlows--;
            }

            for(int i = 0; i < nFlows; i +=2 ){
                double fRateVar = uniform(0.0, avgRateVar);
                //fRateVar = 0.0;////////////////////////////////

                f.iniRate(wtXbit*(1.0-fRateVar), rateVar);
                if(listening) {
                    f.setCepId(cCepId++);
                    f.markStatus(true);
                }
                flows.push_back(f);

                f.iniRate(wtXbit*(1.0+fRateVar), rateVar);
                if(listening) {
                    f.setCepId(cCepId++);
                    f.markStatus(true);
                }
                flows.push_back(f);
            }
        }

        start = new cMessage("Start");
        scheduleAt(iniT, start);

        stop = new cMessage("Stop");
        scheduleAt(finT, stop);

        if(miniT <= 0) {
            for(Flow & f : flows) { f.listenStatus(true); }
            listen = nullptr;
        } else {
            listen = new cMessage("Listen");
            scheduleAt(miniT, listen);
        }
        finlisten = new cMessage("FinListen");
        scheduleAt(mfinT, finlisten);

        signal = registerSignal("InfectionSignal");
    }

    void T2Infection::handleMessage(cMessage *msg) {
        if(msg == start) {
            simtime_t now = simTime();
            for(Flow & f : flows) {
                double t = f.randomWait();
                commMsg * m = new commMsg(&f);
              //  cout << (now+t)<<endl;
              //  cout << f.currentRate << endl;

                scheduleAt(now+t, m);
            }
            delete start;
            start = nullptr;
            return;
        }

        if (msg == stop) {
            delete stop;
            stop = nullptr;
            return;
        }

        if (msg == listen) {
            for(Flow & f : flows) { f.listenStatus(true); }
            delete listen;
            listen = nullptr;
            return;
        }

        if (msg == finlisten) {
            for(Flow & f : flows) { f.listenStatus(false); }
            delete finlisten;
            finlisten = nullptr;
            return;
        }

        if(msg == timer) {
            //cout << q.size() << endl;

            if(q.empty()) {
                delete timer;
                timer = nullptr;
                return;
            }

            InfectedDataTransferPDU * pdu = q.front();
            q.pop();
            double wt = (pdu->getBitLength() + 88) * wtXbit;
            data += (pdu->getBitLength() + 88);

            if(pdu->signaled) { emit(signal, new SendInfMsg(
                    pdu->getSrcAddr().getIpcAddress().getName(),
                    pdu->getDstAddr().getIpcAddress().getName(),
                    pdu->getConnId().getSrcCepId(),
                    pdu->getConnId().getQoSId())
            );}

            pdu->sendT = simTime();
            send(pdu, "g$o");
            scheduleAt(simTime() + wt, timer);
            return;
        }

        commMsg * m = dynamic_cast<commMsg *>(msg);
        if(stop != nullptr && m != nullptr ) {
            pduT k = m->f->getPDU();
            q.push(k.pdu);

            scheduleAt(simTime() + k.wT, msg);
            if(timer == nullptr) {
                timer = new cMessage("schedule");
                handleMessage(timer);
            }
            return;
        }

        delete msg;
    }

    void T2Infection::finish() {
        cout << "Infection, data sent: "<<data << endl;
    }
}
