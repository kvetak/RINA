package rina.src.DIF.FA;

import rina.src.DIF.NSM.NameSpaceManager;
import rina.policies.DIF.FA.AllocateRetry.IAllocateRetry;
import rina.policies.DIF.FA.NewFlowRequest.*;


module FlowAllocator
{
    parameters:
        @display("i=block/fork;bgb=513,318");
        string newFlowReqPolicyType = default("ScoreComparer");
        string allocRetryPolicyType = default("LimitedRetries");
    gates:

    submodules:
        fa: FA {
            @display("p=68,65");
        }

        faiTable: FAITable {
            @display("p=160,65");
        }

        newFlowRequestPolicy: <newFlowReqPolicyType> like INewFlowRequest {
            @display("p=302,65");
        }
        allocateRetryPolicy: <allocRetryPolicyType> like IAllocateRetry {
            @display("p=428,65");
        }
    connections:


}
