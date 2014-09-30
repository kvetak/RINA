//
// Generated file, do not edit! Created by opp_msgc 4.5 from DIF/EFCP/ControlPDU.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "ControlPDU_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

Register_Class(ControlPDU);

ControlPDU::ControlPDU(const char *name, int kind) : ::PDU(name,kind)
{
    this->controlSeqNum_var = 0;
}

ControlPDU::ControlPDU(const ControlPDU& other) : ::PDU(other)
{
    copy(other);
}

ControlPDU::~ControlPDU()
{
}

ControlPDU& ControlPDU::operator=(const ControlPDU& other)
{
    if (this==&other) return *this;
    ::PDU::operator=(other);
    copy(other);
    return *this;
}

void ControlPDU::copy(const ControlPDU& other)
{
    this->controlSeqNum_var = other.controlSeqNum_var;
}

void ControlPDU::parsimPack(cCommBuffer *b)
{
    ::PDU::parsimPack(b);
    doPacking(b,this->controlSeqNum_var);
}

void ControlPDU::parsimUnpack(cCommBuffer *b)
{
    ::PDU::parsimUnpack(b);
    doUnpacking(b,this->controlSeqNum_var);
}

unsigned int ControlPDU::getControlSeqNum() const
{
    return controlSeqNum_var;
}

void ControlPDU::setControlSeqNum(unsigned int controlSeqNum)
{
    this->controlSeqNum_var = controlSeqNum;
}

class ControlPDUDescriptor : public cClassDescriptor
{
  public:
    ControlPDUDescriptor();
    virtual ~ControlPDUDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(ControlPDUDescriptor);

ControlPDUDescriptor::ControlPDUDescriptor() : cClassDescriptor("ControlPDU", "PDU")
{
}

ControlPDUDescriptor::~ControlPDUDescriptor()
{
}

bool ControlPDUDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<ControlPDU *>(obj)!=NULL;
}

const char *ControlPDUDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int ControlPDUDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int ControlPDUDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *ControlPDUDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "controlSeqNum",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int ControlPDUDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "controlSeqNum")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *ControlPDUDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *ControlPDUDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int ControlPDUDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    ControlPDU *pp = (ControlPDU *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string ControlPDUDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    ControlPDU *pp = (ControlPDU *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getControlSeqNum());
        default: return "";
    }
}

bool ControlPDUDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    ControlPDU *pp = (ControlPDU *)object; (void)pp;
    switch (field) {
        case 0: pp->setControlSeqNum(string2ulong(value)); return true;
        default: return false;
    }
}

const char *ControlPDUDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *ControlPDUDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    ControlPDU *pp = (ControlPDU *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(FlowControlPDU);

FlowControlPDU::FlowControlPDU(const char *name, int kind) : ::ControlPDU(name,kind)
{
    this->rateLen_var = 0;
    this->timeUnit_var = 0;
    this->myLeftWinEdge_var = 0;
    this->myRightWinEdge_var = 0;
    this->myRcvRate_var = 0;
}

FlowControlPDU::FlowControlPDU(const FlowControlPDU& other) : ::ControlPDU(other)
{
    copy(other);
}

FlowControlPDU::~FlowControlPDU()
{
}

FlowControlPDU& FlowControlPDU::operator=(const FlowControlPDU& other)
{
    if (this==&other) return *this;
    ::ControlPDU::operator=(other);
    copy(other);
    return *this;
}

void FlowControlPDU::copy(const FlowControlPDU& other)
{
    this->rateLen_var = other.rateLen_var;
    this->timeUnit_var = other.timeUnit_var;
    this->myLeftWinEdge_var = other.myLeftWinEdge_var;
    this->myRightWinEdge_var = other.myRightWinEdge_var;
    this->myRcvRate_var = other.myRcvRate_var;
}

void FlowControlPDU::parsimPack(cCommBuffer *b)
{
    ::ControlPDU::parsimPack(b);
    doPacking(b,this->rateLen_var);
    doPacking(b,this->timeUnit_var);
    doPacking(b,this->myLeftWinEdge_var);
    doPacking(b,this->myRightWinEdge_var);
    doPacking(b,this->myRcvRate_var);
}

void FlowControlPDU::parsimUnpack(cCommBuffer *b)
{
    ::ControlPDU::parsimUnpack(b);
    doUnpacking(b,this->rateLen_var);
    doUnpacking(b,this->timeUnit_var);
    doUnpacking(b,this->myLeftWinEdge_var);
    doUnpacking(b,this->myRightWinEdge_var);
    doUnpacking(b,this->myRcvRate_var);
}

unsigned int FlowControlPDU::getRateLen() const
{
    return rateLen_var;
}

void FlowControlPDU::setRateLen(unsigned int rateLen)
{
    this->rateLen_var = rateLen;
}

unsigned int FlowControlPDU::getTimeUnit() const
{
    return timeUnit_var;
}

void FlowControlPDU::setTimeUnit(unsigned int timeUnit)
{
    this->timeUnit_var = timeUnit;
}

unsigned int FlowControlPDU::getMyLeftWinEdge() const
{
    return myLeftWinEdge_var;
}

void FlowControlPDU::setMyLeftWinEdge(unsigned int myLeftWinEdge)
{
    this->myLeftWinEdge_var = myLeftWinEdge;
}

unsigned int FlowControlPDU::getMyRightWinEdge() const
{
    return myRightWinEdge_var;
}

void FlowControlPDU::setMyRightWinEdge(unsigned int myRightWinEdge)
{
    this->myRightWinEdge_var = myRightWinEdge;
}

unsigned int FlowControlPDU::getMyRcvRate() const
{
    return myRcvRate_var;
}

void FlowControlPDU::setMyRcvRate(unsigned int myRcvRate)
{
    this->myRcvRate_var = myRcvRate;
}

class FlowControlPDUDescriptor : public cClassDescriptor
{
  public:
    FlowControlPDUDescriptor();
    virtual ~FlowControlPDUDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(FlowControlPDUDescriptor);

FlowControlPDUDescriptor::FlowControlPDUDescriptor() : cClassDescriptor("FlowControlPDU", "ControlPDU")
{
}

FlowControlPDUDescriptor::~FlowControlPDUDescriptor()
{
}

bool FlowControlPDUDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<FlowControlPDU *>(obj)!=NULL;
}

const char *FlowControlPDUDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int FlowControlPDUDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int FlowControlPDUDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *FlowControlPDUDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "rateLen",
        "timeUnit",
        "myLeftWinEdge",
        "myRightWinEdge",
        "myRcvRate",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int FlowControlPDUDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "rateLen")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "timeUnit")==0) return base+1;
    if (fieldName[0]=='m' && strcmp(fieldName, "myLeftWinEdge")==0) return base+2;
    if (fieldName[0]=='m' && strcmp(fieldName, "myRightWinEdge")==0) return base+3;
    if (fieldName[0]=='m' && strcmp(fieldName, "myRcvRate")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *FlowControlPDUDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
        "unsigned int",
        "unsigned int",
        "unsigned int",
        "unsigned int",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *FlowControlPDUDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int FlowControlPDUDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    FlowControlPDU *pp = (FlowControlPDU *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string FlowControlPDUDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    FlowControlPDU *pp = (FlowControlPDU *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getRateLen());
        case 1: return ulong2string(pp->getTimeUnit());
        case 2: return ulong2string(pp->getMyLeftWinEdge());
        case 3: return ulong2string(pp->getMyRightWinEdge());
        case 4: return ulong2string(pp->getMyRcvRate());
        default: return "";
    }
}

