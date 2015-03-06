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

#endif /* UTILS_H_ */
