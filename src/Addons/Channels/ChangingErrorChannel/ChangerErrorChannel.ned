package rina.src.Addons.Channels.ChangingErrorChannel;

simple ChangerErrorChannel {
    parameters:
        double problemsAt = default(100.0);
        double changeEach = default(10.0);
        double newBer = default(0.0);
        double newDataRate @unit(bps) = default(10Mbps);
}
