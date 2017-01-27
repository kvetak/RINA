#include "Addons/Channels/EthChannel/EthChannel.h"

Define_Channel(EthChannel);

EthChannel::EthChannel() : cDatarateChannel() {
    etxfinishtime = 0.0;
}
void EthChannel::initialize() {
    cDatarateChannel::initialize();
    eheader = par("header").longValue();
    eipg = par("ipg").longValue();
    edelay = par("delay").doubleValue();
    edatarate = par("datarate").doubleValue()/8.0;
    etxfinishtime = 0.0;
 //   std::cout << "--initialized"<<endl;
}

void EthChannel::processMessage(cMessage *msg, simtime_t t, result_t& result){
    double ps = eheader;
    if(msg->isPacket()){
        ps =  dynamic_cast<cPacket * >(msg)->getByteLength();
    }
    result.delay = edelay;
    result.duration = ps/edatarate;
    etxfinishtime = t + (ps+eipg)/edatarate;
}
