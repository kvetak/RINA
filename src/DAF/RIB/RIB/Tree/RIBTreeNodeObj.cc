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

#include <Tree/RIBTreeNodeObj.h>

RIBTreeNodeObj::RIBTreeNodeObj() {
    this->parent = NULL;
    this->leftChild = NULL;
    this->rightChild = NULL;
}

RIBTreeNodeObj::RIBTreeNodeObj(RIBTreeNodeObj* parent) {
    this->parent = parent;
    this->leftChild = NULL;
    this->rightChild = NULL;
}

RIBTreeNodeObj::RIBTreeNodeObj(std::string path) {
    this->name = this->getNameFromPath(path);
    this->path = path;
    this->parent = NULL;
    this->leftChild = NULL;
    this->rightChild = NULL;
}

RIBTreeNodeObj::~RIBTreeNodeObj() {
    this->parent = NULL;
    this->leftChild = NULL;
    this->rightChild = NULL;
}

std::string RIBTreeNodeObj::getNameFromPath(std::string path) {
    std::string tmp = path;
    while (tmp.find("/") != string::npos) {
        tmp = tmp.substr(tmp.find("/")+1);
    }

    return tmp;
}

/*
 * return - near match node
 */
RIBTreeNodeObj *RIBTreeNodeObj::search(std::string name) {
    RIBTreeNodeObj *tmp = this;
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
RIBTreeNodeObj *RIBTreeNodeObj::searchExactMatch(std::string name) {
    RIBTreeNodeObj *tmp = this;
    int cmp = 0;

    tmp = this->search(name);

    if (!strcmp(name, tmp->getName()))
        return tmp;
    else
        return NULL;
}

RIBTreeNodeObj *RIBTreeNodeObj::create(RIBTreeNodeObj *node) {
    RIBTreeNodeObj *tmp = this->search(node->getName());
    int cond;
    RIBTreeNodeObj *child;

    cond = strcmp(tmp->getName(), node->getName());
    if (!cond) {
        return NULL;
    }
    else {
        node->setParentNode(node);

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

void RIBTreeNodeObj::deleteNode(std::string name) {
    //TODO: finish this
}

RIBTreeNodeObj *RIBTreeNodeObj::getLeftChild() {
    return this->leftChild;
}

RIBTreeNodeObj *RIBTreeNodeObj::getRightChild() {
    return this->rightChild;
}

RIBTreeNodeObj *RIBTreeNodeObj::getParentNode() {
    return this->parent;
}

std::string RIBTreeNodeObj::getName() {
    return this->name;
}

void RIBTreeNodeObj::setLeftChild(RIBTreeNodeObj *node) {
    this->leftChild = node;
}

void RIBTreeNodeObj::setRightChild(RIBTreeNodeObj *node) {
    this->rightChild = node;
}

void RIBTreeNodeObj::setParentNode(RIBTreeNodeObj *node) {
    this->parent = node;
}

std::string RIBTreeNodeObj::getPath() {
    return this->path;
}
