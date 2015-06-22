//
// Copyright © 2014 - 2015 PRISTINE Consortium (http://ict-pristine.eu)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include "dlCUInfo.h"
#include <algorithm>

namespace DQMonitor {

ILimVals::ILimVals(double i, long long r, long long sr, double sv, double p):
    index(i), rate(r), spaceRate(sr), spaceVar(sv), dropProb(p){}

IDropProb::IDropProb(int i, double p):
    index(i), prob(p){}

PP::PP(int prio, double prob):
    priority(prio), probability(prob) {}


IDegrad::IDegrad(double i):
    index(i){}

int IDegrad::getRandomPriority (int def){
    int p = def;

    double t = 0, lim = uniform(0,1);
    for(PPlistIt it = PPs.begin(); it != PPs.end(); it++){
        p = it->priority;
        t += it->probability;
        if(t > lim) { break; }
    }

    return p;
}

template <typename T> bool compareIndex(const T& a, const T& b) {
    return a.index < b.index;
}

Times::Times():
    serveT(0), spaceT(0) {}

Times::Times(double se, double sp):
    serveT(se), spaceT(sp) {}

L::L(){}

L::L(bool lim, bool spa, ILimValsList v, IDropProbList d):
    limit(lim), space(spa), vl(v), dl(d) {
    sort(vl.begin(), vl.end(), compareIndex<ILimVals>);
    sort(dl.begin(), dl.end(), compareIndex<IDropProb>);
}


bool L::needRate() {
    return space || limit;
}

bool L::spaces() {
    return space;
}
bool L::limits() {
    return limit;
}

Times L::getTimes(double wt, int size) {
    Times t(0.0, 0.0);
    long long rate = LLONG_MAX;
    long long sprate = LLONG_MAX;
    double spvar = 0.0;

    for(ILimValsIt it = vl.begin(); it != vl.end(); it++) {
        if(wt <= it->index) {
            rate = it->rate;
            sprate = it->spaceRate;
            spvar = it->spaceRate;
        }
    }

    if(limit || space) {
        if(rate!=LLONG_MAX){ t.serveT = ((double)size)/((double)rate); }
        if(space && sprate!=LLONG_MAX){
            double avg = ((double)size)/((double)sprate);
            t.spaceT =  avg*uniform(1-spvar, 1+spvar);
        }
    }

    return t;
}

double L::getDropProb(double wt, int ws) {
    if(limit) {
        double tw = 0, ts = 0;
        for(ILimValsIt it = vl.begin(); it != vl.end(); it++) {
            if(wt >= it->index) { tw = it->dropProb; }
            else { break; }
        }
        for(IDropProbIt it = dl.begin(); it != dl.end(); it++) {
            if(ws >= it->index) { ts = it->prob; }
            else { break; }
        }
        return max(tw, ts);
    }
    return 0;
}

C::C(){}

C::C(double dd, IDropProbList d):
    defaultDropProb(dd), dl(d) {
    sort(dl.begin(), dl.end(), compareIndex<IDropProb>);
}

double C::getDropProb(int s) {
    double t = defaultDropProb;
    for(IDropProbIt it = dl.begin(); it != dl.end(); it++) {
        if(s >= it->index) { t = it->prob; }
        else { break; }
    }
    return t;
}

U::U(){}

U::U(int dp, bool deg, long long r, IDegradList d):
    defaultPriority(dp), degrad(deg), rate(r), dl(d){
    sort(dl.begin(), dl.end(), compareIndex<IDegrad>);
}

bool U::isDegraded() {
    return degrad;
}

double U::getTime(int size) {
    if(degrad) { return ((double)size)/((double)rate); }
    else { return 0.0; }
}

int U::getPriority(double wt) {
    if(!degrad) { return defaultPriority; }

    IDegrad * pr = NULL;

    for(IDegradIt it = dl.begin(); it != dl.end(); it++) {
        if(wt >= it->index) { pr = &(*it); }
        else { break; }
    }

    if(pr == NULL) { return defaultPriority; }

    return pr->getRandomPriority(defaultPriority);
}

dlCUInfo::dlCUInfo() {}
dlCUInfo::dlCUInfo(string qn, L * l, C * c, U * u) :
        queueName(qn), limit(l), cherish(c), urgency(u) {}

///////////////////OLD

/*



dlCUInfo::dlCUInfo(std::string id, cherishL * ch, urgencyL * ur, inputL * lim) {
    CUId = id;
    cherish = ch;
    urgency = ur;
    inLimit = lim;
}


bool parse(cXMLElementList vals, irangeTProbs& res){
    bool found0 = false;
    for (cXMLElementList::iterator it = vals.begin(); it != vals.end(); ++it) {
        cXMLElement* n = *it;
        if (!n->getAttribute("mark") || !n->getAttribute("val") || !n->getAttribute("prob")) {
            return false;
        }

        int mark = atoi(n->getAttribute("mark"));
        int val = atoi(n->getAttribute("val"));
        double prob = atof(n->getAttribute("prob"));

        if(mark < 0) { return false; }
        if(val < 0) { return false; }
        if(prob < 0 || prob > 1) { return false; }

        if(mark == 0) { found0 = true; }

        res[mark] = typeProb(val, prob);
    }
    return found0;
}

bool parse(cXMLElementList vals, drangeTProbs& res){
    bool found0 = false;
    for (cXMLElementList::iterator it = vals.begin(); it != vals.end(); ++it) {
        cXMLElement* n = *it;
        if (!n->getAttribute("mark") || !n->getAttribute("val") || !n->getAttribute("prob")) {
            return false;
        }

        int mark = atof(n->getAttribute("mark"));
        int val = atoi(n->getAttribute("val"));
        double prob = atof(n->getAttribute("prob"));

        if(mark < 0) { return false; }
        if(val < 0) { return false; }
        if(prob < 0 || prob > 1) { return false; }

        if(mark == 0) { found0 = true; }

        res[mark] = typeProb(val, prob);
    }
    return found0;
}

bool parse(cXMLElementList vals, irangeDouble& res){
    bool found0 = false;
    for (cXMLElementList::iterator it = vals.begin(); it != vals.end(); ++it) {
        cXMLElement* n = *it;
        if (!n->getAttribute("mark") || !n->getAttribute("val")) {
            return false;
        }

        int mark = atoi(n->getAttribute("mark"));
        int val = atof(n->getAttribute("val"));

        if(mark < 0) { return false; }
        if(val < 0) { return false; }

        if(mark == 0) { found0 = true; }

        res[mark] = typeProb(val, prob);
    }
    return found0;
}

bool parse(cXMLElementList vals, drangeDouble& res){
    bool found0 = false;
    for (cXMLElementList::iterator it = vals.begin(); it != vals.end(); ++it) {
        cXMLElement* n = *it;
        if (!n->getAttribute("mark") || !n->getAttribute("val")) {
            return false;
        }

        int mark = atof(n->getAttribute("mark"));
        int val = atof(n->getAttribute("val"));

        if(mark < 0) { return false; }
        if(val < 0) { return false; }

        if(mark == 0) { found0 = true; }

        res[mark] = typeProb(val, prob);
    }
    return found0;
}

bool parse(cXMLElementList vals, irangeInt& res){
    bool found0 = false;
    for (cXMLElementList::iterator it = vals.begin(); it != vals.end(); ++it) {
        cXMLElement* n = *it;
        if (!n->getAttribute("mark") || !n->getAttribute("val")) {
            return false;
        }

        int mark = atoi(n->getAttribute("mark"));
        int val = atoi(n->getAttribute("val"));

        if(mark < 0) { return false; }
        if(val < 0) { return false; }

        if(mark == 0) { found0 = true; }

        res[mark] = typeProb(val, prob);
    }
    return found0;
}

bool parse(cXMLElementList vals, drangeInt& res){
    bool found0 = false;
    for (cXMLElementList::iterator it = vals.begin(); it != vals.end(); ++it) {
        cXMLElement* n = *it;
        if (!n->getAttribute("mark") || !n->getAttribute("val")) {
            return false;
        }

        int mark = atof(n->getAttribute("mark"));
        int val = atoi(n->getAttribute("val"));

        if(mark < 0) { return false; }
        if(val < 0) { return false; }

        if(mark == 0) { found0 = true; }

        res[mark] = typeProb(val, prob);
    }
    return found0;
}


bool cherishL::parse_outDropProb(cXMLElementList::iterator attrs) {
    for (cXMLElementList::iterator it = attrs.begin(); it != attrs.end(); ++it) {
        cXMLElement* n = *it;
        if ( !strcmp(n->getTagName(), "outDropProb") ) {
            return parse(n->getChildren(), _outDropProb);
        }
    }
    return false;
}

bool inputL::parseS_inSpace(cXMLElementList::iterator attrs) {
    for (cXMLElementList::iterator it = attrs.begin(); it != attrs.end(); ++it) {
        cXMLElement* n = *it;
        if ( !strcmp(n->getTagName(), "inSpace") ) {
            return parse(n->getChildren(), s_inSpace);
        }
    }
    return false;
}

bool inputL::parseS_inSpaceVar(cXMLElementList::iterator attrs) {
    for (cXMLElementList::iterator it = attrs.begin(); it != attrs.end(); ++it) {
        cXMLElement* n = *it;
        if ( !strcmp(n->getTagName(), "inSpaceVar") ) {
            return parse(n->getChildren(), s_inSpaceVar);
        }
    }
    return false;
}
bool inputL::parseS_inDropProb(cXMLElementList::iterator attrs) {
    for (cXMLElementList::iterator it = attrs.begin(); it != attrs.end(); ++it) {
        cXMLElement* n = *it;
        if ( !strcmp(n->getTagName(), "inDropProb") ) {
            return parse(n->getChildren(), s_inDropProb);
        }
    }
    return false;
}
bool urgencyL::parseS_pUrgency(cXMLElementList::iterator attrs) {
    for (cXMLElementList::iterator it = attrs.begin(); it != attrs.end(); ++it) {
        cXMLElement* n = *it;
        if ( !strcmp(n->getTagName(), "pUrgency") ) {
            return parse(n->getChildren(), s_pUrgency);
        }
    }
    return false;
}
bool inputL::parseT_inRate(cXMLElementList::iterator attrs) {
    for (cXMLElementList::iterator it = attrs.begin(); it != attrs.end(); ++it) {
        cXMLElement* n = *it;
        if ( !strcmp(n->getTagName(), "inRate") ) {
            return parse(n->getChildren(), t_inRate);
        }
    }
    return false;
}
bool inputL::parseT_inSpace(cXMLElementList::iterator attrs) {
    for (cXMLElementList::iterator it = attrs.begin(); it != attrs.end(); ++it) {
        cXMLElement* n = *it;
        if ( !strcmp(n->getTagName(), "inSpace") ) {
            return parse(n->getChildren(), t_inSpace);
        }
    }
    return false;
}
bool inputL::parseT_inSpaceVar(cXMLElementList::iterator attrs) {
    for (cXMLElementList::iterator it = attrs.begin(); it != attrs.end(); ++it) {
        cXMLElement* n = *it;
        if ( !strcmp(n->getTagName(), "inSpaceVar") ) {
            return parse(n->getChildren(), t_inSpaceVar);
        }
    }
    return false;
}
bool inputL::parseT_inDropProb(cXMLElementList::iterator attrs) {
    for (cXMLElementList::iterator it = attrs.begin(); it != attrs.end(); ++it) {
        cXMLElement* n = *it;
        if ( !strcmp(n->getTagName(), "inDropProb") ) {
            return parse(n->getChildren(), t_inDropProb);
        }
    }
    return false;
}
bool urgencyL::parseT_outRate(cXMLElementList::iterator attrs) {
    for (cXMLElementList::iterator it = attrs.begin(); it != attrs.end(); ++it) {
        cXMLElement* n = *it;
        if ( !strcmp(n->getTagName(), "outRate") ) {
            return parse(n->getChildren(), t_outRate);
        }
    }
    return false;
}
bool urgencyL::parseT_pUrgency(cXMLElementList::iterator attrs) {
    for (cXMLElementList::iterator it = attrs.begin(); it != attrs.end(); ++it) {
        cXMLElement* n = *it;
        if ( !strcmp(n->getTagName(), "pUrgency") ) {
            return parse(n->getChildren(), t_pUrgency);
        }
    }
    return false;
}

*/
}
