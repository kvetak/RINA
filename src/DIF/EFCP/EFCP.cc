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

/*
 * @file EFCP.cc
 * @author Marcel Marek
 * @date Apr 28, 2014
 * @brief
 * @detail
 */
#include "EFCP.h"
Define_Module(EFCP);

#define ECN_POLICY_PREFIX "rina.policies.DIF.EFCP.DTCP.ECN."
#define ECN_POLICY_NAME "ecnPolicy"

#define RCVR_FC_POLICY_PREFIX "rina.policies.DIF.EFCP.DTCP.RcvrFC."
#define RCVR_FC_POLICY_NAME "rcvrFCPolicy"

#define RCVR_ACK_POLICY_PREFIX "rina.policies.DIF.EFCP.DTCP.RcvrAck."
#define RCVR_ACK_POLICY_NAME "rcvrAckPolicy"

#define RECEIVING_FC_POLICY_PREFIX "rina.policies.DIF.EFCP.DTCP.ReceivingFC."
#define RECEIVING_FC_POLICY_NAME "receivingFCPolicy"

#define SENDING_ACK_POLICY_PREFIX "rina.policies.DIF.EFCP.DTCP.SendingAck."
#define SENDING_ACK_POLICY_NAME "sendingAckPolicy"

#define LOST_CONTROL_PDU_POLICY_PREFIX "rina.policies.DIF.EFCP.DTCP.LostControlPDU."
#define LOST_CONTROL_PDU_POLICY_NAME "lostControlPDUPolicy"

#define RCVR_CONTROL_ACK_POLICY_PREFIX "rina.policies.DIF.EFCP.DTCP.RcvrControlAck."
#define RCVR_CONTROL_ACK_POLICY_NAME "rcvrControlAckPolicy"

#define SENDER_ACK_POLICY_PREFIX "rina.policies.DIF.EFCP.DTCP.SenderAck."
#define SENDER_ACK_POLICY_NAME "senderAckPolicy"

#define FC_OVERRUN_POLICY_PREFIX "rina.policies.DIF.EFCP.DTCP.FCOverrun."
#define FC_OVERRUN_POLICY_NAME "fcOverrunPolicy"

#define NO_OVERRIDE_PEAK_POLICY_PREFIX "rina.policies.DIF.EFCP.DTCP.NoOverridePeak."
#define NO_OVERRIDE_PEAK_POLICY_NAME "noOverridePeakPolicy"

#define TX_CONTROL_POLICY_PREFIX "rina.policies.DIF.EFCP.DTCP.TxControl."
#define TX_CONTROL_POLICY_NAME "txControlPolicy"

#define NO_RATE_SLOW_DOWN_POLICY_PREFIX "rina.policies.DIF.EFCP.DTCP.NoRateSlowDown."
#define NO_RATE_SLOW_DOWN_POLICY_NAME "noRateSlowDownPolicy"

#define RECONCILE_FC_POLICY_PREFIX "rina.policies.DIF.EFCP.DTCP.ReconcileFC."
#define RECONCILE_FC_POLICY_NAME "reconcileFCPolicy"

#define RATE_REDUCTION_POLICY_PREFIX "rina.policies.DIF.EFCP.DTCP.RateReduction."
#define RATE_REDUCTION_POLICY_NAME "rateReductionPolicy"


#define RCVR_INACTIVITY_POLICY_PREFIX "rina.policies.DIF.EFCP.DTP.RcvrInactivity."
#define RCVR_INACTIVITY_POLICY_NAME "rcvrInactivityPolicy"

#define SENDER_INACTIVITY_POLICY_PREFIX "rina.policies.DIF.EFCP.DTP.SenderInactivity."
#define SENDER_INACTIVITY_POLICY_NAME "senderInactivityPolicy"

#define INITIAL_SEQ_NUM_POLICY_PREFIX "rina.policies.DIF.EFCP.DTP.InitialSeqNum."
#define INITIAL_SEQ_NUM_POLICY_NAME "initialSeqNumPolicy"

#define RTT_ESTIMATOR_POLICY_PREFIX "rina.policies.DIF.EFCP.DTP.RTTEstimator."
#define RTT_ESTIMATOR_POLICY_NAME "rttEstimatorPolicy"

