#pragma once
#include <IntRouting.h>
#include "DCLinkInfo.h"

namespace RERtDC {

    class LinksUpdate : public IntRoutingUpdate {
        public:
            vector<linkInfo> linksStatus;

            LinksUpdate(Address dst);
            void addOrReplaceUpdate(linkInfo);
            bool empty();
    };

}
