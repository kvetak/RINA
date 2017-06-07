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

#ifndef DAF_RIB_RIB_RIB_H_
#define DAF_RIB_RIB_RIB_H_

#include "DAF/RIB/RIB/Tree/RIBTreeNode.h"
#include "DAF/RIB/RIB/Tree/RIBTreeNodeObj.h"
#include "DAF/CDAP/CDAPMessage_m.h"
#include "DAF/RIB/RIB/RIBBase.h"

class RIB : public RIBBase {
public:
    RIB();
    virtual ~RIB();

    virtual bool createAE(std::string AEName);
    virtual bool createIAE(std::string IAEName, AEBase* ae);
    virtual bool deleteAE(std::string AEName);
    virtual bool deleteIAE(std::string IAEName);

    virtual object_t* createObj(int CDAPConn, object_t *obj);
    virtual object_t* deleteObj(int CDAPConn, std::string objName);
    virtual object_t* writeObj(int CDAPConn, object_t *obj);
    virtual object_t* readObj(int CDAPConn, std::string objName);

protected:
    virtual object_t* findObj(int CDAPConn, std::string objName);

    RIBTreeNodeObj *objRoot;
    RIBTreeNode *treeRoot;
};

#endif /* DAF_RIB_RIB_RIB_H_ */