#define ECN_SLOW_DOWN_POLICY_PREFIX "rina.policies.DIF.EFCP.DTCP.ECNSlowDown."
#define ECN_SLOW_DOWN_POLICY_NAME "ecnSlowDownPolicy"

#define RX_TIMER_EXPIRY_POLICY_PREFIX "rina.policies.DIF.EFCP.DTCP.RxTimerExpiry."
#define RX_TIMER_EXPIRY_POLICY_NAME "rxTimerExpiryPolicy"

EFCP::EFCP() {

}

EFCP::~EFCP() {

}

void EFCP::initialize(int step){
//  if(step == 3){
    efcpTable = (EFCPTable*) getParentModule()->getSubmodule(MOD_EFCPTABLE);
    resourceAllocator = check_and_cast<RA*>
        (getRINAModule(this, 2, {MOD_RESALLOC, MOD_RA}));

//  }


    lisEFCPCongestFromRA = new LisEFCPCongestFromRA(efcpTable);
    getModuleByPath("^.^")->subscribe(SIG_RA_ExecuteSlowdown, lisEFCPCongestFromRA);

}



EFCPInstance* EFCP::createEFCPI(const Flow* flow, int cepId, int portId){
  Enter_Method("createEFCPI()");

//  this->efcpTable = (EFCPTable*)this->getSubmodule("efcpTable");
  const QoSCube* qosCube = resourceAllocator->getQoSCubeById(flow->getConId().getQoSId());
  const EFCPPolicySet* efcpPolicySet = qosCube->getEfcpPolicies();

  cModule* efcpModule = this->getParentModule();

  std::ostringstream name;
  name << MOD_EFCPI << cepId;
  cModuleType* moduleType = cModuleType::get(MOD_EFCPI_PATH);
  cModule* efcpiModule = moduleType->create(name.str().c_str(), efcpModule);
  efcpiModule->par("initialSeqNumPolicyName").setStringValue(efcpPolicySet->getInitialSeqNum());
  efcpiModule->par("rcvrInactivityPolicyName").setStringValue(efcpPolicySet->getRcvrInactiv());
  efcpiModule->par("senderInactivityPolicyName").setStringValue(efcpPolicySet->getSenderInactiv());
  efcpiModule->par("rttEstimatorPolicyName").setStringValue(efcpPolicySet->getRttEstimat());

  efcpiModule->finalizeParameters();
  efcpiModule->buildInside();

  efcpiModule->scheduleStart(simTime());



  //-1. Check for existing Delimiting module for this Flow
  EFCPTableEntry* tmpEfcpEntry;
  if((tmpEfcpEntry = efcpTable->getEntryByFlow(flow)) ==NULL){
    tmpEfcpEntry = new EFCPTableEntry();

   //Flow is not in EFCPTable -> create delimiting
    tmpEfcpEntry->setDelimit(this->createDelimiting(efcpiModule, portId));

    //Add tmpEFCPEntry to efcpTable
    efcpTable->insertEntry(tmpEfcpEntry);
    tmpEfcpEntry->setFlow(flow);
  }


  DTP* dtpModule = check_and_cast<DTP*>
      (getRINAModule(efcpiModule, 0, {MOD_DTP}));
  DTPState* dtpState = check_and_cast<DTPState*>
      (getRINAModule(efcpiModule, 0, {MOD_DTP_STATE}));

  dtpState->setQoSCube(qosCube);
  dtpModule->setState(dtpState);

//  dtpModule->par("rcvrInactivityPolicy").setStringValue(par("rcvrInactivityPolicy").stringValue());
//  dtpModule->par("senderInactivityPolicy").setStringValue(par("senderInactivityPolicy").stringValue());
//  dtpModule->par("initialSeqNumPolicy").setStringValue(par("initialSeqNumPolicy").stringValue());
//  dtpModule->par("rttEstimatorPolicy").setStringValue(par("rttEstimatorPolicy").stringValue());
//  dtpModule->callInitialize(0);
  dtpModule->setFlow(flow);

//  dtpModule->setPduDroppingEnabled(par("pduDroppingEnabled"));

  EFCPInstance* efcpi = new EFCPInstance();
  efcpi->setDtp(dtpModule);


  //2. If necessary create DTCP module
  if(qosCube->isDTCPNeeded()){
      efcpi->setDtcp(this->createDTCP(efcpiModule, efcpPolicySet));
  }else{
    efcpi->setDtcp(NULL);
  }
  //Put created EFCP instance to EFCP Table Entry
  tmpEfcpEntry->addEFCPI(efcpi);


  /* Connect EFCPi module with delimiting */
  int size = tmpEfcpEntry->getDelimit()->gateSize(GATE_DELIMIT_SOUTHIO);
  tmpEfcpEntry->getDelimit()->setGateSize(GATE_DELIMIT_SOUTHIO, size + 1);

  tmpEfcpEntry->getDelimit()->initGates();



  cGate* delToEfcpiI = (cGate*) tmpEfcpEntry->getDelimit()->gateHalf(GATE_DELIMIT_SOUTHIO, cGate::INPUT, size);
  cGate* delToEfcpiO = (cGate*) tmpEfcpEntry->getDelimit()->gateHalf(GATE_DELIMIT_SOUTHIO, cGate::OUTPUT, size);

  cGate* delToFaI = (cGate*) tmpEfcpEntry->getDelimit()->gateHalf(GATE_DELIMIT_NORTHIO, cGate::INPUT);
  cGate* delToFaO = (cGate*) tmpEfcpEntry->getDelimit()->gateHalf(GATE_DELIMIT_NORTHIO, cGate::OUTPUT);


  cGate* efcpiToDelI = efcpiModule->gateHalf(std::string(GATE_EFCPI_NORTHIO).c_str(), cGate::INPUT);
  cGate* efcpiToDelO = efcpiModule->gateHalf(std::string(GATE_EFCPI_NORTHIO).c_str(), cGate::OUTPUT);

  delToEfcpiO->connectTo(efcpiToDelI);
  efcpiToDelO->connectTo(delToEfcpiI);


  /* Create gate in EFCPModule for Delimiting <--> FAI */
  std::ostringstream gateName_str;
  gateName_str << GATE_APPIO_ << portId;



  efcpModule->addGate(gateName_str.str().c_str(), cGate::INOUT);
  cGate* efcpToFaI = efcpModule->gateHalf(gateName_str.str().c_str(), cGate::INPUT);
  cGate* efcpToFaO = efcpModule->gateHalf(gateName_str.str().c_str(), cGate::OUTPUT);

  /* Connect Delimiting with compound module's gates */
  delToFaO->connectTo(efcpToFaO);
  efcpToFaI->connectTo(delToFaI);

  /* Create gate in EFCPModule for EFCPi <--> RMT */
  gateName_str.str(std::string());
  gateName_str << GATE_RMT_ << cepId;
  efcpModule->addGate(gateName_str.str().c_str(), cGate::INOUT);

  cGate* efcpToEfcpiI = efcpModule->gateHalf(gateName_str.str().c_str(), cGate::INPUT);
  cGate* efcpToEfcpiO = efcpModule->gateHalf(gateName_str.str().c_str(), cGate::OUTPUT);

  cGate* efcpiToRmtI = efcpiModule->gateHalf(GATE_EFCPI_SOUTHIO, cGate::INPUT);
  cGate* efcpiToRmtO = efcpiModule->gateHalf(GATE_EFCPI_SOUTHIO, cGate::OUTPUT);

  efcpiToRmtO->connectTo(efcpToEfcpiO);
  efcpToEfcpiI->connectTo(efcpiToRmtI);

  efcpiModule->callInitialize();

  return efcpi;
}

