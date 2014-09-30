//
// Generated file, do not edit! Created by opp_msgc 4.5 from DAF/CDAP/CDAPMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "CDAPMessage_m.h"

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
    cEnum *e = cEnum::find("opCode_t");
    if (!e) enums.getInstance()->add(e = new cEnum("opCode_t"));
    e->insert(M_CONNECT, "M_CONNECT");
    e->insert(M_CONNECT_R, "M_CONNECT_R");
    e->insert(M_RELEASE, "M_RELEASE");
    e->insert(M_RELEASE_R, "M_RELEASE_R");
    e->insert(M_CREATE, "M_CREATE");
    e->insert(M_CREATE_R, "M_CREATE_R");
    e->insert(M_DELETE, "M_DELETE");
    e->insert(M_DELETE_R, "M_DELETE_R");
    e->insert(M_READ, "M_READ");
    e->insert(M_READ_R, "M_READ_R");
    e->insert(M_CANCELREAD, "M_CANCELREAD");
    e->insert(M_CANCELREAD_R, "M_CANCELREAD_R");
    e->insert(M_WRITE, "M_WRITE");
    e->insert(M_WRITE_R, "M_WRITE_R");
    e->insert(M_START, "M_START");
    e->insert(M_START_R, "M_START_R");
    e->insert(M_STOP, "M_STOP");
    e->insert(M_STOP_R, "M_STOP_R");
);

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("flagValues_t");
    if (!e) enums.getInstance()->add(e = new cEnum("flagValues_t"));
    e->insert(F_SYNC, "F_SYNC");
    e->insert(F_RD_INCOMPLETE, "F_RD_INCOMPLETE");
);

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("authTypes_t");
    if (!e) enums.getInstance()->add(e = new cEnum("authTypes_t"));
    e->insert(AUTH_NONE, "AUTH_NONE");
    e->insert(AUTH_PASSWD, "AUTH_PASSWD");
    e->insert(AUTH_SSHRSA, "AUTH_SSHRSA");
    e->insert(AUTH_SSHDSA, "AUTH_SSHDSA");
);

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("resultVal_t");
    if (!e) enums.getInstance()->add(e = new cEnum("resultVal_t"));
    e->insert(R_CLASSNOTFOUND, "R_CLASSNOTFOUND");
    e->insert(R_OBJBADINST, "R_OBJBADINST");
    e->insert(R_OBJNOTFOUND, "R_OBJNOTFOUND");
    e->insert(R_OS_ERR, "R_OS_ERR");
    e->insert(R_FAIL, "R_FAIL");
    e->insert(R_SUCCESS, "R_SUCCESS");
    e->insert(R_SYNC_UNIMP, "R_SYNC_UNIMP");
    e->insert(R_FILTER_FALSE, "R_FILTER_FALSE");
    e->insert(R_FILTER_MIXED, "R_FILTER_MIXED");
);

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("absSyntax_t");
    if (!e) enums.getInstance()->add(e = new cEnum("absSyntax_t"));
    e->insert(GPB, "GPB");
);

objVal_t::objVal_t()
{
    intval = 0;
    sintval = 0;
    int64val = 0;
    sint64val = 0;
    strval = 0;
    floatval = 0;
    doubleval = 0;
}

void doPacking(cCommBuffer *b, objVal_t& a)
{
    doPacking(b,a.intval);
    doPacking(b,a.sintval);
    doPacking(b,a.int64val);
    doPacking(b,a.sint64val);
    doPacking(b,a.strval);
    doPacking(b,a.floatval);
    doPacking(b,a.doubleval);
}

void doUnpacking(cCommBuffer *b, objVal_t& a)
{
    doUnpacking(b,a.intval);
    doUnpacking(b,a.sintval);
    doUnpacking(b,a.int64val);
    doUnpacking(b,a.sint64val);
    doUnpacking(b,a.strval);
    doUnpacking(b,a.floatval);
    doUnpacking(b,a.doubleval);
}

class objVal_tDescriptor : public cClassDescriptor
{
  public:
    objVal_tDescriptor();
    virtual ~objVal_tDescriptor();

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

Register_ClassDescriptor(objVal_tDescriptor);

objVal_tDescriptor::objVal_tDescriptor() : cClassDescriptor("objVal_t", "")
{
}

objVal_tDescriptor::~objVal_tDescriptor()
{
}

bool objVal_tDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<objVal_t *>(obj)!=NULL;
}

const char *objVal_tDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int objVal_tDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int objVal_tDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *objVal_tDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "intval",
        "sintval",
        "int64val",
        "sint64val",
        "strval",
        "floatval",
        "doubleval",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int objVal_tDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "intval")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "sintval")==0) return base+1;
    if (fieldName[0]=='i' && strcmp(fieldName, "int64val")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "sint64val")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "strval")==0) return base+4;
    if (fieldName[0]=='f' && strcmp(fieldName, "floatval")==0) return base+5;
    if (fieldName[0]=='d' && strcmp(fieldName, "doubleval")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *objVal_tDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "uint32",
        "int32",
        "uint64",
        "int64",
        "string",
        "float",
        "double",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *objVal_tDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int objVal_tDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    objVal_t *pp = (objVal_t *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string objVal_tDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    objVal_t *pp = (objVal_t *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->intval);
        case 1: return long2string(pp->sintval);
        case 2: return uint642string(pp->int64val);
        case 3: return int642string(pp->sint64val);
        case 4: return oppstring2string(pp->strval);
        case 5: return double2string(pp->floatval);
        case 6: return double2string(pp->doubleval);
        default: return "";
    }
}

bool objVal_tDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    objVal_t *pp = (objVal_t *)object; (void)pp;
    switch (field) {
        case 0: pp->intval = string2ulong(value); return true;
        case 1: pp->sintval = string2long(value); return true;
        case 2: pp->int64val = string2uint64(value); return true;
        case 3: pp->sint64val = string2int64(value); return true;
        case 4: pp->strval = (value); return true;
        case 5: pp->floatval = string2double(value); return true;
        case 6: pp->doubleval = string2double(value); return true;
        default: return false;
    }
}

const char *objVal_tDescriptor::getFieldStructName(void *object, int field) const
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

void *objVal_tDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    objVal_t *pp = (objVal_t *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

authValue_t::authValue_t()
{
    authName = 0;
    authPassword = 0;
    authOther = 0;
}

void doPacking(cCommBuffer *b, authValue_t& a)
{
    doPacking(b,a.authName);
    doPacking(b,a.authPassword);
    doPacking(b,a.authOther);
}

void doUnpacking(cCommBuffer *b, authValue_t& a)
{
    doUnpacking(b,a.authName);
    doUnpacking(b,a.authPassword);
    doUnpacking(b,a.authOther);
}

class authValue_tDescriptor : public cClassDescriptor
{
  public:
    authValue_tDescriptor();
    virtual ~authValue_tDescriptor();

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

Register_ClassDescriptor(authValue_tDescriptor);

authValue_tDescriptor::authValue_tDescriptor() : cClassDescriptor("authValue_t", "")
{
}

authValue_tDescriptor::~authValue_tDescriptor()
{
}

bool authValue_tDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<authValue_t *>(obj)!=NULL;
}

const char *authValue_tDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int authValue_tDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int authValue_tDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *authValue_tDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "authName",
        "authPassword",
        "authOther",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int authValue_tDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='a' && strcmp(fieldName, "authName")==0) return base+0;
    if (fieldName[0]=='a' && strcmp(fieldName, "authPassword")==0) return base+1;
    if (fieldName[0]=='a' && strcmp(fieldName, "authOther")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *authValue_tDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "string",
        "string",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *authValue_tDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int authValue_tDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    authValue_t *pp = (authValue_t *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string authValue_tDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    authValue_t *pp = (authValue_t *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->authName);
        case 1: return oppstring2string(pp->authPassword);
        case 2: return oppstring2string(pp->authOther);
        default: return "";
    }
}

bool authValue_tDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    authValue_t *pp = (authValue_t *)object; (void)pp;
    switch (field) {
        case 0: pp->authName = (value); return true;
        case 1: pp->authPassword = (value); return true;
        case 2: pp->authOther = (value); return true;
        default: return false;
    }
}

const char *authValue_tDescriptor::getFieldStructName(void *object, int field) const
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

void *authValue_tDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    authValue_t *pp = (authValue_t *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

result_t::result_t()
{
    resultReason = 0;
    resultValue = 0;
}

void doPacking(cCommBuffer *b, result_t& a)
{
    doPacking(b,a.resultReason);
    doPacking(b,a.resultValue);
}

void doUnpacking(cCommBuffer *b, result_t& a)
{
    doUnpacking(b,a.resultReason);
    doUnpacking(b,a.resultValue);
}

class result_tDescriptor : public cClassDescriptor
{
  public:
    result_tDescriptor();
    virtual ~result_tDescriptor();

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

Register_ClassDescriptor(result_tDescriptor);

result_tDescriptor::result_tDescriptor() : cClassDescriptor("result_t", "")
{
}

result_tDescriptor::~result_tDescriptor()
{
}

bool result_tDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<result_t *>(obj)!=NULL;
}

const char *result_tDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int result_tDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int result_tDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *result_tDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "resultReason",
        "resultValue",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int result_tDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "resultReason")==0) return base+0;
    if (fieldName[0]=='r' && strcmp(fieldName, "resultValue")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *result_tDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "int",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *result_tDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int result_tDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    result_t *pp = (result_t *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string result_tDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    result_t *pp = (result_t *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->resultReason);
        case 1: return long2string(pp->resultValue);
        default: return "";
    }
}

bool result_tDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    result_t *pp = (result_t *)object; (void)pp;
    switch (field) {
        case 0: pp->resultReason = (value); return true;
        case 1: pp->resultValue = string2long(value); return true;
        default: return false;
    }
}

const char *result_tDescriptor::getFieldStructName(void *object, int field) const
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

void *result_tDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    result_t *pp = (result_t *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

auth_t::auth_t()
{
    authType = 0;
}

void doPacking(cCommBuffer *b, auth_t& a)
{
    doPacking(b,a.authType);
    doPacking(b,a.authValue);
}

void doUnpacking(cCommBuffer *b, auth_t& a)
{
    doUnpacking(b,a.authType);
    doUnpacking(b,a.authValue);
}

class auth_tDescriptor : public cClassDescriptor
{
  public:
    auth_tDescriptor();
    virtual ~auth_tDescriptor();

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

Register_ClassDescriptor(auth_tDescriptor);

auth_tDescriptor::auth_tDescriptor() : cClassDescriptor("auth_t", "")
{
}

auth_tDescriptor::~auth_tDescriptor()
{
}

bool auth_tDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<auth_t *>(obj)!=NULL;
}

const char *auth_tDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int auth_tDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int auth_tDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *auth_tDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "authType",
        "authValue",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int auth_tDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='a' && strcmp(fieldName, "authType")==0) return base+0;
    if (fieldName[0]=='a' && strcmp(fieldName, "authValue")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *auth_tDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "authValue_t",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *auth_tDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "authTypes_t";
            return NULL;
        default: return NULL;
    }
}

int auth_tDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    auth_t *pp = (auth_t *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string auth_tDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    auth_t *pp = (auth_t *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->authType);
        case 1: {std::stringstream out; out << pp->authValue; return out.str();}
        default: return "";
    }
}

bool auth_tDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    auth_t *pp = (auth_t *)object; (void)pp;
    switch (field) {
        case 0: pp->authType = string2ulong(value); return true;
        default: return false;
    }
}

const char *auth_tDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 1: return opp_typename(typeid(authValue_t));
        default: return NULL;
    };
}

void *auth_tDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    auth_t *pp = (auth_t *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->authValue); break;
        default: return NULL;
    }
}

naming_t::naming_t()
{
    AEInst = 0;
    AEName = 0;
    ApInst = 0;
    ApName = 0;
}

void doPacking(cCommBuffer *b, naming_t& a)
{
    doPacking(b,a.AEInst);
    doPacking(b,a.AEName);
    doPacking(b,a.ApInst);
    doPacking(b,a.ApName);
}

void doUnpacking(cCommBuffer *b, naming_t& a)
{
    doUnpacking(b,a.AEInst);
    doUnpacking(b,a.AEName);
    doUnpacking(b,a.ApInst);
    doUnpacking(b,a.ApName);
}

class naming_tDescriptor : public cClassDescriptor
{
  public:
    naming_tDescriptor();
    virtual ~naming_tDescriptor();

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

Register_ClassDescriptor(naming_tDescriptor);

naming_tDescriptor::naming_tDescriptor() : cClassDescriptor("naming_t", "")
{
}

naming_tDescriptor::~naming_tDescriptor()
{
}

bool naming_tDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<naming_t *>(obj)!=NULL;
}

const char *naming_tDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int naming_tDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int naming_tDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *naming_tDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "AEInst",
        "AEName",
        "ApInst",
        "ApName",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int naming_tDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='A' && strcmp(fieldName, "AEInst")==0) return base+0;
    if (fieldName[0]=='A' && strcmp(fieldName, "AEName")==0) return base+1;
    if (fieldName[0]=='A' && strcmp(fieldName, "ApInst")==0) return base+2;
    if (fieldName[0]=='A' && strcmp(fieldName, "ApName")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *naming_tDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "string",
        "string",
        "string",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *naming_tDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int naming_tDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    naming_t *pp = (naming_t *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string naming_tDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    naming_t *pp = (naming_t *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->AEInst);
        case 1: return oppstring2string(pp->AEName);
        case 2: return oppstring2string(pp->ApInst);
        case 3: return oppstring2string(pp->ApName);
        default: return "";
    }
}

bool naming_tDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    naming_t *pp = (naming_t *)object; (void)pp;
    switch (field) {
        case 0: pp->AEInst = (value); return true;
        case 1: pp->AEName = (value); return true;
        case 2: pp->ApInst = (value); return true;
        case 3: pp->ApName = (value); return true;
        default: return false;
    }
}

const char *naming_tDescriptor::getFieldStructName(void *object, int field) const
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

void *naming_tDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    naming_t *pp = (naming_t *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

object_t::object_t()
{
    objectClass = 0;
    objectName = 0;
    objectInstance = 0;
}

void doPacking(cCommBuffer *b, object_t& a)
{
    doPacking(b,a.objectClass);
    doPacking(b,a.objectName);
    doPacking(b,a.objectInstance);
    doPacking(b,a.objectVal);
}

void doUnpacking(cCommBuffer *b, object_t& a)
{
    doUnpacking(b,a.objectClass);
    doUnpacking(b,a.objectName);
    doUnpacking(b,a.objectInstance);
    doUnpacking(b,a.objectVal);
}

class object_tDescriptor : public cClassDescriptor
{
  public:
    object_tDescriptor();
    virtual ~object_tDescriptor();

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

Register_ClassDescriptor(object_tDescriptor);

object_tDescriptor::object_tDescriptor() : cClassDescriptor("object_t", "")
{
}

object_tDescriptor::~object_tDescriptor()
{
}

bool object_tDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<object_t *>(obj)!=NULL;
}

const char *object_tDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int object_tDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int object_tDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND | FD_ISCOBJECT,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *object_tDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "objectClass",
        "objectName",
        "objectInstance",
        "objectVal",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int object_tDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "objectClass")==0) return base+0;
    if (fieldName[0]=='o' && strcmp(fieldName, "objectName")==0) return base+1;
    if (fieldName[0]=='o' && strcmp(fieldName, "objectInstance")==0) return base+2;
    if (fieldName[0]=='o' && strcmp(fieldName, "objectVal")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *object_tDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "string",
        "int",
        "cObject",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *object_tDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int object_tDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    object_t *pp = (object_t *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string object_tDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    object_t *pp = (object_t *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->objectClass);
        case 1: return oppstring2string(pp->objectName);
        case 2: return long2string(pp->objectInstance);
        case 3: {std::stringstream out; out << pp->objectVal; return out.str();}
        default: return "";
    }
}

bool object_tDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    object_t *pp = (object_t *)object; (void)pp;
    switch (field) {
        case 0: pp->objectClass = (value); return true;
        case 1: pp->objectName = (value); return true;
        case 2: pp->objectInstance = string2long(value); return true;
        default: return false;
    }
}

const char *object_tDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 3: return opp_typename(typeid(cObject));
        default: return NULL;
    };
}

void *object_tDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    object_t *pp = (object_t *)object; (void)pp;
    switch (field) {
        case 3: return (void *)static_cast<cObject *>(&pp->objectVal); break;
        default: return NULL;
    }
}

