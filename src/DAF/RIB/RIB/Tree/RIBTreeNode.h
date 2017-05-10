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

#ifndef DAF_RIB_RIB_TREE_RIBTREENODE_H_
#define DAF_RIB_RIB_TREE_RIBTREENODE_H_

#include "Tree/RIBTreeNodeObj.h"
#include <omnetpp.h>
#include <queue>

class RIBTreeNode {
public:
    RIBTreeNode();
    RIBTreeNode(std::string path);
    RIBTreeNode(RIBTreeNode *parent, std::string path);
    virtual ~RIBTreeNode();

    RIBTreeNode *search(std::string name);
    RIBTreeNode *searchExactMatch(std::string name);
    RIBTreeNode *searchByPath(std::string path);
    RIBTreeNode *searchByPathExactMatch(std::string path);

    RIBTreeNode *create(RIBTreeNode *node);
    void deleteNode(std::string path);

    RIBTreeNode *getLeftChild();
    RIBTreeNode *getRightChild();
    RIBTreeNode *getParentNode();
    RIBTreeNode *getSubLevelRoot();
    RIBTreeNodeObj *getObjRoot();
    AEBase *getAE();

    std::string getName();
    std::string getPath();

    std::queue<std::string> parsePath(std::string path);

    void setLeftChild(RIBTreeNode *node);
    void setRightChild(RIBTreeNode *node);
    void setParentNode(RIBTreeNode *node);
    void setSubLevelRoot(RIBTreeNode *node);
    void setObjRoot(RIBTreeNodeObj *node);
    void setAE(AEBase *ae);

protected:
    RIBTreeNode *parent;
    RIBTreeNode *leftChild;
    RIBTreeNode *rightChild;

    RIBTreeNode *subLevelRoot;

    RIBTreeNodeObj *objRoot;

    AEBase *ae;

    std::string name;
    std::string path;

};

#endif /* DAF_RIB_RIB_TREE_RIBTREENODE_H_ */
