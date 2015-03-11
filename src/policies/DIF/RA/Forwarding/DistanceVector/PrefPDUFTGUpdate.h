/*
 * PrefPDUFTGUpdate.h
 *
 *  Created on: Mar 6, 2015
 *      Author: gaixas1
 */

#ifndef PREFPDUFTGUPDATE_H_
#define PREFPDUFTGUPDATE_H_

#include <PDUFTGUpdate.h>
#include "rtTab.h"

class PrefPDUFTGUpdate: public PDUFTGUpdate {
public:
    PrefPDUFTGUpdate();
    PrefPDUFTGUpdate(Address from, Address to);
    virtual ~PrefPDUFTGUpdate();

    void setUpdates(updatesList list);
    void addEntry(unsigned short _qos, std::string _dst, int _metric);
    void addEntries(updatesList list);

    updatesListIterator entriesBegin();
    updatesListIterator entriesEnd();

protected:
    updatesList entries;
};

#endif /* PREFPDUFTGUPDATE_H_ */
