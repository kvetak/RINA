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

#ifndef SimpleLS_H_
#define SimpleLS_H_

#include <IntSimpleRouting.h>

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

typedef std::map<unsigned short, linksSt> linksStCol;
typedef std::pair<unsigned short, linksSt> linksStColEntry;

typedef std::map<std::string, unsigned short>::iterator linksIt;
typedef linksSt::iterator linksStIt;
typedef linksStCol::iterator linksStColIt;

typedef std::map<Address, unsigned short> neighMetric;
typedef std::map<unsigned short, neighMetric> qosNeighMetric;
typedef neighMetric::iterator neighMetricIt;
typedef qosNeighMetric::iterator qosNeighMetricIt;


typedef std::set<unsigned short> qosSet;
typedef std::set<std::string> addrSet;
typedef std::vector<std::string> addrList;
typedef std::map<unsigned short, addrSet> qos2addrSet;
typedef std::pair<unsigned short, addrSet> qos2addrSetEntry;
typedef qosSet::iterator qosSetIt;
typedef addrSet::iterator addrSetIt;
typedef qos2addrSet::iterator qos2addrSetIt;

struct TreeNode {
    std::string addr;
    unsigned short metric;
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
        for(std::set<TreeNode *>::iterator it = chl.begin(); it != chl.end(); it++){
            TreeNode * c = *it;
            delete c;
        }
    }
};
typedef std::set<TreeNode *>::iterator TreeNodeIt;

struct psT {
    TreeNode* p;
    unsigned short metric;
    psT(){
        p = NULL;
        metric = UINT16_MAX;
    }
    psT(TreeNode* _p, const unsigned short _metric){
        p = _p;
        metric = _metric;
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
    RoutingUpdate(const Address &_addr, const unsigned short &_qos);

    unsigned short getQoS();

    void addEntry(const std::string &, linksU);
    void setEntries(linksSt);

    linksStIt entriesBegin();
    linksStIt entriesEnd();

protected:
    unsigned short qos;
    linksSt entries;
};

class SimpleLS: public IntSimpleRouting {
public:
    //Process a Routing Update, return true => inform FWDG of the update
    bool processUpdate(IntRoutingUpdate * update);


    //Flow inserted/removed
    void insertFlow(const Address &addr, const std::string &dst, const unsigned short &qos, const unsigned short &metric);
    void removeFlow(const Address &addr, const std::string &dst, const unsigned short &qos);

    //Get Changes
    entries2Next getChanges();
    entries2Next getAll();

    void handleMessage(cMessage *msg);
    void finish();

protected:
    // Called after initialize
    void onIni();

private:
    unsigned short infMetric;
    std::string myAddr;
    qosNeighMetric neig;
    linksStCol netState;
    qos2addrSet lastChanges;
    unsigned int secId;
    linksSt getChangedEntries (const unsigned short &qos);

    TreeNode constructTree(linksSt &ls);
    void addRecursive(entries2Next &ret, const unsigned short &qos, const std::string &next, TreeNode * t);

    bool scheduledUpdate;
    void scheduleUpdate();

    entries2Next table;


    void printTreeNode(TreeNode *t, const std::string &next);
};

}

#endif /* SimpleLS_H_ */
