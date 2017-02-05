// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "DAF/AE/AE.h"
#include "Common/Socket.h"
Define_Module(AE);

AE::AE() :
        Irm(NULL), Cdap(NULL)
{
    FlowObject = NULL;
    connectionState = NIL;
    maxConRetries = 3;
    authType = AUTH_NONE;
}

AE::~AE() {
    connectionState = NIL;
    FlowObject = NULL;
    Irm = NULL;
    Cdap = NULL;
}

void AE::initialize() {
    //Init pointers
    initPointers();
    //Source info
    initNamingInfo();
    //Setup signals
    initSignalsAndListeners();
    //Watchers
    //WATCH_LIST(flows);
    WATCH(FlowObject);
    WATCH(connectionState);
}

void AE::initPointers() {
    Irm = getRINAModule<IRM*>(this, 4, {MOD_IPCRESMANAGER, MOD_IRM});
    Cdap = getRINAModule<cModule*>(this, 1, {MOD_CDAP});
    Cace = new CACEGeneric(this);

    if (!Cdap)
        error("Pointers to Cdap !");
    if (!Irm || !Cdap)
        error("Pointers to Irm or ConnectionTable or Cdap are not initialized!");
}

void AE::initSignalsAndListeners() {
    cModule* catcher1 = this->getParentModule();
    cModule* catcher2 = this->getModuleByPath("^.^.^.^");
    cModule* catcher3 = this->getModuleByPath("^.^.^");


    //Signals that this module is emitting
    sigAEAllocReq      = registerSignal(SIG_AE_AllocateRequest);
    sigAEDeallocReq    = registerSignal(SIG_AE_DeallocateRequest);
    sigAESendData      = registerSignal(SIG_AE_DataSend);
    sigAEAllocResPosi  = registerSignal(SIG_AERIBD_AllocateResponsePositive);
    sigAEAllocResNega  = registerSignal(SIG_AERIBD_AllocateResponseNegative);
    sigAEConReq        = registerSignal(SIG_AE_ConnectionRequest);
    sigAERelReq        = registerSignal(SIG_AE_ReleaseRequest);
    sigAEEnrolled      = registerSignal(SIG_AE_Enrolled);
    sigAEAPAPI         = registerSignal(SIG_AE_AP_API);


    //Signals that this module is processing
    lisAERcvData = new LisAEReceiveData(this);
    catcher1->subscribe(SIG_CDAP_DateReceive, lisAERcvData);

    //TODO: solve problem with dynamic creation when listener is called (can not subscribe to the same signal)
    //  AllocationRequest from FAI
    //lisAEAllReqFromFai = new LisAEAllReqFromFai(this);
    //catcher2->subscribe(SIG_FAI_AllocateRequest, lisAEAllReqFromFai);

    //  Enrollment
    lisAEEnrolled = new LisAEEnrolled(this);
    //catcher3->subscribe(SIG_AEMGMT_ConnectionResponsePositive, lisAEEnrolled);

    // AP-AE API
    lisAPAEAPI = new LisAPAEAPI(this);
    catcher3->subscribe(SIG_AP_AE_API, lisAPAEAPI);

    //  DeallocationRequest from FAI
    lisAEDeallReqFromFai = new LisAEDeallReqFromFai(this);
    catcher2->subscribe(SIG_FAI_DeallocateRequest, lisAEDeallReqFromFai);
    lisAEDeallResFromFai = new LisAEDeallReqFromFai(this);
    catcher2->subscribe(SIG_FAI_DeallocateResponse, lisAEDeallResFromFai);

    lisAEAllResPosi = new LisAEAllResPosi(this);
    catcher2->subscribe(SIG_FAI_AllocateResponsePositive, lisAEAllResPosi);

    lisAEAllResNega = new LisAEAllResNega(this);
    catcher2->subscribe(SIG_FAI_AllocateResponseNegative, lisAEAllResNega);
}


void AE::handleMessage(cMessage* msg) {
}

