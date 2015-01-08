#include "PDUFTGListeners.h"
#include "PDUFwdTabGenerator.h"

PDUFTGListener::PDUFTGListener(PDUFwdTabGenerator * generator)
{
    fwdtg = generator;
}

PDUFTGListener::~PDUFTGListener()
{
    /* Nothing here... */
}

void LisPDUFTGFwdInfoRecv::receiveSignal(cComponent *src, simsignal_t id, cObject *obj)
{
    EV << "ForwardingInfoUpdate initiated by " << src->getFullPath()
       << " and processed by " << fwdtg->getFullPath() << endl;

    FSUpdateInfo * info = dynamic_cast<FSUpdateInfo *>(obj);

    if (info)
    {
        fwdtg->handleUpdateMessage(info);
    }
    else
    {
        EV << "ForwardingInfoUpdate received unknown object!" << endl;
    }

    // Dispose of the event resource allocated.
    // Ticket #19. Thank you gaixas1.
    delete info;
}
