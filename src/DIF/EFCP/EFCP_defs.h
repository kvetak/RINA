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
 * @file EFCP_defs.h
 * @author Marcel Marek
 * @date Apr 28, 2014
 * @brief
 * @detail
 */

#ifndef EFCP_H_
#define EFCP_H_
//TODO B1 Make const char of most of them

#define QOSIDLENGTH 8
#define PORTIDLENGTH 8
#define CEPIDLENGTH 16
#define SEQNUMLENGTH 64

#define MAXSDUSIZE  1500 //made up
#define MAX_PDU_SIZE  1500 //made up

#define MAX_CLOSED_WIN_Q_LEN 20
#define DTP_EPSILON 0.0001
#define INITIAL_SENDER_CREDIT 10

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

#define SND_FC_OVERRUN_POLICY_PREFIX "rina.policies.DIF.EFCP.DTCP.FCOverrun."
#define SND_FC_OVERRUN_POLICY_NAME "fcOverrunPolicy"

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



#endif /* EFCP_H_ */
