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

#include "DIF/RMT/PDUForwarding/GREFWD/Clos/Clos.h"

Register_Class(GRE::Clos0);
Register_Class(GRE::Clos1);
Register_Class(GRE::Clos2);

namespace GRE {

void Clos0::setZone(const addr_t & v) { A = v; }
void Clos0::setSpines(const index_t & v) { B = v; }
grouprange_t Clos0::execRule(const addr_t & a) {
    //cout << "Clos 0"<<endl;
    addr_t z = getZone(a);
    if(z == A) {                                                    // Same zone
        //cout << "use " << 1 << " , " << 0 << " , " << groups[1].size() <<endl;
        return grouprange_t(1, 0, groups[1].size());
    } else if(z < B) {                                              // Specific Spine set
        //cout << "use " << 0 << " , " << z << " , " << 1 <<endl;
        return grouprange_t(0, z, 1);
    } else {                                                        // Other Pod
        //cout << "use " << 2 << " , " << 0 << " , " << groups[2].size() <<endl;
        return grouprange_t(2, 0, groups[2].size());
    }
}

void Clos1::setZone(const addr_t & v) { A = v; }
void Clos1::setIdentifier(const addr_t & v) { B = v; }
void Clos1::setNumSpines(const addr_t & v) { C = v; }
grouprange_t Clos1::execRule(const addr_t & a) {
    //cout << "Clos 1 - "<< A << " " << B << " " << C <<endl;
    addr_t z = getZone(a);
    addr_t id = getIdentifier(a);

    if(z == A) {
        //cout << "use " << 1 << " , " << 0 << " , " << groups[1].size() <<endl;
        return grouprange_t(1, 0, groups[1].size()); }     // Same zone (no directly connected
    else if(z == B) {
        //cout << "use " << 2 << " , " << id << " , " << 1 <<endl;
        return grouprange_t(2, id, 1); }               // Spine of spine set
    else if (z < C){
        //cout << "use " << 1 << " , " << 0 << " , " << groups[1].size() <<endl;
        return grouprange_t(1, 0, groups[1].size()); }  // Other spine set
    else {
        //cout << "use " << 2 << " , " << 0 << " , " << groups[2].size() <<endl;
        return grouprange_t(2, 0, groups[2].size()); }            // Other Pod
}

void Clos2::setPadding(const index_t & v) { A = v; }
void Clos2::setNumPods(const index_t & v) { B = v; }
grouprange_t Clos2::execRule(const addr_t & a) {
    //cout << "Clos 2"<<endl;
    addr_t z = getZone(a);
    if(z < A) {
        //cout << "use " << 0 << " , " << 0 << " , " << B <<endl;
        return grouprange_t(0, 0, B); }                     // Other spine
    else {
        //cout << "use " << 0 << " , " << (z-A) << " , " << 1 <<endl;
        return grouprange_t(0, z-A, 1); }                        // To a Pod
}

}
