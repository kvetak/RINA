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

#ifndef SDU_H_
#define SDU_H_


#include <cobject.h>

class SDU: public cObject {

private:
    unsigned char * userData;
    unsigned int size;
    unsigned int offset;

public:
    SDU();
    virtual ~SDU();
    unsigned int getSize() const;
    unsigned int getRestSize() const;
    void setSize(unsigned int size);
    unsigned char* getUserData() const;
    const unsigned char* getUserData(unsigned int offset);
    void setUserData(unsigned char* userData, unsigned int size);
};

#endif /* SDU_H_ */
