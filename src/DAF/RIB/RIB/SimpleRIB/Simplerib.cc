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

#include "Simplerib.h"

Define_Module(Simplerib);

void Simplerib::initialize()
{

    EV << "Initializing SimpleRIB" << endl;
    WATCH_LIST(this->objTable);
}

void Simplerib::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}

bool Simplerib::createAE(std::string AEName) {
    return false;
}

bool Simplerib::createIAE(std::string IAEName, AEBase* ae) {
    return false;
}

bool Simplerib::deleteAE(std::string AEName) {
    return false;
}

bool Simplerib::deleteIAE(std::string IAEName) {
    return false;
}

object_t* Simplerib::createObj(int CDAPConn, object_t *obj) {
    std::string s(obj->objectName.c_str());
    object_t* object = this->findObj(CDAPConn, s);
    if (!object) {
        SimpleRIBObj tmpObj = SimpleRIBObj(obj, s, CDAPConn);
        objTable.push_back(tmpObj);
        return obj;
    }

    return NULL;
}

object_t* Simplerib::deleteObj(int CDAPConn, std::string objName) {
    return NULL;
}

object_t* Simplerib::writeObj(int CDAPConn, object_t *obj) {
    std::string s(obj->objectName.c_str());
    object_t *tmpObj = this->findObj(CDAPConn, s);

    if (tmpObj) {
        tmpObj->objectVal = obj->objectVal;
    }

    return tmpObj;
}

object_t* Simplerib::readObj(int CDAPConn, std::string objName) {
    return this->findObj(CDAPConn, objName);
}


object_t* Simplerib::findObj(int CDAPConn, std::string objName) {
    for(auto it = objTable.begin(); it != objTable.end(); ++it) {
        SimpleRIBObj obj = *it;
        if (obj.path == objName) {
            return &(*obj.appObject);
        }
    }
    return NULL;
}
