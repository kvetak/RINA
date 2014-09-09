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
    // TODO Auto-generated constructor stub
  this->efcpTable = (EFCPTable*)this->getParentModule()->getSubmodule("efcpTable");


}

EFCP::~EFCP() {
    // TODO Auto-generated destructor stub
}



EFCPInstance* EFCP::createEFCPI(Flow* flow){
  Enter_Method("createEFCPI()");
  EFCPInstance* efcpi = new EFCPInstance();

  cModuleType *moduleType = cModuleType::get("rina.DIF.EFCP.EFCPI");
//  std::ostringstream ostr;
//      ostr << "test";
  cModule* efcpiModule = moduleType->create("efcpi", this);
  efcpiModule->finalizeParameters();
  efcpiModule->buildInside();

  efcpiModule->scheduleStart(simTime());
  efcpiModule->callInitialize();



  //TODO:
  //-1. Check for existing Delimiting module for this Flow
  //0. Create Delimiting module within EFCPModule
  //1. Create DTP module within the "module" aka EFCI
  //2. If necessary create DTCP module
  //3. create EFCPInstance and set dtp (and dtcp) variables in EFCPInstance
  //4. Start modules

  //-1. Check for existing Delimiting module for this Flow
  EFCPTableEntry* tmpEfcpEntry;
  if((tmpEfcpEntry = efcpTable->getEntryByFlow(flow)) ==NULL){
   //Flow is not in EFCPTable -> create delimiting

    //0. Create Delimiting module within EFCPModule
    cModuleType* delimitType = cModuleType::get("rina.DIF.Delimiting.Delimiting");

    Delimiting* delimit = (Delimiting*)delimitType->create(DELIMITING_MODULE_NAME, this);
    delimit->finalizeParameters();
    delimit->buildInside();
    delimit->scheduleStart(simTime());
    delimit->callInitialize();


    tmpEfcpEntry = new EFCPTableEntry();
    tmpEfcpEntry->setDelimit(delimit);

    //TODO A1: Connect Delimiting and FAI modules
    //TODO A!: Add tmpEFCPEntry to efcpTable

  }

  Delimiting* delModule = (Delimiting*)efcpiModule->getModuleByPath((std::string(".") + std::string(DTP_MODULE_NAME)).c_str());
  DTP* dtpModule = (DTP*)efcpiModule->getModuleByPath((std::string(".") + std::string(DTP_MODULE_NAME)).c_str());

  //1. Create DTP module within the "module" aka EFCI
//  cModuleType* dtpType = cModuleType::get("rina.DIF.EFCP.DTP");

//  DTP* dtp = (DTP*)dtpType->create("dtp",efcpiModule);
//  dtp->finalizeParameters();
//  dtp->buildInside();
//  dtp->scheduleStart(simTime());
//  dtp->callInitialize();

  efcpi->setDtp(dtpModule);

  //2. If necessary create DTCP module
  //TODO how to determine DTCP module is needed
  if(true){
    cModuleType* dtcpType = cModuleType::get("rina.DIF.EFCP.DTCP");
    DTCP* dtcpModule = (DTCP*)dtcpType->create("dtcp",efcpiModule);
      dtcpModule->finalizeParameters();
      dtcpModule->buildInside();
      dtcpModule->scheduleStart(simTime());
      dtcpModule->callInitialize();

      efcpi->setDtcp(dtcpModule);

  }


  //3. create EFCPInstance and set dtp (and dtcp) variables in EFCPInstance
  //done

  //4. Start modules
  //done

  //TODO A! Connect modules





  /* Connect EFCPi module with delimiting */
  int size = tmpEfcpEntry->getDelimit()->gateSize("efcpiIo");
  tmpEfcpEntry->getDelimit()->setGateSize("efcpiIo", size + 1);
//  delToEfcp->size();

  cGate* delToEfcpiI = (cGate*) tmpEfcpEntry->getDelimit()->gateHalf("efcpiIo", cGate::INPUT, size);
  cGate* delToEfcpiO = (cGate*) tmpEfcpEntry->getDelimit()->gateHalf("efcpiIo", cGate::OUTPUT, size);

  cGate* delToFaI = (cGate*) tmpEfcpEntry->getDelimit()->gateHalf("efcpModuleIo", cGate::INPUT);
  cGate* delToFaO = (cGate*) tmpEfcpEntry->getDelimit()->gateHalf("efcpModuleIo", cGate::OUTPUT);


//  cModule* efcpModule = this->getParentModule();
//  efcpModule->addGate("fa_" + flow->getDstPortId(), cGate::INOUT, false);
//  cGate* efcpToFA = efcpModule->gate("fa_" + flow->getDstPortId());

//  cGate* dtpToEfcpI = dtpModule->gateHalf("efcpIo", cGate::INPUT);
//  cGate* dtpToEfcpO = dtpModule->gateHalf("efcpIo", cGate::OUTPUT);

//  efcpiModule->addGate(std::string("delToEfcpiIo").c_str(), cGate::INOUT);

  cGate* efcpiToDelI = efcpiModule->gateHalf(std::string("delToEfcpiIo").c_str(), cGate::INPUT);
  cGate* efcpiToDelO = efcpiModule->gateHalf(std::string("delToEfcpiIo").c_str(), cGate::OUTPUT);

  delToEfcpiO->connectTo(efcpiToDelI);
  efcpiToDelO->connectTo(delToEfcpiI);
//  efcpiToDtpO->connectTo(dtpToEfcpI);
//  dtpToEfcpO->connectTo(efcpiToDtpI);
//
//   delToEfcpiI->connectTo(efcpiToDtpO);
//   delToEfcpiO->connectTo(efcpiToDtpI);

//   delToEfcpiO->connectTo(efcpiToDtp);
//   dtpToEfcpO->connectTo(delToEfcpiI);

//  cGate* gateDelimitToFAI = (cGate*)tmpEfcpEntry->getDelimit()->gate("faiIo$i");
//  cGate* gateFAIToDelimit = (cGate*)fai->gate("efcpIo$o");
//  gateDelimitToFAI->connectTo(gateFAIToDelimit);
//  gateDelimitToFAI->connectTo()

  /* Create gate in EFCPModule for Delimiting <--> FAI */
  std::ostringstream gateName_str;
  gateName_str << "fai_" << flow->getConId().getSrcCepId();

  cModule* efcpModule = this;
  efcpModule->addGate(gateName_str.str().c_str(), cGate::INOUT);
  cGate* efcpToFaI = efcpModule->gateHalf(gateName_str.str().c_str(), cGate::INPUT);
  cGate* efcpToFaO = efcpModule->gateHalf(gateName_str.str().c_str(), cGate::OUTPUT);

  /* Connect Delimiting with compound module's gates */
  delToFaO->connectTo(efcpToFaO);
  efcpToFaI->connectTo(delToFaI);

  /* Create gate in EFCPModule for EFCPi <--> RMT */
  gateName_str.str(std::string());
  gateName_str << "rmt_" << flow->getConId().getSrcCepId();
  efcpModule->addGate(gateName_str.str().c_str(), cGate::INOUT);

  cGate* efcpToEfcpiI = efcpModule->gateHalf(gateName_str.str().c_str(), cGate::INPUT);
  cGate* efcpToEfcpiO = efcpModule->gateHalf(gateName_str.str().c_str(), cGate::OUTPUT);

  cGate* efcpiToRmtI = efcpiModule->gateHalf(std::string("rmtIo").c_str(), cGate::INPUT);
  cGate* efcpiToRmtO = efcpiModule->gateHalf(std::string("rmtIo").c_str(), cGate::OUTPUT);

  efcpiToRmtO->connectTo(efcpToEfcpiO);
  efcpToEfcpiI->connectTo(efcpiToRmtI);

  return efcpi;
}

