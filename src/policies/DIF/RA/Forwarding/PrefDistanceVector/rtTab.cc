/*
 * rtTab.cc
 *
 *  Created on: Mar 6, 2015
 *      Author: gaixas1
 */

#include <rtTab.h>

extern const int INF_METRIC = 32;

rtEntry::rtEntry(){
    nextHop1 = "";
    metric1 = INF_METRIC;
    nextHop2 = "";
    metric2 = INF_METRIC;
    share = false;
}

void rtEntry::setShare(bool _share){
    share = _share;
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
    im = im;
}
void rtTab::setIm(std::string _im) {
    im = im;
}

void rtTab::addQoS(unsigned short qos){
    tables[qos];
}

rtTab::~rtTab() {}

bool rtTab::addOrReplaceEntry(std::string addr, std::string nextHop, int metric, unsigned short qos, bool shared){
    rtEntry * entry = &tables[qos][addr];
    entry->share = shared;

    if(entry->nextHop1 == nextHop){
        entry->metric1 = metric;
    } else if(entry->metric2 >= metric){
        entry->setLast(nextHop, metric);
    }

    if(entry->metric1 > entry->metric2){
        entry->swap();
        return true;
    }
    return false;
}

std::string rtTab::getNextHop(std::string addr, unsigned short qos){
    rtTable * table = &tables[qos];

    rtTabIterator it = table->find(addr);
    if(it == table->end() || it->second.metric1 >= INF_METRIC){
        return "";
    }

    return it->second.nextHop1;
}

qosAddrList rtTab::remove(std::string nextHop){

    qosAddrList modified;

    for(std::map<unsigned short, rtTable>::iterator it = tables.begin(); it != tables.end(); it++){
        for(rtTabIterator it2 = it->second.begin(); it2 != it->second.end(); it2++){
            if(it2->second.nextHop2 == nextHop) {
                it2->second.setLast("", INF_METRIC);
            } else if(it2->second.nextHop1 == nextHop) {
                it2->second.setFirst("", INF_METRIC);
                it2->second.swap();
                modified.push_back(qosAddr(it->first, it2->first));
            }
        }
    }
    return modified;
}

qosAddrList rtTab::remove(std::string nextHop, unsigned short qos){

    qosAddrList modified;

    for(rtTabIterator it2 = tables[qos].begin(); it2 != tables[qos].end(); it2++){
        if(it2->second.nextHop2 == nextHop) {
            it2->second.setLast("", INF_METRIC);
        } else if(it2->second.nextHop1 == nextHop) {
            it2->second.setFirst("", INF_METRIC);
            it2->second.swap();
            modified.push_back(qosAddr(qos, it2->first));
        }
    }
    return modified;
}

updatesList rtTab::getUpdates(std::string next, bool all){
    updatesList ret;

    for(std::map<unsigned short, rtTable>::iterator it = tables.begin(); it != tables.end(); it++){
        ret.push_back(rtUpdate(it->first, im, 0));
        for(rtTabIterator it2 = it->second.begin(); it2 != it->second.end(); it2++){
            if((all || it2->second.share) && it2->first != next){
                if(it2->second.nextHop1 == next) {
                    ret.push_back(rtUpdate(it->first, it2->first, it2->second.metric2));
                } else {
                    ret.push_back(rtUpdate(it->first, it2->first, it2->second.metric1));
                }
            }
        }
    }
    return ret;
}


std::string rtTab::prepareFriendlyNetState()
{
    std::stringstream os;

    for(std::map<unsigned short, rtTable>::iterator it = tables.begin(); it != tables.end(); it++){
        os << "Qos:" << it->first << endl;
        for(rtTabIterator it2 = it->second.begin(); it2 != it->second.end(); it2++){
            if(it2->second.metric1<INF_METRIC && it2->second.nextHop1 != ""){
                os << "  " << it2->first;
                if(it2->second.share) {
                    os<< "*";
                }
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