bool AE::createBindings(Flow& flow) {
    EV << this->getFullPath() << " created bindings and registered a new flow" << endl;
    //Create new gates
    cGate* gIrmIn;
    cGate* gIrmOut;
    Irm->getOrCreateFirstUnconnectedGatePair(GATE_AEIO, false, true, *&gIrmIn, *&gIrmOut);

    cModule* IrmMod = Irm->getParentModule();
    cGate* gIrmModIn;
    cGate* gIrmModOut;
    IrmMod->getOrCreateFirstUnconnectedGatePair(GATE_NORTHIO, false, true, *&gIrmModIn, *&gIrmModOut);

    cModule* ApMon = this->getModuleByPath("^.^.^");
    cGate* gApIn;
    cGate* gApOut;
    ApMon->getOrCreateFirstUnconnectedGatePair(GATE_SOUTHIO, false, true, *&gApIn, *&gApOut);

    //Get AE gates
    cModule* AeMod = this->getModuleByPath("^.^");
    cGate* gAeIn;
    cGate* gAeOut;
    AeMod->getOrCreateFirstUnconnectedGatePair("southIo", false, true, *&gAeIn, *&gAeOut);

    //Get AE instance gates
    cModule* AeInstanceMod = this->getModuleByPath("^");
    cGate* gAeInstIn;
    cGate* gAeInstOut;
    AeInstanceMod->getOrCreateFirstUnconnectedGatePair("aeIo", false, true, *&gAeInstIn, *&gAeInstOut);

    //Get Socket South Gates
    cModule* SocketMod = this->getModuleByPath("^.socket");
    cGate* gSocketIn;
    cGate* gSocketOut;
    SocketMod->getOrCreateFirstUnconnectedGatePair("southIo", false, true, *&gSocketIn, *&gSocketOut);

    //Get Socket CDAP Gates
    cGate* gSocketCdapIn = SocketMod->gateHalf("cdapIo", cGate::INPUT);

    //TODO: Vesely -> Jerabek: Unused variable!
    //cGate* gSocketCdapOut = SocketMod->gateHalf("cdapIo", cGate::OUTPUT);

    //Dirty hack
    Socket* socket = dynamic_cast<Socket*>(SocketMod);
    socket->setFlow(&flow);


    //CDAPParent Module gates
    //TODO: Vesely -> Jerabek: Unused variable!
    //cGate* gCdapParentIn = Cdap->gateHalf(GATE_SOUTHIO, cGate::INPUT);
    //TODO: Vesely -> Jerabek: Unused variable!
    //cGate* gCdapParentOut = Cdap->gateHalf(GATE_SOUTHIO, cGate::OUTPUT);

    //Connect gates together
    gIrmOut->connectTo(gIrmModOut);
    gIrmModOut->connectTo(gApIn);
    gApIn->connectTo(gAeIn);
    gAeIn->connectTo(gAeInstIn);
    gAeInstIn->connectTo(gSocketIn);
    //gSocketCdapIn->connectTo(gCdapParentIn);

    //gCdapParentOut->connectTo(gSocketCdapOut);
    gSocketOut->connectTo(gAeInstOut);
    gAeInstOut->connectTo(gAeOut);
    gAeOut->connectTo(gApOut);
    gApOut->connectTo(gIrmModIn);
    gIrmModIn->connectTo(gIrmIn);

    //Set north-half of the routing in ConnectionTable
    Irm->setNorthGates(&flow, gIrmIn, gIrmOut);


    //Return true if all dynamically created gates have same index
    return gIrmIn->isConnected()
           && gAeIn->isConnected()
           && gIrmModIn->isConnected()
           && gApIn->isConnected()
           && gAeInstIn->isConnected()
           && gSocketCdapIn->isConnected();
}


void AE::insertFlow() {
    //Add a new flow to

    //Prepare flow
    Irm->newFlow(FlowObject);

    //Interconnect IRM and AE

    bool status = createBindings(*FlowObject);
    if (!status) {
        EV << "Gate inconsistency during creation of a new flow!" << endl;
    }
}