Register_Class(CDAPMessage);

CDAPMessage::CDAPMessage(const char *name, int kind) : ::cMessage(name,kind)
{
    this->size_var = 0;
}

CDAPMessage::CDAPMessage(const CDAPMessage& other) : ::cMessage(other)
{
    copy(other);
}

CDAPMessage::~CDAPMessage()
{
}

CDAPMessage& CDAPMessage::operator=(const CDAPMessage& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void CDAPMessage::copy(const CDAPMessage& other)
{
    this->size_var = other.size_var;
}

void CDAPMessage::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->size_var);
}

void CDAPMessage::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->size_var);
}

unsigned int CDAPMessage::getSize() const
{
    return size_var;
}

void CDAPMessage::setSize(unsigned int size)
{
    this->size_var = size;
}

class CDAPMessageDescriptor : public cClassDescriptor
{
  public:
    CDAPMessageDescriptor();
    virtual ~CDAPMessageDescriptor();

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

Register_ClassDescriptor(CDAPMessageDescriptor);

CDAPMessageDescriptor::CDAPMessageDescriptor() : cClassDescriptor("CDAPMessage", "cMessage")
{
}

CDAPMessageDescriptor::~CDAPMessageDescriptor()
{
}

bool CDAPMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CDAPMessage *>(obj)!=NULL;
}

const char *CDAPMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CDAPMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int CDAPMessageDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *CDAPMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "size",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int CDAPMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "size")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CDAPMessageDescriptor::getFieldTypeString(void *object, int field) const
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

const char *CDAPMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int CDAPMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CDAPMessage *pp = (CDAPMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CDAPMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CDAPMessage *pp = (CDAPMessage *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getSize());
        default: return "";
    }
}

bool CDAPMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CDAPMessage *pp = (CDAPMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setSize(string2ulong(value)); return true;
        default: return false;
    }
}

const char *CDAPMessageDescriptor::getFieldStructName(void *object, int field) const
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

void *CDAPMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CDAPMessage *pp = (CDAPMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(CDAP_M_Connect);

CDAP_M_Connect::CDAP_M_Connect(const char *name, int kind) : ::CDAPMessage(name,kind)
{
    this->opCode_var = M_CONNECT;
    this->invokeID_var = 0;
    this->flags_var = 0;
    this->version_var = 0;
    this->absSyntax_var = 0;
}

CDAP_M_Connect::CDAP_M_Connect(const CDAP_M_Connect& other) : ::CDAPMessage(other)
{
    copy(other);
}

CDAP_M_Connect::~CDAP_M_Connect()
{
}

CDAP_M_Connect& CDAP_M_Connect::operator=(const CDAP_M_Connect& other)
{
    if (this==&other) return *this;
    ::CDAPMessage::operator=(other);
    copy(other);
    return *this;
}

void CDAP_M_Connect::copy(const CDAP_M_Connect& other)
{
    this->opCode_var = other.opCode_var;
    this->invokeID_var = other.invokeID_var;
    this->flags_var = other.flags_var;
    this->version_var = other.version_var;
    this->absSyntax_var = other.absSyntax_var;
    this->auth_var = other.auth_var;
    this->src_var = other.src_var;
    this->dst_var = other.dst_var;
}

void CDAP_M_Connect::parsimPack(cCommBuffer *b)
{
    ::CDAPMessage::parsimPack(b);
    doPacking(b,this->opCode_var);
    doPacking(b,this->invokeID_var);
    doPacking(b,this->flags_var);
    doPacking(b,this->version_var);
    doPacking(b,this->absSyntax_var);
    doPacking(b,this->auth_var);
    doPacking(b,this->src_var);
    doPacking(b,this->dst_var);
}

void CDAP_M_Connect::parsimUnpack(cCommBuffer *b)
{
    ::CDAPMessage::parsimUnpack(b);
    doUnpacking(b,this->opCode_var);
    doUnpacking(b,this->invokeID_var);
    doUnpacking(b,this->flags_var);
    doUnpacking(b,this->version_var);
    doUnpacking(b,this->absSyntax_var);
    doUnpacking(b,this->auth_var);
    doUnpacking(b,this->src_var);
    doUnpacking(b,this->dst_var);
}

unsigned char CDAP_M_Connect::getOpCode() const
{
    return opCode_var;
}

void CDAP_M_Connect::setOpCode(unsigned char opCode)
{
    this->opCode_var = opCode;
}

int CDAP_M_Connect::getInvokeID() const
{
    return invokeID_var;
}

void CDAP_M_Connect::setInvokeID(int invokeID)
{
    this->invokeID_var = invokeID;
}

unsigned char CDAP_M_Connect::getFlags() const
{
    return flags_var;
}

void CDAP_M_Connect::setFlags(unsigned char flags)
{
    this->flags_var = flags;
}

int CDAP_M_Connect::getVersion() const
{
    return version_var;
}

void CDAP_M_Connect::setVersion(int version)
{
    this->version_var = version;
}

int CDAP_M_Connect::getAbsSyntax() const
{
    return absSyntax_var;
}

void CDAP_M_Connect::setAbsSyntax(int absSyntax)
{
    this->absSyntax_var = absSyntax;
}

auth_t& CDAP_M_Connect::getAuth()
{
    return auth_var;
}

void CDAP_M_Connect::setAuth(const auth_t& auth)
{
    this->auth_var = auth;
}

naming_t& CDAP_M_Connect::getSrc()
{
    return src_var;
}

void CDAP_M_Connect::setSrc(const naming_t& src)
{
    this->src_var = src;
}

naming_t& CDAP_M_Connect::getDst()
{
    return dst_var;
}

void CDAP_M_Connect::setDst(const naming_t& dst)
{
    this->dst_var = dst;
}

class CDAP_M_ConnectDescriptor : public cClassDescriptor
{
  public:
    CDAP_M_ConnectDescriptor();
    virtual ~CDAP_M_ConnectDescriptor();

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

Register_ClassDescriptor(CDAP_M_ConnectDescriptor);

CDAP_M_ConnectDescriptor::CDAP_M_ConnectDescriptor() : cClassDescriptor("CDAP_M_Connect", "CDAPMessage")
{
}

CDAP_M_ConnectDescriptor::~CDAP_M_ConnectDescriptor()
{
}

bool CDAP_M_ConnectDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CDAP_M_Connect *>(obj)!=NULL;
}

const char *CDAP_M_ConnectDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CDAP_M_ConnectDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount(object) : 8;
}

unsigned int CDAP_M_ConnectDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<8) ? fieldTypeFlags[field] : 0;
}

const char *CDAP_M_ConnectDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "opCode",
        "invokeID",
        "flags",
        "version",
        "absSyntax",
        "auth",
        "src",
        "dst",
    };
    return (field>=0 && field<8) ? fieldNames[field] : NULL;
}

int CDAP_M_ConnectDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "opCode")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "invokeID")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "flags")==0) return base+2;
    if (fieldName[0]=='v' && strcmp(fieldName, "version")==0) return base+3;
    if (fieldName[0]=='a' && strcmp(fieldName, "absSyntax")==0) return base+4;
    if (fieldName[0]=='a' && strcmp(fieldName, "auth")==0) return base+5;
    if (fieldName[0]=='s' && strcmp(fieldName, "src")==0) return base+6;
    if (fieldName[0]=='d' && strcmp(fieldName, "dst")==0) return base+7;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CDAP_M_ConnectDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "int",
        "unsigned char",
        "int",
        "int",
        "auth_t",
        "naming_t",
        "naming_t",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : NULL;
}

const char *CDAP_M_ConnectDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "opCode_t";
            return NULL;
        case 2:
            if (!strcmp(propertyname,"enum")) return "flagValues_t";
            return NULL;
        case 4:
            if (!strcmp(propertyname,"enum")) return "absSyntax_t";
            return NULL;
        default: return NULL;
    }
}

int CDAP_M_ConnectDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Connect *pp = (CDAP_M_Connect *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CDAP_M_ConnectDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Connect *pp = (CDAP_M_Connect *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getOpCode());
        case 1: return long2string(pp->getInvokeID());
        case 2: return ulong2string(pp->getFlags());
        case 3: return long2string(pp->getVersion());
        case 4: return long2string(pp->getAbsSyntax());
        case 5: {std::stringstream out; out << pp->getAuth(); return out.str();}
        case 6: {std::stringstream out; out << pp->getSrc(); return out.str();}
        case 7: {std::stringstream out; out << pp->getDst(); return out.str();}
        default: return "";
    }
}

bool CDAP_M_ConnectDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Connect *pp = (CDAP_M_Connect *)object; (void)pp;
    switch (field) {
        case 0: pp->setOpCode(string2ulong(value)); return true;
        case 1: pp->setInvokeID(string2long(value)); return true;
        case 2: pp->setFlags(string2ulong(value)); return true;
        case 3: pp->setVersion(string2long(value)); return true;
        case 4: pp->setAbsSyntax(string2long(value)); return true;
        default: return false;
    }
}

const char *CDAP_M_ConnectDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 5: return opp_typename(typeid(auth_t));
        case 6: return opp_typename(typeid(naming_t));
        case 7: return opp_typename(typeid(naming_t));
        default: return NULL;
    };
}

void *CDAP_M_ConnectDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Connect *pp = (CDAP_M_Connect *)object; (void)pp;
    switch (field) {
        case 5: return (void *)(&pp->getAuth()); break;
        case 6: return (void *)(&pp->getSrc()); break;
        case 7: return (void *)(&pp->getDst()); break;
        default: return NULL;
    }
}

Register_Class(CDAP_M_Connect_R);

CDAP_M_Connect_R::CDAP_M_Connect_R(const char *name, int kind) : ::CDAPMessage(name,kind)
{
    this->opCode_var = M_CONNECT_R;
    this->invokeID_var = 0;
    this->flags_var = 0;
    this->version_var = 0;
    this->absSyntax_var = 0;
}

CDAP_M_Connect_R::CDAP_M_Connect_R(const CDAP_M_Connect_R& other) : ::CDAPMessage(other)
{
    copy(other);
}

CDAP_M_Connect_R::~CDAP_M_Connect_R()
{
}

CDAP_M_Connect_R& CDAP_M_Connect_R::operator=(const CDAP_M_Connect_R& other)
{
    if (this==&other) return *this;
    ::CDAPMessage::operator=(other);
    copy(other);
    return *this;
}

void CDAP_M_Connect_R::copy(const CDAP_M_Connect_R& other)
{
    this->opCode_var = other.opCode_var;
    this->invokeID_var = other.invokeID_var;
    this->flags_var = other.flags_var;
    this->version_var = other.version_var;
    this->result_var = other.result_var;
    this->absSyntax_var = other.absSyntax_var;
    this->auth_var = other.auth_var;
    this->src_var = other.src_var;
    this->dst_var = other.dst_var;
}

void CDAP_M_Connect_R::parsimPack(cCommBuffer *b)
{
    ::CDAPMessage::parsimPack(b);
    doPacking(b,this->opCode_var);
    doPacking(b,this->invokeID_var);
    doPacking(b,this->flags_var);
    doPacking(b,this->version_var);
    doPacking(b,this->result_var);
    doPacking(b,this->absSyntax_var);
    doPacking(b,this->auth_var);
    doPacking(b,this->src_var);
    doPacking(b,this->dst_var);
}

void CDAP_M_Connect_R::parsimUnpack(cCommBuffer *b)
{
    ::CDAPMessage::parsimUnpack(b);
    doUnpacking(b,this->opCode_var);
    doUnpacking(b,this->invokeID_var);
    doUnpacking(b,this->flags_var);
    doUnpacking(b,this->version_var);
    doUnpacking(b,this->result_var);
    doUnpacking(b,this->absSyntax_var);
    doUnpacking(b,this->auth_var);
    doUnpacking(b,this->src_var);
    doUnpacking(b,this->dst_var);
}

unsigned char CDAP_M_Connect_R::getOpCode() const
{
    return opCode_var;
}

void CDAP_M_Connect_R::setOpCode(unsigned char opCode)
{
    this->opCode_var = opCode;
}

int CDAP_M_Connect_R::getInvokeID() const
{
    return invokeID_var;
}

void CDAP_M_Connect_R::setInvokeID(int invokeID)
{
    this->invokeID_var = invokeID;
}

unsigned char CDAP_M_Connect_R::getFlags() const
{
    return flags_var;
}

void CDAP_M_Connect_R::setFlags(unsigned char flags)
{
    this->flags_var = flags;
}

int CDAP_M_Connect_R::getVersion() const
{
    return version_var;
}

void CDAP_M_Connect_R::setVersion(int version)
{
    this->version_var = version;
}

result_t& CDAP_M_Connect_R::getResult()
{
    return result_var;
}

void CDAP_M_Connect_R::setResult(const result_t& result)
{
    this->result_var = result;
}

int CDAP_M_Connect_R::getAbsSyntax() const
{
    return absSyntax_var;
}

void CDAP_M_Connect_R::setAbsSyntax(int absSyntax)
{
    this->absSyntax_var = absSyntax;
}

auth_t& CDAP_M_Connect_R::getAuth()
{
    return auth_var;
}

void CDAP_M_Connect_R::setAuth(const auth_t& auth)
{
    this->auth_var = auth;
}

naming_t& CDAP_M_Connect_R::getSrc()
{
    return src_var;
}

void CDAP_M_Connect_R::setSrc(const naming_t& src)
{
    this->src_var = src;
}

naming_t& CDAP_M_Connect_R::getDst()
{
    return dst_var;
}

void CDAP_M_Connect_R::setDst(const naming_t& dst)
{
    this->dst_var = dst;
}

class CDAP_M_Connect_RDescriptor : public cClassDescriptor
{
  public:
    CDAP_M_Connect_RDescriptor();
    virtual ~CDAP_M_Connect_RDescriptor();

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

Register_ClassDescriptor(CDAP_M_Connect_RDescriptor);

CDAP_M_Connect_RDescriptor::CDAP_M_Connect_RDescriptor() : cClassDescriptor("CDAP_M_Connect_R", "CDAPMessage")
{
}

CDAP_M_Connect_RDescriptor::~CDAP_M_Connect_RDescriptor()
{
}

bool CDAP_M_Connect_RDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CDAP_M_Connect_R *>(obj)!=NULL;
}

const char *CDAP_M_Connect_RDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CDAP_M_Connect_RDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 9+basedesc->getFieldCount(object) : 9;
}

unsigned int CDAP_M_Connect_RDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<9) ? fieldTypeFlags[field] : 0;
}

const char *CDAP_M_Connect_RDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "opCode",
        "invokeID",
        "flags",
        "version",
        "result",
        "absSyntax",
        "auth",
        "src",
        "dst",
    };
    return (field>=0 && field<9) ? fieldNames[field] : NULL;
}

int CDAP_M_Connect_RDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "opCode")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "invokeID")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "flags")==0) return base+2;
    if (fieldName[0]=='v' && strcmp(fieldName, "version")==0) return base+3;
    if (fieldName[0]=='r' && strcmp(fieldName, "result")==0) return base+4;
    if (fieldName[0]=='a' && strcmp(fieldName, "absSyntax")==0) return base+5;
    if (fieldName[0]=='a' && strcmp(fieldName, "auth")==0) return base+6;
    if (fieldName[0]=='s' && strcmp(fieldName, "src")==0) return base+7;
    if (fieldName[0]=='d' && strcmp(fieldName, "dst")==0) return base+8;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CDAP_M_Connect_RDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "int",
        "unsigned char",
        "int",
        "result_t",
        "int",
        "auth_t",
        "naming_t",
        "naming_t",
    };
    return (field>=0 && field<9) ? fieldTypeStrings[field] : NULL;
}

const char *CDAP_M_Connect_RDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "opCode_t";
            return NULL;
        case 2:
            if (!strcmp(propertyname,"enum")) return "flagValues_t";
            return NULL;
        case 5:
            if (!strcmp(propertyname,"enum")) return "absSyntax_t";
            return NULL;
        default: return NULL;
    }
}

int CDAP_M_Connect_RDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Connect_R *pp = (CDAP_M_Connect_R *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CDAP_M_Connect_RDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Connect_R *pp = (CDAP_M_Connect_R *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getOpCode());
        case 1: return long2string(pp->getInvokeID());
        case 2: return ulong2string(pp->getFlags());
        case 3: return long2string(pp->getVersion());
        case 4: {std::stringstream out; out << pp->getResult(); return out.str();}
        case 5: return long2string(pp->getAbsSyntax());
        case 6: {std::stringstream out; out << pp->getAuth(); return out.str();}
        case 7: {std::stringstream out; out << pp->getSrc(); return out.str();}
        case 8: {std::stringstream out; out << pp->getDst(); return out.str();}
        default: return "";
    }
}

