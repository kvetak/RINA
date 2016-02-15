#include "GDC_L1.h"

namespace GDC {
    using namespace std;

    Register_Class(L1);

    void L1::initializeSubPolicy() {
        if(Im.a <= nPod) { mySons = nTor; }
        else { mySons = nEdge; }

        if(nSpines + mySons > 0) {
            myportsSyze = nSpines + mySons;
            myports = new Port[myportsSyze];
        }
    }

    bool L1::setNeigh(const Addr & dst, Port port) {
        ushort pId;
        uchar neiT = 0;

        if(dst.a == 0 && dst.b>0 && dst.b <= nSpines) {
            neiT = 1;
            pId = dst.b-1;
        } else if(dst.a == Im.a && dst.b > nFab && dst.b <= nFab+mySons) {
            neiT = 1;
            pId = nSpines + dst.b - nFab - 1;
        }

        if(neiT == 0) {
            cerr << "At "<< Im << " invalid neighbour "<< dst << endl;
            endSimulation();
            return false;
        }

        Port old = myports[pId];
        myports[pId] = port;

        bool refresh = false;
        if(port != nullptr) {
            if(old != nullptr) { cache.replacePort(old, port);}
            else { refresh = true; }
        } else if(old != nullptr) {
            cache.removePort(old);
            refresh = true;
        }

        if(refresh) {
            if(neiT == 1) {
                upList.clear();
                for(ushort i = 0; i < nSpines; i++) {
                    if(myports[i] != nullptr) { upList.push_back(i); }
                }
            } else {
                downList.clear();
                for(ushort i = nSpines; i < myportsSyze; i++) {
                    if(myports[i] != nullptr) { downList.push_back(i); }
                }
            }
            bothList.clear();
            for(ushort i = 0; i < myportsSyze; i++) {
                if(myports[i] != nullptr) { bothList.push_back(i); }
            }
        }
        return refresh;
    }


    vecushort L1::readException(const Exception & e) {
        vecushort ret;
        uchar header = e[0] & 0x00FF;
        uchar size = (e[1]>>8)& 0x00FF;

        if(! (header & GDC_EXCEPTION_FLAG_UPDOWN) ) { return ret; }

        bool inverse = header | GDC_EXCEPTION_FLAG_INVERSE;

        uchar hType = header & GDC_EXCEPTION_FLAG_UPDOWN;

        if(size == 0) {
            if(!inverse) { return ret; }
            switch(hType) {
                case GDC_EXCEPTION_FLAG_UP : return upList;
                case GDC_EXCEPTION_FLAG_DOWN : return downList;
                case GDC_EXCEPTION_FLAG_UPDOWN : return bothList;
            }
        }

        ushort min = (hType | GDC_EXCEPTION_FLAG_UP)? 0 : nSpines;
        ushort max = (hType | GDC_EXCEPTION_FLAG_DOWN)? nSpines : myportsSyze;

        ushort j = 0;
        ushort current = e[j+2];

        for(ushort i = min; i < max; i++) {
            if((current == i) != inverse) { ret.push_back(i); }
            if(current == i) {
                j++;
                if(j < e[1]) { current = e[j+2]; }
                else { current = max; }
            }
        }

        return ret;
    }

    vecushort L1::readRawException(const RawException & raw) {
        if(raw.OK) { return executeRule(raw.addr); }
        if(raw.validNeis.empty()) { return vecushort(); }

        setushort ports;
        for(const auto n : raw.validNeis) {
            if(n.a == 0 && n.b>0 && n.b <= nSpines) {
                ushort pId = n.b-1;
                if(myports[pId] != nullptr) { ports.insert(pId); }
            } else if(n.a == Im.a && n.b > nFab && n.b <= nFab+mySons) {
                ushort pId = nSpines + n.b - nFab - 1;
                if(myports[pId] != nullptr) { ports.insert(pId); }
            }
        }

        return vecushort(ports.begin(), ports.end() );
    }

    vecushort L1::executeRule(const Addr & dst) {
        vecushort ret;

        if(dst.a == Im.a) {
            if(dst.b == 0 || dst.b == Im.b || dst.b > mySons+nFab) { return ret; }
            if(dst.b <= nFab) { return downList; }
            ushort pId = dst.b + nSpines - 1 - nFab;
            if(myports[pId] != nullptr) { return directList(pId); }
        } else if(dst.a == 0) {
            if(dst.b == 0) { return upList; }
            else if (dst.b <= nSpines) {
                ushort pId = dst.b - 1;
                if(myports[pId] != nullptr) { return directList(pId); }
            }
        } else { return upList; }

        return vecushort();
    }

    Exception L1::computeException(const RawException & raw) {
        vecushort list = readRawException(raw);
        if(list.empty()) { return createEmptyException(); }

        unsigned char hType = GDC_EXCEPTION_FLAG_NONE;
        if(list[0] < nSpines) { hType |= GDC_EXCEPTION_FLAG_UP; }
        if(list[list.size()-1] >= nSpines) { hType |= GDC_EXCEPTION_FLAG_DOWN; }

        switch(hType) {
            case GDC_EXCEPTION_FLAG_UP:
                if(list.size()*2 > nSpines) {
                    vecushort ilist = inverseList(list,0,nSpines);
                    return createException(GDC_EXCEPTION_FLAG_UP | GDC_EXCEPTION_FLAG_INVERSE, ilist);
                } else {
                    return createException(GDC_EXCEPTION_FLAG_UP, list);
                }
                break;
            case GDC_EXCEPTION_FLAG_DOWN:
                if(list.size()*2 > mySons) {
                    vecushort ilist = inverseList(list,nSpines,myportsSyze);
                    return createException(GDC_EXCEPTION_FLAG_DOWN | GDC_EXCEPTION_FLAG_INVERSE, ilist);
                } else {
                    return createException(GDC_EXCEPTION_FLAG_DOWN, list);
                }
                break;
            case GDC_EXCEPTION_FLAG_UPDOWN:
                if(list.size()*2 > myportsSyze) {
                    vecushort ilist = inverseList(list,0,myportsSyze);
                    return createException(GDC_EXCEPTION_FLAG_UPDOWN | GDC_EXCEPTION_FLAG_INVERSE, ilist);
                } else {
                    return createException(GDC_EXCEPTION_FLAG_UPDOWN, list);
                }
                break;
        }

        return createEmptyException();
    }

    bool L1::useDefault(const Addr & dst) { return Im.a == dst.a; }

}
