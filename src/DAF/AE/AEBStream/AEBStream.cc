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

#include "AEBStream.h"

namespace AEBStream {

Define_Module(AEBStream);

int Stream::nextId = 0;

Stream::Stream(){
    id = nextId++;
    wt = 0.03;
    brt = 8.0;
    rng = &uniform;
    rngb = &uniform;

    pduS=1024;
    varPduS=0;
    burstS=10240;
    varBurstS=0;
    burstProb=0.05;
}

void Stream::setBrt(double val) {
    brt = val*1024;
}

void Stream::setPduS(int val){
    pduS = val;
}
void Stream::setVarPduS(double val){
    varPduS = val;
}

void Stream::setBurstS(int val){
    burstS = val;
}
void Stream::setVarBurstS(double val){
    varBurstS = val;
}

void Stream::setBurstProb(double val){
    burstProb = val;
}

void Stream::setRNG(RNG_function val){
    rng = val;
}

void Stream::setBRNG(RNG_function val){
    rngb = val;
}


int Stream::getid(){
    return id;
}

double Stream::getWt(int size) {
    return wt*size;
}

int Stream::getPDU(){
    return (int) rng(minPduS, maxPduS, 0);
}

int Stream::getBurst(){
    return (int) rng(minBurstS, maxBurstS, 0);
}

double Stream::getBurstProb(){
    return burstProb;
}

void Stream::setState(bool val){
    state = val;
}
bool Stream::getState(){
    return state;
}

void Stream::compute(){
    wt = 1/brt;
    minPduS = (int) ceil(pduS*(1-varPduS));
    maxPduS = (int) ceil(pduS*(1+varPduS));
    minBurstS = (int) ceil(burstS*(1-varBurstS));
    maxBurstS = (int) ceil(burstS*(1+varBurstS));
}

Stream_Timer::Stream_Timer(int id){
    streamId = id;
}

void AEBStream::doIni() {
    startVar = par("startVar");

    cXMLElement* slXml = NULL;
    if (par("streamList").xmlValue() != NULL && par("streamList").xmlValue()->hasChildren()){
        slXml = par("streamList").xmlValue();
    } else {
        error("streamList parameter not initialized!");
    }

    cXMLElementList streamsXML = slXml->getChildrenByTagName("Stream");
    for (cXMLElementList::iterator it = streamsXML.begin(); it != streamsXML.end(); ++it) {
        cXMLElement* m = *it;

        Stream st;

        cXMLElementList attrs = m->getChildren();
        for (cXMLElementList::iterator jt = attrs.begin(); jt != attrs.end(); ++jt) {
            cXMLElement* n = *jt;
            if ( !strcmp(n->getTagName(), "brt") ) {
                double v = n->getNodeValue() ? atof(n->getNodeValue()) : 0;
                if (v > 0) { st.setBrt(v); }
            } else if ( !strcmp(n->getTagName(), "pduS") ) {
                double v = n->getNodeValue() ? atoi(n->getNodeValue()) : 0;
                if (v >= 0) { st.setPduS(v); }
            }  else if ( !strcmp(n->getTagName(), "varPduS") ) {
                double v = n->getNodeValue() ? atof(n->getNodeValue()) : 0;
                if (v >= 0 && v <= 1) { st.setVarPduS(v); }
            } else if ( !strcmp(n->getTagName(), "BurstS") ) {
                double v = n->getNodeValue() ? atoi(n->getNodeValue()) : 0;
                if (v >= 0) { st.setBurstS(v); }
            } else if ( !strcmp(n->getTagName(), "varBurstS") ) {
                double v = n->getNodeValue() ? atof(n->getNodeValue()) : 0;
                if (v >= 0 && v <= 1) { st.setVarBurstS(v); }
            } else if ( !strcmp(n->getTagName(), "burstProb") ) {
                double v = n->getNodeValue() ? atof(n->getNodeValue()) : 0;
                if (v >= 0 && v <= 1) { st.setBurstProb(v); }
            } else if ( !strcmp(n->getTagName(), "rng") ) {
                string nodeVal = n->getNodeValue();
                if(nodeVal == "uniform"){
                    st.setRNG(&uniform);
                } else if(nodeVal == "normal"){
                    st.setRNG(&minMaxNormal);
                }
            } else if ( !strcmp(n->getTagName(), "rngb") ) {
                string nodeVal = n->getNodeValue();
                if(nodeVal == "uniform"){
                    st.setBRNG(&uniform);
                } else if(nodeVal == "normal"){
                    st.setBRNG(&minMaxNormal);
                }
            }
        }
        st.compute();

        streams.push_back(st);
    }
}

void AEBStream::doFin(){}

void AEBStream::iniCom(){
    for(sVecIt it = streams.begin(); it != streams.end(); it++){
        it->setState(false);
        scheduleAt(uniform(simTime(), simTime()+startVar), new  Stream_Timer(it->getid()) );
    }
}

void AEBStream::processMsg(_AESInt_self * msg){
    Stream_Timer * st = dynamic_cast<Stream_Timer*>(msg);
    if(inTime && st){
        Stream *s = &streams[st->streamId];
        int data;
        if(s->getState()){
            data = s->getPDU();
            if(uniform(0,1) < s->getBurstProb()){ s->setState(true); }
        } else {
            data = s->getBurst();
            s->setState(false);
        }
        int remaining = data;

        while(remaining > 0){
            sendMsg(new _PingMsg(), min(remaining, maxSize));
            remaining -= maxSize;
        }

        scheduleAt(simTime()+s->getWt(data), new  Stream_Timer(st->streamId) );
    }
    delete msg;
}

}
