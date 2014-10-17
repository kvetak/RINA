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



}

EFCP::~EFCP() {
    // TODO Auto-generated destructor stub
}

void EFCP::initialize(int step){
//  if(step == 3){
    this->efcpTable = (EFCPTable*) getParentModule()->getSubmodule(MOD_EFCPTABLE);
//  }
}



EFCPInstance* EFCP::createEFCPI(Flow* flow, int cepId){
  Enter_Method("createEFCPI()");

//  this->efcpTable = (EFCPTable*)this->getSubmodule("efcpTable");

  cModule* efcpModule = this->getParentModule();

  cModuleType *moduleType = cModuleType::get("rina.DIF.EFCP.EFCPI");
  cModule* efcpiModule = moduleType->create(MOD_EFCPI, efcpModule);
  efcpiModule->finalizeParameters();
  efcpiModule->buildInside();

  efcpiModule->scheduleStart(simTime());
  efcpiModule->callInitialize();


  //-1. Check for existing Delimiting module for this Flow
  EFCPTableEntry* tmpEfcpEntry;
  if((tmpEfcpEntry = efcpTable->getEntryByFlow(flow)) ==NULL){
    tmpEfcpEntry = new EFCPTableEntry();
   //Flow is not in EFCPTable -> create delimiting
    tmpEfcpEntry->setDelimit(this->createDelimiting(efcpiModule));

    //TODO A!: Add tmpEFCPEntry to efcpTable
  }


  DTP* dtpModule = (DTP*)efcpiModule->getModuleByPath((std::string(".") + std::string(DTP_MODULE_NAME)).c_str());
  dtpModule->setFlow(flow);

  EFCPInstance* efcpi = new EFCPInstance();
  efcpi->setDtp(dtpModule);

  //2. If necessary create DTCP module
  //TODO how to determine DTCP module is needed
  if(true){
      efcpi->setDtcp(this->createDTCP(efcpiModule));
  }
  //Put created EFCP instance to EFCP Table Entry
  tmpEfcpEntry->addEFCPI(efcpi);

 //TODO A! if it already exists in efcpTable?
 //insert triplet (DTP,DTCP,Delimiting) to efcpTable
  efcpTable->insertEntry(tmpEfcpEntry);


  /* Connect EFCPi module with delimiting */
  int size = tmpEfcpEntry->getDelimit()->gateSize("efcpiIo");
  tmpEfcpEntry->getDelimit()->setGateSize("efcpiIo", size + 1);


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

  return efcpi;
}

DTCP* EFCP::createDTCP(cModule* efcpiModule)
{
    cModuleType* dtcpType = cModuleType::get("rina.DIF.EFCP.DTCP");
    DTCP* dtcpModule = (DTCP*) dtcpType->create(MOD_DTCP, efcpiModule);
    dtcpModule->finalizeParameters();
    dtcpModule->buildInside();
    dtcpModule->scheduleStart(simTime());
    dtcpModule->callInitialize();


    return dtcpModule;
}


Delimiting* EFCP::createDelimiting(cModule* efcpiModule){
    //0. Create Delimiting module within EFCPModule
    cModuleType* delimitType = cModuleType::get("rina.DIF.Delimiting.Delimiting");

    Delimiting* delimit = (Delimiting*)delimitType->create(DELIMITING_MODULE_NAME, this->getParentModule());
    delimit->finalizeParameters();
    delimit->buildInside();
    delimit->scheduleStart(simTime());
    delimit->callInitialize();

    return delimit;
}


