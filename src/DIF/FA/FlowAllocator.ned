package rina.DIF.FA;

import rina.DIF.NSM.NameSpaceManager;
import rina.policies.DIF.FA.AllocateRetry.IAllocateRetry;
import rina.policies.DIF.FA.NewFlowRequest.*;


module FlowAllocator
{
    parameters:
        @display("i=block/fork;bgb=513,318");
		string newFlowReqPolicyType = default("QoSCubeComparer");
		string allocRetryPolicyType = default("LimitedRetries");
    gates:

    submodules:
        fa: FA {
            @display("p=67,49");
        }

        faiTable: FAITable {
            @display("p=159,49");
        }

        newFlowRequestPolicy: <newFlowReqPolicyType> like INewFlowRequest {
            @display("p=301,49");
        }
        allocateRetryPolicy: <allocRetryPolicyType> like IAllocateRetry {
            @display("p=427,49");
        }
    connections:


}
