#pragma once

class Flow_t;
class Flow_Data;

struct PDU_Req {
    Flow_t * f;
    Flow_Data * data;
    PDU_Req ();
    PDU_Req (Flow_t * _f, Flow_Data * _data);
};