void AE::CACEFinished() {
    changeConStatus(ESTABLISHED);

    //send response to AP Instance
    APIResult *obj = new APIResult();
    obj->setInvokeId(startInvokeId);
    obj->setCDAPConId(cdapConId);
    obj->setAPIResType(APIResult::A_GET_OPEN);
    signalizeAEAPAPI(obj);

}

void AE::start(Flow* flow) {
    initQoSRequirements();

    if (flow) {
        signalizeAllocateResponsePositive(flow);
        FlowObject = flow;
        insertFlow();

        //Interconnect IRM and IPC
        bool status = Irm->receiveAllocationResponsePositiveFromIpc(flow);

        //Change connection status
        if (status) {
            changeConStatus(CONNECTION_PENDING);
            this->signalizeAllocateResponsePositive(FlowObject);
        }
        else {
            EV << "IRM was unable to create bindings!" << endl;
        }
    }
    else {
        APNamingInfo src = this->getApni();

        std::string dstApName     = this->par("dstApName").stringValue();
        std::string dstApInstance = this->par("dstApInstance").stringValue();
        std::string dstAeName     = this->par("dstAeName").stringValue();
        std::string dstAeInstance = this->par("dstAeInstance").stringValue();

        APNamingInfo dst = APNamingInfo( APN(dstApName), dstApInstance,
                                         dstAeName, dstAeInstance);

        //Create a flow
        FlowObject = new Flow(src, dst);
        //TODO: change configuration of qos
        FlowObject->setQosRequirements(this->getQoSRequirements());

        //Notify IRM about a new flow
        insertFlow();

        //Call flow allocation request
        sendAllocationRequest(FlowObject);
    }
}


void AE::apiSwitcher(APIReqObj *obj) {
    if (obj->getAPIReqType() == APIReqObj::A_READ) {
        Enter_Method("onA_read()");
        onA_read(obj);
    }
    else if (obj->getAPIReqType() == APIReqObj::A_WRITE) {
        Enter_Method("onA_write()");
        onA_write(obj);
    }
    if (obj->getAPIReqType() == APIReqObj::A_CLOSE) {
        Enter_Method("onA_close()");
        sendDeallocationRequest(FlowObject);
    }
}

void AE::receiveData(CDAPMessage* msg) {
    Enter_Method("receiveData()");
    //M_READ_Request
    if (dynamic_cast<CDAP_M_Read*>(msg)) {
        Enter_Method("processMRead()");
        processMRead(msg);
    }
    //M_READ_Response
    else if (dynamic_cast<CDAP_M_Read_R*>(msg)) {
        Enter_Method("processMReadR()");
        processMReadR(msg);
    }
    else if (dynamic_cast<CDAP_M_Connect_R*>(msg)) {
        Enter_Method("processMConnectR()");
        CDAP_M_Connect_R* cmsg = dynamic_cast<CDAP_M_Connect_R*>(msg);
        if (!cmsg->getResult().resultValue) {
           Cace->receivePositiveConnectResponse(msg);
        }
        else {
           Cace->receiveNegativeConnectResponse(msg);
        }
    }
    else if (dynamic_cast<CDAP_M_Connect*>(msg)) {
        Cace->receiveConnectRequest(msg);
    }
    //M_WRITE_Request
    else if (dynamic_cast<CDAP_M_Write*>(msg)) {
        processMWrite(msg);
    }
    //M_WRITE_Response
    else if (dynamic_cast<CDAP_M_Write_R*>(msg)) {
        processMWriteR(msg);
    }

    delete msg;
}

void AE::receiveAllocationRequestFromFAI(Flow* flow) {
    Enter_Method("receiveAllocationRequestFromFai()");

    if ( QoSRequirements.compare(flow->getQosRequirements()) ) {

        //Initialize flow within AE
        FlowObject = flow;
        insertFlow();

        //Interconnect IRM and IPC
        bool status = Irm->receiveAllocationResponsePositiveFromIpc(flow);

        //Change connection status
        if (status) {
            changeConStatus(CONNECTION_PENDING);
            this->signalizeAllocateResponsePositive(FlowObject);
        }
        else {
            EV << "IRM was unable to create bindings!" << endl;
        }
    }
    else {
        EV << "QoS Requirement cannot be met, please check AE attributes!" << endl;
        this->signalizeAllocateResponseNegative(flow);
    }
}


