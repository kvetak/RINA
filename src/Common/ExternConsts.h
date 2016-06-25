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

#ifndef EXTERNCONSTS_H_
#define EXTERNCONSTS_H_

#include <sstream>

//Static module names
extern const char* MOD_CDAP;
extern const char* MOD_CDAPAUTH;
extern const char* MOD_CDAPCACE;
extern const char* MOD_CDAPCDAP;
extern const char* MOD_CDAPMSGLOG;
extern const char* MOD_CDAPSPLIT;
extern const char* MOD_CONNTABLE;
extern const char* MOD_DA;
extern const char* MOD_DIFALLOC;
extern const char* MOD_DIRECTORY;
extern const char* MOD_DTCP;
extern const char* MOD_DTCP_STATE;
extern const char* MOD_DTP;
extern const char* MOD_DTP_STATE;
extern const char* MOD_EFCP;
extern const char* MOD_EFCPI;
extern const char* MOD_EFCPTABLE;
extern const char* MOD_ENROLLMENT;
extern const char* MOD_ENROLLMENTMODULE;
extern const char* MOD_ENROLLMENTTABLE;
extern const char* MOD_FA;
extern const char* MOD_FLOWALLOC;
extern const char* MOD_IAE;
extern const char* MOD_IPCRESMANAGER;
extern const char* MOD_IRM;
extern const char* MOD_NAMINFO;
extern const char* MOD_NEIGHBORTABLE;
extern const char* MOD_NFLOWTABLE;
extern const char* MOD_PDUFWDGEN;
extern const char* MOD_RA;
extern const char* MOD_RANM1FLOWTABLE;
extern const char* MOD_RELAYANDMUX;
extern const char* MOD_RESALLOC;
extern const char* MOD_RIBD;
extern const char* MOD_RIBDAEMON;
extern const char* MOD_RIBDSPLITTER;
extern const char* MOD_RMT;
extern const char* MOD_RMTALLOC;
extern const char* MOD_RMTPORT;
extern const char* MOD_SEARCHTAB;

//Policy module names
extern const char* MOD_POL_RA_ADDRCOMPARATOR;
extern const char* MOD_POL_RA_IDGENERATOR;
extern const char* MOD_POL_RA_QOSCOMPARER;
extern const char* MOD_POL_RA_QUEUEALLOC;
extern const char* MOD_POL_RMT_MAXQ;
extern const char* MOD_POL_RMT_PDUFWD;
extern const char* MOD_POL_RMT_QMONITOR;
extern const char* MOD_POL_RMT_SCHEDULER;
extern const char* MOD_POL_QUEUEALLOC;
extern const char* MOD_POL_ROUTING;

//Module type paths
extern const char* MOD_EFCP_PATH;
extern const char* MOD_EFCPI_PATH;
extern const char* MOD_DTP_PATH;
extern const char* MOD_DTP_STATE_PATH;
extern const char* MOD_DTCP_PATH;
extern const char* MOD_DTCP_STATE_PATH;
extern const char* MOD_DELIMITING_PATH;
extern const char* MOD_RMT_PORTWRAPPER;
extern const char* MOD_RMT_QUEUE;

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

//Gate names
extern const char* GATE_SOUTHIO;
extern const char* GATE_NORTHIO;
extern const char* GATE_NORTHIO_;
extern const char* GATE_SOUTHIO_;
extern const char* GATE_EFCPIO_;
extern const char* GATE_EFCPIO;
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
extern const char* ATTR_SRC;
extern const char* ATTR_DST;
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

extern const char* ELEM_ATIME;
extern const char* ELEM_RXON;
extern const char* ELEM_WINON;
extern const char* ELEM_RATEON;
extern const char* ELEM_EFCPPOL;
extern const char* ELEM_RESILIENCYFACTOR;

//Values
extern const int    VAL_QOSPARDONOTCARE;
extern const bool   VAL_QOSPARDEFBOOL;
extern const int    UNINIT_INVOKEID;
extern const int    DONTCARE_INVOKEID;
extern const int   VAL_DEFINSTANCE;

//extern const int    VAL_UNDEF_PORTID;

class ExternConsts {
  public:
    static const char* prepareCiName(const char* name) {
        std::ostringstream os;
        os << "CI-" << name;
        return os.str().c_str();
    }
};

#endif /* EXTERNCONSTS_H_ */
