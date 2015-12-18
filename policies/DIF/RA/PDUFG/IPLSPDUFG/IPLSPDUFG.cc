#include "IPLSPDUFG.h"
#include "IDPerNQoSxPLen.h"

void IPLSPDUFG::registerQidsGen(IDPerNQoSxPLen * qId) {
    qIds.insert(qId);
}
void IPLSPDUFG::unregisterQidsGen(IDPerNQoSxPLen * qId) {
    qIds.erase(qId);
}
