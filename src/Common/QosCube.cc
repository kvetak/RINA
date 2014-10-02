//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
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

/*
 * @file QoSCube.cc
 * @author Marcel Marek
 * @date Apr 28, 2014
 * @brief
 * @detail
 */
#include "QosCube.h"

QosCube::QosCube() {
    // TODO Auto-generated constructor stub

}

int QosCube::getAvgBand() const {
    return avgBand;
}

void QosCube::setAvgBand(int avgBand) {
    this->avgBand = avgBand;
}

int QosCube::getAvgSduBand() const {
    return avgSDUBand;
}

void QosCube::setAvgSduBand(int avgSduBand) {
    avgSDUBand = avgSduBand;
}

int QosCube::getBurstDuration() const {
    return burstDuration;
}

void QosCube::setBurstDuration(int burstDuration) {
    this->burstDuration = burstDuration;
}

int QosCube::getBurstPeriod() const {
    return burstPeriod;
}

void QosCube::setBurstPeriod(int burstPeriod) {
    this->burstPeriod = burstPeriod;
}

int QosCube::getDelay() const {
    return delay;
}

void QosCube::setDelay(int delay) {
    this->delay = delay;
}

bool QosCube::isForceOrder() const {
    return forceOrder;
}

void QosCube::setForceOrder(bool forceOrder) {
    this->forceOrder = forceOrder;
}

bool QosCube::isIncompleteDelivery() const {
    return incompleteDeliv;
}

void QosCube::setIncompleteDelivery(bool incompleteDeliv) {
    this->incompleteDeliv = incompleteDeliv;
}

int QosCube::getJitter() const {
    return jitter;
}

void QosCube::setJitter(int jitter) {
    this->jitter = jitter;
}

unsigned int QosCube::getMaxAllowGap() const {
    return maxAllowGap;
}

void QosCube::setMaxAllowGap(unsigned int maxAllowGap) {
    this->maxAllowGap = maxAllowGap;
}

int QosCube::getMaxSduSize() const {
    return maxSDUsize;
}

void QosCube::setMaxSduSize(int maxSdUsize) {
    maxSDUsize = maxSdUsize;
}

bool QosCube::isPartialDelivery() const {
    return partDeliv;
}

void QosCube::setPartialDelivery(bool partDeliv) {
    this->partDeliv = partDeliv;
}

int QosCube::getPeakBandDuration() const {
    return peakBandDuration;
}

void QosCube::setPeakBandDuration(int peakBandDuration) {
    this->peakBandDuration = peakBandDuration;
}

int QosCube::getPeakSduBandDuration() const {
    return peakSDUBandDuration;
}

void QosCube::setPeakSduBandDuration(int peakSduBandDuration) {
    peakSDUBandDuration = peakSduBandDuration;
}

int QosCube::getUndetectedBitErr() const {
    return undetectedBitErr;
}

void QosCube::setUndetectedBitErr(int undetectedBitErr) {
    this->undetectedBitErr = undetectedBitErr;
}

QosCube::~QosCube() {
    // TODO Auto-generated destructor stub
}

bool QosCube::isDtcpOn() const {
    return dtcpOn;
}

unsigned short QosCube::getQosId() const {
    return qoSId;
}

void QosCube::setQosId(unsigned short qoSId) {
    this->qoSId = qoSId;
}

void QosCube::setDtcpOn(bool dtcpOn) {
    this->dtcpOn = dtcpOn;
}

std::ostream& operator <<(std::ostream& os, const QosCube& cube) {
    os << "QoSCube Id> " << cube.getQosId() << endl
       << "   average BW = " << cube.getAvgBand() << " bit/s" << endl
       << "   average SDU BW = " << cube.getAvgSduBand() << " SDU/s" << endl
       << "   peak BW duration = " << cube.getPeakBandDuration() << " bit/s" << endl
       << "   peak SDU BW duration = " << cube.getPeakSduBandDuration() << " SDU/s" << endl
       << "   burst period = " << cube.getBurstPeriod() << " s" << endl
       << "   burst duration = " << cube.getBurstDuration() << " s" << endl
       << "   undetect. bit errors = " << cube.getUndetectedBitErr() << "%" << endl
       << "   max SDU Size = " << cube.getMaxSduSize() << " B" << endl
       << "   partial delivery = " << (cube.isPartialDelivery() ? "yes" : "no" ) << endl
       << "   incomplete delivery = " << (cube.isIncompleteDelivery() ? "yes" : "no" ) << endl
       << "   force order = " << (cube.isForceOrder() ? "yes" : "no" ) << endl
       << "   max allowed gap = " << cube.getMaxAllowGap() << " SDUs" << endl
       << "   delay = " << cube.getDelay() << " s" << endl
       << "   jitter = " << cube.getJitter() << " s" << endl
       << "   dtcp-on = " << (cube.isDtcpOn() ? "yes" : "no" ) << endl;
    return os;
}