bool FlowControlPDUDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    FlowControlPDU *pp = (FlowControlPDU *)object; (void)pp;
    switch (field) {
        case 0: pp->setRateLen(string2ulong(value)); return true;
        case 1: pp->setTimeUnit(string2ulong(value)); return true;
        case 2: pp->setMyLeftWinEdge(string2ulong(value)); return true;
        case 3: pp->setMyRightWinEdge(string2ulong(value)); return true;
        case 4: pp->setMyRcvRate(string2ulong(value)); return true;
        default: return false;
    }
}

const char *FlowControlPDUDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *FlowControlPDUDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    FlowControlPDU *pp = (FlowControlPDU *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(NAckPDU);

NAckPDU::NAckPDU(const char *name, int kind) : ::ControlPDU(name,kind)
{
    this->setType(-1);

    this->ackNackSeqNum_var = 0;
}

NAckPDU::NAckPDU(const NAckPDU& other) : ::ControlPDU(other)
{
    copy(other);
}

NAckPDU::~NAckPDU()
{
}

NAckPDU& NAckPDU::operator=(const NAckPDU& other)
{
    if (this==&other) return *this;
    ::ControlPDU::operator=(other);
    copy(other);
    return *this;
}

void NAckPDU::copy(const NAckPDU& other)
{
    this->ackNackSeqNum_var = other.ackNackSeqNum_var;
}

void NAckPDU::parsimPack(cCommBuffer *b)
{
    ::ControlPDU::parsimPack(b);
    doPacking(b,this->ackNackSeqNum_var);
}

void NAckPDU::parsimUnpack(cCommBuffer *b)
{
    ::ControlPDU::parsimUnpack(b);
    doUnpacking(b,this->ackNackSeqNum_var);
}

unsigned int NAckPDU::getAckNackSeqNum() const
{
    return ackNackSeqNum_var;
}

void NAckPDU::setAckNackSeqNum(unsigned int ackNackSeqNum)
{
    this->ackNackSeqNum_var = ackNackSeqNum;
}

class NAckPDUDescriptor : public cClassDescriptor
{
  public:
    NAckPDUDescriptor();
    virtual ~NAckPDUDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(NAckPDUDescriptor);

NAckPDUDescriptor::NAckPDUDescriptor() : cClassDescriptor("NAckPDU", "ControlPDU")
{
}

NAckPDUDescriptor::~NAckPDUDescriptor()
{
}

bool NAckPDUDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<NAckPDU *>(obj)!=NULL;
}

const char *NAckPDUDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int NAckPDUDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int NAckPDUDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *NAckPDUDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "ackNackSeqNum",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int NAckPDUDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='a' && strcmp(fieldName, "ackNackSeqNum")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *NAckPDUDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *NAckPDUDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int NAckPDUDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    NAckPDU *pp = (NAckPDU *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string NAckPDUDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    NAckPDU *pp = (NAckPDU *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getAckNackSeqNum());
        default: return "";
    }
}

