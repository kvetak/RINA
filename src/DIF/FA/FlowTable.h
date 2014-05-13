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

#ifndef FLOWTABLE_H_
#define FLOWTABLE_H_

//Standard libraries
#include <omnetpp.h>
#include <stdint.h>
//RINASim libraries
#include "Flow.h"

class FlowTable : public cModule {

    typedef std::list<Flow>::iterator ftIter;

public:
    FlowTable();
    virtual ~FlowTable();

    //TODO: VV - Think about changing container to something better
    //List of all allocated flows
    std::list<Flow> flowTable;

    void add(Flow fl);
    void remove(Flow fl);
    void search(uint64_t port);

};

#endif /* FLOWTABLE_H_ */
