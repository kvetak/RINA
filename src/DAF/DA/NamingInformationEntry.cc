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

#include <NamingInformationEntry.h>

NamingInformationEntry::NamingInformationEntry(const APN& napn) :
    Apn(napn)
{
}

NamingInformationEntry::~NamingInformationEntry() {
    Synonyms.clear();
}

std::string NamingInformationEntry::info() const {
    std::ostringstream os;
    os << "APN: " << Apn << ", Synonyms: " << Synonyms;
    return os.str();
}

void NamingInformationEntry::addSynonym(const APN& synonym) {
    Synonyms.push_back(synonym);
}

const APN& NamingInformationEntry::getApn() const {
    return Apn;
}

void NamingInformationEntry::setApn(const APN& apn) {
    this->Apn = apn;
}

const std::list<APN>& NamingInformationEntry::getSynonyms() const {
    return Synonyms;
}

void NamingInformationEntry::setSynonyms(const std::list<APN>& synonyms) {
    this->Synonyms = synonyms;
}

std::ostream& operator <<(std::ostream& os, const NamingInformationEntry& nie) {
    return os << nie.info();
}

bool NamingInformationEntry::operator ==(
        const NamingInformationEntry& other) const {
    return this->Apn == other.Apn && this->Synonyms == other.Synonyms;
}

bool NamingInformationEntry::hasSynonym(const APN& synonym) {
    for (ApnCItem it = Synonyms.begin(); it != Synonyms.end(); ++it) {
       if (*it == synonym)
           return true;
    }
    return false;
}