bool CDAP_M_Connect_RDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Connect_R *pp = (CDAP_M_Connect_R *)object; (void)pp;
    switch (field) {
        case 0: pp->setOpCode(string2ulong(value)); return true;
        case 1: pp->setInvokeID(string2long(value)); return true;
        case 2: pp->setFlags(string2ulong(value)); return true;
        case 3: pp->setVersion(string2long(value)); return true;
        case 5: pp->setAbsSyntax(string2long(value)); return true;
        default: return false;
    }
}

const char *CDAP_M_Connect_RDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 4: return opp_typename(typeid(result_t));
        case 6: return opp_typename(typeid(auth_t));
        case 7: return opp_typename(typeid(naming_t));
        case 8: return opp_typename(typeid(naming_t));
        default: return NULL;
    };
}

void *CDAP_M_Connect_RDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Connect_R *pp = (CDAP_M_Connect_R *)object; (void)pp;
    switch (field) {
        case 4: return (void *)(&pp->getResult()); break;
        case 6: return (void *)(&pp->getAuth()); break;
        case 7: return (void *)(&pp->getSrc()); break;
        case 8: return (void *)(&pp->getDst()); break;
        default: return NULL;
    }
}

Register_Class(CDAP_M_Release);

CDAP_M_Release::CDAP_M_Release(const char *name, int kind) : ::CDAPMessage(name,kind)
{
    this->opCode_var = M_RELEASE;
    this->invokeID_var = 0;
    this->flags_var = 0;
    this->version_var = 0;
}

CDAP_M_Release::CDAP_M_Release(const CDAP_M_Release& other) : ::CDAPMessage(other)
{
    copy(other);
}

CDAP_M_Release::~CDAP_M_Release()
{
}

CDAP_M_Release& CDAP_M_Release::operator=(const CDAP_M_Release& other)
{
    if (this==&other) return *this;
    ::CDAPMessage::operator=(other);
    copy(other);
    return *this;
}

void CDAP_M_Release::copy(const CDAP_M_Release& other)
{
    this->opCode_var = other.opCode_var;
    this->invokeID_var = other.invokeID_var;
    this->flags_var = other.flags_var;
    this->version_var = other.version_var;
}

void CDAP_M_Release::parsimPack(cCommBuffer *b)
{
    ::CDAPMessage::parsimPack(b);
    doPacking(b,this->opCode_var);
    doPacking(b,this->invokeID_var);
    doPacking(b,this->flags_var);
    doPacking(b,this->version_var);
}

void CDAP_M_Release::parsimUnpack(cCommBuffer *b)
{
    ::CDAPMessage::parsimUnpack(b);
    doUnpacking(b,this->opCode_var);
    doUnpacking(b,this->invokeID_var);
    doUnpacking(b,this->flags_var);
    doUnpacking(b,this->version_var);
}

unsigned char CDAP_M_Release::getOpCode() const
{
    return opCode_var;
}

void CDAP_M_Release::setOpCode(unsigned char opCode)
{
    this->opCode_var = opCode;
}

int CDAP_M_Release::getInvokeID() const
{
    return invokeID_var;
}

void CDAP_M_Release::setInvokeID(int invokeID)
{
    this->invokeID_var = invokeID;
}

unsigned char CDAP_M_Release::getFlags() const
{
    return flags_var;
}

void CDAP_M_Release::setFlags(unsigned char flags)
{
    this->flags_var = flags;
}

int CDAP_M_Release::getVersion() const
{
    return version_var;
}

void CDAP_M_Release::setVersion(int version)
{
    this->version_var = version;
}

class CDAP_M_ReleaseDescriptor : public cClassDescriptor
{
  public:
    CDAP_M_ReleaseDescriptor();
    virtual ~CDAP_M_ReleaseDescriptor();

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

Register_ClassDescriptor(CDAP_M_ReleaseDescriptor);

CDAP_M_ReleaseDescriptor::CDAP_M_ReleaseDescriptor() : cClassDescriptor("CDAP_M_Release", "CDAPMessage")
{
}

CDAP_M_ReleaseDescriptor::~CDAP_M_ReleaseDescriptor()
{
}

bool CDAP_M_ReleaseDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CDAP_M_Release *>(obj)!=NULL;
}

const char *CDAP_M_ReleaseDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CDAP_M_ReleaseDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int CDAP_M_ReleaseDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *CDAP_M_ReleaseDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "opCode",
        "invokeID",
        "flags",
        "version",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int CDAP_M_ReleaseDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "opCode")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "invokeID")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "flags")==0) return base+2;
    if (fieldName[0]=='v' && strcmp(fieldName, "version")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CDAP_M_ReleaseDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "int",
        "unsigned char",
        "int",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *CDAP_M_ReleaseDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "opCode_t";
            return NULL;
        case 2:
            if (!strcmp(propertyname,"enum")) return "flagValues_t";
            return NULL;
        default: return NULL;
    }
}

int CDAP_M_ReleaseDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Release *pp = (CDAP_M_Release *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CDAP_M_ReleaseDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Release *pp = (CDAP_M_Release *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getOpCode());
        case 1: return long2string(pp->getInvokeID());
        case 2: return ulong2string(pp->getFlags());
        case 3: return long2string(pp->getVersion());
        default: return "";
    }
}

bool CDAP_M_ReleaseDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Release *pp = (CDAP_M_Release *)object; (void)pp;
    switch (field) {
        case 0: pp->setOpCode(string2ulong(value)); return true;
        case 1: pp->setInvokeID(string2long(value)); return true;
        case 2: pp->setFlags(string2ulong(value)); return true;
        case 3: pp->setVersion(string2long(value)); return true;
        default: return false;
    }
}

const char *CDAP_M_ReleaseDescriptor::getFieldStructName(void *object, int field) const
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

void *CDAP_M_ReleaseDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Release *pp = (CDAP_M_Release *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(CDAP_M_Release_R);

CDAP_M_Release_R::CDAP_M_Release_R(const char *name, int kind) : ::CDAPMessage(name,kind)
{
    this->opCode_var = M_RELEASE_R;
    this->invokeID_var = 0;
    this->flags_var = 0;
    this->version_var = 0;
}

CDAP_M_Release_R::CDAP_M_Release_R(const CDAP_M_Release_R& other) : ::CDAPMessage(other)
{
    copy(other);
}

CDAP_M_Release_R::~CDAP_M_Release_R()
{
}

CDAP_M_Release_R& CDAP_M_Release_R::operator=(const CDAP_M_Release_R& other)
{
    if (this==&other) return *this;
    ::CDAPMessage::operator=(other);
    copy(other);
    return *this;
}

void CDAP_M_Release_R::copy(const CDAP_M_Release_R& other)
{
    this->opCode_var = other.opCode_var;
    this->invokeID_var = other.invokeID_var;
    this->flags_var = other.flags_var;
    this->version_var = other.version_var;
    this->result_var = other.result_var;
}

void CDAP_M_Release_R::parsimPack(cCommBuffer *b)
{
    ::CDAPMessage::parsimPack(b);
    doPacking(b,this->opCode_var);
    doPacking(b,this->invokeID_var);
    doPacking(b,this->flags_var);
    doPacking(b,this->version_var);
    doPacking(b,this->result_var);
}

void CDAP_M_Release_R::parsimUnpack(cCommBuffer *b)
{
    ::CDAPMessage::parsimUnpack(b);
    doUnpacking(b,this->opCode_var);
    doUnpacking(b,this->invokeID_var);
    doUnpacking(b,this->flags_var);
    doUnpacking(b,this->version_var);
    doUnpacking(b,this->result_var);
}

unsigned char CDAP_M_Release_R::getOpCode() const
{
    return opCode_var;
}

void CDAP_M_Release_R::setOpCode(unsigned char opCode)
{
    this->opCode_var = opCode;
}

int CDAP_M_Release_R::getInvokeID() const
{
    return invokeID_var;
}

void CDAP_M_Release_R::setInvokeID(int invokeID)
{
    this->invokeID_var = invokeID;
}

unsigned char CDAP_M_Release_R::getFlags() const
{
    return flags_var;
}

void CDAP_M_Release_R::setFlags(unsigned char flags)
{
    this->flags_var = flags;
}

int CDAP_M_Release_R::getVersion() const
{
    return version_var;
}

void CDAP_M_Release_R::setVersion(int version)
{
    this->version_var = version;
}

result_t& CDAP_M_Release_R::getResult()
{
    return result_var;
}

void CDAP_M_Release_R::setResult(const result_t& result)
{
    this->result_var = result;
}

class CDAP_M_Release_RDescriptor : public cClassDescriptor
{
  public:
    CDAP_M_Release_RDescriptor();
    virtual ~CDAP_M_Release_RDescriptor();

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

Register_ClassDescriptor(CDAP_M_Release_RDescriptor);

CDAP_M_Release_RDescriptor::CDAP_M_Release_RDescriptor() : cClassDescriptor("CDAP_M_Release_R", "CDAPMessage")
{
}

CDAP_M_Release_RDescriptor::~CDAP_M_Release_RDescriptor()
{
}

bool CDAP_M_Release_RDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CDAP_M_Release_R *>(obj)!=NULL;
}

const char *CDAP_M_Release_RDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CDAP_M_Release_RDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int CDAP_M_Release_RDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *CDAP_M_Release_RDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "opCode",
        "invokeID",
        "flags",
        "version",
        "result",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int CDAP_M_Release_RDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "opCode")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "invokeID")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "flags")==0) return base+2;
    if (fieldName[0]=='v' && strcmp(fieldName, "version")==0) return base+3;
    if (fieldName[0]=='r' && strcmp(fieldName, "result")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CDAP_M_Release_RDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "int",
        "unsigned char",
        "int",
        "result_t",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *CDAP_M_Release_RDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "opCode_t";
            return NULL;
        case 2:
            if (!strcmp(propertyname,"enum")) return "flagValues_t";
            return NULL;
        default: return NULL;
    }
}

int CDAP_M_Release_RDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Release_R *pp = (CDAP_M_Release_R *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CDAP_M_Release_RDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Release_R *pp = (CDAP_M_Release_R *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getOpCode());
        case 1: return long2string(pp->getInvokeID());
        case 2: return ulong2string(pp->getFlags());
        case 3: return long2string(pp->getVersion());
        case 4: {std::stringstream out; out << pp->getResult(); return out.str();}
        default: return "";
    }
}

bool CDAP_M_Release_RDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Release_R *pp = (CDAP_M_Release_R *)object; (void)pp;
    switch (field) {
        case 0: pp->setOpCode(string2ulong(value)); return true;
        case 1: pp->setInvokeID(string2long(value)); return true;
        case 2: pp->setFlags(string2ulong(value)); return true;
        case 3: pp->setVersion(string2long(value)); return true;
        default: return false;
    }
}

const char *CDAP_M_Release_RDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 4: return opp_typename(typeid(result_t));
        default: return NULL;
    };
}

void *CDAP_M_Release_RDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Release_R *pp = (CDAP_M_Release_R *)object; (void)pp;
    switch (field) {
        case 4: return (void *)(&pp->getResult()); break;
        default: return NULL;
    }
}

Register_Class(CDAP_M_Create);

CDAP_M_Create::CDAP_M_Create(const char *name, int kind) : ::CDAPMessage(name,kind)
{
    this->opCode_var = M_CREATE;
    this->invokeID_var = 0;
    this->flags_var = 0;
    this->version_var = 0;
    this->scope_var = 0;
    this->filter_var = 0;
}

CDAP_M_Create::CDAP_M_Create(const CDAP_M_Create& other) : ::CDAPMessage(other)
{
    copy(other);
}

CDAP_M_Create::~CDAP_M_Create()
{
}

CDAP_M_Create& CDAP_M_Create::operator=(const CDAP_M_Create& other)
{
    if (this==&other) return *this;
    ::CDAPMessage::operator=(other);
    copy(other);
    return *this;
}

void CDAP_M_Create::copy(const CDAP_M_Create& other)
{
    this->opCode_var = other.opCode_var;
    this->invokeID_var = other.invokeID_var;
    this->flags_var = other.flags_var;
    this->version_var = other.version_var;
    this->object_var = other.object_var;
    this->scope_var = other.scope_var;
    this->filter_var = other.filter_var;
}

void CDAP_M_Create::parsimPack(cCommBuffer *b)
{
    ::CDAPMessage::parsimPack(b);
    doPacking(b,this->opCode_var);
    doPacking(b,this->invokeID_var);
    doPacking(b,this->flags_var);
    doPacking(b,this->version_var);
    doPacking(b,this->object_var);
    doPacking(b,this->scope_var);
    doPacking(b,this->filter_var);
}

void CDAP_M_Create::parsimUnpack(cCommBuffer *b)
{
    ::CDAPMessage::parsimUnpack(b);
    doUnpacking(b,this->opCode_var);
    doUnpacking(b,this->invokeID_var);
    doUnpacking(b,this->flags_var);
    doUnpacking(b,this->version_var);
    doUnpacking(b,this->object_var);
    doUnpacking(b,this->scope_var);
    doUnpacking(b,this->filter_var);
}

unsigned char CDAP_M_Create::getOpCode() const
{
    return opCode_var;
}

void CDAP_M_Create::setOpCode(unsigned char opCode)
{
    this->opCode_var = opCode;
}

int CDAP_M_Create::getInvokeID() const
{
    return invokeID_var;
}

void CDAP_M_Create::setInvokeID(int invokeID)
{
    this->invokeID_var = invokeID;
}

unsigned char CDAP_M_Create::getFlags() const
{
    return flags_var;
}

void CDAP_M_Create::setFlags(unsigned char flags)
{
    this->flags_var = flags;
}

int CDAP_M_Create::getVersion() const
{
    return version_var;
}

void CDAP_M_Create::setVersion(int version)
{
    this->version_var = version;
}

object_t& CDAP_M_Create::getObject()
{
    return object_var;
}

void CDAP_M_Create::setObject(const object_t& object)
{
    this->object_var = object;
}

int CDAP_M_Create::getScope() const
{
    return scope_var;
}

void CDAP_M_Create::setScope(int scope)
{
    this->scope_var = scope;
}

int CDAP_M_Create::getFilter() const
{
    return filter_var;
}

void CDAP_M_Create::setFilter(int filter)
{
    this->filter_var = filter;
}

class CDAP_M_CreateDescriptor : public cClassDescriptor
{
  public:
    CDAP_M_CreateDescriptor();
    virtual ~CDAP_M_CreateDescriptor();

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

Register_ClassDescriptor(CDAP_M_CreateDescriptor);

CDAP_M_CreateDescriptor::CDAP_M_CreateDescriptor() : cClassDescriptor("CDAP_M_Create", "CDAPMessage")
{
}

CDAP_M_CreateDescriptor::~CDAP_M_CreateDescriptor()
{
}

bool CDAP_M_CreateDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CDAP_M_Create *>(obj)!=NULL;
}

const char *CDAP_M_CreateDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CDAP_M_CreateDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int CDAP_M_CreateDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *CDAP_M_CreateDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "opCode",
        "invokeID",
        "flags",
        "version",
        "object",
        "scope",
        "filter",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int CDAP_M_CreateDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "opCode")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "invokeID")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "flags")==0) return base+2;
    if (fieldName[0]=='v' && strcmp(fieldName, "version")==0) return base+3;
    if (fieldName[0]=='o' && strcmp(fieldName, "object")==0) return base+4;
    if (fieldName[0]=='s' && strcmp(fieldName, "scope")==0) return base+5;
    if (fieldName[0]=='f' && strcmp(fieldName, "filter")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CDAP_M_CreateDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "int",
        "unsigned char",
        "int",
        "object_t",
        "int",
        "int",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *CDAP_M_CreateDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "opCode_t";
            return NULL;
        case 2:
            if (!strcmp(propertyname,"enum")) return "flagValues_t";
            return NULL;
        default: return NULL;
    }
}

int CDAP_M_CreateDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Create *pp = (CDAP_M_Create *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CDAP_M_CreateDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Create *pp = (CDAP_M_Create *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getOpCode());
        case 1: return long2string(pp->getInvokeID());
        case 2: return ulong2string(pp->getFlags());
        case 3: return long2string(pp->getVersion());
        case 4: {std::stringstream out; out << pp->getObject(); return out.str();}
        case 5: return long2string(pp->getScope());
        case 6: return long2string(pp->getFilter());
        default: return "";
    }
}

