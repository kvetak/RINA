/*
 * rtTab.h
 *
 *  Created on: Mar 6, 2015
 *      Author: gaixas1
 */

#ifndef RTTAB_H_
#define RTTAB_H_

#include <omnetpp.h>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>


extern const int INF_METRIC;

struct rtEntry {
    std::string nextHop1;
    int metric1;
    std::string nextHop2;
    int metric2;
    bool share;

    rtEntry();
    void setShare(bool _share);
    void setFirst(std::string nextHop, int metric);
    void setLast(std::string nextHop, int metric);
    void swap();
};

struct rtUpdate {
    unsigned short qos;
    std::string dst;
    int metric;

    rtUpdate(unsigned short _qos, std::string _dst, int _metric);
};

typedef std::map<std::string, rtEntry> rtTable;
typedef std::pair<std::string, rtEntry> rtTabEntry;
typedef rtTable::iterator rtTabIterator;

typedef std::pair<unsigned short, std::string> qosAddr;
typedef std::vector<qosAddr> qosAddrList;
typedef qosAddrList::iterator qosAddrListIterator;

typedef std::vector<rtUpdate> updatesList;
typedef updatesList::iterator updatesListIterator;

class rtTab {
public:
    rtTab(std::string _im);
    rtTab();
    virtual ~rtTab();
    void setIm(std::string _im);

    void addQoS(unsigned short qos);

    bool addOrReplaceEntry(std::string addr, std::string nextHop, int metric, unsigned short qos, bool shared);
    qosAddrList remove(std::string nextHop);
    qosAddrList remove(std::string nextHop, unsigned short qos);

    std::string getNextHop(std::string addr, unsigned short qos);

    updatesList getUpdates(std::string next, bool all);


    // Gets a user friendly formatted network state report.
    //
    std::string prepareFriendlyNetState();

protected:
    std::string im;
    std::map<unsigned short, rtTable> tables;
};

#endif /* RTTAB_H_ */
