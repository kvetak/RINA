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

#ifndef APIRESULT_H_
#define APIRESULT_H_

#include "DAF/AP/APIObjBase.h"

class APIResult : public APIObjBase {
public:
    APIResult();
    virtual ~APIResult();

    enum APIResType {A_GET_OPEN, A_GET_READ, A_GET_WRITE, D_DELETE};

    void setAPIResType(APIResult::APIResType type);
    APIResult::APIResType getAPIResType();

    void setObj(object_t *obj);
    object_t *getObj();

    void setObjName(std::string objName);
    std::string getObjName();
private:
    APIResType type;
    std::string objName;
    object_t *obj;
};

#endif /* APIRESULT_H_ */
