//
// Generated file, do not edit! Created by opp_msgc 4.4 from Common/PDU.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "PDU_m.h"

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
    cEnum *e = cEnum::find("PDUType");
    if (!e) enums.getInstance()->add(e = new cEnum("PDUType"));
    e->insert(EFCP_PDU, "EFCP_PDU");
    e->insert(DATA_TRANSFER_PDU, "DATA_TRANSFER_PDU");
    e->insert(CONTROL_ACK_PDU, "CONTROL_ACK_PDU");
    e->insert(ACK_ONLY_PDU, "ACK_ONLY_PDU");
    e->insert(NACK_ONLY_PDU, "NACK_ONLY_PDU");
    e->insert(SELECT_ACK_PDU, "SELECT_ACK_PDU");
    e->insert(SELECT_NACK_PDU, "SELECT_NACK_PDU");
    e->insert(FLOW_ONLY_PDU, "FLOW_ONLY_PDU");
    e->insert(ACK_FLOW_PDU, "ACK_FLOW_PDU");
    e->insert(NACK_FLOW_PDU, "NACK_FLOW_PDU");
    e->insert(SELECT_ACK_FLOW_PDU, "SELECT_ACK_FLOW_PDU");
    e->insert(SELECT_NACK_FLOW_PDU, "SELECT_NACK_FLOW_PDU");
);

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("FLAGS");
    if (!e) enums.getInstance()->add(e = new cEnum("FLAGS"));
);

PDU_Base::PDU_Base(const char *name, int kind) : ::cPacket(name,kind)
{
    this->version_var = 1;
    this->type_var = 0;
    this->flags_var = 0;
    this->pduLen_var = PDU_HEADER_LEN;
    this->seqNum_var = 0;
    userData_arraysize = 0;
    this->userData_var = 0;
}

PDU_Base::PDU_Base(const PDU_Base& other) : ::cPacket(other)
{
    userData_arraysize = 0;
    this->userData_var = 0;
    copy(other);
}

PDU_Base::~PDU_Base()
{
    delete [] userData_var;
}

PDU_Base& PDU_Base::operator=(const PDU_Base& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void PDU_Base::copy(const PDU_Base& other)
{
    this->version_var = other.version_var;
    this->destAddr_var = other.destAddr_var;
    this->srcAddr_var = other.srcAddr_var;
    this->connId_var = other.connId_var;
    this->type_var = other.type_var;
    this->flags_var = other.flags_var;
    this->pduLen_var = other.pduLen_var;
    this->seqNum_var = other.seqNum_var;
    delete [] this->userData_var;
    this->userData_var = (other.userData_arraysize==0) ? NULL : new unsigned char[other.userData_arraysize];
    userData_arraysize = other.userData_arraysize;
    for (unsigned int i=0; i<userData_arraysize; i++)
        this->userData_var[i] = other.userData_var[i];
}

void PDU_Base::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->version_var);
    doPacking(b,this->destAddr_var);
    doPacking(b,this->srcAddr_var);
    doPacking(b,this->connId_var);
    doPacking(b,this->type_var);
    doPacking(b,this->flags_var);
    doPacking(b,this->pduLen_var);
    doPacking(b,this->seqNum_var);
    b->pack(userData_arraysize);
    doPacking(b,this->userData_var,userData_arraysize);
}

void PDU_Base::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->version_var);
    doUnpacking(b,this->destAddr_var);
    doUnpacking(b,this->srcAddr_var);
    doUnpacking(b,this->connId_var);
    doUnpacking(b,this->type_var);
    doUnpacking(b,this->flags_var);
    doUnpacking(b,this->pduLen_var);
    doUnpacking(b,this->seqNum_var);
    delete [] this->userData_var;
    b->unpack(userData_arraysize);
    if (userData_arraysize==0) {
        this->userData_var = 0;
    } else {
        this->userData_var = new unsigned char[userData_arraysize];
        doUnpacking(b,this->userData_var,userData_arraysize);
    }
}

unsigned int PDU_Base::getVersion() const
{
    return version_var;
}

void PDU_Base::setVersion(unsigned int version)
{
    this->version_var = version;
}

APN& PDU_Base::getDestAddr()
{
    return destAddr_var;
}

void PDU_Base::setDestAddr(const APN& destAddr)
{
    this->destAddr_var = destAddr;
}

APN& PDU_Base::getSrcAddr()
{
    return srcAddr_var;
}

void PDU_Base::setSrcAddr(const APN& srcAddr)
{
    this->srcAddr_var = srcAddr;
}

ConnectionId& PDU_Base::getConnId()
{
    return connId_var;
}

void PDU_Base::setConnId(const ConnectionId& connId)
{
    this->connId_var = connId;
}

int PDU_Base::getType() const
{
    return type_var;
}

void PDU_Base::setType(int type)
{
    this->type_var = type;
}

int PDU_Base::getFlags() const
{
    return flags_var;
}

void PDU_Base::setFlags(int flags)
{
    this->flags_var = flags;
}

unsigned int PDU_Base::getPduLen() const
{
    return pduLen_var;
}

