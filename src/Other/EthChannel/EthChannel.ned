package rina.src.Other.EthChannel;


channel EthChannel extends ned.DatarateChannel {
    @class("EthChannel");
    int header @unit(B);
    int ipg @unit(B);
}