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

#ifndef APN_H_
#define APN_H_

#include <string>
#include <omnetpp.h>

/* Application Process Name
 *
 */
class APN {
private:
    std::string apname;
    std::string apinstance;
    std::string aename;
    std::string aeinstance;

public:
    APN();
    APN(std::string nam);
    virtual ~APN();

    const std::string& getAeinstance() const;
    void setAeinstance(const std::string& aeinstance);
    const std::string& getAename() const;
    void setAename(const std::string& aename);
    const std::string& getApinstance() const;
    void setApinstance(const std::string& apinstance);
    const std::string& getApname() const;
    void setApname(const std::string& apname);
};

#endif /* APN_H_ */
