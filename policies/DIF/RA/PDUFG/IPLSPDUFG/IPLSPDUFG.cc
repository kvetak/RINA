#include "DIF/RA/PDUFG/IPLSPDUFG/IPLSPDUFG.h"
#include "DIF/RA/QueueIDGen/IDPerNQoSxPLen/IDPerNQoSxPLen.h"

void IPLSPDUFG::registerQidsGen(IDPerNQoSxPLen * qId) {
    qIds.insert(qId);
}
void IPLSPDUFG::unregisterQidsGen(IDPerNQoSxPLen * qId) {
    qIds.erase(qId);
}
