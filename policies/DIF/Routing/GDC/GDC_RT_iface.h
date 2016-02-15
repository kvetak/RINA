#pragma once

#include <IntRouting.h>

#include "GDC_defines.h"
#include "GDC_RawExceptions.h"
#include "GDC_LinkInfo.h"
#include "GDC_LinkUpdate.h"

#define fnd(a,b) (a.find(b) != a.end())

namespace GDC {
    using namespace std;

    struct nodeNeig {
        Addr n_addr;
        Address addr;
        bool status;
        long timestamp;

        LinksUpdate * tempUpdate;

        nodeNeig();
        void init(const Addr & _n_addr, const Address & _addr);

        LinksUpdate * popUpdate();
        void addInfo(const linkInfo & li);
        void addInfo(const vector<linkInfo> & lli);
        bool emptyUpdate();
    };

    class iface_RT: public IntRouting {
        public:
            iface_RT();
            virtual ~iface_RT();

            //Process a Routing Update, return true => inform FWDG of the update
            bool processUpdate(IntRoutingUpdate * update);

            //Flow inserted/removed
            void insertNeighbour(const Address &addr, const Addr &dst);
            void removeNeighbour(const Address &addr, const Addr &dst);

            virtual vecRawException getExceptions() = 0;

        protected:
            Addr Im;

            nodeNeig * myNeis;
            ushort myNeisSize;

            map<linkId, linkInfo> linksStatus;

            void onPolicyInit();
            void finish();
            virtual void handleMessage(cMessage * msg);

            virtual void startMyNeis() = 0;
            virtual ushort getNeiId(const Address & addr);
            virtual ushort getNeiId(const Addr & addr) = 0;

            cMessage * clean, * start;
            ushort nSpines, nPod, nEdgeP, nFab, nTor, nEdge;
            long oldAfter, expiresAfter;

            void cleanOK();
            void FirstUpdate();
            void Update();

            void addToUpdates(linkInfo li);


            bool preparseFailures();
            void parseFailure(const Addr & src, const Addr & dst);
            void clearParsedFailures();


            Addr2setAddr R0Fails, R1FailsUp, R1FailsDown, R2Fails;
            map<uchar, uchar2setuchar> R0GroupedFailures, R2GroupedFailures;
            setAddr R0Dead, R1DeadUp, R1DeadDown, R2Dead;
            uchar2setuchar groupDeadsUp;
            setuchar groupProb, unreachGroup;


            bool fullSet(const setuchar &sa, const setuchar &sb, const ushort size);
            bool fullSet(const setAddr &sa, const setAddr &sb, const ushort size);
    };
}
