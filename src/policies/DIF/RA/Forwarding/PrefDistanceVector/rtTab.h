/*
 * rtTab.h
 *
 *  Created on: Mar 6, 2015
 *      Author: gaixas1
 */

#ifndef rtTab_H_
#define rtTab_H_


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
    unsigned char size;

    rtEntry();
    void setSize(bool _size);
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

typedef std::vector<rtUpdate> updatesList;
typedef updatesList::iterator updatesListIterator;

typedef std::vector<std::string> AddrList;
typedef AddrList::iterator AddrListIterator;

struct difRTab {
    rtTable sons;
    rtTable neig;
    rtTable rand;
    rtEntry parent;
};

class rtTab {
public:
    rtTab(std::string _im);
    rtTab();
    virtual ~rtTab();
    void setIm(std::string _im);

    void addQoS(unsigned short qos);

    bool addOrReplaceSon(std::string addr, std::string nextHop, int metric, unsigned short qos);
    bool addOrReplaceNeighbour(std::string addr, std::string nextHop, int metric, unsigned short qos);
    bool addOrReplaceRand(std::string addr, std::string nextHop, int metric, unsigned short qos, unsigned char prefSize);
    bool addOrReplaceParent(std::string nextHop, int metric, unsigned short qos);

    AddrList removeSons(std::string nextHop, unsigned short qos);
    AddrList removeNeighbours(std::string nextHop, unsigned short qos);
    AddrList removeRand(std::string nextHop, unsigned short qos);
    AddrList removeParent(std::string nextHop, unsigned short qos);

    std::string getNextHopSon(std::string addr, unsigned short qos);
    std::string getNextHopNeighbour(std::string addr, unsigned short qos);
    std::string getNextHopRand(std::string addr, unsigned short qos);
    std::string getNextHopParent(unsigned short qos);

    updatesList getUpdatesSon(std::string next, unsigned short qos);
    updatesList getUpdatesNeighbour(std::string next, unsigned short qos);
    updatesList getUpdatesRand(std::string next, unsigned short qos);
    updatesList getUpdatesRand(std::string next, unsigned short qos, unsigned char prefSize);
    updatesList getUpdatesParent(std::string next, unsigned short qos);


    // Gets a user friendly formatted network state report.
    //
    std::string prepareFriendlyNetState();

protected:
    std::string im;
    std::map<unsigned short, difRTab> tables;
    bool change(rtEntry * entry, std::string nextHop, int metric);
};

#endif /* rtTab_H_ */
