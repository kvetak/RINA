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

#include "AEVideo.h"

namespace AEVideo {

Define_Module(AEVideo);

int Stream::nextId = 0;

Stream::Stream(){
    id = nextId++;
    wt = 0.03;
    brt = 8.0;
    varFrameS = 0.0;
    rng = &uniform;
}

void Stream::setFps(double val) {
    wt = 1/val;
}

void Stream::setBrt(double val) {
    brt = val*1024;
}

void Stream::setVarFrameS(double val){
    varFrameS = val;
}

void Stream::setRNG(RNG_function val){
    rng = val;
}


int Stream::getid(){
    return id;
}

double Stream::getWt() {
    return wt;
}

int Stream::getNextFrame(){
    return (int) rng(minFrameS, maxFrameS,0);
}

void Stream::compute(){
    double packetSize = brt*wt;
    minFrameS = ceil(packetSize*(1-varFrameS));
    maxFrameS = ceil(packetSize*(1+varFrameS));
}

Stream_Timer::Stream_Timer(int id){
    streamId = id;
}

void AEVideo::doIni() {
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
        if(streamType == "LR" || streamType == "1"){
            st.setFps(15.0);
            st.setBrt(128.0);
        } else if(streamType == "SD" || streamType == "2"){
            st.setFps(30.0);
            st.setBrt(400.0);
        } else if(streamType == "HD" || streamType == "3"){
            st.setFps(30.0);
            st.setBrt(1228.8);
        }

        cXMLElementList attrs = m->getChildren();
        for (cXMLElementList::iterator jt = attrs.begin(); jt != attrs.end(); ++jt) {
            cXMLElement* n = *jt;
            if ( !strcmp(n->getTagName(), "fps") ) {
                double v = n->getNodeValue() ? atof(n->getNodeValue()) : 0;
                if (v > 0) { st.setFps(v); }
            } else if ( !strcmp(n->getTagName(), "brt") ) {
                double v = n->getNodeValue() ? atof(n->getNodeValue()) : 0;
                if (v > 0) { st.setBrt(v); }
            } else if ( !strcmp(n->getTagName(), "varFr") ) {
                double v = n->getNodeValue() ? atof(n->getNodeValue()) : 0;
                if (v >= 0 && v <= 1) { st.setVarFrameS(v); }
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

void AEVideo::doFin(){
    EV << k <<endl;
    EV << maxSize <<endl;
}

void AEVideo::iniCom(){
    for(sVecIt it = streams.begin(); it != streams.end(); it++){
        scheduleAt(uniform(simTime(), simTime()+startVar), new  Stream_Timer(it->getid()) );
    }
}

void AEVideo::processMsg(_AESInt_self * msg){
    Stream_Timer * st = dynamic_cast<Stream_Timer*>(msg);
    if(inTime && st){
        Stream *s = &streams[st->streamId];
        int data = s->getNextFrame();
        while(data > 0){
            sendMsg(new _PingMsg(), min(data, maxSize));
            data -= maxSize;
        }
        scheduleAt(simTime()+s->getWt(), new  Stream_Timer(st->streamId) );
    }
    delete msg;
}

}
