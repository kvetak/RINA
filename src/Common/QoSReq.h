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


#ifndef QOSREQ_H_
#define QOSREQ_H_

//Standard libraries
#include <vector>
//RINASim libraries
#include "Common/ExternConsts.h"
#include "Common/QoSCube.h"

extern const char* STR_DONOTCARE;
extern const char* STR_YES;
extern const char* STR_NO;
extern const int   VAL_DEFAULT_QOS;

/**
 * @brief Class representing QoSReq with all its properties that is primarily used by FA, RMT and RA
 * Specification sources are http://nes.fit.vutbr.cz/ivesely/pmwiki.php/RINA/EFCP#t2._QoS-Cube_Specfic_Parameters and http://nes.fit.vutbr.cz/ivesely/pmwiki.php/RINA/ServiceDefinition
 * @authors Vladimir Vesely (ivesely@fit.vutbr.cz)
 * @date Last refactorized and documented on 2015-01-12
 */
class QoSReq {

  protected:

    /**
     * @brief Attribute holding average bandwidth
     */
    int avgBand ;               //Average bandwidth (measured at the application in bits/sec)

    /**
     * @brief Attribute holding average SDU bandwidth
     */
    int avgSDUBand;             //Average SDU bandwidth (measured in SDUs/sec)

    /**
     * @brief Attribute holding peak bandwidth duration
     */
    int peakBandDuration;       //Peak bandwidth-duration (measured in bits/sec);

    /**
     * @brief Attribute holding peak SDU bandwidth duration
     */
    int peakSDUBandDuration;    //Peak SDU bandwidth-duration (measured in SDUs/sec);

    /**
     * @brief Attribute holding burst period in usecs
     */
    int burstPeriod;            //Burst period measured in useconds

    /**
     * @brief Attribute holding burst durating as usec fraction of burst period
     */
    int burstDuration;          //Burst duration, measured in useconds fraction of Burst Period

    /**
     * @brief Attribute holding probability of undetected bit error rate
     */
    double undetectedBitErr;    //Undetected bit error rate measured as a probability

    /**
     * @brief Attribute holding probability of dropping PDUs
     */
    double pduDropProbability;  //Probability of dropping PDUs

    /**
     * @brief Attribute holding maximum SDU size
     */
    int maxSDUsize;             //MaxSDUSize measured in bytes

    /**
     * @brief Attribute holding partial delivery flag
     */
    bool partDeliv;             //Partial Delivery - Can SDUs be delivered in pieces rather than all at once? (SHOULD NOT be part of QoS cube see EFCPSpec)

    /**
     * @brief Attribute holding incomplete delivery flag
     */
    bool incompleteDeliv;       //Incomplete Delivery - Can SDUs with missing pieces be delivered? (SHOULD NOT be part of QoS cube see EFCPSpec)

    /**
     * @brief Attribute holding in-order delivery flag
     */
    bool forceOrder;            //Must SDUs be delivered in-order bits

    /**
     * @brief Attribute holding maximum allowd gap in SDUs
     */
    int maxAllowGap;            //Max allowable gap in SDUs, (a gap of N SDUs is considered the same as all SDUs delivered, i.e. a gap of N is a "don't care.")

    /**
     * @brief Attribute holding accepted delay
     */
    int delay;                  //Delay in usecs

    /**
     * @brief Attribute holding accepted jitter
     */
    int jitter;                 //Jitter in usecs

    /**
     * @brief Attribute holding connection's time price
     */
    int costTime;               //measured in $/ms

    /**
     * @brief Attribute holding connection's transmission size price
     */
    int costBits;               //measured in $/Mb

    /**
     * @brief Attribute holding resiliency information, see PRISTINE D4.3 for more
     */
    int resiliencyFactor;


  public:
    /**
     * @brief Constructor of QoSReq with undefined values
     */
    QoSReq();

    QoSReq(int tavgBand, int tavgSDUBand, int tpeakBandDuration, int tpeakSDUBandDuration, int tburstPeriod, int tburstDuration,
           double tundetectedBitErr, double tpduDropProbab,
           int tmaxSDUsize, bool tpartDeliv, bool tincompleteDeliv, bool tforceOrder,
           unsigned int tmaxAllowGap, int tdelay, int tjitter, int tcosttime, int tcostbits);

    QoSReq(cXMLElementList& attrs);

    static const QoSReq MANAGEMENT;

    /**
     * @brief Destructor assigning default uninitialized values
     */
    virtual ~QoSReq();

    /**
     * Comparator comparing this and other AP requirements.
     * @param other
     * @return Returns true if other requirements are same or less than this, otherwise returns false.
     */
    bool compare(const QoSReq& other) const;

    /**
     * @brief Gets Average Bandwidth parameter
     * @return Value measured at the application in bits/sec
     */
    int getAvgBand() const;

    /**
     * @brief Sets Average Bandwidth parameter
     * @param avgBand A new value in bits/sec
     */
    void setAvgBand(int avgBand);

    /**
     * @brief Gets Average SDU Bandwidth parameter
     * @return Value measured in SDUs/sec
     */
    int getAvgSduBand() const;

    /**
     * @brief Sets Average SDU Bandwidth  parameter
     * @param avgSduBand A new value in SDUs/sec
     */
    void setAvgSduBand(int avgSduBand);

    /**
     * @brief Gets Peak Band Duration parameter
     * @return Value measured in bits/sec
     */
    int getPeakBandDuration() const;

