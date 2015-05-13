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
#define DRF_FLAG 0x80
#define ECN_FLAG 0x01
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



#endif /* EFCP_H_ */
