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

#include "AEVoice.h"

namespace AEVoice {

Define_Module(AEVoice);

int Stream::nextId = 0;

Stream::Stream(){
    id = nextId++;
    wt = 0.03;
    brt = 8.0;
    avgSTime = 10.0;
    avgWTime = 10.0;
    varSTime = 2.0;
    varWTime = 2.0;
    rng = &uniform;
}

void Stream::setWt(double val) {
    wt = val;
}

void Stream::setBrt(double val) {
    brt = val*1024;
}

void Stream::setAvgSTime(double val){
    avgSTime = val;
}

void Stream::setAvgWTime(double val){
    avgWTime = val;
}

void Stream::setVarSTime(double val){
    varSTime = val;
}

void Stream::setVarWTime(double val){
    varWTime = val;
}

void Stream::setRNG(RNG_function val){
    rng = val;
}

void Stream::setState(bool val) {
    state = val;
}

int Stream::getid(){
    return id;
}

void Stream::compute(){
    packetSize = (int) ceil(brt*wt);
    minSTime = avgSTime-varSTime;
    maxSTime = avgSTime+varSTime;
    minWTime = avgWTime-varSTime;
    maxWTime = avgWTime+varSTime;
}

double Stream::nexSendT(){
    return rng(minSTime, maxSTime,0);
}

double Stream::nexWaitT(){
    return rng(minWTime, maxWTime,0);
}


double Stream::getWt() {
    return wt;
}

int Stream::getDataSize(){
    return packetSize;
}

bool Stream::getState(){
    return state;
}

State_Change::State_Change(int id, bool state){
    streamId = id;
    newState = state;
}

Stream_Timer::Stream_Timer(int id){
    streamId = id;
}

void AEVoice::doIni() {
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

        std::string streamType = "";
        if (m->getAttribute("type")) {
            streamType = m->getAttribute("type");
        }

        Stream st;
        if(streamType == "GSM_06.10" || streamType == "1"){
            st.setWt(0.02);
            st.setBrt(13);
        } else if(streamType == "G.729" || streamType == "2"){
            st.setWt(0.06);
            st.setBrt(8);
        } else if(streamType == "G.723.1_A" || streamType == "3"){
            st.setWt(0.03);
            st.setBrt(6.4);
        } else if(streamType == "G.723.1_B" || streamType == "4"){
            st.setWt(0.03);
            st.setBrt(5.3);
        } else if(streamType == "ILBC_A" || streamType == "5"){
            st.setWt(0.02);
            st.setBrt(15.2);
        } else if(streamType == "ILBC_B" || streamType == "6"){
            st.setWt(0.03);
            st.setBrt(13.33);
        }

        cXMLElementList attrs = m->getChildren();
        for (cXMLElementList::iterator jt = attrs.begin(); jt != attrs.end(); ++jt) {
            cXMLElement* n = *jt;
            if ( !strcmp(n->getTagName(), "wt") ) {
                double v = n->getNodeValue() ? atof(n->getNodeValue()) : 0;
                if (v > 0) { st.setWt(v); }
            } else if ( !strcmp(n->getTagName(), "brt") ) {
                double v = n->getNodeValue() ? atof(n->getNodeValue()) : 0;
                if (v > 0) { st.setBrt(v); }
            } else if ( !strcmp(n->getTagName(), "avgS") ) {
                double v = n->getNodeValue() ? atof(n->getNodeValue()) : 0;
                if (v > 0) { st.setAvgSTime(v); }
            } else if ( !strcmp(n->getTagName(), "avgW") ) {
                double v = n->getNodeValue() ? atof(n->getNodeValue()) : 0;
                if (v > 0) { st.setAvgSTime(v); }
            } else if ( !strcmp(n->getTagName(), "varS") ) {
                double v = n->getNodeValue() ? atof(n->getNodeValue()) : 0;
                if (v > 0) { st.setVarSTime(v); }
            } else if ( !strcmp(n->getTagName(), "varW") ) {
                double v = n->getNodeValue() ? atof(n->getNodeValue()) : 0;
                if (v > 0) { st.setVarSTime(v); }
            } else if ( !strcmp(n->getTagName(), "rng") ) {
                string nodeVal = n->getNodeValue();
                if(nodeVal == "uniform"){
                    st.setRNG(&uniform);
                } else if(nodeVal == "normal"){
                    st.setRNG(&minMaxNormal);
                }
            }
        }
        st.compute();

        streams.push_back(st);
    }
}

void AEVoice::doFin(){
    for(sVecIt it = streams.begin(); it != streams.end(); it++){
        EV << 1/it->getWt() << " -> " << it->getDataSize() << endl;
    }
}

void AEVoice::iniCom(){
    for(sVecIt it = streams.begin(); it != streams.end(); it++){
        it->setState(false);
        scheduleAt(uniform(simTime(), simTime()+startVar), new  State_Change(it->getid(), true) );
    }
}

void AEVoice::processMsg(_AESInt_self * msg){
    if(inTime){
        if(State_Change * stc = dynamic_cast<State_Change*>(msg)){
            if(stc->newState){
                Stream *s = &streams[stc->streamId];
                s->setState(true);
                scheduleAt(simTime()+s->nexWaitT(), new  State_Change(stc->streamId, false) );
                scheduleAt(simTime(), new  Stream_Timer(stc->streamId) );
            } else {
                Stream *s = &streams[stc->streamId];
                s->setState(false);
                scheduleAt(simTime()+s->nexWaitT(), new  State_Change(stc->streamId, true) );
            }
        } else if(Stream_Timer * st = dynamic_cast<Stream_Timer*>(msg)){
            Stream *s = &streams[st->streamId];
            if(s->getState()){
                int data = s->getDataSize();
                while(data > 0){
                    sendMsg(new _PingMsg(), min(data, maxSize));
                    data -= maxSize;
                }
                scheduleAt(simTime()+s->getWt(), new  Stream_Timer(st->streamId) );
            }
        }
    }
    delete msg;
}

}
