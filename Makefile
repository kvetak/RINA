#
# OMNeT++/OMNEST Makefile for rina
#
# This file was generated with the command:
#  opp_makemake -f --deep -O out
#

# Name of target to be created (-o option)
TARGET = rina$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I. \
    -Iexamples \
    -Iexamples/AllNodes \
    -Iexamples/AllNodes/results \
    -Iexamples/BigRandNet \
    -Iexamples/BigRandNet/results \
    -Iexamples/CongestedNode \
    -Iexamples/CongestedNode2 \
    -Iexamples/DC \
    -Iexamples/DC/results \
    -Iexamples/ExtendedPingTwoCSsSimple \
    -Iexamples/ExtendedPingTwoCSsSimple/results \
    -Iexamples/FatTreeTopology \
    -Iexamples/FatTreeTopology/results \
    -Iexamples/FatTreeTopologyPref \
    -Iexamples/FatTreeTopologyPref/results \
    -Iexamples/SimpleRelay \
    -Iexamples/SimpleRelay/results \
    -Iexamples/SimpleRelayCongestion \
    -Iexamples/SimpleRelayCongestion/results \
    -Iexamples/SingleCS \
    -Iexamples/SingleCS/results \
    -Iexamples/SmallNetRouting \
    -Iexamples/SmallNetRouting/results \
    -Iexamples/SmallNetwork \
    -Iexamples/SmallNetwork/results \
    -Iexamples/SmallNetwork2 \
    -Iexamples/SmallNetwork2/results \
    -Iexamples/SmallRandNet \
    -Iexamples/SmallRandNet/results \
    -Iexamples/TreeCongestion \
    -Iexamples/TwoCSWithDelay \
    -Iexamples/TwoCSWithDelay/results \
    -Iexamples/TwoCSs \
    -Iexamples/TwoCSs/results \
    -Iexamples/TwoCSsSimple \
    -Iexamples/TwoCSsSimple/results \
    -Iexamples/TwoScheduling \
    -Iexamples/TwoScheduling9 \
    -Iexamples/randPrefNet \
    -Iexamples/randPrefNet/results \
    -Iexamples/treeBipart \
    -Iexamples/treeBipart/results \
    -Ipolicies \
    -Ipolicies/DAF \
    -Ipolicies/DIF \
    -Ipolicies/DIF/EFCP \
    -Ipolicies/DIF/EFCP/DTCP \
    -Ipolicies/DIF/EFCP/DTCP/ECN \
    -Ipolicies/DIF/EFCP/DTCP/ECNSlowDown \
    -Ipolicies/DIF/EFCP/DTCP/FCOverrun \
    -Ipolicies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyDefault \
    -Ipolicies/DIF/EFCP/DTCP/LostControlPDU \
    -Ipolicies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyDefault \
    -Ipolicies/DIF/EFCP/DTCP/NoOverridePeak \
    -Ipolicies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyDefault \
    -Ipolicies/DIF/EFCP/DTCP/NoRateSlowDown \
    -Ipolicies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyDefault \
    -Ipolicies/DIF/EFCP/DTCP/RateReduction \
    -Ipolicies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyDefault \
    -Ipolicies/DIF/EFCP/DTCP/RcvrAck \
    -Ipolicies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyDefault \
    -Ipolicies/DIF/EFCP/DTCP/RcvrControlAck \
    -Ipolicies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyDefault \
    -Ipolicies/DIF/EFCP/DTCP/RcvrFC \
    -Ipolicies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyDefault \
    -Ipolicies/DIF/EFCP/DTCP/ReceivingFC \
    -Ipolicies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyDefault \
    -Ipolicies/DIF/EFCP/DTCP/ReconcileFC \
    -Ipolicies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyDefault \
    -Ipolicies/DIF/EFCP/DTCP/RxTimerExpiry \
    -Ipolicies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyDefault \
    -Ipolicies/DIF/EFCP/DTCP/SenderAck \
    -Ipolicies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyDefault \
    -Ipolicies/DIF/EFCP/DTCP/SendingAck \
    -Ipolicies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyDefault \
    -Ipolicies/DIF/EFCP/DTCP/TxControl \
    -Ipolicies/DIF/EFCP/DTCP/TxControl/TxControlPolicyDefault \
    -Ipolicies/DIF/EFCP/DTP \
    -Ipolicies/DIF/EFCP/DTP/InitialSeqNum \
    -Ipolicies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyDefault \
    -Ipolicies/DIF/EFCP/DTP/RTTEstimator \
    -Ipolicies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyDefault \
    -Ipolicies/DIF/EFCP/DTP/RcvrInactivity \
    -Ipolicies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyDefault \
    -Ipolicies/DIF/EFCP/DTP/SenderInactivity \
    -Ipolicies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyDefault \
    -Ipolicies/DIF/FA \
    -Ipolicies/DIF/FA/AllocateRetry \
    -Ipolicies/DIF/FA/AllocateRetry/LimitedRetries \
    -Ipolicies/DIF/FA/NewFlowRequest \
    -Ipolicies/DIF/FA/NewFlowRequest/MinComparer \
    -Ipolicies/DIF/FA/NewFlowRequest/ScoreComparer \
    -Ipolicies/DIF/RA \
    -Ipolicies/DIF/RA/AddressComparator \
    -Ipolicies/DIF/RA/AddressComparator/ExactMatch \
    -Ipolicies/DIF/RA/AddressComparator/PrefixMatch \
    -Ipolicies/DIF/RA/PDUFG \
    -Ipolicies/DIF/RA/PDUFG/BiDomainGenerator \
    -Ipolicies/DIF/RA/PDUFG/QoSDomainGenerator \
    -Ipolicies/DIF/RA/PDUFG/SimpleGenerator \
    -Ipolicies/DIF/RA/PDUFG/SingleDomainGenerator \
    -Ipolicies/DIF/RA/PDUFG/StaticGenerator \
    -Ipolicies/DIF/RA/QueueAlloc \
    -Ipolicies/DIF/RA/QueueAlloc/QueuePerNCU \
    -Ipolicies/DIF/RA/QueueAlloc/QueuePerNFlow \
    -Ipolicies/DIF/RA/QueueAlloc/QueuePerNQoS \
    -Ipolicies/DIF/RA/QueueAlloc/SingleQueue \
    -Ipolicies/DIF/RA/QueueIDGen \
    -Ipolicies/DIF/RA/QueueIDGen/IDPerNCU \
    -Ipolicies/DIF/RA/QueueIDGen/IDPerNFlow \
    -Ipolicies/DIF/RA/QueueIDGen/IDPerNQoS \
    -Ipolicies/DIF/RA/QueueIDGen/SingleID \
    -Ipolicies/DIF/RMT \
    -Ipolicies/DIF/RMT/MaxQueue \
    -Ipolicies/DIF/RMT/MaxQueue/DumbMaxQ \
    -Ipolicies/DIF/RMT/MaxQueue/ECNMarker \
    -Ipolicies/DIF/RMT/MaxQueue/PortMaxQ \
    -Ipolicies/DIF/RMT/MaxQueue/REDDropper \
    -Ipolicies/DIF/RMT/MaxQueue/ReadRateReducer \
    -Ipolicies/DIF/RMT/MaxQueue/TailDrop \
    -Ipolicies/DIF/RMT/MaxQueue/UpstreamNotifier \
    -Ipolicies/DIF/RMT/Monitor \
    -Ipolicies/DIF/RMT/Monitor/BEMonitor \
    -Ipolicies/DIF/RMT/Monitor/DLMonitor \
    -Ipolicies/DIF/RMT/Monitor/REDMonitor \
    -Ipolicies/DIF/RMT/Monitor/SimpleMonitor \
    -Ipolicies/DIF/RMT/Monitor/SmartMonitor \
    -Ipolicies/DIF/RMT/Monitor/eDLMonitor \
    -Ipolicies/DIF/RMT/PDUForwarding \
    -Ipolicies/DIF/RMT/PDUForwarding/DomainTable \
    -Ipolicies/DIF/RMT/PDUForwarding/MiniTable \
    -Ipolicies/DIF/RMT/PDUForwarding/QoSTable \
    -Ipolicies/DIF/RMT/PDUForwarding/SimpleTable \
    -Ipolicies/DIF/RMT/Scheduler \
    -Ipolicies/DIF/RMT/Scheduler/DumbSch \
    -Ipolicies/DIF/RMT/Scheduler/LongestQFirst \
    -Ipolicies/DIF/Routing \
    -Ipolicies/DIF/Routing/DomainRouting \
    -Ipolicies/DIF/Routing/DomainRouting/DV \
    -Ipolicies/DIF/Routing/DomainRouting/LS \
    -Ipolicies/DIF/Routing/DummyRouting \
    -Ipolicies/DIF/Routing/SimpleRouting \
    -Ipolicies/DIF/Routing/SimpleRouting/SimpleDV \
    -Ipolicies/DIF/Routing/SimpleRouting/SimpleLS \
    -Iscripts \
    -Isrc \
    -Isrc/CS \
    -Isrc/Common \
    -Isrc/DAF \
    -Isrc/DAF/AE \
    -Isrc/DAF/CDAP \
    -Isrc/DAF/DA \
    -Isrc/DAF/IRM \
    -Isrc/DIF \
    -Isrc/DIF/Delimiting \
    -Isrc/DIF/EFCP \
    -Isrc/DIF/EFCP/DTCP \
    -Isrc/DIF/EFCP/DTP \
    -Isrc/DIF/EFCP/EFCPTable \
    -Isrc/DIF/EFCP/EFCPTable/DTP \
    -Isrc/DIF/Enrollment \
    -Isrc/DIF/FA \
    -Isrc/DIF/NSM \
    -Isrc/DIF/RA \
    -Isrc/DIF/RIB \
    -Isrc/DIF/RMT

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS =

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/policies/DIF/EFCP/EFCPPolicy.o \
    $O/policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyDefault.o \
    $O/policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyDefault/FCOverrunPolicyDefault.o \
    $O/policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyDefault/LostControlPDUPolicyDefault.o \
    $O/policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyDefault/NoOverridePeakPolicyDefault.o \
    $O/policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyDefault/NoRateSlowDownPolicyDefault.o \
    $O/policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyDefault/RateReductionPolicyDefault.o \
    $O/policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyDefault/RcvrAckPolicyDefault.o \
    $O/policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyDefault/RcvrControlAckPolicyDefault.o \
    $O/policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyDefault/RcvrFCPolicyDefault.o \
    $O/policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyDefault/ReceivingFCPolicyDefault.o \
    $O/policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyDefault/ReconcileFCPolicyDefault.o \
    $O/policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyDefault/RxTimerExpiryPolicyDefault.o \
    $O/policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyDefault/SenderAckPolicyDefault.o \
    $O/policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyDefault/SendingAckPolicyDefault.o \
    $O/policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyDefault/TxControlPolicyDefault.o \
    $O/policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyBase.o \
    $O/policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyDefault/InitialSeqNumPolicyDefault.o \
    $O/policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyBase.o \
    $O/policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyDefault/RTTEstimatorPolicyDefault.o \
    $O/policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyBase.o \
    $O/policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyDefault/RcvrInactivityPolicyDefault.o \
    $O/policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyBase.o \
    $O/policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyDefault/SenderInactivityPolicyDefault.o \
    $O/policies/DIF/FA/AllocateRetry/AllocateRetryBase.o \
    $O/policies/DIF/FA/AllocateRetry/LimitedRetries/LimitedRetries.o \
    $O/policies/DIF/FA/NewFlowRequest/NewFlowRequestBase.o \
    $O/policies/DIF/FA/NewFlowRequest/MinComparer/MinComparer.o \
    $O/policies/DIF/FA/NewFlowRequest/ScoreComparer/ScoreComparer.o \
    $O/policies/DIF/RA/AddressComparator/AddressComparatorBase.o \
    $O/policies/DIF/RA/AddressComparator/ExactMatch/ExactMatch.o \
    $O/policies/DIF/RA/AddressComparator/PrefixMatch/PrefixMatch.o \
    $O/policies/DIF/RA/PDUFG/IntBbPDUFG.o \
    $O/policies/DIF/RA/PDUFG/IntPDUFG.o \
    $O/policies/DIF/RA/PDUFG/PDUFGNeighbor.o \
    $O/policies/DIF/RA/PDUFG/BiDomainGenerator/BiDomainGenerator.o \
    $O/policies/DIF/RA/PDUFG/QoSDomainGenerator/QoSDomainGenerator.o \
    $O/policies/DIF/RA/PDUFG/SimpleGenerator/SimpleGenerator.o \
    $O/policies/DIF/RA/PDUFG/SingleDomainGenerator/SingleDomainGenerator.o \
    $O/policies/DIF/RA/PDUFG/StaticGenerator/StaticGenerator.o \
    $O/policies/DIF/RA/QueueAlloc/QueueAllocBase.o \
    $O/policies/DIF/RA/QueueAlloc/QueuePerNCU/QueuePerNCU.o \
    $O/policies/DIF/RA/QueueAlloc/QueuePerNFlow/QueuePerNFlow.o \
    $O/policies/DIF/RA/QueueAlloc/QueuePerNQoS/QueuePerNQoS.o \
    $O/policies/DIF/RA/QueueAlloc/SingleQueue/SingleQueue.o \
    $O/policies/DIF/RA/QueueIDGen/QueueIDGenBase.o \
    $O/policies/DIF/RA/QueueIDGen/IDPerNCU/IDPerNCU.o \
    $O/policies/DIF/RA/QueueIDGen/IDPerNFlow/IDPerNFlow.o \
    $O/policies/DIF/RA/QueueIDGen/IDPerNQoS/IDPerNQoS.o \
    $O/policies/DIF/RA/QueueIDGen/SingleID/SingleID.o \
    $O/policies/DIF/RMT/MaxQueue/RMTMaxQBase.o \
    $O/policies/DIF/RMT/MaxQueue/DumbMaxQ/DumbMaxQ.o \
    $O/policies/DIF/RMT/MaxQueue/ECNMarker/ECNMarker.o \
    $O/policies/DIF/RMT/MaxQueue/PortMaxQ/PortMaxQ.o \
    $O/policies/DIF/RMT/MaxQueue/REDDropper/REDDropper.o \
    $O/policies/DIF/RMT/MaxQueue/ReadRateReducer/ReadRateReducer.o \
    $O/policies/DIF/RMT/MaxQueue/TailDrop/TailDrop.o \
    $O/policies/DIF/RMT/MaxQueue/UpstreamNotifier/UpstreamNotifier.o \
    $O/policies/DIF/RMT/Monitor/RMTQMonitorBase.o \
    $O/policies/DIF/RMT/Monitor/BEMonitor/BEMonitor.o \
    $O/policies/DIF/RMT/Monitor/DLMonitor/DLMonitor.o \
    $O/policies/DIF/RMT/Monitor/REDMonitor/REDMonitor.o \
    $O/policies/DIF/RMT/Monitor/SimpleMonitor/SimpleMonitor.o \
    $O/policies/DIF/RMT/Monitor/eDLMonitor/eDLMonitor.o \
    $O/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.o \
    $O/policies/DIF/RMT/PDUForwarding/DomainTable/DomainTable.o \
    $O/policies/DIF/RMT/PDUForwarding/MiniTable/MiniTable.o \
    $O/policies/DIF/RMT/PDUForwarding/QoSTable/QoSTable.o \
    $O/policies/DIF/RMT/PDUForwarding/SimpleTable/SimpleTable.o \
    $O/policies/DIF/RMT/Scheduler/RMTSchedulingBase.o \
    $O/policies/DIF/RMT/Scheduler/DumbSch/DumbSch.o \
    $O/policies/DIF/RMT/Scheduler/LongestQFirst/LongestQFirst.o \
    $O/policies/DIF/Routing/IntBbRouting.o \
    $O/policies/DIF/Routing/IntRouting.o \
    $O/policies/DIF/Routing/IntRoutingUpdate.o \
    $O/policies/DIF/Routing/DomainRouting/rModule.o \
    $O/policies/DIF/Routing/DomainRouting/Routing.o \
    $O/policies/DIF/Routing/DomainRouting/DV/DV.o \
    $O/policies/DIF/Routing/DomainRouting/LS/LS.o \
    $O/policies/DIF/Routing/DummyRouting/DummyRouting.o \
    $O/policies/DIF/Routing/SimpleRouting/SimpleDV/SimpleDV.o \
    $O/policies/DIF/Routing/SimpleRouting/SimpleLS/SimpleLS.o \
    $O/src/Common/Address.o \
    $O/src/Common/APN.o \
    $O/src/Common/APNamingInfo.o \
    $O/src/Common/CongestionDescriptor.o \
    $O/src/Common/ConnectionId.o \
    $O/src/Common/DAP.o \
    $O/src/Common/Data.o \
    $O/src/Common/ExternConsts.o \
    $O/src/Common/Flow.o \
    $O/src/Common/ModuleAccess.o \
    $O/src/Common/PDU.o \
    $O/src/Common/Policy.o \
    $O/src/Common/QoSCube.o \
    $O/src/Common/QoSReq.o \
    $O/src/Common/RINASignals.o \
    $O/src/Common/SDU.o \
    $O/src/Common/SHA256.o \
    $O/src/Common/Test.o \
    $O/src/Common/Utils.o \
    $O/src/DAF/AE/AE.o \
    $O/src/DAF/AE/AEBase.o \
    $O/src/DAF/AE/AEExtendedPing.o \
    $O/src/DAF/AE/AEListeners.o \
    $O/src/DAF/AE/AEPing.o \
    $O/src/DAF/AE/AESender.o \
    $O/src/DAF/AE/AEStream.o \
    $O/src/DAF/CDAP/Auth.o \
    $O/src/DAF/CDAP/AuthListeners.o \
    $O/src/DAF/CDAP/CACE.o \
    $O/src/DAF/CDAP/CACEListeners.o \
    $O/src/DAF/CDAP/CDAP.o \
    $O/src/DAF/CDAP/CDAPListeners.o \
    $O/src/DAF/CDAP/CDAPMsgLog.o \
    $O/src/DAF/CDAP/CDAPMsgLogEntry.o \
    $O/src/DAF/CDAP/CDAPSplitter.o \
    $O/src/DAF/DA/DA.o \
    $O/src/DAF/DA/Directory.o \
    $O/src/DAF/DA/DirectoryEntry.o \
    $O/src/DAF/DA/NamingInformation.o \
    $O/src/DAF/DA/NamingInformationEntry.o \
    $O/src/DAF/DA/NeighborTable.o \
    $O/src/DAF/DA/NeighborTableEntry.o \
    $O/src/DAF/DA/SearchTable.o \
    $O/src/DAF/DA/SearchTableEntry.o \
    $O/src/DAF/IRM/ConnectionTable.o \
    $O/src/DAF/IRM/ConnectionTableEntry.o \
    $O/src/DAF/IRM/IRM.o \
    $O/src/DAF/IRM/IRMListeners.o \
    $O/src/DIF/Delimiting/Delimiting.o \
    $O/src/DIF/EFCP/EFCP.o \
    $O/src/DIF/EFCP/EFCPInstance.o \
    $O/src/DIF/EFCP/EFCPListeners.o \
    $O/src/DIF/EFCP/EFCPPolicySet.o \
    $O/src/DIF/EFCP/DTCP/DTCP.o \
    $O/src/DIF/EFCP/DTCP/DTCPState.o \
    $O/src/DIF/EFCP/DTCP/RXControl.o \
    $O/src/DIF/EFCP/DTP/DataTransferPDU.o \
    $O/src/DIF/EFCP/DTP/DTP.o \
    $O/src/DIF/EFCP/DTP/DTPState.o \
    $O/src/DIF/EFCP/DTP/DumbGate.o \
    $O/src/DIF/EFCP/DTP/PushBackChannel.o \
    $O/src/DIF/EFCP/DTP/UserDataField.o \
    $O/src/DIF/EFCP/EFCPTable/EFCPTable.o \
    $O/src/DIF/EFCP/EFCPTable/EFCPTableEntry.o \
    $O/src/DIF/Enrollment/Enrollment.o \
    $O/src/DIF/FA/FA.o \
    $O/src/DIF/FA/FABase.o \
    $O/src/DIF/FA/FAI.o \
    $O/src/DIF/FA/FAIBase.o \
    $O/src/DIF/FA/FAIListeners.o \
    $O/src/DIF/FA/FAITable.o \
    $O/src/DIF/FA/FAITableEntry.o \
    $O/src/DIF/FA/FAListeners.o \
    $O/src/DIF/NSM/DirectoryForwardingTable.o \
    $O/src/DIF/NSM/LocalDirectoryCache.o \
    $O/src/DIF/NSM/NSM.o \
    $O/src/DIF/RA/NM1FlowTable.o \
    $O/src/DIF/RA/NM1FlowTableItem.o \
    $O/src/DIF/RA/RA.o \
    $O/src/DIF/RA/RABase.o \
    $O/src/DIF/RA/RAListeners.o \
    $O/src/DIF/RIB/RIBd.o \
    $O/src/DIF/RIB/RIBdBase.o \
    $O/src/DIF/RIB/RIBdListeners.o \
    $O/src/DIF/RMT/RMT.o \
    $O/src/DIF/RMT/RMTBase.o \
    $O/src/DIF/RMT/RMTListeners.o \
    $O/src/DIF/RMT/RMTModuleAllocator.o \
    $O/src/DIF/RMT/RMTPort.o \
    $O/src/DIF/RMT/RMTQueue.o \
    $O/src/Common/Data_m.o \
    $O/src/Common/PDU_m.o \
    $O/src/Common/SDU_m.o \
    $O/src/DAF/CDAP/CDAPMessage_m.o \
    $O/src/DIF/EFCP/DTCP/ControlPDU_m.o \
    $O/src/DIF/EFCP/DTCP/DTCPTimers_m.o \
    $O/src/DIF/EFCP/DTP/DataTransferPDU_m.o \
    $O/src/DIF/EFCP/DTP/DTPTimers_m.o

