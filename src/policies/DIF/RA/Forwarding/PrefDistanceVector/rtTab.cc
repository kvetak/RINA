/*
 * rtTab.cc
 *
 *  Created on: Mar 6, 2015
 *      Author: gaixas1
 */

#include <rtTab.h>
#include "Utils.h"

extern const int INF_METRIC = 32;

rtEntry::rtEntry(){
    nextHop1 = "";
    metric1 = INF_METRIC;
    nextHop2 = "";
    metric2 = INF_METRIC;
}

void rtEntry::setSize(bool _size){
    size = _size;
}

void rtEntry::setFirst(std::string nextHop, int metric){
    nextHop1 = nextHop;
    metric1 = metric;
}

void rtEntry::setLast(std::string nextHop, int metric){
    nextHop2 = nextHop;
    metric2 = metric;
}

void rtEntry::swap(){
    std::string nextHopT = nextHop1;
    int metricT = metric1;

    nextHop1 = nextHop2;
    metric1 = metric2;

    nextHop2 = nextHopT;
    metric2 = metricT;
}


rtUpdate::rtUpdate(unsigned short _qos, std::string _dst, int _metric){
    qos = _qos;
    dst = _dst;
    metric = _metric;
}


rtTab::rtTab() {
    im = "";
}

rtTab::rtTab(std::string _im) {
    im = _im;
}

void rtTab::setIm(std::string _im) {
    im = im;
}

void rtTab::addQoS(unsigned short qos){
    tables[qos];
}

rtTab::~rtTab() {}

bool addOrReplaceSon(std::string addr, std::string nextHop, int metric, unsigned short qos);
bool addOrReplaceNeighbour(std::string addr, std::string nextHop, int metric, unsigned short qos);
bool addOrReplaceRand(std::string addr, std::string nextHop, int metric, unsigned short qos);
bool addOrReplaceParent(std::string nextHop, int metric, unsigned short qos);



bool rtTab::addOrReplaceSon(std::string addr, std::string nextHop, int metric, unsigned short qos){
    rtEntry * entry = &tables[qos].sons[addr];
    return change(entry, nextHop, metric);
}

bool rtTab::addOrReplaceNeighbour(std::string addr, std::string nextHop, int metric, unsigned short qos){
    rtEntry * entry = &tables[qos].neig[addr];
    return change(entry, nextHop, metric);
}

bool rtTab::addOrReplaceRand(std::string addr, std::string nextHop, int metric, unsigned short qos, unsigned char prefSize){
    rtEntry * entry = &tables[qos].rand[addr];
    entry->size = prefSize;
    return change(entry, nextHop, metric);
}

bool rtTab::addOrReplaceParent(std::string nextHop, int metric, unsigned short qos){
    rtEntry * entry = &tables[qos].parent;
    return change(entry, nextHop, metric);
}

bool rtTab::change(rtEntry * entry, std::string nextHop, int metric){
    if(entry->nextHop1 == nextHop){
        entry->metric1 = metric;
    } else if(entry->nextHop2 == nextHop){
        entry->metric2 = metric;
    } else if(entry->metric2 >= metric){
        entry->setLast(nextHop, metric);
    }

    if(entry->metric1 > entry->metric2){
        entry->swap();
        return true;
    }
    return false;
}

std::string rtTab::getNextHopSon(std::string addr, unsigned short qos){
    rtTable * table = &tables[qos].sons;

    rtTabIterator it = table->find(addr);
    if(it == table->end() || it->second.metric1 >= INF_METRIC){
        return "";
    }

    return it->second.nextHop1;
}
std::string rtTab::getNextHopNeighbour(std::string addr, unsigned short qos){
    rtTable * table = &tables[qos].neig;

    rtTabIterator it = table->find(addr);
    if(it == table->end() || it->second.metric1 >= INF_METRIC){
        return "";
    }

    return it->second.nextHop1;
}
std::string rtTab::getNextHopRand(std::string addr, unsigned short qos){
    rtTable * table = &tables[qos].rand;

    rtTabIterator it = table->find(addr);
    if(it == table->end() || it->second.metric1 >= INF_METRIC){
        return "";
    }

    return it->second.nextHop1;
}
std::string rtTab::getNextHopParent(unsigned short qos){
    if(tables[qos].parent.metric1 >= INF_METRIC){
        return "";
    }
    return tables[qos].parent.nextHop1;
}


