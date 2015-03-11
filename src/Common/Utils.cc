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