bool CDAP_M_CreateDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Create *pp = (CDAP_M_Create *)object; (void)pp;
    switch (field) {
        case 0: pp->setOpCode(string2ulong(value)); return true;
        case 1: pp->setInvokeID(string2long(value)); return true;
        case 2: pp->setFlags(string2ulong(value)); return true;
        case 3: pp->setVersion(string2long(value)); return true;
        case 5: pp->setScope(string2long(value)); return true;
        case 6: pp->setFilter(string2long(value)); return true;
        default: return false;
    }
}

const char *CDAP_M_CreateDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 4: return opp_typename(typeid(object_t));
        default: return NULL;
    };
}

void *CDAP_M_CreateDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Create *pp = (CDAP_M_Create *)object; (void)pp;
    switch (field) {
        case 4: return (void *)(&pp->getObject()); break;
        default: return NULL;
    }
}

Register_Class(CDAP_M_Create_R);

CDAP_M_Create_R::CDAP_M_Create_R(const char *name, int kind) : ::CDAPMessage(name,kind)
{
    this->opCode_var = M_CREATE_R;
    this->invokeID_var = 0;
    this->flags_var = 0;
    this->version_var = 0;
    this->filter_var = 0;
}

CDAP_M_Create_R::CDAP_M_Create_R(const CDAP_M_Create_R& other) : ::CDAPMessage(other)
{
    copy(other);
}

CDAP_M_Create_R::~CDAP_M_Create_R()
{
}

CDAP_M_Create_R& CDAP_M_Create_R::operator=(const CDAP_M_Create_R& other)
{
    if (this==&other) return *this;
    ::CDAPMessage::operator=(other);
    copy(other);
    return *this;
}

void CDAP_M_Create_R::copy(const CDAP_M_Create_R& other)
{
    this->opCode_var = other.opCode_var;
    this->invokeID_var = other.invokeID_var;
    this->flags_var = other.flags_var;
    this->version_var = other.version_var;
    this->result_var = other.result_var;
    this->object_var = other.object_var;
    this->filter_var = other.filter_var;
}

void CDAP_M_Create_R::parsimPack(cCommBuffer *b)
{
    ::CDAPMessage::parsimPack(b);
    doPacking(b,this->opCode_var);
    doPacking(b,this->invokeID_var);
    doPacking(b,this->flags_var);
    doPacking(b,this->version_var);
    doPacking(b,this->result_var);
    doPacking(b,this->object_var);
    doPacking(b,this->filter_var);
}

void CDAP_M_Create_R::parsimUnpack(cCommBuffer *b)
{
    ::CDAPMessage::parsimUnpack(b);
    doUnpacking(b,this->opCode_var);
    doUnpacking(b,this->invokeID_var);
    doUnpacking(b,this->flags_var);
    doUnpacking(b,this->version_var);
    doUnpacking(b,this->result_var);
    doUnpacking(b,this->object_var);
    doUnpacking(b,this->filter_var);
}

unsigned char CDAP_M_Create_R::getOpCode() const
{
    return opCode_var;
}

void CDAP_M_Create_R::setOpCode(unsigned char opCode)
{
    this->opCode_var = opCode;
}

int CDAP_M_Create_R::getInvokeID() const
{
    return invokeID_var;
}

void CDAP_M_Create_R::setInvokeID(int invokeID)
{
    this->invokeID_var = invokeID;
}

unsigned char CDAP_M_Create_R::getFlags() const
{
    return flags_var;
}

void CDAP_M_Create_R::setFlags(unsigned char flags)
{
    this->flags_var = flags;
}

int CDAP_M_Create_R::getVersion() const
{
    return version_var;
}

void CDAP_M_Create_R::setVersion(int version)
{
    this->version_var = version;
}

result_t& CDAP_M_Create_R::getResult()
{
    return result_var;
}

void CDAP_M_Create_R::setResult(const result_t& result)
{
    this->result_var = result;
}

object_t& CDAP_M_Create_R::getObject()
{
    return object_var;
}

void CDAP_M_Create_R::setObject(const object_t& object)
{
    this->object_var = object;
}

int CDAP_M_Create_R::getFilter() const
{
    return filter_var;
}

void CDAP_M_Create_R::setFilter(int filter)
{
    this->filter_var = filter;
}

class CDAP_M_Create_RDescriptor : public cClassDescriptor
{
  public:
    CDAP_M_Create_RDescriptor();
    virtual ~CDAP_M_Create_RDescriptor();

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

Register_ClassDescriptor(CDAP_M_Create_RDescriptor);

CDAP_M_Create_RDescriptor::CDAP_M_Create_RDescriptor() : cClassDescriptor("CDAP_M_Create_R", "CDAPMessage")
{
}

CDAP_M_Create_RDescriptor::~CDAP_M_Create_RDescriptor()
{
}

bool CDAP_M_Create_RDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CDAP_M_Create_R *>(obj)!=NULL;
}

const char *CDAP_M_Create_RDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CDAP_M_Create_RDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int CDAP_M_Create_RDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *CDAP_M_Create_RDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "opCode",
        "invokeID",
        "flags",
        "version",
        "result",
        "object",
        "filter",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int CDAP_M_Create_RDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "opCode")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "invokeID")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "flags")==0) return base+2;
    if (fieldName[0]=='v' && strcmp(fieldName, "version")==0) return base+3;
    if (fieldName[0]=='r' && strcmp(fieldName, "result")==0) return base+4;
    if (fieldName[0]=='o' && strcmp(fieldName, "object")==0) return base+5;
    if (fieldName[0]=='f' && strcmp(fieldName, "filter")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CDAP_M_Create_RDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "int",
        "unsigned char",
        "int",
        "result_t",
        "object_t",
        "int",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *CDAP_M_Create_RDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "opCode_t";
            return NULL;
        case 2:
            if (!strcmp(propertyname,"enum")) return "flagValues_t";
            return NULL;
        default: return NULL;
    }
}

int CDAP_M_Create_RDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Create_R *pp = (CDAP_M_Create_R *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CDAP_M_Create_RDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Create_R *pp = (CDAP_M_Create_R *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getOpCode());
        case 1: return long2string(pp->getInvokeID());
        case 2: return ulong2string(pp->getFlags());
        case 3: return long2string(pp->getVersion());
        case 4: {std::stringstream out; out << pp->getResult(); return out.str();}
        case 5: {std::stringstream out; out << pp->getObject(); return out.str();}
        case 6: return long2string(pp->getFilter());
        default: return "";
    }
}

bool CDAP_M_Create_RDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Create_R *pp = (CDAP_M_Create_R *)object; (void)pp;
    switch (field) {
        case 0: pp->setOpCode(string2ulong(value)); return true;
        case 1: pp->setInvokeID(string2long(value)); return true;
        case 2: pp->setFlags(string2ulong(value)); return true;
        case 3: pp->setVersion(string2long(value)); return true;
        case 6: pp->setFilter(string2long(value)); return true;
        default: return false;
    }
}

const char *CDAP_M_Create_RDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 4: return opp_typename(typeid(result_t));
        case 5: return opp_typename(typeid(object_t));
        default: return NULL;
    };
}

void *CDAP_M_Create_RDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Create_R *pp = (CDAP_M_Create_R *)object; (void)pp;
    switch (field) {
        case 4: return (void *)(&pp->getResult()); break;
        case 5: return (void *)(&pp->getObject()); break;
        default: return NULL;
    }
}

Register_Class(CDAP_M_Delete);

CDAP_M_Delete::CDAP_M_Delete(const char *name, int kind) : ::CDAPMessage(name,kind)
{
    this->opCode_var = M_DELETE;
    this->invokeID_var = 0;
    this->flags_var = 0;
    this->version_var = 0;
    this->scope_var = 0;
    this->filter_var = 0;
}

CDAP_M_Delete::CDAP_M_Delete(const CDAP_M_Delete& other) : ::CDAPMessage(other)
{
    copy(other);
}

CDAP_M_Delete::~CDAP_M_Delete()
{
}

CDAP_M_Delete& CDAP_M_Delete::operator=(const CDAP_M_Delete& other)
{
    if (this==&other) return *this;
    ::CDAPMessage::operator=(other);
    copy(other);
    return *this;
}

void CDAP_M_Delete::copy(const CDAP_M_Delete& other)
{
    this->opCode_var = other.opCode_var;
    this->invokeID_var = other.invokeID_var;
    this->flags_var = other.flags_var;
    this->version_var = other.version_var;
    this->object_var = other.object_var;
    this->scope_var = other.scope_var;
    this->filter_var = other.filter_var;
}

void CDAP_M_Delete::parsimPack(cCommBuffer *b)
{
    ::CDAPMessage::parsimPack(b);
    doPacking(b,this->opCode_var);
    doPacking(b,this->invokeID_var);
    doPacking(b,this->flags_var);
    doPacking(b,this->version_var);
    doPacking(b,this->object_var);
    doPacking(b,this->scope_var);
    doPacking(b,this->filter_var);
}

void CDAP_M_Delete::parsimUnpack(cCommBuffer *b)
{
    ::CDAPMessage::parsimUnpack(b);
    doUnpacking(b,this->opCode_var);
    doUnpacking(b,this->invokeID_var);
    doUnpacking(b,this->flags_var);
    doUnpacking(b,this->version_var);
    doUnpacking(b,this->object_var);
    doUnpacking(b,this->scope_var);
    doUnpacking(b,this->filter_var);
}

unsigned char CDAP_M_Delete::getOpCode() const
{
    return opCode_var;
}

void CDAP_M_Delete::setOpCode(unsigned char opCode)
{
    this->opCode_var = opCode;
}

int CDAP_M_Delete::getInvokeID() const
{
    return invokeID_var;
}

void CDAP_M_Delete::setInvokeID(int invokeID)
{
    this->invokeID_var = invokeID;
}

unsigned char CDAP_M_Delete::getFlags() const
{
    return flags_var;
}

void CDAP_M_Delete::setFlags(unsigned char flags)
{
    this->flags_var = flags;
}

int CDAP_M_Delete::getVersion() const
{
    return version_var;
}

void CDAP_M_Delete::setVersion(int version)
{
    this->version_var = version;
}

object_t& CDAP_M_Delete::getObject()
{
    return object_var;
}

void CDAP_M_Delete::setObject(const object_t& object)
{
    this->object_var = object;
}

int CDAP_M_Delete::getScope() const
{
    return scope_var;
}

void CDAP_M_Delete::setScope(int scope)
{
    this->scope_var = scope;
}

int CDAP_M_Delete::getFilter() const
{
    return filter_var;
}

void CDAP_M_Delete::setFilter(int filter)
{
    this->filter_var = filter;
}

class CDAP_M_DeleteDescriptor : public cClassDescriptor
{
  public:
    CDAP_M_DeleteDescriptor();
    virtual ~CDAP_M_DeleteDescriptor();

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

Register_ClassDescriptor(CDAP_M_DeleteDescriptor);

CDAP_M_DeleteDescriptor::CDAP_M_DeleteDescriptor() : cClassDescriptor("CDAP_M_Delete", "CDAPMessage")
{
}

CDAP_M_DeleteDescriptor::~CDAP_M_DeleteDescriptor()
{
}

bool CDAP_M_DeleteDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CDAP_M_Delete *>(obj)!=NULL;
}

const char *CDAP_M_DeleteDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CDAP_M_DeleteDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int CDAP_M_DeleteDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *CDAP_M_DeleteDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "opCode",
        "invokeID",
        "flags",
        "version",
        "object",
        "scope",
        "filter",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int CDAP_M_DeleteDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "opCode")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "invokeID")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "flags")==0) return base+2;
    if (fieldName[0]=='v' && strcmp(fieldName, "version")==0) return base+3;
    if (fieldName[0]=='o' && strcmp(fieldName, "object")==0) return base+4;
    if (fieldName[0]=='s' && strcmp(fieldName, "scope")==0) return base+5;
    if (fieldName[0]=='f' && strcmp(fieldName, "filter")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CDAP_M_DeleteDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "int",
        "unsigned char",
        "int",
        "object_t",
        "int",
        "int",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *CDAP_M_DeleteDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "opCode_t";
            return NULL;
        case 2:
            if (!strcmp(propertyname,"enum")) return "flagValues_t";
            return NULL;
        default: return NULL;
    }
}

int CDAP_M_DeleteDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Delete *pp = (CDAP_M_Delete *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CDAP_M_DeleteDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Delete *pp = (CDAP_M_Delete *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getOpCode());
        case 1: return long2string(pp->getInvokeID());
        case 2: return ulong2string(pp->getFlags());
        case 3: return long2string(pp->getVersion());
        case 4: {std::stringstream out; out << pp->getObject(); return out.str();}
        case 5: return long2string(pp->getScope());
        case 6: return long2string(pp->getFilter());
        default: return "";
    }
}

bool CDAP_M_DeleteDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Delete *pp = (CDAP_M_Delete *)object; (void)pp;
    switch (field) {
        case 0: pp->setOpCode(string2ulong(value)); return true;
        case 1: pp->setInvokeID(string2long(value)); return true;
        case 2: pp->setFlags(string2ulong(value)); return true;
        case 3: pp->setVersion(string2long(value)); return true;
        case 5: pp->setScope(string2long(value)); return true;
        case 6: pp->setFilter(string2long(value)); return true;
        default: return false;
    }
}

const char *CDAP_M_DeleteDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 4: return opp_typename(typeid(object_t));
        default: return NULL;
    };
}

void *CDAP_M_DeleteDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Delete *pp = (CDAP_M_Delete *)object; (void)pp;
    switch (field) {
        case 4: return (void *)(&pp->getObject()); break;
        default: return NULL;
    }
}

Register_Class(CDAP_M_Delete_R);

CDAP_M_Delete_R::CDAP_M_Delete_R(const char *name, int kind) : ::CDAPMessage(name,kind)
{
    this->opCode_var = M_DELETE_R;
    this->invokeID_var = 0;
    this->flags_var = 0;
    this->version_var = 0;
    this->filter_var = 0;
}

CDAP_M_Delete_R::CDAP_M_Delete_R(const CDAP_M_Delete_R& other) : ::CDAPMessage(other)
{
    copy(other);
}

CDAP_M_Delete_R::~CDAP_M_Delete_R()
{
}

CDAP_M_Delete_R& CDAP_M_Delete_R::operator=(const CDAP_M_Delete_R& other)
{
    if (this==&other) return *this;
    ::CDAPMessage::operator=(other);
    copy(other);
    return *this;
}

void CDAP_M_Delete_R::copy(const CDAP_M_Delete_R& other)
{
    this->opCode_var = other.opCode_var;
    this->invokeID_var = other.invokeID_var;
    this->flags_var = other.flags_var;
    this->version_var = other.version_var;
    this->result_var = other.result_var;
    this->object_var = other.object_var;
    this->filter_var = other.filter_var;
}

void CDAP_M_Delete_R::parsimPack(cCommBuffer *b)
{
    ::CDAPMessage::parsimPack(b);
    doPacking(b,this->opCode_var);
    doPacking(b,this->invokeID_var);
    doPacking(b,this->flags_var);
    doPacking(b,this->version_var);
    doPacking(b,this->result_var);
    doPacking(b,this->object_var);
    doPacking(b,this->filter_var);
}

void CDAP_M_Delete_R::parsimUnpack(cCommBuffer *b)
{
    ::CDAPMessage::parsimUnpack(b);
    doUnpacking(b,this->opCode_var);
    doUnpacking(b,this->invokeID_var);
    doUnpacking(b,this->flags_var);
    doUnpacking(b,this->version_var);
    doUnpacking(b,this->result_var);
    doUnpacking(b,this->object_var);
    doUnpacking(b,this->filter_var);
}

unsigned char CDAP_M_Delete_R::getOpCode() const
{
    return opCode_var;
}

void CDAP_M_Delete_R::setOpCode(unsigned char opCode)
{
    this->opCode_var = opCode;
}

int CDAP_M_Delete_R::getInvokeID() const
{
    return invokeID_var;
}

void CDAP_M_Delete_R::setInvokeID(int invokeID)
{
    this->invokeID_var = invokeID;
}

unsigned char CDAP_M_Delete_R::getFlags() const
{
    return flags_var;
}