AddrList rtTab::removeSons(std::string nextHop, unsigned short qos){
    AddrList modified;

    for(rtTabIterator it2 = tables[qos].sons.begin(); it2 != tables[qos].sons.end(); it2++){
        if(it2->second.nextHop2 == nextHop) {
            it2->second.setLast("", INF_METRIC);
        } else if(it2->second.nextHop1 == nextHop) {
            it2->second.setFirst("", INF_METRIC);
            it2->second.swap();
            modified.push_back(it2->first);
        }
    }
    return modified;
}
AddrList rtTab::removeNeighbours(std::string nextHop, unsigned short qos){
    AddrList modified;

    for(rtTabIterator it2 = tables[qos].neig.begin(); it2 != tables[qos].neig.end(); it2++){
        if(it2->second.nextHop2 == nextHop) {
            it2->second.setLast("", INF_METRIC);
        } else if(it2->second.nextHop1 == nextHop) {
            it2->second.setFirst("", INF_METRIC);
            it2->second.swap();
            modified.push_back(it2->first);
        }
    }
    return modified;
}
AddrList rtTab::removeRand(std::string nextHop, unsigned short qos){
    AddrList modified;

    for(rtTabIterator it2 = tables[qos].rand.begin(); it2 != tables[qos].rand.end(); it2++){
        if(it2->second.nextHop2 == nextHop) {
            it2->second.setLast("", INF_METRIC);
        } else if(it2->second.nextHop1 == nextHop) {
            it2->second.setFirst("", INF_METRIC);
            it2->second.swap();
            modified.push_back(it2->first);
        }
    }
    return modified;
}

AddrList rtTab::removeParent(std::string nextHop, unsigned short qos){
    AddrList modified;
    if(tables[qos].parent.nextHop2 == nextHop) {
        tables[qos].parent.setLast("", INF_METRIC);
    } else if(tables[qos].parent.nextHop1 == nextHop) {
        tables[qos].parent.setFirst("", INF_METRIC);
        tables[qos].parent.swap();
        modified.push_back("");
    }
    return modified;
}



updatesList rtTab::getUpdatesSon(std::string next, unsigned short qos){
    updatesList ret;
    for(rtTabIterator it2 = tables[qos].sons.begin(); it2 != tables[qos].sons.end(); it2++){
        if(it2->first != next){
            if(it2->second.nextHop1 == next) {
                if(it2->second.nextHop2 != "" && it2->second.metric2 < INF_METRIC) {
                    ret.push_back(rtUpdate(qos, it2->first, it2->second.metric2));
                } else {
                    ret.push_back(rtUpdate(qos, it2->first, INF_METRIC));
                }
            } else if(it2->second.nextHop1 != "" && it2->second.metric1 < INF_METRIC) {
                ret.push_back(rtUpdate(qos, it2->first, it2->second.metric1));
            } else {
                ret.push_back(rtUpdate(qos, it2->first, INF_METRIC));
            }
        }
    }
    return ret;
}

updatesList rtTab::getUpdatesNeighbour(std::string next, unsigned short qos){
    updatesList ret;
    ret.push_back(rtUpdate(qos, im, 0));

    for(rtTabIterator it2 = tables[qos].neig.begin(); it2 != tables[qos].neig.end(); it2++){
        if(it2->first != next){
            if(it2->second.nextHop1 == next) {
                if(it2->second.nextHop2 != "" && it2->second.metric2 < INF_METRIC) {
                    ret.push_back(rtUpdate(qos, it2->first, it2->second.metric2));
                } else {
                    ret.push_back(rtUpdate(qos, it2->first, INF_METRIC));
                }
            } else if(it2->second.nextHop1 != "" && it2->second.metric1 < INF_METRIC) {
                ret.push_back(rtUpdate(qos, it2->first, it2->second.metric1));
            } else {
                ret.push_back(rtUpdate(qos, it2->first, INF_METRIC));
            }
        }
    }
    return ret;
}

