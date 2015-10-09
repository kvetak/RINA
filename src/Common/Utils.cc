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

/*
 * Utils.cpp
 *
 *  Created on: Mar 5, 2015
 *      Author: gaixas1
 */

#include <Utils.h>
#include <algorithm>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
   while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

std::string join(const std::vector<std::string> &elems, const unsigned int n, const char delim) {
    std::string s = "";
    char d[2] = {delim, 0};

    for(unsigned int i = 0; i < elems.size() && i<n; i++){
        if(i>0){
            s.append(d);
        }
        s.append(elems.at(i));
    }

    return s;
}

bool isPrefix(std::string prefix, std::string s) {
    if(prefix.size() > s.size()) {
        return false;
    }
    return std::mismatch(prefix.begin(), prefix.end(), s.begin()).first == prefix.end();
}

cModule* getRINAModule(cModule* curMod, int parentLevel, std::initializer_list<const char*> modPath)
{
    std::ostringstream modulePath;

    while (parentLevel)
    {
        modulePath << ".^";
        --parentLevel;
    }

    for (auto elem : modPath)
    {
        modulePath << "." << elem;
    }

    cModule* ret = curMod->getModuleByPath(modulePath.str().c_str());
    ASSERT(ret != NULL);
    return ret;
}
