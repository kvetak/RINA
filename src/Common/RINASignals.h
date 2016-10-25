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
 * RINASignals.h
 *
 *  Created on: 21. 7. 2014
 *      Author: Vladimir Vesely, Marcel Marek, Tomas Hykel, Kamil Jerabek
 */

#ifndef RINASIGNALS_H_
#define RINASIGNALS_H_

//AP
extern const char* SIG_AP_AE_API;

//AE
extern const char* SIG_AE_AllocateRequest;
extern const char* SIG_AE_DeallocateRequest;
extern const char* SIG_AE_DataSend;
extern const char* SIG_AE_ConnectionRequest;
extern const char* SIG_AE_ReleaseRequest;
extern const char* SIG_AE_Enrolled;

extern const char* SIG_AE_AP_API;

//Socket
extern const char* SIG_Socket_QueueInfo;

//RIBd
extern const char* SIG_RIBD_DataSend;
extern const char* SIG_RIBD_CreateRequestFlow;
extern const char* SIG_RIBD_DeleteRequestFlow;
extern const char* SIG_RIBD_DeleteResponseFlow;
extern const char* SIG_RIBD_CreateFlow;
extern const char* SIG_RIBD_CreateFlowResponseNegative;
extern const char* SIG_RIBD_CreateFlowResponsePositive;
extern const char* SIG_RIBD_ForwardingUpdateReceived;
extern const char* SIG_RIBD_RoutingUpdateReceived;
extern const char* SIG_RIBD_CongestionNotification;

extern const char* SIG_RIBD_StartEnrollmentRequest;
extern const char* SIG_RIBD_StartEnrollmentResponse;
extern const char* SIG_RIBD_StopEnrollmentRequest;
extern const char* SIG_RIBD_StopEnrollmentResponse;
extern const char* SIG_RIBD_StartOperationRequest;
extern const char* SIG_RIBD_StartOperationResponse;

extern const char* SIG_RIBD_ConnectionResponsePositive;
extern const char* SIG_RIBD_ConnectionResponseNegative;
extern const char* SIG_RIBD_ConnectionRequest;
extern const char* SIG_RIBD_CACESend;

//DAF AEMgmt
extern const char* SIG_AEMGMT_ConnectionResponsePositive;

//Enrollment
extern const char* SIG_ENROLLMENT_DataSend;
extern const char* SIG_ENROLLMENT_CACEDataSend;
extern const char* SIG_ENROLLMENT_StartEnrollmentRequest;
extern const char* SIG_ENROLLMENT_StartEnrollmentResponse;
extern const char* SIG_ENROLLMENT_StopEnrollmentRequest;
extern const char* SIG_ENROLLMENT_StopEnrollmentResponse;
extern const char* SIG_ENROLLMENT_StartOperationRequest;
extern const char* SIG_ENROLLMENT_StartOperationResponse;

extern const char* SIG_ENROLLMENT_Finished;

//CDAP
extern const char* SIG_CDAP_DateReceive;
extern const char* SIG_CDAP_SendData;

//CACE
extern const char* SIG_CACE_DataReceive;

//IRM
extern const char* SIG_IRM_AllocateRequest;
extern const char* SIG_IRM_DeallocateRequest;
extern const char* SIG_AERIBD_AllocateResponsePositive;
extern const char* SIG_AERIBD_AllocateResponseNegative;

//FA
extern const char* SIG_FA_CreateFlowResponseNegative;
extern const char* SIG_FA_CreateFlowResponsePositive;
extern const char* SIG_FA_CreateFlowRequestForward;
extern const char* SIG_FA_CreateFlowResponseForward;
extern const char* SIG_FA_AllocateResponsePositive;
extern const char* SIG_FA_AllocateResponseNegative;
extern const char* SIG_FA_MgmtFlowAllocated;

//FAI
extern const char* SIG_toFAI_AllocateRequest;
extern const char* SIG_toFAI_AllocateResponsePositive;
extern const char* SIG_toFAI_AllocateResponseNegative;
extern const char* SIG_FAI_AllocateRequest;
extern const char* SIG_FAI_DeallocateRequest;
extern const char* SIG_FAI_DeallocateResponse;
extern const char* SIG_FAI_AllocateResponsePositive;
extern const char* SIG_FAI_AllocateResponseNegative;
extern const char* SIG_FAI_CreateFlowRequest;
extern const char* SIG_FAI_DeleteFlowRequest;
extern const char* SIG_FAI_CreateFlowResponsePositive;
extern const char* SIG_FAI_CreateFlowResponseNegative;
extern const char* SIG_FAI_DeleteFlowResponse;

//RA
extern const char* SIG_RA_CreateFlowPositive;
extern const char* SIG_RA_CreateFlowNegative;
extern const char* SIG_RA_InvokeSlowdown;
extern const char* SIG_RA_ExecuteSlowdown;
extern const char* SIG_RA_MgmtFlowAllocated;
extern const char* SIG_RA_MgmtFlowDeallocated;

//RIB
extern const char* SIG_RIB_CreateRequestFlow;
extern const char* SIG_RIB_CreateResponseFlow;
extern const char* SIG_RIB_DeleteRequestFlow;
extern const char* SIG_RIB_DeleteResponseFlow;

//RMT
extern const char* SIG_RMT_NoConnId;
extern const char* SIG_RMT_ErrornousPacket;
extern const char* SIG_RMT_SlowdownRequest;
extern const char* SIG_RMT_QueuePDUPreRcvd;
extern const char* SIG_RMT_QueuePDUPostRcvd;
extern const char* SIG_RMT_QueuePDUPreSend;
extern const char* SIG_RMT_QueuePDUSent;
extern const char* SIG_RMT_PortPDURcvd;
extern const char* SIG_RMT_PortPDUSent;
extern const char* SIG_RMT_PortReadyToServe;
extern const char* SIG_RMT_PortReadyForRead;
extern const char* SIG_RMT_QueueInfo;

// PDUFTG
extern const char* SIG_PDUFTG_FwdInfoUpdate;
extern const char* SIG_RIBD_RoutingUpdate;

//EFCP (DTP+DTCP)
extern const char* SIG_EFCP_StopSending;
extern const char* SIG_EFCP_StartSending;

//VAR
extern const char* SIG_VAR_ViFIB_Slave2Master;
extern const char* SIG_VAR_ViFIB_Master2Slave;
extern const char* SIG_VAR_AddedFlow;
extern const char* SIG_VAR_RemovedFlow;

#endif /* RINASIGNALS_H_ */


