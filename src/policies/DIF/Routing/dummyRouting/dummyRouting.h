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

#ifndef dummyRouting_H_
#define dummyRouting_H_

#include <IntRouting.h>

class dummyRouting: public IntRouting {
public:
    //Process a Routing Update, return true => inform FWDG of the update
    bool processUpdate(const IntRoutingUpdate * update);

protected:
    // Called after initialize
    void onIni();
};

#endif /* dummyRouting_H_ */
