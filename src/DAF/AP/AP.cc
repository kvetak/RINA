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

#include "AP.h"

Define_Module(AP);

AP::AP(){
    this->isEnrolled = this->EnrollmentState::NOT_ENROLLED;
}

AP::~AP() {
}

void AP::initialize() {
    initPointers();
    initSignalsAndListeners();
}

void AP::initSignalsAndListeners() {
    cModule* catcher1 = this->getParentModule();
    cModule* catcher2 = this->getModuleByPath("^.^");

    sigAPAEAPI = registerSignal(SIG_AP_AE_API);
    sigAEEnrolled = registerSignal(SIG_AE_Enrolled);

    //  AllocationRequest from FAI
    lisAPAllReqFromFai = new LisAPAllReqFromFai(this);
    catcher2->subscribe(SIG_FAI_AllocateRequest, lisAPAllReqFromFai);


    //  Enrollment
    lisAPEnrolled = new LisAPEnrolled(this);
    catcher1->subscribe(SIG_AEMGMT_ConnectionResponsePositive, lisAPEnrolled);

    // API listeners
    lisAEAPAPI = new LisAEAPAPI(this);
    catcher1->subscribe(SIG_AE_AP_API, lisAEAPAPI);
}

void AP::initPointers() {
}

void AP::onA_getOpen(APIResult* result) {
}

void AP::onA_getRead(APIResult* result) {
}

void AP::onA_getWrite(APIResult* result) {
}

void AP::onClose(APIResult* result) {
}

bool AP::a_open(int invokeID, std::string APName, std::string APInst, std::string AEName, std::string AEInst) {
    if (this->isEnrolled == this->EnrollmentState::NOT_ENROLLED) {
        //Vesely -> Jerabek: Je zde duvod k hardcodovani hodnot?
        APNIPair* apnip = new APNIPair(
        APNamingInfo(APN(this->getParentModule()->par("apName").stringValue()),
                    "0",
                    "Mgmt",
                    "0"),
        APNamingInfo(APN(APName),
                    "0",
                    "Mgmt",
                    "0"));

        emit(sigAEEnrolled, apnip);
        this->isEnrolled = this->EnrollmentState::ENROLLING;

        //insert connection requests to queue
        Flow tmp = Flow(APNamingInfo(), APNamingInfo(APN(APName), APInst, AEName, AEInst));
        tmp.setAllocInvokeId(invokeID);
        this->insertAEReq(tmp);
    }
    else if (this->isEnrolled == this->EnrollmentState::ENROLLING) {
        Flow tmp = Flow(APNamingInfo(), APNamingInfo(APN(APName), APInst, AEName, AEInst));
        tmp.setAllocInvokeId(invokeID);
        this->insertAEReq(tmp);
    }
    else
        return createIAE(APName, APInst, AEName, AEInst, NULL, invokeID);

    return false;
}

bool AP::a_open(int invokeID, Flow* flow){
    return false;
}

bool AP::a_close(int CDAPConn, int invokeID) {
    APIReqObj* obj = new APIReqObj();
    obj->setCDAPConId(CDAPConn);
    obj->setAPIReqType(APIReqObj::A_CLOSE);

    this->signalizeAPAEAPI(obj);
    return true;
}

bool AP::a_read(int CDAPConn, std::string objName, int invokeID) {
    APIReqObj* obj = new APIReqObj();
    obj->setCDAPConId(CDAPConn);
    obj->setObjName(objName);
    obj->setInvokeId(invokeID);
    obj->setAPIReqType(APIReqObj::A_READ);

    this->signalizeAPAEAPI(obj);
    return true;
}

bool AP::a_write(int CDAPConn, std::string objName, object_t *obj, int invokeID) {
    APIReqObj *req = new APIReqObj();
    req->setCDAPConId(CDAPConn);
    req->setObjName(objName);
    req->setObj(obj);
    req->setInvokeId(invokeID);
    req->setAPIReqType(APIReqObj::A_WRITE);

    this->signalizeAPAEAPI(req);
    return true;
}

APIRetObj* AP::a_getopen_r(int invokeID) {
    return NULL;
}

APIRetObj* AP::a_getclose_r(int CDAPConn, int invokeID) {
    return NULL;
}

bool AP::a_read_r(int CDAPconn, int invokeID, std::string objName, object_t *obj, bool complete) {
    return false;
}

APIRetObj* AP::a_get_read_r(int CDAPConn, int invokeID) {
    return NULL;
}

bool AP::a_cancelread_r(int CDAPConn, int invokeID) {
    return false;
}

APIRetObj* AP::a_getwrite_r(int CDAPconn, int invokeID, APIResult* result, std::string objName, object_t *obj){
    return NULL;
}

