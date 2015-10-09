#include "AdmFlyIPC.h"

Define_Module(AdmFlyIPC);

#include <string>
#include <list>
#include "Utils.h"

#include "RA.h"
#include "AdminMsgs.h"

#include "Directory.h"

using namespace std;

void AdmFlyIPC::initialize(){
    dif = par("difName").stdstringValue();
    addr = par("addr").stdstringValue();
    dst = par("neigh").stdstringValue();
    string myAddr = par("myAddr").stdstringValue();
    string neighAddr = par("neighAddr").stdstringValue();

    if(dif == "" || addr == "") { return; }

    int atTime = par("atTime").longValue();
    int conAtTime = par("conAtTime").longValue();


    Directory * dir = check_and_cast<Directory*>
        (getRINAModule(this, 3, {MOD_DIFALLOC, MOD_DA}));

    if(addr != "" && myAddr != ""){
        string addrAppName = addr;
        addrAppName.append("_").append(dif);
        dir->addDirEntry(APN(addrAppName));
        dir->addNewDif(APN(addrAppName), Address(myAddr));
    }
    if(dst != "" && neighAddr != ""){
        string addrAppName = dst;
        addrAppName.append("_").append(dif);
        dir->addDirEntry(APN(addrAppName));
        dir->addNewDif(APN(addrAppName), Address(neighAddr));
    }

    if(atTime >= 0 || dif != "" || addr != ""){
        scheduleAt(atTime, new cMessage("createIPC"));
        if(conAtTime >= atTime && dst != ""){
            scheduleAt(conAtTime, new cMessage("connect"));
        }
    }
}
void AdmFlyIPC::handleMessage(cMessage *msg){
    if(strcmp(msg->getName(), "createIPC") == 0){
        cModuleType* moduleType = cModuleType::get("rina.src.DIF.IPCProcess");
        cModule *mod = moduleType->create("flyIPC", this->getModuleByPath("^.^.^"));
        mod->par("ipcAddress").setStringValue(addr);
        mod->par("difName").setStringValue(dif);

        mod->setGateSize("southIo", 1);
        cGate * modIn = mod->gateHalf("southIo", cGate::INPUT, 0);
        cGate * modOut = mod->gateHalf("southIo", cGate::OUTPUT, 0);

        cModule *minus =  getRINAModule(this, 3, {"ipcProcess1"});
        minus->setGateSize("northIo", minus->gateSize("northIo")+1);
        cGate * minusIn = minus->gateHalf("northIo", cGate::INPUT, minus->gateSize("northIo")-1);
        cGate * minusOut = minus->gateHalf("northIo", cGate::OUTPUT, minus->gateSize("northIo")-1);

        //Connecting mod <-> minus
        modOut->connectTo(minusIn);
        minusOut->connectTo(modIn);

        mod->finalizeParameters();

        mod->par("routingPolicyName").setStringValue("TDomainRouting");

        mod->buildInside();

        mod->getSubmodule(MOD_POL_ROUTING)->par("printAtEnd").setBoolValue(true);

        mod->getSubmodule(MOD_RESALLOC)->getSubmodule(MOD_PDUFWDGEN)->deleteModule();
        cModule *modgen = cModuleType::get("rina.policies.DIF.RA.PDUFG.HierarchicalGenerator.HierarchicalGenerator")
            ->create(MOD_PDUFWDGEN,mod->getSubmodule(MOD_RESALLOC));

        mod->getSubmodule(MOD_RELAYANDMUX)->getSubmodule(MOD_POL_RMT_PDUFWD)->deleteModule();
        cModule *modfor = cModuleType::get("rina.policies.DIF.RMT.PDUForwarding.HierarchicalTable.HierarchicalTable")
            ->create(MOD_POL_RMT_PDUFWD,mod->getSubmodule(MOD_RELAYANDMUX));

        modfor->finalizeParameters();
        modgen->finalizeParameters();

        modfor->buildInside();
        modgen->buildInside();


        mod->scheduleStart(simTime());
        mod->callInitialize();

    } else if(strcmp(msg->getName(), "connect") == 0){

        //Retrieve DIF's local IPC member
        DA * DifAllocator = check_and_cast<DA*>
            (getRINAModule(this, 3, {MOD_DIFALLOC, MOD_DA}));
        cModule* targetIpc = DifAllocator->getDifMember(DAP(dif));
        RA * ra = dynamic_cast<RA*>
            (getRINAModule(targetIpc, 0, {MOD_RESALLOC, MOD_RA}));
        if(!ra) { error( "Local IPC RA not found"); }

        string srcN = addr;
        string dstN = dst;

        srcN.append("_").append(dif);
        dstN.append("_").append(dif);

        APNamingInfo srcAPN = APNamingInfo(APN(srcN.c_str()));
        APNamingInfo dstAPN = APNamingInfo(APN(dstN.c_str()));

        Flow * flow   = new Flow(srcAPN, dstAPN);

        if (flow->isManagementFlow()) { // mgmt flow
            ra->createNFlow(flow);
        } else { // data flow
            ra->createNM1Flow(flow);
        }
    }
    delete msg;
}
