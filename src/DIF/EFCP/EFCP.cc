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


EFCPInstance * EFCP::createEFCPI(Flow* flow){

  EFCPInstance* efcpi = new EFCPInstance();

  cModuleType *moduleType = cModuleType::get("rina.DIF.EFCP.EFCPI");
//  std::ostringstream ostr;
//      ostr << "test";
  cModule* efcpiModule = moduleType->create("Test", this->getParentModule());
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
  if((tmpEfcpEntry = efcpTable.getEntryByFlow(flow)) ==NULL){
   //Flow is not in EFCPTable -> create delimiting

    //0. Create Delimiting module within EFCPModule
    cModuleType* delimitType = cModuleType::get("rina.DIF.Delimiting.Delimiting");

    Delimiting* delimit = (Delimiting*)delimitType->create("delimit", this->getParentModule());
    delimit->finalizeParameters();
    delimit->buildInside();
    delimit->scheduleStart(simTime());
    delimit->callInitialize();


    tmpEfcpEntry = new EFCPTableEntry();
    tmpEfcpEntry->setDelimit(delimit);

    //TODO A1: Connect Delimiting and FAI modules


  }

  //1. Create DTP module within the "module" aka EFCI
  cModuleType* dtpType = cModuleType::get("rina.DIF.EFCP.DTP");

  DTP* dtp = (DTP*)dtpType->create("dtp",efcpiModule);
  dtp->finalizeParameters();
  dtp->buildInside();
  dtp->scheduleStart(simTime());
  dtp->callInitialize();

  efcpi->setDtp(dtp);

  //2. If necessary create DTCP module
  //TODO how to determine DTCP module is needed
  if(true){
    cModuleType* dtcpType = cModuleType::get("rina.DIF.EFCP.DTCP");
    DTCP* dtcp = (DTCP*)dtcpType->create("dtcp",efcpiModule);
      dtcp->finalizeParameters();
      dtcp->buildInside();
      dtcp->scheduleStart(simTime());
      dtcp->callInitialize();

      efcpi->setDtcp(dtcp);
  }


  //3. create EFCPInstance and set dtp (and dtcp) variables in EFCPInstance
  //done

  //4. Start modules
  //done

  //TODO A! Connect modules





  return efcpi;
}