void CDAP_M_Delete_R::setFlags(unsigned char flags)
{
    this->flags_var = flags;
}

int CDAP_M_Delete_R::getVersion() const
{
    return version_var;
}

void CDAP_M_Delete_R::setVersion(int version)
{
    this->version_var = version;
}

result_t& CDAP_M_Delete_R::getResult()
{
    return result_var;
}

void CDAP_M_Delete_R::setResult(const result_t& result)
{
    this->result_var = result;
}

object_t& CDAP_M_Delete_R::getObject()
{
    return object_var;
}

void CDAP_M_Delete_R::setObject(const object_t& object)
{
    this->object_var = object;
}

int CDAP_M_Delete_R::getFilter() const
{
    return filter_var;
}

void CDAP_M_Delete_R::setFilter(int filter)
{
    this->filter_var = filter;
}

class CDAP_M_Delete_RDescriptor : public cClassDescriptor
{
  public:
    CDAP_M_Delete_RDescriptor();
    virtual ~CDAP_M_Delete_RDescriptor();

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

Register_ClassDescriptor(CDAP_M_Delete_RDescriptor);

CDAP_M_Delete_RDescriptor::CDAP_M_Delete_RDescriptor() : cClassDescriptor("CDAP_M_Delete_R", "CDAPMessage")
{
}

CDAP_M_Delete_RDescriptor::~CDAP_M_Delete_RDescriptor()
{
}

bool CDAP_M_Delete_RDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CDAP_M_Delete_R *>(obj)!=NULL;
}

const char *CDAP_M_Delete_RDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CDAP_M_Delete_RDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int CDAP_M_Delete_RDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *CDAP_M_Delete_RDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "opCode",
        "invokeID",
        "flags",
        "version",
        "result",
        "object",
        "filter",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int CDAP_M_Delete_RDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "opCode")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "invokeID")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "flags")==0) return base+2;
    if (fieldName[0]=='v' && strcmp(fieldName, "version")==0) return base+3;
    if (fieldName[0]=='r' && strcmp(fieldName, "result")==0) return base+4;
    if (fieldName[0]=='o' && strcmp(fieldName, "object")==0) return base+5;
    if (fieldName[0]=='f' && strcmp(fieldName, "filter")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CDAP_M_Delete_RDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "int",
        "unsigned char",
        "int",
        "result_t",
        "object_t",
        "int",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *CDAP_M_Delete_RDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "opCode_t";
            return NULL;
        case 2:
            if (!strcmp(propertyname,"enum")) return "flagValues_t";
            return NULL;
        default: return NULL;
    }
}

int CDAP_M_Delete_RDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Delete_R *pp = (CDAP_M_Delete_R *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CDAP_M_Delete_RDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Delete_R *pp = (CDAP_M_Delete_R *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getOpCode());
        case 1: return long2string(pp->getInvokeID());
        case 2: return ulong2string(pp->getFlags());
        case 3: return long2string(pp->getVersion());
        case 4: {std::stringstream out; out << pp->getResult(); return out.str();}
        case 5: {std::stringstream out; out << pp->getObject(); return out.str();}
        case 6: return long2string(pp->getFilter());
        default: return "";
    }
}

bool CDAP_M_Delete_RDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Delete_R *pp = (CDAP_M_Delete_R *)object; (void)pp;
    switch (field) {
        case 0: pp->setOpCode(string2ulong(value)); return true;
        case 1: pp->setInvokeID(string2long(value)); return true;
        case 2: pp->setFlags(string2ulong(value)); return true;
        case 3: pp->setVersion(string2long(value)); return true;
        case 6: pp->setFilter(string2long(value)); return true;
        default: return false;
    }
}

const char *CDAP_M_Delete_RDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 4: return opp_typename(typeid(result_t));
        case 5: return opp_typename(typeid(object_t));
        default: return NULL;
    };
}

void *CDAP_M_Delete_RDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Delete_R *pp = (CDAP_M_Delete_R *)object; (void)pp;
    switch (field) {
        case 4: return (void *)(&pp->getResult()); break;
        case 5: return (void *)(&pp->getObject()); break;
        default: return NULL;
    }
}

Register_Class(CDAP_M_Read);

CDAP_M_Read::CDAP_M_Read(const char *name, int kind) : ::CDAPMessage(name,kind)
{
    this->opCode_var = M_READ;
    this->invokeID_var = 0;
    this->flags_var = 0;
    this->version_var = 0;
    this->scope_var = 0;
    this->filter_var = 0;
}

CDAP_M_Read::CDAP_M_Read(const CDAP_M_Read& other) : ::CDAPMessage(other)
{
    copy(other);
}

CDAP_M_Read::~CDAP_M_Read()
{
}

CDAP_M_Read& CDAP_M_Read::operator=(const CDAP_M_Read& other)
{
    if (this==&other) return *this;
    ::CDAPMessage::operator=(other);
    copy(other);
    return *this;
}

void CDAP_M_Read::copy(const CDAP_M_Read& other)
{
    this->opCode_var = other.opCode_var;
    this->invokeID_var = other.invokeID_var;
    this->flags_var = other.flags_var;
    this->version_var = other.version_var;
    this->object_var = other.object_var;
    this->scope_var = other.scope_var;
    this->filter_var = other.filter_var;
}

void CDAP_M_Read::parsimPack(cCommBuffer *b)
{
    ::CDAPMessage::parsimPack(b);
    doPacking(b,this->opCode_var);
    doPacking(b,this->invokeID_var);
    doPacking(b,this->flags_var);
    doPacking(b,this->version_var);
    doPacking(b,this->object_var);
    doPacking(b,this->scope_var);
    doPacking(b,this->filter_var);
}

void CDAP_M_Read::parsimUnpack(cCommBuffer *b)
{
    ::CDAPMessage::parsimUnpack(b);
    doUnpacking(b,this->opCode_var);
    doUnpacking(b,this->invokeID_var);
    doUnpacking(b,this->flags_var);
    doUnpacking(b,this->version_var);
    doUnpacking(b,this->object_var);
    doUnpacking(b,this->scope_var);
    doUnpacking(b,this->filter_var);
}

unsigned char CDAP_M_Read::getOpCode() const
{
    return opCode_var;
}

void CDAP_M_Read::setOpCode(unsigned char opCode)
{
    this->opCode_var = opCode;
}

int CDAP_M_Read::getInvokeID() const
{
    return invokeID_var;
}

void CDAP_M_Read::setInvokeID(int invokeID)
{
    this->invokeID_var = invokeID;
}

unsigned char CDAP_M_Read::getFlags() const
{
    return flags_var;
}

void CDAP_M_Read::setFlags(unsigned char flags)
{
    this->flags_var = flags;
}

int CDAP_M_Read::getVersion() const
{
    return version_var;
}

void CDAP_M_Read::setVersion(int version)
{
    this->version_var = version;
}

object_t& CDAP_M_Read::getObject()
{
    return object_var;
}

void CDAP_M_Read::setObject(const object_t& object)
{
    this->object_var = object;
}

int CDAP_M_Read::getScope() const
{
    return scope_var;
}

void CDAP_M_Read::setScope(int scope)
{
    this->scope_var = scope;
}

int CDAP_M_Read::getFilter() const
{
    return filter_var;
}

void CDAP_M_Read::setFilter(int filter)
{
    this->filter_var = filter;
}

class CDAP_M_ReadDescriptor : public cClassDescriptor
{
  public:
    CDAP_M_ReadDescriptor();
    virtual ~CDAP_M_ReadDescriptor();

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

Register_ClassDescriptor(CDAP_M_ReadDescriptor);

CDAP_M_ReadDescriptor::CDAP_M_ReadDescriptor() : cClassDescriptor("CDAP_M_Read", "CDAPMessage")
{
}

CDAP_M_ReadDescriptor::~CDAP_M_ReadDescriptor()
{
}

bool CDAP_M_ReadDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CDAP_M_Read *>(obj)!=NULL;
}

const char *CDAP_M_ReadDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CDAP_M_ReadDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int CDAP_M_ReadDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *CDAP_M_ReadDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "opCode",
        "invokeID",
        "flags",
        "version",
        "object",
        "scope",
        "filter",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int CDAP_M_ReadDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "opCode")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "invokeID")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "flags")==0) return base+2;
    if (fieldName[0]=='v' && strcmp(fieldName, "version")==0) return base+3;
    if (fieldName[0]=='o' && strcmp(fieldName, "object")==0) return base+4;
    if (fieldName[0]=='s' && strcmp(fieldName, "scope")==0) return base+5;
    if (fieldName[0]=='f' && strcmp(fieldName, "filter")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CDAP_M_ReadDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "int",
        "unsigned char",
        "int",
        "object_t",
        "int",
        "int",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *CDAP_M_ReadDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "opCode_t";
            return NULL;
        case 2:
            if (!strcmp(propertyname,"enum")) return "flagValues_t";
            return NULL;
        default: return NULL;
    }
}

int CDAP_M_ReadDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Read *pp = (CDAP_M_Read *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CDAP_M_ReadDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Read *pp = (CDAP_M_Read *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getOpCode());
        case 1: return long2string(pp->getInvokeID());
        case 2: return ulong2string(pp->getFlags());
        case 3: return long2string(pp->getVersion());
        case 4: {std::stringstream out; out << pp->getObject(); return out.str();}
        case 5: return long2string(pp->getScope());
        case 6: return long2string(pp->getFilter());
        default: return "";
    }
}

bool CDAP_M_ReadDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Read *pp = (CDAP_M_Read *)object; (void)pp;
    switch (field) {
        case 0: pp->setOpCode(string2ulong(value)); return true;
        case 1: pp->setInvokeID(string2long(value)); return true;
        case 2: pp->setFlags(string2ulong(value)); return true;
        case 3: pp->setVersion(string2long(value)); return true;
        case 5: pp->setScope(string2long(value)); return true;
        case 6: pp->setFilter(string2long(value)); return true;
        default: return false;
    }
}

const char *CDAP_M_ReadDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 4: return opp_typename(typeid(object_t));
        default: return NULL;
    };
}

void *CDAP_M_ReadDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Read *pp = (CDAP_M_Read *)object; (void)pp;
    switch (field) {
        case 4: return (void *)(&pp->getObject()); break;
        default: return NULL;
    }
}

Register_Class(CDAP_M_Read_R);

CDAP_M_Read_R::CDAP_M_Read_R(const char *name, int kind) : ::CDAPMessage(name,kind)
{
    this->opCode_var = M_READ_R;
    this->invokeID_var = 0;
    this->flags_var = 0;
    this->version_var = 0;
    this->filter_var = 0;
}

CDAP_M_Read_R::CDAP_M_Read_R(const CDAP_M_Read_R& other) : ::CDAPMessage(other)
{
    copy(other);
}

CDAP_M_Read_R::~CDAP_M_Read_R()
{
}

CDAP_M_Read_R& CDAP_M_Read_R::operator=(const CDAP_M_Read_R& other)
{
    if (this==&other) return *this;
    ::CDAPMessage::operator=(other);
    copy(other);
    return *this;
}

void CDAP_M_Read_R::copy(const CDAP_M_Read_R& other)
{
    this->opCode_var = other.opCode_var;
    this->invokeID_var = other.invokeID_var;
    this->flags_var = other.flags_var;
    this->version_var = other.version_var;
    this->result_var = other.result_var;
    this->object_var = other.object_var;
    this->filter_var = other.filter_var;
}

void CDAP_M_Read_R::parsimPack(cCommBuffer *b)
{
    ::CDAPMessage::parsimPack(b);
    doPacking(b,this->opCode_var);
    doPacking(b,this->invokeID_var);
    doPacking(b,this->flags_var);
    doPacking(b,this->version_var);
    doPacking(b,this->result_var);
    doPacking(b,this->object_var);
    doPacking(b,this->filter_var);
}

void CDAP_M_Read_R::parsimUnpack(cCommBuffer *b)
{
    ::CDAPMessage::parsimUnpack(b);
    doUnpacking(b,this->opCode_var);
    doUnpacking(b,this->invokeID_var);
    doUnpacking(b,this->flags_var);
    doUnpacking(b,this->version_var);
    doUnpacking(b,this->result_var);
    doUnpacking(b,this->object_var);
    doUnpacking(b,this->filter_var);
}

unsigned char CDAP_M_Read_R::getOpCode() const
{
    return opCode_var;
}

void CDAP_M_Read_R::setOpCode(unsigned char opCode)
{
    this->opCode_var = opCode;
}

int CDAP_M_Read_R::getInvokeID() const
{
    return invokeID_var;
}

void CDAP_M_Read_R::setInvokeID(int invokeID)
{
    this->invokeID_var = invokeID;
}

unsigned char CDAP_M_Read_R::getFlags() const
{
    return flags_var;
}

void CDAP_M_Read_R::setFlags(unsigned char flags)
{
    this->flags_var = flags;
}

int CDAP_M_Read_R::getVersion() const
{
    return version_var;
}

void CDAP_M_Read_R::setVersion(int version)
{
    this->version_var = version;
}

result_t& CDAP_M_Read_R::getResult()
{
    return result_var;
}

void CDAP_M_Read_R::setResult(const result_t& result)
{
    this->result_var = result;
}

object_t& CDAP_M_Read_R::getObject()
{
    return object_var;
}

void CDAP_M_Read_R::setObject(const object_t& object)
{
    this->object_var = object;
}

int CDAP_M_Read_R::getFilter() const
{
    return filter_var;
}

void CDAP_M_Read_R::setFilter(int filter)
{
    this->filter_var = filter;
}

class CDAP_M_Read_RDescriptor : public cClassDescriptor
{
  public:
    CDAP_M_Read_RDescriptor();
    virtual ~CDAP_M_Read_RDescriptor();

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

Register_ClassDescriptor(CDAP_M_Read_RDescriptor);

CDAP_M_Read_RDescriptor::CDAP_M_Read_RDescriptor() : cClassDescriptor("CDAP_M_Read_R", "CDAPMessage")
{
}

CDAP_M_Read_RDescriptor::~CDAP_M_Read_RDescriptor()
{
}

bool CDAP_M_Read_RDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CDAP_M_Read_R *>(obj)!=NULL;
}

const char *CDAP_M_Read_RDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CDAP_M_Read_RDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int CDAP_M_Read_RDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *CDAP_M_Read_RDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "opCode",
        "invokeID",
        "flags",
        "version",
        "result",
        "object",
        "filter",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int CDAP_M_Read_RDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "opCode")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "invokeID")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "flags")==0) return base+2;
    if (fieldName[0]=='v' && strcmp(fieldName, "version")==0) return base+3;
    if (fieldName[0]=='r' && strcmp(fieldName, "result")==0) return base+4;
    if (fieldName[0]=='o' && strcmp(fieldName, "object")==0) return base+5;
    if (fieldName[0]=='f' && strcmp(fieldName, "filter")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CDAP_M_Read_RDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "int",
        "unsigned char",
        "int",
        "result_t",
        "object_t",
        "int",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *CDAP_M_Read_RDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "opCode_t";
            return NULL;
        case 2:
            if (!strcmp(propertyname,"enum")) return "flagValues_t";
            return NULL;
        default: return NULL;
    }
}

int CDAP_M_Read_RDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Read_R *pp = (CDAP_M_Read_R *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CDAP_M_Read_RDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Read_R *pp = (CDAP_M_Read_R *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getOpCode());
        case 1: return long2string(pp->getInvokeID());
        case 2: return ulong2string(pp->getFlags());
        case 3: return long2string(pp->getVersion());
        case 4: {std::stringstream out; out << pp->getResult(); return out.str();}
        case 5: {std::stringstream out; out << pp->getObject(); return out.str();}
        case 6: return long2string(pp->getFilter());
        default: return "";
    }
}

bool CDAP_M_Read_RDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Read_R *pp = (CDAP_M_Read_R *)object; (void)pp;
    switch (field) {
        case 0: pp->setOpCode(string2ulong(value)); return true;
        case 1: pp->setInvokeID(string2long(value)); return true;
        case 2: pp->setFlags(string2ulong(value)); return true;
        case 3: pp->setVersion(string2long(value)); return true;
        case 6: pp->setFilter(string2long(value)); return true;
        default: return false;
    }
}

const char *CDAP_M_Read_RDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 4: return opp_typename(typeid(result_t));
        case 5: return opp_typename(typeid(object_t));
        default: return NULL;
    };
}

