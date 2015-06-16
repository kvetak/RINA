//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "AdmCore.h"

Define_Module(AdmCore);

#include <string>
#include <list>
#include "Utils.h"

#include "RA.h"

using namespace std;


void AdmCore::initialize() {
    sig = registerSignal("LISTENER_SLAVE");
    this->getParentModule()->getParentModule()->getParentModule()->subscribe("LISTENER_MASTER", this);


    cXMLElement* Xml = NULL;
    if (par("flows").xmlValue() != NULL && par("flows").xmlValue()->hasChildren()){
        Xml = par("flows").xmlValue();
    } else {
        error("flows parameter not initialized!");
    }

    cXMLElementList items = Xml->getChildrenByTagName("item");
    for(auto item : items) {
        if (!item->getAttribute("src")) {
            EV << "Error parsing flows item. Its src is missing!" << endl;
            continue;
        }
        std::string src = item->getAttribute("src");
        if (src == "") {
            EV << "Error parsing flows item. Its src is missing!" << endl;
            continue;
        }

        if (!item->getAttribute("dif")) {
            EV << "Error parsing flows item. Its dif is missing!" << endl;
            continue;
        }
        std::string dif = item->getAttribute("dif");
        if (src == "") {
            EV << "Error parsing flows item. Its dif is missing!" << endl;
            continue;
        }

        cXMLElementList fls = item->getChildrenByTagName("flow");
        for(auto flow : fls) {
            if (!flow->getAttribute("dst")) {
                EV << "Error parsing flow. Its dst is missing!" << endl;
                continue;
            }
            std::string dst = flow->getAttribute("dst");
            if (dst == "") {
                EV << "Error parsing flow. Its dst is missing!" << endl;
                continue;
            }

            data[dif][src].push_back(dst);
        }
    }
}

void AdmCore::receiveSignal(cComponent *src, simsignal_t id, cObject *obj) {
    if(HelloMsg * m = dynamic_cast<HelloMsg*>(obj)){
        if(!data[m->dif][m->src].empty()) {
            reqFlowMsg * response = new reqFlowMsg(m->src, m->dif);
            response->flowsDstAppName = data[m->dif][m->src];
            emit(sig, response);
        }
    }
}