DTCP* EFCP::createDTCP(cModule* efcpiModule, const EFCPPolicySet* efcpPolicySet)
{
    cModuleType* dtcpType = cModuleType::get(MOD_DTCP_PATH);
    DTCP* dtcpModule = (DTCP*) dtcpType->create(MOD_DTCP, efcpiModule);
//    dtcpModule->par("ecnPolicy").setStringValue(par("ecnPolicy").stringValue());
//    dtcpModule->par("rcvrFCPolicy").setStringValue(par("rcvrFCPolicy").stringValue());
//    dtcpModule->par("rcvrAckPolicy").setStringValue(par("rcvrAckPolicy").stringValue());
//    dtcpModule->par("receivingFCPolicy").setStringValue(par("receivingFCPolicy").stringValue());
//    dtcpModule->par("sendingAckPolicy").setStringValue(par("sendingAckPolicy").stringValue());
//    dtcpModule->par("lostControlPDUPolicy").setStringValue(par("lostControlPDUPolicy").stringValue());
//    dtcpModule->par("rcvrControlAckPolicy").setStringValue(par("rcvrControlAckPolicy").stringValue());
//    dtcpModule->par("senderAckPolicy").setStringValue(par("senderAckPolicy").stringValue());
//    dtcpModule->par("fcOverrunPolicy").setStringValue(par("fcOverrunPolicy").stringValue());
//    dtcpModule->par("noOverridePeakPolicy").setStringValue(par("noOverridePeakPolicy").stringValue());
//    dtcpModule->par("txControlPolicy").setStringValue(par("txControlPolicy").stringValue());
//    dtcpModule->par("noRateSlowDownPolicy").setStringValue(par("noRateSlowDownPolicy").stringValue());
//    dtcpModule->par("reconcileFCPolicy").setStringValue(par("reconcileFCPolicy").stringValue());
//    dtcpModule->par("rateReductionPolicy").setStringValue(par("rateReductionPolicy").stringValue());
//    dtcpModule->par("ecnSlowDownPolicy").setStringValue(par("ecnSlowDownPolicy").stringValue());
//

//    ecnPolicy             = (DTCPECNPolicyBase*) createPolicyModule(ECN_POLICY_PREFIX, ECN_POLICY_NAME);
    dtcpModule->setRcvrFcPolicy((RcvrFCPolicyBase*) createPolicyModule(RCVR_FC_POLICY_PREFIX, efcpPolicySet->getRcvrFc(), RCVR_FC_POLICY_NAME, efcpiModule));
    dtcpModule->setRcvrAckPolicy((RcvrAckPolicyBase*) createPolicyModule(RCVR_ACK_POLICY_PREFIX, efcpPolicySet->getRcvrAck(), RCVR_ACK_POLICY_NAME, efcpiModule));
    dtcpModule->setReceivingFcPolicy((ReceivingFCPolicyBase*) createPolicyModule(RECEIVING_FC_POLICY_PREFIX, efcpPolicySet->getReceivingFc(), RECEIVING_FC_POLICY_NAME, efcpiModule));
    dtcpModule->setSendingAckPolicy((SendingAckPolicyBase*) createPolicyModule(SENDING_ACK_POLICY_PREFIX, efcpPolicySet->getSendingAck(), SENDING_ACK_POLICY_NAME, efcpiModule));
    dtcpModule->setLostControlPduPolicy((LostControlPDUPolicyBase*) createPolicyModule(LOST_CONTROL_PDU_POLICY_PREFIX, efcpPolicySet->getLostControlPdu(), LOST_CONTROL_PDU_POLICY_NAME, efcpiModule));
    dtcpModule->setRcvrControlAckPolicy((RcvrControlAckPolicyBase*) createPolicyModule(RCVR_CONTROL_ACK_POLICY_PREFIX, efcpPolicySet->getRcvrControlAck(), RCVR_CONTROL_ACK_POLICY_NAME, efcpiModule));
    dtcpModule->setSenderAckPolicy((SenderAckPolicyBase*) createPolicyModule(SENDER_ACK_POLICY_PREFIX, efcpPolicySet->getSenderAck(), SENDER_ACK_POLICY_NAME, efcpiModule));
    dtcpModule->setFcOverrunPolicy((FCOverrunPolicyBase*) createPolicyModule(FC_OVERRUN_POLICY_PREFIX, efcpPolicySet->getFcOverrun(), FC_OVERRUN_POLICY_NAME, efcpiModule));
    dtcpModule->setNoOverridePeakPolicy((NoOverridePeakPolicyBase*) createPolicyModule(NO_OVERRIDE_PEAK_POLICY_PREFIX, efcpPolicySet->getNoOverridePeak(), NO_OVERRIDE_PEAK_POLICY_NAME, efcpiModule));
    dtcpModule->setTxControlPolicy((TxControlPolicyBase*) createPolicyModule(TX_CONTROL_POLICY_PREFIX, efcpPolicySet->getTxControl(), TX_CONTROL_POLICY_NAME, efcpiModule));
    dtcpModule->setNoRateSlowDownPolicy((NoRateSlowDownPolicyBase*) createPolicyModule(NO_RATE_SLOW_DOWN_POLICY_PREFIX, efcpPolicySet->getNoRateSlowDown(), NO_RATE_SLOW_DOWN_POLICY_NAME, efcpiModule));
    dtcpModule->setReconcileFcPolicy( (ReconcileFCPolicyBase*) createPolicyModule(RECONCILE_FC_POLICY_PREFIX, efcpPolicySet->getReconcileFc(), RECONCILE_FC_POLICY_NAME, efcpiModule));
    dtcpModule->setRateReductionPolicy( (RateReductionPolicyBase*) createPolicyModule(RATE_REDUCTION_POLICY_PREFIX, efcpPolicySet->getRateReduction(), RATE_REDUCTION_POLICY_NAME, efcpiModule));
    dtcpModule->setRxTimerExpiryPolicy( (RxTimerExpiryPolicyBase*) createPolicyModule(RX_TIMER_EXPIRY_POLICY_PREFIX, efcpPolicySet->getRxTimerExpiry(), RX_TIMER_EXPIRY_POLICY_NAME, efcpiModule));
//    dtcpModule->setEcnSlowDownPolicy( (DTCPECNSlowDownPolicyBase*) createPolicyModule(ECN_SLOW_DOWN_POLICY_PREFIX, ECN_SLOW_DOWN_POLICY_NAME);





//    efcpiModule->par("rttEstimatorPolicyName").setStringValue(efcpPolicySet->getRttEstimat());


    dtcpModule->finalizeParameters();
    dtcpModule->buildInside();
    dtcpModule->scheduleStart(simTime());



    cModuleType* dtcpStateType = cModuleType::get(MOD_DTCP_STATE_PATH);

    DTCPState* dtcpState = (DTCPState*)dtcpStateType->create(MOD_DTCP_STATE, efcpiModule);
    dtcpState->finalizeParameters();
    dtcpState->buildInside();
    dtcpState->scheduleStart(simTime());

    dtcpModule->setDtcpState(dtcpState);


//    dtcpModule->callInitialize();


    return dtcpModule;
}

