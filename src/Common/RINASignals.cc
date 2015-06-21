/*
 * RINASignals.cc
 *
 *  Created on: 22. 7. 2014
 *      Author: Mordeth
 */

#include "RINASignals.h"

const char* SIG_AE_AllocateRequest              = "AE-AllocateRequest";
const char* SIG_AE_DeallocateRequest            = "AE-DeallocateRequest";
const char* SIG_AE_DataSend                     = "AE-DataSend";
const char* SIG_AE_ConnectionRequest            = "AE-ConnectionRequest";
const char* SIG_AE_ReleaseRequest               = "AE-ReleaseRequest";

const char* SIG_RIBD_DataSend                   = "RIBd-DataSend";
const char* SIG_RIBD_CreateRequestFlow          = "RIBd-CreateRequestFlow";
const char* SIG_RIBD_DeleteRequestFlow          = "RIBd-DeleteRequestFlow";
const char* SIG_RIBD_DeleteResponseFlow         = "RIBd-DeleteResponseFlow";
const char* SIG_RIBD_CreateFlow                 = "RIBd-CreateFlow";
const char* SIG_RIBD_CreateFlowResponseNegative = "RIBd-CreateFlowResponseNegative";
const char* SIG_RIBD_CreateFlowResponsePositive = "RIBd-CreateFlowResponsePositive";
const char* SIG_RIBD_ForwardingUpdateReceived   = "RIBd-ForwardingUpdateReceived";
const char* SIG_RIBD_RoutingUpdateReceived      = "Routing-UpdateReceived";

const char* SIG_RIBD_CongestionNotification     = "RIBd-CongestionNotification";

const char* SIG_RIBD_StartEnrollmentRequest     = "RIBd-StartEnrollmentRequest";
const char* SIG_RIBD_StartEnrollmentResponse    = "RIBd-StartEnrollmentResponse";
const char* SIG_RIBD_StopEnrollmentRequest      = "RIBd-StopEnrollmentRequest";
const char* SIG_RIBD_StopEnrollmentResponse     = "RIBd-StopEnrollmentResponse";
const char* SIG_RIBD_StartOperationRequest      = "RIBd-StartOperationRequest";
const char* SIG_RIBD_StartOperationResponse     = "RIBd-StartOperationResponse";

const char* SIG_RIBD_ConnectionResponsePositive = "RIBd-ConnectionResponsePositive";
const char* SIG_RIBD_ConnectionResponseNegative = "RIBd-ConnectionResponseNegative";
const char* SIG_RIBD_ConnectionRequest          = "RIBd-ConnectionRequest";
const char* SIG_RIBD_CACESend                   = "RIBd-CACEDataSend";

const char* SIG_ENROLLMENT_DataSend             = "Enrollment-DataSend";
const char* SIG_ENROLLMENT_CACEDataSend         = "Enrollment-CACEDataSend";
const char* SIG_ENROLLMENT_StartEnrollmentRequest = "Enrollment-StartEnrollmentRequest";
const char* SIG_ENROLLMENT_StartEnrollmentResponse = "Enrollment-StartEnrollmentResponse";
const char* SIG_ENROLLMENT_StopEnrollmentRequest = "Enrollment-StopEnrollmentRequest";
const char* SIG_ENROLLMENT_StopEnrollmentResponse = "Enrollment-StopEnrollmentResponse";
const char* SIG_ENROLLMENT_StartOperationRequest = "Enrollment-StartOperationRequest";
const char* SIG_ENROLLMENT_StartOperationResponse = "Enrollment-StartOperationResponse";
const char* SIG_ENROLLMENT_Finished      = "Enrollment-Finished";

const char* SIG_CDAP_DateReceive                = "CDAP-DataReceive";
const char* SIG_CDAP_SendData                   = "CDAP-SendData";

const char* SIG_CACE_DataReceive                = "CACE-DataReceive";

const char* SIG_IRM_AllocateRequest             = "IRM-AllocateRequest";
const char* SIG_IRM_DeallocateRequest           = "IRM-DeallocateRequest";
const char* SIG_IRM_AllocateResponsePositive    = "IRM-AllocateResponsePositive";
const char* SIG_IRM_AllocateResponseNegative    = "IRM-AllocateResponseNegative";

