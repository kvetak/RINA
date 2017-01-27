#include "Addons/Channels/ChangingErrorChannel/ChangingErrorChannel.h"
#include "Addons/Channels/ChangingErrorChannel/ChangerErrorChannel.h"
Define_Channel(ChangingErrorChannel);

ChangingErrorChannel::ChangingErrorChannel() : cDatarateChannel() { }

void ChangingErrorChannel::initialize() {
    cDatarateChannel::initialize();

    ChangerErrorChannel::registerChannel(this, par("name").stdstringValue());

}
