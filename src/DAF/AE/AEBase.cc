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

#include "AEBase.h"

Define_Module(AEBase);

const APNamingInfo& AEBase::getApni() const {
    return apni;
}

void AEBase::setApni(const APNamingInfo& apni) {
    this->apni = apni;
}

const Flows& AEBase::getFlows() const {
    return flows;
}

void AEBase::setFlows(const Flows& flows) {
    this->flows = flows;
}

const std::string& AEBase::getSrcAeInstance() const {
    return srcAeInstance;
}

void AEBase::setSrcAeInstance(const std::string& srcAeInstance) {
    this->srcAeInstance = srcAeInstance;
}

const std::string& AEBase::getSrcAeName() const {
    return srcAeName;
}

void AEBase::setSrcAeName(const std::string& srcAeName) {
    this->srcAeName = srcAeName;
}

const std::string& AEBase::getSrcApInstance() const {
    return srcApInstance;
}

void AEBase::setSrcApInstance(const std::string& srcApInstance) {
    this->srcApInstance = srcApInstance;
}

const std::string& AEBase::getSrcApName() const {
    return srcApName;
}

void AEBase::setSrcApName(const std::string& srcApName) {
    this->srcApName = srcApName;
}

void AEBase::initNamingInfo() {
    //Source info
    srcApName = this->getParentModule()->par("apName").str();
    srcApInstance = this->getParentModule()->par("apInstance").str();
    srcAeName = this->par("aeName").str();
    srcAeInstance = this->par("aeInstance").str();

    apni = APNamingInfo(APN(this->srcApName), this->srcApInstance,
            this->srcAeName, this->srcAeInstance);
}

void AEBase::initialize()
{
    initNamingInfo();
}

void AEBase::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}

void AEBase::insert(const Flow& flow) {
    flows.push_back(flow);
}

bool AEBase::isFlowUsed(const Flow* flow) {
    for (TFlowsIter it = flows.begin(); it != flows.end(); ++it) {
        if (*it == *flow)
            return true;
    }
    return false;
}
