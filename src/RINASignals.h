/*
 * RINASignals.h
 *
 *  Created on: 21. 7. 2014
 *      Author: Mordeth
 */

#ifndef RINASIGNALS_H_
#define RINASIGNALS_H_

//IRM
extern const char* SIG_IRM_AllocateRequest;
extern const char* SIG_IRM_DeallocateRequest;
extern const char* SIG_IRM_AllocateResponsePositive;
extern const char* SIG_IRM_AllocateResponseNegative;

//FA
extern const char* SIG_FA_CreateFlowResponseNegative;
extern const char* SIG_FA_CreateFlowResponsePositive;
extern const char* SIG_FA_CreateFlowRequestForward;
extern const char* SIG_FA_AllocateResponsePositive;
extern const char* SIG_FA_AllocateResponseNegative;

//FAI
extern const char* SIG_toFAI_AllocateRequest;
extern const char* SIG_toFAI_AllocateResponsePositive;
extern const char* SIG_toFAI_AllocateResponseNegative;
extern const char* SIG_FAI_AllocateRequest;
extern const char* SIG_FAI_AllocateResponsePositive;
extern const char* SIG_FAI_AllocateResponseNegative;
extern const char* SIG_FAI_CreateFlowRequest;
extern const char* SIG_FAI_DeleteFlowRequest;
extern const char* SIG_FAI_CreateFlowResponsePositive;
extern const char* SIG_FAI_CreateFlowResponseNegative;
extern const char* SIG_FAI_DeleteFlowResponse;

#endif /* RINASIGNALS_H_ */
