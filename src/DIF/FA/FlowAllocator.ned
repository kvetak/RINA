package rina.src.DIF.FA;

import rina.policies.DIF.FA.AllocateRetry.IAllocateRetry;
import rina.policies.DIF.FA.NewFlowRequest.INewFlowRequest;
import rina.policies.DIF.FA.MultilevelQoS.IAMultilevelQoS;


module FlowAllocator
{
    parameters:
        @display("i=block/fork;bgb=424,357");
        string newFlowReqPolicyType = default("ScoreComparer");
        string allocRetryPolicyType = default("LimitedRetries");
        string qosComparerPolicyType = default("QoSIdComparer");
    gates:

    submodules:
        fa: FA {
            @display("p=75,64");
        }

        nFlowTable: NFlowTable {
            @display("p=167,64");
        }

        newFlowRequestPolicy: <newFlowReqPolicyType> like INewFlowRequest {
            @display("p=357,64");
        }

        allocateRetryPolicy: <allocRetryPolicyType> like IAllocateRetry {
            @display("p=357,154");
        }

        qosComparerPolicy: <qosComparerPolicyType> like IAMultilevelQoS {
            @display("p=357,245");
        }
    connections:


}
