#pragma once

#include "GDC_defines.h"

namespace GDC {
    using namespace std;

    typedef ushort* Exception;

    Exception createException(const uchar & type, const vecushort & ports);
    Exception createEmptyException();
    void removeException(Exception & e);
    void printException(Addr addr, Exception & e);

    struct ExceptionTable {
        //Default exception 0.0
        Exception defEx;
        //Group Exceptions K.0
        map<uchar, Exception> groupEx;
        //Node Exceptions K.Q
        map<Addr, Exception> nodeEx;

        ExceptionTable();

        Exception getNodeException(const Addr & dst);
        Exception getGroupException(const uchar & dst);
        Exception getDefaultException();

        void addNodeException(const Addr & dst, Exception &e);
        void addGroupException(const uchar & dst, Exception &e);
        void addDefaultException(Exception &e);

        void removeNodeException(const Addr & dst);
        void removeGroupException(const uchar & dst);
        void removeDefaultException();

        void clear();
        void print();
    };

}
