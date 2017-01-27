#pragma once

#include <map>
#include <set>

#include "DIF/RMT/PDUForwarding/GREFWD/GRE_Helpers.h"

using namespace std;


#define NOCH 0
#define CH1OPT 1
#define CHMET 2
#define CHBOTH 3


struct dst_Entry {
    set<addr_t> op1, op2;
    char m1, m2;

    inline void insert1(const addr_t &  dst, const char & m){ op1.insert(dst); m1 = m;}
    inline void insert2(const addr_t &  dst, const char & m){ op2.insert(dst); m2 = m;}
    inline void erase1(const addr_t &  dst){ op1.erase(dst);}
    inline void erase2(const addr_t &  dst){ op2.erase(dst);}
    inline void clear1(){ op1.clear(); m1 = 16;}
    inline void clear2(){ op2.clear(); m2 = 16;}
    inline void swap() {char tm = m1; m1 = m2; m2 = tm; set<addr_t> td = op1; op1 = op2; op2 = td; }

    dst_Entry():m1(16), m2(16) {}

    unsigned char addEntry(const addr_t & dst, const char &m) {
        if(op1.empty()){

            insert1(dst, m); return CHBOTH;
        }else if(op2.empty()){
            if(op1.find(dst) != op1.end()){
                if(op1.size() == 1){
                    if(m != m1){

                        insert1(dst, m); return CHBOTH;
                    } else {
                        return  NOCH;
                    }
                } else {
                    if(m < m1){

                        erase1(dst); swap(); insert1(dst, m); return CHBOTH;
                    } else if( m > m1) {

                        erase1(dst); insert2(dst, m); return (op1.size() > 2)? CH1OPT : CHBOTH;
                    } else {
                        return  NOCH;
                    }
                }
            } else {
                if(m < m1){

                    swap(); insert1(dst, m); return CHBOTH;
                } else if( m > m1) {

                    insert2(dst, m); return (op1.size() > 1)? NOCH : CHMET;
                } else {
                    insert1(dst, m); return  CH1OPT;
                }
            }
        } else if(op1.find(dst) != op1.end()){
            if(op1.size() == 1) {
                if( m == m1) {
                    return  NOCH;
                } else if( m < m2) {

                    erase1(dst); insert1(dst, m); return CHBOTH;
                } else if( m == m2) {

                    clear1();  swap(); insert1(dst, m); return CHBOTH;
                } else {

                    swap(); return CHBOTH;
                }
            } else {
                if(m < m1){

                    erase1(dst); clear2(); swap(); insert1(dst, m); return CHBOTH;
                } else if( m == m1) {
                    return  NOCH;
                } else if( m < m2) {

                    erase1(dst); clear2(); insert2(dst, m); return (op1.size() > 2)? CH1OPT : CHBOTH;
                } else if( m == m2) {

                    erase1(dst); insert2(dst, m); return (op1.size() > 2)? CH1OPT : CHBOTH;
                } else {

                    erase1(dst); return  (op1.size() > 2)? CHBOTH : CH1OPT;
                }
            }
        } else if(op2.find(dst) != op2.end()){
            if(op2.size() == 1) {
                if(m < m1){

                    swap(); return CHBOTH;
                } else if( m == m1) {

                    clear2(); insert1(dst, m); return (op1.size() > 2)? CH1OPT : CHBOTH;
                } else if( m != m2) {

                    insert2(dst, m); return (op1.size() > 1)? NOCH : CHMET;
                } else {
                    return  NOCH;
                }
            } else {
                if(m < m1){

                    clear2(); swap(); insert1(dst, m); return CHBOTH;
                } else if( m == m1) {

                    erase2(dst); insert1(dst, m); return (op1.size() > 2)? CH1OPT : CHBOTH;
                } else if( m < m2) {

                    clear2(); insert2(dst, m); return (op1.size() > 1)? NOCH : CHMET;
                } else if( m == m2) {
                    return  NOCH;
                } else {

                    erase2(dst); return NOCH;
                }
            }
        } else {
            if(m < m1){

                clear2(); swap(); insert1(dst, m); return CHBOTH;
            } else if( m == m1) {

                insert1(dst, m); return (op1.size() > 2)? CH1OPT : CHBOTH;
            } else if( m < m2) {

                clear2(); insert2(dst, m); return (op1.size() > 1)? NOCH : CHMET;
            } else if( m == m2) {

                insert2(dst, m); return NOCH;
            } else {
                return  NOCH;
            }
        }
        return NOCH;
    }

    void removeEntry(const addr_t & dst) {

        if(op1.find(dst) != op1.end()){
            op1.erase(dst);
            erase1(dst);
            if(op1.empty()) {
                clear1();
                swap();
            }
        } else if(op2.find(dst) != op2.end()){
            erase2(dst);
            if(op2.empty()) {
                clear2();
            }
        }
    }
};

struct rt_Entry{
    addr_t src;
    map<addr_t, char> entries;
    rt_Entry(const addr_t &_src = -1) : src(_src){}
};


class RoutingModule {
public:
    RoutingModule();

    void setId(const addr_t & i);

    void addAddress(const addr_t & a);
    void removeAddress(const addr_t & a);

    void removeFrom(const addr_t &i);
    bool receiveChanges(const addr_t &i, const map<addr_t, char>  & entries);

    rt_Entry getRTUpdate();

    map<addr_t, dst_Entry> neiState;
    map<addr_t, char> neiDistance;

    addr_t id;
    set<addr_t> shareAddrs;
};
