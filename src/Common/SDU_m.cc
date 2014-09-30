//
// Generated file, do not edit! Created by opp_msgc 4.5 from Common/SDU.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "SDU_m.h"

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

SDU_Base::SDU_Base(const char *name, int kind) : ::Data(name,kind)
{
    this->size_var = 0;
    this->offset_var = 0;
}

SDU_Base::SDU_Base(const SDU_Base& other) : ::Data(other)
{
    copy(other);
}

SDU_Base::~SDU_Base()
{
}

SDU_Base& SDU_Base::operator=(const SDU_Base& other)
{
    if (this==&other) return *this;
    ::Data::operator=(other);
    copy(other);
    return *this;
}

void SDU_Base::copy(const SDU_Base& other)
{
    this->size_var = other.size_var;
    this->offset_var = other.offset_var;
    this->mUserData_var = other.mUserData_var;
}

void SDU_Base::parsimPack(cCommBuffer *b)
{
    ::Data::parsimPack(b);
    doPacking(b,this->size_var);
    doPacking(b,this->offset_var);
    doPacking(b,this->mUserData_var);
}

void SDU_Base::parsimUnpack(cCommBuffer *b)
{
    ::Data::parsimUnpack(b);
    doUnpacking(b,this->size_var);
    doUnpacking(b,this->offset_var);
    doUnpacking(b,this->mUserData_var);
}

unsigned int SDU_Base::getSize() const
{
    return size_var;
}

void SDU_Base::setSize(unsigned int size)
{
    this->size_var = size;
}

unsigned int SDU_Base::getOffset() const
{
    return offset_var;
}

void SDU_Base::setOffset(unsigned int offset)
{
    this->offset_var = offset;
}

mUserDataType& SDU_Base::getMUserData()
{
    return mUserData_var;
}

void SDU_Base::setMUserData(const mUserDataType& mUserData)
{
    this->mUserData_var = mUserData;
}

class SDUDescriptor : public cClassDescriptor
{
  public:
    SDUDescriptor();
    virtual ~SDUDescriptor();

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

Register_ClassDescriptor(SDUDescriptor);

SDUDescriptor::SDUDescriptor() : cClassDescriptor("SDU", "Data")
{
}

SDUDescriptor::~SDUDescriptor()
{
}

bool SDUDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<SDU_Base *>(obj)!=NULL;
}

const char *SDUDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"customize")) return "true";
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int SDUDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int SDUDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *SDUDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "size",
        "offset",
        "mUserData",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int SDUDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "size")==0) return base+0;
    if (fieldName[0]=='o' && strcmp(fieldName, "offset")==0) return base+1;
    if (fieldName[0]=='m' && strcmp(fieldName, "mUserData")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *SDUDescriptor::getFieldTypeString(void *object, int field) const
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
        "mUserDataType",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *SDUDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int SDUDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    SDU_Base *pp = (SDU_Base *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string SDUDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    SDU_Base *pp = (SDU_Base *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getSize());
        case 1: return ulong2string(pp->getOffset());
        case 2: {std::stringstream out; out << pp->getMUserData(); return out.str();}
        default: return "";
    }
}

bool SDUDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    SDU_Base *pp = (SDU_Base *)object; (void)pp;
    switch (field) {
        case 0: pp->setSize(string2ulong(value)); return true;
        case 1: pp->setOffset(string2ulong(value)); return true;
        default: return false;
    }
}

const char *SDUDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 2: return opp_typename(typeid(mUserDataType));
        default: return NULL;
    };
}

void *SDUDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    SDU_Base *pp = (SDU_Base *)object; (void)pp;
    switch (field) {
        case 2: return (void *)(&pp->getMUserData()); break;
        default: return NULL;
    }
}


