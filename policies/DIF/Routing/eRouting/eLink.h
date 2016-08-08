#pragma once

#include <iostream>

using namespace std;

typedef uint32_t elink_t;
typedef uint16_t eaddr_t;

elink_t getELink(const eaddr_t & a, const eaddr_t & b);
eaddr_t getESrc(const elink_t & a);
eaddr_t getEDst(const elink_t & a);
