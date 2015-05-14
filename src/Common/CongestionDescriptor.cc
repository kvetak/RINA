//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <CongestionDescriptor.h>

Register_Class(CongestionDescriptor);

CongestionDescriptor::CongestionDescriptor()
{
    ConId.setSrcCepId(-1);
    ConId.setDstCepId(-1);
    ConId.setQoSId(0);
}

CongestionDescriptor::~CongestionDescriptor() {
    ConId.setSrcCepId(-1);
    ConId.setDstCepId(-1);
    ConId.setQoSId(0);
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
