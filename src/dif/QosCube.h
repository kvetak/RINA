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

#ifndef QOSCUBE_H_
#define QOSCUBE_H_

/*
 *
 */
class QosCube {
private:
    int avgBand; //Average bandwidth (measured at the application in bits/sec)
    int avgSDUBand;//Average SDU bandwidth (measured in SDUs/sec)
    int peakBandDuration; //Peak bandwidth-duration (measured in bits/sec);
    int peakSDUBandDuration; //Peak SDU bandwidth-duration (measured in SDUs/sec);
    int burstPeriod; //Burst period measured in seconds
    int burstDuration; //Burst duration, measured in fraction of Burst Period
    int undetectedBitErr; //Undetected bit error rate measured as a probability
    int maxSDUsize; //MaxSDUSize measured in bytes
    bool partDeliv; //Partial Delivery - Can SDUs be delivered in pieces rather than all at once?
    bool incompleteDeliv; //Incomplete Delivery – Can SDUs with missing pieces be delivered?
    bool forceOrder; // - Must SDUs be delivered in order?
    int maxAllowGap; //Max allowable gap in SDUs, (a gap of N SDUs is considered the same as all SDUs delivered, i.e. a gap of N is a "don't care.")
    int delay; //Delay in secs
    int jitter; //Jitter in secs2

public:
    QosCube();
    virtual ~QosCube();
    int getAvgBand() const;
    void setAvgBand(int avgBand);
    int getAvgSduBand() const;
    void setAvgSduBand(int avgSduBand);
    int getBurstDuration() const;
    void setBurstDuration(int burstDuration);
    int getBurstPeriod() const;
    void setBurstPeriod(int burstPeriod);
    int getDelay() const;
    void setDelay(int delay);
    bool isForceOrder() const;
    void setForceOrder(bool forceOrder);
    bool isIncompleteDeliv() const;
    void setIncompleteDeliv(bool incompleteDeliv);
    int getJitter() const;
    void setJitter(int jitter);
    int getMaxAllowGap() const;
    void setMaxAllowGap(int maxAllowGap);
    int getMaxSdUsize() const;
    void setMaxSdUsize(int maxSdUsize);
    bool isPartDeliv() const;
    void setPartDeliv(bool partDeliv);
    int getPeakBandDuration() const;
    void setPeakBandDuration(int peakBandDuration);
    int getPeakSduBandDuration() const;
    void setPeakSduBandDuration(int peakSduBandDuration);
    int getUndetectedBitErr() const;
    void setUndetectedBitErr(int undetectedBitErr);
};

#endif /* QOSCUBE_H_ */