    /**
     * @brief Sets Peak Band Duration parameter
     * @param peakBandDuration A new value measured in bits/sec
     */
    void setPeakBandDuration(int peakBandDuration);

    /**
     * @brief Gets Peak SDU Duration parameter
     * @return Value measured in SDUs/sec
     */
    int getPeakSduBandDuration() const;

    /**
     * @brief Sets Peak SDU Duration parameter
     * @param peakSduBandDuration A new value measured in SDUs/sec
     */
    void setPeakSduBandDuration(int peakSduBandDuration);

    /**
     * @brief Gets Burst Duration parameter
     * @return Value measured in usecs
     */
    int getBurstDuration() const;

    /**
     * @brief Sets Burst Duration parameter
     * @param burstDuration A new value in usecs
     */
    void setBurstDuration(int burstDuration);

    /**
     * @brief Gets Burst Period parameter
     * @return Value measured as a fraction of Burst Period
     */
    int getBurstPeriod() const;

    /**
     * @brief Sets Burst Period parameter
     * @param burstPeriod A new value measured as a fraction of Burst Period
     */
    void setBurstPeriod(int burstPeriod);

    /**
     * @brief Gets Maximum SDU Size parameter
     * @return Value measured in bytes
     */
    int getMaxSduSize() const;

    /**
     * @brief Sets Maximum SDU Size parameter
     * @param maxSdUsize A new value measured in bytes
     */
    void setMaxSduSize(int maxSdUsize);

    /**
     * @brief Gets Undetected Bit Error Rate parameter
     * @return Value in range from 0.0 to 1.0 measured as a probability
     */
    double getUndetectedBitErr() const;

    /**
     * @brief Sets Undetected Bit Error Rate parameter
     * @param undetectedBitErr A new value in range from 0.0 to 1.0 measured as a probability
     */
    void setUndetectedBitErr(double undetectedBitErr);

    /**
     * @brief Gets PDU Dropping Probability parameter
     * @return Value in range from 0.0 to 1.0 measured as a probability
     */
    double getPduDropProbability() const;

    /**
     * @brief Sets PDU Dropping Probability parameter
     * @param pduDropProbability A new value in range from 0.0 to 1.0 measured as a probability
     */
    void setPduDropProbability(double pduDropProbability);

    /**
     * @brief Gets partial delivery flag
     * @return Boolean flag value
     */
    bool isPartialDelivery() const;

    /**
     * @brief Sets partial delivery flag
     * @param partDeliv A new partial delivery flag value
     */
    void setPartialDelivery(bool partDeliv);

    /**
     * @brief Gets incomplete delivery flag
     * @return Boolean flag value
     */
    bool isIncompleteDelivery() const;

    /**
     * @brief Sets incomplete delivery flag
     * @param incompleteDeliv A new incomplete delivery flag value
     */
    void setIncompleteDelivery(bool incompleteDeliv);

    /**
     * @brief Gets in-order delivery flag
     * @return Boolean flag value
     */
    bool isForceOrder() const;

    /**
     * @brief Sets in-order delivery flag
     * @param forceOrder A new in-order delivery flag value
     */
    void setForceOrder(bool forceOrder);

    /**
     * @brief Gets Maximum Allowable Gap in SDUs parameter
     * @return Gap value measured in number of SDUs
     */
    int getMaxAllowGap() const;

    /**
     * @brief Sets Maximum Allowable Gap in SDUs parameter
     * @param maxAllowGap A new gap value measured in number of SDUs
     */
    void setMaxAllowGap(int maxAllowGap);

    /**
     * @brief Gets Delay parameter
     * @return Value measured in usecs
     */
    int getDelay() const;

    /**
     * @brief Sets Delay parameter
     * @param delay A new value measured in usecs
     */
    void setDelay(int delay);

    /**
     * @brief Gets Jitter parameter
     * @return Value measured in usecs
     */
    int getJitter() const;

    /**
     * @brief Sets Jitter parameter
     * @param jitter A new value measured in usecs
     */
    void setJitter(int jitter);

    /**
     * @brief Gets Cost-time parameter
     * @return Value measured in $/ms
     */
    double getCostTime() const;

    /**
     * @brief Sets Cost-time parameter
     * @param costTime A new value measured in $/ms
     */
    void setCostTime(double costTime);

    /**
     * @brief Gets Cost-bits parameter
     * @return Value measured in $/bit
     */
    double getCostBits() const;

    /**
     * @brief Sets Cost-bits parameter
     * @param costBits A new value measured in $/bit
     */
    void setCostBits(double costBits);

    /**
     * @brief Gets Resiliency Factor parameter
     * @param costBits A new value measured in $/bit
     */
    int getResiliencyFactor() const {
        return resiliencyFactor;
    }

    /**
     * @brief Sets Resiliency Factor  parameter
     * @param resiliencyFactor A new value measured in $/bit
     */
    void setResiliencyFactor(int resiliencyFactor) {
        this->resiliencyFactor = resiliencyFactor;
    }


    /**
     * @brief Prints QoSReq information as string
     * @return String of QoSReq textual representation
     */
    std::string info() const;
};

//Free function
/**
 * << operator overload that feeds ostream with QoSReq string representation
 * @param os Resulting ostream
 * @param cube QoSReq class that is being converted to string
 * @return Infotext representing QoSReq
 */
std::ostream& operator<< (std::ostream& os, const QoSReq& cube);

#endif /* QOSREQ_H_ */
