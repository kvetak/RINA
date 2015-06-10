package rina.src.DIF.FA;

import rina.src.DIF.NSM.NameSpaceManager;
import rina.policies.DIF.FA.AllocateRetry.IAllocateRetry;
import rina.policies.DIF.FA.NewFlowRequest.INewFlowRequest;
import rina.policies.DIF.FA.MultilevelQoS.IAMultilevelQoS;


module FlowAllocator
{
    parameters:
        @display("i=block/fork;bgb=386,234");
        string newFlowReqPolicyType = default("ScoreComparer");
        string allocRetryPolicyType = default("LimitedRetries");
        string qosComparerPolicyType = default("QoSIdComparer");
    gates:

    submodules:
        fa: FA {
            @display("p=75,64");
        }

        faiTable: FAITable {
            @display("p=167,64");
        }

        newFlowRequestPolicy: <newFlowReqPolicyType> like INewFlowRequest {
            @display("p=290,64");
        }

        allocateRetryPolicy: <allocRetryPolicyType> like IAllocateRetry {
            @display("p=102,155");
        }

        qosComparerPolicy: <qosComparerPolicyType> like IAMultilevelQoS {
            @display("p=240,155");
        }
    connections:


}