/**
 *
 * @param prefix Prefix to the location of specific policy (eg. rina.policies.DIF.EFCP.DTP.InitialSeqNum.) including the last dot.
 * @param name Name of the specific policy type. This method expects .ned file in directory with the same name (eg. InitialSeqNumPolicyDefault)
 * @param policy Name of the variable holding pointer to this policy.
 * @param parent Parent module in which the policy will be created.
 * @return returns pointer to newly created module
 */
cModule* EFCP::createPolicyModule(const char* prefix, const char* name, const char* policy, cModule* parent)
{

    std::stringstream modulePath;
    modulePath << prefix << name <<"."<< name;
    cModuleType* policyType = cModuleType::get(modulePath.str().c_str());
    cModule* module =  policyType->create(policy, parent);
    module->finalizeParameters();
    module->buildInside();
    module->scheduleStart(simTime());

    cDisplayString& disp = module->getDisplayString();
    disp.setTagArg("is", 0, "vs");

//    return policyType->createScheduleInit(policy, parent);
    return module;

}


Delimiting* EFCP::createDelimiting(cModule* efcpiModule, int portId){


    std::ostringstream name;
    name << DELIMITING_MODULE_NAME << "_" << portId;
    //0. Create Delimiting module within EFCPModule
    cModuleType* delimitType = cModuleType::get(MOD_DELIMITING_PATH);

    Delimiting* delimit = (Delimiting*)delimitType->create(name.str().c_str(), this->getParentModule());
    delimit->finalizeParameters();
    delimit->buildInside();
    delimit->scheduleStart(simTime());
    delimit->callInitialize();

    return delimit;
}
/**
 *
 * @param flow
 * @return
 */
bool EFCP::deleteEFCPI(Flow* flow)
{
  EFCPTableEntry* entry;
  if((entry = efcpTable->getEntryByFlow(flow)) == NULL){

    EV << getFullPath() << ": failed to found EFCPTableEntry by Flow to deallocate EFCPI" << endl;
    return false;
  }

//  entry->flushDTPs();
  entry->getDelimit()->callFinish();
  entry->getDelimit()->deleteModule();
  for(;!entry->getEfcpiTab()->empty();){
    entry->getEfcpiTab()->front()->getDtp()->getParentModule()->callFinish();
    entry->getEfcpiTab()->front()->getDtp()->getParentModule()->deleteModule();
//    delete entry->getEfcpiTab()->front()->getDtcp()->deleteModule();
    entry->getEfcpiTab()->erase(entry->getEfcpiTab()->begin());

  }


  return true;


}