bool AP::createIAE(std::string APName, std::string APInst, std::string AEName, std::string AEInst, Flow* flow, int invokeID) {
    std::string str = "^."+AEName;
    cModule *submodule, *module = this->getModuleByPath(str.c_str());
    cModuleType *moduleType;
    std::ostringstream ostr;

    str = "rina.src.DAF.AE."+AEName;
    cModuleType *moduleAEType = cModuleType::find(str.c_str());
    if(!moduleAEType) {
        str = "rina.src.DAF.AE."+AEName+"."+AEName;
        moduleAEType = cModuleType::find(str.c_str());
    }

    if(!moduleAEType) {
        return false;
    }

    int AEInstanceNum = getNewAEInstNum(AEName);

    //create module wrapper for AE if not exists
    if(!module) {
        moduleType = cModuleType::get("rina.src.DAF.AE.ApplicationEntity");
        //Create a name
        ostr << AEName;

        //Instantiate module
        module = moduleType->create(ostr.str().c_str(), this->getModuleByPath("^"));
        module->finalizeParameters();
        module->buildInside();
        module->callInitialize();
    }

    //create whole module AEInst, inside IAE,Socket
    str = "^."+AEName;
    module = this->getModuleByPath(str.c_str());

    if (!module) {
        return false;
    }

    ostr.clear();
    ostr.str("");

    ostr << AEName << "_" << AEInstanceNum;
    moduleType = cModuleType::get("rina.src.DAF.AE.ApplicationEntityInstance");
    module = moduleType->create(ostr.str().c_str(), this->getModuleByPath(str.c_str()));
    module->par("aeType") = AEName;

    module->finalizeParameters();
    module->buildInside();

    submodule = module->getSubmodule("iae");
    submodule->par("aeName") = AEName;
    submodule->par("aeInstance") = std::to_string(AEInstanceNum);
    submodule->par("dstApName") = APName;
    submodule->par("dstApInstance") = APInst;
    submodule->par("dstAeName") = AEName;
    submodule->par("dstAeInstance") = AEInst;

    if (flow == NULL)
        submodule->par("initiator") = true;
    else
        submodule->par("initiator") = false;

    module->callInitialize();

    AE* aeModule = dynamic_cast<AE*>(module->getSubmodule("iae"));

    aeModule->setCdapConId(this->getNewCdapConID());
    aeModule->setStartInvokeId(invokeID);
    aeModule->start(flow);

    return true;
}

void AP::receiveAllocationRequestFromFAI(Flow* flow) {

    Enter_Method("receiveAllocationRequestFromFai()");
    //EV << this->getFullPath() << " received AllocationRequest from FAI" << endl;

//    if ( QoSRequirements.compare(flow->getQosRequirements()) ) {





    //Initialize flow within AE
        //TODO: tady dodelat vytvoreni a inicializace IAE
        createIAE(flow->getDstApni().getApn().getName(), flow->getDstApni().getApinstance(),
                flow->getDstApni().getAename(), flow->getDstApni().getAeinstance(), flow, 0);
        //FlowObject = flow;
        //insertFlow();
        //EV << "======================" << endl << flow->info() << endl;
        //Interconnect IRM and IPC

        //bool status = Irm->receiveAllocationResponsePositiveFromIpc(flow);

        //Change connection status
        /*if (status) {
            this->signalizeAllocateResponsePositive(flow);
        }
        else {
            EV << "IRM was unable to create bindings!" << endl;
        }
//    }
//    else {
//        EV << "QoS Requirement cannot be met, please check AE attributes!" << endl;
//        this->signalizeAllocateResponseNegative(flow);
//    }
 *
 */
}

bool AP::deleteIAE(APIResult* result) {
    //TODO: repair this crap
    //std::string ae = result->getObjName().substr(0,result->getObjName().find("_",0));
    //cModule* aen = this->getModuleByPath("^")->getSubmodule(ae.c_str());
    //std::string iaes = result->getObjName();
    //cModule* iaen = aen->getSubmodule(iaes.c_str());
    //iaen->getSubmodule("socket")->callFinish();
    //iaen->getSubmodule("socket")->deleteModule();
    //aen->callFinish();
    //aen->deleteModule();
    return true;
}

void AP::resultAssign(APIResult* result) {
    if (result->getAPIResType() == APIResult::A_GET_OPEN) {
        Enter_Method("onA_getOpen()");
        onA_getOpen(result);
    }
    if (result->getAPIResType() == APIResult::A_GET_READ) {
        Enter_Method("onA_getRead()");
        onA_getRead(result);
    }
    else if (result->getAPIResType() == APIResult::A_GET_WRITE) {
        Enter_Method("onA_getWrite()");
        onA_getWrite(result);
    }
    else if (result->getAPIResType() == APIResult::D_DELETE) {
        deleteIAE(result);
    }
}

void AP::startRequestedConnections() {
    Enter_Method("startRequestedConnections()");
    Flow tmp;
    while (!this->ConReqStack.empty()) {
        tmp = this->ConReqStack.back();
        this->createIAE(tmp.getDstApni().getApn().getName(), tmp.getDstApni().getApinstance(),
                tmp.getDstApni().getAename(), tmp.getDstApni().getAeinstance(),
                NULL, tmp.getAllocInvokeId());
        this->ConReqStack.pop_back();
    }
    this->isEnrolled = this->EnrollmentState::ENROLLED;
}

void AP::insertAEReq(Flow req) {
    this->ConReqStack.push_back(req);
}



void AP::signalizeAPAEAPI(APIReqObj* obj) {
    emit(sigAPAEAPI, obj);
}
