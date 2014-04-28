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

bool QosCube::isIncompleteDeliv() const {
    return incompleteDeliv;
}

void QosCube::setIncompleteDeliv(bool incompleteDeliv) {
    this->incompleteDeliv = incompleteDeliv;
}

int QosCube::getJitter() const {
    return jitter;
}

void QosCube::setJitter(int jitter) {
    this->jitter = jitter;
}

int QosCube::getMaxAllowGap() const {
    return maxAllowGap;
}

void QosCube::setMaxAllowGap(int maxAllowGap) {
    this->maxAllowGap = maxAllowGap;
}

int QosCube::getMaxSdUsize() const {
    return maxSDUsize;
}

void QosCube::setMaxSdUsize(int maxSdUsize) {
    maxSDUsize = maxSdUsize;
}

bool QosCube::isPartDeliv() const {
    return partDeliv;
}

void QosCube::setPartDeliv(bool partDeliv) {
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

