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
 * Utils.h
 *
 *  Created on: Mar 5, 2015
 *      Author: gaixas1
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <sstream>
#include <vector>

#include "omnetpp.h"

/*
 * Explode a string into a vector of strings, given a delimiter
 *
 */
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

/*
 * Implode the first n values of a vector of string into a strings, separated by a delimiter
 *
 */
std::string join(const std::vector<std::string> &elems, const unsigned int n, const char delim);


/*
 * Check if the first value is a prefix of the second
 *
 */
bool isPrefix(std::string prefix, std::string s);


/*
 * A OR B into dst
 * return number of true positions
 */
int intersectBv(std::vector<bool> & A, std::vector<bool> & B, std::vector<bool> & dst);

/*
 * A AND B into dst
 * return number of true positions
 */
int unionBv(std::vector<bool> & A, std::vector<bool> & B, std::vector<bool> & dst);

/*
 * A included into B
 * return true if each true position in A is true in B
 */
bool includedBv(std::vector<bool> & A, std::vector<bool> & B);

/*
 * A included into B
 * return true if each true position in A is true in B
 * sets C as the intersection between A & B
 */
bool includedBv(std::vector<bool> & A, std::vector<bool> & B, std::vector<bool> & C);


/*
 * Iterate distance matrix DM
 */
void iterateDM(unsigned char ** DM, unsigned int l, unsigned char inf);

/**
 * Display the selected policy next to given policy module.
 *
 * @param mod target instance
 */
void setPolicyDisplayString(cModule* mod, const char* str = nullptr);

/**
 * A convenience function for interconnecting two modules.
 *
 * @param m1 first module
 * @param m2 second module
 * @param n1 first module gate name
 * @param n2 second module gate name
 */
void interconnectModules(cModule* m1, cModule* m2, std::string n1, std::string n2);


/**
 * A getModuleByPath wrapper accepting individual modules in the path as variables.
 * e.g. TMod* newMod = (TMod*)parentMod->getModuleByPath("^.^.a.b")
 *      ==
 *      getRINAModule<TMod*>(parentMod, 2, {"a", "b"})
 *
 * @tparam target module type
 * @param curMod starting module
 * @param parentLevel level of initial ascent into parent modules
 * @param modPath path of modules to descent into
 * @param nullCheck causes an exception to be thrown in case of module not present
 * @return pointer to the retrieved module
 */
template<typename modType>
modType getRINAModule(  cModule* curMod,
                        int parentLevel,
                        std::initializer_list<const char*> modPath,
                        bool nullCheck = true)
{
    std::ostringstream modulePath;
    while (parentLevel--) { modulePath << ".^"; }
    for (auto elem : modPath) { modulePath << "." << elem; }
    cModule* mod = curMod->getModuleByPath(modulePath.str().c_str());
    return (nullCheck ? check_and_cast<modType>(mod) : dynamic_cast<modType>(mod));
}

int m_iuniform(int min, int max);
double m_duniform(double min, double max);
simtime_t m_tuniform(simtime_t min, simtime_t max);

#endif /* UTILS_H_ */
