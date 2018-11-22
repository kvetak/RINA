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

#include <RAFTLogObj.h>

RAFTLogObj::RAFTLogObj(unsigned int term, unsigned int index,
        CDAPMessage *entry) {
    this->term = term;
    this->index = index;
    this->entry = entry;
}

RAFTLogObj::~RAFTLogObj() {
    // TODO Auto-generated destructor stub
}

std::string RAFTLogObj::info() const {
    std::ostringstream os;

    os << "Term: " << this->term << "\n";
    os << "Index: " << this->index << "\n";
    os << "Command: ";

    if (dynamic_cast<CDAP_M_Write*>(this->entry)) {
        os << "CDAP_M_Write";
    }
    else if (dynamic_cast<CDAP_M_Create*>(this->entry)) {
        os << "CDAP_M_Create";
    }
    os << "\n";
    return os.str();
}

std::ostream& operator <<(std::ostream& os, const RAFTLogObj& obj) {
    return os << obj.info();
}
