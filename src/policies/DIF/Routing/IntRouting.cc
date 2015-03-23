#include "IntRouting.h"

IntRouting::IntRouting(){
    SIG_RIBD_RoutingUpdate = "Routing-Update";
    SIG_RIBD_RoutingUpdateReceived = "Routing-UpdateReceived";
}

void IntRouting::finish(){

    cModule* catcher = this->getParentModule();
    catcher->unsubscribe(SIG_RIBD_RoutingUpdateReceived, listener);
    delete listener;
   // delete SIG_RIBD_RoutingUpdate;
   // delete SIG_RIBD_RoutingUpdateReceived;
}

void IntRouting::initialize(){

    // IPCProcess module.
    cModule * ipcModule = getParentModule();

    myAddress   = Address(
        ipcModule->par("ipcAddress").stringValue(),
        ipcModule->par("difName").stringValue());

    check_and_cast<cObject *>
            (getModuleByPath("^.resourceAllocator.pduFwdGenerator"));

    //Set FWDGenerator
    fwdg = check_and_cast<IntPDUFG *>
        (getModuleByPath("^.resourceAllocator.pduFwdGenerator"));
   // (getModuleByPath("^.PDUFWDGPolicy"));

    // Display active policy name.
    cDisplayString& disp = getDisplayString();
    disp.setTagArg("t", 1, "t");
    disp.setTagArg("t", 0, getClassName());

    cModule* catcher = this->getParentModule();

    // Signal emitters; there will be part of our outputs.
    sigRoutingUpdate = registerSignal(SIG_RIBD_RoutingUpdate);

    // Signal receivers; there will be part of our inputs.
    listener = new LisRoutingRecv(this);
    catcher->subscribe(SIG_RIBD_RoutingUpdateReceived, listener);

    onIni();

}

void IntRouting::sendUpdate(IntRoutingUpdate * update) {
    update->setSource(myAddress);
    emit(sigRoutingUpdate, update);
}

void IntRouting::receiveUpdate(const IntRoutingUpdate * update) {
    if(processUpdate(update)) {
        fwdg->routingUpdated();
    }
}


LisRoutingRecv::LisRoutingRecv(IntRouting * _module){
    module = _module;
}

void LisRoutingRecv::receiveSignal(cComponent *src, simsignal_t id, cObject *obj){
    EV << "RoutingUpdate initiated by " << src->getFullPath()
       << " and processed by " << module->getFullPath() << endl;

    IntRoutingUpdate * update = dynamic_cast<IntRoutingUpdate *>(obj);

    if (update) {
        module->receiveUpdate(update);
    } else {
        EV << "RoutingUpdate received unknown object!" << endl;
    }

    delete update;
}
