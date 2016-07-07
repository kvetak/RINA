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

#pragma once

#include <iostream>
#include <string>
#include <functional>

using namespace std;

inline int hashFlow(const string &src, const string & dst, const int & src_cepid, const int & dst_cepid) {
    std::hash<std::string> hash_fn;
    return hash_fn(src) ^ hash_fn(dst) ^ src_cepid ^ dst_cepid;
}


inline string inverse(const string & s, const int &l) {
    string r = "";
    for(int i = s.length() - l; i>= 0; i-=l) {
        for(int j = 0; j < l; j++) {
            r += s[i+j];
        }
    }
    return r;
}

inline string reduce(const string & s, const int &symbolLen){
   // cout << s << " " << (s.length()/symbolLen)<< endl;
    bool changes;
    string t = s;
    do {
        changes = false;
        int k = t.length()/symbolLen;
        int i = 0;
        string r = "";

        if(k == 0) { return ""; }

        do {
            bool m = true;
            for(int j = 0; j < symbolLen; j++) {
                if(s[i*symbolLen+j] != s[(i+1)*symbolLen+j]) { m = false; }
            }
            if(m) {
                i+=2;
                changes = true;
            } else {
                i++;
                for(int j = 0; j < symbolLen; j++) {
                    r +=t[i*symbolLen+j];
                }
            }
            if(i == k-1) {
                for(int j = 0; j < symbolLen; j++) {
                    r +=t[i*symbolLen+j];
                }
            }
            t = r;
        } while(i < k-1);
    } while(changes);
  //  cout <<  " --> " << t <<  endl;
    return t;
}

inline int getFirst(const string & s, const int &symbolLen) {
    return stoul(s.substr(0, symbolLen), nullptr, 16);
}
