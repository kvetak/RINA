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

#include <RIB/RIB.h>

RIB::RIB() {
    // TODO Auto-generated constructor stub

}

RIB::~RIB() {
    // TODO Auto-generated destructor stub
}

/*
 * @AEName - expects format "/ae"
 */
bool RIB::createAE(std::string AEName) {
    RIBTreeNode *node = new RIBTreeNode(AEName);

    if (this->treeRoot == NULL) {
        this->treeRoot = node;
    }
    else {
        this->treeRoot->create(node);
    }
}

bool RIB::createIAE(std::string IAEName, AEBase* ae) {
    RIBTreeNode *node = new RIBTreeNode(AEName);
    node->setAE(ae);

    if (this->treeRoot == NULL) {
        this->treeRoot = node;
    }
    else {
        this->treeRoot->create(node);
    }
}

bool RIB::deleteAE(std::string AEName) {
    if (this->treeRoot != NULL) {
        this->treeRoot->deleteNode(AEName);
    }
}

bool RIB::deleteIAE(std::string IAEName) {
    if (this->treeRoot != NULL) {
        this->treeRoot->deleteNode(AEName);
    }
}

object_t* RIB::createObj(int CDAPConn, object_t *obj) {
    return NULL;
}

object_t* RIB::deleteObj(int CDAPConn, object_t *obj) {
    return NULL;
}

object_t* RIB::writeObj(int CDAPConn, object_t *obj) {
    return NULL;
}

object_t* RIB::readObj(int CDAPConn, std::string objName) {
    return NULL;
}

object_t* RIB::findObj(int CDAPConn, std::string objName) {
    return NULL;
}
