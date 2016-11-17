
package rina.src.Addons.DataInjectors;

moduleinterface Infection_t {
    parameters:
        string infectedIPC;
        
    gates:
        inout g;
}
