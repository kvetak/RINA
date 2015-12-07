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

#ifndef NAMINGINFORMATIONENTRY_H_
#define NAMINGINFORMATIONENTRY_H_

//RINASim libraries
#include "APN.h"

class NamingInformationEntry {
  public:
    NamingInformationEntry(const APN& napn);
    virtual ~NamingInformationEntry();

    bool operator== (const NamingInformationEntry& other) const;

    const APN& getApn() const;
    void setApn(const APN& apn);
    const std::list<APN>& getSynonyms() const;
    void setSynonyms(const std::list<APN>& synonyms);

    std::string info() const;

    void addSynonym(const APN& synonym);
    bool hasSynonym(const APN& synonym);
  private:
    APN Apn;
    APNList Synonyms;
};


//Free function
std::ostream& operator<< (std::ostream& os, const NamingInformationEntry& nie);

#endif /* NAMINGINFORMATIONENTRY_H_ */
