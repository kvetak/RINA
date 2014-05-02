//
// Generated file, do not edit! Created by opp_msgc 4.4 from DAF/CDAP/CDAPMessage.msg.
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

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




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
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<7) ? fieldStructNames[field] : NULL;
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
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
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

Register_Class(CDAPMessage);

CDAPMessage::CDAPMessage(const char *name, int kind) : ::cMessage(name,kind)
{
    this->absSyntax_var = 0;
    this->opCode_var = 0;
    this->invokeID_var = 0;
    this->flags_var = 0;
    this->objClass_var = 0;
    this->objName_var = 0;
    this->objInst_var = 0;
    this->result_var = 0;
    this->scope_var = 0;
    this->authMech_var = 0;
    this->destAEInst_var = 0;
    this->destAEName_var = 0;
    this->destApInst_var = 0;
    this->destApName_var = 0;
    this->srcAEInst_var = 0;
    this->srcAEName_var = 0;
    this->srcApInst_var = 0;
    this->srcApName_var = 0;
    this->resultReason_var = 0;
    this->version_var = 0;
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
    this->absSyntax_var = other.absSyntax_var;
    this->opCode_var = other.opCode_var;
    this->invokeID_var = other.invokeID_var;
    this->flags_var = other.flags_var;
    this->objClass_var = other.objClass_var;
    this->objName_var = other.objName_var;
    this->objInst_var = other.objInst_var;
    this->objValue_var = other.objValue_var;
    this->result_var = other.result_var;
    this->scope_var = other.scope_var;
    this->authMech_var = other.authMech_var;
    this->authValue_var = other.authValue_var;
    this->destAEInst_var = other.destAEInst_var;
    this->destAEName_var = other.destAEName_var;
    this->destApInst_var = other.destApInst_var;
    this->destApName_var = other.destApName_var;
    this->srcAEInst_var = other.srcAEInst_var;
    this->srcAEName_var = other.srcAEName_var;
    this->srcApInst_var = other.srcApInst_var;
    this->srcApName_var = other.srcApName_var;
    this->resultReason_var = other.resultReason_var;
    this->version_var = other.version_var;
}

void CDAPMessage::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->absSyntax_var);
    doPacking(b,this->opCode_var);
    doPacking(b,this->invokeID_var);
    doPacking(b,this->flags_var);
    doPacking(b,this->objClass_var);
    doPacking(b,this->objName_var);
    doPacking(b,this->objInst_var);
    doPacking(b,this->objValue_var);
    doPacking(b,this->result_var);
    doPacking(b,this->scope_var);
    doPacking(b,this->authMech_var);
    doPacking(b,this->authValue_var);
    doPacking(b,this->destAEInst_var);
    doPacking(b,this->destAEName_var);
    doPacking(b,this->destApInst_var);
    doPacking(b,this->destApName_var);
    doPacking(b,this->srcAEInst_var);
    doPacking(b,this->srcAEName_var);
    doPacking(b,this->srcApInst_var);
    doPacking(b,this->srcApName_var);
    doPacking(b,this->resultReason_var);
    doPacking(b,this->version_var);
}

void CDAPMessage::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->absSyntax_var);
    doUnpacking(b,this->opCode_var);
    doUnpacking(b,this->invokeID_var);
    doUnpacking(b,this->flags_var);
    doUnpacking(b,this->objClass_var);
    doUnpacking(b,this->objName_var);
    doUnpacking(b,this->objInst_var);
    doUnpacking(b,this->objValue_var);
    doUnpacking(b,this->result_var);
    doUnpacking(b,this->scope_var);
    doUnpacking(b,this->authMech_var);
    doUnpacking(b,this->authValue_var);
    doUnpacking(b,this->destAEInst_var);
    doUnpacking(b,this->destAEName_var);
    doUnpacking(b,this->destApInst_var);
    doUnpacking(b,this->destApName_var);
    doUnpacking(b,this->srcAEInst_var);
    doUnpacking(b,this->srcAEName_var);
    doUnpacking(b,this->srcApInst_var);
    doUnpacking(b,this->srcApName_var);
    doUnpacking(b,this->resultReason_var);
    doUnpacking(b,this->version_var);
}

uint32 CDAPMessage::getAbsSyntax() const
{
    return absSyntax_var;
}

void CDAPMessage::setAbsSyntax(uint32 absSyntax)
{
    this->absSyntax_var = absSyntax;
}

unsigned char CDAPMessage::getOpCode() const
{
    return opCode_var;
}

void CDAPMessage::setOpCode(unsigned char opCode)
{
    this->opCode_var = opCode;
}

uint32 CDAPMessage::getInvokeID() const
{
    return invokeID_var;
}

void CDAPMessage::setInvokeID(uint32 invokeID)
{
    this->invokeID_var = invokeID;
}

unsigned char CDAPMessage::getFlags() const
{
    return flags_var;
}

