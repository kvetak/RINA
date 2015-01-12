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
 * @file EFCP.h
 * @author Marcel Marek
 * @date Apr 28, 2014
 * @brief
 * @detail
 */

#ifndef EFCP_H_
#define EFCP_H_

#define QOSIDLENGTH 8
#define PORTIDLENGTH 8
#define CEPIDLENGTH 16
#define SEQNUMLENGTH 64

#define MAXSDUSIZE  1500 //made up
#define MAX_PDU_SIZE  1500 //made up
#define DRF_FLAG 0x80
#define ECN_FLAG 0x01
#define MAX_CLOSED_WIN_Q_LEN 20
#define MPL_TIME 20

#define ECN_POLICY_PREFIX "rina.DIF.EFCP.policies.ECN."
#define ECN_POLICY_NAME "ecnPolicy"

#define RCVR_FC_POLICY_PREFIX "rina.DIF.EFCP.policies.RcvrFC."
#define RCVR_FC_POLICY_NAME "rcvrFCPolicy"

#define RCVR_ACK_POLICY_PREFIX "rina.DIF.EFCP.policies.RcvrAck."
#define RCVR_ACK_POLICY_NAME "rcvrAckPolicy"

#define RECEIVING_FC_POLICY_PREFIX "rina.DIF.EFCP.policies.ReceivingFC."
#define RECEIVING_FC_POLICY_NAME "receivingFCPolicy"

#define SENDING_ACK_POLICY_PREFIX "rina.DIF.EFCP.policies.SendingAck."
#define SENDING_ACK_POLICY_NAME "sendingAckPolicy"

#define LOST_CONTROL_PDU_POLICY_PREFIX "rina.DIF.EFCP.policies.LostControlPDU."
#define LOST_CONTROL_PDU_POLICY_NAME "lostControlPDUPolicy"

#define RCVR_CONTROL_ACK_POLICY_PREFIX "rina.DIF.EFCP.policies.RcvrControlAck."
#define RCVR_CONTROL_ACK_POLICY_NAME "rcvrControlAckPolicy"

#define SENDER_ACK_POLICY_PREFIX "rina.DIF.EFCP.policies.SenderAck."
#define SENDER_ACK_POLICY_NAME "senderAckPolicy"

#define FC_OVERRUN_POLICY_PREFIX "rina.DIF.EFCP.policies.FCOverrun."
#define FC_OVERRUN_POLICY_NAME "fcOverrunPolicy"

#define NO_OVERRIDE_PEAK_POLICY_PREFIX "rina.DIF.EFCP.policies.NoOverridePeak."
#define NO_OVERRIDE_PEAK_POLICY_NAME "noOverridePeakPolicy"

#define TX_CONTROL_POLICY_PREFIX "rina.DIF.EFCP.policies.TxControl."
#define TX_CONTROL_POLICY_NAME "txControlPolicy"

#define NO_RATE_SLOW_DOWN_POLICY_PREFIX "rina.DIF.EFCP.policies.NoRateSlowDown."
#define NO_RATE_SLOW_DOWN_POLICY_NAME "noRateSlowDownPolicy"

#define RECONCILE_FC_POLICY_PREFIX "rina.DIF.EFCP.policies.ReconcileFC."
#define RECONCILE_FC_POLICY_NAME "reconcileFCPolicy"

#define RATE_REDUCTION_POLICY_PREFIX "rina.DIF.EFCP.policies.RateReduction."
#define RATE_REDUCTION_POLICY_NAME "rateReductionPolicy"


#define RCVR_INACTIVITY_POLICY_PREFIX "rina.DIF.EFCP.policies.RcvrInactivity."
#define RCVR_INACTIVITY_POLICY_NAME "rcvrInactivityPolicy"

#define SENDER_INACTIVITY_POLICY_PREFIX "rina.DIF.EFCP.policies.SenderInactivity."
#define SENDER_INACTIVITY_POLICY_NAME "senderInactivityPolicy"

#define INITIAL_SEQ_NUM_POLICY_PREFIX "rina.DIF.EFCP.policies.InitialSeqNum."
#define INITIAL_SEQ_NUM_POLICY_NAME "initialSeqNumPolicy"



#endif /* EFCP_H_ */
