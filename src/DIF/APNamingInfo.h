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

#ifndef APNAMINGINFO_H_
#define APNAMINGINFO_H_

#include <string>
#include <APN.h>

class APNamingInfo {
public:
    APNamingInfo();
    virtual ~APNamingInfo();

    const std::string& getAeinstance() const {
        return aeinstance;
    }

    void setAeinstance(const std::string& aeinstance) {
        this->aeinstance = aeinstance;
    }

    const std::string& getAename() const {
        return aename;
    }

    void setAename(const std::string& aename) {
        this->aename = aename;
    }

    const std::string& getApinstance() const {
        return apinstance;
    }

    void setApinstance(const std::string& apinstance) {
        this->apinstance = apinstance;
    }

    const APN& getApn() const {
        return apn;
    }

    void setApn(const APN& apn) {
        this->apn = apn;
    }

private:
    APN apn;
    std::string apinstance;
    std::string aename;
    std::string aeinstance;
};

#endif /* APNAMINGINFO_H_ */
