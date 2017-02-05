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

#ifndef __RINA_AEBASE_H_
#define __RINA_AEBASE_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "Common/APNamingInfo.h"
#include "Common/Flow.h"
#include "Common/ExternConsts.h"
#include "Common/QoSReq.h"

typedef std::list<Flow> Flows;
typedef Flows::iterator TFlowsIter;
//Consts

extern const char* PAR_AVGBW;
extern const char* PAR_AVGSDUBW;
extern const char* PAR_PEAKBWDUR;
extern const char* PAR_PEAKSDUBWDUR;
extern const char* PAR_BURSTPERIOD;
extern const char* PAR_BURSTDURATION;
extern const char* PAR_UNDETECTBITERR;
extern const char* PAR_PDUDROPPROBAB;
extern const char* PAR_MAXSDUSIZE;
extern const char* PAR_PARTIALDELIVER;
extern const char* PAR_INCOMPLETEDELIVER;
extern const char* PAR_FORCEORDER;
extern const char* PAR_MAXALLOWGAP;
extern const char* PAR_DELAY;
extern const char* PAR_JITTER;
extern const char* PAR_COSTTIME;
extern const char* PAR_COSTBITS;
extern const char* PAR_ATIME;
extern const char* PAR_RESILIENCYFACTOR;

enum CDAPConnectionState {NIL,
    FLOW_PENDING, CONNECTION_PENDING,
    AUTHENTICATING, ESTABLISHED, RELEASING};

class AEBase : public cSimpleModule
{
  public:
    bool hasFlow(const Flow* flow);

    const APNamingInfo& getApni() const;

    bool operator== (const AEBase& other) {
        return (apni == other.apni);
    }

    const int getAuthType();
    const unsigned long getCdapConId();
    void setCdapConId(unsigned long cdapConId);
    const int getStartInvokeId();
    void setStartInvokeId(int invokeId);
    const std::string& getAuthName() const;
    const std::string& getAuthPassword() const;
    const std::string& getAuthOther() const;
    void changeConStatus(CDAPConnectionState conState);
    CDAPConnectionState getConStatus();
    Flow* getFlowObject() const;
    void setFlowObject(Flow* flowObject);

  protected:
    int startInvokeId;
    unsigned long cdapConId;
    //Flows flows;
    Flow* FlowObject;
    APNamingInfo apni;

    std::string srcApName;
    std::string srcApInstance;
    std::string srcAeName;
    std::string srcAeInstance;

    int authType;
    std::string authName;
    std::string authPassword;
    std::string authOther;
    int maxConRetries;

    QoSReq QoSRequirements;

    CDAPConnectionState connectionState;

    //Getters/Setters
    const std::string& getSrcAeInstance() const;
    void setSrcAeInstance(const std::string& srcAeInstance);
    const std::string& getSrcAeName() const;
    void setSrcAeName(const std::string& srcAeName);
    const std::string& getSrcApInstance() const;
    void setSrcApInstance(const std::string& srcApInstance);
    const std::string& getSrcApName() const;
    void setSrcApName(const std::string& srcApName);
    void setApni(const APNamingInfo& apni);
    void setFlows(const Flows& flows);
    const QoSReq& getQoSRequirements() const;
    void setQoSRequirements(const QoSReq& qoSRequirements);

    void initNamingInfo();
    void initQoSRequirements();

    void insertFlow(Flow& flow);

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:

};

#endif
