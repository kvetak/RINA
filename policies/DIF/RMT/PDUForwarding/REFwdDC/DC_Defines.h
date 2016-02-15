#pragma once

#include <vector>
#include "RMTPort.h"

#define  TYPEID_ToR 0
#define  TYPEID_Fabric 1
#define  TYPEID_Edge 3
#define  TYPEID_Spine 2

#define  AGID_Pod 4
#define  AGID_Spine 5


#define  EXCEPTION_FLAG_NONE 0
#define  EXCEPTION_FLAG_UP 1
#define  EXCEPTION_FLAG_DOWN 2
#define  EXCEPTION_FLAG_UPDOWN 3
#define  EXCEPTION_FLAG_INVERSE 4

typedef RMTPort* Port;
typedef unsigned char portId;
typedef std::vector<portId> portList;
