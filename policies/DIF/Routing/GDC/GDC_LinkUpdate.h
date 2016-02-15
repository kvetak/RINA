#pragma once
#include <IntRouting.h>
#include "GDC_LinkInfo.h"

namespace GDC {
    using namespace std;

    class LinksUpdate : public IntRoutingUpdate {
        public:
            vector<linkInfo> linksStatus;

            LinksUpdate(Address dst);
            void addOrReplaceUpdate(linkInfo);
            bool empty();
    };

}
