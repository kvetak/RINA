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
extern const char* MOD_EFCP;
extern const char* MOD_FAITABLE;
extern const char* MOD_RESALLOC;
extern const char* MOD_RA;
extern const char* MOD_IRM;
extern const char* MOD_CDAP;
extern const char* MOD_CDAPMSGLOG;
extern const char* MOD_CDAPSPLIT;
extern const char* MOD_CDAPCACE;
extern const char* MOD_CDAPAUTH;
extern const char* MOD_CDAPCDAP;

//Module parameters
extern const char* PAR_IPCADDR;
extern const char* PAR_DIFNAME;
extern const char* PAR_PORTID;
extern const char* PAR_CEPID;
extern const char* PAR_APNAME;
extern const char* PAR_APINSTANCE;
extern const char* PAR_AENAME;
extern const char* PAR_AEINSTANCE;
extern const char* PAR_CONFIGDATA;

//Gate names
extern const char* GATE_SOUTHIO;
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

//XML attributes and elements
extern const char* ELEM_APN;
extern const char* ATTR_APN;

//Values
extern const int   VAL_QOSPARDONOTCARE;
extern const bool  VAL_QOSPARDEFBOOL;


class ExternConsts {
  public:
    static const char* prepareCiName(const char* name) {
        std::ostringstream os;
        os << "CI-" << name;
        return os.str().c_str();
    }
};

#endif /* EXTERNCONSTS_H_ */
