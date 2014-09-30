//
// Generated file, do not edit! Created by opp_msgc 4.5 from DIF/EFCP/DTPTimers.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "DTPTimers_m.h"

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

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("DTPTimerType");
    if (!e) enums.getInstance()->add(e = new cEnum("DTPTimerType"));
    e->insert(DTP_SENDER_INACTIVITY_TIMER, "DTP_SENDER_INACTIVITY_TIMER");
    e->insert(DTP_RCVR_INACTIVITY_TIMER, "DTP_RCVR_INACTIVITY_TIMER");
    e->insert(DTP_RX_EXPIRY_TIMER, "DTP_RX_EXPIRY_TIMER");
    e->insert(DTP_SENDING_RATE_TIMER, "DTP_SENDING_RATE_TIMER");
    e->insert(DTP_A_TIMER, "DTP_A_TIMER");
);

Register_Class(DTPTimers);

DTPTimers::DTPTimers(const char *name, int kind) : ::cMessage(name,kind)
{
    this->type_var = 0;
}

DTPTimers::DTPTimers(const DTPTimers& other) : ::cMessage(other)
{
    copy(other);
}

DTPTimers::~DTPTimers()
{
}

DTPTimers& DTPTimers::operator=(const DTPTimers& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void DTPTimers::copy(const DTPTimers& other)
{
    this->type_var = other.type_var;
}

void DTPTimers::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->type_var);
}

void DTPTimers::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->type_var);
}

int DTPTimers::getType() const
{
    return type_var;
}

void DTPTimers::setType(int type)
{
    this->type_var = type;
}

class DTPTimersDescriptor : public cClassDescriptor
{
  public:
    DTPTimersDescriptor();
    virtual ~DTPTimersDescriptor();

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

Register_ClassDescriptor(DTPTimersDescriptor);

DTPTimersDescriptor::DTPTimersDescriptor() : cClassDescriptor("DTPTimers", "cMessage")
{
}

DTPTimersDescriptor::~DTPTimersDescriptor()
{
}

bool DTPTimersDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DTPTimers *>(obj)!=NULL;
}

const char *DTPTimersDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DTPTimersDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int DTPTimersDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *DTPTimersDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "type",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int DTPTimersDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DTPTimersDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *DTPTimersDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "DTPTimerType";
            return NULL;
        default: return NULL;
    }
}

int DTPTimersDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DTPTimers *pp = (DTPTimers *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DTPTimersDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DTPTimers *pp = (DTPTimers *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getType());
        default: return "";
    }
}

bool DTPTimersDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DTPTimers *pp = (DTPTimers *)object; (void)pp;
    switch (field) {
        case 0: pp->setType(string2long(value)); return true;
        default: return false;
    }
}

const char *DTPTimersDescriptor::getFieldStructName(void *object, int field) const
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

