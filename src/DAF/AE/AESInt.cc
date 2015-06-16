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

#include "AESInt.h"

_AESInt_self::_AESInt_self(){}

_PingMsg::_PingMsg(){
    pingAt = simTime();
}

_PongMsg::_PongMsg(simtime_t _pingAt){
    pingAt = _pingAt;
    pongAt = simTime();
}


double minMaxNormal (double a, double b, int rng){
    double rn = normal(a+(b-a)/2, (b-a)/6);
    if(rn < a) { rn = a; }
    if(rn > b) { rn = b; }
    return b;
}

AESInt::AESInt() : AE() {}

AESInt::~AESInt() {
    connectionState = NIL;
    FlowObject = NULL;
    Irm = NULL;
    Cdap = NULL;
}

void AESInt::initialize()
{
    //Init pointers
    initPointers();
    //Source info
    initNamingInfo();
    //Setup signals
    initSignalsAndListeners();
    //Init QoSRequirements
    initQoSRequiremets();

    //Timers
    startAt = simTime() + par("startAt");
    stopAt  = simTime() + par("stopAt");
    sendAfter  = par("sendAfter");
    sendDuring  = par("stopAfter");

    if(sendAfter<1){ sendAfter = 1; }
    if(sendDuring<1){ sendDuring = 1; }
    if(stopAt < startAt + sendAfter + sendDuring + 1) { stopAt = startAt + sendAfter + sendDuring + 1; }

    //Destination for flow
    dstApName     = par("dstApName").stringValue();
    dstApInstance = par("dstApInstance").stringValue();
    dstAeName     = par("dstAeName").stringValue();
    dstAeInstance = par("dstAeInstance").stringValue();

    //Schedule AllocateRequest & DeallocateRequest
    if (startAt > 0) {
        scheduleAt(startAt, new cMessage("StartCommunication"));
        scheduleAt(startAt + sendAfter + sendDuring, new cMessage("EndCommunication"));
        scheduleAt(stopAt, new cMessage("StopCommunication"));
        inTime = true;
    } else {
        inTime = false;
    }


    //MAX PDU Size
    maxSize = par("maxPDUsize").longValue();

    send = 0;
    sendSize = 0;

    received = 0;
    receivedSize = 0;

    maxDelay = -1;
    sumDelay = 0;

    recTimes = par("recTimes").boolValue();

    //Watchers
    WATCH(FlowObject);
    WATCH(send);
    WATCH(received);
    WATCH(sendSize);
    WATCH(receivedSize);
    WATCH(maxDelay);

    doIni();
}

void AESInt::finish()
{
    if(par("printAtEnd").boolValue()){
        EV << "At "<<this->getApni()<<endl;
        if(FlowObject != NULL) {
            EV << "With QoS " << FlowObject->getConId().getQoSId() <<endl;
        }
        EV << "send " << send << " ("<<sendSize << ")"<<endl;
        EV << "pongs Rcv "  << received << " ("<<receivedSize << ")"<<endl;
        if(received > 0){
            EV << "Delay " << (sumDelay/received) << " ("<< maxDelay << ")" <<endl;
        }

        if(recTimes){
            EV << "-----------------"<<endl;
            for(std::map<double, int>::iterator it = times.begin(); it!=times.end(); it++) {
                EV << "  " << it->first << " " << it->second <<endl;
            }
            EV << "-----------------"<<endl;
        }
        EV << "-----------------"<<endl;
    }

    doFin();
}

void AESInt::handleSelfMessage(cMessage *msg) {
    if ( !strcmp(msg->getName(), "StartCommunication") ) {
        APNamingInfo src = this->getApni();
        APNamingInfo dst = APNamingInfo( APN(this->dstApName), this->dstApInstance, this->dstAeName, this->dstAeInstance);
        FlowObject = new Flow(src, dst);
        FlowObject->setQosRequirements(this->getQoSRequirements());
        insertFlow();
        sendAllocationRequest(FlowObject);
        scheduleAt(simTime()+sendAfter, new cMessage("MakeCommunication"));
    } else if ( !strcmp(msg->getName(), "StopCommunication") ) {
        sendDeallocationRequest(FlowObject);
    } else if ( !strcmp(msg->getName(), "EndCommunication") ) {
        inTime = false;
    } else if ( !strcmp(msg->getName(), "MakeCommunication") ) {
        if(stopAt > simTime()){ iniCom(); }
    }

    delete(msg);
}

void AESInt::handleMessage(cMessage *msg) {
    if ( msg->isSelfMessage() ) {
        if(_AESInt_self * smsg = dynamic_cast<_AESInt_self*>(msg)){
            processMsg(smsg);
        } else {
            this->handleSelfMessage(msg);
        }
    }
}

void AESInt::processMRead(CDAPMessage* msg) {
    if(_PingMsg* ping = dynamic_cast<_PingMsg*>(msg)){
        processMsg(ping);
    }
}

void AESInt::processMReadR(CDAPMessage* msg) {
    if(_PongMsg* pong = dynamic_cast<_PongMsg*>(msg)){
        received++;
        receivedSize += msg->getByteLength();

        simtime_t delay = simTime() - pong->pingAt;
        sumDelay += delay;
        if(maxDelay<delay){
            maxDelay = delay;
        }

        if(recTimes){
            double dl = dround(delay.dbl(), 3);
            times[dl]++;
        }

        processMsg(pong);
    }
}


void AESInt::sendMsg(_PingMsg * msg, int size){
    send++;
    sendSize += size;

    msg->setByteLength(size);
    sendData(FlowObject, msg);
}

void AESInt::sendMsg(_PongMsg * msg, int size){
    msg->setByteLength(size);
    sendData(FlowObject, msg);
}

void AESInt::processMsg(_AESInt_self * msg){}

void AESInt::processMsg(_PingMsg * ping){
    _PongMsg* pong = new _PongMsg(ping->pingAt);
    sendMsg(pong, ping->getByteLength());
}

void AESInt::processMsg(_PongMsg *){}


double AESInt::dround(double a, int ndigits) {
    int    exp_base10 = round(log10(a));
    double man_base10 = a*pow(10.0,-exp_base10);
    double factor     = pow(10.0,-ndigits+1);
    double truncated_man_base10 = man_base10 - fmod(man_base10,factor);
    double rounded_remainder    = fmod(man_base10,factor)/factor;

    rounded_remainder = rounded_remainder > 0.5 ? 1.0*factor : 0.0;

    return (truncated_man_base10 + rounded_remainder)*pow(10.0,exp_base10) ;
}
