#pragma once

#include "DC_Defines.h"
#include "DCAddr.h"
#include <vector>
#include <map>


namespace REFwdDC {
using namespace std;
using namespace NSPSimpleDC;

    typedef unsigned char* Exception;
    struct ExceptionTable {
        map<unsigned char, map<unsigned char, Exception > > torTable;
        map<unsigned char, Exception> podTable;
        map<unsigned char, map<unsigned char, Exception > > edgeTable;
        map<unsigned char, Exception> spinesTable;

        Exception findToRException(const DCAddr & addr);
        Exception findEdgeException(const DCAddr & addr);

        Exception findToROnlyException(const DCAddr & addr);
        Exception findEdgeOnlyException(const DCAddr & addr);
        Exception findPodOnlyException(const DCAddr & addr);
        Exception findSpinesOnlyException(const DCAddr & addr);

        void addTorException(const unsigned char pod, const unsigned char id, Exception &e);
        void addPodException(const unsigned char pod, Exception &e);

        void addEdgeException(const unsigned char eset, const unsigned char id, Exception &e);
        void addSpinesException(const unsigned char spines, Exception &e);

        void removeTorException(const unsigned char pod, const unsigned char id);
        void removePodException(const unsigned char pod);

        void removeEdgeException(const unsigned char eset, const unsigned char id);
        void removeSpinesException(const unsigned char spines);

        void clear();

        void print();
    };

    Exception createException(const unsigned char & type, const portList & ports);
    Exception createEmptyException();
    void removeException(Exception & e);
    void printException(DCAddr addr, Exception & e);
}