void *CDAP_M_Read_RDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Read_R *pp = (CDAP_M_Read_R *)object; (void)pp;
    switch (field) {
        case 4: return (void *)(&pp->getResult()); break;
        case 5: return (void *)(&pp->getObject()); break;
        default: return NULL;
    }
}

Register_Class(CDAP_M_CancelRead);

CDAP_M_CancelRead::CDAP_M_CancelRead(const char *name, int kind) : ::CDAPMessage(name,kind)
{
    this->opCode_var = M_CANCELREAD;
    this->invokeID_var = 0;
    this->flags_var = 0;
    this->version_var = 0;
}

CDAP_M_CancelRead::CDAP_M_CancelRead(const CDAP_M_CancelRead& other) : ::CDAPMessage(other)
{
    copy(other);
}

CDAP_M_CancelRead::~CDAP_M_CancelRead()
{
}

CDAP_M_CancelRead& CDAP_M_CancelRead::operator=(const CDAP_M_CancelRead& other)
{
    if (this==&other) return *this;
    ::CDAPMessage::operator=(other);
    copy(other);
    return *this;
}

void CDAP_M_CancelRead::copy(const CDAP_M_CancelRead& other)
{
    this->opCode_var = other.opCode_var;
    this->invokeID_var = other.invokeID_var;
    this->flags_var = other.flags_var;
    this->version_var = other.version_var;
    this->result_var = other.result_var;
}

void CDAP_M_CancelRead::parsimPack(cCommBuffer *b)
{
    ::CDAPMessage::parsimPack(b);
    doPacking(b,this->opCode_var);
    doPacking(b,this->invokeID_var);
    doPacking(b,this->flags_var);
    doPacking(b,this->version_var);
    doPacking(b,this->result_var);
}

void CDAP_M_CancelRead::parsimUnpack(cCommBuffer *b)
{
    ::CDAPMessage::parsimUnpack(b);
    doUnpacking(b,this->opCode_var);
    doUnpacking(b,this->invokeID_var);
    doUnpacking(b,this->flags_var);
    doUnpacking(b,this->version_var);
    doUnpacking(b,this->result_var);
}

unsigned char CDAP_M_CancelRead::getOpCode() const
{
    return opCode_var;
}

void CDAP_M_CancelRead::setOpCode(unsigned char opCode)
{
    this->opCode_var = opCode;
}

int CDAP_M_CancelRead::getInvokeID() const
{
    return invokeID_var;
}

void CDAP_M_CancelRead::setInvokeID(int invokeID)
{
    this->invokeID_var = invokeID;
}

unsigned char CDAP_M_CancelRead::getFlags() const
{
    return flags_var;
}

void CDAP_M_CancelRead::setFlags(unsigned char flags)
{
    this->flags_var = flags;
}

int CDAP_M_CancelRead::getVersion() const
{
    return version_var;
}

void CDAP_M_CancelRead::setVersion(int version)
{
    this->version_var = version;
}

result_t& CDAP_M_CancelRead::getResult()
{
    return result_var;
}

void CDAP_M_CancelRead::setResult(const result_t& result)
{
    this->result_var = result;
}

class CDAP_M_CancelReadDescriptor : public cClassDescriptor
{
  public:
    CDAP_M_CancelReadDescriptor();
    virtual ~CDAP_M_CancelReadDescriptor();

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

Register_ClassDescriptor(CDAP_M_CancelReadDescriptor);

CDAP_M_CancelReadDescriptor::CDAP_M_CancelReadDescriptor() : cClassDescriptor("CDAP_M_CancelRead", "CDAPMessage")
{
}

CDAP_M_CancelReadDescriptor::~CDAP_M_CancelReadDescriptor()
{
}

bool CDAP_M_CancelReadDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CDAP_M_CancelRead *>(obj)!=NULL;
}

const char *CDAP_M_CancelReadDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CDAP_M_CancelReadDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int CDAP_M_CancelReadDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *CDAP_M_CancelReadDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "opCode",
        "invokeID",
        "flags",
        "version",
        "result",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int CDAP_M_CancelReadDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "opCode")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "invokeID")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "flags")==0) return base+2;
    if (fieldName[0]=='v' && strcmp(fieldName, "version")==0) return base+3;
    if (fieldName[0]=='r' && strcmp(fieldName, "result")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CDAP_M_CancelReadDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "int",
        "unsigned char",
        "int",
        "result_t",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *CDAP_M_CancelReadDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "opCode_t";
            return NULL;
        case 2:
            if (!strcmp(propertyname,"enum")) return "flagValues_t";
            return NULL;
        default: return NULL;
    }
}

int CDAP_M_CancelReadDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_CancelRead *pp = (CDAP_M_CancelRead *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CDAP_M_CancelReadDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_CancelRead *pp = (CDAP_M_CancelRead *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getOpCode());
        case 1: return long2string(pp->getInvokeID());
        case 2: return ulong2string(pp->getFlags());
        case 3: return long2string(pp->getVersion());
        case 4: {std::stringstream out; out << pp->getResult(); return out.str();}
        default: return "";
    }
}

bool CDAP_M_CancelReadDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_CancelRead *pp = (CDAP_M_CancelRead *)object; (void)pp;
    switch (field) {
        case 0: pp->setOpCode(string2ulong(value)); return true;
        case 1: pp->setInvokeID(string2long(value)); return true;
        case 2: pp->setFlags(string2ulong(value)); return true;
        case 3: pp->setVersion(string2long(value)); return true;
        default: return false;
    }
}

const char *CDAP_M_CancelReadDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 4: return opp_typename(typeid(result_t));
        default: return NULL;
    };
}

void *CDAP_M_CancelReadDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_CancelRead *pp = (CDAP_M_CancelRead *)object; (void)pp;
    switch (field) {
        case 4: return (void *)(&pp->getResult()); break;
        default: return NULL;
    }
}

Register_Class(CDAP_M_CancelRead_R);

CDAP_M_CancelRead_R::CDAP_M_CancelRead_R(const char *name, int kind) : ::CDAPMessage(name,kind)
{
    this->opCode_var = M_CANCELREAD_R;
    this->invokeID_var = 0;
    this->flags_var = 0;
    this->version_var = 0;
}

CDAP_M_CancelRead_R::CDAP_M_CancelRead_R(const CDAP_M_CancelRead_R& other) : ::CDAPMessage(other)
{
    copy(other);
}

CDAP_M_CancelRead_R::~CDAP_M_CancelRead_R()
{
}

CDAP_M_CancelRead_R& CDAP_M_CancelRead_R::operator=(const CDAP_M_CancelRead_R& other)
{
    if (this==&other) return *this;
    ::CDAPMessage::operator=(other);
    copy(other);
    return *this;
}

void CDAP_M_CancelRead_R::copy(const CDAP_M_CancelRead_R& other)
{
    this->opCode_var = other.opCode_var;
    this->invokeID_var = other.invokeID_var;
    this->flags_var = other.flags_var;
    this->version_var = other.version_var;
    this->result_var = other.result_var;
}

void CDAP_M_CancelRead_R::parsimPack(cCommBuffer *b)
{
    ::CDAPMessage::parsimPack(b);
    doPacking(b,this->opCode_var);
    doPacking(b,this->invokeID_var);
    doPacking(b,this->flags_var);
    doPacking(b,this->version_var);
    doPacking(b,this->result_var);
}

void CDAP_M_CancelRead_R::parsimUnpack(cCommBuffer *b)
{
    ::CDAPMessage::parsimUnpack(b);
    doUnpacking(b,this->opCode_var);
    doUnpacking(b,this->invokeID_var);
    doUnpacking(b,this->flags_var);
    doUnpacking(b,this->version_var);
    doUnpacking(b,this->result_var);
}

unsigned char CDAP_M_CancelRead_R::getOpCode() const
{
    return opCode_var;
}

void CDAP_M_CancelRead_R::setOpCode(unsigned char opCode)
{
    this->opCode_var = opCode;
}

int CDAP_M_CancelRead_R::getInvokeID() const
{
    return invokeID_var;
}

void CDAP_M_CancelRead_R::setInvokeID(int invokeID)
{
    this->invokeID_var = invokeID;
}

unsigned char CDAP_M_CancelRead_R::getFlags() const
{
    return flags_var;
}

void CDAP_M_CancelRead_R::setFlags(unsigned char flags)
{
    this->flags_var = flags;
}

int CDAP_M_CancelRead_R::getVersion() const
{
    return version_var;
}

void CDAP_M_CancelRead_R::setVersion(int version)
{
    this->version_var = version;
}

result_t& CDAP_M_CancelRead_R::getResult()
{
    return result_var;
}

void CDAP_M_CancelRead_R::setResult(const result_t& result)
{
    this->result_var = result;
}

class CDAP_M_CancelRead_RDescriptor : public cClassDescriptor
{
  public:
    CDAP_M_CancelRead_RDescriptor();
    virtual ~CDAP_M_CancelRead_RDescriptor();

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

Register_ClassDescriptor(CDAP_M_CancelRead_RDescriptor);

CDAP_M_CancelRead_RDescriptor::CDAP_M_CancelRead_RDescriptor() : cClassDescriptor("CDAP_M_CancelRead_R", "CDAPMessage")
{
}

CDAP_M_CancelRead_RDescriptor::~CDAP_M_CancelRead_RDescriptor()
{
}

bool CDAP_M_CancelRead_RDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CDAP_M_CancelRead_R *>(obj)!=NULL;
}

const char *CDAP_M_CancelRead_RDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CDAP_M_CancelRead_RDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int CDAP_M_CancelRead_RDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *CDAP_M_CancelRead_RDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "opCode",
        "invokeID",
        "flags",
        "version",
        "result",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int CDAP_M_CancelRead_RDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "opCode")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "invokeID")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "flags")==0) return base+2;
    if (fieldName[0]=='v' && strcmp(fieldName, "version")==0) return base+3;
    if (fieldName[0]=='r' && strcmp(fieldName, "result")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CDAP_M_CancelRead_RDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "int",
        "unsigned char",
        "int",
        "result_t",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *CDAP_M_CancelRead_RDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "opCode_t";
            return NULL;
        case 2:
            if (!strcmp(propertyname,"enum")) return "flagValues_t";
            return NULL;
        default: return NULL;
    }
}

int CDAP_M_CancelRead_RDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_CancelRead_R *pp = (CDAP_M_CancelRead_R *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CDAP_M_CancelRead_RDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_CancelRead_R *pp = (CDAP_M_CancelRead_R *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getOpCode());
        case 1: return long2string(pp->getInvokeID());
        case 2: return ulong2string(pp->getFlags());
        case 3: return long2string(pp->getVersion());
        case 4: {std::stringstream out; out << pp->getResult(); return out.str();}
        default: return "";
    }
}

bool CDAP_M_CancelRead_RDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_CancelRead_R *pp = (CDAP_M_CancelRead_R *)object; (void)pp;
    switch (field) {
        case 0: pp->setOpCode(string2ulong(value)); return true;
        case 1: pp->setInvokeID(string2long(value)); return true;
        case 2: pp->setFlags(string2ulong(value)); return true;
        case 3: pp->setVersion(string2long(value)); return true;
        default: return false;
    }
}

const char *CDAP_M_CancelRead_RDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 4: return opp_typename(typeid(result_t));
        default: return NULL;
    };
}

void *CDAP_M_CancelRead_RDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_CancelRead_R *pp = (CDAP_M_CancelRead_R *)object; (void)pp;
    switch (field) {
        case 4: return (void *)(&pp->getResult()); break;
        default: return NULL;
    }
}

Register_Class(CDAP_M_Write);

CDAP_M_Write::CDAP_M_Write(const char *name, int kind) : ::CDAPMessage(name,kind)
{
    this->opCode_var = M_WRITE;
    this->invokeID_var = 0;
    this->flags_var = 0;
    this->version_var = 0;
    this->scope_var = 0;
    this->filter_var = 0;
}

CDAP_M_Write::CDAP_M_Write(const CDAP_M_Write& other) : ::CDAPMessage(other)
{
    copy(other);
}

CDAP_M_Write::~CDAP_M_Write()
{
}

CDAP_M_Write& CDAP_M_Write::operator=(const CDAP_M_Write& other)
{
    if (this==&other) return *this;
    ::CDAPMessage::operator=(other);
    copy(other);
    return *this;
}

void CDAP_M_Write::copy(const CDAP_M_Write& other)
{
    this->opCode_var = other.opCode_var;
    this->invokeID_var = other.invokeID_var;
    this->flags_var = other.flags_var;
    this->version_var = other.version_var;
    this->object_var = other.object_var;
    this->scope_var = other.scope_var;
    this->filter_var = other.filter_var;
}

void CDAP_M_Write::parsimPack(cCommBuffer *b)
{
    ::CDAPMessage::parsimPack(b);
    doPacking(b,this->opCode_var);
    doPacking(b,this->invokeID_var);
    doPacking(b,this->flags_var);
    doPacking(b,this->version_var);
    doPacking(b,this->object_var);
    doPacking(b,this->scope_var);
    doPacking(b,this->filter_var);
}

void CDAP_M_Write::parsimUnpack(cCommBuffer *b)
{
    ::CDAPMessage::parsimUnpack(b);
    doUnpacking(b,this->opCode_var);
    doUnpacking(b,this->invokeID_var);
    doUnpacking(b,this->flags_var);
    doUnpacking(b,this->version_var);
    doUnpacking(b,this->object_var);
    doUnpacking(b,this->scope_var);
    doUnpacking(b,this->filter_var);
}

unsigned char CDAP_M_Write::getOpCode() const
{
    return opCode_var;
}

void CDAP_M_Write::setOpCode(unsigned char opCode)
{
    this->opCode_var = opCode;
}

int CDAP_M_Write::getInvokeID() const
{
    return invokeID_var;
}

void CDAP_M_Write::setInvokeID(int invokeID)
{
    this->invokeID_var = invokeID;
}

unsigned char CDAP_M_Write::getFlags() const
{
    return flags_var;
}

void CDAP_M_Write::setFlags(unsigned char flags)
{
    this->flags_var = flags;
}

int CDAP_M_Write::getVersion() const
{
    return version_var;
}

void CDAP_M_Write::setVersion(int version)
{
    this->version_var = version;
}

object_t& CDAP_M_Write::getObject()
{
    return object_var;
}

void CDAP_M_Write::setObject(const object_t& object)
{
    this->object_var = object;
}

int CDAP_M_Write::getScope() const
{
    return scope_var;
}

void CDAP_M_Write::setScope(int scope)
{
    this->scope_var = scope;
}

int CDAP_M_Write::getFilter() const
{
    return filter_var;
}

void CDAP_M_Write::setFilter(int filter)
{
    this->filter_var = filter;
}

class CDAP_M_WriteDescriptor : public cClassDescriptor
{
  public:
    CDAP_M_WriteDescriptor();
    virtual ~CDAP_M_WriteDescriptor();

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

Register_ClassDescriptor(CDAP_M_WriteDescriptor);

CDAP_M_WriteDescriptor::CDAP_M_WriteDescriptor() : cClassDescriptor("CDAP_M_Write", "CDAPMessage")
{
}

CDAP_M_WriteDescriptor::~CDAP_M_WriteDescriptor()
{
}

bool CDAP_M_WriteDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CDAP_M_Write *>(obj)!=NULL;
}

const char *CDAP_M_WriteDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CDAP_M_WriteDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int CDAP_M_WriteDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *CDAP_M_WriteDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "opCode",
        "invokeID",
        "flags",
        "version",
        "object",
        "scope",
        "filter",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int CDAP_M_WriteDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "opCode")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "invokeID")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "flags")==0) return base+2;
    if (fieldName[0]=='v' && strcmp(fieldName, "version")==0) return base+3;
    if (fieldName[0]=='o' && strcmp(fieldName, "object")==0) return base+4;
    if (fieldName[0]=='s' && strcmp(fieldName, "scope")==0) return base+5;
    if (fieldName[0]=='f' && strcmp(fieldName, "filter")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CDAP_M_WriteDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "int",
        "unsigned char",
        "int",
        "object_t",
        "int",
        "int",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *CDAP_M_WriteDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "opCode_t";
            return NULL;
        case 2:
            if (!strcmp(propertyname,"enum")) return "flagValues_t";
            return NULL;
        default: return NULL;
    }
}

int CDAP_M_WriteDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Write *pp = (CDAP_M_Write *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CDAP_M_WriteDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Write *pp = (CDAP_M_Write *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getOpCode());
        case 1: return long2string(pp->getInvokeID());
        case 2: return ulong2string(pp->getFlags());
        case 3: return long2string(pp->getVersion());
        case 4: {std::stringstream out; out << pp->getObject(); return out.str();}
        case 5: return long2string(pp->getScope());
        case 6: return long2string(pp->getFilter());
        default: return "";
    }
}

