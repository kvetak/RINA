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

#include "Common/APNamingInfo.h"

APNamingInfo::APNamingInfo() :
    apn(APN()), apinstance(""),
    aename(""), aeinstance("")
{
}

APNamingInfo::APNamingInfo(APN napn) : apinstance(""), aename(""), aeinstance("")
{
    this->apn = napn;
}

APNamingInfo::APNamingInfo(APN napn, std::string napinstance,
        std::string naename, std::string naeinstance) :
        apn(napn), apinstance(napinstance),
        aename(naename), aeinstance(naeinstance)
{
}

APNamingInfo::~APNamingInfo()
{
    this->apn = APN();
    this->apinstance = "";
    this->aename = "";
    this->aeinstance = "";
}

std::string APNamingInfo::info() const
{
    std::ostringstream os;
    os << "AP: "<< apn;
    if (!apinstance.empty())
        os << " (" << apinstance << ")";
    if (!aename.empty())
        os << " AE: " << aename;
    if (!aeinstance.empty())
        os << " (" << aeinstance << ")";
    //os << endl;
    return os.str();
}

//Free function
std::ostream& operator<< (std::ostream& os, const APNamingInfo& apni)
{
    return os << apni.info();
}

Register_Class(APNIPair);

APNIPair::APNIPair(APNamingInfo src, APNamingInfo dst) {
    first = src;
    second = dst;
}

APNIPair::APNIPair() {
    first = APNamingInfo();
    second = APNamingInfo();
}

APNIPair::APNIPair(const char* src, const char* dst) :
        APNIPair(APNamingInfo(APN( std::string(src) ) ), APNamingInfo(APN( std::string(dst) ) ))
{
}

APNIPair::~APNIPair() {
    first = APNamingInfo();
    second = APNamingInfo();
}

std::ostream& operator <<(std::ostream& os, const APNIPair& apnip) {
    return os << apnip.info();
}

std::string APNIPair::info() const {
    std::ostringstream os;
    os << "SRC> "<< first << "\tDST> " << second;
    return os.str();
}
