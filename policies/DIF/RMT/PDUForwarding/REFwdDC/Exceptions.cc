#include "Exceptions.h"

namespace REFwdDC {

using namespace std;
using namespace NSPSimpleDC;

//Exceptions

    Exception createException(const unsigned char & type, const portList & ports) {
        unsigned int size = 2+ports.size();
        Exception e = (Exception)malloc(size*sizeof(unsigned char));
        e[0] = type;
        e[1] = (unsigned char) ports.size();
        int i = 2;
        for(const auto & p : ports) {
            e[i] = p;
            i++;
        }
        return e;
    }
    Exception createEmptyException() {
        Exception e = (Exception)malloc(2*sizeof(unsigned char));
        e[0] = EXCEPTION_FLAG_NONE;
        e[1] = 0;
        return e;
    }

    void removeException(Exception & e) {
        if(e != nullptr) { free(e); }
    }

//Exceptions Table
    Exception ExceptionTable::findToRException(const DCAddr & addr) {
        auto itA = torTable.find(addr.a);
        if(itA != torTable.end()) {
            auto itB = itA->second.find(addr.b);
            if(itB != itA->second.end()) {
                return itB->second;
            }
        }
        auto itB = podTable.find(addr.a);
        if(itB != podTable.end()) {
            return itB->second;
        }
        return nullptr;
    }

    Exception ExceptionTable::findEdgeException(const DCAddr & addr) {
        auto itA = edgeTable.find(addr.a);
        if(itA != edgeTable.end()) {
            auto itB = itA->second.find(addr.b);
            if(itB != itA->second.end()) {
                return itB->second;
            }
        }
        auto itB = spinesTable.find(addr.b);
        if(itB != spinesTable.end()) {
            return itB->second;
        }
        return nullptr;
    }

    Exception ExceptionTable::findToROnlyException(const DCAddr & addr) {
        auto itA = torTable.find(addr.a);
        if(itA != torTable.end()) {
            auto itB = itA->second.find(addr.b);
            if(itB != itA->second.end()) {
                return itB->second;
            }
        }
        return nullptr;
    }
    Exception ExceptionTable::findEdgeOnlyException(const DCAddr & addr) {
        auto itB = podTable.find(addr.a);
        if(itB != podTable.end()) {
            return itB->second;
        }
        return nullptr;
    }
    Exception ExceptionTable::findPodOnlyException(const DCAddr & addr) {
        auto itA = edgeTable.find(addr.a);
        if(itA != edgeTable.end()) {
            auto itB = itA->second.find(addr.b);
            if(itB != itA->second.end()) {
                return itB->second;
            }
        }
        return nullptr;
    }
    Exception ExceptionTable::findSpinesOnlyException(const DCAddr & addr) {
        auto itB = spinesTable.find(addr.b);
        if(itB != spinesTable.end()) {
            return itB->second;
        }
        return nullptr;

    }

    void ExceptionTable::addTorException(const unsigned char pod, const unsigned char id, Exception &e) {
        torTable[pod][id] = e;
    }
    void ExceptionTable::addPodException(const unsigned char pod, Exception &e){
        podTable[pod] = e;
    }
    void ExceptionTable::addEdgeException(const unsigned char eset, const unsigned char id, Exception &e){
        edgeTable[eset][id] = e;
    }
    void ExceptionTable::addSpinesException(const unsigned char spines, Exception &e){
        spinesTable[spines] = e;
    }

    void ExceptionTable::removeTorException(const unsigned char pod, const unsigned char id) {
        Exception e = torTable[pod][id];
        removeException(e);
        torTable[pod].erase(id);
        if(torTable[pod].empty()) { torTable.erase(pod); }
    }
    void ExceptionTable::removePodException(const unsigned char pod) {
        Exception e = podTable[pod];
        removeException(e);
        podTable.erase(pod);
    }
    void ExceptionTable::removeEdgeException(const unsigned char eset, const unsigned char id) {
        Exception e = edgeTable[eset][id];
        removeException(e);
        edgeTable[eset].erase(id);
        if(edgeTable[eset].empty()) { edgeTable.erase(eset); }
    }
    void ExceptionTable::removeSpinesException(const unsigned char spines) {
        Exception e = spinesTable[spines];
        removeException(e);
        spinesTable.erase(spines);
    }

    void ExceptionTable::clear() {
        for(auto & a : torTable) {
            for(auto b : a.second) {
                removeException(b.second);
            }
        }
        for(auto b : podTable) {
            removeException(b.second);
        }
        for(auto & a : edgeTable) {
            for(auto b : a.second) {
                removeException(b.second);
            }
        }
        for(auto b : spinesTable) {
            removeException(b.second);
        }
    }



    void ExceptionTable::print() {
        for(auto & a : torTable) {
            for(auto b : a.second) {
                printException(DCAddr(TYPEID_ToR, a.first, b.first), b.second);
            }
        }
        for(auto b : podTable) {
            printException(DCAddr(AGID_Pod, b.first, 0), b.second);
        }
        for(auto & a : edgeTable) {
            for(auto b : a.second) {
                printException(DCAddr(TYPEID_Edge, a.first, b.first), b.second);
            }
        }
        for(auto b : spinesTable) {
            printException(DCAddr(AGID_Spine, b.first, 0),b.second);
        }
    }

    void printException(DCAddr addr, Exception & e) {
        unsigned char header = e[0];
        unsigned char size = e[1];

        cout << "\t\t" << addr;

        unsigned char type = header & EXCEPTION_FLAG_UPDOWN;
        switch(type) {
            case EXCEPTION_FLAG_NONE: cout << " [UNREACHABLE] "; break;
            case EXCEPTION_FLAG_UP: cout << " [UP] "; break;
            case EXCEPTION_FLAG_DOWN: cout << " [DOWN] "; break;
            case EXCEPTION_FLAG_UPDOWN: cout << " [UP-DOWN] "; break;
        }

        if(type != EXCEPTION_FLAG_NONE) {
            if(header & EXCEPTION_FLAG_INVERSE) {
                cout << " <INVERSE STORAGE> ";
            }
            cout << " PortsList (size " << (int)size << ") : ";
            for(unsigned char i = 0; i<size; i++) {
                cout << (int)e[i+2]<<" ";
            }
        }

        cout << endl;
    }
}
