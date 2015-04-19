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
    -Iexamples/BigRandNet \
    -Iexamples/BigRandNet/results \
    -Iexamples/DC \
    -Iexamples/ExtendedPingTwoCSsSimple \
    -Iexamples/FatTreeTopology \
    -Iexamples/FatTreeTopologyPref \
    -Iexamples/SimpleRelay \
    -Iexamples/SimpleRelay/results \
    -Iexamples/SimpleRelayCongestion \
    -Iexamples/SimpleRelayCongestion/results \
    -Iexamples/SingleCS \
    -Iexamples/SmallNetRouting \
    -Iexamples/SmallNetRouting/results \
    -Iexamples/SmallNetwork \
    -Iexamples/SmallNetwork/results \
    -Iexamples/SmallNetwork2 \
    -Iexamples/SmallRandNet \
    -Iexamples/SmallRandNet/results \
    -Iexamples/TwoCSWithDelay \
    -Iexamples/TwoCSWithDelay/results \
    -Iexamples/TwoCSs \
    -Iexamples/TwoCSs/results \
    -Iexamples/TwoCSsSimple \
    -Iexamples/TwoCSsSimple/results \
    -Iexamples/randPrefNet \
    -Iexamples/treeBipart \
    -Ipolicies \
    -Ipolicies/DIF \
    -Ipolicies/DIF/EFCP \
    -Ipolicies/DIF/EFCP/DTCP \
    -Ipolicies/DIF/EFCP/DTCP/ECN \
    -Ipolicies/DIF/EFCP/DTCP/ECNSlowDown \
    -Ipolicies/DIF/EFCP/DTCP/FCOverrun \
    -Ipolicies/DIF/EFCP/DTCP/LostControlPDU \
    -Ipolicies/DIF/EFCP/DTCP/NoOverridePeak \
    -Ipolicies/DIF/EFCP/DTCP/NoRateSlowDown \
    -Ipolicies/DIF/EFCP/DTCP/RateReduction \
    -Ipolicies/DIF/EFCP/DTCP/RcvrAck \
    -Ipolicies/DIF/EFCP/DTCP/RcvrControlAck \
    -Ipolicies/DIF/EFCP/DTCP/RcvrFC \
    -Ipolicies/DIF/EFCP/DTCP/ReceivingFC \
    -Ipolicies/DIF/EFCP/DTCP/ReconcileFC \
    -Ipolicies/DIF/EFCP/DTCP/SenderAck \
    -Ipolicies/DIF/EFCP/DTCP/SendingAck \
    -Ipolicies/DIF/EFCP/DTCP/TxControl \
    -Ipolicies/DIF/EFCP/DTP \
    -Ipolicies/DIF/EFCP/DTP/InitialSeqNum \
    -Ipolicies/DIF/EFCP/DTP/RTTEstimator \
    -Ipolicies/DIF/EFCP/DTP/RcvrInactivity \
    -Ipolicies/DIF/EFCP/DTP/SenderInactivity \
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
    -Isrc/DIF/EFCP/policies \
    -Isrc/DIF/Enrollment \
    -Isrc/DIF/FA \
    -Isrc/DIF/NSM \
    -Isrc/DIF/RA \
    -Isrc/DIF/RIB \
    -Isrc/DIF/RMT \
    -Isrc/policies \
    -Isrc/policies/DAF \
    -Isrc/policies/DIF \
    -Isrc/policies/DIF/FA \
    -Isrc/policies/DIF/FA/AllocateRetry \
    -Isrc/policies/DIF/FA/AllocateRetry/LimitedRetries \
    -Isrc/policies/DIF/FA/NewFlowRequest \
    -Isrc/policies/DIF/FA/NewFlowRequest/QoSCubeComparer \
    -Isrc/policies/DIF/FA/NewFlowRequest/QoSCubeComparerMin \
    -Isrc/policies/DIF/RA \
    -Isrc/policies/DIF/RA/AddressComparator \
    -Isrc/policies/DIF/RA/AddressComparator/ExactMatch \
    -Isrc/policies/DIF/RA/AddressComparator/PrefixMatch \
    -Isrc/policies/DIF/RA/PDUFG \
    -Isrc/policies/DIF/RA/PDUFG/BiDomainGenerator \
    -Isrc/policies/DIF/RA/PDUFG/SimpleGenerator \
    -Isrc/policies/DIF/RA/PDUFG/SingleDomainGenerator \
    -Isrc/policies/DIF/RA/PDUFG/StaticGenerator \
    -Isrc/policies/DIF/RA/QueueAlloc \
    -Isrc/policies/DIF/RA/QueueAlloc/QueuePerNCU \
    -Isrc/policies/DIF/RA/QueueAlloc/QueuePerNFlow \
    -Isrc/policies/DIF/RA/QueueAlloc/QueuePerNQoS \
    -Isrc/policies/DIF/RA/QueueAlloc/SingleQueue \
    -Isrc/policies/DIF/RA/QueueIDGen \
    -Isrc/policies/DIF/RA/QueueIDGen/IDPerNCU \
    -Isrc/policies/DIF/RA/QueueIDGen/IDPerNFlow \
    -Isrc/policies/DIF/RA/QueueIDGen/IDPerNQoS \
    -Isrc/policies/DIF/RA/QueueIDGen/SingleID \
    -Isrc/policies/DIF/RMT \
    -Isrc/policies/DIF/RMT/MaxQueue \
    -Isrc/policies/DIF/RMT/MaxQueue/DLMaxQ \
    -Isrc/policies/DIF/RMT/MaxQueue/ECNMarker \
    -Isrc/policies/DIF/RMT/MaxQueue/REDDropper \
    -Isrc/policies/DIF/RMT/MaxQueue/ReadRateReducer \
    -Isrc/policies/DIF/RMT/MaxQueue/TailDrop \
    -Isrc/policies/DIF/RMT/MaxQueue/UpstreamNotifier \
    -Isrc/policies/DIF/RMT/Monitor \
    -Isrc/policies/DIF/RMT/Monitor/DLMonitor \
    -Isrc/policies/DIF/RMT/Monitor/REDMonitor \
    -Isrc/policies/DIF/RMT/Monitor/SimpleMonitor \
    -Isrc/policies/DIF/RMT/PDUForwarding \
    -Isrc/policies/DIF/RMT/PDUForwarding/DomainTable \
    -Isrc/policies/DIF/RMT/PDUForwarding/MiniTable \
    -Isrc/policies/DIF/RMT/PDUForwarding/SimpleTable \
    -Isrc/policies/DIF/RMT/Scheduler \
    -Isrc/policies/DIF/RMT/Scheduler/DL \
    -Isrc/policies/DIF/RMT/Scheduler/LongestQFirst \
    -Isrc/policies/DIF/Routing \
    -Isrc/policies/DIF/Routing/DomainRouting \
    -Isrc/policies/DIF/Routing/DomainRouting/DV \
    -Isrc/policies/DIF/Routing/DomainRouting/LS \
    -Isrc/policies/DIF/Routing/DummyRouting \
    -Isrc/policies/DIF/Routing/SimpleRouting \
    -Isrc/policies/DIF/Routing/SimpleRouting/SimpleDV \
    -Isrc/policies/DIF/Routing/SimpleRouting/SimpleLS

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
    $O/policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyDefault.o \
    $O/policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/FCOverrun/DTCPFCOverrunPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/LostControlPDU/DTCPLostControlPDUPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/NoOverridePeak/DTCPNoOverridePeakPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/NoRateSlowDown/DTCPNoRateSlowDownPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/RateReduction/DTCPRateReductionPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/RcvrAck/DTCPRcvrAckPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/RcvrControlAck/DTCPRcvrControlAckPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/RcvrFC/DTCPRcvrFCPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/ReceivingFC/DTCPReceivingFCPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/ReconcileFC/DTCPReconcileFCPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/SenderAck/DTCPSenderAckPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/SendingAck/DTCPSendingAckPolicyBase.o \
    $O/policies/DIF/EFCP/DTCP/TxControl/DTCPTxControlPolicyBase.o \
    $O/policies/DIF/EFCP/DTP/InitialSeqNum/DTPInitialSeqNumPolicyBase.o \
    $O/policies/DIF/EFCP/DTP/RTTEstimator/DTPRTTEstimatorPolicyBase.o \
    $O/policies/DIF/EFCP/DTP/RcvrInactivity/DTPRcvrInactivityPolicyBase.o \
    $O/policies/DIF/EFCP/DTP/SenderInactivity/DTPSenderInactivityPolicyBase.o \
    $O/src/Common/Utils.o \
    $O/src/Common/ConnectionId.o \
    $O/src/Common/CongestionDescriptor.o \
    $O/src/Common/Test.o \
    $O/src/Common/Policy.o \
    $O/src/Common/SDU.o \
    $O/src/Common/ModuleAccess.o \
    $O/src/Common/Address.o \
    $O/src/Common/Flow.o \
    $O/src/Common/RINASignals.o \
    $O/src/Common/SHA256.o \
    $O/src/Common/QoSCube.o \
    $O/src/Common/APN.o \
    $O/src/Common/APNamingInfo.o \
    $O/src/Common/Data.o \
    $O/src/Common/DAP.o \
    $O/src/Common/ExternConsts.o \
    $O/src/Common/PDU.o \
    $O/src/DAF/AE/AESender.o \
    $O/src/DAF/AE/AEBase.o \
    $O/src/DAF/AE/AEPing.o \
    $O/src/DAF/AE/AEListeners.o \
    $O/src/DAF/AE/AE.o \
    $O/src/DAF/AE/EFCPListeners.o \
    $O/src/DAF/AE/AEExtendedPing.o \
    $O/src/DAF/AE/AEStream.o \
    $O/src/DAF/CDAP/CDAPSplitter.o \
    $O/src/DAF/CDAP/CDAPListeners.o \
    $O/src/DAF/CDAP/CDAP.o \
    $O/src/DAF/CDAP/CDAPMsgLogEntry.o \
    $O/src/DAF/CDAP/CACEListeners.o \
    $O/src/DAF/CDAP/Auth.o \
    $O/src/DAF/CDAP/CDAPMsgLog.o \
    $O/src/DAF/CDAP/CACE.o \
    $O/src/DAF/CDAP/AuthListeners.o \
    $O/src/DAF/DA/NeighborTable.o \
    $O/src/DAF/DA/SearchTableEntry.o \
    $O/src/DAF/DA/Directory.o \
    $O/src/DAF/DA/DirectoryEntry.o \
    $O/src/DAF/DA/SearchTable.o \
    $O/src/DAF/DA/NamingInformationEntry.o \
    $O/src/DAF/DA/NamingInformation.o \
    $O/src/DAF/DA/NeighborTableEntry.o \
    $O/src/DAF/DA/DA.o \
    $O/src/DAF/IRM/IRM.o \
    $O/src/DAF/IRM/ConnectionTableEntry.o \
    $O/src/DAF/IRM/IRMListeners.o \
    $O/src/DAF/IRM/ConnectionTable.o \
    $O/src/DIF/Delimiting/Delimiting.o \
    $O/src/DIF/EFCP/EFCPInstance.o \
    $O/src/DIF/EFCP/EFCP.o \
    $O/src/DIF/EFCP/DTCP/DTCPState.o \
    $O/src/DIF/EFCP/DTCP/DTCP.o \
    $O/src/DIF/EFCP/DTCP/RXControl.o \
    $O/src/DIF/EFCP/DTP/DumbGate.o \
    $O/src/DIF/EFCP/DTP/DataTransferPDU.o \
    $O/src/DIF/EFCP/DTP/DTP.o \
    $O/src/DIF/EFCP/DTP/UserDataField.o \
    $O/src/DIF/EFCP/DTP/DTPState.o \
    $O/src/DIF/EFCP/DTP/PushBackChannel.o \
    $O/src/DIF/EFCP/EFCPTable/EFCPTableEntry.o \
    $O/src/DIF/EFCP/EFCPTable/EFCPTable.o \
    $O/src/DIF/Enrollment/Enrollment.o \
    $O/src/DIF/FA/FAITable.o \
    $O/src/DIF/FA/FAListeners.o \
    $O/src/DIF/FA/FAI.o \
    $O/src/DIF/FA/FA.o \
    $O/src/DIF/FA/FAIBase.o \
    $O/src/DIF/FA/FAIListeners.o \
    $O/src/DIF/FA/FABase.o \
    $O/src/DIF/FA/FAITableEntry.o \
    $O/src/DIF/NSM/NSM.o \
    $O/src/DIF/NSM/LocalDirectoryCache.o \
    $O/src/DIF/NSM/DirectoryForwardingTable.o \
    $O/src/DIF/RA/QueueAllocBase.o \
    $O/src/DIF/RA/RA.o \
    $O/src/DIF/RA/RABase.o \
    $O/src/DIF/RA/AddressComparatorBase.o \
    $O/src/DIF/RA/NM1FlowTableItem.o \
    $O/src/DIF/RA/RAListeners.o \
    $O/src/DIF/RA/QueueIDGenBase.o \
    $O/src/DIF/RA/NM1FlowTable.o \
    $O/src/DIF/RIB/RIBd.o \
    $O/src/DIF/RIB/RIBdListeners.o \
    $O/src/DIF/RIB/RIBdBase.o \
    $O/src/DIF/RMT/RMTListeners.o \
    $O/src/DIF/RMT/RMTSchedulingBase.o \
    $O/src/DIF/RMT/RMTModuleAllocator.o \
    $O/src/DIF/RMT/RMTQueue.o \
    $O/src/DIF/RMT/RMTPort.o \
    $O/src/DIF/RMT/RMT.o \
    $O/src/DIF/RMT/RMTQMonitorBase.o \
    $O/src/DIF/RMT/RMTMaxQBase.o \
    $O/src/DIF/RMT/RMTBase.o \
    $O/src/policies/DIF/FA/AllocateRetry/AllocateRetryBase.o \
    $O/src/policies/DIF/FA/AllocateRetry/LimitedRetries/LimitedRetries.o \
    $O/src/policies/DIF/FA/NewFlowRequest/NewFlowRequestBase.o \
    $O/src/policies/DIF/FA/NewFlowRequest/QoSCubeComparer/QoSCubeComparer.o \
    $O/src/policies/DIF/FA/NewFlowRequest/QoSCubeComparerMin/QoSCubeComparerMin.o \
    $O/src/policies/DIF/RA/AddressComparator/ExactMatch/ExactMatch.o \
    $O/src/policies/DIF/RA/AddressComparator/PrefixMatch/PrefixMatch.o \
    $O/src/policies/DIF/RA/PDUFG/PDUFGNeighbor.o \
    $O/src/policies/DIF/RA/PDUFG/IntBbPDUFG.o \
    $O/src/policies/DIF/RA/PDUFG/IntPDUFG.o \
    $O/src/policies/DIF/RA/PDUFG/BiDomainGenerator/BiDomainGenerator.o \
    $O/src/policies/DIF/RA/PDUFG/SimpleGenerator/SimpleGenerator.o \
    $O/src/policies/DIF/RA/PDUFG/SingleDomainGenerator/SingleDomainGenerator.o \
    $O/src/policies/DIF/RA/PDUFG/StaticGenerator/StaticGenerator.o \
    $O/src/policies/DIF/RA/QueueAlloc/QueuePerNCU/QueuePerNCU.o \
    $O/src/policies/DIF/RA/QueueAlloc/QueuePerNFlow/QueuePerNFlow.o \
    $O/src/policies/DIF/RA/QueueAlloc/QueuePerNQoS/QueuePerNQoS.o \
    $O/src/policies/DIF/RA/QueueAlloc/SingleQueue/SingleQueue.o \
    $O/src/policies/DIF/RA/QueueIDGen/IDPerNCU/IDPerNCU.o \
    $O/src/policies/DIF/RA/QueueIDGen/IDPerNFlow/IDPerNFlow.o \
    $O/src/policies/DIF/RA/QueueIDGen/IDPerNQoS/IDPerNQoS.o \
    $O/src/policies/DIF/RA/QueueIDGen/SingleID/SingleID.o \
    $O/src/policies/DIF/RMT/MaxQueue/DLMaxQ/DLMaxQ.o \
    $O/src/policies/DIF/RMT/MaxQueue/ECNMarker/ECNMarker.o \
    $O/src/policies/DIF/RMT/MaxQueue/REDDropper/REDDropper.o \
    $O/src/policies/DIF/RMT/MaxQueue/ReadRateReducer/ReadRateReducer.o \
    $O/src/policies/DIF/RMT/MaxQueue/TailDrop/TailDrop.o \
    $O/src/policies/DIF/RMT/MaxQueue/UpstreamNotifier/UpstreamNotifier.o \
    $O/src/policies/DIF/RMT/Monitor/DLMonitor/DLMonitor.o \
    $O/src/policies/DIF/RMT/Monitor/REDMonitor/REDMonitor.o \
    $O/src/policies/DIF/RMT/Monitor/SimpleMonitor/SimpleMonitor.o \
    $O/src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.o \
    $O/src/policies/DIF/RMT/PDUForwarding/DomainTable/DomainTable.o \
    $O/src/policies/DIF/RMT/PDUForwarding/MiniTable/MiniTable.o \
    $O/src/policies/DIF/RMT/PDUForwarding/SimpleTable/SimpleTable.o \
    $O/src/policies/DIF/RMT/Scheduler/DL/DL.o \
    $O/src/policies/DIF/RMT/Scheduler/LongestQFirst/LongestQFirst.o \
    $O/src/policies/DIF/Routing/IntRouting.o \
    $O/src/policies/DIF/Routing/IntRoutingUpdate.o \
    $O/src/policies/DIF/Routing/IntBbRouting.o \
    $O/src/policies/DIF/Routing/DomainRouting/rModule.o \
    $O/src/policies/DIF/Routing/DomainRouting/Routing.o \
    $O/src/policies/DIF/Routing/DomainRouting/DV/DV.o \
    $O/src/policies/DIF/Routing/DomainRouting/LS/LS.o \
    $O/src/policies/DIF/Routing/DummyRouting/DummyRouting.o \
    $O/src/policies/DIF/Routing/SimpleRouting/SimpleDV/SimpleDV.o \
    $O/src/policies/DIF/Routing/SimpleRouting/SimpleLS/SimpleLS.o \
    $O/src/Common/SDU_m.o \
    $O/src/Common/Data_m.o \
    $O/src/Common/PDU_m.o \
    $O/src/DAF/CDAP/CDAPMessage_m.o \
    $O/src/DIF/EFCP/DTCP/DTCPTimers_m.o \
    $O/src/DIF/EFCP/DTCP/ControlPDU_m.o \
    $O/src/DIF/EFCP/DTP/DataTransferPDU_m.o \
    $O/src/DIF/EFCP/DTP/DTPTimers_m.o

