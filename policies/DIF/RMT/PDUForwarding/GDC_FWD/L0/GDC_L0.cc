#include "GDC_L0.h"

namespace GDC {
    using namespace std;

    Register_Class(L0);

    void L0::initializeSubPolicy() {
        nSets = nPod+ nEdgeP;
        if(nSets > 0 && nFab > 0) {
            myportsSyze = nSets*nFab;
            myports = new Port[myportsSyze];
        }
    }

    bool L0::setNeigh(const Addr & dst, Port port) {
        if(dst.a == 0 || dst.a > nSets || dst.b == 0 || dst.b > nFab ) {
            cerr << "At "<< Im << " invalid neighbour "<< dst << endl;
            endSimulation();
            return false;
        }

        ushort pId = (dst.a-1)*nFab + dst.b - 1;

        Port old = myports[pId];
        myports[pId] = port;

        bool refreshDown = false;
        if(port != nullptr) {
            if(old != nullptr) { cache.replacePort(old, port);}
            else { refreshDown = true; }
        } else if(old != nullptr) {
            cache.removePort(old);
            refreshDown = true;
        }

        if(refreshDown) {
            downList.clear();
            for(ushort i = 0; i < myportsSyze; i++) {
                if(myports[i] != nullptr) { downList.push_back(i); }
            }
            return true;
        }

        return false;
    }


    vecushort L0::readException(const Exception & e) {
        vecushort ret;
        uchar header = e[0] & 0x00FF;
        uchar size = (e[1]>>8)& 0x00FF;

        if(! (header & GDC_EXCEPTION_FLAG_DOWN) ) { return ret; }

        bool inverse = header | GDC_EXCEPTION_FLAG_INVERSE;
        if(size == 0) {
            if(inverse) { return inverseList(ret, 0, myportsSyze); }
            else { return ret; }
        }

        ushort j = 0;
        ushort current = e[j+2];

        for(ushort i = 0; i < myportsSyze; i++) {
            if((current == i) != inverse) { ret.push_back(i); }
            if(current == i) {
                j++;
                if(j < e[1]) { current = e[j+2]; }
                else { current = myportsSyze; }
            }
        }

        return ret;
    }

    vecushort L0::readRawException(const RawException & raw) {
        if(raw.OK) { return executeRule(raw.addr); }
        if(raw.validNeis.empty()) { return vecushort(); }

        setushort ports;
        for(const Addr n : raw.validNeis) {
            ushort pId = (n.a-1)*nFab + n.b - 1;
            if(n.a > 0
                    && n.a <= nSets
                    && n.b > 0
                    && n.b <= nFab
                    && myports[pId] != nullptr) {
                ports.insert(pId);
            }
        }

        return vecushort(ports.begin(), ports.end() );
    }

    vecushort L0::executeRule(const Addr & dst) {
        vecushort ret;

        if(dst == Im || (dst.a == 0 && dst.b == 0) || dst.a > nSets) { return ret; }

        if(dst.a == 0) { return downList; }
        else if(dst.b > 0 || dst.b){
            ushort pId = nFab*(dst.a-1) + dst.b-1;
            if(myports[pId] != nullptr) { return directList(pId); }
        } else {
            ushort pId = nFab*(dst.a-1);
            for(ushort i = 0; i< nFab; i++) { ret.push_back(pId+i); }
        }
        return ret;
    }

    Exception L0::computeException(const RawException & raw) {
        vecushort list = readRawException(raw);
        if(list.empty()) { return createEmptyException(); }

        if(list.size()*2 > myportsSyze) {
            vecushort ilist = inverseList(list, 0, myportsSyze);
            return createException(GDC_EXCEPTION_FLAG_DOWN | GDC_EXCEPTION_FLAG_INVERSE, ilist);
        } else {
            return createException(GDC_EXCEPTION_FLAG_DOWN, list);
        }
    }

    bool L0::useDefault(const Addr & dst) { return true; }

}