updatesList rtTab::getUpdatesRand(std::string next, std::string stored, unsigned short qos, unsigned char prefSize){
    updatesList ret;
    for(rtTabIterator it2 = tables[qos].rand.begin(); it2 != tables[qos].rand.end(); it2++){
        if(it2->first != next && it2->second.size <= prefSize && it2->first != "" && !isPrefix(stored, it2->first) && !isPrefix(it2->first, stored)){
            if(it2->second.nextHop1 == next) {
                if(it2->second.nextHop2 != "" && it2->second.metric2 < INF_METRIC) {
                    ret.push_back(rtUpdate(qos, it2->first, it2->second.metric2));
                } else {
                    ret.push_back(rtUpdate(qos, it2->first, INF_METRIC));
                }
            } else if(it2->second.nextHop1 != "" && it2->second.metric1 < INF_METRIC) {
                ret.push_back(rtUpdate(qos, it2->first, it2->second.metric1));
            } else {
                ret.push_back(rtUpdate(qos, it2->first, INF_METRIC));
            }
        }
    }
    return ret;
}

updatesList rtTab::getUpdatesParent(std::string next, unsigned short qos){
    updatesList ret;
    rtEntry * entry = &tables[qos].parent;
    if(entry->nextHop1 == next) {
        if(entry->nextHop2 != "" && entry->metric2 < INF_METRIC) {
            ret.push_back(rtUpdate(qos, "", entry->metric2));
        } else {
            ret.push_back(rtUpdate(qos, "", INF_METRIC));
        }
    } else if(entry->nextHop1 != "" && entry->metric1 < INF_METRIC) {
        ret.push_back(rtUpdate(qos, "", entry->metric1));
    } else {
        ret.push_back(rtUpdate(qos, "", INF_METRIC));
    }
    return ret;
}


std::string rtTab::prepareFriendlyNetState()
{
    std::stringstream os;

    for(std::map<unsigned short, difRTab>::iterator it = tables.begin(); it != tables.end(); it++){
        os << "Qos:" << it->first << endl;

        os << "  * -> " << it->second.parent.nextHop1 << "("<<it->second.parent.metric1<<")";
        if(it->second.parent.metric2<INF_METRIC && it->second.parent.nextHop2 != ""){
            os << " or " << it->second.parent.nextHop2 << "("<<it->second.parent.metric2<<")";
        }
        os << endl;


        for(rtTabIterator it2 = it->second.neig.begin(); it2 != it->second.neig.end(); it2++){
            if(it2->second.metric1<INF_METRIC && it2->second.nextHop1 != ""){
                os << "  +" << it2->first << "*";
                os << " -> " << it2->second.nextHop1 << "("<<it2->second.metric1<<")";
                if(it2->second.metric2<INF_METRIC && it2->second.nextHop2 != ""){
                    os << " or " << it2->second.nextHop2 << "("<<it2->second.metric2<<")";
                }
                os << endl;
            }
        }
        for(rtTabIterator it2 = it->second.sons.begin(); it2 != it->second.sons.end(); it2++){
            if(it2->second.metric1<INF_METRIC && it2->second.nextHop1 != ""){
                os << "  -" << it2->first << "*";
                os << " -> " << it2->second.nextHop1 << "("<<it2->second.metric1<<")";
                if(it2->second.metric2<INF_METRIC && it2->second.nextHop2 != ""){
                    os << " or " << it2->second.nextHop2 << "("<<it2->second.metric2<<")";
                }
                os << endl;
            }
        }
        for(rtTabIterator it2 = it->second.rand.begin(); it2 != it->second.rand.end(); it2++){
            os << "  /" << it2->first << "*";
            if(it2->second.metric1<INF_METRIC && it2->second.nextHop1 != ""){
                os << "  " << it2->first;
                os << " -> " << it2->second.nextHop1 << "("<<it2->second.metric1<<")";
                if(it2->second.metric2<INF_METRIC && it2->second.nextHop2 != ""){
                    os << " or " << it2->second.nextHop2 << "("<<it2->second.metric2<<")";
                }
                os << endl;
            }
        }
    }

    return os.str();
}
