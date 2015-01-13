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

cplusplus {{

#include <vector>
#include "CDAPMessage_m.h"
#include "Data.h"
typedef std::vector<CDAPMessage*> mUserDataType;
}}

message Data;
class noncobject mUserDataType;

enum FragmentType{
    	SDU_FRAG_FIRST 		= 0x01;
    	SDU_FRAG_MIDDLE		= 0x00;
    	SDU_FRAG_LAST		= 0x02;
}

message SDU extends Data {
    @customize(true);
    unsigned int size = 0;
    unsigned int offset = 0;
    
    
    unsigned int fSize = 0;
    unsigned int fOffset = 0;
    
    unsigned int seqNum = 0;
    unsigned int fSeqNum = 0;
    
    int fragType enum(FragmentType) = 0	;
    
}
