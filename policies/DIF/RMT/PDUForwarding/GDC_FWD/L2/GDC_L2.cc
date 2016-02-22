#include "GDC_L2.h"

namespace GDC {
    using namespace std;

    Register_Class(L2);

    void L2::initializeSubPolicy() {
        if(nFab > 0) {
            myports = new Port[nFab];
            myportsSyze = nFab;
        }
    }

    bool L2::setNeigh(const Addr & dst, Port port) {
        if(dst.a != Im.a || dst.b == 0 || dst.b > nFab) {
            cerr << "At "<< Im << " invalid neighbour "<< dst << endl;
            endSimulation();
            return false;
        }

        ushort pId = dst.b - 1;

        Port old = myports[pId];
        myports[pId] = port;

        bool refreshUp = false;
        if(port != nullptr) {
            if(old != nullptr) { cache.replacePort(old, port);}
            else { refreshUp = true; }
        } else if(old != nullptr) {
            cache.removePort(old);
            refreshUp = true;
        }

        if(refreshUp) {
            upList.clear();
            for(ushort i = 0; i < nFab; i++) {
                if(myports[i] != nullptr) { upList.push_back(i); }
            }
            return true;
        }

        return false;
    }


    vecushort L2::readException(const Exception & e) {
        vecushort ret;
        ushort header = e[0];
        ushort size = e[1];

        if(! (header & GDC_EXCEPTION_FLAG_UP) ) { return ret; }

        bool inverse = header | GDC_EXCEPTION_FLAG_INVERSE;
        if(size == 0) {
            if(inverse) { return upList; }
            else { return ret; }
        }

        ushort j = 0;
        ushort current = e[j+2];

        for(ushort i = 0; i < nFab; i++) {
            if((current == i) != inverse) { ret.push_back(i); }
            if(current == i) {
                j++;
                if(j < size) { current = e[j+2]; }
                else { current = nFab; }
            }
        }

        return ret;
    }

    vecushort L2::readRawException(const RawException & raw) {
        if(raw.OK) { return executeRule(raw.addr); }
        if(raw.validNeis.empty()) { return vecushort(); }

        setushort ports;
        for(const auto n : raw.validNeis) {
            if(n.a == Im.a
                    && n.b > 0
                    &&  n.b <= nFab
                    && myports[n.b-1] != nullptr) {
                ports.insert(n.b-1);
            }
        }

        return vecushort(ports.begin(), ports.end() );
    }

    vecushort L2::executeRule(const Addr & dst) {
        if(dst == Im) { return vecushort(); }

        if(dst.a == Im.a && dst.b > 0 && dst.b <= nFab) {
            ushort pId = dst.b-1;
            if(myports[pId] != nullptr) { return directList(pId); }
            else { return vecushort(); }
        }

        return upList;
    }

    Exception L2::computeException(const RawException & raw) {
        vecushort list = readRawException(raw);
        if(list.empty()) { return createEmptyException(); }

        if(list.size()*2 > nFab) {
            vecushort ilist = inverseList(list,0,nFab);
            return createException(GDC_EXCEPTION_FLAG_UP | GDC_EXCEPTION_FLAG_INVERSE, ilist);
        } else {
            return createException(GDC_EXCEPTION_FLAG_UP, list);
        }
    }

    bool L2::useDefault(const Addr & dst) { return Im.a == dst.a; }

}
