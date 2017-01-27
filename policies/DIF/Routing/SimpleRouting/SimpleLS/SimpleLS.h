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

#ifndef SimpleLS_H_
#define SimpleLS_H_

#include "DIF/Routing/SimpleRouting/IntSimpleRouting.h"

#include <vector>
#include <map>

namespace SimpleLS {

struct linksU{
    unsigned int sId;
    std::map<std::string, unsigned short> links;
    linksU(){
        sId = 0;
    }
    linksU(const unsigned int &_sId){
        sId = _sId;
    }
};

typedef std::map<std::string, linksU> linksSt;
typedef std::pair<std::string, linksU> linksStEntry;

typedef std::map<std::string, linksSt> linksStCol;
typedef std::pair<std::string, linksSt> linksStColEntry;

typedef std::map<std::string, unsigned short>::iterator linksIt;
typedef linksSt::iterator linksStIt;
typedef linksStCol::iterator linksStColIt;

typedef std::map<Address, unsigned short> neighMetric;
typedef std::map<std::string, neighMetric> qosNeighMetric;
typedef neighMetric::iterator neighMetricIt;
typedef qosNeighMetric::iterator qosNeighMetricIt;


typedef std::set<std::string> qosSet;
typedef std::set<std::string> addrSet;
typedef std::vector<std::string> addrList;
typedef std::map<std::string, addrSet> qos2addrSet;
typedef std::pair<std::string, addrSet> qos2addrSetEntry;
typedef qosSet::iterator qosSetIt;
typedef addrSet::iterator addrSetIt;
typedef qos2addrSet::iterator qos2addrSetIt;

struct TreeNode {
    std::string addr;
    unsigned short metric;
    std::set<TreeNode*> chldel;
    std::set<TreeNode*> chl;
    TreeNode(){
            addr = "";
            metric = UINT16_MAX;
    }
    TreeNode(const std::string &_addr, const unsigned short &_metric){
        addr = _addr;
        metric = _metric;
    }
    bool operator == (const TreeNode &b) const
    {
        return addr == b.addr;
    }
    bool operator < (const TreeNode &b) const
    {
        return addr < b.addr;
    }

    ~TreeNode(){
        for(TreeNode * c: chldel){
            delete c;
        }
    }

};
typedef std::set<TreeNode *>::iterator TreeNodeIt;

struct psT {
    std::set<TreeNode*> p;
    unsigned short metric;
    psT(){
        metric = UINT16_MAX;
    }
    psT(TreeNode* _p, const unsigned short _metric){
        p.insert(_p);
        metric = _metric;
    }

    void addParent(TreeNode* _p, const unsigned short _metric){
        if(metric > _metric) {
            metric = _metric;
            p.clear();
        }
        if(metric == _metric) {
            p.insert(_p);
        }
    }

    bool operator == (const psT &b) const
    {
        return p == b.p;
    }
    bool operator < (const psT &b) const
    {
        return p < b.p;
    }
};

typedef std::map<std::string, psT > wMap;
typedef std::map<std::string, unsigned short > aMap;

typedef wMap::iterator wMapIt;
typedef aMap::iterator aMapIt;

typedef std::vector<wMapIt> mList;
typedef mList::iterator mListIt;

class RoutingUpdate : public IntRoutingUpdate {
public:
    RoutingUpdate(const Address &_addr, const std::string&_qos);

    std::string getQoS();

    void addEntry(const std::string &, linksU);
    void setEntries(linksSt);

    linksStIt entriesBegin();
    linksStIt entriesEnd();

protected:
    std::string qos;
    linksSt entries;
};

class SimpleLS: public IntSimpleRouting {
public:
    //Process a Routing Update, return true => inform FWDG of the update
    bool processUpdate(IntRoutingUpdate * update);


    //Flow inserted/removed
    void insertFlow(const Address &addr, const std::string &dst, const std::string& qos, const unsigned short &metric);
    void removeFlow(const Address &addr, const std::string &dst, const std::string& qos);

    //Get Changes
    entries2Next getChanges();
    entries2Next getAll();

    void handleMessage(cMessage *msg);
    void finish();

protected:
    // Called after initialize
    void onPolicyInit();

private:
    unsigned short infMetric;
    std::string myAddr;
    qosNeighMetric neig;
    linksStCol netState;
    qos2addrSet lastChanges;
    unsigned int secId;
    linksSt getChangedEntries (const std::string& qos);

    TreeNode constructTree(linksSt &ls);
    void addRecursive(entries2Next &ret, const std::string& qos, const std::string &next, TreeNode * t);

    bool scheduledUpdate;
    void scheduleUpdate();

    entries2Next table;


    void printTreeNode(TreeNode *t, const std::string &next);
};

}

#endif /* SimpleLS_H_ */
