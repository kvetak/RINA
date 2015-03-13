/*
 * PrefPDUFTGUpdate.cc
 *
 *  Created on: Mar 6, 2015
 *      Author: gaixas1
 */

#include <PrefPDUFTGUpdate.h>

PrefPDUFTGUpdate::PrefPDUFTGUpdate() {}

PrefPDUFTGUpdate::PrefPDUFTGUpdate(Address from, Address to){
    setSource(from);
    setDestination(to);
    info = NULL;
}

PrefPDUFTGUpdate::~PrefPDUFTGUpdate() {}

void PrefPDUFTGUpdate::setUpdates(updatesList list){
    entries = list;
}

void PrefPDUFTGUpdate::addEntry(unsigned short _qos, std::string _dst, int _metric){
    entries.push_back(rtUpdate(_qos, _dst, _metric));
}

void PrefPDUFTGUpdate::addEntries(updatesList list){
    entries.insert(entries.end(),list.begin(),  list.end());
}

updatesListIterator PrefPDUFTGUpdate::entriesBegin(){
    return entries.begin();
}
updatesListIterator PrefPDUFTGUpdate::entriesEnd(){
    return entries.end();
}
