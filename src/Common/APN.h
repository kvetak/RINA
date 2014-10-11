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

#ifndef APN_H_
#define APN_H_

#include <omnetpp.h>
#include <string>
#include <sstream>

class APN
{
  public:
    APN();
    APN(std::string nam);
    virtual ~APN();

    bool operator== (const APN& other) const {
        return !name.compare(other.getName());
    }

    std::string info() const;

    const std::string& getName() const;
    void setName(const std::string& name);

  private:
    std::string name;

};

typedef std::list<APN> APNList;
typedef APNList::const_iterator ApnCItem;
typedef APNList::iterator ApnItem;

//Free functions
std::ostream& operator<< (std::ostream& os, const APN& apn);
std::ostream& operator<< (std::ostream& os, const APNList& apns);

#endif /* APN_H_ */
