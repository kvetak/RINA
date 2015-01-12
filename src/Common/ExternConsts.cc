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
const char* MOD_DIFALLOC        = "difAllocator";
const char* MOD_FAITABLE        = "faiTable";
const char* MOD_EFCP            = "efcp";
const char* MOD_RESALLOC        = "resourceAllocator";
const char* MOD_RA              = "ra";
const char* MOD_IRM             = "irm";
const char* MOD_IPCRESMANAGER   = "ipcResourceManager";
const char* MOD_CDAP            = "commonDistributedApplicationProtocol";
const char* MOD_CDAPMSGLOG      = "cdapMsgLog";
const char* MOD_CDAPSPLIT       = "cdapSplitter";
const char* MOD_CDAPCACE        = "cace";
const char* MOD_CDAPAUTH        = "auth";
const char* MOD_CDAPCDAP        = "cdap";


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
const char* GATE_SOUTHIO        = "southIo";
const char* GATE_NORTHIO        = "northIo";
const char* GATE_NORTHIO_       = "northIo_";
const char* GATE_SOUTHIO_       = "southIo_";
const char* GATE_EFCPIO_        = "efcpIo_";
const char* GATE_RMT_           = "rmt_";
const char* GATE_RMTIO          = "rmtIo";
const char* GATE_APPIO_         = "appIo_";
const char* GATE_AEIO           = "aeIo";
const char* GATE_DATAIO         = "dataIo";
const char* GATE_SPLITIO        = "splitterIo";
const char* GATE_CACEIO         = "caceIo";
const char* GATE_AUTHIO         = "authIo";
const char* GATE_CDAPIO         = "cdapIo";

//XML attributes and elements
const char* ELEM_APN            = "APN";
const char* ATTR_APN            = "apn";

//Values
//TODO: Vesely @Marek - What about -1 as default DoNotCare value
const int   VAL_QOSPARDONOTCARE = -1;
const bool  VAL_QOSPARDEFBOOL   = false;

