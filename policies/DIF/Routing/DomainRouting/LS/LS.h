/*
 * LS.h
 *
 *  Created on: Mar 23, 2015
 *      Author: gaixas1
 */

#ifndef LS_H_
#define LS_H_

#include <DomainRouting/rModule.h>

namespace DMRnmsLS {

using namespace DMRnms;

///////////////////////////////////////////////////////////////////////
// Data structures

typedef std::map<std::string, unsigned short> s2m;
typedef s2m::iterator s2mIt;

struct linksU{
    unsigned int sId;
    s2m links;
    linksU()
        :sId(0){}
    linksU(const unsigned int &_sId)
        :sId(_sId){}
};

typedef std::map<std::string, linksU> linksSt;
typedef linksSt::iterator linksStIt;

typedef std::map<Address, unsigned short> neighMetric;
typedef neighMetric::iterator neighMetricIt;

typedef std::set<std::string> sSet;
typedef sSet::iterator sSetIt;

typedef std::vector<std::string> sList;
typedef sList::iterator sListIt;


struct TreeNode {
    std::string addr;
    unsigned short metric;
    std::set<TreeNode*> chl;
    TreeNode()
        :addr(""), metric(UINT16_MAX) {}
    TreeNode(const std::string &_addr, const unsigned short &_metric)
        :addr(_addr), metric(_metric) {}

    bool operator == (const TreeNode &b) const { return addr == b.addr; }
    bool operator < (const TreeNode &b) const { return addr < b.addr; }

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
    psT()
        :p(NULL), metric(UINT16_MAX){}
    psT(TreeNode* _p, const unsigned short _metric)
        :p(_p), metric(_metric){}

    bool operator == (const psT &b) const { return p == b.p; }
    bool operator < (const psT &b) const { return p < b.p; }
};
typedef std::map<std::string, psT > wMap;
typedef wMap::iterator wMapIt;


///////////////////////////////////////////////////////////////////////
// Update Message

class LSUpdate : public RoutingUpdate {
public:
    LSUpdate(const Address &_addr, const std::string &_domain);

    void addEntry(const std::string & _addr, linksU _neig);
    void setEntries(linksSt _entries);

    linksStIt entriesBegin();
    linksStIt entriesEnd();

protected:
    linksSt entries;
};

///////////////////////////////////////////////////////////////////////
// Routing Module


class LS: public rModule {
public:
    LS(Routing * parent, const Address &_nAddr, const std::string &_domain, const std::string &_addr);

    bool processUpdate(RoutingUpdate * update);
    void addFlow(const Address &_nAddr, const std::string &_addr, const unsigned short &_metric);
    void removeFlow(const Address &_nAddr, const std::string &_addr);

    void addAddr(const std::string &_addr);
    void removeAddr(const std::string &_addr);

    void setInfMetric(const unsigned short &inf);

    dmNxt getChanges();
    dmNxt getAll();

    void handleMessage(cMessage *msg);

protected:
    sSet myAddrSet;

    neighMetric nei;
    unsigned short infMetric;

    s2A neigTable;
    linksSt netState;
    unsigned int secId;

    sSet changed;
    linksSt getChangedEntries ();

    s2A currentTable;
    TreeNode constructTree();
    void addRecursive(s2A &ret, const Address &next, TreeNode * t);

    bool scheduledUpdate;
    void scheduleUpdate();

};

} /* namespace DomainRoutingLS */

#endif /* LS_H_ */