void CDAPMessage::setFlags(unsigned char flags)
{
    this->flags_var = flags;
}

const char * CDAPMessage::getObjClass() const
{
    return objClass_var.c_str();
}

void CDAPMessage::setObjClass(const char * objClass)
{
    this->objClass_var = objClass;
}

const char * CDAPMessage::getObjName() const
{
    return objName_var.c_str();
}

void CDAPMessage::setObjName(const char * objName)
{
    this->objName_var = objName;
}

uint64 CDAPMessage::getObjInst() const
{
    return objInst_var;
}

void CDAPMessage::setObjInst(uint64 objInst)
{
    this->objInst_var = objInst;
}

objVal_t& CDAPMessage::getObjValue()
{
    return objValue_var;
}

void CDAPMessage::setObjValue(const objVal_t& objValue)
{
    this->objValue_var = objValue;
}

uint32 CDAPMessage::getResult() const
{
    return result_var;
}

void CDAPMessage::setResult(uint32 result)
{
    this->result_var = result;
}

uint32 CDAPMessage::getScope() const
{
    return scope_var;
}

void CDAPMessage::setScope(uint32 scope)
{
    this->scope_var = scope;
}

unsigned char CDAPMessage::getAuthMech() const
{
    return authMech_var;
}

void CDAPMessage::setAuthMech(unsigned char authMech)
{
    this->authMech_var = authMech;
}

authValue_t& CDAPMessage::getAuthValue()
{
    return authValue_var;
}

void CDAPMessage::setAuthValue(const authValue_t& authValue)
{
    this->authValue_var = authValue;
}

const char * CDAPMessage::getDestAEInst() const
{
    return destAEInst_var.c_str();
}

void CDAPMessage::setDestAEInst(const char * destAEInst)
{
    this->destAEInst_var = destAEInst;
}

const char * CDAPMessage::getDestAEName() const
{
    return destAEName_var.c_str();
}

void CDAPMessage::setDestAEName(const char * destAEName)
{
    this->destAEName_var = destAEName;
}

const char * CDAPMessage::getDestApInst() const
{
    return destApInst_var.c_str();
}

void CDAPMessage::setDestApInst(const char * destApInst)
{
    this->destApInst_var = destApInst;
}

const char * CDAPMessage::getDestApName() const
{
    return destApName_var.c_str();
}

void CDAPMessage::setDestApName(const char * destApName)
{
    this->destApName_var = destApName;
}

const char * CDAPMessage::getSrcAEInst() const
{
    return srcAEInst_var.c_str();
}

void CDAPMessage::setSrcAEInst(const char * srcAEInst)
{
    this->srcAEInst_var = srcAEInst;
}

const char * CDAPMessage::getSrcAEName() const
{
    return srcAEName_var.c_str();
}

void CDAPMessage::setSrcAEName(const char * srcAEName)
{
    this->srcAEName_var = srcAEName;
}

const char * CDAPMessage::getSrcApInst() const
{
    return srcApInst_var.c_str();
}

void CDAPMessage::setSrcApInst(const char * srcApInst)
{
    this->srcApInst_var = srcApInst;
}

const char * CDAPMessage::getSrcApName() const
{
    return srcApName_var.c_str();
}

void CDAPMessage::setSrcApName(const char * srcApName)
{
    this->srcApName_var = srcApName;
}

const char * CDAPMessage::getResultReason() const
{
    return resultReason_var.c_str();
}

void CDAPMessage::setResultReason(const char * resultReason)
{
    this->resultReason_var = resultReason;
}

int64 CDAPMessage::getVersion() const
{
    return version_var;
}

void CDAPMessage::setVersion(int64 version)
{
    this->version_var = version;
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
    return basedesc ? 22+basedesc->getFieldCount(object) : 22;
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<22) ? fieldTypeFlags[field] : 0;
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
        "absSyntax",
        "opCode",
        "invokeID",
        "flags",
        "objClass",
        "objName",
        "objInst",
        "objValue",
        "result",
        "scope",
        "authMech",
        "authValue",
        "destAEInst",
        "destAEName",
        "destApInst",
        "destApName",
        "srcAEInst",
        "srcAEName",
        "srcApInst",
        "srcApName",
        "resultReason",
        "version",
    };
    return (field>=0 && field<22) ? fieldNames[field] : NULL;
}

int CDAPMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='a' && strcmp(fieldName, "absSyntax")==0) return base+0;
    if (fieldName[0]=='o' && strcmp(fieldName, "opCode")==0) return base+1;
    if (fieldName[0]=='i' && strcmp(fieldName, "invokeID")==0) return base+2;
    if (fieldName[0]=='f' && strcmp(fieldName, "flags")==0) return base+3;
    if (fieldName[0]=='o' && strcmp(fieldName, "objClass")==0) return base+4;
    if (fieldName[0]=='o' && strcmp(fieldName, "objName")==0) return base+5;
    if (fieldName[0]=='o' && strcmp(fieldName, "objInst")==0) return base+6;
    if (fieldName[0]=='o' && strcmp(fieldName, "objValue")==0) return base+7;
    if (fieldName[0]=='r' && strcmp(fieldName, "result")==0) return base+8;
    if (fieldName[0]=='s' && strcmp(fieldName, "scope")==0) return base+9;
    if (fieldName[0]=='a' && strcmp(fieldName, "authMech")==0) return base+10;
    if (fieldName[0]=='a' && strcmp(fieldName, "authValue")==0) return base+11;
    if (fieldName[0]=='d' && strcmp(fieldName, "destAEInst")==0) return base+12;
    if (fieldName[0]=='d' && strcmp(fieldName, "destAEName")==0) return base+13;
    if (fieldName[0]=='d' && strcmp(fieldName, "destApInst")==0) return base+14;
    if (fieldName[0]=='d' && strcmp(fieldName, "destApName")==0) return base+15;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcAEInst")==0) return base+16;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcAEName")==0) return base+17;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcApInst")==0) return base+18;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcApName")==0) return base+19;
    if (fieldName[0]=='r' && strcmp(fieldName, "resultReason")==0) return base+20;
    if (fieldName[0]=='v' && strcmp(fieldName, "version")==0) return base+21;
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
        "uint32",
        "unsigned char",
        "uint32",
        "unsigned char",
        "string",
        "string",
        "uint64",
        "objVal_t",
        "uint32",
        "uint32",
        "unsigned char",
        "authValue_t",
        "string",
        "string",
        "string",
        "string",
        "string",
        "string",
        "string",
        "string",
        "string",
        "int64",
    };
    return (field>=0 && field<22) ? fieldTypeStrings[field] : NULL;
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
        case 1:
            if (!strcmp(propertyname,"enum")) return "opCode_t";
            return NULL;
        case 3:
            if (!strcmp(propertyname,"enum")) return "flagValues_t";
            return NULL;
        case 10:
            if (!strcmp(propertyname,"enum")) return "authTypes_t";
            return NULL;
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
        case 0: return ulong2string(pp->getAbsSyntax());
        case 1: return ulong2string(pp->getOpCode());
        case 2: return ulong2string(pp->getInvokeID());
        case 3: return ulong2string(pp->getFlags());
        case 4: return oppstring2string(pp->getObjClass());
        case 5: return oppstring2string(pp->getObjName());
        case 6: return uint642string(pp->getObjInst());
        case 7: {std::stringstream out; out << pp->getObjValue(); return out.str();}
        case 8: return ulong2string(pp->getResult());
        case 9: return ulong2string(pp->getScope());
        case 10: return ulong2string(pp->getAuthMech());
        case 11: {std::stringstream out; out << pp->getAuthValue(); return out.str();}
        case 12: return oppstring2string(pp->getDestAEInst());
        case 13: return oppstring2string(pp->getDestAEName());
        case 14: return oppstring2string(pp->getDestApInst());
        case 15: return oppstring2string(pp->getDestApName());
        case 16: return oppstring2string(pp->getSrcAEInst());
        case 17: return oppstring2string(pp->getSrcAEName());
        case 18: return oppstring2string(pp->getSrcApInst());
        case 19: return oppstring2string(pp->getSrcApName());
        case 20: return oppstring2string(pp->getResultReason());
        case 21: return int642string(pp->getVersion());
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
        case 0: pp->setAbsSyntax(string2ulong(value)); return true;
        case 1: pp->setOpCode(string2ulong(value)); return true;
        case 2: pp->setInvokeID(string2ulong(value)); return true;
        case 3: pp->setFlags(string2ulong(value)); return true;
        case 4: pp->setObjClass((value)); return true;
        case 5: pp->setObjName((value)); return true;
        case 6: pp->setObjInst(string2uint64(value)); return true;
        case 8: pp->setResult(string2ulong(value)); return true;
        case 9: pp->setScope(string2ulong(value)); return true;
        case 10: pp->setAuthMech(string2ulong(value)); return true;
        case 12: pp->setDestAEInst((value)); return true;
        case 13: pp->setDestAEName((value)); return true;
        case 14: pp->setDestApInst((value)); return true;
        case 15: pp->setDestApName((value)); return true;
        case 16: pp->setSrcAEInst((value)); return true;
        case 17: pp->setSrcAEName((value)); return true;
        case 18: pp->setSrcApInst((value)); return true;
        case 19: pp->setSrcApName((value)); return true;
        case 20: pp->setResultReason((value)); return true;
        case 21: pp->setVersion(string2int64(value)); return true;
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
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        "objVal_t",
        NULL,
        NULL,
        NULL,
        "authValue_t",
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<22) ? fieldStructNames[field] : NULL;
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
        case 7: return (void *)(&pp->getObjValue()); break;
        case 11: return (void *)(&pp->getAuthValue()); break;
        default: return NULL;
    }
}


