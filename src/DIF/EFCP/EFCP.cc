//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
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

/*
 * @file EFCP.cc
 * @author Marcel Marek
 * @date Apr 28, 2014
 * @brief
 * @detail
 */
#include "EFCP.h"
Define_Module(EFCP);

EFCP::EFCP() {

}

EFCP::~EFCP() {

}

void EFCP::initialize(int step){
//  if(step == 3){
    this->efcpTable = (EFCPTable*) getParentModule()->getSubmodule(MOD_EFCPTABLE);
    resourceAllocator = ModuleAccess<RA>(MOD_RA).get();
//  }
}



EFCPInstance* EFCP::createEFCPI(Flow* flow, int cepId){
  Enter_Method("createEFCPI()");

//  this->efcpTable = (EFCPTable*)this->getSubmodule("efcpTable");

  cModule* efcpModule = this->getParentModule();

  std::ostringstream name;
  name << MOD_EFCPI << flow->getConId().getSrcCepId();
  cModuleType *moduleType = cModuleType::get("rina.DIF.EFCP.EFCPI");
  cModule* efcpiModule = moduleType->create(name.str().c_str(), efcpModule);

  efcpiModule->finalizeParameters();
  efcpiModule->buildInside();

  efcpiModule->scheduleStart(simTime());



  //-1. Check for existing Delimiting module for this Flow
  EFCPTableEntry* tmpEfcpEntry;
  if((tmpEfcpEntry = efcpTable->getEntryByFlow(flow)) ==NULL){
    tmpEfcpEntry = new EFCPTableEntry();



   //Flow is not in EFCPTable -> create delimiting
    tmpEfcpEntry->setDelimit(this->createDelimiting(efcpiModule, flow->getSrcPortId()));

    //Add tmpEFCPEntry to efcpTable
    efcpTable->insertEntry(tmpEfcpEntry);
    tmpEfcpEntry->setFlow(flow);
  }

  const QoSCube* qosCube = resourceAllocator->getQoSCubeById(flow->getConId().getQoSId());
  DTP* dtpModule = (DTP*)efcpiModule->getModuleByPath((std::string(".") + std::string(DTP_MODULE_NAME)).c_str());
  dtpModule->par("rcvrInactivityPolicy").setStringValue(par("rcvrInactivityPolicy").stringValue());
  dtpModule->par("senderInactivityPolicy").setStringValue(par("senderInactivityPolicy").stringValue());
  dtpModule->par("initialSeqNumPolicy").setStringValue(par("initialSeqNumPolicy").stringValue());
  dtpModule->par("rttEstimatorPolicy").setStringValue(par("rttEstimatorPolicy").stringValue());
  dtpModule->callInitialize(0);
  dtpModule->setFlow(flow);
  dtpModule->setQoSCube(qosCube);
  dtpModule->setPduDroppingEnabled(par("pduDroppingEnabled"));

  EFCPInstance* efcpi = new EFCPInstance();
  efcpi->setDtp(dtpModule);


  //2. If necessary create DTCP module
  if(qosCube->isDTCPNeeded()){
      efcpi->setDtcp(this->createDTCP(efcpiModule));
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
  gateName_str << GATE_APPIO_ << cepId;



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

DTCP* EFCP::createDTCP(cModule* efcpiModule)
{
    cModuleType* dtcpType = cModuleType::get(MOD_DTCP_PATH);
    DTCP* dtcpModule = (DTCP*) dtcpType->create(MOD_DTCP, efcpiModule);
    dtcpModule->par("ecnPolicy").setStringValue(par("ecnPolicy").stringValue());
    dtcpModule->par("rcvrFCPolicy").setStringValue(par("rcvrFCPolicy").stringValue());
    dtcpModule->par("rcvrAckPolicy").setStringValue(par("rcvrAckPolicy").stringValue());
    dtcpModule->par("receivingFCPolicy").setStringValue(par("receivingFCPolicy").stringValue());
    dtcpModule->par("sendingAckPolicy").setStringValue(par("sendingAckPolicy").stringValue());
    dtcpModule->par("lostControlPDUPolicy").setStringValue(par("lostControlPDUPolicy").stringValue());
    dtcpModule->par("rcvrControlAckPolicy").setStringValue(par("rcvrControlAckPolicy").stringValue());
    dtcpModule->par("senderAckPolicy").setStringValue(par("senderAckPolicy").stringValue());
    dtcpModule->par("fcOverrunPolicy").setStringValue(par("fcOverrunPolicy").stringValue());
    dtcpModule->par("noOverridePeakPolicy").setStringValue(par("noOverridePeakPolicy").stringValue());
    dtcpModule->par("txControlPolicy").setStringValue(par("txControlPolicy").stringValue());
    dtcpModule->par("noRateSlowDownPolicy").setStringValue(par("noRateSlowDownPolicy").stringValue());
    dtcpModule->par("reconcileFCPolicy").setStringValue(par("reconcileFCPolicy").stringValue());
    dtcpModule->par("rateReductionPolicy").setStringValue(par("rateReductionPolicy").stringValue());
    dtcpModule->finalizeParameters();
    dtcpModule->buildInside();
    dtcpModule->scheduleStart(simTime());
//    dtcpModule->callInitialize();


    return dtcpModule;
}


Delimiting* EFCP::createDelimiting(cModule* efcpiModule, int portId){


    std::ostringstream name;
    name << DELIMITING_MODULE_NAME << "_" << portId;
    //0. Create Delimiting module within EFCPModule
    cModuleType* delimitType = cModuleType::get("rina.DIF.Delimiting.Delimiting");

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
  delete entry->getDelimit();
  for(;!entry->getEfcpiTab()->empty();){
    delete entry->getEfcpiTab()->front()->getDtp();
    delete entry->getEfcpiTab()->front()->getDtcp();
    entry->getEfcpiTab()->erase(entry->getEfcpiTab()->begin());

  }


  return true;


}

