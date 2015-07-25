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

#include "AEData.h"

namespace AEData {

Define_Module(AEData);

int Stream::nextId = 0;

Stream::Stream(){
    id = nextId++;
    state = false;

    wt = 0.03;
    brt = 8.0;

    dataS = 10240;
    rng = &uniform;

    waitT = 0;
    rngwt = &uniform;
}

void Stream::setBrt(double val) {
    brt = val*1024;
}

void Stream::setDataS(int val){
    dataS = val;
}
void Stream::setVarDataS(double val){
    varDataS = val;
}

void Stream::setWaitT(double val){
    waitT = val;
}
void Stream::setVarWaitT(double val){
    varWaitT = val;
}

void Stream::setRNG(RNG_function val){
    rng = val;
}

void Stream::setWTRNG(RNG_function val){
    rngwt = val;
}


int Stream::getid(){
    return id;
}

int Stream::getRemaining(){
    return wData;
}

int Stream::getNextPDU(int maxSize){
    int ret = (wData < maxSize)? wData : maxSize;
    wData -= ret;
    return ret;
}

void Stream::setWaiting(){
    state = false;
    wData = 0;
}
void Stream::setSending(){
    state = true;
    wData = (int) rng(minDataS, maxDataS, 0);
}

bool Stream::getState(){
    return state;
}

double Stream::getWt(int size){
    return wt*size;
}

double Stream::getWait(){
    return rng(minWaitT, maxWaitT, 0);
}

void Stream::compute(){
    wt = 1/brt;
    minDataS = (int) ceil(dataS*(1-varDataS));
    maxDataS = (int) ceil(dataS*(1+varDataS));
    minWaitT = (int) ceil(waitT*(1-varWaitT));
    maxWaitT = (int) ceil(waitT*(1+varWaitT));
}

State_Change::State_Change(int id, bool state){
    streamId = id;
    newState = state;
}

Stream_Timer::Stream_Timer(int id){
    streamId = id;
}

void AEData::doIni() {
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
            } else if ( !strcmp(n->getTagName(), "dataS") ) {
                double v = n->getNodeValue() ? atoi(n->getNodeValue()) : 0;
                if (v >= 0) { st.setDataS(v); }
            }  else if ( !strcmp(n->getTagName(), "vardataS") ) {
                double v = n->getNodeValue() ? atof(n->getNodeValue()) : 0;
                if (v >= 0 && v <= 1) { st.setVarDataS(v); }
            } else if ( !strcmp(n->getTagName(), "waitT") ) {
                double v = n->getNodeValue() ? atof(n->getNodeValue()) : 0;
                if (v >= 0) { st.setWaitT(v); }
            } else if ( !strcmp(n->getTagName(), "varWaitT") ) {
                double v = n->getNodeValue() ? atof(n->getNodeValue()) : 0;
                if (v >= 0 && v <= 1) { st.setVarWaitT(v); }
            } else if ( !strcmp(n->getTagName(), "rng") ) {
                string nodeVal = n->getNodeValue();
                if(nodeVal == "uniform"){
                    st.setRNG(&uniform);
                } else if(nodeVal == "normal"){
                    st.setRNG(&minMaxNormal);
                }
            } else if ( !strcmp(n->getTagName(), "rngwt") ) {
                string nodeVal = n->getNodeValue();
                if(nodeVal == "uniform"){
                    st.setWTRNG(&uniform);
                } else if(nodeVal == "normal"){
                    st.setWTRNG(&minMaxNormal);
                }
            }
        }
        st.compute();

        streams.push_back(st);
    }
}

void AEData::doFin(){}

void AEData::iniCom(){
    for(sVecIt it = streams.begin(); it != streams.end(); it++){
        it->setWaiting();
        scheduleAt(uniform(simTime(), simTime()+startVar), new  State_Change(it->getid(), true) );
    }
}

void AEData::processMsg(_AESInt_self * msg){
    if(inTime){
        if(State_Change * stc = dynamic_cast<State_Change*>(msg)){
            if(stc->newState){
                streams[stc->streamId].setSending();
                scheduleAt(simTime(), new  Stream_Timer(stc->streamId) );
            } else {
                Stream *s = &streams[stc->streamId];
                s->setWaiting();
                scheduleAt(simTime()+s->getWait(), new  State_Change(stc->streamId, true) );
            }
        } else if(Stream_Timer * st = dynamic_cast<Stream_Timer*>(msg)){
            Stream *s = &streams[st->streamId];
            if(s->getState()){
                if(s->getRemaining() <= 0){
                    scheduleAt(simTime(), new  State_Change(st->streamId, false) );
                } else {
                    int data = s->getNextPDU(maxSize);
                    sendMsg(new _PingMsg(), data);
                    scheduleAt(simTime()+s->getWt(data), new  Stream_Timer(st->streamId) );
                }
            }
        }
    }
    delete msg;
}

}
