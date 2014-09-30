#
# OMNeT++/OMNEST Makefile for RINA
#
# This file was generated with the command:
#  opp_makemake -f --deep
#

# Name of target to be created (-o option)
TARGET = RINA$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I. \
    -ICS \
    -ICommon \
    -IDAF \
    -IDAF/AE \
    -IDAF/CDAP \
    -IDAF/DA \
    -IDAF/IRM \
    -IDIF \
    -IDIF/Delimiting \
    -IDIF/EFCP \
    -IDIF/EFCP/EFCPTable \
    -IDIF/EFCP/policies \
    -IDIF/Enrollment \
    -IDIF/FA \
    -IDIF/NSM \
    -IDIF/RA \
    -IDIF/RIB \
    -IDIF/RMT \
    -IDIF/RMT/policies

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS =

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/Common/Address.o \
    $O/Common/APN.o \
    $O/Common/APNamingInfo.o \
    $O/Common/ConnectionId.o \
    $O/Common/Data.o \
    $O/Common/ExternConsts.o \
    $O/Common/Flow.o \
    $O/Common/ModuleAccess.o \
    $O/Common/PDU.o \
    $O/Common/Policy.o \
    $O/Common/QosCube.o \
    $O/Common/RINASignals.o \
    $O/Common/SDU.o \
    $O/Common/Test.o \
    $O/DAF/AE/AE.o \
    $O/DAF/AE/AEBase.o \
    $O/DAF/AE/AEListeners.o \
    $O/DAF/AE/AEPing.o \
    $O/DAF/CDAP/Auth.o \
    $O/DAF/CDAP/CACE.o \
    $O/DAF/CDAP/CDAP.o \
    $O/DAF/CDAP/CDAPMsgLog.o \
    $O/DAF/CDAP/CDAPMsgLogEntry.o \
    $O/DAF/CDAP/CDAPSplitter.o \
    $O/DAF/DA/DA.o \
    $O/DAF/DA/Directory.o \
    $O/DAF/DA/DirectoryEntry.o \
    $O/DAF/DA/NamingInformation.o \
    $O/DAF/DA/NeighborTable.o \
    $O/DAF/DA/SearchTable.o \
    $O/DAF/IRM/ConnectionTable.o \
    $O/DAF/IRM/ConnectionTableEntry.o \
    $O/DAF/IRM/IRM.o \
    $O/DAF/IRM/IRMListeners.o \
    $O/DIF/Delimiting/Delimiting.o \
    $O/DIF/Delimiting/SDUFrag.o \
    $O/DIF/EFCP/DTCP.o \
    $O/DIF/EFCP/DTCPState.o \
    $O/DIF/EFCP/DTP.o \
    $O/DIF/EFCP/DTPState.o \
    $O/DIF/EFCP/EFCP.o \
    $O/DIF/EFCP/EFCPInstance.o \
    $O/DIF/EFCP/FlowControl.o \
    $O/DIF/EFCP/RXControl.o \
    $O/DIF/EFCP/SDUs.o \
    $O/DIF/EFCP/EFCPTable/EFCPTable.o \
    $O/DIF/EFCP/EFCPTable/EFCPTableEntry.o \
    $O/DIF/EFCP/policies/DefaultTxControlPolicy.o \
    $O/DIF/EFCP/policies/TxControlPolicy.o \
    $O/DIF/Enrollment/Enrollment.o \
    $O/DIF/FA/FA.o \
    $O/DIF/FA/FABase.o \
    $O/DIF/FA/FAI.o \
    $O/DIF/FA/FAIListeners.o \
    $O/DIF/FA/FAITable.o \
    $O/DIF/FA/FAITableEntry.o \
    $O/DIF/FA/FAListeners.o \
    $O/DIF/NSM/DirectoryForwardingTable.o \
    $O/DIF/NSM/LocalDirectoryCache.o \
    $O/DIF/NSM/NSM.o \
    $O/DIF/RA/PDUForwardingTable.o \
    $O/DIF/RA/PDUFwdTabGenerator.o \
    $O/DIF/RA/PDUTableEntry.o \
    $O/DIF/RA/RA.o \
    $O/DIF/RIB/RIBDaemon.o \
    $O/DIF/RMT/RMT.o \
    $O/DIF/RMT/RMTPort.o \
    $O/DIF/RMT/RMTPortManager.o \
    $O/DIF/RMT/RMTQueue.o \
    $O/DIF/RMT/policies/MaxQPolicy.o \
    $O/DIF/RMT/policies/RMTQMonitorPolicy.o \
    $O/DIF/RMT/policies/RMTSchedulingPolicy.o \
    $O/Common/Data_m.o \
    $O/Common/PDU_m.o \
    $O/Common/SDU_m.o \
    $O/DAF/CDAP/CDAPMessage_m.o \
    $O/DIF/Delimiting/SDUFrag_m.o \
    $O/DIF/EFCP/ControlPDU_m.o \
    $O/DIF/EFCP/DataTransferPDU_m.o \
    $O/DIF/EFCP/DTCPTimers_m.o \
    $O/DIF/EFCP/DTPTimers_m.o \
    $O/DIF/EFCP/FCTimers_m.o