# Message files
MSGFILES = \
    src/Common/Data.msg \
    src/Common/PDU.msg \
    src/Common/SDU.msg \
    src/DAF/CDAP/CDAPMessage.msg \
    src/DIF/EFCP/DTCP/ControlPDU.msg \
    src/DIF/EFCP/DTCP/DTCPTimers.msg \
    src/DIF/EFCP/DTP/DataTransferPDU.msg \
    src/DIF/EFCP/DTP/DTPTimers.msg

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)echo >.tmp$$$$ $(OBJS) $(EXTRA_OBJS) && $(AR) .tmplib$$$$ @.tmp$$$$ && $(CXX) -o $O/$(TARGET) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) .tmplib$$$$ $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS) $(LDFLAGS) && rm .tmp$$$$ && rm .tmplib$$$$

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f rina rina.exe librina.so librina.a librina.dll librina.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f examples/*_m.cc examples/*_m.h
	$(Q)-rm -f examples/AllNodes/*_m.cc examples/AllNodes/*_m.h
	$(Q)-rm -f examples/AllNodes/results/*_m.cc examples/AllNodes/results/*_m.h
	$(Q)-rm -f examples/BigRandNet/*_m.cc examples/BigRandNet/*_m.h
	$(Q)-rm -f examples/BigRandNet/results/*_m.cc examples/BigRandNet/results/*_m.h
	$(Q)-rm -f examples/CongestedNode/*_m.cc examples/CongestedNode/*_m.h
	$(Q)-rm -f examples/CongestedNode2/*_m.cc examples/CongestedNode2/*_m.h
	$(Q)-rm -f examples/DC/*_m.cc examples/DC/*_m.h
	$(Q)-rm -f examples/DC/results/*_m.cc examples/DC/results/*_m.h
	$(Q)-rm -f examples/ExtendedPingTwoCSsSimple/*_m.cc examples/ExtendedPingTwoCSsSimple/*_m.h
	$(Q)-rm -f examples/ExtendedPingTwoCSsSimple/results/*_m.cc examples/ExtendedPingTwoCSsSimple/results/*_m.h
	$(Q)-rm -f examples/FatTreeTopology/*_m.cc examples/FatTreeTopology/*_m.h
	$(Q)-rm -f examples/FatTreeTopology/results/*_m.cc examples/FatTreeTopology/results/*_m.h
	$(Q)-rm -f examples/FatTreeTopologyPref/*_m.cc examples/FatTreeTopologyPref/*_m.h
	$(Q)-rm -f examples/FatTreeTopologyPref/results/*_m.cc examples/FatTreeTopologyPref/results/*_m.h
	$(Q)-rm -f examples/SimpleRelay/*_m.cc examples/SimpleRelay/*_m.h
	$(Q)-rm -f examples/SimpleRelay/results/*_m.cc examples/SimpleRelay/results/*_m.h
	$(Q)-rm -f examples/SimpleRelayCongestion/*_m.cc examples/SimpleRelayCongestion/*_m.h
	$(Q)-rm -f examples/SimpleRelayCongestion/results/*_m.cc examples/SimpleRelayCongestion/results/*_m.h
	$(Q)-rm -f examples/SingleCS/*_m.cc examples/SingleCS/*_m.h
	$(Q)-rm -f examples/SingleCS/results/*_m.cc examples/SingleCS/results/*_m.h
	$(Q)-rm -f examples/SmallNetRouting/*_m.cc examples/SmallNetRouting/*_m.h
	$(Q)-rm -f examples/SmallNetRouting/results/*_m.cc examples/SmallNetRouting/results/*_m.h
	$(Q)-rm -f examples/SmallNetwork/*_m.cc examples/SmallNetwork/*_m.h
	$(Q)-rm -f examples/SmallNetwork/results/*_m.cc examples/SmallNetwork/results/*_m.h
	$(Q)-rm -f examples/SmallNetwork2/*_m.cc examples/SmallNetwork2/*_m.h
	$(Q)-rm -f examples/SmallNetwork2/results/*_m.cc examples/SmallNetwork2/results/*_m.h
	$(Q)-rm -f examples/SmallRandNet/*_m.cc examples/SmallRandNet/*_m.h
	$(Q)-rm -f examples/SmallRandNet/results/*_m.cc examples/SmallRandNet/results/*_m.h
	$(Q)-rm -f examples/TreeCongestion/*_m.cc examples/TreeCongestion/*_m.h
	$(Q)-rm -f examples/TwoCSWithDelay/*_m.cc examples/TwoCSWithDelay/*_m.h
	$(Q)-rm -f examples/TwoCSWithDelay/results/*_m.cc examples/TwoCSWithDelay/results/*_m.h
	$(Q)-rm -f examples/TwoCSs/*_m.cc examples/TwoCSs/*_m.h
	$(Q)-rm -f examples/TwoCSs/results/*_m.cc examples/TwoCSs/results/*_m.h
	$(Q)-rm -f examples/TwoCSsSimple/*_m.cc examples/TwoCSsSimple/*_m.h
	$(Q)-rm -f examples/TwoCSsSimple/results/*_m.cc examples/TwoCSsSimple/results/*_m.h
	$(Q)-rm -f examples/TwoScheduling/*_m.cc examples/TwoScheduling/*_m.h
	$(Q)-rm -f examples/TwoScheduling9/*_m.cc examples/TwoScheduling9/*_m.h
	$(Q)-rm -f examples/randPrefNet/*_m.cc examples/randPrefNet/*_m.h
	$(Q)-rm -f examples/randPrefNet/results/*_m.cc examples/randPrefNet/results/*_m.h
	$(Q)-rm -f examples/treeBipart/*_m.cc examples/treeBipart/*_m.h
	$(Q)-rm -f examples/treeBipart/results/*_m.cc examples/treeBipart/results/*_m.h
	$(Q)-rm -f policies/*_m.cc policies/*_m.h
	$(Q)-rm -f policies/DAF/*_m.cc policies/DAF/*_m.h
	$(Q)-rm -f policies/DIF/*_m.cc policies/DIF/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/*_m.cc policies/DIF/EFCP/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/*_m.cc policies/DIF/EFCP/DTCP/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/ECN/*_m.cc policies/DIF/EFCP/DTCP/ECN/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/ECNSlowDown/*_m.cc policies/DIF/EFCP/DTCP/ECNSlowDown/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/FCOverrun/*_m.cc policies/DIF/EFCP/DTCP/FCOverrun/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyDefault/*_m.cc policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyDefault/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/LostControlPDU/*_m.cc policies/DIF/EFCP/DTCP/LostControlPDU/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyDefault/*_m.cc policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyDefault/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/NoOverridePeak/*_m.cc policies/DIF/EFCP/DTCP/NoOverridePeak/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyDefault/*_m.cc policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyDefault/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/NoRateSlowDown/*_m.cc policies/DIF/EFCP/DTCP/NoRateSlowDown/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyDefault/*_m.cc policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyDefault/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/RateReduction/*_m.cc policies/DIF/EFCP/DTCP/RateReduction/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyDefault/*_m.cc policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyDefault/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/RcvrAck/*_m.cc policies/DIF/EFCP/DTCP/RcvrAck/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyDefault/*_m.cc policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyDefault/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/RcvrControlAck/*_m.cc policies/DIF/EFCP/DTCP/RcvrControlAck/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyDefault/*_m.cc policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyDefault/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/RcvrFC/*_m.cc policies/DIF/EFCP/DTCP/RcvrFC/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyDefault/*_m.cc policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyDefault/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/ReceivingFC/*_m.cc policies/DIF/EFCP/DTCP/ReceivingFC/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyDefault/*_m.cc policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyDefault/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/ReconcileFC/*_m.cc policies/DIF/EFCP/DTCP/ReconcileFC/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyDefault/*_m.cc policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyDefault/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/RxTimerExpiry/*_m.cc policies/DIF/EFCP/DTCP/RxTimerExpiry/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyDefault/*_m.cc policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyDefault/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/SenderAck/*_m.cc policies/DIF/EFCP/DTCP/SenderAck/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyDefault/*_m.cc policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyDefault/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/SendingAck/*_m.cc policies/DIF/EFCP/DTCP/SendingAck/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyDefault/*_m.cc policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyDefault/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/TxControl/*_m.cc policies/DIF/EFCP/DTCP/TxControl/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyDefault/*_m.cc policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyDefault/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTP/*_m.cc policies/DIF/EFCP/DTP/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTP/InitialSeqNum/*_m.cc policies/DIF/EFCP/DTP/InitialSeqNum/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyDefault/*_m.cc policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyDefault/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTP/RTTEstimator/*_m.cc policies/DIF/EFCP/DTP/RTTEstimator/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyDefault/*_m.cc policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyDefault/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTP/RcvrInactivity/*_m.cc policies/DIF/EFCP/DTP/RcvrInactivity/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyDefault/*_m.cc policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyDefault/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTP/SenderInactivity/*_m.cc policies/DIF/EFCP/DTP/SenderInactivity/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyDefault/*_m.cc policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyDefault/*_m.h
	$(Q)-rm -f policies/DIF/FA/*_m.cc policies/DIF/FA/*_m.h
	$(Q)-rm -f policies/DIF/FA/AllocateRetry/*_m.cc policies/DIF/FA/AllocateRetry/*_m.h
	$(Q)-rm -f policies/DIF/FA/AllocateRetry/LimitedRetries/*_m.cc policies/DIF/FA/AllocateRetry/LimitedRetries/*_m.h
	$(Q)-rm -f policies/DIF/FA/NewFlowRequest/*_m.cc policies/DIF/FA/NewFlowRequest/*_m.h
	$(Q)-rm -f policies/DIF/FA/NewFlowRequest/MinComparer/*_m.cc policies/DIF/FA/NewFlowRequest/MinComparer/*_m.h
	$(Q)-rm -f policies/DIF/FA/NewFlowRequest/ScoreComparer/*_m.cc policies/DIF/FA/NewFlowRequest/ScoreComparer/*_m.h
	$(Q)-rm -f policies/DIF/RA/*_m.cc policies/DIF/RA/*_m.h
	$(Q)-rm -f policies/DIF/RA/AddressComparator/*_m.cc policies/DIF/RA/AddressComparator/*_m.h
	$(Q)-rm -f policies/DIF/RA/AddressComparator/ExactMatch/*_m.cc policies/DIF/RA/AddressComparator/ExactMatch/*_m.h
	$(Q)-rm -f policies/DIF/RA/AddressComparator/PrefixMatch/*_m.cc policies/DIF/RA/AddressComparator/PrefixMatch/*_m.h
	$(Q)-rm -f policies/DIF/RA/PDUFG/*_m.cc policies/DIF/RA/PDUFG/*_m.h
	$(Q)-rm -f policies/DIF/RA/PDUFG/BiDomainGenerator/*_m.cc policies/DIF/RA/PDUFG/BiDomainGenerator/*_m.h
	$(Q)-rm -f policies/DIF/RA/PDUFG/QoSDomainGenerator/*_m.cc policies/DIF/RA/PDUFG/QoSDomainGenerator/*_m.h
	$(Q)-rm -f policies/DIF/RA/PDUFG/SimpleGenerator/*_m.cc policies/DIF/RA/PDUFG/SimpleGenerator/*_m.h
	$(Q)-rm -f policies/DIF/RA/PDUFG/SingleDomainGenerator/*_m.cc policies/DIF/RA/PDUFG/SingleDomainGenerator/*_m.h
	$(Q)-rm -f policies/DIF/RA/PDUFG/StaticGenerator/*_m.cc policies/DIF/RA/PDUFG/StaticGenerator/*_m.h
	$(Q)-rm -f policies/DIF/RA/QueueAlloc/*_m.cc policies/DIF/RA/QueueAlloc/*_m.h
	$(Q)-rm -f policies/DIF/RA/QueueAlloc/QueuePerNCU/*_m.cc policies/DIF/RA/QueueAlloc/QueuePerNCU/*_m.h
	$(Q)-rm -f policies/DIF/RA/QueueAlloc/QueuePerNFlow/*_m.cc policies/DIF/RA/QueueAlloc/QueuePerNFlow/*_m.h
	$(Q)-rm -f policies/DIF/RA/QueueAlloc/QueuePerNQoS/*_m.cc policies/DIF/RA/QueueAlloc/QueuePerNQoS/*_m.h
	$(Q)-rm -f policies/DIF/RA/QueueAlloc/SingleQueue/*_m.cc policies/DIF/RA/QueueAlloc/SingleQueue/*_m.h
	$(Q)-rm -f policies/DIF/RA/QueueIDGen/*_m.cc policies/DIF/RA/QueueIDGen/*_m.h
	$(Q)-rm -f policies/DIF/RA/QueueIDGen/IDPerNCU/*_m.cc policies/DIF/RA/QueueIDGen/IDPerNCU/*_m.h
	$(Q)-rm -f policies/DIF/RA/QueueIDGen/IDPerNFlow/*_m.cc policies/DIF/RA/QueueIDGen/IDPerNFlow/*_m.h
	$(Q)-rm -f policies/DIF/RA/QueueIDGen/IDPerNQoS/*_m.cc policies/DIF/RA/QueueIDGen/IDPerNQoS/*_m.h
	$(Q)-rm -f policies/DIF/RA/QueueIDGen/SingleID/*_m.cc policies/DIF/RA/QueueIDGen/SingleID/*_m.h
	$(Q)-rm -f policies/DIF/RMT/*_m.cc policies/DIF/RMT/*_m.h
	$(Q)-rm -f policies/DIF/RMT/MaxQueue/*_m.cc policies/DIF/RMT/MaxQueue/*_m.h
	$(Q)-rm -f policies/DIF/RMT/MaxQueue/DumbMaxQ/*_m.cc policies/DIF/RMT/MaxQueue/DumbMaxQ/*_m.h
	$(Q)-rm -f policies/DIF/RMT/MaxQueue/ECNMarker/*_m.cc policies/DIF/RMT/MaxQueue/ECNMarker/*_m.h
	$(Q)-rm -f policies/DIF/RMT/MaxQueue/PortMaxQ/*_m.cc policies/DIF/RMT/MaxQueue/PortMaxQ/*_m.h
	$(Q)-rm -f policies/DIF/RMT/MaxQueue/REDDropper/*_m.cc policies/DIF/RMT/MaxQueue/REDDropper/*_m.h
	$(Q)-rm -f policies/DIF/RMT/MaxQueue/ReadRateReducer/*_m.cc policies/DIF/RMT/MaxQueue/ReadRateReducer/*_m.h
	$(Q)-rm -f policies/DIF/RMT/MaxQueue/TailDrop/*_m.cc policies/DIF/RMT/MaxQueue/TailDrop/*_m.h
	$(Q)-rm -f policies/DIF/RMT/MaxQueue/UpstreamNotifier/*_m.cc policies/DIF/RMT/MaxQueue/UpstreamNotifier/*_m.h
	$(Q)-rm -f policies/DIF/RMT/Monitor/*_m.cc policies/DIF/RMT/Monitor/*_m.h
	$(Q)-rm -f policies/DIF/RMT/Monitor/BEMonitor/*_m.cc policies/DIF/RMT/Monitor/BEMonitor/*_m.h
	$(Q)-rm -f policies/DIF/RMT/Monitor/DLMonitor/*_m.cc policies/DIF/RMT/Monitor/DLMonitor/*_m.h
	$(Q)-rm -f policies/DIF/RMT/Monitor/REDMonitor/*_m.cc policies/DIF/RMT/Monitor/REDMonitor/*_m.h
	$(Q)-rm -f policies/DIF/RMT/Monitor/SimpleMonitor/*_m.cc policies/DIF/RMT/Monitor/SimpleMonitor/*_m.h
	$(Q)-rm -f policies/DIF/RMT/Monitor/SmartMonitor/*_m.cc policies/DIF/RMT/Monitor/SmartMonitor/*_m.h
	$(Q)-rm -f policies/DIF/RMT/Monitor/eDLMonitor/*_m.cc policies/DIF/RMT/Monitor/eDLMonitor/*_m.h
	$(Q)-rm -f policies/DIF/RMT/PDUForwarding/*_m.cc policies/DIF/RMT/PDUForwarding/*_m.h
	$(Q)-rm -f policies/DIF/RMT/PDUForwarding/DomainTable/*_m.cc policies/DIF/RMT/PDUForwarding/DomainTable/*_m.h
	$(Q)-rm -f policies/DIF/RMT/PDUForwarding/MiniTable/*_m.cc policies/DIF/RMT/PDUForwarding/MiniTable/*_m.h
	$(Q)-rm -f policies/DIF/RMT/PDUForwarding/QoSTable/*_m.cc policies/DIF/RMT/PDUForwarding/QoSTable/*_m.h
	$(Q)-rm -f policies/DIF/RMT/PDUForwarding/SimpleTable/*_m.cc policies/DIF/RMT/PDUForwarding/SimpleTable/*_m.h
	$(Q)-rm -f policies/DIF/RMT/Scheduler/*_m.cc policies/DIF/RMT/Scheduler/*_m.h
	$(Q)-rm -f policies/DIF/RMT/Scheduler/DumbSch/*_m.cc policies/DIF/RMT/Scheduler/DumbSch/*_m.h
	$(Q)-rm -f policies/DIF/RMT/Scheduler/LongestQFirst/*_m.cc policies/DIF/RMT/Scheduler/LongestQFirst/*_m.h
	$(Q)-rm -f policies/DIF/Routing/*_m.cc policies/DIF/Routing/*_m.h
	$(Q)-rm -f policies/DIF/Routing/DomainRouting/*_m.cc policies/DIF/Routing/DomainRouting/*_m.h
	$(Q)-rm -f policies/DIF/Routing/DomainRouting/DV/*_m.cc policies/DIF/Routing/DomainRouting/DV/*_m.h
	$(Q)-rm -f policies/DIF/Routing/DomainRouting/LS/*_m.cc policies/DIF/Routing/DomainRouting/LS/*_m.h
	$(Q)-rm -f policies/DIF/Routing/DummyRouting/*_m.cc policies/DIF/Routing/DummyRouting/*_m.h
	$(Q)-rm -f policies/DIF/Routing/SimpleRouting/*_m.cc policies/DIF/Routing/SimpleRouting/*_m.h
	$(Q)-rm -f policies/DIF/Routing/SimpleRouting/SimpleDV/*_m.cc policies/DIF/Routing/SimpleRouting/SimpleDV/*_m.h
	$(Q)-rm -f policies/DIF/Routing/SimpleRouting/SimpleLS/*_m.cc policies/DIF/Routing/SimpleRouting/SimpleLS/*_m.h
	$(Q)-rm -f scripts/*_m.cc scripts/*_m.h
	$(Q)-rm -f src/*_m.cc src/*_m.h
	$(Q)-rm -f src/CS/*_m.cc src/CS/*_m.h
	$(Q)-rm -f src/Common/*_m.cc src/Common/*_m.h
	$(Q)-rm -f src/DAF/*_m.cc src/DAF/*_m.h
	$(Q)-rm -f src/DAF/AE/*_m.cc src/DAF/AE/*_m.h
	$(Q)-rm -f src/DAF/CDAP/*_m.cc src/DAF/CDAP/*_m.h
	$(Q)-rm -f src/DAF/DA/*_m.cc src/DAF/DA/*_m.h
	$(Q)-rm -f src/DAF/IRM/*_m.cc src/DAF/IRM/*_m.h
	$(Q)-rm -f src/DIF/*_m.cc src/DIF/*_m.h
	$(Q)-rm -f src/DIF/Delimiting/*_m.cc src/DIF/Delimiting/*_m.h
	$(Q)-rm -f src/DIF/EFCP/*_m.cc src/DIF/EFCP/*_m.h
	$(Q)-rm -f src/DIF/EFCP/DTCP/*_m.cc src/DIF/EFCP/DTCP/*_m.h
	$(Q)-rm -f src/DIF/EFCP/DTP/*_m.cc src/DIF/EFCP/DTP/*_m.h
	$(Q)-rm -f src/DIF/EFCP/EFCPTable/*_m.cc src/DIF/EFCP/EFCPTable/*_m.h
	$(Q)-rm -f src/DIF/EFCP/EFCPTable/DTP/*_m.cc src/DIF/EFCP/EFCPTable/DTP/*_m.h
	$(Q)-rm -f src/DIF/Enrollment/*_m.cc src/DIF/Enrollment/*_m.h
	$(Q)-rm -f src/DIF/FA/*_m.cc src/DIF/FA/*_m.h
	$(Q)-rm -f src/DIF/NSM/*_m.cc src/DIF/NSM/*_m.h
	$(Q)-rm -f src/DIF/RA/*_m.cc src/DIF/RA/*_m.h
	$(Q)-rm -f src/DIF/RIB/*_m.cc src/DIF/RIB/*_m.h
	$(Q)-rm -f src/DIF/RMT/*_m.cc src/DIF/RMT/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc examples/*.cc examples/AllNodes/*.cc examples/AllNodes/results/*.cc examples/BigRandNet/*.cc examples/BigRandNet/results/*.cc examples/CongestedNode/*.cc examples/CongestedNode2/*.cc examples/DC/*.cc examples/DC/results/*.cc examples/ExtendedPingTwoCSsSimple/*.cc examples/ExtendedPingTwoCSsSimple/results/*.cc examples/FatTreeTopology/*.cc examples/FatTreeTopology/results/*.cc examples/FatTreeTopologyPref/*.cc examples/FatTreeTopologyPref/results/*.cc examples/SimpleRelay/*.cc examples/SimpleRelay/results/*.cc examples/SimpleRelayCongestion/*.cc examples/SimpleRelayCongestion/results/*.cc examples/SingleCS/*.cc examples/SingleCS/results/*.cc examples/SmallNetRouting/*.cc examples/SmallNetRouting/results/*.cc examples/SmallNetwork/*.cc examples/SmallNetwork/results/*.cc examples/SmallNetwork2/*.cc examples/SmallNetwork2/results/*.cc examples/SmallRandNet/*.cc examples/SmallRandNet/results/*.cc examples/TreeCongestion/*.cc examples/TwoCSWithDelay/*.cc examples/TwoCSWithDelay/results/*.cc examples/TwoCSs/*.cc examples/TwoCSs/results/*.cc examples/TwoCSsSimple/*.cc examples/TwoCSsSimple/results/*.cc examples/TwoScheduling/*.cc examples/TwoScheduling9/*.cc examples/randPrefNet/*.cc examples/randPrefNet/results/*.cc examples/treeBipart/*.cc examples/treeBipart/results/*.cc policies/*.cc policies/DAF/*.cc policies/DIF/*.cc policies/DIF/EFCP/*.cc policies/DIF/EFCP/DTCP/*.cc policies/DIF/EFCP/DTCP/ECN/*.cc policies/DIF/EFCP/DTCP/ECNSlowDown/*.cc policies/DIF/EFCP/DTCP/FCOverrun/*.cc policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyDefault/*.cc policies/DIF/EFCP/DTCP/LostControlPDU/*.cc policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyDefault/*.cc policies/DIF/EFCP/DTCP/NoOverridePeak/*.cc policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyDefault/*.cc policies/DIF/EFCP/DTCP/NoRateSlowDown/*.cc policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyDefault/*.cc policies/DIF/EFCP/DTCP/RateReduction/*.cc policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyDefault/*.cc policies/DIF/EFCP/DTCP/RcvrAck/*.cc policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyDefault/*.cc policies/DIF/EFCP/DTCP/RcvrControlAck/*.cc policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyDefault/*.cc policies/DIF/EFCP/DTCP/RcvrFC/*.cc policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyDefault/*.cc policies/DIF/EFCP/DTCP/ReceivingFC/*.cc policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyDefault/*.cc policies/DIF/EFCP/DTCP/ReconcileFC/*.cc policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyDefault/*.cc policies/DIF/EFCP/DTCP/RxTimerExpiry/*.cc policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyDefault/*.cc policies/DIF/EFCP/DTCP/SenderAck/*.cc policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyDefault/*.cc policies/DIF/EFCP/DTCP/SendingAck/*.cc policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyDefault/*.cc policies/DIF/EFCP/DTCP/TxControl/*.cc policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyDefault/*.cc policies/DIF/EFCP/DTP/*.cc policies/DIF/EFCP/DTP/InitialSeqNum/*.cc policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyDefault/*.cc policies/DIF/EFCP/DTP/RTTEstimator/*.cc policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyDefault/*.cc policies/DIF/EFCP/DTP/RcvrInactivity/*.cc policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyDefault/*.cc policies/DIF/EFCP/DTP/SenderInactivity/*.cc policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyDefault/*.cc policies/DIF/FA/*.cc policies/DIF/FA/AllocateRetry/*.cc policies/DIF/FA/AllocateRetry/LimitedRetries/*.cc policies/DIF/FA/NewFlowRequest/*.cc policies/DIF/FA/NewFlowRequest/MinComparer/*.cc policies/DIF/FA/NewFlowRequest/ScoreComparer/*.cc policies/DIF/RA/*.cc policies/DIF/RA/AddressComparator/*.cc policies/DIF/RA/AddressComparator/ExactMatch/*.cc policies/DIF/RA/AddressComparator/PrefixMatch/*.cc policies/DIF/RA/PDUFG/*.cc policies/DIF/RA/PDUFG/BiDomainGenerator/*.cc policies/DIF/RA/PDUFG/QoSDomainGenerator/*.cc policies/DIF/RA/PDUFG/SimpleGenerator/*.cc policies/DIF/RA/PDUFG/SingleDomainGenerator/*.cc policies/DIF/RA/PDUFG/StaticGenerator/*.cc policies/DIF/RA/QueueAlloc/*.cc policies/DIF/RA/QueueAlloc/QueuePerNCU/*.cc policies/DIF/RA/QueueAlloc/QueuePerNFlow/*.cc policies/DIF/RA/QueueAlloc/QueuePerNQoS/*.cc policies/DIF/RA/QueueAlloc/SingleQueue/*.cc policies/DIF/RA/QueueIDGen/*.cc policies/DIF/RA/QueueIDGen/IDPerNCU/*.cc policies/DIF/RA/QueueIDGen/IDPerNFlow/*.cc policies/DIF/RA/QueueIDGen/IDPerNQoS/*.cc policies/DIF/RA/QueueIDGen/SingleID/*.cc policies/DIF/RMT/*.cc policies/DIF/RMT/MaxQueue/*.cc policies/DIF/RMT/MaxQueue/DumbMaxQ/*.cc policies/DIF/RMT/MaxQueue/ECNMarker/*.cc policies/DIF/RMT/MaxQueue/PortMaxQ/*.cc policies/DIF/RMT/MaxQueue/REDDropper/*.cc policies/DIF/RMT/MaxQueue/ReadRateReducer/*.cc policies/DIF/RMT/MaxQueue/TailDrop/*.cc policies/DIF/RMT/MaxQueue/UpstreamNotifier/*.cc policies/DIF/RMT/Monitor/*.cc policies/DIF/RMT/Monitor/BEMonitor/*.cc policies/DIF/RMT/Monitor/DLMonitor/*.cc policies/DIF/RMT/Monitor/REDMonitor/*.cc policies/DIF/RMT/Monitor/SimpleMonitor/*.cc policies/DIF/RMT/Monitor/SmartMonitor/*.cc policies/DIF/RMT/Monitor/eDLMonitor/*.cc policies/DIF/RMT/PDUForwarding/*.cc policies/DIF/RMT/PDUForwarding/DomainTable/*.cc policies/DIF/RMT/PDUForwarding/MiniTable/*.cc policies/DIF/RMT/PDUForwarding/QoSTable/*.cc policies/DIF/RMT/PDUForwarding/SimpleTable/*.cc policies/DIF/RMT/Scheduler/*.cc policies/DIF/RMT/Scheduler/DumbSch/*.cc policies/DIF/RMT/Scheduler/LongestQFirst/*.cc policies/DIF/Routing/*.cc policies/DIF/Routing/DomainRouting/*.cc policies/DIF/Routing/DomainRouting/DV/*.cc policies/DIF/Routing/DomainRouting/LS/*.cc policies/DIF/Routing/DummyRouting/*.cc policies/DIF/Routing/SimpleRouting/*.cc policies/DIF/Routing/SimpleRouting/SimpleDV/*.cc policies/DIF/Routing/SimpleRouting/SimpleLS/*.cc scripts/*.cc src/*.cc src/CS/*.cc src/Common/*.cc src/DAF/*.cc src/DAF/AE/*.cc src/DAF/CDAP/*.cc src/DAF/DA/*.cc src/DAF/IRM/*.cc src/DIF/*.cc src/DIF/Delimiting/*.cc src/DIF/EFCP/*.cc src/DIF/EFCP/DTCP/*.cc src/DIF/EFCP/DTP/*.cc src/DIF/EFCP/EFCPTable/*.cc src/DIF/EFCP/EFCPTable/DTP/*.cc src/DIF/Enrollment/*.cc src/DIF/FA/*.cc src/DIF/NSM/*.cc src/DIF/RA/*.cc src/DIF/RIB/*.cc src/DIF/RMT/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/policies/DIF/EFCP/EFCPPolicy.o: policies/DIF/EFCP/EFCPPolicy.cc \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.o: policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyDefault.o: policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyDefault.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyDefault.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.o: policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.cc \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyBase.o: policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyBase.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/CongestionDescriptor.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/DTCP/ControlPDU_m.h \
	src/DIF/EFCP/DTCP/DTCP.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTP.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RA.h \
	src/DIF/RA/RABase.h \
	src/DIF/RA/RAListeners.h \
	src/DIF/RMT/RMT.h \
	src/DIF/RMT/RMTBase.h \
	src/DIF/RMT/RMTListeners.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyDefault/FCOverrunPolicyDefault.o: policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyDefault/FCOverrunPolicyDefault.cc \
	policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyDefault/FCOverrunPolicyDefault.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyBase.o: policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyBase.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/CongestionDescriptor.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/DTCP/ControlPDU_m.h \
	src/DIF/EFCP/DTCP/DTCP.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTP.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RA.h \
	src/DIF/RA/RABase.h \
	src/DIF/RA/RAListeners.h \
	src/DIF/RMT/RMT.h \
	src/DIF/RMT/RMTBase.h \
	src/DIF/RMT/RMTListeners.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyDefault/LostControlPDUPolicyDefault.o: policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyDefault/LostControlPDUPolicyDefault.cc \
	policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyDefault/LostControlPDUPolicyDefault.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyBase.o: policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyBase.cc \
	policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyDefault/NoOverridePeakPolicyDefault.o: policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyDefault/NoOverridePeakPolicyDefault.cc \
	policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyDefault/NoOverridePeakPolicyDefault.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyBase.o: policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyBase.cc \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyDefault/NoRateSlowDownPolicyDefault.o: policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyDefault/NoRateSlowDownPolicyDefault.cc \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyDefault/NoRateSlowDownPolicyDefault.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyBase.o: policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyBase.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/CongestionDescriptor.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/DTCP/ControlPDU_m.h \
	src/DIF/EFCP/DTCP/DTCP.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTP.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RA.h \
	src/DIF/RA/RABase.h \
	src/DIF/RA/RAListeners.h \
	src/DIF/RMT/RMT.h \
	src/DIF/RMT/RMTBase.h \
	src/DIF/RMT/RMTListeners.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyDefault/RateReductionPolicyDefault.o: policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyDefault/RateReductionPolicyDefault.cc \
	policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyDefault/RateReductionPolicyDefault.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyBase.o: policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyBase.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/CongestionDescriptor.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/DTCP/ControlPDU_m.h \
	src/DIF/EFCP/DTCP/DTCP.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTP.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RA.h \
	src/DIF/RA/RABase.h \
	src/DIF/RA/RAListeners.h \
	src/DIF/RMT/RMT.h \
	src/DIF/RMT/RMTBase.h \
	src/DIF/RMT/RMTListeners.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyDefault/RcvrAckPolicyDefault.o: policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyDefault/RcvrAckPolicyDefault.cc \
	policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyDefault/RcvrAckPolicyDefault.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyBase.o: policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyBase.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/CongestionDescriptor.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/DTCP/ControlPDU_m.h \
	src/DIF/EFCP/DTCP/DTCP.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTP.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RA.h \
	src/DIF/RA/RABase.h \
	src/DIF/RA/RAListeners.h \
	src/DIF/RMT/RMT.h \
	src/DIF/RMT/RMTBase.h \
	src/DIF/RMT/RMTListeners.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyDefault/RcvrControlAckPolicyDefault.o: policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyDefault/RcvrControlAckPolicyDefault.cc \
	policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyDefault/RcvrControlAckPolicyDefault.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyBase.o: policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyBase.cc \
	policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyDefault/RcvrFCPolicyDefault.o: policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyDefault/RcvrFCPolicyDefault.cc \
	policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyDefault/RcvrFCPolicyDefault.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyBase.o: policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyBase.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/CongestionDescriptor.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/DTCP/ControlPDU_m.h \
	src/DIF/EFCP/DTCP/DTCP.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTP.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RA.h \
	src/DIF/RA/RABase.h \
	src/DIF/RA/RAListeners.h \
	src/DIF/RMT/RMT.h \
	src/DIF/RMT/RMTBase.h \
	src/DIF/RMT/RMTListeners.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyDefault/ReceivingFCPolicyDefault.o: policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyDefault/ReceivingFCPolicyDefault.cc \
	policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyDefault/ReceivingFCPolicyDefault.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyBase.o: policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyBase.cc \
	policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyDefault/ReconcileFCPolicyDefault.o: policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyDefault/ReconcileFCPolicyDefault.cc \
	policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyDefault/ReconcileFCPolicyDefault.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyBase.o: policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyBase.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/CongestionDescriptor.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/DTCP/ControlPDU_m.h \
	src/DIF/EFCP/DTCP/DTCP.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTP.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RA.h \
	src/DIF/RA/RABase.h \
	src/DIF/RA/RAListeners.h \
	src/DIF/RMT/RMT.h \
	src/DIF/RMT/RMTBase.h \
	src/DIF/RMT/RMTListeners.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyDefault/RxTimerExpiryPolicyDefault.o: policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyDefault/RxTimerExpiryPolicyDefault.cc \
	policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyBase.h \
	policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyDefault/RxTimerExpiryPolicyDefault.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyBase.o: policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyBase.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/CongestionDescriptor.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/DTCP/ControlPDU_m.h \
	src/DIF/EFCP/DTCP/DTCP.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTP.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RA.h \
	src/DIF/RA/RABase.h \
	src/DIF/RA/RAListeners.h \
	src/DIF/RMT/RMT.h \
	src/DIF/RMT/RMTBase.h \
	src/DIF/RMT/RMTListeners.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyDefault/SenderAckPolicyDefault.o: policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyDefault/SenderAckPolicyDefault.cc \
	policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyDefault/SenderAckPolicyDefault.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyBase.o: policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyBase.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/CongestionDescriptor.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/DTCP/ControlPDU_m.h \
	src/DIF/EFCP/DTCP/DTCP.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTP.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RA.h \
	src/DIF/RA/RABase.h \
	src/DIF/RA/RAListeners.h \
	src/DIF/RMT/RMT.h \
	src/DIF/RMT/RMTBase.h \
	src/DIF/RMT/RMTListeners.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyDefault/SendingAckPolicyDefault.o: policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyDefault/SendingAckPolicyDefault.cc \
	policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyDefault/SendingAckPolicyDefault.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyBase.o: policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyBase.cc \
	policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyDefault/TxControlPolicyDefault.o: policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyDefault/TxControlPolicyDefault.cc \
	policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyDefault/TxControlPolicyDefault.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyBase.o: policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyBase.cc \
	policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyDefault/InitialSeqNumPolicyDefault.o: policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyDefault/InitialSeqNumPolicyDefault.cc \
	policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyDefault/InitialSeqNumPolicyDefault.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyBase.o: policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyBase.cc \
	policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/ControlPDU_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyDefault/RTTEstimatorPolicyDefault.o: policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyDefault/RTTEstimatorPolicyDefault.cc \
	policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyDefault/RTTEstimatorPolicyDefault.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/ControlPDU_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyBase.o: policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyBase.cc \
	policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyDefault/RcvrInactivityPolicyDefault.o: policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyDefault/RcvrInactivityPolicyDefault.cc \
	policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyDefault/RcvrInactivityPolicyDefault.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyBase.o: policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyBase.cc \
	policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyDefault/SenderInactivityPolicyDefault.o: policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyDefault/SenderInactivityPolicyDefault.cc \
	policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyDefault/SenderInactivityPolicyDefault.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/FA/AllocateRetry/AllocateRetryBase.o: policies/DIF/FA/AllocateRetry/AllocateRetryBase.cc \
	policies/DIF/FA/AllocateRetry/AllocateRetryBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/DIF/EFCP/EFCPPolicySet.h
$O/policies/DIF/FA/AllocateRetry/LimitedRetries/LimitedRetries.o: policies/DIF/FA/AllocateRetry/LimitedRetries/LimitedRetries.cc \
	policies/DIF/FA/AllocateRetry/AllocateRetryBase.h \
	policies/DIF/FA/AllocateRetry/LimitedRetries/LimitedRetries.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/DIF/EFCP/EFCPPolicySet.h
$O/policies/DIF/FA/NewFlowRequest/NewFlowRequestBase.o: policies/DIF/FA/NewFlowRequest/NewFlowRequestBase.cc \
	policies/DIF/FA/NewFlowRequest/NewFlowRequestBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RABase.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/FA/NewFlowRequest/MinComparer/MinComparer.o: policies/DIF/FA/NewFlowRequest/MinComparer/MinComparer.cc \
	policies/DIF/FA/NewFlowRequest/MinComparer/MinComparer.h \
	policies/DIF/FA/NewFlowRequest/NewFlowRequestBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RABase.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/FA/NewFlowRequest/ScoreComparer/ScoreComparer.o: policies/DIF/FA/NewFlowRequest/ScoreComparer/ScoreComparer.cc \
	policies/DIF/FA/NewFlowRequest/NewFlowRequestBase.h \
	policies/DIF/FA/NewFlowRequest/ScoreComparer/ScoreComparer.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RABase.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RA/AddressComparator/AddressComparatorBase.o: policies/DIF/RA/AddressComparator/AddressComparatorBase.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h
$O/policies/DIF/RA/AddressComparator/ExactMatch/ExactMatch.o: policies/DIF/RA/AddressComparator/ExactMatch/ExactMatch.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/AddressComparator/ExactMatch/ExactMatch.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h
$O/policies/DIF/RA/AddressComparator/PrefixMatch/PrefixMatch.o: policies/DIF/RA/AddressComparator/PrefixMatch/PrefixMatch.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/AddressComparator/PrefixMatch/PrefixMatch.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Utils.h
$O/policies/DIF/RA/PDUFG/IntBbPDUFG.o: policies/DIF/RA/PDUFG/IntBbPDUFG.cc \
	policies/DIF/RA/PDUFG/IntBbPDUFG.h \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/PDUForwarding/IntBbPDUForwarding.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/Routing/IntBbRouting.h \
	policies/DIF/Routing/IntRouting.h \
	policies/DIF/Routing/IntRoutingUpdate.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RA/PDUFG/IntPDUFG.o: policies/DIF/RA/PDUFG/IntPDUFG.cc \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RA/PDUFG/PDUFGNeighbor.o: policies/DIF/RA/PDUFG/PDUFGNeighbor.cc \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RA/PDUFG/BiDomainGenerator/BiDomainGenerator.o: policies/DIF/RA/PDUFG/BiDomainGenerator/BiDomainGenerator.cc \
	policies/DIF/RA/PDUFG/BiDomainGenerator/BiDomainGenerator.h \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/PDUForwarding/DomainTable/DomainTable.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/Routing/DomainRouting/Routing.h \
	policies/DIF/Routing/DomainRouting/rModule.h \
	policies/DIF/Routing/IntRouting.h \
	policies/DIF/Routing/IntRoutingUpdate.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/Common/Utils.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RA/PDUFG/QoSDomainGenerator/QoSDomainGenerator.o: policies/DIF/RA/PDUFG/QoSDomainGenerator/QoSDomainGenerator.cc \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/PDUFG/QoSDomainGenerator/QoSDomainGenerator.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/PDUForwarding/QoSTable/QoSTable.h \
	policies/DIF/Routing/DomainRouting/Routing.h \
	policies/DIF/Routing/DomainRouting/rModule.h \
	policies/DIF/Routing/IntRouting.h \
	policies/DIF/Routing/IntRoutingUpdate.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RA/PDUFG/SimpleGenerator/SimpleGenerator.o: policies/DIF/RA/PDUFG/SimpleGenerator/SimpleGenerator.cc \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/PDUFG/SimpleGenerator/SimpleGenerator.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/PDUForwarding/SimpleTable/SimpleTable.h \
	policies/DIF/Routing/IntRouting.h \
	policies/DIF/Routing/IntRoutingUpdate.h \
	policies/DIF/Routing/SimpleRouting/IntSimpleRouting.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RA/PDUFG/SingleDomainGenerator/SingleDomainGenerator.o: policies/DIF/RA/PDUFG/SingleDomainGenerator/SingleDomainGenerator.cc \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/PDUFG/SingleDomainGenerator/SingleDomainGenerator.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/PDUForwarding/MiniTable/MiniTable.h \
	policies/DIF/Routing/DomainRouting/Routing.h \
	policies/DIF/Routing/DomainRouting/rModule.h \
	policies/DIF/Routing/IntRouting.h \
	policies/DIF/Routing/IntRoutingUpdate.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RA/PDUFG/StaticGenerator/StaticGenerator.o: policies/DIF/RA/PDUFG/StaticGenerator/StaticGenerator.cc \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/PDUFG/StaticGenerator/StaticGenerator.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/PDUForwarding/SimpleTable/SimpleTable.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RA/QueueAlloc/QueueAllocBase.o: policies/DIF/RA/QueueAlloc/QueueAllocBase.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RABase.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RA/QueueAlloc/QueuePerNCU/QueuePerNCU.o: policies/DIF/RA/QueueAlloc/QueuePerNCU/QueuePerNCU.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	policies/DIF/RA/QueueAlloc/QueuePerNCU/QueuePerNCU.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RABase.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RA/QueueAlloc/QueuePerNFlow/QueuePerNFlow.o: policies/DIF/RA/QueueAlloc/QueuePerNFlow/QueuePerNFlow.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	policies/DIF/RA/QueueAlloc/QueuePerNFlow/QueuePerNFlow.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RABase.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RA/QueueAlloc/QueuePerNQoS/QueuePerNQoS.o: policies/DIF/RA/QueueAlloc/QueuePerNQoS/QueuePerNQoS.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	policies/DIF/RA/QueueAlloc/QueuePerNQoS/QueuePerNQoS.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RABase.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RA/QueueAlloc/SingleQueue/SingleQueue.o: policies/DIF/RA/QueueAlloc/SingleQueue/SingleQueue.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	policies/DIF/RA/QueueAlloc/SingleQueue/SingleQueue.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RABase.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RA/QueueIDGen/QueueIDGenBase.o: policies/DIF/RA/QueueIDGen/QueueIDGenBase.cc \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/DIF/EFCP/EFCPPolicySet.h
$O/policies/DIF/RA/QueueIDGen/IDPerNCU/IDPerNCU.o: policies/DIF/RA/QueueIDGen/IDPerNCU/IDPerNCU.cc \
	policies/DIF/RA/QueueIDGen/IDPerNCU/IDPerNCU.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/DIF/EFCP/EFCPPolicySet.h
$O/policies/DIF/RA/QueueIDGen/IDPerNFlow/IDPerNFlow.o: policies/DIF/RA/QueueIDGen/IDPerNFlow/IDPerNFlow.cc \
	policies/DIF/RA/QueueIDGen/IDPerNFlow/IDPerNFlow.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/DIF/EFCP/EFCPPolicySet.h
$O/policies/DIF/RA/QueueIDGen/IDPerNQoS/IDPerNQoS.o: policies/DIF/RA/QueueIDGen/IDPerNQoS/IDPerNQoS.cc \
	policies/DIF/RA/QueueIDGen/IDPerNQoS/IDPerNQoS.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/DIF/EFCP/EFCPPolicySet.h
$O/policies/DIF/RA/QueueIDGen/SingleID/SingleID.o: policies/DIF/RA/QueueIDGen/SingleID/SingleID.cc \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RA/QueueIDGen/SingleID/SingleID.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/DIF/EFCP/EFCPPolicySet.h
$O/policies/DIF/RMT/MaxQueue/RMTMaxQBase.o: policies/DIF/RMT/MaxQueue/RMTMaxQBase.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RMT/MaxQueue/DumbMaxQ/DumbMaxQ.o: policies/DIF/RMT/MaxQueue/DumbMaxQ/DumbMaxQ.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/DumbMaxQ/DumbMaxQ.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/Monitor/SmartMonitor/SmartMonitor.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RMT/MaxQueue/ECNMarker/ECNMarker.o: policies/DIF/RMT/MaxQueue/ECNMarker/ECNMarker.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/ECNMarker/ECNMarker.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RMT/MaxQueue/PortMaxQ/PortMaxQ.o: policies/DIF/RMT/MaxQueue/PortMaxQ/PortMaxQ.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/PortMaxQ/PortMaxQ.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/Monitor/SmartMonitor/SmartMonitor.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RMT/MaxQueue/REDDropper/REDDropper.o: policies/DIF/RMT/MaxQueue/REDDropper/REDDropper.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/REDDropper/REDDropper.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/Monitor/REDMonitor/REDMonitor.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RMT/MaxQueue/ReadRateReducer/ReadRateReducer.o: policies/DIF/RMT/MaxQueue/ReadRateReducer/ReadRateReducer.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/MaxQueue/ReadRateReducer/ReadRateReducer.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RMT/MaxQueue/TailDrop/TailDrop.o: policies/DIF/RMT/MaxQueue/TailDrop/TailDrop.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/MaxQueue/TailDrop/TailDrop.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RMT/MaxQueue/UpstreamNotifier/UpstreamNotifier.o: policies/DIF/RMT/MaxQueue/UpstreamNotifier/UpstreamNotifier.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/MaxQueue/UpstreamNotifier/UpstreamNotifier.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RMT/Monitor/RMTQMonitorBase.o: policies/DIF/RMT/Monitor/RMTQMonitorBase.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RMT/Monitor/BEMonitor/BEMonitor.o: policies/DIF/RMT/Monitor/BEMonitor/BEMonitor.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/Monitor/BEMonitor/BEMonitor.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/Monitor/SmartMonitor/SmartMonitor.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RMT/Monitor/DLMonitor/DLMonitor.o: policies/DIF/RMT/Monitor/DLMonitor/DLMonitor.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/Monitor/DLMonitor/DLMonitor.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/Monitor/SmartMonitor/SmartMonitor.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RMT/Monitor/REDMonitor/REDMonitor.o: policies/DIF/RMT/Monitor/REDMonitor/REDMonitor.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/Monitor/REDMonitor/REDMonitor.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RMT/Monitor/SimpleMonitor/SimpleMonitor.o: policies/DIF/RMT/Monitor/SimpleMonitor/SimpleMonitor.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/Monitor/SimpleMonitor/SimpleMonitor.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RMT/Monitor/eDLMonitor/eDLMonitor.o: policies/DIF/RMT/Monitor/eDLMonitor/eDLMonitor.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/Monitor/SmartMonitor/SmartMonitor.h \
	policies/DIF/RMT/Monitor/eDLMonitor/eDLMonitor.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.o: policies/DIF/RMT/PDUForwarding/IntPDUForwarding.cc \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RMT/PDUForwarding/DomainTable/DomainTable.o: policies/DIF/RMT/PDUForwarding/DomainTable/DomainTable.cc \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/PDUForwarding/DomainTable/DomainTable.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/Common/Utils.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RMT/PDUForwarding/MiniTable/MiniTable.o: policies/DIF/RMT/PDUForwarding/MiniTable/MiniTable.cc \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/PDUForwarding/MiniTable/MiniTable.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RMT/PDUForwarding/QoSTable/QoSTable.o: policies/DIF/RMT/PDUForwarding/QoSTable/QoSTable.cc \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/PDUForwarding/QoSTable/QoSTable.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RMT/PDUForwarding/SimpleTable/SimpleTable.o: policies/DIF/RMT/PDUForwarding/SimpleTable/SimpleTable.cc \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/PDUForwarding/SimpleTable/SimpleTable.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RMT/Scheduler/RMTSchedulingBase.o: policies/DIF/RMT/Scheduler/RMTSchedulingBase.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RMT/Scheduler/DumbSch/DumbSch.o: policies/DIF/RMT/Scheduler/DumbSch/DumbSch.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/Monitor/SmartMonitor/SmartMonitor.h \
	policies/DIF/RMT/Scheduler/DumbSch/DumbSch.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/RMT/Scheduler/LongestQFirst/LongestQFirst.o: policies/DIF/RMT/Scheduler/LongestQFirst/LongestQFirst.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/Scheduler/LongestQFirst/LongestQFirst.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/Routing/IntBbRouting.o: policies/DIF/Routing/IntBbRouting.cc \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/Routing/IntBbRouting.h \
	policies/DIF/Routing/IntRouting.h \
	policies/DIF/Routing/IntRoutingUpdate.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/Routing/IntRouting.o: policies/DIF/Routing/IntRouting.cc \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/Routing/IntRouting.h \
	policies/DIF/Routing/IntRoutingUpdate.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/Routing/IntRoutingUpdate.o: policies/DIF/Routing/IntRoutingUpdate.cc \
	policies/DIF/Routing/IntRoutingUpdate.h \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/DAP.h
$O/policies/DIF/Routing/DomainRouting/Routing.o: policies/DIF/Routing/DomainRouting/Routing.cc \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/Routing/DomainRouting/DV/DV.h \
	policies/DIF/Routing/DomainRouting/LS/LS.h \
	policies/DIF/Routing/DomainRouting/Routing.h \
	policies/DIF/Routing/DomainRouting/rModule.h \
	policies/DIF/Routing/IntRouting.h \
	policies/DIF/Routing/IntRoutingUpdate.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/Routing/DomainRouting/rModule.o: policies/DIF/Routing/DomainRouting/rModule.cc \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/Routing/DomainRouting/Routing.h \
	policies/DIF/Routing/DomainRouting/rModule.h \
	policies/DIF/Routing/IntRouting.h \
	policies/DIF/Routing/IntRoutingUpdate.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/Routing/DomainRouting/DV/DV.o: policies/DIF/Routing/DomainRouting/DV/DV.cc \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/Routing/DomainRouting/DV/DV.h \
	policies/DIF/Routing/DomainRouting/Routing.h \
	policies/DIF/Routing/DomainRouting/rModule.h \
	policies/DIF/Routing/IntRouting.h \
	policies/DIF/Routing/IntRoutingUpdate.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/Routing/DomainRouting/LS/LS.o: policies/DIF/Routing/DomainRouting/LS/LS.cc \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/Routing/DomainRouting/LS/LS.h \
	policies/DIF/Routing/DomainRouting/Routing.h \
	policies/DIF/Routing/DomainRouting/rModule.h \
	policies/DIF/Routing/IntRouting.h \
	policies/DIF/Routing/IntRoutingUpdate.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/Routing/DummyRouting/DummyRouting.o: policies/DIF/Routing/DummyRouting/DummyRouting.cc \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/Routing/DummyRouting/DummyRouting.h \
	policies/DIF/Routing/IntRouting.h \
	policies/DIF/Routing/IntRoutingUpdate.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/Routing/SimpleRouting/SimpleDV/SimpleDV.o: policies/DIF/Routing/SimpleRouting/SimpleDV/SimpleDV.cc \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/Routing/IntRouting.h \
	policies/DIF/Routing/IntRoutingUpdate.h \
	policies/DIF/Routing/SimpleRouting/IntSimpleRouting.h \
	policies/DIF/Routing/SimpleRouting/SimpleDV/SimpleDV.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/policies/DIF/Routing/SimpleRouting/SimpleLS/SimpleLS.o: policies/DIF/Routing/SimpleRouting/SimpleLS/SimpleLS.cc \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/Routing/IntRouting.h \
	policies/DIF/Routing/IntRoutingUpdate.h \
	policies/DIF/Routing/SimpleRouting/IntSimpleRouting.h \
	policies/DIF/Routing/SimpleRouting/SimpleLS/SimpleLS.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/src/Common/APN.o: src/Common/APN.cc \
	src/Common/APN.h
$O/src/Common/APNamingInfo.o: src/Common/APNamingInfo.cc \
	src/Common/APN.h \
	src/Common/APNamingInfo.h
$O/src/Common/Address.o: src/Common/Address.cc \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/DAP.h
$O/src/Common/CongestionDescriptor.o: src/Common/CongestionDescriptor.cc \
	src/Common/CongestionDescriptor.h \
	src/Common/ConnectionId.h \
	src/Common/ExternConsts.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/DIF/EFCP/EFCPPolicySet.h
$O/src/Common/ConnectionId.o: src/Common/ConnectionId.cc \
	src/Common/ConnectionId.h \
	src/Common/ExternConsts.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/DIF/EFCP/EFCPPolicySet.h
$O/src/Common/DAP.o: src/Common/DAP.cc \
	src/Common/DAP.h
$O/src/Common/Data.o: src/Common/Data.cc \
	src/Common/Data.h \
	src/Common/Data_m.h
$O/src/Common/Data_m.o: src/Common/Data_m.cc \
	src/Common/Data_m.h
$O/src/Common/ExternConsts.o: src/Common/ExternConsts.cc \
	src/Common/ExternConsts.h
$O/src/Common/Flow.o: src/Common/Flow.cc \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/DIF/EFCP/EFCPPolicySet.h
$O/src/Common/ModuleAccess.o: src/Common/ModuleAccess.cc \
	src/Common/ModuleAccess.h
$O/src/Common/PDU.o: src/Common/PDU.cc \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/DIF/EFCP/EFCPPolicySet.h
$O/src/Common/PDU_m.o: src/Common/PDU_m.cc \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/DIF/EFCP/EFCPPolicySet.h
$O/src/Common/Policy.o: src/Common/Policy.cc \
	src/Common/Policy.h
$O/src/Common/QoSCube.o: src/Common/QoSCube.cc \
	src/Common/ExternConsts.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/DIF/EFCP/EFCPPolicySet.h
$O/src/Common/QoSReq.o: src/Common/QoSReq.cc \
	src/Common/ExternConsts.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/DIF/EFCP/EFCPPolicySet.h
$O/src/Common/RINASignals.o: src/Common/RINASignals.cc \
	src/Common/RINASignals.h
$O/src/Common/SDU.o: src/Common/SDU.cc \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCP_defs.h
$O/src/Common/SDU_m.o: src/Common/SDU_m.cc \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/SDU_m.h
$O/src/Common/SHA256.o: src/Common/SHA256.cc \
	src/Common/SHA256.h
$O/src/Common/Test.o: src/Common/Test.cc \
	src/Common/Test.h
$O/src/Common/Utils.o: src/Common/Utils.cc \
	src/Common/Utils.h
$O/src/DAF/AE/AE.o: src/DAF/AE/AE.cc \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/AE/AE.h \
	src/DAF/AE/AEBase.h \
	src/DAF/AE/AEListeners.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DAF/IRM/ConnectionTable.h \
	src/DAF/IRM/ConnectionTableEntry.h \
	src/DAF/IRM/IRM.h \
	src/DAF/IRM/IRMListeners.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h
$O/src/DAF/AE/AEBase.o: src/DAF/AE/AEBase.cc \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/DAF/AE/AEBase.h \
	src/DIF/EFCP/EFCPPolicySet.h
$O/src/DAF/AE/AEExtendedPing.o: src/DAF/AE/AEExtendedPing.cc \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/AE/AE.h \
	src/DAF/AE/AEBase.h \
	src/DAF/AE/AEExtendedPing.h \
	src/DAF/AE/AEListeners.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DAF/IRM/ConnectionTable.h \
	src/DAF/IRM/ConnectionTableEntry.h \
	src/DAF/IRM/IRM.h \
	src/DAF/IRM/IRMListeners.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h
$O/src/DAF/AE/AEListeners.o: src/DAF/AE/AEListeners.cc \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/AE/AE.h \
	src/DAF/AE/AEBase.h \
	src/DAF/AE/AEListeners.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DAF/IRM/ConnectionTable.h \
	src/DAF/IRM/ConnectionTableEntry.h \
	src/DAF/IRM/IRM.h \
	src/DAF/IRM/IRMListeners.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h
$O/src/DAF/AE/AEPing.o: src/DAF/AE/AEPing.cc \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/AE/AE.h \
	src/DAF/AE/AEBase.h \
	src/DAF/AE/AEListeners.h \
	src/DAF/AE/AEPing.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DAF/IRM/ConnectionTable.h \
	src/DAF/IRM/ConnectionTableEntry.h \
	src/DAF/IRM/IRM.h \
	src/DAF/IRM/IRMListeners.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h
$O/src/DAF/AE/AESender.o: src/DAF/AE/AESender.cc \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/AE/AE.h \
	src/DAF/AE/AEBase.h \
	src/DAF/AE/AEListeners.h \
	src/DAF/AE/AESender.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DAF/IRM/ConnectionTable.h \
	src/DAF/IRM/ConnectionTableEntry.h \
	src/DAF/IRM/IRM.h \
	src/DAF/IRM/IRMListeners.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h
$O/src/DAF/AE/AEStream.o: src/DAF/AE/AEStream.cc \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/AE/AE.h \
	src/DAF/AE/AEBase.h \
	src/DAF/AE/AEListeners.h \
	src/DAF/AE/AEStream.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DAF/IRM/ConnectionTable.h \
	src/DAF/IRM/ConnectionTableEntry.h \
	src/DAF/IRM/IRM.h \
	src/DAF/IRM/IRMListeners.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h
$O/src/DAF/CDAP/Auth.o: src/DAF/CDAP/Auth.cc \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/AE/AE.h \
	src/DAF/AE/AEBase.h \
	src/DAF/AE/AEListeners.h \
	src/DAF/CDAP/Auth.h \
	src/DAF/CDAP/AuthListeners.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DAF/IRM/ConnectionTable.h \
	src/DAF/IRM/ConnectionTableEntry.h \
	src/DAF/IRM/IRM.h \
	src/DAF/IRM/IRMListeners.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h
$O/src/DAF/CDAP/AuthListeners.o: src/DAF/CDAP/AuthListeners.cc \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/AE/AE.h \
	src/DAF/AE/AEBase.h \
	src/DAF/AE/AEListeners.h \
	src/DAF/CDAP/Auth.h \
	src/DAF/CDAP/AuthListeners.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DAF/IRM/ConnectionTable.h \
	src/DAF/IRM/ConnectionTableEntry.h \
	src/DAF/IRM/IRM.h \
	src/DAF/IRM/IRMListeners.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h
$O/src/DAF/CDAP/CACE.o: src/DAF/CDAP/CACE.cc \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/AE/AE.h \
	src/DAF/AE/AEBase.h \
	src/DAF/AE/AEListeners.h \
	src/DAF/CDAP/CACE.h \
	src/DAF/CDAP/CACEListeners.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DAF/IRM/ConnectionTable.h \
	src/DAF/IRM/ConnectionTableEntry.h \
	src/DAF/IRM/IRM.h \
	src/DAF/IRM/IRMListeners.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h
$O/src/DAF/CDAP/CACEListeners.o: src/DAF/CDAP/CACEListeners.cc \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/AE/AE.h \
	src/DAF/AE/AEBase.h \
	src/DAF/AE/AEListeners.h \
	src/DAF/CDAP/CACE.h \
	src/DAF/CDAP/CACEListeners.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DAF/IRM/ConnectionTable.h \
	src/DAF/IRM/ConnectionTableEntry.h \
	src/DAF/IRM/IRM.h \
	src/DAF/IRM/IRMListeners.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h
$O/src/DAF/CDAP/CDAP.o: src/DAF/CDAP/CDAP.cc \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAP.h \
	src/DAF/CDAP/CDAPListeners.h \
	src/DAF/CDAP/CDAPMessage_m.h
$O/src/DAF/CDAP/CDAPListeners.o: src/DAF/CDAP/CDAPListeners.cc \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAP.h \
	src/DAF/CDAP/CDAPListeners.h \
	src/DAF/CDAP/CDAPMessage_m.h
$O/src/DAF/CDAP/CDAPMessage_m.o: src/DAF/CDAP/CDAPMessage_m.cc \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/DAP.h \
	src/DAF/CDAP/CDAPMessage_m.h
$O/src/DAF/CDAP/CDAPMsgLog.o: src/DAF/CDAP/CDAPMsgLog.cc \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/CDAP/CDAPMsgLog.h \
	src/DAF/CDAP/CDAPMsgLogEntry.h
$O/src/DAF/CDAP/CDAPMsgLogEntry.o: src/DAF/CDAP/CDAPMsgLogEntry.cc \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/CDAP/CDAPMsgLogEntry.h
$O/src/DAF/CDAP/CDAPSplitter.o: src/DAF/CDAP/CDAPSplitter.cc \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/CDAP/CDAPMsgLog.h \
	src/DAF/CDAP/CDAPMsgLogEntry.h \
	src/DAF/CDAP/CDAPSplitter.h
$O/src/DAF/DA/DA.o: src/DAF/DA/DA.cc \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h
$O/src/DAF/DA/Directory.o: src/DAF/DA/Directory.cc \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h
$O/src/DAF/DA/DirectoryEntry.o: src/DAF/DA/DirectoryEntry.cc \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/DAP.h \
	src/DAF/DA/DirectoryEntry.h
$O/src/DAF/DA/NamingInformation.o: src/DAF/DA/NamingInformation.cc \
	src/Common/APN.h \
	src/Common/ExternConsts.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h
$O/src/DAF/DA/NamingInformationEntry.o: src/DAF/DA/NamingInformationEntry.cc \
	src/Common/APN.h \
	src/DAF/DA/NamingInformationEntry.h
$O/src/DAF/DA/NeighborTable.o: src/DAF/DA/NeighborTable.cc \
	src/Common/APN.h \
	src/Common/ExternConsts.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h
$O/src/DAF/DA/NeighborTableEntry.o: src/DAF/DA/NeighborTableEntry.cc \
	src/Common/APN.h \
	src/DAF/DA/NeighborTableEntry.h
$O/src/DAF/DA/SearchTable.o: src/DAF/DA/SearchTable.cc \
	src/Common/APN.h \
	src/Common/ExternConsts.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h
$O/src/DAF/DA/SearchTableEntry.o: src/DAF/DA/SearchTableEntry.cc \
	src/Common/APN.h \
	src/DAF/DA/SearchTableEntry.h
$O/src/DAF/IRM/ConnectionTable.o: src/DAF/IRM/ConnectionTable.cc \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/DAF/IRM/ConnectionTable.h \
	src/DAF/IRM/ConnectionTableEntry.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h
$O/src/DAF/IRM/ConnectionTableEntry.o: src/DAF/IRM/ConnectionTableEntry.cc \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/DAF/IRM/ConnectionTableEntry.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h
$O/src/DAF/IRM/IRM.o: src/DAF/IRM/IRM.cc \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DAF/IRM/ConnectionTable.h \
	src/DAF/IRM/ConnectionTableEntry.h \
	src/DAF/IRM/IRM.h \
	src/DAF/IRM/IRMListeners.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h
$O/src/DAF/IRM/IRMListeners.o: src/DAF/IRM/IRMListeners.cc \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DAF/IRM/ConnectionTable.h \
	src/DAF/IRM/ConnectionTableEntry.h \
	src/DAF/IRM/IRM.h \
	src/DAF/IRM/IRMListeners.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h
$O/src/DIF/Delimiting/Delimiting.o: src/DIF/Delimiting/Delimiting.cc \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/Delimiting/Delimiting.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/src/DIF/EFCP/EFCP.o: src/DIF/EFCP/EFCP.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/CongestionDescriptor.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/Delimiting/Delimiting.h \
	src/DIF/EFCP/DTCP/ControlPDU_m.h \
	src/DIF/EFCP/DTCP/DTCP.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTP.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCP.h \
	src/DIF/EFCP/EFCPInstance.h \
	src/DIF/EFCP/EFCPListeners.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCPTable/EFCPTable.h \
	src/DIF/EFCP/EFCPTable/EFCPTableEntry.h \
	src/DIF/EFCP/EFCP_defs.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RA.h \
	src/DIF/RA/RABase.h \
	src/DIF/RA/RAListeners.h \
	src/DIF/RMT/RMT.h \
	src/DIF/RMT/RMTBase.h \
	src/DIF/RMT/RMTListeners.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/src/DIF/EFCP/EFCPInstance.o: src/DIF/EFCP/EFCPInstance.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/CongestionDescriptor.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/DTCP/ControlPDU_m.h \
	src/DIF/EFCP/DTCP/DTCP.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTP.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPInstance.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RA.h \
	src/DIF/RA/RABase.h \
	src/DIF/RA/RAListeners.h \
	src/DIF/RMT/RMT.h \
	src/DIF/RMT/RMTBase.h \
	src/DIF/RMT/RMTListeners.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/src/DIF/EFCP/EFCPListeners.o: src/DIF/EFCP/EFCPListeners.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/CongestionDescriptor.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/Delimiting/Delimiting.h \
	src/DIF/EFCP/DTCP/ControlPDU_m.h \
	src/DIF/EFCP/DTCP/DTCP.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTP.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPInstance.h \
	src/DIF/EFCP/EFCPListeners.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCPTable/EFCPTable.h \
	src/DIF/EFCP/EFCPTable/EFCPTableEntry.h \
	src/DIF/EFCP/EFCP_defs.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RA.h \
	src/DIF/RA/RABase.h \
	src/DIF/RA/RAListeners.h \
	src/DIF/RMT/RMT.h \
	src/DIF/RMT/RMTBase.h \
	src/DIF/RMT/RMTListeners.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/src/DIF/EFCP/EFCPPolicySet.o: src/DIF/EFCP/EFCPPolicySet.cc \
	src/DIF/EFCP/EFCPPolicySet.h
$O/src/DIF/EFCP/DTCP/ControlPDU_m.o: src/DIF/EFCP/DTCP/ControlPDU_m.cc \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/DIF/EFCP/DTCP/ControlPDU_m.h \
	src/DIF/EFCP/EFCPPolicySet.h
$O/src/DIF/EFCP/DTCP/DTCP.o: src/DIF/EFCP/DTCP/DTCP.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/CongestionDescriptor.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/DTCP/ControlPDU_m.h \
	src/DIF/EFCP/DTCP/DTCP.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTP.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RA.h \
	src/DIF/RA/RABase.h \
	src/DIF/RA/RAListeners.h \
	src/DIF/RMT/RMT.h \
	src/DIF/RMT/RMTBase.h \
	src/DIF/RMT/RMTListeners.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/src/DIF/EFCP/DTCP/DTCPState.o: src/DIF/EFCP/DTCP/DTCPState.cc \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/src/DIF/EFCP/DTCP/DTCPTimers_m.o: src/DIF/EFCP/DTCP/DTCPTimers_m.cc \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/src/DIF/EFCP/DTCP/RXControl.o: src/DIF/EFCP/DTCP/RXControl.cc \
	src/DIF/EFCP/DTCP/RXControl.h
$O/src/DIF/EFCP/DTP/DTP.o: src/DIF/EFCP/DTP/DTP.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/CongestionDescriptor.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/DTCP/ControlPDU_m.h \
	src/DIF/EFCP/DTCP/DTCP.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTP.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RA.h \
	src/DIF/RA/RABase.h \
	src/DIF/RA/RAListeners.h \
	src/DIF/RMT/RMT.h \
	src/DIF/RMT/RMTBase.h \
	src/DIF/RMT/RMTListeners.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/src/DIF/EFCP/DTP/DTPState.o: src/DIF/EFCP/DTP/DTPState.cc \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/src/DIF/EFCP/DTP/DTPTimers_m.o: src/DIF/EFCP/DTP/DTPTimers_m.cc \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/src/DIF/EFCP/DTP/DataTransferPDU.o: src/DIF/EFCP/DTP/DataTransferPDU.cc \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/src/DIF/EFCP/DTP/DataTransferPDU_m.o: src/DIF/EFCP/DTP/DataTransferPDU_m.cc \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCP_defs.h
$O/src/DIF/EFCP/DTP/DumbGate.o: src/DIF/EFCP/DTP/DumbGate.cc \
	src/DIF/EFCP/DTP/DumbGate.h
$O/src/DIF/EFCP/DTP/PushBackChannel.o: src/DIF/EFCP/DTP/PushBackChannel.cc \
	src/DIF/EFCP/DTP/PushBackChannel.h
$O/src/DIF/EFCP/DTP/UserDataField.o: src/DIF/EFCP/DTP/UserDataField.cc \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCP_defs.h
$O/src/DIF/EFCP/EFCPTable/EFCPTable.o: src/DIF/EFCP/EFCPTable/EFCPTable.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/CongestionDescriptor.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/Delimiting/Delimiting.h \
	src/DIF/EFCP/DTCP/ControlPDU_m.h \
	src/DIF/EFCP/DTCP/DTCP.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTP.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPInstance.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCPTable/EFCPTable.h \
	src/DIF/EFCP/EFCPTable/EFCPTableEntry.h \
	src/DIF/EFCP/EFCP_defs.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RA.h \
	src/DIF/RA/RABase.h \
	src/DIF/RA/RAListeners.h \
	src/DIF/RMT/RMT.h \
	src/DIF/RMT/RMTBase.h \
	src/DIF/RMT/RMTListeners.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/src/DIF/EFCP/EFCPTable/EFCPTableEntry.o: src/DIF/EFCP/EFCPTable/EFCPTableEntry.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/CongestionDescriptor.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/Delimiting/Delimiting.h \
	src/DIF/EFCP/DTCP/ControlPDU_m.h \
	src/DIF/EFCP/DTCP/DTCP.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTP.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCPInstance.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCPTable/EFCPTableEntry.h \
	src/DIF/EFCP/EFCP_defs.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RA.h \
	src/DIF/RA/RABase.h \
	src/DIF/RA/RAListeners.h \
	src/DIF/RMT/RMT.h \
	src/DIF/RMT/RMTBase.h \
	src/DIF/RMT/RMTListeners.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/src/DIF/Enrollment/Enrollment.o: src/DIF/Enrollment/Enrollment.cc \
	src/DIF/Enrollment/Enrollment.h
$O/src/DIF/FA/FA.o: src/DIF/FA/FA.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	policies/DIF/FA/AllocateRetry/AllocateRetryBase.h \
	policies/DIF/FA/NewFlowRequest/NewFlowRequestBase.h \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/CongestionDescriptor.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/Delimiting/Delimiting.h \
	src/DIF/EFCP/DTCP/ControlPDU_m.h \
	src/DIF/EFCP/DTCP/DTCP.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTP.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCP.h \
	src/DIF/EFCP/EFCPInstance.h \
	src/DIF/EFCP/EFCPListeners.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCPTable/EFCPTable.h \
	src/DIF/EFCP/EFCPTable/EFCPTableEntry.h \
	src/DIF/EFCP/EFCP_defs.h \
	src/DIF/FA/FA.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAI.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAIListeners.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/FA/FAListeners.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RA.h \
	src/DIF/RA/RABase.h \
	src/DIF/RA/RAListeners.h \
	src/DIF/RMT/RMT.h \
	src/DIF/RMT/RMTBase.h \
	src/DIF/RMT/RMTListeners.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/src/DIF/FA/FABase.o: src/DIF/FA/FABase.cc \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h
$O/src/DIF/FA/FAI.o: src/DIF/FA/FAI.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	policies/DIF/FA/AllocateRetry/AllocateRetryBase.h \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/CongestionDescriptor.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/Delimiting/Delimiting.h \
	src/DIF/EFCP/DTCP/ControlPDU_m.h \
	src/DIF/EFCP/DTCP/DTCP.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTP.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCP.h \
	src/DIF/EFCP/EFCPInstance.h \
	src/DIF/EFCP/EFCPListeners.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCPTable/EFCPTable.h \
	src/DIF/EFCP/EFCPTable/EFCPTableEntry.h \
	src/DIF/EFCP/EFCP_defs.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAI.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAIListeners.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RA.h \
	src/DIF/RA/RABase.h \
	src/DIF/RA/RAListeners.h \
	src/DIF/RMT/RMT.h \
	src/DIF/RMT/RMTBase.h \
	src/DIF/RMT/RMTListeners.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/src/DIF/FA/FAIBase.o: src/DIF/FA/FAIBase.cc \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FAIBase.h
$O/src/DIF/FA/FAIListeners.o: src/DIF/FA/FAIListeners.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/FCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/LostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/NoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/NoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/RateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/RcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/ReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/ReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/SenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/SendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/TxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/InitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/RcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/SenderInactivityPolicyBase.h \
	policies/DIF/EFCP/EFCPPolicy.h \
	policies/DIF/FA/AllocateRetry/AllocateRetryBase.h \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/CongestionDescriptor.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/Data.h \
	src/Common/Data_m.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/Delimiting/Delimiting.h \
	src/DIF/EFCP/DTCP/ControlPDU_m.h \
	src/DIF/EFCP/DTCP/DTCP.h \
	src/DIF/EFCP/DTCP/DTCPState.h \
	src/DIF/EFCP/DTCP/DTCPTimers_m.h \
	src/DIF/EFCP/DTP/DTP.h \
	src/DIF/EFCP/DTP/DTPState.h \
	src/DIF/EFCP/DTP/DTPTimers_m.h \
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCP.h \
	src/DIF/EFCP/EFCPInstance.h \
	src/DIF/EFCP/EFCPListeners.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/EFCP/EFCPTable/EFCPTable.h \
	src/DIF/EFCP/EFCPTable/EFCPTableEntry.h \
	src/DIF/EFCP/EFCP_defs.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAI.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAIListeners.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RA.h \
	src/DIF/RA/RABase.h \
	src/DIF/RA/RAListeners.h \
	src/DIF/RMT/RMT.h \
	src/DIF/RMT/RMTBase.h \
	src/DIF/RMT/RMTListeners.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/src/DIF/FA/FAITable.o: src/DIF/FA/FAITable.cc \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h
$O/src/DIF/FA/FAITableEntry.o: src/DIF/FA/FAITableEntry.cc \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITableEntry.h
$O/src/DIF/FA/FAListeners.o: src/DIF/FA/FAListeners.cc \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/FA/FAListeners.h
$O/src/DIF/NSM/DirectoryForwardingTable.o: src/DIF/NSM/DirectoryForwardingTable.cc \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/DIF/NSM/DirectoryForwardingTable.h
$O/src/DIF/NSM/LocalDirectoryCache.o: src/DIF/NSM/LocalDirectoryCache.cc \
	src/DIF/NSM/LocalDirectoryCache.h
$O/src/DIF/NSM/NSM.o: src/DIF/NSM/NSM.cc \
	src/DIF/NSM/NSM.h
$O/src/DIF/RA/NM1FlowTable.o: src/DIF/RA/NM1FlowTable.cc \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/src/DIF/RA/NM1FlowTableItem.o: src/DIF/RA/NM1FlowTableItem.cc \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/src/DIF/RA/RA.o: src/DIF/RA/RA.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/PDUFG/IntPDUFG.h \
	policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/CongestionDescriptor.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/ModuleAccess.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RA.h \
	src/DIF/RA/RABase.h \
	src/DIF/RA/RAListeners.h \
	src/DIF/RMT/RMT.h \
	src/DIF/RMT/RMTBase.h \
	src/DIF/RMT/RMTListeners.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/src/DIF/RA/RABase.o: src/DIF/RA/RABase.cc \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RABase.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/src/DIF/RA/RAListeners.o: src/DIF/RA/RAListeners.cc \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RABase.h \
	src/DIF/RA/RAListeners.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/src/DIF/RIB/RIBd.o: src/DIF/RIB/RIBd.cc \
	policies/DIF/Routing/IntRoutingUpdate.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/CongestionDescriptor.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RIB/RIBd.h \
	src/DIF/RIB/RIBdBase.h \
	src/DIF/RIB/RIBdListeners.h
$O/src/DIF/RIB/RIBdBase.o: src/DIF/RIB/RIBdBase.cc \
	policies/DIF/Routing/IntRoutingUpdate.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/CongestionDescriptor.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RIB/RIBdBase.h
$O/src/DIF/RIB/RIBdListeners.o: src/DIF/RIB/RIBdListeners.cc \
	policies/DIF/Routing/IntRoutingUpdate.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/CongestionDescriptor.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RIB/RIBdBase.h \
	src/DIF/RIB/RIBdListeners.h
$O/src/DIF/RMT/RMT.o: src/DIF/RMT/RMT.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RABase.h \
	src/DIF/RMT/RMT.h \
	src/DIF/RMT/RMTBase.h \
	src/DIF/RMT/RMTListeners.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/src/DIF/RMT/RMTBase.o: src/DIF/RMT/RMTBase.cc \
	src/DIF/RMT/RMTBase.h
$O/src/DIF/RMT/RMTListeners.o: src/DIF/RMT/RMTListeners.cc \
	src/DIF/RMT/RMTBase.h \
	src/DIF/RMT/RMTListeners.h
$O/src/DIF/RMT/RMTModuleAllocator.o: src/DIF/RMT/RMTModuleAllocator.cc \
	policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	policies/DIF/RMT/Scheduler/RMTSchedulingBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/src/DIF/RMT/RMTPort.o: src/DIF/RMT/RMTPort.cc \
	policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/QoSReq.h \
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h
$O/src/DIF/RMT/RMTQueue.o: src/DIF/RMT/RMTQueue.cc \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/PDU.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/Common/RINASignals.h \
	src/DIF/EFCP/EFCPPolicySet.h \
	src/DIF/RMT/RMTQueue.h

