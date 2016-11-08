package rina.src.Addons.Channels.EthChannel;


channel EthChannel extends ned.DatarateChannel {
    @class("EthChannel");
    int header = default(12B) @unit(B);
    int ipg = default(8B) @unit(B);
    datarate = default(1Gbps);
}