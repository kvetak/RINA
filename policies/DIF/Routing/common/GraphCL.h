#pragma once


#include <omnetpp.h>
#include <limits>
#include <string>
#include <vector>
#include <set>
#include <map>

#include "DIF/Routing/common/nhLMetric.h"

namespace common_GraphCL {

using namespace std;

template <class T>
struct Link {
    string dst;
    T metric;
    Link(const string & d, const T & m) : dst(d), metric(m) {}
};

template <class T>
class GraphCL {

protected:
    struct TNode {
        string name;
        T metric;
        set<TNode *> parents, childs;
        bool known;

        TNode() : known(false) {}
    };


    map<string, vector<Link<T> > > links;
    map<string, TNode > nodes;

public:
    void addNode(const string &n, const vector<Link<T> > &ls) {
        links[n] = ls;
    }

    void addLink(const string &n, const Link<T> &l) {
        links[n].push_back(l);
    }

    map<string, nhLMetric<T>  > getNextHops (const string & root, const T & infMetric) {
        computeMinG(infMetric, root);

        map<string, nhLMetric<T>  > ret;

        for(TNode * n : nodes[root].childs){
            ret[n->name].metric = n->metric;
            ret[n->name].nh.insert(n->name);
            recursiveLook(ret, n->name, n->name);
        }

        return ret;
    }

    void print(const string & root, const T & infMetric) {

        map<string, nhLMetric<T>  > res = getNextHops (root, infMetric);

        EV << "Print tree : " << endl;
        EV << "" << root << " (0) " << endl;

        for(TNode * n : nodes[root].childs){
            printRecursive(n->name, 0);
        }

        EV << endl;
        EV << "Print nextHops : "<< endl;
        for(auto n : res) {
            EV << n.first << " (" << n.second.metric << ") ::";
            for (string d : n.second.nh) {
                EV << " <" << d << ">";
            }
            EV << endl;
        }
    }

protected:

    void computeMinG(const T & infMetric, const string & root) {
        nodes.clear();

        for(const auto & vl : links) {
            nodes[vl.first].name = vl.first;
            nodes[vl.first].metric = infMetric;
            nodes[vl.first].known = true;
            for(const Link<T> & l : vl.second) {
                nodes[l.dst].name = l.dst;
                nodes[l.dst].metric = infMetric;
            }
        }

        set<TNode *> waiting;

        nodes[root].metric = 0;
        waiting.insert(&nodes[root]);

        while(!waiting.empty()) {
            T minCost = USHRT_MAX;
            set<TNode *> minSet;

            for(TNode * n : waiting) {
                if(n->metric < minCost) {
                    minCost = n->metric;
                    minSet.clear();
                }
                if(n->metric == minCost){
                    minSet.insert(n);
                }
            }
            for(TNode * n : minSet) {
                waiting.erase(n);

                for(TNode * p : n->parents){
                    p->childs.insert(n);
                }

                if(n->known){
                    for(const Link<T> & l : links[n->name]) {
                        TNode * d = &nodes[l.dst];
                        T tCost = minCost + l.metric;
                        if(d->metric > tCost){
                            d->metric = tCost;
                            d->parents.clear();
                        }
                        if(d->metric == tCost){
                            d->parents.insert(n);
                            waiting.insert(d);
                        }
                    }
                }
            }
        }
    }

    void recursiveLook(map<string, nhLMetric<T>  > & ret, const string & node, const string & src) {
        for(TNode * n : nodes[node].childs){
            ret[n->name].metric = n->metric;
            ret[n->name].nh.insert(src);
            recursiveLook(ret, n->name, src);
        }
    }

    void printRecursive(const string & node, const int & index) {
        for(int i = 0; i< index; i++) { EV << "  "; }

        EV << "|-" << node << " ("<< nodes[node].metric << ") " << endl;

        for(TNode * n : nodes[node].childs){
            printRecursive(n->name, index + 1);
        }
    }

};

} /* namespace common_GraphCL */