bool CDAP_M_WriteDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Write *pp = (CDAP_M_Write *)object; (void)pp;
    switch (field) {
        case 0: pp->setOpCode(string2ulong(value)); return true;
        case 1: pp->setInvokeID(string2long(value)); return true;
        case 2: pp->setFlags(string2ulong(value)); return true;
        case 3: pp->setVersion(string2long(value)); return true;
        case 5: pp->setScope(string2long(value)); return true;
        case 6: pp->setFilter(string2long(value)); return true;
        default: return false;
    }
}

const char *CDAP_M_WriteDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 4: return opp_typename(typeid(object_t));
        default: return NULL;
    };
}

void *CDAP_M_WriteDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Write *pp = (CDAP_M_Write *)object; (void)pp;
    switch (field) {
        case 4: return (void *)(&pp->getObject()); break;
        default: return NULL;
    }
}

Register_Class(CDAP_M_Write_R);

CDAP_M_Write_R::CDAP_M_Write_R(const char *name, int kind) : ::CDAPMessage(name,kind)
{
    this->opCode_var = M_WRITE_R;
    this->invokeID_var = 0;
    this->flags_var = 0;
    this->version_var = 0;
    this->filter_var = 0;
}

CDAP_M_Write_R::CDAP_M_Write_R(const CDAP_M_Write_R& other) : ::CDAPMessage(other)
{
    copy(other);
}

CDAP_M_Write_R::~CDAP_M_Write_R()
{
}

CDAP_M_Write_R& CDAP_M_Write_R::operator=(const CDAP_M_Write_R& other)
{
    if (this==&other) return *this;
    ::CDAPMessage::operator=(other);
    copy(other);
    return *this;
}

void CDAP_M_Write_R::copy(const CDAP_M_Write_R& other)
{
    this->opCode_var = other.opCode_var;
    this->invokeID_var = other.invokeID_var;
    this->flags_var = other.flags_var;
    this->version_var = other.version_var;
    this->result_var = other.result_var;
    this->object_var = other.object_var;
    this->filter_var = other.filter_var;
}

void CDAP_M_Write_R::parsimPack(cCommBuffer *b)
{
    ::CDAPMessage::parsimPack(b);
    doPacking(b,this->opCode_var);
    doPacking(b,this->invokeID_var);
    doPacking(b,this->flags_var);
    doPacking(b,this->version_var);
    doPacking(b,this->result_var);
    doPacking(b,this->object_var);
    doPacking(b,this->filter_var);
}

void CDAP_M_Write_R::parsimUnpack(cCommBuffer *b)
{
    ::CDAPMessage::parsimUnpack(b);
    doUnpacking(b,this->opCode_var);
    doUnpacking(b,this->invokeID_var);
    doUnpacking(b,this->flags_var);
    doUnpacking(b,this->version_var);
    doUnpacking(b,this->result_var);
    doUnpacking(b,this->object_var);
    doUnpacking(b,this->filter_var);
}

unsigned char CDAP_M_Write_R::getOpCode() const
{
    return opCode_var;
}

void CDAP_M_Write_R::setOpCode(unsigned char opCode)
{
    this->opCode_var = opCode;
}

int CDAP_M_Write_R::getInvokeID() const
{
    return invokeID_var;
}

void CDAP_M_Write_R::setInvokeID(int invokeID)
{
    this->invokeID_var = invokeID;
}

unsigned char CDAP_M_Write_R::getFlags() const
{
    return flags_var;
}

void CDAP_M_Write_R::setFlags(unsigned char flags)
{
    this->flags_var = flags;
}

int CDAP_M_Write_R::getVersion() const
{
    return version_var;
}

void CDAP_M_Write_R::setVersion(int version)
{
    this->version_var = version;
}

result_t& CDAP_M_Write_R::getResult()
{
    return result_var;
}

void CDAP_M_Write_R::setResult(const result_t& result)
{
    this->result_var = result;
}

object_t& CDAP_M_Write_R::getObject()
{
    return object_var;
}

void CDAP_M_Write_R::setObject(const object_t& object)
{
    this->object_var = object;
}

int CDAP_M_Write_R::getFilter() const
{
    return filter_var;
}

void CDAP_M_Write_R::setFilter(int filter)
{
    this->filter_var = filter;
}

class CDAP_M_Write_RDescriptor : public cClassDescriptor
{
  public:
    CDAP_M_Write_RDescriptor();
    virtual ~CDAP_M_Write_RDescriptor();

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

Register_ClassDescriptor(CDAP_M_Write_RDescriptor);

CDAP_M_Write_RDescriptor::CDAP_M_Write_RDescriptor() : cClassDescriptor("CDAP_M_Write_R", "CDAPMessage")
{
}

CDAP_M_Write_RDescriptor::~CDAP_M_Write_RDescriptor()
{
}

bool CDAP_M_Write_RDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CDAP_M_Write_R *>(obj)!=NULL;
}

const char *CDAP_M_Write_RDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CDAP_M_Write_RDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int CDAP_M_Write_RDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *CDAP_M_Write_RDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "opCode",
        "invokeID",
        "flags",
        "version",
        "result",
        "object",
        "filter",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int CDAP_M_Write_RDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "opCode")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "invokeID")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "flags")==0) return base+2;
    if (fieldName[0]=='v' && strcmp(fieldName, "version")==0) return base+3;
    if (fieldName[0]=='r' && strcmp(fieldName, "result")==0) return base+4;
    if (fieldName[0]=='o' && strcmp(fieldName, "object")==0) return base+5;
    if (fieldName[0]=='f' && strcmp(fieldName, "filter")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CDAP_M_Write_RDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "int",
        "unsigned char",
        "int",
        "result_t",
        "object_t",
        "int",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *CDAP_M_Write_RDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "opCode_t";
            return NULL;
        case 2:
            if (!strcmp(propertyname,"enum")) return "flagValues_t";
            return NULL;
        default: return NULL;
    }
}

int CDAP_M_Write_RDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Write_R *pp = (CDAP_M_Write_R *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CDAP_M_Write_RDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Write_R *pp = (CDAP_M_Write_R *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getOpCode());
        case 1: return long2string(pp->getInvokeID());
        case 2: return ulong2string(pp->getFlags());
        case 3: return long2string(pp->getVersion());
        case 4: {std::stringstream out; out << pp->getResult(); return out.str();}
        case 5: {std::stringstream out; out << pp->getObject(); return out.str();}
        case 6: return long2string(pp->getFilter());
        default: return "";
    }
}

bool CDAP_M_Write_RDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Write_R *pp = (CDAP_M_Write_R *)object; (void)pp;
    switch (field) {
        case 0: pp->setOpCode(string2ulong(value)); return true;
        case 1: pp->setInvokeID(string2long(value)); return true;
        case 2: pp->setFlags(string2ulong(value)); return true;
        case 3: pp->setVersion(string2long(value)); return true;
        case 6: pp->setFilter(string2long(value)); return true;
        default: return false;
    }
}

const char *CDAP_M_Write_RDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 4: return opp_typename(typeid(result_t));
        case 5: return opp_typename(typeid(object_t));
        default: return NULL;
    };
}

void *CDAP_M_Write_RDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Write_R *pp = (CDAP_M_Write_R *)object; (void)pp;
    switch (field) {
        case 4: return (void *)(&pp->getResult()); break;
        case 5: return (void *)(&pp->getObject()); break;
        default: return NULL;
    }
}

Register_Class(CDAP_M_Start);

CDAP_M_Start::CDAP_M_Start(const char *name, int kind) : ::CDAPMessage(name,kind)
{
    this->opCode_var = M_START;
    this->invokeID_var = 0;
    this->flags_var = 0;
    this->version_var = 0;
    this->scope_var = 0;
    this->filter_var = 0;
}

CDAP_M_Start::CDAP_M_Start(const CDAP_M_Start& other) : ::CDAPMessage(other)
{
    copy(other);
}

CDAP_M_Start::~CDAP_M_Start()
{
}

CDAP_M_Start& CDAP_M_Start::operator=(const CDAP_M_Start& other)
{
    if (this==&other) return *this;
    ::CDAPMessage::operator=(other);
    copy(other);
    return *this;
}

void CDAP_M_Start::copy(const CDAP_M_Start& other)
{
    this->opCode_var = other.opCode_var;
    this->invokeID_var = other.invokeID_var;
    this->flags_var = other.flags_var;
    this->version_var = other.version_var;
    this->object_var = other.object_var;
    this->scope_var = other.scope_var;
    this->filter_var = other.filter_var;
}

void CDAP_M_Start::parsimPack(cCommBuffer *b)
{
    ::CDAPMessage::parsimPack(b);
    doPacking(b,this->opCode_var);
    doPacking(b,this->invokeID_var);
    doPacking(b,this->flags_var);
    doPacking(b,this->version_var);
    doPacking(b,this->object_var);
    doPacking(b,this->scope_var);
    doPacking(b,this->filter_var);
}

void CDAP_M_Start::parsimUnpack(cCommBuffer *b)
{
    ::CDAPMessage::parsimUnpack(b);
    doUnpacking(b,this->opCode_var);
    doUnpacking(b,this->invokeID_var);
    doUnpacking(b,this->flags_var);
    doUnpacking(b,this->version_var);
    doUnpacking(b,this->object_var);
    doUnpacking(b,this->scope_var);
    doUnpacking(b,this->filter_var);
}

unsigned char CDAP_M_Start::getOpCode() const
{
    return opCode_var;
}

void CDAP_M_Start::setOpCode(unsigned char opCode)
{
    this->opCode_var = opCode;
}

int CDAP_M_Start::getInvokeID() const
{
    return invokeID_var;
}

void CDAP_M_Start::setInvokeID(int invokeID)
{
    this->invokeID_var = invokeID;
}

unsigned char CDAP_M_Start::getFlags() const
{
    return flags_var;
}

void CDAP_M_Start::setFlags(unsigned char flags)
{
    this->flags_var = flags;
}

int CDAP_M_Start::getVersion() const
{
    return version_var;
}

void CDAP_M_Start::setVersion(int version)
{
    this->version_var = version;
}

object_t& CDAP_M_Start::getObject()
{
    return object_var;
}

void CDAP_M_Start::setObject(const object_t& object)
{
    this->object_var = object;
}

int CDAP_M_Start::getScope() const
{
    return scope_var;
}

void CDAP_M_Start::setScope(int scope)
{
    this->scope_var = scope;
}

int CDAP_M_Start::getFilter() const
{
    return filter_var;
}

void CDAP_M_Start::setFilter(int filter)
{
    this->filter_var = filter;
}

class CDAP_M_StartDescriptor : public cClassDescriptor
{
  public:
    CDAP_M_StartDescriptor();
    virtual ~CDAP_M_StartDescriptor();

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

Register_ClassDescriptor(CDAP_M_StartDescriptor);

CDAP_M_StartDescriptor::CDAP_M_StartDescriptor() : cClassDescriptor("CDAP_M_Start", "CDAPMessage")
{
}

CDAP_M_StartDescriptor::~CDAP_M_StartDescriptor()
{
}

bool CDAP_M_StartDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CDAP_M_Start *>(obj)!=NULL;
}

const char *CDAP_M_StartDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CDAP_M_StartDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int CDAP_M_StartDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *CDAP_M_StartDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "opCode",
        "invokeID",
        "flags",
        "version",
        "object",
        "scope",
        "filter",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int CDAP_M_StartDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "opCode")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "invokeID")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "flags")==0) return base+2;
    if (fieldName[0]=='v' && strcmp(fieldName, "version")==0) return base+3;
    if (fieldName[0]=='o' && strcmp(fieldName, "object")==0) return base+4;
    if (fieldName[0]=='s' && strcmp(fieldName, "scope")==0) return base+5;
    if (fieldName[0]=='f' && strcmp(fieldName, "filter")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CDAP_M_StartDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "int",
        "unsigned char",
        "int",
        "object_t",
        "int",
        "int",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *CDAP_M_StartDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "opCode_t";
            return NULL;
        case 2:
            if (!strcmp(propertyname,"enum")) return "flagValues_t";
            return NULL;
        default: return NULL;
    }
}

int CDAP_M_StartDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Start *pp = (CDAP_M_Start *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CDAP_M_StartDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Start *pp = (CDAP_M_Start *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getOpCode());
        case 1: return long2string(pp->getInvokeID());
        case 2: return ulong2string(pp->getFlags());
        case 3: return long2string(pp->getVersion());
        case 4: {std::stringstream out; out << pp->getObject(); return out.str();}
        case 5: return long2string(pp->getScope());
        case 6: return long2string(pp->getFilter());
        default: return "";
    }
}

bool CDAP_M_StartDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Start *pp = (CDAP_M_Start *)object; (void)pp;
    switch (field) {
        case 0: pp->setOpCode(string2ulong(value)); return true;
        case 1: pp->setInvokeID(string2long(value)); return true;
        case 2: pp->setFlags(string2ulong(value)); return true;
        case 3: pp->setVersion(string2long(value)); return true;
        case 5: pp->setScope(string2long(value)); return true;
        case 6: pp->setFilter(string2long(value)); return true;
        default: return false;
    }
}

const char *CDAP_M_StartDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 4: return opp_typename(typeid(object_t));
        default: return NULL;
    };
}

void *CDAP_M_StartDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Start *pp = (CDAP_M_Start *)object; (void)pp;
    switch (field) {
        case 4: return (void *)(&pp->getObject()); break;
        default: return NULL;
    }
}

Register_Class(CDAP_M_Start_R);

CDAP_M_Start_R::CDAP_M_Start_R(const char *name, int kind) : ::CDAPMessage(name,kind)
{
    this->opCode_var = M_START_R;
    this->invokeID_var = 0;
    this->flags_var = 0;
    this->version_var = 0;
    this->filter_var = 0;
}

CDAP_M_Start_R::CDAP_M_Start_R(const CDAP_M_Start_R& other) : ::CDAPMessage(other)
{
    copy(other);
}

CDAP_M_Start_R::~CDAP_M_Start_R()
{
}

CDAP_M_Start_R& CDAP_M_Start_R::operator=(const CDAP_M_Start_R& other)
{
    if (this==&other) return *this;
    ::CDAPMessage::operator=(other);
    copy(other);
    return *this;
}

void CDAP_M_Start_R::copy(const CDAP_M_Start_R& other)
{
    this->opCode_var = other.opCode_var;
    this->invokeID_var = other.invokeID_var;
    this->flags_var = other.flags_var;
    this->version_var = other.version_var;
    this->result_var = other.result_var;
    this->object_var = other.object_var;
    this->filter_var = other.filter_var;
}

void CDAP_M_Start_R::parsimPack(cCommBuffer *b)
{
    ::CDAPMessage::parsimPack(b);
    doPacking(b,this->opCode_var);
    doPacking(b,this->invokeID_var);
    doPacking(b,this->flags_var);
    doPacking(b,this->version_var);
    doPacking(b,this->result_var);
    doPacking(b,this->object_var);
    doPacking(b,this->filter_var);
}

void CDAP_M_Start_R::parsimUnpack(cCommBuffer *b)
{
    ::CDAPMessage::parsimUnpack(b);
    doUnpacking(b,this->opCode_var);
    doUnpacking(b,this->invokeID_var);
    doUnpacking(b,this->flags_var);
    doUnpacking(b,this->version_var);
    doUnpacking(b,this->result_var);
    doUnpacking(b,this->object_var);
    doUnpacking(b,this->filter_var);
}

unsigned char CDAP_M_Start_R::getOpCode() const
{
    return opCode_var;
}

void CDAP_M_Start_R::setOpCode(unsigned char opCode)
{
    this->opCode_var = opCode;
}

int CDAP_M_Start_R::getInvokeID() const
{
    return invokeID_var;
}

void CDAP_M_Start_R::setInvokeID(int invokeID)
{
    this->invokeID_var = invokeID;
}

unsigned char CDAP_M_Start_R::getFlags() const
{
    return flags_var;
}

void CDAP_M_Start_R::setFlags(unsigned char flags)
{
    this->flags_var = flags;
}

int CDAP_M_Start_R::getVersion() const
{
    return version_var;
}

void CDAP_M_Start_R::setVersion(int version)
{
    this->version_var = version;
}

