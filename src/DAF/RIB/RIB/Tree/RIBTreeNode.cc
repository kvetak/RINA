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

#include <Tree/RIBTreeNode.h>

RIBTreeNode::RIBTreeNode() {
    this->parent = NULL;
    this->leftChild = NULL;
    this->rightChild = NULL;
    this->objRoot = NULL;
    this->subLevelRoot = NULL;
    this->ae = NULL;
}

RIBTreeNode::RIBTreeNode(std::string path) {
    this->path = path;
    this->name = this->getNameFromPath(path);
    this->parent = NULL;
    this->leftChild = NULL;
    this->rightChild = NULL;
    this->objRoot = NULL;
    this->subLevelRoot = NULL;
    this->ae = NULL;
}

RIBTreeNode::RIBTreeNode(RIBTreeNode *parent, std::string path) {
    this->path = path;
    this->name = this->getNameFromPath(path);
    this->parent = parent;
    this->leftChild = NULL;
    this->rightChild = NULL;
    this->objRoot = NULL;
    this->subLevelRoot = NULL;
    this->ae = NULL;
}

RIBTreeNode::~RIBTreeNode() {
    this->parent = NULL;
    this->leftChild = NULL;
    this->rightChild = NULL;
    this->objRoot = NULL;
    this->subLevelRoot = NULL;
    this->ae = NULL
}

/*
 * return - last name from path
 */
std::string RIBTreeNode::getNameFromPath(std::string path) {
    std::string tmp = path;
    while (tmp.find("/") != string::npos) {
        tmp = tmp.substr(tmp.find("/")+1);
    }

    return tmp;
}

/*
 * return - near match node
 */
RIBTreeNode *RIBTreeNode::search(std::string name) {
    RIBTreeNode *tmp = this;
    int cmp = 0;

    for (;;) {
        cmp = strcmp(name, tmp->getName());

        if (cmp == 0) {
            break;
        }
        else if (cmp < 0) {
            if (this->leftChild == NULL)
                break;
            else
                tmp = this->leftChild;
        }
        else if (cmp > 0) {
            if (this->rightChild == NULL)
                break;
            else
                tmp = this-rightChild;
        }
    }

    return tmp;
}

/*
 * return - exact match or NULL
 */
RIBTreeNode *RIBTreeNode::searchExactMatch(std::string name) {
    RIBTreeNode *tmp = this;
    int cmp = 0;

    tmp = this->search(name);

    if (!strcmp(name, tmp->getName()))
        return tmp;
    else
        return NULL;
}


/*
 * return - exact match or NULL
 */
RIBTreeNode *RIBTreeNode::searchByPathExactMatch(std::string path) {
    RIBTreeNode *tmp = this;
    std::string name = this->getNameFromPath(path);

    tmp = this->searchByPath(path);

    if (tmp) {
        if (!strcmp(name, tmp->getName())) {
            return tmp;
        }
        else
            return NULL;
    }

    return tmp;
}

/*
 * return - near match node/exact match, otherwise NULL
 */
RIBTreeNode *RIBTreeNode::searchByPath(std::string path) {
    RIBTreeNode *tmp = this;
    std::string name;

    std::queue<std::string> tmpPath = this->parsePath(path);

    for (;;) {
        name = tmpPath.front();
        tmpPath.pop();

        if (!tmpPath.empty()) {
            tmp = tmp->searchByPathExactMatch(name);
            tmp = tmp->getSubLevelRoot();

            if (tmp == NULL)
                return NULL;
        }
        else {
            tmp = tmp->search(name);
            break;
        }
    }

    return tmp;
}

RIBTreeNode *RIBTreeNode::create(RIBTreeNode *node) {
    RIBTreeNode *tmp = this->findByPath(node->getPath());
    int cond;
    RIBTreeNode *child = NULL;
    std::string tmpName;

    if (tmp == NULL) {
        tmpName = node->getPath();

        tmpName = tmpName.substr(0, tmpName.find_last_of("/\\"));

        tmp = this->findByPathExactMatch(tmpName);

        if (tmp != NULL) {
            tmp->setSubLevelRoot(node);
        }
        return NULL;
    }
    else if(!strcmp(tmp->getName(), node->getName())) {
        return tmp;
    }
    else {
       cond = strcmp(tmp->getName(), node->getName());

       node->setParentNode(tmp);

       if (cond < 0) {
           child = tmp->getLeftChild();
           tmp->setLeftChild(node);
       }
       else {
           child = tmp->getRightChild();
           tmp->setRightChild(node);
       }

       if (child != NULL) {
           cond = strcmp(node->getName(), child->getName());

           if (cond < 0) {
               node->setLeftChild(child);
           }
           else {
               node->setRightChild(child);
           }

           child->setParentNode(node);
       }
    }
}


void RIBTreeNode::deleteNode(std::string path) {
    //TODO: delete nodes
}

/*
 * @path - expects format "/../ae/iae"
 */
std::queue<std::string> RIBTreeNode::parsePath(std::string path) {
    std::queue<std::string> que;
    std::string tmpPath = path;
    std::string tmp;

    while (tmpPath.find("/") != string::npos) {
        tmpPath = tmpPath.substr(tmpPath.find("/")+1);
        tmp = tmpPath.substr(0, tmpPath.find("/"));
        que.push(tmp);
    }

    return que;
}

RIBTreeNode *RIBTreeNode::getLeftChild() {
    return this->leftChild;
}

RIBTreeNode *RIBTreeNode::getRightChild() {
    return this->rightChild;
}

RIBTreeNode *RIBTreeNode::getParentNode() {
    return this->parent;
}

RIBTreeNode *RIBTreeNode::getSubLevelRoot() {
    return this->subLevelRoot;
}

RIBTreeNodeObj *RIBTreeNode::getObjRoot() {
    return this->objRoot;
}

std::string RIBTreeNode::getName() {
    return this->name;
}

void RIBTreeNode::setLeftChild(RIBTreeNode *node) {
    this->leftChild = node;
}

void RIBTreeNode::setRightChild(RIBTreeNode *node) {
    this->rightChild = node;
}

void RIBTreeNode::setParentNode(RIBTreeNode *node) {
    this->parent = node;
}

void RIBTreeNode::setSubLevelRoot(RIBTreeNode *node) {
    this->subLevelRoot = node;
}

void RIBTreeNode::setObjRoot(RIBTreeNodeObj *node) {
    this->objRoot = node;
}

std::string RIBTreeNode::getPath() {
    return this->path;
}

AEBase *RIBTreeNode::getAE() {
    return this->ae;
}

void RIBTreeNode::setAE(AEBase *ae) {
    this->ae = ae;
}
