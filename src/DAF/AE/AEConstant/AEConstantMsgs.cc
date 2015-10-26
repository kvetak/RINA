#include "AEConstantMsgs.h"



PingMsg::PingMsg(bool _counted){
    pingAt = simTime();
    counted = _counted;
}

PongMsg::PongMsg(simtime_t _pingAt, bool _counted){
    pingAt = _pingAt;
    pongAt = simTime();
    counted = _counted;
}


StartMsg::StartMsg(){
}


SignalMsg::SignalMsg(std::string _qos) {
    qos = _qos;
    type = 0;
}
SignalMsg::SignalMsg(std::string _qos, simtime_t _delay) {
    qos = _qos;
    delay = _delay;
    type = 1;
}
SignalMsg::SignalMsg(std::string _qos, simtime_t _delay, simtime_t _rtt) {
    qos = _qos;
    delay = _delay;
    rtt = _rtt;
    type = 2;
}
