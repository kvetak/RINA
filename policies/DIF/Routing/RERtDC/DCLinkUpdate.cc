#include "DCLinkUpdate.h"

namespace RERtDC {

    LinksUpdate::LinksUpdate(Address dst){
        dstAddr = dst;
    }

    void LinksUpdate::addOrReplaceUpdate(linkInfo l) {
        for(linkInfo & li : linksStatus) {
            if(li.link == l.link) { li = l; return; }
        }
        linksStatus.push_back(l);
    }

    bool LinksUpdate::empty() {
        return linksStatus.empty();
    }

}
