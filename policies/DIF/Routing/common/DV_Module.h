#pragma once

#include "DIF/Routing/common/Routing_Alg.h"
#include "DIF/Routing/common/GraphCL.h"

namespace common_DVModule {

using namespace std;
using namespace common_Routing;
using namespace common_GraphCL;

#define NOCH 0
#define CH1OPT 1
#define CHMET 2
#define CHBOTH 3

template<class T>
class DV_Module : public Routing_Alg<T> {
    //Vars and classes
public:
protected:
    int secId;

    struct Entry {
        set<string> op1, op2;
        T m1, m2;

        inline void insert1(const string &  dst, const T & m){ op1.insert(dst); m1 = m;}
        inline void insert2(const string &  dst, const T & m){ op2.insert(dst); m2 = m;}
        inline void erase1(const string &  dst){ op1.erase(dst);}
        inline void erase2(const string &  dst){ op2.erase(dst);}
        inline void clear1(){ op1.clear();}
        inline void clear2(){ op2.clear();}
        inline void swap() {T tm = m1; m1 = m2; m2 = tm; set<string> td = op1; op1 = op2; op2 = td; }

        unsigned char addEntry(const string & dst, const T &m) {
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

        unsigned char removeEntry(const string & dst) {
            if(op1.find(dst) != op1.end()){
                if(op1.size() == 1) {
                    clear1(); swap(); return CHBOTH;
                } else {
                    erase1(dst);  return (op1.size() > 2)? CH1OPT : CHBOTH;
                }
            } else if(op2.find(dst) != op2.end()){
                erase2(dst);  return (op1.size() > 1)? NOCH : CHMET;
            } else {
                return  NOCH;
            }
        }
    };

    struct rtEntry{
        int sId;
        map<string, T> entries;
        rtEntry() : sId(-1){}
        rtEntry(const int &_sId) : sId(_sId){}
    };

    class DV_Update : public Routing_Update {
    public:
        string src;
        rtEntry entries;
        DV_Update(const string & s, rtEntry & ent) : src(s), entries(ent) {}
    };

    map<string, rtEntry> neiState;
    map<string, Entry> table;

    set<string> changed;

    //Functions
public:
    DV_Module() : secId(-1){}
    DV_Module(Routing_Module * p, const Address &_nAddr, const string &_addr, T inf) :
        Routing_Alg<T>(p, _nAddr, _addr, inf), secId(1){}

    virtual void addSynonym(const string syn) {
        Routing_Alg<T>::addSynonym(syn);
        changed.insert(syn);
        if(table[syn].addEntry(Routing_Alg<T>::myAddr, 0) & CHMET){
            Routing_Alg<T>::scheduleUpdate();
        }
    }
    virtual void removeSynonym(const string syn) {
        Routing_Alg<T>::removeSynonym(syn);
        changed.insert(syn);
        if(table[syn].removeEntry(Routing_Alg<T>::myAddr) & CHMET){
            Routing_Alg<T>::scheduleUpdate();
        }
    }

    virtual void addFlow(const Address &_nAddr, const string &_addr, const T &_metric){
        T oldM = Routing_Alg<T>::nei[_addr];
        if(oldM == _metric) { return; }

        Routing_Alg<T>::addFlow(_nAddr, _addr, _metric);

        unsigned char result = table[_addr].addEntry(_addr, _metric);
        if(result & CH1OPT) { changed.insert(_addr); }

        rtEntry * oldE = &neiState[_addr];

        T Dm = _metric - oldM;
        for(auto & entry : oldE->entries){
            entry.second += Dm;
            unsigned char eResult =  table[entry.first].addEntry(_addr, entry.second);
            if(eResult & CH1OPT) { changed.insert(entry.first); }
            result |= eResult;
        }

        if(result & CHMET) { Routing_Alg<T>::scheduleUpdate(); }
    }

