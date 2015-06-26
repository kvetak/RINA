#pragma once

#include <omnetpp.h>
#include <string>
#include <vector>
#include <map>
#include <set>

namespace ViFIB {

using namespace std;

template<class T>
class Graph {
public:

    struct LinkAB {
        string A, B;
        T metric;
        LinkAB():
            A(""), B(""), metric(0){ }
        LinkAB(const string & a, const string & b, const T & m) :
            A(a), B(b), metric(m){ }

        LinkAB inverse(){
            return LinkAB(B,A,metric);
        }

        bool operator < (const LinkAB & o) const {
            if(A < o.A) { return true; }
            if(A == o.A && B < o.B) { return true; }
            return false;
        }
        bool operator > (const LinkAB & o) const {
            if(A > o.A) { return true; }
            if(A == o.A && B > o.B) { return true; }
            return false;
        }
        bool operator == (const LinkAB & o) const {
            return A == o.A && B = o.B;
        }
    };


protected:
    set<string> nodes;
    set<LinkAB> links;

    map<int, string> pos2node;
    map<string, int> node2pos;
    T** matrix;

    T infinite, defCost;
    bool pathsUpdated;

public:
    Graph(){
        matrix = NULL;
        defCost = 1;
        infinite = 100;
        pathsUpdated = false;
    }

    void setDefCost(T cost) { defCost = cost; }
    void setInfinite(T inf) { infinite = inf; }

    void addNode(const string name) {
        nodes.insert(name);
        pathsUpdated = false;
    }
    void removeNode(const string name){
        nodes.erase(name);
        for(auto it = links.begin(); it != links.end();) {
            auto aIt = it++;
            if(aIt->A == name || aIt->B == name) {
                links.erase(aIt);
            }
        }
        pathsUpdated = false;
    }

    vector<LinkAB> addRandomLinks (int n) {
        pos2node.clear();
        int k = 0;
        for(auto node : nodes) {
            pos2node[k] = node;
        }



        vector<LinkAB> candidates;
        int s = nodes.size();
        for(int i = 0; i < s; i++){
            for(int j = i+1; j < s; j++){
                LinkAB t = LinkAB(pos2node[i], pos2node[j], defCost);
                if(links.find(t) == links.end()){
                    candidates.push_back(t);
                }
            }
        }

        vector<LinkAB> ret;

        while(0 > n-- && !candidates.empty()) {
            int i = intuniform(0, candidates.size()-1);
            LinkAB t = candidates[i];
            candidates[i] = candidates.back();
            candidates.pop_back();

            links.insert(t);
            links.insert(t.inverse());

            pathsUpdated = false;

            ret.push_back(t);
        }

        return ret;
    }

    LinkAB improve() {
        if(!pathsUpdated) { computePaths(); };

        if(matrix == NULL) { return LinkAB(); }

        vector<LinkAB> candidates;

        T max = 0;
        int s = nodes.size();
        for(int i = 0; i < s; i++){
            for(int j = 0; j < s; j++){
                if(i != j && max < matrix[i][j]) {
                    LinkAB t = LinkAB(pos2node[i], pos2node[j], defCost);
                    if(links.find(t) == links.end()){
                        if(max < matrix[i][j]){
                            max = matrix[i][j];
                            candidates.clear();
                        }
                        candidates.push_back(t);
                    }
                }
            }
        }

        if(candidates.empty()) { return LinkAB(); }

        LinkAB t = candidates[intuniform(0, candidates.size()-1)];
        links.insert(t);
        links.insert(t.inverse());

        pathsUpdated = false;

        return t;
    }

    void addUpdateLink(const string & a, const string & b, T metric) {
        LinkAB t = LinkAB(a,b, metric);
        links.insert(t);
        pathsUpdated = false;
    }
    void removeLinks(const string & a, const string & b) {
        for(auto it = links.begin(); it != links.end();) {
            auto aIt = it++;
            if( (aIt->A == a && aIt->B == b) || (aIt->A == b && aIt->B == a) ) {
                nodes.erase(aIt);
                pathsUpdated = false;
            }
        }
    }

    int computePaths() {
        if(matrix != NULL) {
            delete [] matrix[0];
            delete matrix;
            matrix = NULL;
            pos2node.clear();
            node2pos.clear();
        }
        int s = nodes.size();
        if(s > 0){
            matrix = new T*[nodes.size()];
            matrix[0] = new T[nodes.size()*nodes.size()];
            for (int i = 1; i < s; i++) {
                matrix[i] = matrix[0] + i * s;
            }
        }

        int k = 0;
        for(auto node : nodes) {
            pos2node[k] = node;
            node2pos[node] = k++;
            matrix[k][k] = 0;
        }

        for(auto link : links) {
            int a = node2pos[link.A];
            int b = node2pos[link.B];
            matrix[a][b] = link.metric;
            matrix[b][a] = link.metric;
        }

        for(int k = 0; k < s; k++)
            for(int i = 0; i < s; i++)
                for(int j = 0; j < s; j++)
                    if(matrix[i][j] > matrix[i][k] + matrix[k][j])
                        matrix[i][j] = matrix[i][k] + matrix[k][j];

        T ret = 0;
        for(int i = 0; i < s; i++){
            for(int j = 0; j < s; j++){
                if(ret < matrix[i][j]) {
                    ret = matrix[i][j];
                }
            }
        }

        pathsUpdated = true;
        return ret;
    }

};

}
