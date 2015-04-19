/*

 * RINASignals.h
 *
 *  Created on: 21. 7. 2014
 *      Author: Mordeth
 */

#ifndef RINASIGNALS_H_
#define RINASIGNALS_H_

//AE
extern const char* SIG_AE_AllocateRequest;
extern const char* SIG_AE_DeallocateRequest;
extern const char* SIG_AE_DataSend;
extern const char* SIG_AE_ConnectionRequest;
extern const char* SIG_AE_ReleaseRequest;

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

//CDAP
extern const char* SIG_CDAP_DateReceive;

//CACE
extern const char* SIG_CACE_ConnectionResponsePositive;
extern const char* SIG_CACE_ConnectionResponseNegative;
extern const char* SIG_CACE_ReleaseResponse;
extern const char* SIG_CACE_AuthenticationRequest;

//Auth
extern const char* SIG_Auth_AuthenticationResponse;

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
extern const char* SIG_RA_AllocateRequest;
extern const char* SIG_RA_DeallocateRequest;
extern const char* SIG_RA_AllocateResponsePositive;
extern const char* SIG_RA_AllocateResponseNegative;
extern const char* SIG_RA_FlowAllocated;
extern const char* SIG_RA_FlowDeallocated;
extern const char* SIG_RA_CreateFlowPositive;
extern const char* SIG_RA_CreateFlowNegative;
extern const char* SIG_RA_InvokeSlowdown;
extern const char* SIG_RA_ExecuteSlowdown;

//RIB
extern const char* SIG_RIB_CreateRequestFlow;
extern const char* SIG_RIB_CreateResponseFlow;
extern const char* SIG_RIB_DeleteRequestFlow;
extern const char* SIG_RIB_DeleteResponseFlow;

//RMT
extern const char* SIG_RMT_NoConnId;
extern const char* SIG_RMT_ErrornousPacket;
extern const char* SIG_RMT_SlowdownRequest;
extern const char* SIG_RMT_QueuePDURcvd;
extern const char* SIG_RMT_QueuePDUPreSend;
extern const char* SIG_RMT_QueuePDUSent;
extern const char* SIG_RMT_PortPDURcvd;
extern const char* SIG_RMT_PortPDUSent;
extern const char* SIG_RMT_PortReadyToServe;
extern const char* SIG_RMT_PortReadyForRead;

// PDUFTG
extern const char* SIG_PDUFTG_FwdInfoUpdate;
extern const char* SIG_RIBD_RoutingUpdate;

//EFCP (DTP+DTCP)
extern const char* SIG_EFCP_StopSending;
extern const char* SIG_EFCP_StartSending;

#endif /* RINASIGNALS_H_ */