# Message files
MSGFILES = \
    Common/Data.msg \
    Common/PDU.msg \
    Common/SDU.msg \
    DAF/CDAP/CDAPMessage.msg \
    DIF/Delimiting/SDUFrag.msg \
    DIF/EFCP/ControlPDU.msg \
    DIF/EFCP/DataTransferPDU.msg \
    DIF/EFCP/DTCPTimers.msg \
    DIF/EFCP/DTPTimers.msg \
    DIF/EFCP/FCTimers.msg

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
	$(Q)-rm -f RINA RINA.exe libRINA.so libRINA.a libRINA.dll libRINA.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f CS/*_m.cc CS/*_m.h
	$(Q)-rm -f Common/*_m.cc Common/*_m.h
	$(Q)-rm -f DAF/*_m.cc DAF/*_m.h
	$(Q)-rm -f DAF/AE/*_m.cc DAF/AE/*_m.h
	$(Q)-rm -f DAF/CDAP/*_m.cc DAF/CDAP/*_m.h
	$(Q)-rm -f DAF/DA/*_m.cc DAF/DA/*_m.h
	$(Q)-rm -f DAF/IRM/*_m.cc DAF/IRM/*_m.h
	$(Q)-rm -f DIF/*_m.cc DIF/*_m.h
	$(Q)-rm -f DIF/Delimiting/*_m.cc DIF/Delimiting/*_m.h
	$(Q)-rm -f DIF/EFCP/*_m.cc DIF/EFCP/*_m.h
	$(Q)-rm -f DIF/EFCP/EFCPTable/*_m.cc DIF/EFCP/EFCPTable/*_m.h
	$(Q)-rm -f DIF/EFCP/policies/*_m.cc DIF/EFCP/policies/*_m.h
	$(Q)-rm -f DIF/Enrollment/*_m.cc DIF/Enrollment/*_m.h
	$(Q)-rm -f DIF/FA/*_m.cc DIF/FA/*_m.h
	$(Q)-rm -f DIF/NSM/*_m.cc DIF/NSM/*_m.h
	$(Q)-rm -f DIF/RA/*_m.cc DIF/RA/*_m.h
	$(Q)-rm -f DIF/RIB/*_m.cc DIF/RIB/*_m.h
	$(Q)-rm -f DIF/RMT/*_m.cc DIF/RMT/*_m.h
	$(Q)-rm -f DIF/RMT/policies/*_m.cc DIF/RMT/policies/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc CS/*.cc Common/*.cc DAF/*.cc DAF/AE/*.cc DAF/CDAP/*.cc DAF/DA/*.cc DAF/IRM/*.cc DIF/*.cc DIF/Delimiting/*.cc DIF/EFCP/*.cc DIF/EFCP/EFCPTable/*.cc DIF/EFCP/policies/*.cc DIF/Enrollment/*.cc DIF/FA/*.cc DIF/NSM/*.cc DIF/RA/*.cc DIF/RIB/*.cc DIF/RMT/*.cc DIF/RMT/policies/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/Common/APN.o: Common/APN.cc \
	Common/APN.h
$O/Common/APNamingInfo.o: Common/APNamingInfo.cc \
	Common/APN.h \
	Common/APNamingInfo.h
$O/Common/Address.o: Common/Address.cc \
	Common/Address.h
$O/Common/ConnectionId.o: Common/ConnectionId.cc \
	Common/ConnectionId.h \
	Common/Policy.h \
	Common/QosCube.h
$O/Common/Data.o: Common/Data.cc \
	Common/Data.h \
	Common/Data_m.h
$O/Common/Data_m.o: Common/Data_m.cc \
	Common/Data_m.h
$O/Common/ExternConsts.o: Common/ExternConsts.cc \
	Common/ExternConsts.h
$O/Common/Flow.o: Common/Flow.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/Flow.h \
	Common/Policy.h \
	Common/QosCube.h
$O/Common/ModuleAccess.o: Common/ModuleAccess.cc \
	Common/ModuleAccess.h
$O/Common/PDU.o: Common/PDU.cc \
	Common/APN.h \
	Common/ConnectionId.h \
	Common/PDU.h \
	Common/PDU_m.h \
	Common/Policy.h \
	Common/QosCube.h
$O/Common/PDU_m.o: Common/PDU_m.cc \
	Common/APN.h \
	Common/ConnectionId.h \
	Common/PDU_m.h \
	Common/Policy.h \
	Common/QosCube.h
$O/Common/Policy.o: Common/Policy.cc \
	Common/Policy.h
$O/Common/QosCube.o: Common/QosCube.cc \
	Common/Policy.h \
	Common/QosCube.h
$O/Common/RINASignals.o: Common/RINASignals.cc \
	Common/RINASignals.h
$O/Common/SDU.o: Common/SDU.cc \
	Common/Data.h \
	Common/Data_m.h \
	Common/SDU.h \
	Common/SDU_m.h \
	DAF/CDAP/CDAPMessage_m.h \
	DIF/EFCP/EFCP_defs.h
$O/Common/SDU_m.o: Common/SDU_m.cc \
	Common/Data.h \
	Common/Data_m.h \
	Common/SDU_m.h \
	DAF/CDAP/CDAPMessage_m.h
$O/Common/Test.o: Common/Test.cc \
	Common/Test.h
$O/DAF/AE/AE.o: DAF/AE/AE.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/ExternConsts.h \
	Common/Flow.h \
	Common/ModuleAccess.h \
	Common/Policy.h \
	Common/QosCube.h \
	Common/RINASignals.h \
	DAF/AE/AE.h \
	DAF/AE/AEBase.h \
	DAF/AE/AEListeners.h \
	DAF/DA/DA.h \
	DAF/DA/Directory.h \
	DAF/DA/DirectoryEntry.h \
	DAF/DA/NamingInformation.h \
	DAF/DA/NeighborTable.h \
	DAF/DA/SearchTable.h \
	DAF/IRM/ConnectionTable.h \
	DAF/IRM/ConnectionTableEntry.h \
	DAF/IRM/IRM.h \
	DAF/IRM/IRMListeners.h \
	DIF/FA/FABase.h
$O/DAF/AE/AEBase.o: DAF/AE/AEBase.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/Flow.h \
	Common/Policy.h \
	Common/QosCube.h \
	DAF/AE/AEBase.h
$O/DAF/AE/AEListeners.o: DAF/AE/AEListeners.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/ExternConsts.h \
	Common/Flow.h \
	Common/ModuleAccess.h \
	Common/Policy.h \
	Common/QosCube.h \
	Common/RINASignals.h \
	DAF/AE/AE.h \
	DAF/AE/AEBase.h \
	DAF/AE/AEListeners.h \
	DAF/DA/DA.h \
	DAF/DA/Directory.h \
	DAF/DA/DirectoryEntry.h \
	DAF/DA/NamingInformation.h \
	DAF/DA/NeighborTable.h \
	DAF/DA/SearchTable.h \
	DAF/IRM/ConnectionTable.h \
	DAF/IRM/ConnectionTableEntry.h \
	DAF/IRM/IRM.h \
	DAF/IRM/IRMListeners.h \
	DIF/FA/FABase.h
$O/DAF/AE/AEPing.o: DAF/AE/AEPing.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/ExternConsts.h \
	Common/Flow.h \
	Common/ModuleAccess.h \
	Common/Policy.h \
	Common/QosCube.h \
	Common/RINASignals.h \
	DAF/AE/AE.h \
	DAF/AE/AEBase.h \
	DAF/AE/AEListeners.h \
	DAF/AE/AEPing.h \
	DAF/DA/DA.h \
	DAF/DA/Directory.h \
	DAF/DA/DirectoryEntry.h \
	DAF/DA/NamingInformation.h \
	DAF/DA/NeighborTable.h \
	DAF/DA/SearchTable.h \
	DAF/IRM/ConnectionTable.h \
	DAF/IRM/ConnectionTableEntry.h \
	DAF/IRM/IRM.h \
	DAF/IRM/IRMListeners.h \
	DIF/FA/FABase.h
$O/DAF/CDAP/Auth.o: DAF/CDAP/Auth.cc \
	DAF/CDAP/Auth.h
$O/DAF/CDAP/CACE.o: DAF/CDAP/CACE.cc \
	DAF/CDAP/CACE.h
$O/DAF/CDAP/CDAP.o: DAF/CDAP/CDAP.cc \
	DAF/CDAP/CDAP.h
$O/DAF/CDAP/CDAPMessage_m.o: DAF/CDAP/CDAPMessage_m.cc \
	DAF/CDAP/CDAPMessage_m.h
$O/DAF/CDAP/CDAPMsgLog.o: DAF/CDAP/CDAPMsgLog.cc \
	DAF/CDAP/CDAPMsgLog.h \
	DAF/CDAP/CDAPMsgLogEntry.h
$O/DAF/CDAP/CDAPMsgLogEntry.o: DAF/CDAP/CDAPMsgLogEntry.cc \
	DAF/CDAP/CDAPMsgLogEntry.h
$O/DAF/CDAP/CDAPSplitter.o: DAF/CDAP/CDAPSplitter.cc \
	DAF/CDAP/CDAPMessage_m.h \
	DAF/CDAP/CDAPSplitter.h
$O/DAF/DA/DA.o: DAF/DA/DA.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/ExternConsts.h \
	Common/Flow.h \
	Common/ModuleAccess.h \
	Common/Policy.h \
	Common/QosCube.h \
	DAF/DA/DA.h \
	DAF/DA/Directory.h \
	DAF/DA/DirectoryEntry.h \
	DAF/DA/NamingInformation.h \
	DAF/DA/NeighborTable.h \
	DAF/DA/SearchTable.h \
	DIF/FA/FABase.h
$O/DAF/DA/Directory.o: DAF/DA/Directory.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/ExternConsts.h \
	Common/Flow.h \
	Common/Policy.h \
	Common/QosCube.h \
	DAF/DA/Directory.h \
	DAF/DA/DirectoryEntry.h \
	DIF/FA/FABase.h
$O/DAF/DA/DirectoryEntry.o: DAF/DA/DirectoryEntry.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/Flow.h \
	Common/Policy.h \
	Common/QosCube.h \
	DAF/DA/DirectoryEntry.h \
	DIF/FA/FABase.h
$O/DAF/DA/NamingInformation.o: DAF/DA/NamingInformation.cc \
	DAF/DA/NamingInformation.h
$O/DAF/DA/NeighborTable.o: DAF/DA/NeighborTable.cc \
	DAF/DA/NeighborTable.h
$O/DAF/DA/SearchTable.o: DAF/DA/SearchTable.cc \
	DAF/DA/SearchTable.h
$O/DAF/IRM/ConnectionTable.o: DAF/IRM/ConnectionTable.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/Flow.h \
	Common/Policy.h \
	Common/QosCube.h \
	DAF/IRM/ConnectionTable.h \
	DAF/IRM/ConnectionTableEntry.h \
	DIF/FA/FABase.h
$O/DAF/IRM/ConnectionTableEntry.o: DAF/IRM/ConnectionTableEntry.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/Flow.h \
	Common/Policy.h \
	Common/QosCube.h \
	DAF/IRM/ConnectionTableEntry.h \
	DIF/FA/FABase.h
$O/DAF/IRM/IRM.o: DAF/IRM/IRM.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/ExternConsts.h \
	Common/Flow.h \
	Common/ModuleAccess.h \
	Common/Policy.h \
	Common/QosCube.h \
	Common/RINASignals.h \
	DAF/DA/DA.h \
	DAF/DA/Directory.h \
	DAF/DA/DirectoryEntry.h \
	DAF/DA/NamingInformation.h \
	DAF/DA/NeighborTable.h \
	DAF/DA/SearchTable.h \
	DAF/IRM/ConnectionTable.h \
	DAF/IRM/ConnectionTableEntry.h \
	DAF/IRM/IRM.h \
	DAF/IRM/IRMListeners.h \
	DIF/FA/FABase.h
$O/DAF/IRM/IRMListeners.o: DAF/IRM/IRMListeners.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/ExternConsts.h \
	Common/Flow.h \
	Common/ModuleAccess.h \
	Common/Policy.h \
	Common/QosCube.h \
	Common/RINASignals.h \
	DAF/DA/DA.h \
	DAF/DA/Directory.h \
	DAF/DA/DirectoryEntry.h \
	DAF/DA/NamingInformation.h \
	DAF/DA/NeighborTable.h \
	DAF/DA/SearchTable.h \
	DAF/IRM/ConnectionTable.h \
	DAF/IRM/ConnectionTableEntry.h \
	DAF/IRM/IRM.h \
	DAF/IRM/IRMListeners.h \
	DIF/FA/FABase.h
$O/DIF/Delimiting/Delimiting.o: DIF/Delimiting/Delimiting.cc \
	Common/APN.h \
	Common/ConnectionId.h \
	Common/Data.h \
	Common/Data_m.h \
	Common/PDU.h \
	Common/PDU_m.h \
	Common/Policy.h \
	Common/QosCube.h \
	Common/SDU.h \
	Common/SDU_m.h \
	DAF/CDAP/CDAPMessage_m.h \
	DIF/Delimiting/Delimiting.h \
	DIF/EFCP/DataTransferPDU_m.h \
	DIF/EFCP/EFCP_defs.h
$O/DIF/Delimiting/SDUFrag.o: DIF/Delimiting/SDUFrag.cc \
	Common/Data.h \
	Common/Data_m.h \
	Common/SDU.h \
	Common/SDU_m.h \
	DAF/CDAP/CDAPMessage_m.h \
	DIF/Delimiting/SDUFrag.h \
	DIF/Delimiting/SDUFrag_m.h \
	DIF/EFCP/EFCP_defs.h
$O/DIF/Delimiting/SDUFrag_m.o: DIF/Delimiting/SDUFrag_m.cc \
	Common/Data.h \
	Common/Data_m.h \
	Common/SDU.h \
	Common/SDU_m.h \
	DAF/CDAP/CDAPMessage_m.h \
	DIF/Delimiting/SDUFrag_m.h \
	DIF/EFCP/EFCP_defs.h
$O/DIF/EFCP/ControlPDU_m.o: DIF/EFCP/ControlPDU_m.cc \
	Common/APN.h \
	Common/ConnectionId.h \
	Common/PDU.h \
	Common/PDU_m.h \
	Common/Policy.h \
	Common/QosCube.h \
	DIF/EFCP/ControlPDU_m.h
$O/DIF/EFCP/DTCP.o: DIF/EFCP/DTCP.cc \
	Common/APN.h \
	Common/ConnectionId.h \
	Common/PDU.h \
	Common/PDU_m.h \
	Common/Policy.h \
	Common/QosCube.h \
	DIF/EFCP/ControlPDU_m.h \
	DIF/EFCP/DTCP.h \
	DIF/EFCP/DTCPState.h \
	DIF/EFCP/DTCPTimers_m.h \
	DIF/EFCP/FlowControl.h \
	DIF/EFCP/RXControl.h
$O/DIF/EFCP/DTCPState.o: DIF/EFCP/DTCPState.cc \
	DIF/EFCP/DTCPState.h
$O/DIF/EFCP/DTCPTimers_m.o: DIF/EFCP/DTCPTimers_m.cc \
	DIF/EFCP/DTCPTimers_m.h
$O/DIF/EFCP/DTP.o: DIF/EFCP/DTP.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/Data.h \
	Common/Data_m.h \
	Common/Flow.h \
	Common/ModuleAccess.h \
	Common/PDU.h \
	Common/PDU_m.h \
	Common/Policy.h \
	Common/QosCube.h \
	Common/SDU.h \
	Common/SDU_m.h \
	DAF/CDAP/CDAPMessage_m.h \
	DAF/IRM/ConnectionTable.h \
	DAF/IRM/ConnectionTableEntry.h \
	DIF/EFCP/ControlPDU_m.h \
	DIF/EFCP/DTCP.h \
	DIF/EFCP/DTCPState.h \
	DIF/EFCP/DTCPTimers_m.h \
	DIF/EFCP/DTP.h \
	DIF/EFCP/DTPState.h \
	DIF/EFCP/DTPTimers_m.h \
	DIF/EFCP/DataTransferPDU_m.h \
	DIF/EFCP/EFCP_defs.h \
	DIF/EFCP/FlowControl.h \
	DIF/EFCP/RXControl.h \
	DIF/EFCP/policies/DefaultTxControlPolicy.h \
	DIF/EFCP/policies/TxControlPolicy.h \
	DIF/FA/FABase.h \
	DIF/RA/PDUForwardingTable.h \
	DIF/RA/PDUTableEntry.h \
	DIF/RMT/RMT.h
$O/DIF/EFCP/DTPState.o: DIF/EFCP/DTPState.cc \
	DIF/EFCP/DTPState.h
$O/DIF/EFCP/DTPTimers_m.o: DIF/EFCP/DTPTimers_m.cc \
	Common/APN.h \
	Common/ConnectionId.h \
	Common/PDU.h \
	Common/PDU_m.h \
	Common/Policy.h \
	Common/QosCube.h \
	DIF/EFCP/DTPTimers_m.h
$O/DIF/EFCP/DataTransferPDU_m.o: DIF/EFCP/DataTransferPDU_m.cc \
	Common/APN.h \
	Common/ConnectionId.h \
	Common/PDU.h \
	Common/PDU_m.h \
	Common/Policy.h \
	Common/QosCube.h \
	DIF/EFCP/DataTransferPDU_m.h
$O/DIF/EFCP/EFCP.o: DIF/EFCP/EFCP.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/Data.h \
	Common/Data_m.h \
	Common/ExternConsts.h \
	Common/Flow.h \
	Common/ModuleAccess.h \
	Common/PDU.h \
	Common/PDU_m.h \
	Common/Policy.h \
	Common/QosCube.h \
	Common/SDU.h \
	Common/SDU_m.h \
	DAF/CDAP/CDAPMessage_m.h \
	DAF/IRM/ConnectionTable.h \
	DAF/IRM/ConnectionTableEntry.h \
	DIF/Delimiting/Delimiting.h \
	DIF/EFCP/ControlPDU_m.h \
	DIF/EFCP/DTCP.h \
	DIF/EFCP/DTCPState.h \
	DIF/EFCP/DTCPTimers_m.h \
	DIF/EFCP/DTP.h \
	DIF/EFCP/DTPState.h \
	DIF/EFCP/DTPTimers_m.h \
	DIF/EFCP/DataTransferPDU_m.h \
	DIF/EFCP/EFCP.h \
	DIF/EFCP/EFCPInstance.h \
	DIF/EFCP/EFCPTable/EFCPTable.h \
	DIF/EFCP/EFCPTable/EFCPTableEntry.h \
	DIF/EFCP/EFCP_defs.h \
	DIF/EFCP/FlowControl.h \
	DIF/EFCP/RXControl.h \
	DIF/EFCP/policies/DefaultTxControlPolicy.h \
	DIF/EFCP/policies/TxControlPolicy.h \
	DIF/FA/FABase.h \
	DIF/RA/PDUForwardingTable.h \
	DIF/RA/PDUTableEntry.h \
	DIF/RMT/RMT.h
$O/DIF/EFCP/EFCPInstance.o: DIF/EFCP/EFCPInstance.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/Data.h \
	Common/Data_m.h \
	Common/Flow.h \
	Common/ModuleAccess.h \
	Common/PDU.h \
	Common/PDU_m.h \
	Common/Policy.h \
	Common/QosCube.h \
	Common/SDU.h \
	Common/SDU_m.h \
	DAF/CDAP/CDAPMessage_m.h \
	DAF/IRM/ConnectionTable.h \
	DAF/IRM/ConnectionTableEntry.h \
	DIF/EFCP/ControlPDU_m.h \
	DIF/EFCP/DTCP.h \
	DIF/EFCP/DTCPState.h \
	DIF/EFCP/DTCPTimers_m.h \
	DIF/EFCP/DTP.h \
	DIF/EFCP/DTPState.h \
	DIF/EFCP/DTPTimers_m.h \
	DIF/EFCP/DataTransferPDU_m.h \
	DIF/EFCP/EFCPInstance.h \
	DIF/EFCP/EFCP_defs.h \
	DIF/EFCP/FlowControl.h \
	DIF/EFCP/RXControl.h \
	DIF/EFCP/policies/DefaultTxControlPolicy.h \
	DIF/EFCP/policies/TxControlPolicy.h \
	DIF/FA/FABase.h \
	DIF/RA/PDUForwardingTable.h \
	DIF/RA/PDUTableEntry.h \
	DIF/RMT/RMT.h
$O/DIF/EFCP/FCTimers_m.o: DIF/EFCP/FCTimers_m.cc \
	DIF/EFCP/FCTimers_m.h
$O/DIF/EFCP/FlowControl.o: DIF/EFCP/FlowControl.cc \
	Common/APN.h \
	Common/ConnectionId.h \
	Common/PDU.h \
	Common/PDU_m.h \
	Common/Policy.h \
	Common/QosCube.h \
	DIF/EFCP/ControlPDU_m.h \
	DIF/EFCP/FlowControl.h
$O/DIF/EFCP/RXControl.o: DIF/EFCP/RXControl.cc \
	DIF/EFCP/RXControl.h
$O/DIF/EFCP/SDUs.o: DIF/EFCP/SDUs.cc \
	DIF/EFCP/SDUs.h
$O/DIF/EFCP/EFCPTable/EFCPTable.o: DIF/EFCP/EFCPTable/EFCPTable.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/Data.h \
	Common/Data_m.h \
	Common/Flow.h \
	Common/ModuleAccess.h \
	Common/PDU.h \
	Common/PDU_m.h \
	Common/Policy.h \
	Common/QosCube.h \
	Common/SDU.h \
	Common/SDU_m.h \
	DAF/CDAP/CDAPMessage_m.h \
	DAF/IRM/ConnectionTable.h \
	DAF/IRM/ConnectionTableEntry.h \
	DIF/Delimiting/Delimiting.h \
	DIF/EFCP/ControlPDU_m.h \
	DIF/EFCP/DTCP.h \
	DIF/EFCP/DTCPState.h \
	DIF/EFCP/DTCPTimers_m.h \
	DIF/EFCP/DTP.h \
	DIF/EFCP/DTPState.h \
	DIF/EFCP/DTPTimers_m.h \
	DIF/EFCP/DataTransferPDU_m.h \
	DIF/EFCP/EFCPInstance.h \
	DIF/EFCP/EFCPTable/EFCPTable.h \
	DIF/EFCP/EFCPTable/EFCPTableEntry.h \
	DIF/EFCP/EFCP_defs.h \
	DIF/EFCP/FlowControl.h \
	DIF/EFCP/RXControl.h \
	DIF/EFCP/policies/DefaultTxControlPolicy.h \
	DIF/EFCP/policies/TxControlPolicy.h \
	DIF/FA/FABase.h \
	DIF/RA/PDUForwardingTable.h \
	DIF/RA/PDUTableEntry.h \
	DIF/RMT/RMT.h
$O/DIF/EFCP/EFCPTable/EFCPTableEntry.o: DIF/EFCP/EFCPTable/EFCPTableEntry.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/Data.h \
	Common/Data_m.h \
	Common/Flow.h \
	Common/ModuleAccess.h \
	Common/PDU.h \
	Common/PDU_m.h \
	Common/Policy.h \
	Common/QosCube.h \
	Common/SDU.h \
	Common/SDU_m.h \
	DAF/CDAP/CDAPMessage_m.h \
	DAF/IRM/ConnectionTable.h \
	DAF/IRM/ConnectionTableEntry.h \
	DIF/Delimiting/Delimiting.h \
	DIF/EFCP/ControlPDU_m.h \
	DIF/EFCP/DTCP.h \
	DIF/EFCP/DTCPState.h \
	DIF/EFCP/DTCPTimers_m.h \
	DIF/EFCP/DTP.h \
	DIF/EFCP/DTPState.h \
	DIF/EFCP/DTPTimers_m.h \
	DIF/EFCP/DataTransferPDU_m.h \
	DIF/EFCP/EFCPInstance.h \
	DIF/EFCP/EFCPTable/EFCPTableEntry.h \
	DIF/EFCP/EFCP_defs.h \
	DIF/EFCP/FlowControl.h \
	DIF/EFCP/RXControl.h \
	DIF/EFCP/policies/DefaultTxControlPolicy.h \
	DIF/EFCP/policies/TxControlPolicy.h \
	DIF/FA/FABase.h \
	DIF/RA/PDUForwardingTable.h \
	DIF/RA/PDUTableEntry.h \
	DIF/RMT/RMT.h
$O/DIF/EFCP/policies/DefaultTxControlPolicy.o: DIF/EFCP/policies/DefaultTxControlPolicy.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/Data.h \
	Common/Data_m.h \
	Common/Flow.h \
	Common/ModuleAccess.h \
	Common/PDU.h \
	Common/PDU_m.h \
	Common/Policy.h \
	Common/QosCube.h \
	Common/SDU.h \
	Common/SDU_m.h \
	DAF/CDAP/CDAPMessage_m.h \
	DAF/IRM/ConnectionTable.h \
	DAF/IRM/ConnectionTableEntry.h \
	DIF/EFCP/ControlPDU_m.h \
	DIF/EFCP/DTCP.h \
	DIF/EFCP/DTCPState.h \
	DIF/EFCP/DTCPTimers_m.h \
	DIF/EFCP/DTP.h \
	DIF/EFCP/DTPState.h \
	DIF/EFCP/DTPTimers_m.h \
	DIF/EFCP/DataTransferPDU_m.h \
	DIF/EFCP/EFCP_defs.h \
	DIF/EFCP/FlowControl.h \
	DIF/EFCP/RXControl.h \
	DIF/EFCP/policies/DefaultTxControlPolicy.h \
	DIF/EFCP/policies/TxControlPolicy.h \
	DIF/FA/FABase.h \
	DIF/RA/PDUForwardingTable.h \
	DIF/RA/PDUTableEntry.h \
	DIF/RMT/RMT.h
$O/DIF/EFCP/policies/TxControlPolicy.o: DIF/EFCP/policies/TxControlPolicy.cc \
	Common/Policy.h \
	DIF/EFCP/policies/TxControlPolicy.h
$O/DIF/Enrollment/Enrollment.o: DIF/Enrollment/Enrollment.cc \
	DIF/Enrollment/Enrollment.h
$O/DIF/FA/FA.o: DIF/FA/FA.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/Data.h \
	Common/Data_m.h \
	Common/ExternConsts.h \
	Common/Flow.h \
	Common/ModuleAccess.h \
	Common/PDU.h \
	Common/PDU_m.h \
	Common/Policy.h \
	Common/QosCube.h \
	Common/RINASignals.h \
	Common/SDU.h \
	Common/SDU_m.h \
	DAF/CDAP/CDAPMessage_m.h \
	DAF/IRM/ConnectionTable.h \
	DAF/IRM/ConnectionTableEntry.h \
	DIF/Delimiting/Delimiting.h \
	DIF/EFCP/ControlPDU_m.h \
	DIF/EFCP/DTCP.h \
	DIF/EFCP/DTCPState.h \
	DIF/EFCP/DTCPTimers_m.h \
	DIF/EFCP/DTP.h \
	DIF/EFCP/DTPState.h \
	DIF/EFCP/DTPTimers_m.h \
	DIF/EFCP/DataTransferPDU_m.h \
	DIF/EFCP/EFCP.h \
	DIF/EFCP/EFCPInstance.h \
	DIF/EFCP/EFCPTable/EFCPTable.h \
	DIF/EFCP/EFCPTable/EFCPTableEntry.h \
	DIF/EFCP/EFCP_defs.h \
	DIF/EFCP/FlowControl.h \
	DIF/EFCP/RXControl.h \
	DIF/EFCP/policies/DefaultTxControlPolicy.h \
	DIF/EFCP/policies/TxControlPolicy.h \
	DIF/FA/FA.h \
	DIF/FA/FABase.h \
	DIF/FA/FAI.h \
	DIF/FA/FAIListeners.h \
	DIF/FA/FAITable.h \
	DIF/FA/FAITableEntry.h \
	DIF/FA/FAListeners.h \
	DIF/RA/PDUForwardingTable.h \
	DIF/RA/PDUTableEntry.h \
	DIF/RMT/RMT.h
$O/DIF/FA/FABase.o: DIF/FA/FABase.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/Flow.h \
	Common/Policy.h \
	Common/QosCube.h \
	DIF/FA/FABase.h
$O/DIF/FA/FAI.o: DIF/FA/FAI.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/Data.h \
	Common/Data_m.h \
	Common/ExternConsts.h \
	Common/Flow.h \
	Common/ModuleAccess.h \
	Common/PDU.h \
	Common/PDU_m.h \
	Common/Policy.h \
	Common/QosCube.h \
	Common/RINASignals.h \
	Common/SDU.h \
	Common/SDU_m.h \
	DAF/CDAP/CDAPMessage_m.h \
	DAF/IRM/ConnectionTable.h \
	DAF/IRM/ConnectionTableEntry.h \
	DIF/Delimiting/Delimiting.h \
	DIF/EFCP/ControlPDU_m.h \
	DIF/EFCP/DTCP.h \
	DIF/EFCP/DTCPState.h \
	DIF/EFCP/DTCPTimers_m.h \
	DIF/EFCP/DTP.h \
	DIF/EFCP/DTPState.h \
	DIF/EFCP/DTPTimers_m.h \
	DIF/EFCP/DataTransferPDU_m.h \
	DIF/EFCP/EFCP.h \
	DIF/EFCP/EFCPInstance.h \
	DIF/EFCP/EFCPTable/EFCPTable.h \
	DIF/EFCP/EFCPTable/EFCPTableEntry.h \
	DIF/EFCP/EFCP_defs.h \
	DIF/EFCP/FlowControl.h \
	DIF/EFCP/RXControl.h \
	DIF/EFCP/policies/DefaultTxControlPolicy.h \
	DIF/EFCP/policies/TxControlPolicy.h \
	DIF/FA/FABase.h \
	DIF/FA/FAI.h \
	DIF/FA/FAIListeners.h \
	DIF/RA/PDUForwardingTable.h \
	DIF/RA/PDUTableEntry.h \
	DIF/RMT/RMT.h
$O/DIF/FA/FAIListeners.o: DIF/FA/FAIListeners.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/Data.h \
	Common/Data_m.h \
	Common/ExternConsts.h \
	Common/Flow.h \
	Common/ModuleAccess.h \
	Common/PDU.h \
	Common/PDU_m.h \
	Common/Policy.h \
	Common/QosCube.h \
	Common/RINASignals.h \
	Common/SDU.h \
	Common/SDU_m.h \
	DAF/CDAP/CDAPMessage_m.h \
	DAF/IRM/ConnectionTable.h \
	DAF/IRM/ConnectionTableEntry.h \
	DIF/Delimiting/Delimiting.h \
	DIF/EFCP/ControlPDU_m.h \
	DIF/EFCP/DTCP.h \
	DIF/EFCP/DTCPState.h \
	DIF/EFCP/DTCPTimers_m.h \
	DIF/EFCP/DTP.h \
	DIF/EFCP/DTPState.h \
	DIF/EFCP/DTPTimers_m.h \
	DIF/EFCP/DataTransferPDU_m.h \
	DIF/EFCP/EFCP.h \
	DIF/EFCP/EFCPInstance.h \
	DIF/EFCP/EFCPTable/EFCPTable.h \
	DIF/EFCP/EFCPTable/EFCPTableEntry.h \
	DIF/EFCP/EFCP_defs.h \
	DIF/EFCP/FlowControl.h \
	DIF/EFCP/RXControl.h \
	DIF/EFCP/policies/DefaultTxControlPolicy.h \
	DIF/EFCP/policies/TxControlPolicy.h \
	DIF/FA/FABase.h \
	DIF/FA/FAI.h \
	DIF/FA/FAIListeners.h \
	DIF/RA/PDUForwardingTable.h \
	DIF/RA/PDUTableEntry.h \
	DIF/RMT/RMT.h
$O/DIF/FA/FAITable.o: DIF/FA/FAITable.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/Data.h \
	Common/Data_m.h \
	Common/ExternConsts.h \
	Common/Flow.h \
	Common/ModuleAccess.h \
	Common/PDU.h \
	Common/PDU_m.h \
	Common/Policy.h \
	Common/QosCube.h \
	Common/RINASignals.h \
	Common/SDU.h \
	Common/SDU_m.h \
	DAF/CDAP/CDAPMessage_m.h \
	DAF/IRM/ConnectionTable.h \
	DAF/IRM/ConnectionTableEntry.h \
	DIF/Delimiting/Delimiting.h \
	DIF/EFCP/ControlPDU_m.h \
	DIF/EFCP/DTCP.h \
	DIF/EFCP/DTCPState.h \
	DIF/EFCP/DTCPTimers_m.h \
	DIF/EFCP/DTP.h \
	DIF/EFCP/DTPState.h \
	DIF/EFCP/DTPTimers_m.h \
	DIF/EFCP/DataTransferPDU_m.h \
	DIF/EFCP/EFCP.h \
	DIF/EFCP/EFCPInstance.h \
	DIF/EFCP/EFCPTable/EFCPTable.h \
	DIF/EFCP/EFCPTable/EFCPTableEntry.h \
	DIF/EFCP/EFCP_defs.h \
	DIF/EFCP/FlowControl.h \
	DIF/EFCP/RXControl.h \
	DIF/EFCP/policies/DefaultTxControlPolicy.h \
	DIF/EFCP/policies/TxControlPolicy.h \
	DIF/FA/FABase.h \
	DIF/FA/FAI.h \
	DIF/FA/FAIListeners.h \
	DIF/FA/FAITable.h \
	DIF/FA/FAITableEntry.h \
	DIF/RA/PDUForwardingTable.h \
	DIF/RA/PDUTableEntry.h \
	DIF/RMT/RMT.h
$O/DIF/FA/FAITableEntry.o: DIF/FA/FAITableEntry.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/Data.h \
	Common/Data_m.h \
	Common/ExternConsts.h \
	Common/Flow.h \
	Common/ModuleAccess.h \
	Common/PDU.h \
	Common/PDU_m.h \
	Common/Policy.h \
	Common/QosCube.h \
	Common/RINASignals.h \
	Common/SDU.h \
	Common/SDU_m.h \
	DAF/CDAP/CDAPMessage_m.h \
	DAF/IRM/ConnectionTable.h \
	DAF/IRM/ConnectionTableEntry.h \
	DIF/Delimiting/Delimiting.h \
	DIF/EFCP/ControlPDU_m.h \
	DIF/EFCP/DTCP.h \
	DIF/EFCP/DTCPState.h \
	DIF/EFCP/DTCPTimers_m.h \
	DIF/EFCP/DTP.h \
	DIF/EFCP/DTPState.h \
	DIF/EFCP/DTPTimers_m.h \
	DIF/EFCP/DataTransferPDU_m.h \
	DIF/EFCP/EFCP.h \
	DIF/EFCP/EFCPInstance.h \
	DIF/EFCP/EFCPTable/EFCPTable.h \
	DIF/EFCP/EFCPTable/EFCPTableEntry.h \
	DIF/EFCP/EFCP_defs.h \
	DIF/EFCP/FlowControl.h \
	DIF/EFCP/RXControl.h \
	DIF/EFCP/policies/DefaultTxControlPolicy.h \
	DIF/EFCP/policies/TxControlPolicy.h \
	DIF/FA/FABase.h \
	DIF/FA/FAI.h \
	DIF/FA/FAIListeners.h \
	DIF/FA/FAITableEntry.h \
	DIF/RA/PDUForwardingTable.h \
	DIF/RA/PDUTableEntry.h \
	DIF/RMT/RMT.h
$O/DIF/FA/FAListeners.o: DIF/FA/FAListeners.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/Flow.h \
	Common/Policy.h \
	Common/QosCube.h \
	DIF/FA/FABase.h \
	DIF/FA/FAListeners.h
$O/DIF/NSM/DirectoryForwardingTable.o: DIF/NSM/DirectoryForwardingTable.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	DIF/NSM/DirectoryForwardingTable.h
$O/DIF/NSM/LocalDirectoryCache.o: DIF/NSM/LocalDirectoryCache.cc \
	DIF/NSM/LocalDirectoryCache.h
$O/DIF/NSM/NSM.o: DIF/NSM/NSM.cc \
	DIF/NSM/NSM.h
$O/DIF/RA/PDUForwardingTable.o: DIF/RA/PDUForwardingTable.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/Flow.h \
	Common/Policy.h \
	Common/QosCube.h \
	DAF/IRM/ConnectionTable.h \
	DAF/IRM/ConnectionTableEntry.h \
	DIF/FA/FABase.h \
	DIF/RA/PDUForwardingTable.h \
	DIF/RA/PDUTableEntry.h
$O/DIF/RA/PDUFwdTabGenerator.o: DIF/RA/PDUFwdTabGenerator.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/Flow.h \
	Common/ModuleAccess.h \
	Common/PDU_m.h \
	Common/Policy.h \
	Common/QosCube.h \
	DAF/CDAP/CDAPMessage_m.h \
	DAF/IRM/ConnectionTable.h \
	DAF/IRM/ConnectionTableEntry.h \
	DIF/FA/FABase.h \
	DIF/RA/PDUForwardingTable.h \
	DIF/RA/PDUFwdTabGenerator.h \
	DIF/RA/PDUTableEntry.h \
	DIF/RMT/RMT.h
$O/DIF/RA/PDUTableEntry.o: DIF/RA/PDUTableEntry.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/Flow.h \
	Common/Policy.h \
	Common/QosCube.h \
	DAF/IRM/ConnectionTable.h \
	DAF/IRM/ConnectionTableEntry.h \
	DIF/FA/FABase.h \
	DIF/RA/PDUTableEntry.h
$O/DIF/RA/RA.o: DIF/RA/RA.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/Data.h \
	Common/Data_m.h \
	Common/ExternConsts.h \
	Common/Flow.h \
	Common/ModuleAccess.h \
	Common/PDU.h \
	Common/PDU_m.h \
	Common/Policy.h \
	Common/QosCube.h \
	Common/RINASignals.h \
	Common/SDU.h \
	Common/SDU_m.h \
	DAF/CDAP/CDAPMessage_m.h \
	DAF/DA/DA.h \
	DAF/DA/Directory.h \
	DAF/DA/DirectoryEntry.h \
	DAF/DA/NamingInformation.h \
	DAF/DA/NeighborTable.h \
	DAF/DA/SearchTable.h \
	DAF/IRM/ConnectionTable.h \
	DAF/IRM/ConnectionTableEntry.h \
	DIF/Delimiting/Delimiting.h \
	DIF/EFCP/ControlPDU_m.h \
	DIF/EFCP/DTCP.h \
	DIF/EFCP/DTCPState.h \
	DIF/EFCP/DTCPTimers_m.h \
	DIF/EFCP/DTP.h \
	DIF/EFCP/DTPState.h \
	DIF/EFCP/DTPTimers_m.h \
	DIF/EFCP/DataTransferPDU_m.h \
	DIF/EFCP/EFCP.h \
	DIF/EFCP/EFCPInstance.h \
	DIF/EFCP/EFCPTable/EFCPTable.h \
	DIF/EFCP/EFCPTable/EFCPTableEntry.h \
	DIF/EFCP/EFCP_defs.h \
	DIF/EFCP/FlowControl.h \
	DIF/EFCP/RXControl.h \
	DIF/EFCP/policies/DefaultTxControlPolicy.h \
	DIF/EFCP/policies/TxControlPolicy.h \
	DIF/FA/FA.h \
	DIF/FA/FABase.h \
	DIF/FA/FAI.h \
	DIF/FA/FAIListeners.h \
	DIF/FA/FAITable.h \
	DIF/FA/FAITableEntry.h \
	DIF/FA/FAListeners.h \
	DIF/RA/PDUForwardingTable.h \
	DIF/RA/PDUTableEntry.h \
	DIF/RA/RA.h \
	DIF/RMT/RMT.h
$O/DIF/RIB/RIBDaemon.o: DIF/RIB/RIBDaemon.cc \
	DIF/RIB/RIBDaemon.h
$O/DIF/RMT/RMT.o: DIF/RMT/RMT.cc \
	Common/APN.h \
	Common/APNamingInfo.h \
	Common/Address.h \
	Common/ConnectionId.h \
	Common/Flow.h \
	Common/ModuleAccess.h \
	Common/PDU_m.h \
	Common/Policy.h \
	Common/QosCube.h \
	DAF/CDAP/CDAPMessage_m.h \
	DAF/IRM/ConnectionTable.h \
	DAF/IRM/ConnectionTableEntry.h \
	DIF/FA/FABase.h \
	DIF/RA/PDUForwardingTable.h \
	DIF/RA/PDUTableEntry.h \
	DIF/RMT/RMT.h
$O/DIF/RMT/RMTPort.o: DIF/RMT/RMTPort.cc \
	Common/APN.h \
	Common/ConnectionId.h \
	Common/PDU.h \
	Common/PDU_m.h \
	Common/Policy.h \
	Common/QosCube.h \
	DIF/EFCP/DataTransferPDU_m.h \
	DIF/RMT/RMTPort.h \
	DIF/RMT/RMTQueue.h
$O/DIF/RMT/RMTPortManager.o: DIF/RMT/RMTPortManager.cc \
	Common/APN.h \
	Common/ConnectionId.h \
	Common/PDU.h \
	Common/PDU_m.h \
	Common/Policy.h \
	Common/QosCube.h \
	DIF/EFCP/DataTransferPDU_m.h \
	DIF/RMT/RMTPort.h \
	DIF/RMT/RMTPortManager.h \
	DIF/RMT/RMTQueue.h
$O/DIF/RMT/RMTQueue.o: DIF/RMT/RMTQueue.cc \
	Common/APN.h \
	Common/ConnectionId.h \
	Common/PDU.h \
	Common/PDU_m.h \
	Common/Policy.h \
	Common/QosCube.h \
	DIF/EFCP/DataTransferPDU_m.h \
	DIF/RMT/RMTQueue.h
$O/DIF/RMT/policies/MaxQPolicy.o: DIF/RMT/policies/MaxQPolicy.cc \
	DIF/RMT/policies/MaxQPolicy.h
$O/DIF/RMT/policies/RMTQMonitorPolicy.o: DIF/RMT/policies/RMTQMonitorPolicy.cc \
	DIF/RMT/policies/RMTQMonitorPolicy.h
$O/DIF/RMT/policies/RMTSchedulingPolicy.o: DIF/RMT/policies/RMTSchedulingPolicy.cc \
	DIF/RMT/policies/RMTSchedulingPolicy.h

