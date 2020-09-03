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

// @author karlhto
// This is heavily inspired by INET's ARP protocol machine.

cplusplus {{
#include "inet/common/packet/chunk/FieldsChunk.h"
#include "inet/linklayer/common/MacAddress.h"
#include "Common/APN.h"

#define ARP_BASE_LEN 14 // 2 * mac addresses (12) + apnLength + opcode
}}

class noncobject APN;

class noncobject inet::MacAddress;
class noncobject inet::FieldsChunk;


enum ARPOpcode
{
    ARP_REQUEST = 1;
    ARP_REPLY = 2;
    ARP_RARP_REQUEST = 3;
    ARP_RARP_REPLY = 4;
}

//
// RINArpPacket. This type of ARPPacket is specialised for RINA, which uses
// variable length addresses.
class RINArpPacket extends inet::FieldsChunk
{
    uint8_t apnLength;
    uint8_t opcode @enum(ARPOpcode);
    inet::MacAddress srcMacAddress;
    APN srcApName;
    inet::MacAddress dstMacAddress;
    APN dstApName;
}
