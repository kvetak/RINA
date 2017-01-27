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

#include "Common/APN.h"

APN::APN()
{
    this->name = "";
}

APN::APN(std::string nam)
{
    this->setName(nam);
}

APN::~APN()
{
    this->name = "";
}

const std::string& APN::getName() const
{
    return name;
}

void APN::setName(const std::string& name)
{
    this->name = name;
}

std::string APN::info() const
{
    std::ostringstream os;
    os << this->getName();
    return os.str();
}

//Free function
std::ostream& operator<< (std::ostream& os, const APN& apn)
{
    return os << apn.info();
}

std::ostream& operator <<(std::ostream& os, const APNList& apns)
{
    for (ApnCItem it = apns.begin(); it != apns.end(); ++it) {
        os << *it << " ";
    }
    return os;
}
