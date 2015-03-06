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
}

PrefPDUFTGUpdate::~PrefPDUFTGUpdate() {}

void PrefPDUFTGUpdate::setUpdates(updatesList list){
    entries = list;
}
updatesListIterator PrefPDUFTGUpdate::entriesBegin(){
    return entries.begin();
}
updatesListIterator PrefPDUFTGUpdate::entriesEnd(){
    return entries.end();
}