# Message files
MSGFILES = \
    src/Common/SDU.msg \
    src/Common/Data.msg \
    src/Common/PDU.msg \
    src/DAF/CDAP/CDAPMessage.msg \
    src/DIF/EFCP/DTCP/DTCPTimers.msg \
    src/DIF/EFCP/DTCP/ControlPDU.msg \
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
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

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
	$(Q)-rm -f examples/BigRandNet/*_m.cc examples/BigRandNet/*_m.h
	$(Q)-rm -f examples/BigRandNet/results/*_m.cc examples/BigRandNet/results/*_m.h
	$(Q)-rm -f examples/DC/*_m.cc examples/DC/*_m.h
	$(Q)-rm -f examples/ExtendedPingTwoCSsSimple/*_m.cc examples/ExtendedPingTwoCSsSimple/*_m.h
	$(Q)-rm -f examples/FatTreeTopology/*_m.cc examples/FatTreeTopology/*_m.h
	$(Q)-rm -f examples/FatTreeTopologyPref/*_m.cc examples/FatTreeTopologyPref/*_m.h
	$(Q)-rm -f examples/SimpleRelay/*_m.cc examples/SimpleRelay/*_m.h
	$(Q)-rm -f examples/SimpleRelay/results/*_m.cc examples/SimpleRelay/results/*_m.h
	$(Q)-rm -f examples/SimpleRelayCongestion/*_m.cc examples/SimpleRelayCongestion/*_m.h
	$(Q)-rm -f examples/SimpleRelayCongestion/results/*_m.cc examples/SimpleRelayCongestion/results/*_m.h
	$(Q)-rm -f examples/SingleCS/*_m.cc examples/SingleCS/*_m.h
	$(Q)-rm -f examples/SmallNetRouting/*_m.cc examples/SmallNetRouting/*_m.h
	$(Q)-rm -f examples/SmallNetRouting/results/*_m.cc examples/SmallNetRouting/results/*_m.h
	$(Q)-rm -f examples/SmallNetwork/*_m.cc examples/SmallNetwork/*_m.h
	$(Q)-rm -f examples/SmallNetwork/results/*_m.cc examples/SmallNetwork/results/*_m.h
	$(Q)-rm -f examples/SmallNetwork2/*_m.cc examples/SmallNetwork2/*_m.h
	$(Q)-rm -f examples/SmallRandNet/*_m.cc examples/SmallRandNet/*_m.h
	$(Q)-rm -f examples/SmallRandNet/results/*_m.cc examples/SmallRandNet/results/*_m.h
	$(Q)-rm -f examples/TwoCSWithDelay/*_m.cc examples/TwoCSWithDelay/*_m.h
	$(Q)-rm -f examples/TwoCSWithDelay/results/*_m.cc examples/TwoCSWithDelay/results/*_m.h
	$(Q)-rm -f examples/TwoCSs/*_m.cc examples/TwoCSs/*_m.h
	$(Q)-rm -f examples/TwoCSs/results/*_m.cc examples/TwoCSs/results/*_m.h
	$(Q)-rm -f examples/TwoCSsSimple/*_m.cc examples/TwoCSsSimple/*_m.h
	$(Q)-rm -f examples/TwoCSsSimple/results/*_m.cc examples/TwoCSsSimple/results/*_m.h
	$(Q)-rm -f examples/randPrefNet/*_m.cc examples/randPrefNet/*_m.h
	$(Q)-rm -f examples/treeBipart/*_m.cc examples/treeBipart/*_m.h
	$(Q)-rm -f policies/*_m.cc policies/*_m.h
	$(Q)-rm -f policies/DIF/*_m.cc policies/DIF/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/*_m.cc policies/DIF/EFCP/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/*_m.cc policies/DIF/EFCP/DTCP/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/ECN/*_m.cc policies/DIF/EFCP/DTCP/ECN/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/ECNSlowDown/*_m.cc policies/DIF/EFCP/DTCP/ECNSlowDown/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/FCOverrun/*_m.cc policies/DIF/EFCP/DTCP/FCOverrun/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/LostControlPDU/*_m.cc policies/DIF/EFCP/DTCP/LostControlPDU/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/NoOverridePeak/*_m.cc policies/DIF/EFCP/DTCP/NoOverridePeak/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/NoRateSlowDown/*_m.cc policies/DIF/EFCP/DTCP/NoRateSlowDown/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/RateReduction/*_m.cc policies/DIF/EFCP/DTCP/RateReduction/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/RcvrAck/*_m.cc policies/DIF/EFCP/DTCP/RcvrAck/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/RcvrControlAck/*_m.cc policies/DIF/EFCP/DTCP/RcvrControlAck/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/RcvrFC/*_m.cc policies/DIF/EFCP/DTCP/RcvrFC/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/ReceivingFC/*_m.cc policies/DIF/EFCP/DTCP/ReceivingFC/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/ReconcileFC/*_m.cc policies/DIF/EFCP/DTCP/ReconcileFC/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/SenderAck/*_m.cc policies/DIF/EFCP/DTCP/SenderAck/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/SendingAck/*_m.cc policies/DIF/EFCP/DTCP/SendingAck/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTCP/TxControl/*_m.cc policies/DIF/EFCP/DTCP/TxControl/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTP/*_m.cc policies/DIF/EFCP/DTP/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTP/InitialSeqNum/*_m.cc policies/DIF/EFCP/DTP/InitialSeqNum/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTP/RTTEstimator/*_m.cc policies/DIF/EFCP/DTP/RTTEstimator/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTP/RcvrInactivity/*_m.cc policies/DIF/EFCP/DTP/RcvrInactivity/*_m.h
	$(Q)-rm -f policies/DIF/EFCP/DTP/SenderInactivity/*_m.cc policies/DIF/EFCP/DTP/SenderInactivity/*_m.h
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
	$(Q)-rm -f src/DIF/EFCP/policies/*_m.cc src/DIF/EFCP/policies/*_m.h
	$(Q)-rm -f src/DIF/Enrollment/*_m.cc src/DIF/Enrollment/*_m.h
	$(Q)-rm -f src/DIF/FA/*_m.cc src/DIF/FA/*_m.h
	$(Q)-rm -f src/DIF/NSM/*_m.cc src/DIF/NSM/*_m.h
	$(Q)-rm -f src/DIF/RA/*_m.cc src/DIF/RA/*_m.h
	$(Q)-rm -f src/DIF/RIB/*_m.cc src/DIF/RIB/*_m.h
	$(Q)-rm -f src/DIF/RMT/*_m.cc src/DIF/RMT/*_m.h
	$(Q)-rm -f src/policies/*_m.cc src/policies/*_m.h
	$(Q)-rm -f src/policies/DAF/*_m.cc src/policies/DAF/*_m.h
	$(Q)-rm -f src/policies/DIF/*_m.cc src/policies/DIF/*_m.h
	$(Q)-rm -f src/policies/DIF/FA/*_m.cc src/policies/DIF/FA/*_m.h
	$(Q)-rm -f src/policies/DIF/FA/AllocateRetry/*_m.cc src/policies/DIF/FA/AllocateRetry/*_m.h
	$(Q)-rm -f src/policies/DIF/FA/AllocateRetry/LimitedRetries/*_m.cc src/policies/DIF/FA/AllocateRetry/LimitedRetries/*_m.h
	$(Q)-rm -f src/policies/DIF/FA/NewFlowRequest/*_m.cc src/policies/DIF/FA/NewFlowRequest/*_m.h
	$(Q)-rm -f src/policies/DIF/FA/NewFlowRequest/QoSCubeComparer/*_m.cc src/policies/DIF/FA/NewFlowRequest/QoSCubeComparer/*_m.h
	$(Q)-rm -f src/policies/DIF/FA/NewFlowRequest/QoSCubeComparerMin/*_m.cc src/policies/DIF/FA/NewFlowRequest/QoSCubeComparerMin/*_m.h
	$(Q)-rm -f src/policies/DIF/RA/*_m.cc src/policies/DIF/RA/*_m.h
	$(Q)-rm -f src/policies/DIF/RA/AddressComparator/*_m.cc src/policies/DIF/RA/AddressComparator/*_m.h
	$(Q)-rm -f src/policies/DIF/RA/AddressComparator/ExactMatch/*_m.cc src/policies/DIF/RA/AddressComparator/ExactMatch/*_m.h
	$(Q)-rm -f src/policies/DIF/RA/AddressComparator/PrefixMatch/*_m.cc src/policies/DIF/RA/AddressComparator/PrefixMatch/*_m.h
	$(Q)-rm -f src/policies/DIF/RA/PDUFG/*_m.cc src/policies/DIF/RA/PDUFG/*_m.h
	$(Q)-rm -f src/policies/DIF/RA/PDUFG/BiDomainGenerator/*_m.cc src/policies/DIF/RA/PDUFG/BiDomainGenerator/*_m.h
	$(Q)-rm -f src/policies/DIF/RA/PDUFG/SimpleGenerator/*_m.cc src/policies/DIF/RA/PDUFG/SimpleGenerator/*_m.h
	$(Q)-rm -f src/policies/DIF/RA/PDUFG/SingleDomainGenerator/*_m.cc src/policies/DIF/RA/PDUFG/SingleDomainGenerator/*_m.h
	$(Q)-rm -f src/policies/DIF/RA/PDUFG/StaticGenerator/*_m.cc src/policies/DIF/RA/PDUFG/StaticGenerator/*_m.h
	$(Q)-rm -f src/policies/DIF/RA/QueueAlloc/*_m.cc src/policies/DIF/RA/QueueAlloc/*_m.h
	$(Q)-rm -f src/policies/DIF/RA/QueueAlloc/QueuePerNCU/*_m.cc src/policies/DIF/RA/QueueAlloc/QueuePerNCU/*_m.h
	$(Q)-rm -f src/policies/DIF/RA/QueueAlloc/QueuePerNFlow/*_m.cc src/policies/DIF/RA/QueueAlloc/QueuePerNFlow/*_m.h
	$(Q)-rm -f src/policies/DIF/RA/QueueAlloc/QueuePerNQoS/*_m.cc src/policies/DIF/RA/QueueAlloc/QueuePerNQoS/*_m.h
	$(Q)-rm -f src/policies/DIF/RA/QueueAlloc/SingleQueue/*_m.cc src/policies/DIF/RA/QueueAlloc/SingleQueue/*_m.h
	$(Q)-rm -f src/policies/DIF/RA/QueueIDGen/*_m.cc src/policies/DIF/RA/QueueIDGen/*_m.h
	$(Q)-rm -f src/policies/DIF/RA/QueueIDGen/IDPerNCU/*_m.cc src/policies/DIF/RA/QueueIDGen/IDPerNCU/*_m.h
	$(Q)-rm -f src/policies/DIF/RA/QueueIDGen/IDPerNFlow/*_m.cc src/policies/DIF/RA/QueueIDGen/IDPerNFlow/*_m.h
	$(Q)-rm -f src/policies/DIF/RA/QueueIDGen/IDPerNQoS/*_m.cc src/policies/DIF/RA/QueueIDGen/IDPerNQoS/*_m.h
	$(Q)-rm -f src/policies/DIF/RA/QueueIDGen/SingleID/*_m.cc src/policies/DIF/RA/QueueIDGen/SingleID/*_m.h
	$(Q)-rm -f src/policies/DIF/RMT/*_m.cc src/policies/DIF/RMT/*_m.h
	$(Q)-rm -f src/policies/DIF/RMT/MaxQueue/*_m.cc src/policies/DIF/RMT/MaxQueue/*_m.h
	$(Q)-rm -f src/policies/DIF/RMT/MaxQueue/DLMaxQ/*_m.cc src/policies/DIF/RMT/MaxQueue/DLMaxQ/*_m.h
	$(Q)-rm -f src/policies/DIF/RMT/MaxQueue/ECNMarker/*_m.cc src/policies/DIF/RMT/MaxQueue/ECNMarker/*_m.h
	$(Q)-rm -f src/policies/DIF/RMT/MaxQueue/REDDropper/*_m.cc src/policies/DIF/RMT/MaxQueue/REDDropper/*_m.h
	$(Q)-rm -f src/policies/DIF/RMT/MaxQueue/ReadRateReducer/*_m.cc src/policies/DIF/RMT/MaxQueue/ReadRateReducer/*_m.h
	$(Q)-rm -f src/policies/DIF/RMT/MaxQueue/TailDrop/*_m.cc src/policies/DIF/RMT/MaxQueue/TailDrop/*_m.h
	$(Q)-rm -f src/policies/DIF/RMT/MaxQueue/UpstreamNotifier/*_m.cc src/policies/DIF/RMT/MaxQueue/UpstreamNotifier/*_m.h
	$(Q)-rm -f src/policies/DIF/RMT/Monitor/*_m.cc src/policies/DIF/RMT/Monitor/*_m.h
	$(Q)-rm -f src/policies/DIF/RMT/Monitor/DLMonitor/*_m.cc src/policies/DIF/RMT/Monitor/DLMonitor/*_m.h
	$(Q)-rm -f src/policies/DIF/RMT/Monitor/REDMonitor/*_m.cc src/policies/DIF/RMT/Monitor/REDMonitor/*_m.h
	$(Q)-rm -f src/policies/DIF/RMT/Monitor/SimpleMonitor/*_m.cc src/policies/DIF/RMT/Monitor/SimpleMonitor/*_m.h
	$(Q)-rm -f src/policies/DIF/RMT/PDUForwarding/*_m.cc src/policies/DIF/RMT/PDUForwarding/*_m.h
	$(Q)-rm -f src/policies/DIF/RMT/PDUForwarding/DomainTable/*_m.cc src/policies/DIF/RMT/PDUForwarding/DomainTable/*_m.h
	$(Q)-rm -f src/policies/DIF/RMT/PDUForwarding/MiniTable/*_m.cc src/policies/DIF/RMT/PDUForwarding/MiniTable/*_m.h
	$(Q)-rm -f src/policies/DIF/RMT/PDUForwarding/SimpleTable/*_m.cc src/policies/DIF/RMT/PDUForwarding/SimpleTable/*_m.h
	$(Q)-rm -f src/policies/DIF/RMT/Scheduler/*_m.cc src/policies/DIF/RMT/Scheduler/*_m.h
	$(Q)-rm -f src/policies/DIF/RMT/Scheduler/DL/*_m.cc src/policies/DIF/RMT/Scheduler/DL/*_m.h
	$(Q)-rm -f src/policies/DIF/RMT/Scheduler/LongestQFirst/*_m.cc src/policies/DIF/RMT/Scheduler/LongestQFirst/*_m.h
	$(Q)-rm -f src/policies/DIF/Routing/*_m.cc src/policies/DIF/Routing/*_m.h
	$(Q)-rm -f src/policies/DIF/Routing/DomainRouting/*_m.cc src/policies/DIF/Routing/DomainRouting/*_m.h
	$(Q)-rm -f src/policies/DIF/Routing/DomainRouting/DV/*_m.cc src/policies/DIF/Routing/DomainRouting/DV/*_m.h
	$(Q)-rm -f src/policies/DIF/Routing/DomainRouting/LS/*_m.cc src/policies/DIF/Routing/DomainRouting/LS/*_m.h
	$(Q)-rm -f src/policies/DIF/Routing/DummyRouting/*_m.cc src/policies/DIF/Routing/DummyRouting/*_m.h
	$(Q)-rm -f src/policies/DIF/Routing/SimpleRouting/*_m.cc src/policies/DIF/Routing/SimpleRouting/*_m.h
	$(Q)-rm -f src/policies/DIF/Routing/SimpleRouting/SimpleDV/*_m.cc src/policies/DIF/Routing/SimpleRouting/SimpleDV/*_m.h
	$(Q)-rm -f src/policies/DIF/Routing/SimpleRouting/SimpleLS/*_m.cc src/policies/DIF/Routing/SimpleRouting/SimpleLS/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc examples/*.cc examples/AllNodes/*.cc examples/BigRandNet/*.cc examples/BigRandNet/results/*.cc examples/DC/*.cc examples/ExtendedPingTwoCSsSimple/*.cc examples/FatTreeTopology/*.cc examples/FatTreeTopologyPref/*.cc examples/SimpleRelay/*.cc examples/SimpleRelay/results/*.cc examples/SimpleRelayCongestion/*.cc examples/SimpleRelayCongestion/results/*.cc examples/SingleCS/*.cc examples/SmallNetRouting/*.cc examples/SmallNetRouting/results/*.cc examples/SmallNetwork/*.cc examples/SmallNetwork/results/*.cc examples/SmallNetwork2/*.cc examples/SmallRandNet/*.cc examples/SmallRandNet/results/*.cc examples/TwoCSWithDelay/*.cc examples/TwoCSWithDelay/results/*.cc examples/TwoCSs/*.cc examples/TwoCSs/results/*.cc examples/TwoCSsSimple/*.cc examples/TwoCSsSimple/results/*.cc examples/randPrefNet/*.cc examples/treeBipart/*.cc policies/*.cc policies/DIF/*.cc policies/DIF/EFCP/*.cc policies/DIF/EFCP/DTCP/*.cc policies/DIF/EFCP/DTCP/ECN/*.cc policies/DIF/EFCP/DTCP/ECNSlowDown/*.cc policies/DIF/EFCP/DTCP/FCOverrun/*.cc policies/DIF/EFCP/DTCP/LostControlPDU/*.cc policies/DIF/EFCP/DTCP/NoOverridePeak/*.cc policies/DIF/EFCP/DTCP/NoRateSlowDown/*.cc policies/DIF/EFCP/DTCP/RateReduction/*.cc policies/DIF/EFCP/DTCP/RcvrAck/*.cc policies/DIF/EFCP/DTCP/RcvrControlAck/*.cc policies/DIF/EFCP/DTCP/RcvrFC/*.cc policies/DIF/EFCP/DTCP/ReceivingFC/*.cc policies/DIF/EFCP/DTCP/ReconcileFC/*.cc policies/DIF/EFCP/DTCP/SenderAck/*.cc policies/DIF/EFCP/DTCP/SendingAck/*.cc policies/DIF/EFCP/DTCP/TxControl/*.cc policies/DIF/EFCP/DTP/*.cc policies/DIF/EFCP/DTP/InitialSeqNum/*.cc policies/DIF/EFCP/DTP/RTTEstimator/*.cc policies/DIF/EFCP/DTP/RcvrInactivity/*.cc policies/DIF/EFCP/DTP/SenderInactivity/*.cc scripts/*.cc src/*.cc src/CS/*.cc src/Common/*.cc src/DAF/*.cc src/DAF/AE/*.cc src/DAF/CDAP/*.cc src/DAF/DA/*.cc src/DAF/IRM/*.cc src/DIF/*.cc src/DIF/Delimiting/*.cc src/DIF/EFCP/*.cc src/DIF/EFCP/DTCP/*.cc src/DIF/EFCP/DTP/*.cc src/DIF/EFCP/EFCPTable/*.cc src/DIF/EFCP/policies/*.cc src/DIF/Enrollment/*.cc src/DIF/FA/*.cc src/DIF/NSM/*.cc src/DIF/RA/*.cc src/DIF/RIB/*.cc src/DIF/RMT/*.cc src/policies/*.cc src/policies/DAF/*.cc src/policies/DIF/*.cc src/policies/DIF/FA/*.cc src/policies/DIF/FA/AllocateRetry/*.cc src/policies/DIF/FA/AllocateRetry/LimitedRetries/*.cc src/policies/DIF/FA/NewFlowRequest/*.cc src/policies/DIF/FA/NewFlowRequest/QoSCubeComparer/*.cc src/policies/DIF/FA/NewFlowRequest/QoSCubeComparerMin/*.cc src/policies/DIF/RA/*.cc src/policies/DIF/RA/AddressComparator/*.cc src/policies/DIF/RA/AddressComparator/ExactMatch/*.cc src/policies/DIF/RA/AddressComparator/PrefixMatch/*.cc src/policies/DIF/RA/PDUFG/*.cc src/policies/DIF/RA/PDUFG/BiDomainGenerator/*.cc src/policies/DIF/RA/PDUFG/SimpleGenerator/*.cc src/policies/DIF/RA/PDUFG/SingleDomainGenerator/*.cc src/policies/DIF/RA/PDUFG/StaticGenerator/*.cc src/policies/DIF/RA/QueueAlloc/*.cc src/policies/DIF/RA/QueueAlloc/QueuePerNCU/*.cc src/policies/DIF/RA/QueueAlloc/QueuePerNFlow/*.cc src/policies/DIF/RA/QueueAlloc/QueuePerNQoS/*.cc src/policies/DIF/RA/QueueAlloc/SingleQueue/*.cc src/policies/DIF/RA/QueueIDGen/*.cc src/policies/DIF/RA/QueueIDGen/IDPerNCU/*.cc src/policies/DIF/RA/QueueIDGen/IDPerNFlow/*.cc src/policies/DIF/RA/QueueIDGen/IDPerNQoS/*.cc src/policies/DIF/RA/QueueIDGen/SingleID/*.cc src/policies/DIF/RMT/*.cc src/policies/DIF/RMT/MaxQueue/*.cc src/policies/DIF/RMT/MaxQueue/DLMaxQ/*.cc src/policies/DIF/RMT/MaxQueue/ECNMarker/*.cc src/policies/DIF/RMT/MaxQueue/REDDropper/*.cc src/policies/DIF/RMT/MaxQueue/ReadRateReducer/*.cc src/policies/DIF/RMT/MaxQueue/TailDrop/*.cc src/policies/DIF/RMT/MaxQueue/UpstreamNotifier/*.cc src/policies/DIF/RMT/Monitor/*.cc src/policies/DIF/RMT/Monitor/DLMonitor/*.cc src/policies/DIF/RMT/Monitor/REDMonitor/*.cc src/policies/DIF/RMT/Monitor/SimpleMonitor/*.cc src/policies/DIF/RMT/PDUForwarding/*.cc src/policies/DIF/RMT/PDUForwarding/DomainTable/*.cc src/policies/DIF/RMT/PDUForwarding/MiniTable/*.cc src/policies/DIF/RMT/PDUForwarding/SimpleTable/*.cc src/policies/DIF/RMT/Scheduler/*.cc src/policies/DIF/RMT/Scheduler/DL/*.cc src/policies/DIF/RMT/Scheduler/LongestQFirst/*.cc src/policies/DIF/Routing/*.cc src/policies/DIF/Routing/DomainRouting/*.cc src/policies/DIF/Routing/DomainRouting/DV/*.cc src/policies/DIF/Routing/DomainRouting/LS/*.cc src/policies/DIF/Routing/DummyRouting/*.cc src/policies/DIF/Routing/SimpleRouting/*.cc src/policies/DIF/Routing/SimpleRouting/SimpleDV/*.cc src/policies/DIF/Routing/SimpleRouting/SimpleLS/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
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
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
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
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
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
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/FCOverrun/DTCPFCOverrunPolicyBase.o: policies/DIF/EFCP/DTCP/FCOverrun/DTCPFCOverrunPolicyBase.cc \
	policies/DIF/EFCP/DTCP/FCOverrun/DTCPFCOverrunPolicyBase.h \
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
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/LostControlPDU/DTCPLostControlPDUPolicyBase.o: policies/DIF/EFCP/DTCP/LostControlPDU/DTCPLostControlPDUPolicyBase.cc \
	policies/DIF/EFCP/DTCP/LostControlPDU/DTCPLostControlPDUPolicyBase.h \
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
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/NoOverridePeak/DTCPNoOverridePeakPolicyBase.o: policies/DIF/EFCP/DTCP/NoOverridePeak/DTCPNoOverridePeakPolicyBase.cc \
	policies/DIF/EFCP/DTCP/NoOverridePeak/DTCPNoOverridePeakPolicyBase.h \
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
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/NoRateSlowDown/DTCPNoRateSlowDownPolicyBase.o: policies/DIF/EFCP/DTCP/NoRateSlowDown/DTCPNoRateSlowDownPolicyBase.cc \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/DTCPNoRateSlowDownPolicyBase.h \
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
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/RateReduction/DTCPRateReductionPolicyBase.o: policies/DIF/EFCP/DTCP/RateReduction/DTCPRateReductionPolicyBase.cc \
	policies/DIF/EFCP/DTCP/RateReduction/DTCPRateReductionPolicyBase.h \
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
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/RcvrAck/DTCPRcvrAckPolicyBase.o: policies/DIF/EFCP/DTCP/RcvrAck/DTCPRcvrAckPolicyBase.cc \
	policies/DIF/EFCP/DTCP/RcvrAck/DTCPRcvrAckPolicyBase.h \
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
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/RcvrControlAck/DTCPRcvrControlAckPolicyBase.o: policies/DIF/EFCP/DTCP/RcvrControlAck/DTCPRcvrControlAckPolicyBase.cc \
	policies/DIF/EFCP/DTCP/RcvrControlAck/DTCPRcvrControlAckPolicyBase.h \
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
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/RcvrFC/DTCPRcvrFCPolicyBase.o: policies/DIF/EFCP/DTCP/RcvrFC/DTCPRcvrFCPolicyBase.cc \
	policies/DIF/EFCP/DTCP/RcvrFC/DTCPRcvrFCPolicyBase.h \
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
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/ReceivingFC/DTCPReceivingFCPolicyBase.o: policies/DIF/EFCP/DTCP/ReceivingFC/DTCPReceivingFCPolicyBase.cc \
	policies/DIF/EFCP/DTCP/ReceivingFC/DTCPReceivingFCPolicyBase.h \
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
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/ReconcileFC/DTCPReconcileFCPolicyBase.o: policies/DIF/EFCP/DTCP/ReconcileFC/DTCPReconcileFCPolicyBase.cc \
	policies/DIF/EFCP/DTCP/ReconcileFC/DTCPReconcileFCPolicyBase.h \
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
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/SenderAck/DTCPSenderAckPolicyBase.o: policies/DIF/EFCP/DTCP/SenderAck/DTCPSenderAckPolicyBase.cc \
	policies/DIF/EFCP/DTCP/SenderAck/DTCPSenderAckPolicyBase.h \
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
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/SendingAck/DTCPSendingAckPolicyBase.o: policies/DIF/EFCP/DTCP/SendingAck/DTCPSendingAckPolicyBase.cc \
	policies/DIF/EFCP/DTCP/SendingAck/DTCPSendingAckPolicyBase.h \
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
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTCP/TxControl/DTCPTxControlPolicyBase.o: policies/DIF/EFCP/DTCP/TxControl/DTCPTxControlPolicyBase.cc \
	policies/DIF/EFCP/DTCP/TxControl/DTCPTxControlPolicyBase.h \
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
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTP/InitialSeqNum/DTPInitialSeqNumPolicyBase.o: policies/DIF/EFCP/DTP/InitialSeqNum/DTPInitialSeqNumPolicyBase.cc \
	policies/DIF/EFCP/DTP/InitialSeqNum/DTPInitialSeqNumPolicyBase.h \
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
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTP/RTTEstimator/DTPRTTEstimatorPolicyBase.o: policies/DIF/EFCP/DTP/RTTEstimator/DTPRTTEstimatorPolicyBase.cc \
	policies/DIF/EFCP/DTP/RTTEstimator/DTPRTTEstimatorPolicyBase.h \
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
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTP/RcvrInactivity/DTPRcvrInactivityPolicyBase.o: policies/DIF/EFCP/DTP/RcvrInactivity/DTPRcvrInactivityPolicyBase.cc \
	policies/DIF/EFCP/DTP/RcvrInactivity/DTPRcvrInactivityPolicyBase.h \
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
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCP_defs.h
$O/policies/DIF/EFCP/DTP/SenderInactivity/DTPSenderInactivityPolicyBase.o: policies/DIF/EFCP/DTP/SenderInactivity/DTPSenderInactivityPolicyBase.cc \
	policies/DIF/EFCP/DTP/SenderInactivity/DTPSenderInactivityPolicyBase.h \
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
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
	src/DIF/EFCP/EFCP_defs.h
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
	src/Common/QoSCube.h
$O/src/Common/ConnectionId.o: src/Common/ConnectionId.cc \
	src/Common/ConnectionId.h \
	src/Common/ExternConsts.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h
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
	src/Common/QoSCube.h
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
	src/Common/QoSCube.h
$O/src/Common/PDU_m.o: src/Common/PDU_m.cc \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/PDU_m.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h
$O/src/Common/Policy.o: src/Common/Policy.cc \
	src/Common/Policy.h
$O/src/Common/QoSCube.o: src/Common/QoSCube.cc \
	src/Common/ExternConsts.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h
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
	src/DAF/AE/AEBase.h
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
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h
$O/src/DAF/AE/EFCPListeners.o: src/DAF/AE/EFCPListeners.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/DTCPFCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/DTCPLostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/DTCPNoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/DTCPNoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/DTCPRateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/DTCPRcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/DTCPRcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/DTCPRcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/DTCPReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/DTCPReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/DTCPSenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/DTCPSendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/DTCPTxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/DTPInitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/DTPRTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/DTPRcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/DTPSenderInactivityPolicyBase.h \
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
	src/Common/RINASignals.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/AE/EFCPListeners.h \
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
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/PDUFG/IntPDUFG.h \
	src/policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	src/policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
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
	src/DAF/DA/DA.h \
	src/DAF/DA/Directory.h \
	src/DAF/DA/DirectoryEntry.h \
	src/DAF/DA/NamingInformation.h \
	src/DAF/DA/NamingInformationEntry.h \
	src/DAF/DA/NeighborTable.h \
	src/DAF/DA/NeighborTableEntry.h \
	src/DAF/DA/SearchTable.h \
	src/DAF/DA/SearchTableEntry.h \
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
	src/DAF/IRM/ConnectionTable.h \
	src/DAF/IRM/ConnectionTableEntry.h \
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
	src/DAF/IRM/ConnectionTableEntry.h \
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
	src/DIF/EFCP/EFCP_defs.h
$O/src/DIF/EFCP/EFCP.o: src/DIF/EFCP/EFCP.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/DTCPFCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/DTCPLostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/DTCPNoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/DTCPNoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/DTCPRateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/DTCPRcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/DTCPRcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/DTCPRcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/DTCPReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/DTCPReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/DTCPSenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/DTCPSendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/DTCPTxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/DTPInitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/DTPRTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/DTPRcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/DTPSenderInactivityPolicyBase.h \
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
	src/Common/RINASignals.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/AE/EFCPListeners.h \
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
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/PDUFG/IntPDUFG.h \
	src/policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	src/policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
$O/src/DIF/EFCP/EFCPInstance.o: src/DIF/EFCP/EFCPInstance.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/DTCPFCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/DTCPLostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/DTCPNoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/DTCPNoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/DTCPRateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/DTCPRcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/DTCPRcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/DTCPRcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/DTCPReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/DTCPReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/DTCPSenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/DTCPSendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/DTCPTxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/DTPInitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/DTPRTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/DTPRcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/DTPSenderInactivityPolicyBase.h \
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
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/PDUFG/IntPDUFG.h \
	src/policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	src/policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
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
	src/DIF/EFCP/DTCP/ControlPDU_m.h
$O/src/DIF/EFCP/DTCP/DTCP.o: src/DIF/EFCP/DTCP/DTCP.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/DTCPFCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/DTCPLostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/DTCPNoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/DTCPNoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/DTCPRateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/DTCPRcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/DTCPRcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/DTCPRcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/DTCPReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/DTCPReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/DTCPSenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/DTCPSendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/DTCPTxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/DTPInitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/DTPRTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/DTPRcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/DTPSenderInactivityPolicyBase.h \
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
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/PDUFG/IntPDUFG.h \
	src/policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	src/policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
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
	src/DIF/EFCP/EFCP_defs.h
$O/src/DIF/EFCP/DTCP/RXControl.o: src/DIF/EFCP/DTCP/RXControl.cc \
	src/DIF/EFCP/DTCP/RXControl.h
$O/src/DIF/EFCP/DTP/DTP.o: src/DIF/EFCP/DTP/DTP.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/DTCPFCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/DTCPLostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/DTCPNoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/DTCPNoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/DTCPRateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/DTCPRcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/DTCPRcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/DTCPRcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/DTCPReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/DTCPReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/DTCPSenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/DTCPSendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/DTCPTxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/DTPInitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/DTPRTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/DTPRcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/DTPSenderInactivityPolicyBase.h \
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
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/PDUFG/IntPDUFG.h \
	src/policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	src/policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
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
	src/DIF/EFCP/DTP/DataTransferPDU.h \
	src/DIF/EFCP/DTP/DataTransferPDU_m.h \
	src/DIF/EFCP/DTP/UserDataField.h \
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
	policies/DIF/EFCP/DTCP/FCOverrun/DTCPFCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/DTCPLostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/DTCPNoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/DTCPNoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/DTCPRateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/DTCPRcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/DTCPRcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/DTCPRcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/DTCPReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/DTCPReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/DTCPSenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/DTCPSendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/DTCPTxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/DTPInitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/DTPRTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/DTPRcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/DTPSenderInactivityPolicyBase.h \
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
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/PDUFG/IntPDUFG.h \
	src/policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	src/policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
$O/src/DIF/EFCP/EFCPTable/EFCPTableEntry.o: src/DIF/EFCP/EFCPTable/EFCPTableEntry.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/DTCPFCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/DTCPLostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/DTCPNoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/DTCPNoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/DTCPRateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/DTCPRcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/DTCPRcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/DTCPRcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/DTCPReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/DTCPReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/DTCPSenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/DTCPSendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/DTCPTxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/DTPInitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/DTPRTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/DTPRcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/DTPSenderInactivityPolicyBase.h \
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
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/PDUFG/IntPDUFG.h \
	src/policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	src/policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
$O/src/DIF/Enrollment/Enrollment.o: src/DIF/Enrollment/Enrollment.cc \
	src/DIF/Enrollment/Enrollment.h
$O/src/DIF/FA/FA.o: src/DIF/FA/FA.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/DTCPFCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/DTCPLostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/DTCPNoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/DTCPNoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/DTCPRateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/DTCPRcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/DTCPRcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/DTCPRcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/DTCPReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/DTCPReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/DTCPSenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/DTCPSendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/DTCPTxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/DTPInitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/DTPRTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/DTPRcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/DTPSenderInactivityPolicyBase.h \
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
	src/Common/RINASignals.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/AE/EFCPListeners.h \
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
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/FA/AllocateRetry/AllocateRetryBase.h \
	src/policies/DIF/FA/NewFlowRequest/NewFlowRequestBase.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/PDUFG/IntPDUFG.h \
	src/policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	src/policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
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
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h
$O/src/DIF/FA/FAI.o: src/DIF/FA/FAI.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/DTCPFCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/DTCPLostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/DTCPNoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/DTCPNoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/DTCPRateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/DTCPRcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/DTCPRcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/DTCPRcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/DTCPReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/DTCPReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/DTCPSenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/DTCPSendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/DTCPTxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/DTPInitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/DTPRTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/DTPRcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/DTPSenderInactivityPolicyBase.h \
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
	src/Common/RINASignals.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/AE/EFCPListeners.h \
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
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/FA/AllocateRetry/AllocateRetryBase.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/PDUFG/IntPDUFG.h \
	src/policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	src/policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
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
	src/DIF/FA/FAIBase.h
$O/src/DIF/FA/FAIListeners.o: src/DIF/FA/FAIListeners.cc \
	policies/DIF/EFCP/DTCP/ECN/DTCPECNPolicyBase.h \
	policies/DIF/EFCP/DTCP/ECNSlowDown/DTCPECNSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/FCOverrun/DTCPFCOverrunPolicyBase.h \
	policies/DIF/EFCP/DTCP/LostControlPDU/DTCPLostControlPDUPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoOverridePeak/DTCPNoOverridePeakPolicyBase.h \
	policies/DIF/EFCP/DTCP/NoRateSlowDown/DTCPNoRateSlowDownPolicyBase.h \
	policies/DIF/EFCP/DTCP/RateReduction/DTCPRateReductionPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrAck/DTCPRcvrAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrControlAck/DTCPRcvrControlAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/RcvrFC/DTCPRcvrFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReceivingFC/DTCPReceivingFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/ReconcileFC/DTCPReconcileFCPolicyBase.h \
	policies/DIF/EFCP/DTCP/SenderAck/DTCPSenderAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/SendingAck/DTCPSendingAckPolicyBase.h \
	policies/DIF/EFCP/DTCP/TxControl/DTCPTxControlPolicyBase.h \
	policies/DIF/EFCP/DTP/InitialSeqNum/DTPInitialSeqNumPolicyBase.h \
	policies/DIF/EFCP/DTP/RTTEstimator/DTPRTTEstimatorPolicyBase.h \
	policies/DIF/EFCP/DTP/RcvrInactivity/DTPRcvrInactivityPolicyBase.h \
	policies/DIF/EFCP/DTP/SenderInactivity/DTPSenderInactivityPolicyBase.h \
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
	src/Common/RINASignals.h \
	src/Common/SDU.h \
	src/Common/SDU_m.h \
	src/DAF/AE/EFCPListeners.h \
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
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/FA/AllocateRetry/AllocateRetryBase.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/PDUFG/IntPDUFG.h \
	src/policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	src/policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
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
$O/src/DIF/RA/AddressComparatorBase.o: src/DIF/RA/AddressComparatorBase.cc \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h
$O/src/DIF/RA/NM1FlowTable.o: src/DIF/RA/NM1FlowTable.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h
$O/src/DIF/RA/NM1FlowTableItem.o: src/DIF/RA/NM1FlowTableItem.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h
$O/src/DIF/RA/QueueAllocBase.o: src/DIF/RA/QueueAllocBase.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RABase.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
$O/src/DIF/RA/QueueIDGenBase.o: src/DIF/RA/QueueIDGenBase.cc \
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
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h
$O/src/DIF/RA/RA.o: src/DIF/RA/RA.cc \
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
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/PDUFG/IntPDUFG.h \
	src/policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	src/policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
$O/src/DIF/RA/RABase.o: src/DIF/RA/RABase.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RABase.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h
$O/src/DIF/RA/RAListeners.o: src/DIF/RA/RAListeners.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RABase.h \
	src/DIF/RA/RAListeners.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h
$O/src/DIF/RIB/RIBd.o: src/DIF/RIB/RIBd.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/RIB/RIBd.h \
	src/DIF/RIB/RIBdBase.h \
	src/DIF/RIB/RIBdListeners.h \
	src/policies/DIF/Routing/IntRoutingUpdate.h
$O/src/DIF/RIB/RIBdBase.o: src/DIF/RIB/RIBdBase.cc \
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
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/RIB/RIBdBase.h \
	src/policies/DIF/Routing/IntRoutingUpdate.h
$O/src/DIF/RIB/RIBdListeners.o: src/DIF/RIB/RIBdListeners.cc \
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
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/RIB/RIBdBase.h \
	src/DIF/RIB/RIBdListeners.h \
	src/policies/DIF/Routing/IntRoutingUpdate.h
$O/src/DIF/RMT/RMT.o: src/DIF/RMT/RMT.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
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
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
$O/src/DIF/RMT/RMTBase.o: src/DIF/RMT/RMTBase.cc \
	src/DIF/RMT/RMTBase.h
$O/src/DIF/RMT/RMTListeners.o: src/DIF/RMT/RMTListeners.cc \
	src/DIF/RMT/RMTBase.h \
	src/DIF/RMT/RMTListeners.h
$O/src/DIF/RMT/RMTMaxQBase.o: src/DIF/RMT/RMTMaxQBase.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
$O/src/DIF/RMT/RMTModuleAllocator.o: src/DIF/RMT/RMTModuleAllocator.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
$O/src/DIF/RMT/RMTPort.o: src/DIF/RMT/RMTPort.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h
$O/src/DIF/RMT/RMTQMonitorBase.o: src/DIF/RMT/RMTQMonitorBase.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
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
	src/DIF/RMT/RMTQueue.h
$O/src/DIF/RMT/RMTSchedulingBase.o: src/DIF/RMT/RMTSchedulingBase.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
$O/src/policies/DIF/FA/AllocateRetry/AllocateRetryBase.o: src/policies/DIF/FA/AllocateRetry/AllocateRetryBase.cc \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/policies/DIF/FA/AllocateRetry/AllocateRetryBase.h
$O/src/policies/DIF/FA/AllocateRetry/LimitedRetries/LimitedRetries.o: src/policies/DIF/FA/AllocateRetry/LimitedRetries/LimitedRetries.cc \
	src/Common/APN.h \
	src/Common/APNamingInfo.h \
	src/Common/Address.h \
	src/Common/ConnectionId.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Flow.h \
	src/Common/Policy.h \
	src/Common/QoSCube.h \
	src/policies/DIF/FA/AllocateRetry/AllocateRetryBase.h \
	src/policies/DIF/FA/AllocateRetry/LimitedRetries/LimitedRetries.h
$O/src/policies/DIF/FA/NewFlowRequest/NewFlowRequestBase.o: src/policies/DIF/FA/NewFlowRequest/NewFlowRequestBase.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RABase.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/FA/NewFlowRequest/NewFlowRequestBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h
$O/src/policies/DIF/FA/NewFlowRequest/QoSCubeComparer/QoSCubeComparer.o: src/policies/DIF/FA/NewFlowRequest/QoSCubeComparer/QoSCubeComparer.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RABase.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/FA/NewFlowRequest/NewFlowRequestBase.h \
	src/policies/DIF/FA/NewFlowRequest/QoSCubeComparer/QoSCubeComparer.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h
$O/src/policies/DIF/FA/NewFlowRequest/QoSCubeComparerMin/QoSCubeComparerMin.o: src/policies/DIF/FA/NewFlowRequest/QoSCubeComparerMin/QoSCubeComparerMin.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RABase.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/FA/NewFlowRequest/NewFlowRequestBase.h \
	src/policies/DIF/FA/NewFlowRequest/QoSCubeComparerMin/QoSCubeComparerMin.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h
$O/src/policies/DIF/RA/AddressComparator/ExactMatch/ExactMatch.o: src/policies/DIF/RA/AddressComparator/ExactMatch/ExactMatch.cc \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/AddressComparator/ExactMatch/ExactMatch.h
$O/src/policies/DIF/RA/AddressComparator/PrefixMatch/PrefixMatch.o: src/policies/DIF/RA/AddressComparator/PrefixMatch/PrefixMatch.cc \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/DAP.h \
	src/Common/ExternConsts.h \
	src/Common/Utils.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/AddressComparator/PrefixMatch/PrefixMatch.h
$O/src/policies/DIF/RA/PDUFG/IntBbPDUFG.o: src/policies/DIF/RA/PDUFG/IntBbPDUFG.cc \
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
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/PDUFG/IntBbPDUFG.h \
	src/policies/DIF/RA/PDUFG/IntPDUFG.h \
	src/policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntBbPDUForwarding.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/Routing/IntBbRouting.h \
	src/policies/DIF/Routing/IntRouting.h \
	src/policies/DIF/Routing/IntRoutingUpdate.h
$O/src/policies/DIF/RA/PDUFG/IntPDUFG.o: src/policies/DIF/RA/PDUFG/IntPDUFG.cc \
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
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/PDUFG/IntPDUFG.h \
	src/policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h
$O/src/policies/DIF/RA/PDUFG/PDUFGNeighbor.o: src/policies/DIF/RA/PDUFG/PDUFGNeighbor.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h
$O/src/policies/DIF/RA/PDUFG/BiDomainGenerator/BiDomainGenerator.o: src/policies/DIF/RA/PDUFG/BiDomainGenerator/BiDomainGenerator.cc \
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
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/PDUFG/BiDomainGenerator/BiDomainGenerator.h \
	src/policies/DIF/RA/PDUFG/IntPDUFG.h \
	src/policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/PDUForwarding/DomainTable/DomainTable.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/Routing/DomainRouting/Routing.h \
	src/policies/DIF/Routing/DomainRouting/rModule.h \
	src/policies/DIF/Routing/IntRouting.h \
	src/policies/DIF/Routing/IntRoutingUpdate.h
$O/src/policies/DIF/RA/PDUFG/SimpleGenerator/SimpleGenerator.o: src/policies/DIF/RA/PDUFG/SimpleGenerator/SimpleGenerator.cc \
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
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/PDUFG/IntPDUFG.h \
	src/policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	src/policies/DIF/RA/PDUFG/SimpleGenerator/SimpleGenerator.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/RMT/PDUForwarding/SimpleTable/SimpleTable.h \
	src/policies/DIF/Routing/IntRouting.h \
	src/policies/DIF/Routing/IntRoutingUpdate.h \
	src/policies/DIF/Routing/SimpleRouting/IntSimpleRouting.h
$O/src/policies/DIF/RA/PDUFG/SingleDomainGenerator/SingleDomainGenerator.o: src/policies/DIF/RA/PDUFG/SingleDomainGenerator/SingleDomainGenerator.cc \
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
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/PDUFG/IntPDUFG.h \
	src/policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	src/policies/DIF/RA/PDUFG/SingleDomainGenerator/SingleDomainGenerator.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/RMT/PDUForwarding/MiniTable/MiniTable.h \
	src/policies/DIF/Routing/DomainRouting/Routing.h \
	src/policies/DIF/Routing/DomainRouting/rModule.h \
	src/policies/DIF/Routing/IntRouting.h \
	src/policies/DIF/Routing/IntRoutingUpdate.h
$O/src/policies/DIF/RA/PDUFG/StaticGenerator/StaticGenerator.o: src/policies/DIF/RA/PDUFG/StaticGenerator/StaticGenerator.cc \
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
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/PDUFG/IntPDUFG.h \
	src/policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	src/policies/DIF/RA/PDUFG/StaticGenerator/StaticGenerator.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/RMT/PDUForwarding/SimpleTable/SimpleTable.h
$O/src/policies/DIF/RA/QueueAlloc/QueuePerNCU/QueuePerNCU.o: src/policies/DIF/RA/QueueAlloc/QueuePerNCU/QueuePerNCU.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RABase.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	src/policies/DIF/RA/QueueAlloc/QueuePerNCU/QueuePerNCU.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
$O/src/policies/DIF/RA/QueueAlloc/QueuePerNFlow/QueuePerNFlow.o: src/policies/DIF/RA/QueueAlloc/QueuePerNFlow/QueuePerNFlow.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RABase.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	src/policies/DIF/RA/QueueAlloc/QueuePerNFlow/QueuePerNFlow.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
$O/src/policies/DIF/RA/QueueAlloc/QueuePerNQoS/QueuePerNQoS.o: src/policies/DIF/RA/QueueAlloc/QueuePerNQoS/QueuePerNQoS.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RABase.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	src/policies/DIF/RA/QueueAlloc/QueuePerNQoS/QueuePerNQoS.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
$O/src/policies/DIF/RA/QueueAlloc/SingleQueue/SingleQueue.o: src/policies/DIF/RA/QueueAlloc/SingleQueue/SingleQueue.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RA/NM1FlowTable.h \
	src/DIF/RA/NM1FlowTableItem.h \
	src/DIF/RA/RABase.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/QueueAlloc/QueueAllocBase.h \
	src/policies/DIF/RA/QueueAlloc/SingleQueue/SingleQueue.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
$O/src/policies/DIF/RA/QueueIDGen/IDPerNCU/IDPerNCU.o: src/policies/DIF/RA/QueueIDGen/IDPerNCU/IDPerNCU.cc \
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
	src/policies/DIF/RA/QueueIDGen/IDPerNCU/IDPerNCU.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h
$O/src/policies/DIF/RA/QueueIDGen/IDPerNFlow/IDPerNFlow.o: src/policies/DIF/RA/QueueIDGen/IDPerNFlow/IDPerNFlow.cc \
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
	src/policies/DIF/RA/QueueIDGen/IDPerNFlow/IDPerNFlow.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h
$O/src/policies/DIF/RA/QueueIDGen/IDPerNQoS/IDPerNQoS.o: src/policies/DIF/RA/QueueIDGen/IDPerNQoS/IDPerNQoS.cc \
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
	src/policies/DIF/RA/QueueIDGen/IDPerNQoS/IDPerNQoS.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h
$O/src/policies/DIF/RA/QueueIDGen/SingleID/SingleID.o: src/policies/DIF/RA/QueueIDGen/SingleID/SingleID.cc \
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
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RA/QueueIDGen/SingleID/SingleID.h
$O/src/policies/DIF/RMT/MaxQueue/DLMaxQ/DLMaxQ.o: src/policies/DIF/RMT/MaxQueue/DLMaxQ/DLMaxQ.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/MaxQueue/DLMaxQ/DLMaxQ.h \
	src/policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	src/policies/DIF/RMT/Monitor/DLMonitor/DLMonitor.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
$O/src/policies/DIF/RMT/MaxQueue/ECNMarker/ECNMarker.o: src/policies/DIF/RMT/MaxQueue/ECNMarker/ECNMarker.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/MaxQueue/ECNMarker/ECNMarker.h \
	src/policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
$O/src/policies/DIF/RMT/MaxQueue/REDDropper/REDDropper.o: src/policies/DIF/RMT/MaxQueue/REDDropper/REDDropper.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/MaxQueue/REDDropper/REDDropper.h \
	src/policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	src/policies/DIF/RMT/Monitor/REDMonitor/REDMonitor.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
$O/src/policies/DIF/RMT/MaxQueue/ReadRateReducer/ReadRateReducer.o: src/policies/DIF/RMT/MaxQueue/ReadRateReducer/ReadRateReducer.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	src/policies/DIF/RMT/MaxQueue/ReadRateReducer/ReadRateReducer.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
$O/src/policies/DIF/RMT/MaxQueue/TailDrop/TailDrop.o: src/policies/DIF/RMT/MaxQueue/TailDrop/TailDrop.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	src/policies/DIF/RMT/MaxQueue/TailDrop/TailDrop.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
$O/src/policies/DIF/RMT/MaxQueue/UpstreamNotifier/UpstreamNotifier.o: src/policies/DIF/RMT/MaxQueue/UpstreamNotifier/UpstreamNotifier.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/MaxQueue/RMTMaxQBase.h \
	src/policies/DIF/RMT/MaxQueue/UpstreamNotifier/UpstreamNotifier.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
$O/src/policies/DIF/RMT/Monitor/DLMonitor/DLMonitor.o: src/policies/DIF/RMT/Monitor/DLMonitor/DLMonitor.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/Monitor/DLMonitor/DLMonitor.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
$O/src/policies/DIF/RMT/Monitor/REDMonitor/REDMonitor.o: src/policies/DIF/RMT/Monitor/REDMonitor/REDMonitor.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/Monitor/REDMonitor/REDMonitor.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
$O/src/policies/DIF/RMT/Monitor/SimpleMonitor/SimpleMonitor.o: src/policies/DIF/RMT/Monitor/SimpleMonitor/SimpleMonitor.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/Monitor/SimpleMonitor/SimpleMonitor.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
$O/src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.o: src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h
$O/src/policies/DIF/RMT/PDUForwarding/DomainTable/DomainTable.o: src/policies/DIF/RMT/PDUForwarding/DomainTable/DomainTable.cc \
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
	src/Common/RINASignals.h \
	src/Common/Utils.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/PDUForwarding/DomainTable/DomainTable.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h
$O/src/policies/DIF/RMT/PDUForwarding/MiniTable/MiniTable.o: src/policies/DIF/RMT/PDUForwarding/MiniTable/MiniTable.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/RMT/PDUForwarding/MiniTable/MiniTable.h
$O/src/policies/DIF/RMT/PDUForwarding/SimpleTable/SimpleTable.o: src/policies/DIF/RMT/PDUForwarding/SimpleTable/SimpleTable.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/RMT/PDUForwarding/SimpleTable/SimpleTable.h
$O/src/policies/DIF/RMT/Scheduler/DL/DL.o: src/policies/DIF/RMT/Scheduler/DL/DL.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/Monitor/DLMonitor/DLMonitor.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/Scheduler/DL/DL.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
$O/src/policies/DIF/RMT/Scheduler/LongestQFirst/LongestQFirst.o: src/policies/DIF/RMT/Scheduler/LongestQFirst/LongestQFirst.cc \
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
	src/Common/RINASignals.h \
	src/DAF/CDAP/CDAPMessage_m.h \
	src/DIF/RMT/RMTModuleAllocator.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/AddressComparator/AddressComparatorBase.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/Monitor/RMTQMonitorBase.h \
	src/policies/DIF/RMT/Scheduler/LongestQFirst/LongestQFirst.h \
	src/policies/DIF/RMT/Scheduler/RMTSchedulingBase.h
$O/src/policies/DIF/Routing/IntBbRouting.o: src/policies/DIF/Routing/IntBbRouting.cc \
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
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/PDUFG/IntPDUFG.h \
	src/policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/Routing/IntBbRouting.h \
	src/policies/DIF/Routing/IntRouting.h \
	src/policies/DIF/Routing/IntRoutingUpdate.h
$O/src/policies/DIF/Routing/IntRouting.o: src/policies/DIF/Routing/IntRouting.cc \
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
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/PDUFG/IntPDUFG.h \
	src/policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/Routing/IntRouting.h \
	src/policies/DIF/Routing/IntRoutingUpdate.h
$O/src/policies/DIF/Routing/IntRoutingUpdate.o: src/policies/DIF/Routing/IntRoutingUpdate.cc \
	src/Common/APN.h \
	src/Common/Address.h \
	src/Common/DAP.h \
	src/policies/DIF/Routing/IntRoutingUpdate.h
$O/src/policies/DIF/Routing/DomainRouting/Routing.o: src/policies/DIF/Routing/DomainRouting/Routing.cc \
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
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/PDUFG/IntPDUFG.h \
	src/policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/Routing/DomainRouting/DV/DV.h \
	src/policies/DIF/Routing/DomainRouting/LS/LS.h \
	src/policies/DIF/Routing/DomainRouting/Routing.h \
	src/policies/DIF/Routing/DomainRouting/rModule.h \
	src/policies/DIF/Routing/IntRouting.h \
	src/policies/DIF/Routing/IntRoutingUpdate.h
$O/src/policies/DIF/Routing/DomainRouting/rModule.o: src/policies/DIF/Routing/DomainRouting/rModule.cc \
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
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/PDUFG/IntPDUFG.h \
	src/policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/Routing/DomainRouting/Routing.h \
	src/policies/DIF/Routing/DomainRouting/rModule.h \
	src/policies/DIF/Routing/IntRouting.h \
	src/policies/DIF/Routing/IntRoutingUpdate.h
$O/src/policies/DIF/Routing/DomainRouting/DV/DV.o: src/policies/DIF/Routing/DomainRouting/DV/DV.cc \
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
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/PDUFG/IntPDUFG.h \
	src/policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/Routing/DomainRouting/DV/DV.h \
	src/policies/DIF/Routing/DomainRouting/Routing.h \
	src/policies/DIF/Routing/DomainRouting/rModule.h \
	src/policies/DIF/Routing/IntRouting.h \
	src/policies/DIF/Routing/IntRoutingUpdate.h
$O/src/policies/DIF/Routing/DomainRouting/LS/LS.o: src/policies/DIF/Routing/DomainRouting/LS/LS.cc \
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
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/PDUFG/IntPDUFG.h \
	src/policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/Routing/DomainRouting/LS/LS.h \
	src/policies/DIF/Routing/DomainRouting/Routing.h \
	src/policies/DIF/Routing/DomainRouting/rModule.h \
	src/policies/DIF/Routing/IntRouting.h \
	src/policies/DIF/Routing/IntRoutingUpdate.h
$O/src/policies/DIF/Routing/DummyRouting/DummyRouting.o: src/policies/DIF/Routing/DummyRouting/DummyRouting.cc \
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
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/PDUFG/IntPDUFG.h \
	src/policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/Routing/DummyRouting/DummyRouting.h \
	src/policies/DIF/Routing/IntRouting.h \
	src/policies/DIF/Routing/IntRoutingUpdate.h
$O/src/policies/DIF/Routing/SimpleRouting/SimpleDV/SimpleDV.o: src/policies/DIF/Routing/SimpleRouting/SimpleDV/SimpleDV.cc \
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
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/PDUFG/IntPDUFG.h \
	src/policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/Routing/IntRouting.h \
	src/policies/DIF/Routing/IntRoutingUpdate.h \
	src/policies/DIF/Routing/SimpleRouting/IntSimpleRouting.h \
	src/policies/DIF/Routing/SimpleRouting/SimpleDV/SimpleDV.h
$O/src/policies/DIF/Routing/SimpleRouting/SimpleLS/SimpleLS.o: src/policies/DIF/Routing/SimpleRouting/SimpleLS/SimpleLS.cc \
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
	src/DIF/FA/FABase.h \
	src/DIF/FA/FAIBase.h \
	src/DIF/FA/FAITable.h \
	src/DIF/FA/FAITableEntry.h \
	src/DIF/RMT/RMTPort.h \
	src/DIF/RMT/RMTQueue.h \
	src/policies/DIF/RA/PDUFG/IntPDUFG.h \
	src/policies/DIF/RA/PDUFG/PDUFGNeighbor.h \
	src/policies/DIF/RA/QueueIDGen/QueueIDGenBase.h \
	src/policies/DIF/RMT/PDUForwarding/IntPDUForwarding.h \
	src/policies/DIF/Routing/IntRouting.h \
	src/policies/DIF/Routing/IntRoutingUpdate.h \
	src/policies/DIF/Routing/SimpleRouting/IntSimpleRouting.h \
	src/policies/DIF/Routing/SimpleRouting/SimpleLS/SimpleLS.h