void AE::receiveAllocationResponseNegative(Flow* flow) {
    Enter_Method("receiveAllocationResponseNegative()");
    //Change allocation status
    Irm->changeStatus(flow, ConnectionTableEntry::CON_ERROR);

    deleteBindings(*FlowObject);

    //Change connection status
    changeConStatus(NIL);
}

void AE::receiveAllocationResponsePositive(Flow* flow) {
    Enter_Method("receiveAllocationResponsePositive()");
    //Interconnect IRM and IPC
    Irm->receiveAllocationResponsePositiveFromIpc(flow);

    //CACE starts here!
    this->Cace->startCACE(flow);
}

void AE::sendAllocationRequest(Flow* flow) {
    //TODO: Vesely - Substitute with signal
    Irm->receiveAllocationRequestFromAe(flow);

    //Change connection status
    changeConStatus(FLOW_PENDING);
}

void AE::sendDeallocationRequest(Flow* flow) {
    //TODO: Vesely - Substitute with signal
    Irm->receiveDeallocationRequestFromAe(flow);
}


void AE::sendData(Flow* flow, CDAPMessage* msg) {
    //Retrieve handle from ConTab record
    int handle = Irm->getIrmGateHandle(flow);
    if (handle != VAL_UNDEF_HANDLE) {
        //Pass Data to CDAP
        //Connection/Release or send data msg
        if (dynamic_cast<CDAP_M_Connect*>(msg) != NULL &&
                getConStatus() == CONNECTION_PENDING){
            signalizeConnectionRequest(msg);
        }
        else if(dynamic_cast<CDAP_M_Release*>(msg) != NULL){
            signalizeReleaseRequest(msg);
            changeConStatus(RELEASING);
        }
        else if(getConStatus() == ESTABLISHED
                //TODO: Vesely - Ugly hack to support old AE wo Establishment. Should be removed sooner or later
                || getConStatus() == CONNECTION_PENDING
                ){
            signalizeSendData(msg);
        }
    }
    else {
        EV << "Sending data before flow is allocated!" << endl;
        delete msg;
    }
}

void AE::processMRead(CDAPMessage* msg) {

}

void AE::receiveDeallocationRequestFromFAI(Flow* flow) {
    Enter_Method("receiveDeallocationRequestFromFai()");

    bool status;
    status = deleteBindings(*flow);
    if (!status) {
        EV << "deleteBindings() failed during DeallocateRequest processing!" << endl;
        return;
    }

    status = Irm->deleteBindings(flow);
    if (!status) {
        EV << "IRM.deleteBindings() failed during DeallocateRequest processing!" << endl;
        return;
    }

    //EV << "Statusak> " << status;
}

