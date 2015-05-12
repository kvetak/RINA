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

#ifndef EXTERNCONSTS_H_
#define EXTERNCONSTS_H_

#include <sstream>

//Module names
extern const char* MOD_FLOWALLOC;
extern const char* MOD_FA;
extern const char* MOD_CONNTABLE;
extern const char* MOD_DA;
extern const char* MOD_DIFALLOC;
extern const char* MOD_EFCP;
extern const char* MOD_FAITABLE;
extern const char* MOD_RESALLOC;
extern const char* MOD_RA;
extern const char* MOD_IAE;
extern const char* MOD_IRM;
extern const char* MOD_IPCRESMANAGER;
extern const char* MOD_CDAP;
extern const char* MOD_CDAPMSGLOG;
extern const char* MOD_CDAPSPLIT;
extern const char* MOD_CDAPCACE;
extern const char* MOD_CDAPAUTH;
extern const char* MOD_CDAPCDAP;
extern const char* MOD_EFCPTABLE;
extern const char* MOD_DTCP;
extern const char* MOD_DTP_STATE;
extern const char* MOD_DTCP_STATE;
extern const char* MOD_EFCPI;

//Module type paths
extern const char* MOD_EFCP_PATH;
extern const char* MOD_EFCPI_PATH;
extern const char* MOD_DTP_PATH;
extern const char* MOD_DTP_STATE_PATH;
extern const char* MOD_DTCP_PATH;
extern const char* MOD_DTCP_STATE_PATH;
extern const char* MOD_DELIMITING_PATH;

//Module parameters
extern const char* PAR_IPCADDR;
extern const char* PAR_DIFNAME;
extern const char* PAR_LOCALPORTID;
extern const char* PAR_LOCALCEPID;
extern const char* PAR_REMOTEPORTID;
extern const char* PAR_REMOTECEPID;
extern const char* PAR_APNAME;
extern const char* PAR_APINSTANCE;
extern const char* PAR_AENAME;
extern const char* PAR_AEINSTANCE;
extern const char* PAR_CONFIGDATA;
extern const char* PAR_CREREQTIMEOUT;
extern const char* PAR_CURINVOKEID;

//TODO:Marek @Vesely Your naming scheme seems little bit ambiguous to me. Modules usually have two inout gates.
//Gate names
extern const char* GATE_SOUTHIO;
extern const char* GATE_NORTHIO;
extern const char* GATE_NORTHIO_;
extern const char* GATE_SOUTHIO_;
extern const char* GATE_EFCPIO_;
extern const char* GATE_RMT_;
extern const char* GATE_RMTIO;
extern const char* GATE_APPIO_;
extern const char* GATE_AEIO;
extern const char* GATE_DATAIO;
extern const char* GATE_SPLITIO;
extern const char* GATE_CACEIO;
extern const char* GATE_AUTHIO;
extern const char* GATE_CDAPIO;
extern const char* GATE_DTP_NORTHIO;
extern const char* GATE_DTP_SOUTHIO;
extern const char* GATE_EFCPI_NORTHIO;
extern const char* GATE_EFCPI_SOUTHIO;

//XML attributes and elements
extern const char* ELEM_APN;
extern const char* ATTR_APN;
extern const char* ELEM_AVGBW;
extern const char* ELEM_AVGSDUBW;
extern const char* ELEM_PEAKBWDUR;
extern const char* ELEM_PEAKSDUBWDUR;
extern const char* ELEM_BURSTPERIOD;
extern const char* ELEM_BURSTDURATION;
extern const char* ELEM_UNDETECTBITERR;
extern const char* ELEM_PDUDROPPROBAB;
extern const char* ELEM_MAXSDUSIZE;
extern const char* ELEM_PARTIALDELIVER;
extern const char* ELEM_INCOMPLETEDELIVER;
extern const char* ELEM_FORCEORDER;
extern const char* ELEM_MAXALLOWGAP;
extern const char* ELEM_DELAY;
extern const char* ELEM_JITTER;
extern const char* ELEM_COSTTIME;
extern const char* ELEM_COSTBITS;

//Values
extern const int    VAL_QOSPARDONOTCARE;
extern const bool   VAL_QOSPARDEFBOOL;
extern const int    UNINIT_INVOKEID;
extern const int    DONTCARE_INVOKEID;
extern const int    VAL_UNDEF_PORTID;


class ExternConsts {
  public:
    static const char* prepareCiName(const char* name) {
        std::ostringstream os;
        os << "CI-" << name;
        return os.str().c_str();
    }
};

#endif /* EXTERNCONSTS_H_ */
