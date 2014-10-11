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

#include <DAP.h>

DAP::DAP() : name("")
{
}

DAP::DAP(std::string nam) : name(nam)
{
}


DAP::~DAP() {
    name = "";
}

bool DAP::operator ==(const DAP& other) const {
    return !name.compare(other.getName());
}

std::string DAP::info() const {
    std::stringstream os;
    os << this->getName();
    return os.str();
}

const std::string& DAP::getName() const {
    return name;
}


void DAP::setName(const std::string& name) {
    this->name = name;
}

std::ostream& operator <<(std::ostream& os, const DAP& dap) {
    return os << dap.info();
}
