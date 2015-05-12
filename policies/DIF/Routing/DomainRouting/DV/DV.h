/*
 * DV.h
 *
 *  Created on: Mar 23, 2015
 *      Author: gaixas1
 */

#ifndef DV_H_
#define DV_H_

#include <DomainRouting/rModule.h>

namespace DMRnmsDV {

using namespace DMRnms;

///////////////////////////////////////////////////////////////////////
// Data structures

struct rtEntry {
    std::string addr;
    unsigned short metric;
    rtEntry()
        :addr(""), metric(UINT16_MAX){}
    rtEntry(const std::string &_addr, const unsigned short &_metric)
        :addr(_addr), metric(_metric){}
};
typedef std::vector<rtEntry> entriesL;
typedef std::vector<rtEntry>::iterator entriesIt;

typedef std::map<Address, unsigned short> neighMetric;
typedef neighMetric::iterator neighMetricIt;


struct tEntry {
    Address addr;
    unsigned short metric;
    tEntry()
        :addr(""), metric(UINT16_MAX){}
    tEntry(const std::string &_addr, const unsigned short &_metric)
        :addr(_addr), metric(_metric){}
};
typedef std::map<std::string, tEntry> tTable;
typedef tTable::iterator tTableIt;

typedef std::set<std::string> sSet;
typedef sSet::iterator sSetIt;



///////////////////////////////////////////////////////////////////////
// Update Message

class DVUpdate : public RoutingUpdate {
public:
    DVUpdate(const Address &_addr, const std::string &_domain);

    void addEntry(rtEntry _e);

    entriesIt entriesBegin();
    entriesIt entriesEnd();

protected:
    entriesL entries;
};



///////////////////////////////////////////////////////////////////////
// Routing Module

class DomainRouting;

class DV: public rModule {
public:
    DV(Routing * parent, const Address &_nAddr,const std::string &_domain, const std::string &_addr);

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
    tTable table;
    neighMetric nei;
    unsigned short infMetric;
    s2A changes;
    sSet changedEntries;
    sSet myAddrSet;

    bool scheduledUpdate;
    void scheduleUpdate();
};

} /* namespace DomainRoutingDV */

#endif /* DV_H_ */