const char* SIG_AERIBD_AllocateResponsePositive = "AEorRIBd-AllocateResponsePositive";
const char* SIG_AERIBD_AllocateResponseNegative = "AEorRIBd-AllocateResponseNegative";

const char* SIG_FA_CreateFlowResponseNegative   = "FA-CreateFlowResponseNegative";
const char* SIG_FA_CreateFlowResponsePositive   = "FA-CreateFlowResponsePositive";
const char* SIG_FA_CreateFlowRequestForward     = "FA-CreateFlowRequestForward";
const char* SIG_FA_CreateFlowResponseForward    = "FA-CreateFlowResponseForward";
const char* SIG_FA_AllocateResponsePositive     = "FA-AllocateResponsePositive";
const char* SIG_FA_AllocateResponseNegative     = "FA-AllocateResponseNegative";

const char* SIG_toFAI_AllocateRequest           = "toFAI-AllocateRequest";
const char* SIG_toFAI_AllocateResponsePositive  = "toFAI-AllocateResponsePositive";
const char* SIG_toFAI_AllocateResponseNegative  = "toFAI-AllocateResponseNegative";
const char* SIG_FAI_AllocateRequest             = "FAI-AllocateRequest";
const char* SIG_FA_MgmtFlowAllocated    = "FAI-AllocateFinishManagement";
const char* SIG_FAI_DeallocateRequest           = "FAI-DeallocateRequest";
const char* SIG_FAI_DeallocateResponse          = "FAI-DeallocateResponse";
const char* SIG_FAI_AllocateResponsePositive    = "FAI-AllocateResponsePositive";
const char* SIG_FAI_AllocateResponseNegative    = "FAI-AllocateResponseNegative";
const char* SIG_FAI_CreateFlowRequest           = "FAI-CreateFlowRequest";
const char* SIG_FAI_DeleteFlowRequest           = "FAI-DeleteFlowRequest";
const char* SIG_FAI_CreateFlowResponsePositive  = "FAI-CreateFlowResponsePositive";
const char* SIG_FAI_CreateFlowResponseNegative  = "FAI-CreateFlowResponseNegative";
const char* SIG_FAI_DeleteFlowResponse          = "FAI-DeleteFlowResponse";

const char* SIG_RA_CreateFlowPositive           = "RA-CreateFlowPositive";
const char* SIG_RA_CreateFlowNegative           = "RA-CreateFlowNegative";
const char* SIG_RA_InvokeSlowdown               = "RA-InvokeSlowdown";
const char* SIG_RA_ExecuteSlowdown              = "RA-ExecuteSlowdown";
const char* SIG_RA_MgmtFlowAllocated            = "RA-MgmtFlowAllocated";
const char* SIG_RA_MgmtFlowDeallocated          = "RA-MgmtFlowDellocated";

const char* SIG_RIB_CreateRequestFlow           = "RIB-CreateRequestFlow";
const char* SIG_RIB_CreateResponseFlow          = "RIB-CreateResponseFlow";
const char* SIG_RIB_DeleteRequestFlow           = "RIB-DeleteRequestFlow";
const char* SIG_RIB_DeleteResponseFlow          = "RIB-DeleteResponseFlow";

const char* SIG_RMT_NoConnId                    = "RMT-NoConnId";
const char* SIG_RMT_ErrornousPacket             = "RMT-ErrornousPacket";
const char* SIG_RMT_SlowdownRequest             = "RMT-SlowDownRequest";
const char* SIG_RMT_QueuePDUPreRcvd             = "RMT-QueuePDUPreRcvd";
const char* SIG_RMT_QueuePDUPostRcvd            = "RMT-QueuePDUPostRcvd";
const char* SIG_RMT_QueuePDUPreSend             = "RMT-QueuePDUPreSend";
const char* SIG_RMT_QueuePDUSent                = "RMT-QueuePDUSent";
const char* SIG_RMT_PortReadyToServe            = "RMT-PortReadyToServe";
const char* SIG_RMT_PortReadyForRead            = "RMT-PortReadyForRead";


const char* SIG_PDUFTG_FwdInfoUpdate            = "PDUFTG-ForwardingInfoUpdate";
const char* SIG_RIBD_RoutingUpdate              = "Routing-Update";

const char* SIG_EFCP_StopSending                = "EFCP-StopSending";
const char* SIG_EFCP_StartSending               = "EFCP-StartSending";

