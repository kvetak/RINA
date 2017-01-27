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

#include "Common/CongestionDescriptor.h"

Register_Class(CongestionDescriptor);

CongestionDescriptor::CongestionDescriptor()
{
    ConId.setSrcCepId(-1);
    ConId.setDstCepId(-1);
    ConId.setQoSId(VAL_UNDEF_QOSID);
}

CongestionDescriptor::~CongestionDescriptor() {
    ConId.setSrcCepId(-1);
    ConId.setDstCepId(-1);
    ConId.setQoSId("");
}

ConnectionId& CongestionDescriptor::getConnectionId() {
    return ConId;
}

CongestionDescriptor::CongestionDescriptor(int srcCepId, int dstCepId,
        std::string qosId)
{
    ConId.setSrcCepId(srcCepId);
    ConId.setDstCepId(dstCepId);
    ConId.setQoSId(qosId);
}

void CongestionDescriptor::setConnectionId(const ConnectionId& conId) {
    ConId = conId;
}

std::string CongestionDescriptor::getCongesDescrName() const {
    std::stringstream os;
    os << ConId.getSrcCepId() << "<=>" << ConId.getDstCepId();
    return os.str();
}

CongestionDescriptor* CongestionDescriptor::dup() const {
    CongestionDescriptor* congDesc = new CongestionDescriptor();
    congDesc->getConnectionId().setSrcCepId(ConId.getSrcCepId());
    congDesc->getConnectionId().setDstCepId(ConId.getDstCepId());
    congDesc->getConnectionId().setQoSId(ConId.getQoSId());
    return congDesc;
}
