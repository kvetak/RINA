//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
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

#include "APN.h"

APN::APN() {
    // TODO Auto-generated constructor stub

}

APN::APN(std::string nam) {
    this->apname = nam;
}

const std::string& APN::getAeinstance() const {
    return aeinstance;
}

void APN::setAeinstance(const std::string& aeinstance) {
    this->aeinstance = aeinstance;
}

const std::string& APN::getAename() const {
    return aename;
}

void APN::setAename(const std::string& aename) {
    this->aename = aename;
}

const std::string& APN::getApinstance() const {
    return apinstance;
}

void APN::setApinstance(const std::string& apinstance) {
    this->apinstance = apinstance;
}

const std::string& APN::getApname() const {
    return apname;
}

void APN::setApname(const std::string& apname) {
    this->apname = apname;
}

APN::~APN() {
    // TODO Auto-generated destructor stub
}