void *DTPTimersDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DTPTimers *pp = (DTPTimers *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(InactivityTimer);

InactivityTimer::InactivityTimer(const char *name, int kind) : ::DTPTimers(name,kind)
{
}

InactivityTimer::InactivityTimer(const InactivityTimer& other) : ::DTPTimers(other)
{
    copy(other);
}

InactivityTimer::~InactivityTimer()
{
}

InactivityTimer& InactivityTimer::operator=(const InactivityTimer& other)
{
    if (this==&other) return *this;
    ::DTPTimers::operator=(other);
    copy(other);
    return *this;
}

void InactivityTimer::copy(const InactivityTimer& other)
{
}

void InactivityTimer::parsimPack(cCommBuffer *b)
{
    ::DTPTimers::parsimPack(b);
}

void InactivityTimer::parsimUnpack(cCommBuffer *b)
{
    ::DTPTimers::parsimUnpack(b);
}

class InactivityTimerDescriptor : public cClassDescriptor
{
  public:
    InactivityTimerDescriptor();
    virtual ~InactivityTimerDescriptor();

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

Register_ClassDescriptor(InactivityTimerDescriptor);

InactivityTimerDescriptor::InactivityTimerDescriptor() : cClassDescriptor("InactivityTimer", "DTPTimers")
{
}

InactivityTimerDescriptor::~InactivityTimerDescriptor()
{
}

bool InactivityTimerDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<InactivityTimer *>(obj)!=NULL;
}

const char *InactivityTimerDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int InactivityTimerDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int InactivityTimerDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *InactivityTimerDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int InactivityTimerDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *InactivityTimerDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *InactivityTimerDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int InactivityTimerDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    InactivityTimer *pp = (InactivityTimer *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string InactivityTimerDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    InactivityTimer *pp = (InactivityTimer *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool InactivityTimerDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    InactivityTimer *pp = (InactivityTimer *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *InactivityTimerDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *InactivityTimerDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    InactivityTimer *pp = (InactivityTimer *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(SenderInactivityTimer);

SenderInactivityTimer::SenderInactivityTimer(const char *name, int kind) : ::InactivityTimer(name,kind)
{
    this->setType(DTP_SENDER_INACTIVITY_TIMER);
}

SenderInactivityTimer::SenderInactivityTimer(const SenderInactivityTimer& other) : ::InactivityTimer(other)
{
    copy(other);
}

SenderInactivityTimer::~SenderInactivityTimer()
{
}

SenderInactivityTimer& SenderInactivityTimer::operator=(const SenderInactivityTimer& other)
{
    if (this==&other) return *this;
    ::InactivityTimer::operator=(other);
    copy(other);
    return *this;
}

void SenderInactivityTimer::copy(const SenderInactivityTimer& other)
{
}

void SenderInactivityTimer::parsimPack(cCommBuffer *b)
{
    ::InactivityTimer::parsimPack(b);
}

void SenderInactivityTimer::parsimUnpack(cCommBuffer *b)
{
    ::InactivityTimer::parsimUnpack(b);
}

class SenderInactivityTimerDescriptor : public cClassDescriptor
{
  public:
    SenderInactivityTimerDescriptor();
    virtual ~SenderInactivityTimerDescriptor();

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

Register_ClassDescriptor(SenderInactivityTimerDescriptor);

SenderInactivityTimerDescriptor::SenderInactivityTimerDescriptor() : cClassDescriptor("SenderInactivityTimer", "InactivityTimer")
{
}

SenderInactivityTimerDescriptor::~SenderInactivityTimerDescriptor()
{
}

bool SenderInactivityTimerDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<SenderInactivityTimer *>(obj)!=NULL;
}

const char *SenderInactivityTimerDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int SenderInactivityTimerDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int SenderInactivityTimerDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *SenderInactivityTimerDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int SenderInactivityTimerDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *SenderInactivityTimerDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *SenderInactivityTimerDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int SenderInactivityTimerDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    SenderInactivityTimer *pp = (SenderInactivityTimer *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string SenderInactivityTimerDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    SenderInactivityTimer *pp = (SenderInactivityTimer *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool SenderInactivityTimerDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    SenderInactivityTimer *pp = (SenderInactivityTimer *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *SenderInactivityTimerDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *SenderInactivityTimerDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    SenderInactivityTimer *pp = (SenderInactivityTimer *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(RcvrInactivityTimer);

RcvrInactivityTimer::RcvrInactivityTimer(const char *name, int kind) : ::InactivityTimer(name,kind)
{
    this->setType(DTP_RCVR_INACTIVITY_TIMER);
}

RcvrInactivityTimer::RcvrInactivityTimer(const RcvrInactivityTimer& other) : ::InactivityTimer(other)
{
    copy(other);
}

RcvrInactivityTimer::~RcvrInactivityTimer()
{
}

RcvrInactivityTimer& RcvrInactivityTimer::operator=(const RcvrInactivityTimer& other)
{
    if (this==&other) return *this;
    ::InactivityTimer::operator=(other);
    copy(other);
    return *this;
}

void RcvrInactivityTimer::copy(const RcvrInactivityTimer& other)
{
}

void RcvrInactivityTimer::parsimPack(cCommBuffer *b)
{
    ::InactivityTimer::parsimPack(b);
}

void RcvrInactivityTimer::parsimUnpack(cCommBuffer *b)
{
    ::InactivityTimer::parsimUnpack(b);
}

class RcvrInactivityTimerDescriptor : public cClassDescriptor
{
  public:
    RcvrInactivityTimerDescriptor();
    virtual ~RcvrInactivityTimerDescriptor();

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

Register_ClassDescriptor(RcvrInactivityTimerDescriptor);

RcvrInactivityTimerDescriptor::RcvrInactivityTimerDescriptor() : cClassDescriptor("RcvrInactivityTimer", "InactivityTimer")
{
}

RcvrInactivityTimerDescriptor::~RcvrInactivityTimerDescriptor()
{
}

bool RcvrInactivityTimerDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<RcvrInactivityTimer *>(obj)!=NULL;
}

const char *RcvrInactivityTimerDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int RcvrInactivityTimerDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int RcvrInactivityTimerDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *RcvrInactivityTimerDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int RcvrInactivityTimerDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *RcvrInactivityTimerDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *RcvrInactivityTimerDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int RcvrInactivityTimerDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    RcvrInactivityTimer *pp = (RcvrInactivityTimer *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string RcvrInactivityTimerDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    RcvrInactivityTimer *pp = (RcvrInactivityTimer *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool RcvrInactivityTimerDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    RcvrInactivityTimer *pp = (RcvrInactivityTimer *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *RcvrInactivityTimerDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *RcvrInactivityTimerDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    RcvrInactivityTimer *pp = (RcvrInactivityTimer *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(RxExpiryTimer);

RxExpiryTimer::RxExpiryTimer(const char *name, int kind) : ::DTPTimers(name,kind)
{
    this->setType(DTP_RX_EXPIRY_TIMER);

    this->pdu_var = NULL;
    this->expiryCount_var = 0;
}

RxExpiryTimer::RxExpiryTimer(const RxExpiryTimer& other) : ::DTPTimers(other)
{
    copy(other);
}

RxExpiryTimer::~RxExpiryTimer()
{
}

RxExpiryTimer& RxExpiryTimer::operator=(const RxExpiryTimer& other)
{
    if (this==&other) return *this;
    ::DTPTimers::operator=(other);
    copy(other);
    return *this;
}

void RxExpiryTimer::copy(const RxExpiryTimer& other)
{
    this->pdu_var = other.pdu_var;
    this->expiryCount_var = other.expiryCount_var;
}

void RxExpiryTimer::parsimPack(cCommBuffer *b)
{
    ::DTPTimers::parsimPack(b);
    doPacking(b,this->pdu_var);
    doPacking(b,this->expiryCount_var);
}

void RxExpiryTimer::parsimUnpack(cCommBuffer *b)
{
    ::DTPTimers::parsimUnpack(b);
    doUnpacking(b,this->pdu_var);
    doUnpacking(b,this->expiryCount_var);
}

PDU_p& RxExpiryTimer::getPdu()
{
    return pdu_var;
}

void RxExpiryTimer::setPdu(const PDU_p& pdu)
{
    this->pdu_var = pdu;
}

unsigned int RxExpiryTimer::getExpiryCount() const
{
    return expiryCount_var;
}

void RxExpiryTimer::setExpiryCount(unsigned int expiryCount)
{
    this->expiryCount_var = expiryCount;
}

class RxExpiryTimerDescriptor : public cClassDescriptor
{
  public:
    RxExpiryTimerDescriptor();
    virtual ~RxExpiryTimerDescriptor();

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

Register_ClassDescriptor(RxExpiryTimerDescriptor);

RxExpiryTimerDescriptor::RxExpiryTimerDescriptor() : cClassDescriptor("RxExpiryTimer", "DTPTimers")
{
}

RxExpiryTimerDescriptor::~RxExpiryTimerDescriptor()
{
}

bool RxExpiryTimerDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<RxExpiryTimer *>(obj)!=NULL;
}

const char *RxExpiryTimerDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int RxExpiryTimerDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int RxExpiryTimerDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *RxExpiryTimerDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "pdu",
        "expiryCount",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int RxExpiryTimerDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "pdu")==0) return base+0;
    if (fieldName[0]=='e' && strcmp(fieldName, "expiryCount")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *RxExpiryTimerDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "PDU_p",
        "unsigned int",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *RxExpiryTimerDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int RxExpiryTimerDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    RxExpiryTimer *pp = (RxExpiryTimer *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string RxExpiryTimerDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    RxExpiryTimer *pp = (RxExpiryTimer *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getPdu(); return out.str();}
        case 1: return ulong2string(pp->getExpiryCount());
        default: return "";
    }
}

bool RxExpiryTimerDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    RxExpiryTimer *pp = (RxExpiryTimer *)object; (void)pp;
    switch (field) {
        case 1: pp->setExpiryCount(string2ulong(value)); return true;
        default: return false;
    }
}

const char *RxExpiryTimerDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return opp_typename(typeid(PDU_p));
        default: return NULL;
    };
}

void *RxExpiryTimerDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    RxExpiryTimer *pp = (RxExpiryTimer *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getPdu()); break;
        default: return NULL;
    }
}

Register_Class(SendingRateTimer);

SendingRateTimer::SendingRateTimer(const char *name, int kind) : ::DTPTimers(name,kind)
{
    this->setType(DTP_SENDING_RATE_TIMER);
}

SendingRateTimer::SendingRateTimer(const SendingRateTimer& other) : ::DTPTimers(other)
{
    copy(other);
}

SendingRateTimer::~SendingRateTimer()
{
}

SendingRateTimer& SendingRateTimer::operator=(const SendingRateTimer& other)
{
    if (this==&other) return *this;
    ::DTPTimers::operator=(other);
    copy(other);
    return *this;
}

void SendingRateTimer::copy(const SendingRateTimer& other)
{
}

void SendingRateTimer::parsimPack(cCommBuffer *b)
{
    ::DTPTimers::parsimPack(b);
}

void SendingRateTimer::parsimUnpack(cCommBuffer *b)
{
    ::DTPTimers::parsimUnpack(b);
}

class SendingRateTimerDescriptor : public cClassDescriptor
{
  public:
    SendingRateTimerDescriptor();
    virtual ~SendingRateTimerDescriptor();

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

Register_ClassDescriptor(SendingRateTimerDescriptor);

SendingRateTimerDescriptor::SendingRateTimerDescriptor() : cClassDescriptor("SendingRateTimer", "DTPTimers")
{
}

SendingRateTimerDescriptor::~SendingRateTimerDescriptor()
{
}

bool SendingRateTimerDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<SendingRateTimer *>(obj)!=NULL;
}

const char *SendingRateTimerDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int SendingRateTimerDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int SendingRateTimerDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *SendingRateTimerDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int SendingRateTimerDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *SendingRateTimerDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *SendingRateTimerDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int SendingRateTimerDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    SendingRateTimer *pp = (SendingRateTimer *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string SendingRateTimerDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    SendingRateTimer *pp = (SendingRateTimer *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool SendingRateTimerDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    SendingRateTimer *pp = (SendingRateTimer *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *SendingRateTimerDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *SendingRateTimerDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    SendingRateTimer *pp = (SendingRateTimer *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(ATimer);

ATimer::ATimer(const char *name, int kind) : ::DTPTimers(name,kind)
{
    this->setType(DTP_A_TIMER);

    this->pdu_var = NULL;
}

ATimer::ATimer(const ATimer& other) : ::DTPTimers(other)
{
    copy(other);
}

ATimer::~ATimer()
{
}

ATimer& ATimer::operator=(const ATimer& other)
{
    if (this==&other) return *this;
    ::DTPTimers::operator=(other);
    copy(other);
    return *this;
}

void ATimer::copy(const ATimer& other)
{
    this->pdu_var = other.pdu_var;
}

void ATimer::parsimPack(cCommBuffer *b)
{
    ::DTPTimers::parsimPack(b);
    doPacking(b,this->pdu_var);
}

void ATimer::parsimUnpack(cCommBuffer *b)
{
    ::DTPTimers::parsimUnpack(b);
    doUnpacking(b,this->pdu_var);
}

PDU_p& ATimer::getPdu()
{
    return pdu_var;
}

void ATimer::setPdu(const PDU_p& pdu)
{
    this->pdu_var = pdu;
}

class ATimerDescriptor : public cClassDescriptor
{
  public:
    ATimerDescriptor();
    virtual ~ATimerDescriptor();

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

Register_ClassDescriptor(ATimerDescriptor);

ATimerDescriptor::ATimerDescriptor() : cClassDescriptor("ATimer", "DTPTimers")
{
}

ATimerDescriptor::~ATimerDescriptor()
{
}

bool ATimerDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<ATimer *>(obj)!=NULL;
}

const char *ATimerDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int ATimerDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int ATimerDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *ATimerDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "pdu",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int ATimerDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "pdu")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *ATimerDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "PDU_p",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *ATimerDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int ATimerDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    ATimer *pp = (ATimer *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string ATimerDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    ATimer *pp = (ATimer *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getPdu(); return out.str();}
        default: return "";
    }
}

bool ATimerDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    ATimer *pp = (ATimer *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *ATimerDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return opp_typename(typeid(PDU_p));
        default: return NULL;
    };
}

void *ATimerDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    ATimer *pp = (ATimer *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getPdu()); break;
        default: return NULL;
    }
}


