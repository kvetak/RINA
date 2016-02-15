#pragma once

#include "GDC_defines.h"
#include "GDC_Exceptions.h"
#include "GDC_RawExceptions.h"
#include "GDC_Cache.h"
#include "IntPDUForwarding.h"


namespace GDC {
    using namespace std;

    class iface_FWD: public IntPDUForwarding {
    public:
        iface_FWD();
        virtual ~iface_FWD();

        vecPort lookup(const PDU * pdu);
        vecPort lookup(const Address & Adst, const string & qos);

        virtual string toString();

        void setExceptions(const vecRawException & exceptions);
        virtual bool setNeigh(const Addr & dst, Port port) = 0;

    protected:
        Addr Im;
        ExceptionTable exceptionsT;

        Port * myports;
        ushort myportsSyze;

        Cache cache;
        simtime_t cacheLivespan;

        ushort nSpines, nPod, nEdgeP, nFab, nTor, nEdge;

        void onPolicyInit();
        virtual void initializeSubPolicy() = 0;

        virtual void handleMessage(cMessage * msg);

        virtual vecushort search(const Addr & dst);

        virtual vecushort readException(const Exception & e) = 0;
        virtual vecushort readRawException(const RawException & raw) = 0;
        virtual vecushort executeRule(const Addr & dst) = 0;
        virtual bool useDefault(const Addr & dst) = 0;

        virtual Exception computeException(const RawException & raw) = 0;

        vecushort directList(const ushort &  p);

        void refreshCache(const Addr & addr, vecushort oldPorts, vecushort newPorts);


        vecushort inverseList(vecushort list, ushort a, ushort b);

        void finish();
    };
}
