//
// Generated file, do not edit! Created by opp_msgc 4.5 from DIF/EFCP/FCTimers.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "FCTimers_m.h"

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
    cEnum *e = cEnum::find("FCTimerType");
    if (!e) enums.getInstance()->add(e = new cEnum("FCTimerType"));
    e->insert(FC_SENDING_RATE_TIMER, "FC_SENDING_RATE_TIMER");
);

Register_Class(FCTimers);

FCTimers::FCTimers(const char *name, int kind) : ::cMessage(name,kind)
{
    this->type_var = 0;
    this->anotherField_var = 0;
    arrayField1_arraysize = 0;
    this->arrayField1_var = 0;
    for (unsigned int i=0; i<10; i++)
        this->arrayField2_var[i] = 0;
}

FCTimers::FCTimers(const FCTimers& other) : ::cMessage(other)
{
    arrayField1_arraysize = 0;
    this->arrayField1_var = 0;
    copy(other);
}

FCTimers::~FCTimers()
{
    delete [] arrayField1_var;
}

FCTimers& FCTimers::operator=(const FCTimers& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void FCTimers::copy(const FCTimers& other)
{
    this->type_var = other.type_var;
    this->anotherField_var = other.anotherField_var;
    delete [] this->arrayField1_var;
    this->arrayField1_var = (other.arrayField1_arraysize==0) ? NULL : new double[other.arrayField1_arraysize];
    arrayField1_arraysize = other.arrayField1_arraysize;
    for (unsigned int i=0; i<arrayField1_arraysize; i++)
        this->arrayField1_var[i] = other.arrayField1_var[i];
    for (unsigned int i=0; i<10; i++)
        this->arrayField2_var[i] = other.arrayField2_var[i];
}

void FCTimers::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->type_var);
    doPacking(b,this->anotherField_var);
    b->pack(arrayField1_arraysize);
    doPacking(b,this->arrayField1_var,arrayField1_arraysize);
    doPacking(b,this->arrayField2_var,10);
}

void FCTimers::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->type_var);
    doUnpacking(b,this->anotherField_var);
    delete [] this->arrayField1_var;
    b->unpack(arrayField1_arraysize);
    if (arrayField1_arraysize==0) {
        this->arrayField1_var = 0;
    } else {
        this->arrayField1_var = new double[arrayField1_arraysize];
        doUnpacking(b,this->arrayField1_var,arrayField1_arraysize);
    }
    doUnpacking(b,this->arrayField2_var,10);
}

int FCTimers::getType() const
{
    return type_var;
}

void FCTimers::setType(int type)
{
    this->type_var = type;
}

const char * FCTimers::getAnotherField() const
{
    return anotherField_var.c_str();
}

void FCTimers::setAnotherField(const char * anotherField)
{
    this->anotherField_var = anotherField;
}

void FCTimers::setArrayField1ArraySize(unsigned int size)
{
    double *arrayField1_var2 = (size==0) ? NULL : new double[size];
    unsigned int sz = arrayField1_arraysize < size ? arrayField1_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        arrayField1_var2[i] = this->arrayField1_var[i];
    for (unsigned int i=sz; i<size; i++)
        arrayField1_var2[i] = 0;
    arrayField1_arraysize = size;
    delete [] this->arrayField1_var;
    this->arrayField1_var = arrayField1_var2;
}

unsigned int FCTimers::getArrayField1ArraySize() const
{
    return arrayField1_arraysize;
}

double FCTimers::getArrayField1(unsigned int k) const
{
    if (k>=arrayField1_arraysize) throw cRuntimeError("Array of size %d indexed by %d", arrayField1_arraysize, k);
    return arrayField1_var[k];
}

void FCTimers::setArrayField1(unsigned int k, double arrayField1)
{
    if (k>=arrayField1_arraysize) throw cRuntimeError("Array of size %d indexed by %d", arrayField1_arraysize, k);
    this->arrayField1_var[k] = arrayField1;
}

unsigned int FCTimers::getArrayField2ArraySize() const
{
    return 10;
}

double FCTimers::getArrayField2(unsigned int k) const
{
    if (k>=10) throw cRuntimeError("Array of size 10 indexed by %lu", (unsigned long)k);
    return arrayField2_var[k];
}

void FCTimers::setArrayField2(unsigned int k, double arrayField2)
{
    if (k>=10) throw cRuntimeError("Array of size 10 indexed by %lu", (unsigned long)k);
    this->arrayField2_var[k] = arrayField2;
}

class FCTimersDescriptor : public cClassDescriptor
{
  public:
    FCTimersDescriptor();
    virtual ~FCTimersDescriptor();

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

Register_ClassDescriptor(FCTimersDescriptor);

FCTimersDescriptor::FCTimersDescriptor() : cClassDescriptor("FCTimers", "cMessage")
{
}

FCTimersDescriptor::~FCTimersDescriptor()
{
}

bool FCTimersDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<FCTimers *>(obj)!=NULL;
}

const char *FCTimersDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int FCTimersDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int FCTimersDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *FCTimersDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "type",
        "anotherField",
        "arrayField1",
        "arrayField2",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int FCTimersDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+0;
    if (fieldName[0]=='a' && strcmp(fieldName, "anotherField")==0) return base+1;
    if (fieldName[0]=='a' && strcmp(fieldName, "arrayField1")==0) return base+2;
    if (fieldName[0]=='a' && strcmp(fieldName, "arrayField2")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *FCTimersDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "string",
        "double",
        "double",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *FCTimersDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "FCTimerType";
            return NULL;
        default: return NULL;
    }
}

int FCTimersDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    FCTimers *pp = (FCTimers *)object; (void)pp;
    switch (field) {
        case 2: return pp->getArrayField1ArraySize();
        case 3: return 10;
        default: return 0;
    }
}

std::string FCTimersDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    FCTimers *pp = (FCTimers *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getType());
        case 1: return oppstring2string(pp->getAnotherField());
        case 2: return double2string(pp->getArrayField1(i));
        case 3: return double2string(pp->getArrayField2(i));
        default: return "";
    }
}

bool FCTimersDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    FCTimers *pp = (FCTimers *)object; (void)pp;
    switch (field) {
        case 0: pp->setType(string2long(value)); return true;
        case 1: pp->setAnotherField((value)); return true;
        case 2: pp->setArrayField1(i,string2double(value)); return true;
        case 3: pp->setArrayField2(i,string2double(value)); return true;
        default: return false;
    }
}

const char *FCTimersDescriptor::getFieldStructName(void *object, int field) const
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

void *FCTimersDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    FCTimers *pp = (FCTimers *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


