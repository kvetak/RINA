#pragma once

#include <set>

class IDPerNQoSxPLen;

class IPLSPDUFG {
public:
    void registerQidsGen(IDPerNQoSxPLen * qId);
    void unregisterQidsGen(IDPerNQoSxPLen * qId);

protected:
    std::set<IDPerNQoSxPLen *> qIds;
};
