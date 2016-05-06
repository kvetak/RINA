// The MIT License (MIT)
//
// Copyright (c) 2015-2016 TSSG, Waterford Institute of Technology, PRISTINE project
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

#ifndef __RINA_STATS_H_
#define __RINA_STATS_H_

//Standard libraries
#include <omnetpp.h>
#include <algorithm>
#include <fstream>
class Stats
{
    private:
        // trim string for empty spaces in begining and at the end
        inline std::string &trim(std::string &s)
        {

            s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
            s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
            return s;
        }

    private:
        std::map<std::pair<unsigned int, unsigned int>, std::string> m_oData;
        const int MAX_LOAD = 100;

    public:
        Stats();
        virtual ~Stats();
        //bool open( const char* filename, char delim);
        bool open( );
        void open_now( std::istream& istream, char delim);
        bool save( );
        //bool save( const char* pFile, char delim);
        void save_now( std::ostream& ostream, char delim);
        std::pair<unsigned int, unsigned int> searchPair(std::string str);
        std::string toString(int i);
        const char *filename;
        char delim;
        int toInt(std::string str);
        int rowCount();
        int getLoad(std::string apn);
        bool isAvailabile(std::string apn);
        int getThreshold(std::string apn);
        void updateLoad(std::string apn, std::string api, std::string aen, std::string aei, bool increment);
        void rowErase(unsigned int row);

        void clear();
        std::string& operator()( unsigned int nCol, unsigned int nRow )
        {
            m_nCols = std::max( m_nCols, nCol+1 );
            m_nRows = std::max( m_nRows, nRow+1 );
            return staticData[std::make_pair(nCol, nRow)];
        }

        inline unsigned int GetRows() { return m_nRows; }
        inline unsigned int GetCols() { return m_nCols; }

        std::string getBestAppByAppList(std::string srcApp, std::string dstApp, std::string allApps);
        std::string getBestAppByAEN(std::string srcApp, std::string dstApp, std::string aen);
        std::string getBestRandAppByAEN(std::string srcApp, std::string dstApp, std::string aen);

        static std::map<std::pair<unsigned int, unsigned int>, std::string> staticData;
        static bool enableLB;
        unsigned int    m_nCols;
        unsigned int    m_nRows;

        static unsigned int    staticCols;
        static unsigned int    staticRows;

        void printStatus();
};
#endif
