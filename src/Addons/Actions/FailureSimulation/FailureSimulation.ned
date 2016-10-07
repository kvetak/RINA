package rina.src.Addons.Actions.FailureSimulation;

simple FailureSimulation {
    parameters:
        double killAt = default(100.0); // kill links at
        double interKill = default(1.0); // kill links each
        double resurrectAt = default(200.0); // ressurrect links at
        int amount = default(0); // how much links kill
}
