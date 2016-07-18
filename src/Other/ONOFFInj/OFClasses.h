#pragma once

class Inj_data;
class Flow_t;

class server_t;
class client_t;
class sender_t;

class Flow_timer;
class actTimer;
class retransTimer;
class selretransTimer;
class ackTimer;

struct pduReq {
    Flow_t * f;
    Inj_data * data;
    pduReq ();
    pduReq (Flow_t * _f, Inj_data * _data);
};


class ONOFInj;