result_t& CDAP_M_Start_R::getResult()
{
    return result_var;
}

void CDAP_M_Start_R::setResult(const result_t& result)
{
    this->result_var = result;
}

object_t& CDAP_M_Start_R::getObject()
{
    return object_var;
}

void CDAP_M_Start_R::setObject(const object_t& object)
{
    this->object_var = object;
}

int CDAP_M_Start_R::getFilter() const
{
    return filter_var;
}

void CDAP_M_Start_R::setFilter(int filter)
{
    this->filter_var = filter;
}

class CDAP_M_Start_RDescriptor : public cClassDescriptor
{
  public:
    CDAP_M_Start_RDescriptor();
    virtual ~CDAP_M_Start_RDescriptor();

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

Register_ClassDescriptor(CDAP_M_Start_RDescriptor);

CDAP_M_Start_RDescriptor::CDAP_M_Start_RDescriptor() : cClassDescriptor("CDAP_M_Start_R", "CDAPMessage")
{
}

CDAP_M_Start_RDescriptor::~CDAP_M_Start_RDescriptor()
{
}

bool CDAP_M_Start_RDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CDAP_M_Start_R *>(obj)!=NULL;
}

const char *CDAP_M_Start_RDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CDAP_M_Start_RDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int CDAP_M_Start_RDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *CDAP_M_Start_RDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "opCode",
        "invokeID",
        "flags",
        "version",
        "result",
        "object",
        "filter",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int CDAP_M_Start_RDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "opCode")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "invokeID")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "flags")==0) return base+2;
    if (fieldName[0]=='v' && strcmp(fieldName, "version")==0) return base+3;
    if (fieldName[0]=='r' && strcmp(fieldName, "result")==0) return base+4;
    if (fieldName[0]=='o' && strcmp(fieldName, "object")==0) return base+5;
    if (fieldName[0]=='f' && strcmp(fieldName, "filter")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CDAP_M_Start_RDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "int",
        "unsigned char",
        "int",
        "result_t",
        "object_t",
        "int",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *CDAP_M_Start_RDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "opCode_t";
            return NULL;
        case 2:
            if (!strcmp(propertyname,"enum")) return "flagValues_t";
            return NULL;
        default: return NULL;
    }
}

int CDAP_M_Start_RDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Start_R *pp = (CDAP_M_Start_R *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CDAP_M_Start_RDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Start_R *pp = (CDAP_M_Start_R *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getOpCode());
        case 1: return long2string(pp->getInvokeID());
        case 2: return ulong2string(pp->getFlags());
        case 3: return long2string(pp->getVersion());
        case 4: {std::stringstream out; out << pp->getResult(); return out.str();}
        case 5: {std::stringstream out; out << pp->getObject(); return out.str();}
        case 6: return long2string(pp->getFilter());
        default: return "";
    }
}

bool CDAP_M_Start_RDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Start_R *pp = (CDAP_M_Start_R *)object; (void)pp;
    switch (field) {
        case 0: pp->setOpCode(string2ulong(value)); return true;
        case 1: pp->setInvokeID(string2long(value)); return true;
        case 2: pp->setFlags(string2ulong(value)); return true;
        case 3: pp->setVersion(string2long(value)); return true;
        case 6: pp->setFilter(string2long(value)); return true;
        default: return false;
    }
}

const char *CDAP_M_Start_RDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 4: return opp_typename(typeid(result_t));
        case 5: return opp_typename(typeid(object_t));
        default: return NULL;
    };
}

void *CDAP_M_Start_RDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Start_R *pp = (CDAP_M_Start_R *)object; (void)pp;
    switch (field) {
        case 4: return (void *)(&pp->getResult()); break;
        case 5: return (void *)(&pp->getObject()); break;
        default: return NULL;
    }
}

Register_Class(CDAP_M_Stop);

CDAP_M_Stop::CDAP_M_Stop(const char *name, int kind) : ::CDAPMessage(name,kind)
{
    this->opCode_var = M_STOP;
    this->invokeID_var = 0;
    this->flags_var = 0;
    this->version_var = 0;
    this->scope_var = 0;
    this->filter_var = 0;
}

CDAP_M_Stop::CDAP_M_Stop(const CDAP_M_Stop& other) : ::CDAPMessage(other)
{
    copy(other);
}

CDAP_M_Stop::~CDAP_M_Stop()
{
}

CDAP_M_Stop& CDAP_M_Stop::operator=(const CDAP_M_Stop& other)
{
    if (this==&other) return *this;
    ::CDAPMessage::operator=(other);
    copy(other);
    return *this;
}

void CDAP_M_Stop::copy(const CDAP_M_Stop& other)
{
    this->opCode_var = other.opCode_var;
    this->invokeID_var = other.invokeID_var;
    this->flags_var = other.flags_var;
    this->version_var = other.version_var;
    this->object_var = other.object_var;
    this->scope_var = other.scope_var;
    this->filter_var = other.filter_var;
}

void CDAP_M_Stop::parsimPack(cCommBuffer *b)
{
    ::CDAPMessage::parsimPack(b);
    doPacking(b,this->opCode_var);
    doPacking(b,this->invokeID_var);
    doPacking(b,this->flags_var);
    doPacking(b,this->version_var);
    doPacking(b,this->object_var);
    doPacking(b,this->scope_var);
    doPacking(b,this->filter_var);
}

void CDAP_M_Stop::parsimUnpack(cCommBuffer *b)
{
    ::CDAPMessage::parsimUnpack(b);
    doUnpacking(b,this->opCode_var);
    doUnpacking(b,this->invokeID_var);
    doUnpacking(b,this->flags_var);
    doUnpacking(b,this->version_var);
    doUnpacking(b,this->object_var);
    doUnpacking(b,this->scope_var);
    doUnpacking(b,this->filter_var);
}

unsigned char CDAP_M_Stop::getOpCode() const
{
    return opCode_var;
}

void CDAP_M_Stop::setOpCode(unsigned char opCode)
{
    this->opCode_var = opCode;
}

int CDAP_M_Stop::getInvokeID() const
{
    return invokeID_var;
}

void CDAP_M_Stop::setInvokeID(int invokeID)
{
    this->invokeID_var = invokeID;
}

unsigned char CDAP_M_Stop::getFlags() const
{
    return flags_var;
}

void CDAP_M_Stop::setFlags(unsigned char flags)
{
    this->flags_var = flags;
}

int CDAP_M_Stop::getVersion() const
{
    return version_var;
}

void CDAP_M_Stop::setVersion(int version)
{
    this->version_var = version;
}

object_t& CDAP_M_Stop::getObject()
{
    return object_var;
}

void CDAP_M_Stop::setObject(const object_t& object)
{
    this->object_var = object;
}

int CDAP_M_Stop::getScope() const
{
    return scope_var;
}

void CDAP_M_Stop::setScope(int scope)
{
    this->scope_var = scope;
}

int CDAP_M_Stop::getFilter() const
{
    return filter_var;
}

void CDAP_M_Stop::setFilter(int filter)
{
    this->filter_var = filter;
}

class CDAP_M_StopDescriptor : public cClassDescriptor
{
  public:
    CDAP_M_StopDescriptor();
    virtual ~CDAP_M_StopDescriptor();

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

Register_ClassDescriptor(CDAP_M_StopDescriptor);

CDAP_M_StopDescriptor::CDAP_M_StopDescriptor() : cClassDescriptor("CDAP_M_Stop", "CDAPMessage")
{
}

CDAP_M_StopDescriptor::~CDAP_M_StopDescriptor()
{
}

bool CDAP_M_StopDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CDAP_M_Stop *>(obj)!=NULL;
}

const char *CDAP_M_StopDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CDAP_M_StopDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int CDAP_M_StopDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *CDAP_M_StopDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "opCode",
        "invokeID",
        "flags",
        "version",
        "object",
        "scope",
        "filter",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int CDAP_M_StopDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "opCode")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "invokeID")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "flags")==0) return base+2;
    if (fieldName[0]=='v' && strcmp(fieldName, "version")==0) return base+3;
    if (fieldName[0]=='o' && strcmp(fieldName, "object")==0) return base+4;
    if (fieldName[0]=='s' && strcmp(fieldName, "scope")==0) return base+5;
    if (fieldName[0]=='f' && strcmp(fieldName, "filter")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CDAP_M_StopDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "int",
        "unsigned char",
        "int",
        "object_t",
        "int",
        "int",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *CDAP_M_StopDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "opCode_t";
            return NULL;
        case 2:
            if (!strcmp(propertyname,"enum")) return "flagValues_t";
            return NULL;
        default: return NULL;
    }
}

int CDAP_M_StopDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Stop *pp = (CDAP_M_Stop *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CDAP_M_StopDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Stop *pp = (CDAP_M_Stop *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getOpCode());
        case 1: return long2string(pp->getInvokeID());
        case 2: return ulong2string(pp->getFlags());
        case 3: return long2string(pp->getVersion());
        case 4: {std::stringstream out; out << pp->getObject(); return out.str();}
        case 5: return long2string(pp->getScope());
        case 6: return long2string(pp->getFilter());
        default: return "";
    }
}

bool CDAP_M_StopDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Stop *pp = (CDAP_M_Stop *)object; (void)pp;
    switch (field) {
        case 0: pp->setOpCode(string2ulong(value)); return true;
        case 1: pp->setInvokeID(string2long(value)); return true;
        case 2: pp->setFlags(string2ulong(value)); return true;
        case 3: pp->setVersion(string2long(value)); return true;
        case 5: pp->setScope(string2long(value)); return true;
        case 6: pp->setFilter(string2long(value)); return true;
        default: return false;
    }
}

const char *CDAP_M_StopDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 4: return opp_typename(typeid(object_t));
        default: return NULL;
    };
}

void *CDAP_M_StopDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Stop *pp = (CDAP_M_Stop *)object; (void)pp;
    switch (field) {
        case 4: return (void *)(&pp->getObject()); break;
        default: return NULL;
    }
}

Register_Class(CDAP_M_Stop_R);

CDAP_M_Stop_R::CDAP_M_Stop_R(const char *name, int kind) : ::CDAPMessage(name,kind)
{
    this->opCode_var = M_STOP_R;
    this->invokeID_var = 0;
    this->flags_var = 0;
    this->version_var = 0;
    this->filter_var = 0;
}

CDAP_M_Stop_R::CDAP_M_Stop_R(const CDAP_M_Stop_R& other) : ::CDAPMessage(other)
{
    copy(other);
}

CDAP_M_Stop_R::~CDAP_M_Stop_R()
{
}

CDAP_M_Stop_R& CDAP_M_Stop_R::operator=(const CDAP_M_Stop_R& other)
{
    if (this==&other) return *this;
    ::CDAPMessage::operator=(other);
    copy(other);
    return *this;
}

void CDAP_M_Stop_R::copy(const CDAP_M_Stop_R& other)
{
    this->opCode_var = other.opCode_var;
    this->invokeID_var = other.invokeID_var;
    this->flags_var = other.flags_var;
    this->version_var = other.version_var;
    this->result_var = other.result_var;
    this->object_var = other.object_var;
    this->filter_var = other.filter_var;
}

void CDAP_M_Stop_R::parsimPack(cCommBuffer *b)
{
    ::CDAPMessage::parsimPack(b);
    doPacking(b,this->opCode_var);
    doPacking(b,this->invokeID_var);
    doPacking(b,this->flags_var);
    doPacking(b,this->version_var);
    doPacking(b,this->result_var);
    doPacking(b,this->object_var);
    doPacking(b,this->filter_var);
}

void CDAP_M_Stop_R::parsimUnpack(cCommBuffer *b)
{
    ::CDAPMessage::parsimUnpack(b);
    doUnpacking(b,this->opCode_var);
    doUnpacking(b,this->invokeID_var);
    doUnpacking(b,this->flags_var);
    doUnpacking(b,this->version_var);
    doUnpacking(b,this->result_var);
    doUnpacking(b,this->object_var);
    doUnpacking(b,this->filter_var);
}

unsigned char CDAP_M_Stop_R::getOpCode() const
{
    return opCode_var;
}

void CDAP_M_Stop_R::setOpCode(unsigned char opCode)
{
    this->opCode_var = opCode;
}

int CDAP_M_Stop_R::getInvokeID() const
{
    return invokeID_var;
}

void CDAP_M_Stop_R::setInvokeID(int invokeID)
{
    this->invokeID_var = invokeID;
}

unsigned char CDAP_M_Stop_R::getFlags() const
{
    return flags_var;
}

void CDAP_M_Stop_R::setFlags(unsigned char flags)
{
    this->flags_var = flags;
}

int CDAP_M_Stop_R::getVersion() const
{
    return version_var;
}

void CDAP_M_Stop_R::setVersion(int version)
{
    this->version_var = version;
}

result_t& CDAP_M_Stop_R::getResult()
{
    return result_var;
}

void CDAP_M_Stop_R::setResult(const result_t& result)
{
    this->result_var = result;
}

object_t& CDAP_M_Stop_R::getObject()
{
    return object_var;
}

void CDAP_M_Stop_R::setObject(const object_t& object)
{
    this->object_var = object;
}

int CDAP_M_Stop_R::getFilter() const
{
    return filter_var;
}

void CDAP_M_Stop_R::setFilter(int filter)
{
    this->filter_var = filter;
}

class CDAP_M_Stop_RDescriptor : public cClassDescriptor
{
  public:
    CDAP_M_Stop_RDescriptor();
    virtual ~CDAP_M_Stop_RDescriptor();

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

Register_ClassDescriptor(CDAP_M_Stop_RDescriptor);

CDAP_M_Stop_RDescriptor::CDAP_M_Stop_RDescriptor() : cClassDescriptor("CDAP_M_Stop_R", "CDAPMessage")
{
}

CDAP_M_Stop_RDescriptor::~CDAP_M_Stop_RDescriptor()
{
}

bool CDAP_M_Stop_RDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CDAP_M_Stop_R *>(obj)!=NULL;
}

const char *CDAP_M_Stop_RDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CDAP_M_Stop_RDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int CDAP_M_Stop_RDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *CDAP_M_Stop_RDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "opCode",
        "invokeID",
        "flags",
        "version",
        "result",
        "object",
        "filter",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int CDAP_M_Stop_RDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "opCode")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "invokeID")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "flags")==0) return base+2;
    if (fieldName[0]=='v' && strcmp(fieldName, "version")==0) return base+3;
    if (fieldName[0]=='r' && strcmp(fieldName, "result")==0) return base+4;
    if (fieldName[0]=='o' && strcmp(fieldName, "object")==0) return base+5;
    if (fieldName[0]=='f' && strcmp(fieldName, "filter")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CDAP_M_Stop_RDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "int",
        "unsigned char",
        "int",
        "result_t",
        "object_t",
        "int",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *CDAP_M_Stop_RDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "opCode_t";
            return NULL;
        case 2:
            if (!strcmp(propertyname,"enum")) return "flagValues_t";
            return NULL;
        default: return NULL;
    }
}

int CDAP_M_Stop_RDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Stop_R *pp = (CDAP_M_Stop_R *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CDAP_M_Stop_RDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Stop_R *pp = (CDAP_M_Stop_R *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getOpCode());
        case 1: return long2string(pp->getInvokeID());
        case 2: return ulong2string(pp->getFlags());
        case 3: return long2string(pp->getVersion());
        case 4: {std::stringstream out; out << pp->getResult(); return out.str();}
        case 5: {std::stringstream out; out << pp->getObject(); return out.str();}
        case 6: return long2string(pp->getFilter());
        default: return "";
    }
}

bool CDAP_M_Stop_RDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Stop_R *pp = (CDAP_M_Stop_R *)object; (void)pp;
    switch (field) {
        case 0: pp->setOpCode(string2ulong(value)); return true;
        case 1: pp->setInvokeID(string2long(value)); return true;
        case 2: pp->setFlags(string2ulong(value)); return true;
        case 3: pp->setVersion(string2long(value)); return true;
        case 6: pp->setFilter(string2long(value)); return true;
        default: return false;
    }
}

const char *CDAP_M_Stop_RDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 4: return opp_typename(typeid(result_t));
        case 5: return opp_typename(typeid(object_t));
        default: return NULL;
    };
}

void *CDAP_M_Stop_RDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CDAP_M_Stop_R *pp = (CDAP_M_Stop_R *)object; (void)pp;
    switch (field) {
        case 4: return (void *)(&pp->getResult()); break;
        case 5: return (void *)(&pp->getObject()); break;
        default: return NULL;
    }
}


