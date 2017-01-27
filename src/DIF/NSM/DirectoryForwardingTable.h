//
// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
/**
 * @file DirectoryForwardingTable.h
 * @author Vladimir Vesely (ivesely@fit.vutbr.cz)
 * @date Apr 30, 2014
 * @brief
 * @detail
 */

#ifndef DIRECTORYFORWARDINGTABLE_H_
#define DIRECTORYFORWARDINGTABLE_H_

//Standard libraries
#include <map>
#include <string>
#include "Common/APNamingInfo.h"
#include <omnetpp.h>
//RINASim libraries
//#include <DFFMapping.h>

typedef std::map<APNamingInfo, std::string> DFTMappings;

class DirectoryForwardingTable : public cSimpleModule {
public:
    DirectoryForwardingTable();
    virtual ~DirectoryForwardingTable();

    std::string search(APNamingInfo apni);
    void add(APNamingInfo apni, std::string addr);
    void remove(APNamingInfo apni);
    void update(APNamingInfo apni);

protected:
  virtual void initialize();
  virtual void handleMessage(cMessage *msg);

private:
    DFTMappings dffMap;
};

#endif /* DIRECTORYFORWARDINGTABLE_H_ */
