// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "DIF/RMT/PDUForwarding/GREFWD/GREFWD.h"

Register_Class(GRE::GREFWD);

namespace GRE {

vPorts GREFWD::lookup(const PDU * pdu) {
    vPorts ret;

    PDU * pd = const_cast<PDU*>(pdu);
    auto hc = pd->getHopCount();
    if(hc <= par("TTL").longValue()) {
        cout << "Over TTL"<<endl;
        return ret;
    }
    pd->setHopCount(hc-1);

    //Patch for empty lookup bug
    string dstAddr = pdu->getDstAddr().getIpcAddress().getName();
    if(dstAddr == "") { return ret; }


    // Parse destination address
    addr_t d = parseRawAddr(dstAddr);

    // Check if it's a neighbour and is connected
    if(isNeighbour(d)) {
        index_t i = getNeighbourId(d);
        port_t & p = ports[i];
        if(p != nullptr) {
            ret.push_back(p);
            return ret;
        }
    }

    // Compute flow "hash"
    rand_t h = hashFlow(parseRawAddr(pdu->getSrcAddr().getIpcAddress().getName()), d, pdu->getConnId().getSrcCepId(), pdu->getConnId().getDstCepId());

    // Query next output port to reach destination with hash h
    port_t p = getNext(d, h);
    if(p != nullptr) { ret.push_back(p); }

    return ret;
}

vPorts GREFWD::lookup(const Address &dst, const std::string& qos) {
    vPorts ret;

    //Patch for empty lookup bug
    string dstAddr = dst.getIpcAddress().getName();
    if(dstAddr == "") { return ret; }

    // Parse destination address
    addr_t d = parseRawAddr(dstAddr);

    // Check if it's a neighbour and is connected
    if(isNeighbour(d)) {
        index_t i = getNeighbourId(d);
        port_t & p = ports[i];
        if(p != nullptr) {
            ret.push_back(p);
            //return ret;
        }
        return ret; //??
    }

    // Compute flow "hash"
    rand_t h = hashFlow(myaddr, d, 0, 0);

    // Query next output port to reach destination with hash h
    port_t p = getNext(d, h);
    if(p != nullptr) { ret.push_back(p); }
    return ret;
}

void GREFWD::setGroup(const index_t & groupId, const vPortsIndex & neis) {
    // Ensure there are enough groups
    while(groups.size() <= groupId) { groups.push_back(vPortsIndex()); }
    groups[groupId] = neis;
}
void GREFWD::unsetGroup(const index_t & groupId) {
    groups[groupId].clear();
    if(groups.size() == (index_t)(groupId+1)) { groups.pop_back(); }
}

void GREFWD::setNeighbour(const addr_t dst, const index_t & index) {
    neiId[dst] = index;
}
void GREFWD::unsetNeighbour(const addr_t dst) {
    neiId.erase(dst);
}

void GREFWD::addPort(const index_t & index, const port_t port) {
    while(ports.size() <= index) { ports.push_back(nullptr); }
    ports[index] = port;
}
void GREFWD::removePort(const index_t & index) {
    while(ports.size() <= index) { ports.push_back(nullptr); }
    ports[index] = nullptr;
}


void GREFWD::addException(const mask_t & mask, const exception_t & e) {
    exceptions[mask] = e;
}

void GREFWD::setExceptions(const map<mask_t, exception_t> & _exceptions) {
    exceptions = _exceptions;
}

void GREFWD::removeException(const mask_t & mask) {
    exceptions.erase(mask);
}

void GREFWD::onPolicyInit() {
    string rawAddr = getModuleByPath("^.^")->par("ipcAddress").stringValue();
    myaddr = parseRawAddr(rawAddr);

    postPolicyInit();
}

string GREFWD::toString() {
    std::ostringstream os;

    os << hex;
    os << "Forwarding policy at "<<myaddr<<endl;
    os <<getFullPath()<<endl;

        for(unsigned int i = 0; i< ports.size(); i++) {
            os << "\tPort " << (int)i << " => "<< (ports[i]!=nullptr? "OK":"NULL")<<endl;
        }
        for(unsigned int i = 1; i < groups.size(); i++) {
            os << "\tGroup " << (int)i << " :";
            for(auto g : groups[i]) {
                os << " "<< (int)g ;
            }
            os <<endl;
        }
        os << "\tNeis"<<endl;
        for(auto ni : neiId) {
            os<<hex<< "\t\t"<<(int)ni.first << " -> "<< (int)ni.second <<endl;
        }

    if(!exceptions.empty()) {
        os << "\tExceptions"<<endl;
        for(auto me : exceptions) {
            os << "\t  "<< me.first.v << "\\"<< (int)me.first.l << endl;
            switch(me.second.mode) {
                case COMMON : { // Listing possible neighbours
                    os << "\t     - COMMON : ";
                    for(auto i : me.second.list ) {
                        os << (int)i<< " ";
                    }
                    os << endl;
                } break;
                case ANY : { // Any neighbour possible
                    os << "\t     - ANY ";
                } break;
                case GROUPA : { // Only Group neighbour possible
                    os << "\t     - GROUP "<<(int)me.second.group<<endl;
                } break;
                case INVERSE : { // Any neighbour - Exceptions possible
                    os << "\t     - INVERSE : ";
                    for(auto i : me.second.list ) {
                        os << (int)i<< " ";
                    }
                    os << endl;
                } break;
                case INVERSEGROUP : { // Group neighbour - Exceptions possible
                    os << "\t     - INVERSE - GROUP "<<(int)me.second.group<<" : ";
                    for(auto i : me.second.list ) {
                        os << (int)i<< " ";
                    }
                    os << endl;
                } break;
                case UNREACHABLE :
                    os << "\t     - UNREACHABLE "<<endl;
            }
        }
    }
    os<<endl;
    os <<dec;

    return os.str();
}

void GREFWD::finish() {
    preFinish();


    if(par("printAtEnd").boolValue()) {

        cout << hex;
        cout << "Forwarding policy at "<<myaddr<<endl;
        cout <<getFullPath()<<endl;

            for(unsigned int i = 0; i< ports.size(); i++) {
                cout << "Port " << (int)i << " => "<< (ports[i]!=nullptr? "OK":"NULL")<<endl;
            }
            for(unsigned int i = 1; i < groups.size(); i++) {
                cout << "Group " << (int)i << " :";
                for(auto g : groups[i]) {
                    cout << " "<< (int)g ;
                }
                cout <<endl;
            }
            cout << "Neis"<<endl;
            for(auto ni : neiId) {
                cout<<hex<< (int)ni.first << " -> "<< (int)ni.second <<endl;
            }

        if(!exceptions.empty()) {
            cout << "Exceptions"<<endl;
            for(auto me : exceptions) {
                cout << "  "<< me.first.v << "\\"<< (int)me.first.l << endl;
                switch(me.second.mode) {
                    case COMMON : { // Listing possible neighbours
                        cout << "     - COMMON : ";
                        for(auto i : me.second.list ) {
                            cout << (int)i<< " ";
                        }
                        cout << endl;
                    } break;
                    case ANY : { // Any neighbour possible
                        cout << "     - ANY ";
                    } break;
                    case GROUPA : { // Only Group neighbour possible
                        cout << "     - GROUP "<<(int)me.second.group<<endl;
                    } break;
                    case INVERSE : { // Any neighbour - Exceptions possible
                        cout << "     - INVERSE : ";
                        for(auto i : me.second.list ) {
                            cout << (int)i<< " ";
                        }
                        cout << endl;
                    } break;
                    case INVERSEGROUP : { // Group neighbour - Exceptions possible
                        cout << "     - INVERSE - GROUP "<<(int)me.second.group<<" : ";
                        for(auto i : me.second.list ) {
                            cout << (int)i<< " ";
                        }
                        cout << endl;
                    } break;
                    case UNREACHABLE :
                        cout << "     - UNREACHABLE "<<endl;
                }
            }
        }
        cout<<endl;
        cout <<dec;
     }
    exceptions.clear();
    ports.clear();
}

port_t GREFWD::getNext(const addr_t & a, const rand_t & r) {
    exception_p ep = getException(a);
    if(ep != nullptr) { // There is an exception
        switch(ep->mode) {
            case COMMON : { // Listing possible neighbours
                vPortsIndex & G = ep->list;
                int T = G.size();
                if(T <= 0) { return nullptr; }
                int R = r%T; // "Random" port to use
                for(int k = 0; k < T; k++) { // Try at most T times
                    port_t p = ports[G[R]];
                    if(p != nullptr) { return p; }
                    R = (R+1)%T;
                }
            } break;
            case ANY : { // Any neighbour possible
                int T = ports.size();
                if(T <= 0) { return nullptr; }
                int R = r%T; // "Random" port to use
                for(int k = 0; k < T; k++) { // Try at most T times
                    port_t p = ports[R];
                    if(p != nullptr) { return p; }
                    R = (R+1)%T;
                }
            } break;
            case GROUPA : { // Only Group neighbour possible
                vPortsIndex & G = groups[ep->group];
                int T = G.size();
                if(T <= 0) { return nullptr; }
                int R = r%T; // "Random" port to use
                for(int k = 0; k < T; k++) { // Try at most T times
                    port_t p = ports[G[R]];
                    if(p != nullptr) { return p; }
                    R = (R+1)%T;
                }
            } break;
            case INVERSE : { // Any neighbour - Exceptions possible
                vPortsIndex & N = ep->list;
                int Gs = ports.size();
                int Ns = N.size();
                int T = Gs-Ns;
                if(T <= 0) { return nullptr; }
                int R = r%T; // "Random" neighbour to use
                int i = 0;
                int j = 0;
                while(i == N[j]) { //Jump function, skips index both in G and N
                    i = (i+1)%Gs;
                    j = (j+1)%Ns;
                }
                for(int k = 0; k< R; k++) { // Skip to the Rth valid G[i]
                    i = (i+1)%Gs;
                    while(i == N[j]) { //Jump
                        i = (i+1)%Gs;
                        j = (j+1)%Ns;
                    }
                }
                for(int k = 0; k < T; k++) { // Try at most T times
                    port_t p = ports[i];
                    if(p != nullptr) { return p; }
                    i = (i+1)%Gs;
                    while(i == N[j]) { // Jump
                        i = (i+1)%Gs;
                        j = (j+1)%Ns;
                    }
                }
            } break;
            case INVERSEGROUP : { // Group neighbour - Exceptions possible
                vPortsIndex & G = groups[ep->group];
                vPortsIndex & N = ep->list;
                int Gs = G.size();
                int Ns = N.size();
                int T = Gs-Ns;
                if(T <= 0) { return nullptr; }
                int R = r%T; // "Random" neighbour to use
                int i = 0;
                int j = 0;
                while(G[i] == N[j]) { //Jump function, skips index both in G and N
                    i = (i+1)%Gs;
                    j = (j+1)%Ns;
                }
                for(int k = 0; k< R; k++) { // Skip to the Rth valid G[i]
                    i = (i+1)%Gs;
                    while(G[i] == N[j]) { //Jump
                        i = (i+1)%Gs;
                        j = (j+1)%Ns;
                    }
                }
                for(int k = 0; k < T; k++) { // Try at most T times
                    port_t p = ports[G[i]];
                    if(p != nullptr) { return p; }
                    i = (i+1)%Gs;
                    while(G[i] == N[j]) { // Jump
                        i = (i+1)%Gs;
                        j = (j+1)%Ns;
                    }
                }
            } break;
            case UNREACHABLE :
            default : return nullptr;
        }
    } else { //No exception in use, try rules
        grouprange_t rl = execRule(a);
        if(rl.total > 0) {
            unsigned int R = r%rl.total; // "Random" neighbour to use
            if(rl.group == 0) { // Rule between all neighbours
                for(int k = 0; k < rl.total; k++) { // Try at most total times
                    if(ports.size()<=R+rl.first) { continue; }
                    port_t p = ports[R+rl.first];
                    if(p != nullptr) { return p; }
                    R = (R+1)%rl.total;
                }
            } else { // Rule for specific group
                for(int k = 0; k < rl.total; k++) { // Try at most total times
                    vPortsIndex & G = groups[rl.group];
                    if(G.size()<=R+rl.first) { continue; }
                    port_t p = ports[G[R+rl.first]];
                    if(p != nullptr) { return p; }
                    R = (R+1)%rl.total;
                }
            }
        }
    }
    return nullptr;
}

exception_p  GREFWD::getException(const addr_t & a) {
    for( auto & me : exceptions) {
        const mask_t & m = me.first;
        if(!((a ^ m.v) >> m.l)) {
            return & me.second; }
    }
    return nullptr;
}

}
