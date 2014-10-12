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

#include <ExternConsts.h>

//Module names
const char* MOD_FLOWALLOC       = "flowAllocator";
const char* MOD_FA              = "fa";
const char* MOD_CONNTABLE       = "connectionTable";
const char* MOD_DA              = "da";
const char* MOD_FAITABLE        = "faiTable";
const char* MOD_EFCP            = "efcp";
const char* MOD_RESALLOC        = "resourceAllocator";
const char* MOD_RA              = "ra";
const char* MOD_IRM             = "irm";
const char* MOD_EFCPTABLE       = "efcpTable";
const char* MOD_DTCP            = "dtcp";

//Module parameters
const char* PAR_IPCADDR         = "ipcAddress";
const char* PAR_DIFNAME         = "difName";
const char* PAR_PORTID          = "portId";
const char* PAR_CEPID           = "cepId";
const char* PAR_APNAME          = "apName";
const char* PAR_APINSTANCE      = "apInstance";
const char* PAR_AENAME          = "aeName";
const char* PAR_AEINSTANCE      = "aeInstance";
const char* PAR_CONFIGDATA      = "configData";

//Gate names
const char* GATE_NORTHIO        = "northIo_";
const char* GATE_SOUTHIO        = "southIo_";
const char* GATE_EFCPIO         = "efcpIo_";
const char* GATE_RMT            = "rmt_";
const char* GATE_APPIO          = "appIo_";
const char* GATE_AEIO           = "aeIo";
const char* GATE_DATAIO         = "dataIo";
const char* GATE_DTP_NORTHIO    = "northIo";
const char* GATE_DTP_SOUTHIO    = "southIo";
const char* GATE_EFCPI_NORTHIO  = "northIo";
const char* GATE_EFCPI_SOUTHIO  = "southIo";

//XML attributes and elements
const char* ELEM_APN         = "APN";
const char* ATTR_APN            = "apn";

//Values
//TODO: Vesely @Marek - What about -1 as default DoNotCare value
//TODO: Marek @Vesely - OK
const int   VAL_QOSPARAMDONOTCARE    = -1;
const bool  VAL_QOSPARAMDEFBOOL      = false;