bool NAckPDUDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    NAckPDU *pp = (NAckPDU *)object; (void)pp;
    switch (field) {
        case 0: pp->setAckNackSeqNum(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NAckPDUDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *NAckPDUDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    NAckPDU *pp = (NAckPDU *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(AckOnlyPDU);

AckOnlyPDU::AckOnlyPDU(const char *name, int kind) : ::NAckPDU(name,kind)
{
    this->setType(ACK_ONLY_PDU);
}

AckOnlyPDU::AckOnlyPDU(const AckOnlyPDU& other) : ::NAckPDU(other)
{
    copy(other);
}

AckOnlyPDU::~AckOnlyPDU()
{
}

AckOnlyPDU& AckOnlyPDU::operator=(const AckOnlyPDU& other)
{
    if (this==&other) return *this;
    ::NAckPDU::operator=(other);
    copy(other);
    return *this;
}

void AckOnlyPDU::copy(const AckOnlyPDU& other)
{
}

void AckOnlyPDU::parsimPack(cCommBuffer *b)
{
    ::NAckPDU::parsimPack(b);
}

void AckOnlyPDU::parsimUnpack(cCommBuffer *b)
{
    ::NAckPDU::parsimUnpack(b);
}

class AckOnlyPDUDescriptor : public cClassDescriptor
{
  public:
    AckOnlyPDUDescriptor();
    virtual ~AckOnlyPDUDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(AckOnlyPDUDescriptor);

AckOnlyPDUDescriptor::AckOnlyPDUDescriptor() : cClassDescriptor("AckOnlyPDU", "NAckPDU")
{
}

AckOnlyPDUDescriptor::~AckOnlyPDUDescriptor()
{
}

bool AckOnlyPDUDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<AckOnlyPDU *>(obj)!=NULL;
}

const char *AckOnlyPDUDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int AckOnlyPDUDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int AckOnlyPDUDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *AckOnlyPDUDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int AckOnlyPDUDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *AckOnlyPDUDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *AckOnlyPDUDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int AckOnlyPDUDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    AckOnlyPDU *pp = (AckOnlyPDU *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string AckOnlyPDUDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    AckOnlyPDU *pp = (AckOnlyPDU *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool AckOnlyPDUDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    AckOnlyPDU *pp = (AckOnlyPDU *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *AckOnlyPDUDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *AckOnlyPDUDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    AckOnlyPDU *pp = (AckOnlyPDU *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(NackOnlyPDU);

NackOnlyPDU::NackOnlyPDU(const char *name, int kind) : ::NAckPDU(name,kind)
{
    this->setType(NACK_ONLY_PDU);
}

NackOnlyPDU::NackOnlyPDU(const NackOnlyPDU& other) : ::NAckPDU(other)
{
    copy(other);
}

NackOnlyPDU::~NackOnlyPDU()
{
}

NackOnlyPDU& NackOnlyPDU::operator=(const NackOnlyPDU& other)
{
    if (this==&other) return *this;
    ::NAckPDU::operator=(other);
    copy(other);
    return *this;
}

void NackOnlyPDU::copy(const NackOnlyPDU& other)
{
}

void NackOnlyPDU::parsimPack(cCommBuffer *b)
{
    ::NAckPDU::parsimPack(b);
}

void NackOnlyPDU::parsimUnpack(cCommBuffer *b)
{
    ::NAckPDU::parsimUnpack(b);
}

class NackOnlyPDUDescriptor : public cClassDescriptor
{
  public:
    NackOnlyPDUDescriptor();
    virtual ~NackOnlyPDUDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(NackOnlyPDUDescriptor);

NackOnlyPDUDescriptor::NackOnlyPDUDescriptor() : cClassDescriptor("NackOnlyPDU", "NAckPDU")
{
}

NackOnlyPDUDescriptor::~NackOnlyPDUDescriptor()
{
}

bool NackOnlyPDUDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<NackOnlyPDU *>(obj)!=NULL;
}

const char *NackOnlyPDUDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int NackOnlyPDUDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int NackOnlyPDUDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *NackOnlyPDUDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int NackOnlyPDUDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *NackOnlyPDUDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *NackOnlyPDUDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int NackOnlyPDUDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    NackOnlyPDU *pp = (NackOnlyPDU *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string NackOnlyPDUDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    NackOnlyPDU *pp = (NackOnlyPDU *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool NackOnlyPDUDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    NackOnlyPDU *pp = (NackOnlyPDU *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *NackOnlyPDUDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *NackOnlyPDUDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    NackOnlyPDU *pp = (NackOnlyPDU *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(NAck);

NAck::NAck(const char *name, int kind) : ::NAckPDU(name,kind)
{
}

NAck::NAck(const NAck& other) : ::NAckPDU(other)
{
    copy(other);
}

NAck::~NAck()
{
}

NAck& NAck::operator=(const NAck& other)
{
    if (this==&other) return *this;
    ::NAckPDU::operator=(other);
    copy(other);
    return *this;
}

void NAck::copy(const NAck& other)
{
}

void NAck::parsimPack(cCommBuffer *b)
{
    ::NAckPDU::parsimPack(b);
}

void NAck::parsimUnpack(cCommBuffer *b)
{
    ::NAckPDU::parsimUnpack(b);
}

class NAckDescriptor : public cClassDescriptor
{
  public:
    NAckDescriptor();
    virtual ~NAckDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(NAckDescriptor);

NAckDescriptor::NAckDescriptor() : cClassDescriptor("NAck", "NAckPDU")
{
}

NAckDescriptor::~NAckDescriptor()
{
}

bool NAckDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<NAck *>(obj)!=NULL;
}

const char *NAckDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int NAckDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int NAckDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *NAckDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int NAckDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *NAckDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *NAckDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int NAckDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    NAck *pp = (NAck *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string NAckDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    NAck *pp = (NAck *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool NAckDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    NAck *pp = (NAck *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *NAckDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *NAckDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    NAck *pp = (NAck *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(NAckFlow);

NAckFlow::NAckFlow(const char *name, int kind) : ::FlowControlPDU(name,kind)
{
}

NAckFlow::NAckFlow(const NAckFlow& other) : ::FlowControlPDU(other)
{
    copy(other);
}

NAckFlow::~NAckFlow()
{
}

NAckFlow& NAckFlow::operator=(const NAckFlow& other)
{
    if (this==&other) return *this;
    ::FlowControlPDU::operator=(other);
    copy(other);
    return *this;
}

void NAckFlow::copy(const NAckFlow& other)
{
}

void NAckFlow::parsimPack(cCommBuffer *b)
{
    ::FlowControlPDU::parsimPack(b);
}

void NAckFlow::parsimUnpack(cCommBuffer *b)
{
    ::FlowControlPDU::parsimUnpack(b);
}

class NAckFlowDescriptor : public cClassDescriptor
{
  public:
    NAckFlowDescriptor();
    virtual ~NAckFlowDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(NAckFlowDescriptor);

NAckFlowDescriptor::NAckFlowDescriptor() : cClassDescriptor("NAckFlow", "FlowControlPDU")
{
}

NAckFlowDescriptor::~NAckFlowDescriptor()
{
}

bool NAckFlowDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<NAckFlow *>(obj)!=NULL;
}

const char *NAckFlowDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int NAckFlowDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int NAckFlowDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *NAckFlowDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int NAckFlowDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *NAckFlowDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *NAckFlowDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int NAckFlowDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    NAckFlow *pp = (NAckFlow *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string NAckFlowDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    NAckFlow *pp = (NAckFlow *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool NAckFlowDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    NAckFlow *pp = (NAckFlow *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *NAckFlowDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *NAckFlowDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    NAckFlow *pp = (NAckFlow *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(AckFlowPDU);

AckFlowPDU::AckFlowPDU(const char *name, int kind) : ::NAckFlow(name,kind)
{
    this->setType(ACK_FLOW_PDU);
}

AckFlowPDU::AckFlowPDU(const AckFlowPDU& other) : ::NAckFlow(other)
{
    copy(other);
}

AckFlowPDU::~AckFlowPDU()
{
}

AckFlowPDU& AckFlowPDU::operator=(const AckFlowPDU& other)
{
    if (this==&other) return *this;
    ::NAckFlow::operator=(other);
    copy(other);
    return *this;
}

void AckFlowPDU::copy(const AckFlowPDU& other)
{
}

void AckFlowPDU::parsimPack(cCommBuffer *b)
{
    ::NAckFlow::parsimPack(b);
}

void AckFlowPDU::parsimUnpack(cCommBuffer *b)
{
    ::NAckFlow::parsimUnpack(b);
}

class AckFlowPDUDescriptor : public cClassDescriptor
{
  public:
    AckFlowPDUDescriptor();
    virtual ~AckFlowPDUDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(AckFlowPDUDescriptor);

AckFlowPDUDescriptor::AckFlowPDUDescriptor() : cClassDescriptor("AckFlowPDU", "NAckFlow")
{
}

AckFlowPDUDescriptor::~AckFlowPDUDescriptor()
{
}

bool AckFlowPDUDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<AckFlowPDU *>(obj)!=NULL;
}

const char *AckFlowPDUDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int AckFlowPDUDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int AckFlowPDUDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *AckFlowPDUDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int AckFlowPDUDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *AckFlowPDUDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *AckFlowPDUDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int AckFlowPDUDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    AckFlowPDU *pp = (AckFlowPDU *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string AckFlowPDUDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    AckFlowPDU *pp = (AckFlowPDU *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool AckFlowPDUDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    AckFlowPDU *pp = (AckFlowPDU *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *AckFlowPDUDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *AckFlowPDUDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    AckFlowPDU *pp = (AckFlowPDU *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(NackFlowPDU);

NackFlowPDU::NackFlowPDU(const char *name, int kind) : ::NAckFlow(name,kind)
{
    this->setType(NACK_FLOW_PDU);
}

NackFlowPDU::NackFlowPDU(const NackFlowPDU& other) : ::NAckFlow(other)
{
    copy(other);
}

NackFlowPDU::~NackFlowPDU()
{
}

NackFlowPDU& NackFlowPDU::operator=(const NackFlowPDU& other)
{
    if (this==&other) return *this;
    ::NAckFlow::operator=(other);
    copy(other);
    return *this;
}

void NackFlowPDU::copy(const NackFlowPDU& other)
{
}

void NackFlowPDU::parsimPack(cCommBuffer *b)
{
    ::NAckFlow::parsimPack(b);
}

void NackFlowPDU::parsimUnpack(cCommBuffer *b)
{
    ::NAckFlow::parsimUnpack(b);
}

class NackFlowPDUDescriptor : public cClassDescriptor
{
  public:
    NackFlowPDUDescriptor();
    virtual ~NackFlowPDUDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(NackFlowPDUDescriptor);

NackFlowPDUDescriptor::NackFlowPDUDescriptor() : cClassDescriptor("NackFlowPDU", "NAckFlow")
{
}

NackFlowPDUDescriptor::~NackFlowPDUDescriptor()
{
}

bool NackFlowPDUDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<NackFlowPDU *>(obj)!=NULL;
}

const char *NackFlowPDUDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int NackFlowPDUDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int NackFlowPDUDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *NackFlowPDUDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int NackFlowPDUDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *NackFlowPDUDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *NackFlowPDUDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int NackFlowPDUDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    NackFlowPDU *pp = (NackFlowPDU *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string NackFlowPDUDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    NackFlowPDU *pp = (NackFlowPDU *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool NackFlowPDUDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    NackFlowPDU *pp = (NackFlowPDU *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *NackFlowPDUDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *NackFlowPDUDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    NackFlowPDU *pp = (NackFlowPDU *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(FlowControlOnlyPDU);

FlowControlOnlyPDU::FlowControlOnlyPDU(const char *name, int kind) : ::FlowControlPDU(name,kind)
{
    this->setType(FLOW_ONLY_PDU);
}

FlowControlOnlyPDU::FlowControlOnlyPDU(const FlowControlOnlyPDU& other) : ::FlowControlPDU(other)
{
    copy(other);
}

FlowControlOnlyPDU::~FlowControlOnlyPDU()
{
}

FlowControlOnlyPDU& FlowControlOnlyPDU::operator=(const FlowControlOnlyPDU& other)
{
    if (this==&other) return *this;
    ::FlowControlPDU::operator=(other);
    copy(other);
    return *this;
}

void FlowControlOnlyPDU::copy(const FlowControlOnlyPDU& other)
{
}

void FlowControlOnlyPDU::parsimPack(cCommBuffer *b)
{
    ::FlowControlPDU::parsimPack(b);
}

void FlowControlOnlyPDU::parsimUnpack(cCommBuffer *b)
{
    ::FlowControlPDU::parsimUnpack(b);
}

class FlowControlOnlyPDUDescriptor : public cClassDescriptor
{
  public:
    FlowControlOnlyPDUDescriptor();
    virtual ~FlowControlOnlyPDUDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(FlowControlOnlyPDUDescriptor);

FlowControlOnlyPDUDescriptor::FlowControlOnlyPDUDescriptor() : cClassDescriptor("FlowControlOnlyPDU", "FlowControlPDU")
{
}

FlowControlOnlyPDUDescriptor::~FlowControlOnlyPDUDescriptor()
{
}

bool FlowControlOnlyPDUDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<FlowControlOnlyPDU *>(obj)!=NULL;
}

const char *FlowControlOnlyPDUDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int FlowControlOnlyPDUDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int FlowControlOnlyPDUDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *FlowControlOnlyPDUDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int FlowControlOnlyPDUDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *FlowControlOnlyPDUDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *FlowControlOnlyPDUDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int FlowControlOnlyPDUDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    FlowControlOnlyPDU *pp = (FlowControlOnlyPDU *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string FlowControlOnlyPDUDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    FlowControlOnlyPDU *pp = (FlowControlOnlyPDU *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool FlowControlOnlyPDUDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    FlowControlOnlyPDU *pp = (FlowControlOnlyPDU *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *FlowControlOnlyPDUDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *FlowControlOnlyPDUDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    FlowControlOnlyPDU *pp = (FlowControlOnlyPDU *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(SelectiveNAckFlow);

SelectiveNAckFlow::SelectiveNAckFlow(const char *name, int kind) : ::FlowControlPDU(name,kind)
{
    this->newLeftWinEdge_var = 0;
    this->newRightWinEdge_var = 0;
    this->nackListLen_var = 0;
    nackList_arraysize = 0;
    this->nackList_var = 0;
}

SelectiveNAckFlow::SelectiveNAckFlow(const SelectiveNAckFlow& other) : ::FlowControlPDU(other)
{
    nackList_arraysize = 0;
    this->nackList_var = 0;
    copy(other);
}

SelectiveNAckFlow::~SelectiveNAckFlow()
{
    delete [] nackList_var;
}

SelectiveNAckFlow& SelectiveNAckFlow::operator=(const SelectiveNAckFlow& other)
{
    if (this==&other) return *this;
    ::FlowControlPDU::operator=(other);
    copy(other);
    return *this;
}

void SelectiveNAckFlow::copy(const SelectiveNAckFlow& other)
{
    this->newLeftWinEdge_var = other.newLeftWinEdge_var;
    this->newRightWinEdge_var = other.newRightWinEdge_var;
    this->nackListLen_var = other.nackListLen_var;
    delete [] this->nackList_var;
    this->nackList_var = (other.nackList_arraysize==0) ? NULL : new unsigned int[other.nackList_arraysize];
    nackList_arraysize = other.nackList_arraysize;
    for (unsigned int i=0; i<nackList_arraysize; i++)
        this->nackList_var[i] = other.nackList_var[i];
}

void SelectiveNAckFlow::parsimPack(cCommBuffer *b)
{
    ::FlowControlPDU::parsimPack(b);
    doPacking(b,this->newLeftWinEdge_var);
    doPacking(b,this->newRightWinEdge_var);
    doPacking(b,this->nackListLen_var);
    b->pack(nackList_arraysize);
    doPacking(b,this->nackList_var,nackList_arraysize);
}

void SelectiveNAckFlow::parsimUnpack(cCommBuffer *b)
{
    ::FlowControlPDU::parsimUnpack(b);
    doUnpacking(b,this->newLeftWinEdge_var);
    doUnpacking(b,this->newRightWinEdge_var);
    doUnpacking(b,this->nackListLen_var);
    delete [] this->nackList_var;
    b->unpack(nackList_arraysize);
    if (nackList_arraysize==0) {
        this->nackList_var = 0;
    } else {
        this->nackList_var = new unsigned int[nackList_arraysize];
        doUnpacking(b,this->nackList_var,nackList_arraysize);
    }
}

unsigned int SelectiveNAckFlow::getNewLeftWinEdge() const
{
    return newLeftWinEdge_var;
}

void SelectiveNAckFlow::setNewLeftWinEdge(unsigned int newLeftWinEdge)
{
    this->newLeftWinEdge_var = newLeftWinEdge;
}

unsigned int SelectiveNAckFlow::getNewRightWinEdge() const
{
    return newRightWinEdge_var;
}

void SelectiveNAckFlow::setNewRightWinEdge(unsigned int newRightWinEdge)
{
    this->newRightWinEdge_var = newRightWinEdge;
}

unsigned int SelectiveNAckFlow::getNackListLen() const
{
    return nackListLen_var;
}

void SelectiveNAckFlow::setNackListLen(unsigned int nackListLen)
{
    this->nackListLen_var = nackListLen;
}

void SelectiveNAckFlow::setNackListArraySize(unsigned int size)
{
    unsigned int *nackList_var2 = (size==0) ? NULL : new unsigned int[size];
    unsigned int sz = nackList_arraysize < size ? nackList_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        nackList_var2[i] = this->nackList_var[i];
    for (unsigned int i=sz; i<size; i++)
        nackList_var2[i] = 0;
    nackList_arraysize = size;
    delete [] this->nackList_var;
    this->nackList_var = nackList_var2;
}

unsigned int SelectiveNAckFlow::getNackListArraySize() const
{
    return nackList_arraysize;
}

unsigned int SelectiveNAckFlow::getNackList(unsigned int k) const
{
    if (k>=nackList_arraysize) throw cRuntimeError("Array of size %d indexed by %d", nackList_arraysize, k);
    return nackList_var[k];
}

void SelectiveNAckFlow::setNackList(unsigned int k, unsigned int nackList)
{
    if (k>=nackList_arraysize) throw cRuntimeError("Array of size %d indexed by %d", nackList_arraysize, k);
    this->nackList_var[k] = nackList;
}

class SelectiveNAckFlowDescriptor : public cClassDescriptor
{
  public:
    SelectiveNAckFlowDescriptor();
    virtual ~SelectiveNAckFlowDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(SelectiveNAckFlowDescriptor);

SelectiveNAckFlowDescriptor::SelectiveNAckFlowDescriptor() : cClassDescriptor("SelectiveNAckFlow", "FlowControlPDU")
{
}

SelectiveNAckFlowDescriptor::~SelectiveNAckFlowDescriptor()
{
}

bool SelectiveNAckFlowDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<SelectiveNAckFlow *>(obj)!=NULL;
}

const char *SelectiveNAckFlowDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int SelectiveNAckFlowDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int SelectiveNAckFlowDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *SelectiveNAckFlowDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "newLeftWinEdge",
        "newRightWinEdge",
        "nackListLen",
        "nackList",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int SelectiveNAckFlowDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "newLeftWinEdge")==0) return base+0;
    if (fieldName[0]=='n' && strcmp(fieldName, "newRightWinEdge")==0) return base+1;
    if (fieldName[0]=='n' && strcmp(fieldName, "nackListLen")==0) return base+2;
    if (fieldName[0]=='n' && strcmp(fieldName, "nackList")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *SelectiveNAckFlowDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
        "unsigned int",
        "unsigned int",
        "unsigned int",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *SelectiveNAckFlowDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int SelectiveNAckFlowDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    SelectiveNAckFlow *pp = (SelectiveNAckFlow *)object; (void)pp;
    switch (field) {
        case 3: return pp->getNackListArraySize();
        default: return 0;
    }
}

std::string SelectiveNAckFlowDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    SelectiveNAckFlow *pp = (SelectiveNAckFlow *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getNewLeftWinEdge());
        case 1: return ulong2string(pp->getNewRightWinEdge());
        case 2: return ulong2string(pp->getNackListLen());
        case 3: return ulong2string(pp->getNackList(i));
        default: return "";
    }
}

bool SelectiveNAckFlowDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    SelectiveNAckFlow *pp = (SelectiveNAckFlow *)object; (void)pp;
    switch (field) {
        case 0: pp->setNewLeftWinEdge(string2ulong(value)); return true;
        case 1: pp->setNewRightWinEdge(string2ulong(value)); return true;
        case 2: pp->setNackListLen(string2ulong(value)); return true;
        case 3: pp->setNackList(i,string2ulong(value)); return true;
        default: return false;
    }
}

const char *SelectiveNAckFlowDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *SelectiveNAckFlowDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    SelectiveNAckFlow *pp = (SelectiveNAckFlow *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(SelectiveAckFlowPDU);

SelectiveAckFlowPDU::SelectiveAckFlowPDU(const char *name, int kind) : ::SelectiveNAckFlow(name,kind)
{
    this->setType(SELECT_ACK_FLOW_PDU);
}

SelectiveAckFlowPDU::SelectiveAckFlowPDU(const SelectiveAckFlowPDU& other) : ::SelectiveNAckFlow(other)
{
    copy(other);
}

SelectiveAckFlowPDU::~SelectiveAckFlowPDU()
{
}

SelectiveAckFlowPDU& SelectiveAckFlowPDU::operator=(const SelectiveAckFlowPDU& other)
{
    if (this==&other) return *this;
    ::SelectiveNAckFlow::operator=(other);
    copy(other);
    return *this;
}

void SelectiveAckFlowPDU::copy(const SelectiveAckFlowPDU& other)
{
}

void SelectiveAckFlowPDU::parsimPack(cCommBuffer *b)
{
    ::SelectiveNAckFlow::parsimPack(b);
}

void SelectiveAckFlowPDU::parsimUnpack(cCommBuffer *b)
{
    ::SelectiveNAckFlow::parsimUnpack(b);
}

class SelectiveAckFlowPDUDescriptor : public cClassDescriptor
{
  public:
    SelectiveAckFlowPDUDescriptor();
    virtual ~SelectiveAckFlowPDUDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(SelectiveAckFlowPDUDescriptor);

SelectiveAckFlowPDUDescriptor::SelectiveAckFlowPDUDescriptor() : cClassDescriptor("SelectiveAckFlowPDU", "SelectiveNAckFlow")
{
}

SelectiveAckFlowPDUDescriptor::~SelectiveAckFlowPDUDescriptor()
{
}

bool SelectiveAckFlowPDUDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<SelectiveAckFlowPDU *>(obj)!=NULL;
}

const char *SelectiveAckFlowPDUDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int SelectiveAckFlowPDUDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int SelectiveAckFlowPDUDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *SelectiveAckFlowPDUDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int SelectiveAckFlowPDUDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *SelectiveAckFlowPDUDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *SelectiveAckFlowPDUDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int SelectiveAckFlowPDUDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    SelectiveAckFlowPDU *pp = (SelectiveAckFlowPDU *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string SelectiveAckFlowPDUDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    SelectiveAckFlowPDU *pp = (SelectiveAckFlowPDU *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool SelectiveAckFlowPDUDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    SelectiveAckFlowPDU *pp = (SelectiveAckFlowPDU *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *SelectiveAckFlowPDUDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *SelectiveAckFlowPDUDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    SelectiveAckFlowPDU *pp = (SelectiveAckFlowPDU *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(SelectiveNackFlowPDU);

SelectiveNackFlowPDU::SelectiveNackFlowPDU(const char *name, int kind) : ::SelectiveNAckFlow(name,kind)
{
    this->setType(SELECT_NACK_FLOW_PDU);
}

SelectiveNackFlowPDU::SelectiveNackFlowPDU(const SelectiveNackFlowPDU& other) : ::SelectiveNAckFlow(other)
{
    copy(other);
}

SelectiveNackFlowPDU::~SelectiveNackFlowPDU()
{
}

SelectiveNackFlowPDU& SelectiveNackFlowPDU::operator=(const SelectiveNackFlowPDU& other)
{
    if (this==&other) return *this;
    ::SelectiveNAckFlow::operator=(other);
    copy(other);
    return *this;
}

void SelectiveNackFlowPDU::copy(const SelectiveNackFlowPDU& other)
{
}

void SelectiveNackFlowPDU::parsimPack(cCommBuffer *b)
{
    ::SelectiveNAckFlow::parsimPack(b);
}

void SelectiveNackFlowPDU::parsimUnpack(cCommBuffer *b)
{
    ::SelectiveNAckFlow::parsimUnpack(b);
}

class SelectiveNackFlowPDUDescriptor : public cClassDescriptor
{
  public:
    SelectiveNackFlowPDUDescriptor();
    virtual ~SelectiveNackFlowPDUDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(SelectiveNackFlowPDUDescriptor);

SelectiveNackFlowPDUDescriptor::SelectiveNackFlowPDUDescriptor() : cClassDescriptor("SelectiveNackFlowPDU", "SelectiveNAckFlow")
{
}

SelectiveNackFlowPDUDescriptor::~SelectiveNackFlowPDUDescriptor()
{
}

bool SelectiveNackFlowPDUDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<SelectiveNackFlowPDU *>(obj)!=NULL;
}

const char *SelectiveNackFlowPDUDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int SelectiveNackFlowPDUDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int SelectiveNackFlowPDUDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *SelectiveNackFlowPDUDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int SelectiveNackFlowPDUDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *SelectiveNackFlowPDUDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *SelectiveNackFlowPDUDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int SelectiveNackFlowPDUDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    SelectiveNackFlowPDU *pp = (SelectiveNackFlowPDU *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string SelectiveNackFlowPDUDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    SelectiveNackFlowPDU *pp = (SelectiveNackFlowPDU *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool SelectiveNackFlowPDUDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    SelectiveNackFlowPDU *pp = (SelectiveNackFlowPDU *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *SelectiveNackFlowPDUDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *SelectiveNackFlowPDUDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    SelectiveNackFlowPDU *pp = (SelectiveNackFlowPDU *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(SelectiveAckPDU);

SelectiveAckPDU::SelectiveAckPDU(const char *name, int kind) : ::SelectiveNAckFlow(name,kind)
{
    this->setType(SELECT_ACK_PDU);
}

SelectiveAckPDU::SelectiveAckPDU(const SelectiveAckPDU& other) : ::SelectiveNAckFlow(other)
{
    copy(other);
}

SelectiveAckPDU::~SelectiveAckPDU()
{
}

SelectiveAckPDU& SelectiveAckPDU::operator=(const SelectiveAckPDU& other)
{
    if (this==&other) return *this;
    ::SelectiveNAckFlow::operator=(other);
    copy(other);
    return *this;
}

void SelectiveAckPDU::copy(const SelectiveAckPDU& other)
{
}

void SelectiveAckPDU::parsimPack(cCommBuffer *b)
{
    ::SelectiveNAckFlow::parsimPack(b);
}

void SelectiveAckPDU::parsimUnpack(cCommBuffer *b)
{
    ::SelectiveNAckFlow::parsimUnpack(b);
}

class SelectiveAckPDUDescriptor : public cClassDescriptor
{
  public:
    SelectiveAckPDUDescriptor();
    virtual ~SelectiveAckPDUDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(SelectiveAckPDUDescriptor);

SelectiveAckPDUDescriptor::SelectiveAckPDUDescriptor() : cClassDescriptor("SelectiveAckPDU", "SelectiveNAckFlow")
{
}

SelectiveAckPDUDescriptor::~SelectiveAckPDUDescriptor()
{
}

bool SelectiveAckPDUDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<SelectiveAckPDU *>(obj)!=NULL;
}

const char *SelectiveAckPDUDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int SelectiveAckPDUDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int SelectiveAckPDUDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *SelectiveAckPDUDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int SelectiveAckPDUDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *SelectiveAckPDUDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *SelectiveAckPDUDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int SelectiveAckPDUDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    SelectiveAckPDU *pp = (SelectiveAckPDU *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string SelectiveAckPDUDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    SelectiveAckPDU *pp = (SelectiveAckPDU *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool SelectiveAckPDUDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    SelectiveAckPDU *pp = (SelectiveAckPDU *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *SelectiveAckPDUDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *SelectiveAckPDUDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    SelectiveAckPDU *pp = (SelectiveAckPDU *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(SelectiveNackPDU);

SelectiveNackPDU::SelectiveNackPDU(const char *name, int kind) : ::SelectiveNAckFlow(name,kind)
{
    this->setType(SELECT_NACK_PDU);
}

SelectiveNackPDU::SelectiveNackPDU(const SelectiveNackPDU& other) : ::SelectiveNAckFlow(other)
{
    copy(other);
}

SelectiveNackPDU::~SelectiveNackPDU()
{
}

SelectiveNackPDU& SelectiveNackPDU::operator=(const SelectiveNackPDU& other)
{
    if (this==&other) return *this;
    ::SelectiveNAckFlow::operator=(other);
    copy(other);
    return *this;
}

void SelectiveNackPDU::copy(const SelectiveNackPDU& other)
{
}

void SelectiveNackPDU::parsimPack(cCommBuffer *b)
{
    ::SelectiveNAckFlow::parsimPack(b);
}

void SelectiveNackPDU::parsimUnpack(cCommBuffer *b)
{
    ::SelectiveNAckFlow::parsimUnpack(b);
}

class SelectiveNackPDUDescriptor : public cClassDescriptor
{
  public:
    SelectiveNackPDUDescriptor();
    virtual ~SelectiveNackPDUDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(SelectiveNackPDUDescriptor);

SelectiveNackPDUDescriptor::SelectiveNackPDUDescriptor() : cClassDescriptor("SelectiveNackPDU", "SelectiveNAckFlow")
{
}

SelectiveNackPDUDescriptor::~SelectiveNackPDUDescriptor()
{
}

bool SelectiveNackPDUDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<SelectiveNackPDU *>(obj)!=NULL;
}

const char *SelectiveNackPDUDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int SelectiveNackPDUDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int SelectiveNackPDUDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *SelectiveNackPDUDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int SelectiveNackPDUDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *SelectiveNackPDUDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *SelectiveNackPDUDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int SelectiveNackPDUDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    SelectiveNackPDU *pp = (SelectiveNackPDU *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string SelectiveNackPDUDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    SelectiveNackPDU *pp = (SelectiveNackPDU *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool SelectiveNackPDUDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    SelectiveNackPDU *pp = (SelectiveNackPDU *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *SelectiveNackPDUDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *SelectiveNackPDUDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    SelectiveNackPDU *pp = (SelectiveNackPDU *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


