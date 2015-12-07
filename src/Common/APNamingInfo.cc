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

#include "APNamingInfo.h"

APNamingInfo::APNamingInfo() :
    apn(APN()), apinstance(""),
    aename(""), aeinstance("")
{
}

APNamingInfo::APNamingInfo(APN napn) : apinstance(""), aename(""), aeinstance("")
{
    this->apn = napn;
}

APNamingInfo::APNamingInfo(APN napn, std::string napinstance,
        std::string naename, std::string naeinstance) :
        apn(napn), apinstance(napinstance),
        aename(naename), aeinstance(naeinstance)
{
}

APNamingInfo::~APNamingInfo()
{
    this->apn = APN();
    this->apinstance = "";
    this->aename = "";
    this->aeinstance = "";
}

std::string APNamingInfo::info() const
{
    std::ostringstream os;
    os << "AP: "<< apn;
    if (!apinstance.empty())
        os << " (" << apinstance << ")";
    if (!aename.empty())
        os << " AE: " << aename;
    if (!aeinstance.empty())
        os << " (" << aeinstance << ")";
    //os << endl;
    return os.str();
}

//Free function
std::ostream& operator<< (std::ostream& os, const APNamingInfo& apni)
{
    return os << apni.info();
}