bool AE::deleteBindings(Flow& flow) {
    EV << this->getFullPath() << " deleted bindings" << endl;

    int handle1 = Irm->getIrmGateHandle(&flow);
    //TODO: Vesely -> Jerabek: Unused variable!
    //int handle2 = Irm->getApGateHandle(&flow);
    if (handle1 == VAL_UNDEF_HANDLE)
        error("Delete gates before flow allocation is impossible!");

    //Disconnect gates
    cGate* gIrmIn = Irm->gateHalf(GATE_AEIO, cGate::INPUT, handle1);
    cGate* gIrmOut = Irm->gateHalf(GATE_AEIO, cGate::OUTPUT, handle1);

    cModule* IrmMod = Irm->getParentModule();
    cGate* gIrmModIn = IrmMod->gateHalf(GATE_NORTHIO,cGate::INPUT, handle1);
    cGate* gIrmModOut = IrmMod->gateHalf(GATE_NORTHIO,cGate::OUTPUT, handle1);

    //Get Socket South Gates
    //TODO: when more connections, change index system
    cModule* SocketMod = this->getModuleByPath("^.socket");
    cGate* gSocketIn = SocketMod->gateHalf(GATE_SOUTHIO, cGate::INPUT, 0);
    cGate* gSocketOut = SocketMod->gateHalf(GATE_SOUTHIO, cGate::OUTPUT, 0);

    cGate* gAeInstIn = gSocketIn->getPreviousGate();
    cGate* gAeInstOut = gSocketOut->getNextGate();

    cGate* gAeIn = gAeInstIn->getPreviousGate();
    cGate* gAeOut = gAeInstOut->getNextGate();

    cGate* gApIn = gAeIn->getPreviousGate();


    cModule* CdapMod = this->getModuleByPath("^.commonDistributedApplicationProtocol");
    cGate* gCdapIn = CdapMod->gateHalf(GATE_SOUTHIO, cGate::INPUT);
    cGate* gCdapOut = CdapMod->gateHalf(GATE_SOUTHIO, cGate::OUTPUT);

    cGate* gCdapSocketOut = gCdapIn->getPreviousGate();

    //Disconnect gates
    gCdapSocketOut->disconnect();
    gCdapOut->disconnect();

    gSocketOut->disconnect();
    gAeInstIn->disconnect();

    gAeInstOut->disconnect();

    gAeIn->disconnect();
    gAeOut->disconnect();
    gApIn->disconnect();


    gIrmOut->disconnect();
    gIrmModOut->disconnect();
    gIrmModIn->disconnect();
    gIrmIn->disconnect();


    APIResult *del = new APIResult();
    del->setAPIResType(APIResult::D_DELETE);
    del->setObjName(this->getModuleByPath("^")->getFullName());
    signalizeAEAPAPI(del);


    //Return true if all dynamically created gates are disconnected
    return !gIrmIn->isConnected()
            && !gIrmOut->isConnected()
            && !gIrmModIn->isConnected()
            && !gIrmModOut->isConnected()
            && !gApIn->isConnected()
            && !gAeOut->isConnected()
            && !gAeIn->isConnected()
            && !gAeInstOut->isConnected()
            && !gSocketOut->isConnected()
            && !gCdapOut->isConnected()
            && !gCdapSocketOut->isConnected();
}

void AE::processMReadR(CDAPMessage* msg) {
}

void AE::processMWrite(CDAPMessage* msg) {
}

void AE::processMWriteR(CDAPMessage* msg) {
}


void AE::connect(){
    APNIPair* apnip = new APNIPair(
        APNamingInfo(),
        APNamingInfo());
    emit(sigAEEnrolled, apnip);
}

void AE::afterOnStart() {
}


bool AE::onA_read(APIReqObj* obj) {
    //TODO: Vesely -> Jerabek: RESOLVE!
    return false;
}

bool AE::onA_write(APIReqObj* obj) {
    //TODO: Vesely -> Jerabek: RESOLVE!
    return false;
}


void AE::signalizeAllocateRequest(Flow* flow) {
    emit(sigAEAllocReq, flow);
}

void AE::signalizeDeallocateRequest(Flow* flow) {
    emit(sigAEDeallocReq, flow);
}

void AE::signalizeConnectionRequest(CDAPMessage* msg){
    emit(sigAEConReq, msg);
}

void AE::signalizeReleaseRequest(CDAPMessage* msg){
    emit(sigAERelReq, msg);
}

void AE::signalizeAllocateResponseNegative(Flow* flow) {
    emit(sigAEAllocResNega, flow);
}

void AE::signalizeSendData(cMessage* msg) {
    EV << "Emits SendData signal for message " << msg->getName() << endl;
    emit(sigAESendData, msg);
}

void AE::signalizeAllocateResponsePositive(Flow* flow) {
    emit(sigAEAllocResPosi, flow);
}

void AE::signalizeAEAPAPI(APIResult* obj) {
    emit(sigAEAPAPI, obj);
}
