#include "GDC_Exceptions.h"

namespace GDC {
    using namespace std;

    //Exceptions
    Exception createException(const uchar & type, const vecushort & ports) {
        uchar size = 1+ports.size();
        Exception e = (Exception)malloc(size*sizeof(uchar));

        ushort s = ((ushort)ports.size())<<8 & 0xFF00;
        ushort h = (ushort) type & 0x00FF;
        e[0] = s | h;

        int i = 1;
        for(const auto & p : ports) { e[i++] = p; }
        return e;
    }
    Exception createEmptyException() {
        Exception e = (Exception)malloc(1*sizeof(ushort));
        e[0] = GDC_EXCEPTION_FLAG_NONE;
        return e;
    }

    void removeException(Exception & e) {
        if(e != nullptr) { free(e); }
    }

    void printException(Addr addr, Exception & e) {
        uchar header = e[0] & 0x00FF;
        uchar size = (e[0]>>8)& 0x00FF;

        cout << "\t\t" << addr;

        uchar type = header & GDC_EXCEPTION_FLAG_UPDOWN;
        switch(type) {
        case GDC_EXCEPTION_FLAG_NONE: cout << " [UNREACHABLE] "; break;
        case GDC_EXCEPTION_FLAG_UP: cout << " [UP] "; break;
        case GDC_EXCEPTION_FLAG_DOWN: cout << " [DOWN] "; break;
        case GDC_EXCEPTION_FLAG_UPDOWN: cout << " [UP-DOWN] "; break;
        }

        if(type != GDC_EXCEPTION_FLAG_NONE) {
            if(header & GDC_EXCEPTION_FLAG_INVERSE) {
                cout << " <INVERSE STORAGE> ";
            }
            cout << " PortsList (size " << (int)size << ") : ";
            for(uchar i = 0; i<size; i++) {
                cout << (int)e[i+1]<<" ";
            }
        }

        cout << endl;
    }

    //Exceptions Table
    ExceptionTable::ExceptionTable():defEx(nullptr) {}

    Exception ExceptionTable::getNodeException(const Addr & dst) {
        auto it = nodeEx.find(dst);
        if(it != nodeEx.end()) { return it->second; }
        return nullptr;
    }

    Exception ExceptionTable::getGroupException(const uchar & dst) {
        auto it = groupEx.find(dst);
        if(it != groupEx.end()) { return it->second; }
        return nullptr;
    }

    Exception ExceptionTable::getDefaultException() {
        return defEx;
    }

    void ExceptionTable::addNodeException(const Addr & dst, Exception &e) {
        Exception & ex = nodeEx[dst];
        if(ex != nullptr) { removeException(ex); }
        ex = e;
    }

    void ExceptionTable::addGroupException(const uchar & dst, Exception &e) {
        Exception & ex = groupEx[dst];
        if(ex != nullptr) { removeException(ex); }
        ex = e;
    }

    void ExceptionTable::addDefaultException(Exception &e) {
        if(defEx != nullptr) { removeException(defEx); }
        defEx = e;
    }

    void ExceptionTable::removeNodeException(const Addr & dst) {
        Exception e = nodeEx[dst];
        removeException(e);
        nodeEx.erase(dst);
    }

    void ExceptionTable::removeGroupException(const uchar & dst) {
        Exception e = groupEx[dst];
        removeException(e);
        groupEx.erase(dst);
    }

    void ExceptionTable::removeDefaultException() {
        removeException(defEx);
        defEx = nullptr;
    }

    void ExceptionTable::clear() {
        for(auto & e : nodeEx) { removeException(e.second); }
        for(auto & e : groupEx) { removeException(e.second); }
        removeException(defEx);
    }

    void ExceptionTable::print() {
        if(defEx != nullptr) { printException(Addr(), defEx); }
        for(auto & e : groupEx)  { printException(e.first, e.second); }
        for(auto & e : nodeEx)  { printException(e.first, e.second); }
    }
}