void PDU_Base::setPduLen(unsigned int pduLen)
{
    this->pduLen_var = pduLen;
}

unsigned int PDU_Base::getSeqNum() const
{
    return seqNum_var;
}

void PDU_Base::setSeqNum(unsigned int seqNum)
{
    this->seqNum_var = seqNum;
}

void PDU_Base::setUserDataArraySize(unsigned int size)
{
    unsigned char *userData_var2 = (size==0) ? NULL : new unsigned char[size];
    unsigned int sz = userData_arraysize < size ? userData_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        userData_var2[i] = this->userData_var[i];
    for (unsigned int i=sz; i<size; i++)
        userData_var2[i] = 0;
    userData_arraysize = size;
    delete [] this->userData_var;
    this->userData_var = userData_var2;
}

unsigned int PDU_Base::getUserDataArraySize() const
{
    return userData_arraysize;
}

unsigned char PDU_Base::getUserData(unsigned int k) const
{
    if (k>=userData_arraysize) throw cRuntimeError("Array of size %d indexed by %d", userData_arraysize, k);
    return userData_var[k];
}

void PDU_Base::setUserData(unsigned int k, unsigned char userData)
{
    if (k>=userData_arraysize) throw cRuntimeError("Array of size %d indexed by %d", userData_arraysize, k);
    this->userData_var[k] = userData;
}

class PDUDescriptor : public cClassDescriptor
{
  public:
    PDUDescriptor();
    virtual ~PDUDescriptor();

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

Register_ClassDescriptor(PDUDescriptor);

PDUDescriptor::PDUDescriptor() : cClassDescriptor("PDU", "cPacket")
{
}

PDUDescriptor::~PDUDescriptor()
{
}

bool PDUDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<PDU_Base *>(obj)!=NULL;
}

const char *PDUDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"customize")) return "true";
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int PDUDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 9+basedesc->getFieldCount(object) : 9;
}

unsigned int PDUDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<9) ? fieldTypeFlags[field] : 0;
}

const char *PDUDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "version",
        "destAddr",
        "srcAddr",
        "connId",
        "type",
        "flags",
        "pduLen",
        "seqNum",
        "userData",
    };
    return (field>=0 && field<9) ? fieldNames[field] : NULL;
}

int PDUDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='v' && strcmp(fieldName, "version")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destAddr")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcAddr")==0) return base+2;
    if (fieldName[0]=='c' && strcmp(fieldName, "connId")==0) return base+3;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+4;
    if (fieldName[0]=='f' && strcmp(fieldName, "flags")==0) return base+5;
    if (fieldName[0]=='p' && strcmp(fieldName, "pduLen")==0) return base+6;
    if (fieldName[0]=='s' && strcmp(fieldName, "seqNum")==0) return base+7;
    if (fieldName[0]=='u' && strcmp(fieldName, "userData")==0) return base+8;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *PDUDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
        "APN",
        "APN",
        "ConnectionId",
        "int",
        "int",
        "unsigned int",
        "unsigned int",
        "unsigned char",
    };
    return (field>=0 && field<9) ? fieldTypeStrings[field] : NULL;
}

const char *PDUDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 4:
            if (!strcmp(propertyname,"enum")) return "PDUType";
            return NULL;
        default: return NULL;
    }
}

int PDUDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    PDU_Base *pp = (PDU_Base *)object; (void)pp;
    switch (field) {
        case 8: return pp->getUserDataArraySize();
        default: return 0;
    }
}

std::string PDUDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    PDU_Base *pp = (PDU_Base *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getVersion());
        case 1: {std::stringstream out; out << pp->getDestAddr(); return out.str();}
        case 2: {std::stringstream out; out << pp->getSrcAddr(); return out.str();}
        case 3: {std::stringstream out; out << pp->getConnId(); return out.str();}
        case 4: return long2string(pp->getType());
        case 5: return long2string(pp->getFlags());
        case 6: return ulong2string(pp->getPduLen());
        case 7: return ulong2string(pp->getSeqNum());
        case 8: return ulong2string(pp->getUserData(i));
        default: return "";
    }
}

bool PDUDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    PDU_Base *pp = (PDU_Base *)object; (void)pp;
    switch (field) {
        case 0: pp->setVersion(string2ulong(value)); return true;
        case 4: pp->setType(string2long(value)); return true;
        case 5: pp->setFlags(string2long(value)); return true;
        case 6: pp->setPduLen(string2ulong(value)); return true;
        case 7: pp->setSeqNum(string2ulong(value)); return true;
        case 8: pp->setUserData(i,string2ulong(value)); return true;
        default: return false;
    }
}

const char *PDUDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        "APN",
        "APN",
        "ConnectionId",
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<9) ? fieldStructNames[field] : NULL;
}

void *PDUDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    PDU_Base *pp = (PDU_Base *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getDestAddr()); break;
        case 2: return (void *)(&pp->getSrcAddr()); break;
        case 3: return (void *)(&pp->getConnId()); break;
        default: return NULL;
    }
}


