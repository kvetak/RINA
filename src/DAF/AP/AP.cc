// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include <AP/AP.h>

Define_Module(AP);

AP::AP() {

}

AP::~AP() {
}

void AP::onOpen(APIResult* result) {
}

void AP::onRead(APIResult* result) {
}

void AP::onWrite(APIResult* result) {
}

void AP::onClose(APIResult* result) {
}

bool AP::a_open(int invokeID, std::string APname, std::string APinst, std::string AEname, std::string AEinst) {
}

bool AP::a_close(int CDAPConn, int invokeID) {
}

bool AP::a_read(int CDAPConn, std::string objName, int invokeID) {
}

bool AP::a_write(int CDAPConn, std::string objName, object_t *obj, int invokeID) {
}

APIRetObj* AP::a_getopen_r(int invokeID) {
}

APIRetObj* AP::a_getclose_r(int CDAPConn, int invokeID) {
}

bool AP::a_read_r(int CDAPconn, int invokeID, std::string objName, object_t *obj, bool complete) {
}

APIRetObj* AP::a_get_read_r(int CDAPConn, int invokeID) {
}

bool a_cancelread_r(int CDAPConn, int invokeID = 0) {
}

APIRetObj* a_getwrite_r(int CDAPconn, int invokeID, APIResult* result, std::string objName, object_t *obj = NULL);
