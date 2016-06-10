package rina.examples.Routing.GRE.TestNet;

import rina.src.Other.NetTest.NetTestRouter;
import rina.src.Other.NetTest.NetTestListener;

network net {
submodules:
N0:NetTestRouter;
N1:NetTestRouter;
N2:NetTestRouter;
N3:NetTestRouter;
N4:NetTestRouter;
N5:NetTestRouter;
N6:NetTestRouter;
N7:NetTestRouter;
N8:NetTestRouter;
listener: NetTestListener;

connections:
N0.medium++ <-->  N1.medium++;
N0.medium++ <-->  N8.medium++;
N1.medium++ <-->  N2.medium++;
N2.medium++ <-->  N3.medium++;
N2.medium++ <-->  N5.medium++;
N3.medium++ <-->  N5.medium++;
N3.medium++ <-->  N6.medium++;
N4.medium++ <-->  N6.medium++;
N4.medium++ <-->  N7.medium++;
N4.medium++ <-->  N8.medium++;
N6.medium++ <-->  N7.medium++;

}