    virtual void removeFlow(const Address &_nAddr, const string &_addr){
        Routing_Alg<T>::removeFlow(_nAddr, _addr);

        unsigned char result = table[_addr].removeEntry(_addr);
        if(result & CH1OPT) { changed.insert(_addr); }

        rtEntry oldE = neiState[_addr];

        for(const auto & entry : oldE.entries){
            unsigned char eResult =  table[entry.first].removeEntry(_addr);
            if(eResult & CH1OPT) { changed.insert(entry.first); }
            result |= eResult;
        }

        neiState.erase(_addr);

        if(result & CHMET) { Routing_Alg<T>::scheduleUpdate(); }
    }

    virtual bool processUpdate(Routing_Update * update) {
        if(DV_Update * up = dynamic_cast<DV_Update*>(update)) {
            if(up->src  == Routing_Alg<T>::myAddr
                    || Routing_Alg<T>::synonyms.find(up->src) != Routing_Alg<T>::synonyms.end()) {
                return false;
            }



            rtEntry oldE = neiState[up->src];
            if(oldE.sId >= up->entries.sId) { return false; }

            unsigned char result = 0;

            for(const auto & entry : up->entries.entries){
                if(entry.first == Routing_Alg<T>::myAddr) { continue; }

                unsigned char eResult = table[entry.first].addEntry(up->src, entry.second);
                if(eResult & CH1OPT) { changed.insert(entry.first); }

                result |= eResult;
            }

            for(const auto & entry : oldE.entries){
                if(up->entries.entries.find(entry.first) == up->entries.entries.end()){
                    unsigned char eResult =  table[entry.first].removeEntry(up->src);
                    if(eResult & CH1OPT) { changed.insert(entry.first); }

                    result |= eResult;
                }
            }

            neiState[up->src] = up->entries;

            if(result & CHMET){ Routing_Alg<T>::scheduleUpdate(); }
            return result & CH1OPT;
        }

        return false;
    };

    virtual void sendUpdate() {
        Routing_Alg<T>::sendUpdate();
        secId++;

        for(auto neig : Routing_Alg<T>::neigTable){
            T linkM = Routing_Alg<T>::nei[neig.first];

            rtEntry entry(secId);

            for(const auto & en : table){
                if(neig.first == en.first) { continue; }
                T cMet;
                bool inform = false;
                if(en.second.op1.size() >= 2 ) {
                    cMet = en.second.m1;
                    inform = true;
                } else if(en.second.op1.size() == 1) {
                    if(en.second.op1.find(neig.first) == en.second.op1.end()){
                        cMet = en.second.m1;
                        inform = true;
                    } else if(!en.second.op2.empty()) {
                        cMet = en.second.m2;
                        inform = true;
                    }
                }

                if(inform && cMet + linkM < Routing_Alg<T>::infinite){
                    entry.entries[en.first] = cMet + linkM;
                }
            }

            entry.entries[Routing_Alg<T>::myAddr] = linkM;
            for(const auto & syn : Routing_Alg<T>::synonyms) {
                entry.entries[syn] = linkM;
            }


            Routing_Alg<T>::parent->chSendUpdate(
                    new DV_Update( Routing_Alg<T>::myAddr,  entry),
                    neig.second, this);
        }

    }

    virtual map<string, nhLMetric<T>  > getChanges() {
        map<string, nhLMetric<T>  > ret;
        for(const auto & dst : changed) {
            Entry * e = &table[dst];
            ret[dst] = nhLMetric<T>(e->m1, e->op1);
        }
        changed.clear();
        return ret;
    };

    virtual map<string, nhLMetric<T>  > getAll() {
        map<string, nhLMetric<T>  > ret;
        for(const auto & e : table) {
            ret[e.first] = nhLMetric<T>(e.second.m1, e.second.op1);
        }
        changed.clear();
        return ret;
    };


    virtual void print() {
        EV << "Print nextHops : "<< endl;
        for(const auto & e : table) {
            if(e.second.op1.empty()) { continue; }
            EV << e.first <<endl;
            EV << "\t (" << e.second.m1 << ") ::";
            for (string d : e.second.op1) {
                EV << " <" << d << ">";
            }
            EV <<endl;
            if(e.second.op2.empty()) { continue; }
            EV << "\t (" << e.second.m2 << ") ::";
            for (string d : e.second.op2) {
                EV << " <" << d << ">";
            }
            EV <<endl;
        }


    }
};

} /* namespace common_DVModule */
