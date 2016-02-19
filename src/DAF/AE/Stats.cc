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

/*****

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
*/
#include "Stats.h"

std::map<std::pair<unsigned int, unsigned int>, std::string> Stats::staticData = {{std::make_pair(0, 0), ","}};
bool Stats::enableLB = false;
unsigned int    Stats::staticCols = 0;
unsigned int    Stats::staticRows = 0;

    Stats::Stats(void)
    {
        if(!enableLB)
        {
            m_nCols = 0; m_nRows = 0;

            filename = "stats.txt";
            delim = ',';

            enableLB = this->open( );
        }
        else
        {
            m_nCols = staticCols; m_nRows = staticRows;
            m_oData = staticData;

        }
    }

    Stats::~Stats()
    {
        clear();
    }

    bool Stats::open()
    {
        std::ifstream file( filename );
        clear();
        if ( file.is_open() )
        {
            open_now( file, delim );
            file.close();
            return true;
        }

        return false;
    }

    //* Load the file in MAP data structure
    void Stats::open_now( std::istream& istream, char delim = ',' )
    {
        std::string line;

        clear();
        while ( std::getline( istream, line ) )
        {
            unsigned int nCol = 0;

            std::istringstream    lineStream(line);
            std::string           cell;

            while( std::getline( lineStream, cell, delim ) )
            {
                m_oData[std::make_pair( nCol, m_nRows )] = trim( cell );
                staticData[std::make_pair( nCol, m_nRows )] = trim( cell );
                nCol++;
            }
            m_nCols = std::max( m_nCols, nCol );
            m_nRows++;
        }
        staticRows = m_nRows; staticCols = m_nCols;
    }

    bool Stats::save()
    {
        std::ofstream ofile( filename );
        if ( ofile.is_open() )
        {
            save_now(ofile, delim );
            ofile.close();
            return true;
        }
        return false;
    }

    //* save the contents of MAP data structure into a txt file
    void Stats::save_now( std::ostream& ostream, char delim = ',' )
    {
        for ( unsigned int nRow = 0; nRow < m_nRows; nRow++ )
        {
            for ( unsigned int nCol = 0; nCol < m_nCols; nCol++ )
            {
                ostream << trim( m_oData[std::make_pair( nCol, nRow )] );
                if ( (nCol+1) < m_nCols )
                {
                    ostream << delim;
                }
                else
                {
                    ostream << std::endl;
                }
            }
        }
    }

    void Stats::clear()
    {
        m_oData.clear();
        m_nRows = m_nCols = 0;
    }

    int Stats::getLoad(std::string apn)
    {
        std::pair<unsigned int, unsigned int> p = searchPair(apn);
        int col = p.first;
        int row = p.second;
        if(col == 0 && row != 0) // App name found, update the load info
        {
            return toInt(m_oData[std::make_pair(4, row)]);
        }
        else // App name not available, create a new row
        {
            return 0;
        }
    }

    int Stats::getThreshold(std::string apn)
    {
        std::pair<unsigned int, unsigned int> p = searchPair(apn);
        int col = p.first;
        int row = p.second;
        if(col == 0 && row != 0)
        {
            return toInt(m_oData[std::make_pair(5, row)]);
        }
        else
        {
            return MAX_LOAD;
        }
    }

    bool Stats::isAvailabile(std::string apn)
    {
        std::pair<unsigned int, unsigned int> p = searchPair(apn);
        int col = p.first;
        int row = p.second;
        if(col == 0 && row != 0)
        {
            if(m_oData[std::make_pair(6, row)]=="Y")
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return true;
        }
    }

    void Stats::updateLoad(std::string apn, std::string api, std::string aen, std::string aei, bool increment)
    {
        if(!enableLB) return;

        std::pair<unsigned int, unsigned int> p = searchPair(apn);
        int col = p.first;
        int row = p.second;
        int load = 0;
        if(col == 0 && row != 0) // // This Server App already having more than one connections, update the load info
        {
            load = toInt(m_oData[std::make_pair(4, row)]);
            if(increment)
            {
                m_oData[std::make_pair(4, row)] = this->toString(++load);
                if(load >= toInt(m_oData[std::make_pair(5, row)]))
                {
                    m_oData[std::make_pair(6, row)] = "N";
                }
            }
            else
            {
                if(--load < 0) load = 0;
                if(load < toInt(m_oData[std::make_pair(5, row)]))
                {
                    m_oData[std::make_pair(6, row)] = "Y";
                }
                m_oData[std::make_pair(4, row)] = this->toString(load);
            }
        }

        else // this server app does not have any connection at the moment, create a new entry for it in the Stats.txt
        {
            if(increment)
            {
                row = this->GetRows();
                m_oData[std::make_pair(0,row)]=apn;
                m_oData[std::make_pair(1,row)]=api;
                m_oData[std::make_pair(2,row)]=aen;
                m_oData[std::make_pair(3,row)]=aei;
                m_oData[std::make_pair(4,row)]="1";
                m_oData[std::make_pair(5,row)]=this->toString(MAX_LOAD);
                m_oData[std::make_pair(6,row)]="Y";
                m_nRows++;
            }
        }
        staticData = m_oData;
        staticRows = m_nRows; staticCols = m_nCols;
        //this->save();
    }

    // looks for the column and row number of the APN
    std::pair<unsigned int, unsigned int> Stats::searchPair(std::string str)
    {
        std::map<std::pair<unsigned int, unsigned int>, std::string>::iterator it = m_oData.begin();
        while(it != m_oData.end())
        {
            if(it->second == str && it->first.first==0)
            {
                return it->first;
            }
            it++;
        }
        std::pair<unsigned int, unsigned int> p = std::make_pair(0, 0);
        return p;
    }


   //* Erase a particular row if the APN is no more in use by any client App
    void Stats::rowErase(unsigned int row)
        {
            if (row < m_nRows)
            {
                for ( unsigned int nRow = row+1; nRow < m_nRows; nRow++ )
                {
                    for ( unsigned int nCol = 0; nCol < m_nCols; nCol++ )
                    {
                        m_oData[std::make_pair( nCol, nRow-1)] = m_oData[std::make_pair(nCol, nRow)];
                    }
                }

                for (unsigned int i=0; i<m_nCols; i++)
                {
                    m_oData.erase(std::make_pair(i, m_nRows-1));
                }
                m_nRows--;
            }
        }

    int Stats::rowCount()
    {
        int rows=0;
        std::map<std::pair<unsigned int, unsigned int>, std::string>::iterator it;
        for (it=m_oData.begin(); it!=m_oData.end(); it++)
        {

        }
        it--;
        rows = it->first.second;
        return ++rows;
    }

    std::string Stats::toString(int i)
    {
        std::stringstream stm;
        stm<<i;
        return stm.str();
    }

    int Stats::toInt (std::string str)
    {
        return atoi(str.c_str());
    }

    std::string Stats::getBestAppByAppList(std::string srcApp, std::string dstApp, std::string allApps)
    {
        if(!enableLB) return dstApp;
        if(!allApps.compare("AppErr"))
            return dstApp;
        std::istringstream    lineStream(allApps);
        std::string app, availableApp = dstApp;
        //std::map<std::string, int> appsMap;
        int minLoad = MAX_LOAD;
        int appLoad = 0;
        int appCount = 0;
        //int dstLoad = 0;
        bool ok = false;
        while( std::getline( lineStream, app, ',' ) )
        {
            app = trim(app);
            if (!srcApp.compare(app))
            {
                continue;
            }
            if(!this->isAvailabile(app))
            {
                continue;
            }
            else
            {
                appLoad = this->getLoad(app);
                //appsMap[app] = appLoad;
                appCount++;
                ok = true;
                std::cout <<"Ehsanz: Selection of App: " << app << " Load:" << appLoad<<" "<<std::endl;;
                if(minLoad > appLoad)
                {
                    minLoad = appLoad;
                    availableApp = app;
                }
            }
        }
        if(ok)
        {
            std::cout << " Min load:" << minLoad << " App:"<< availableApp<<std::endl;
            return availableApp;
        }
        else
        {
            std::cout << " Min load:" << minLoad << " App: AppErr"<<std::endl;
            return "AppErr";
        }
    }

    std::string Stats::getBestAppByAEN(std::string srcApp, std::string dstApp, std::string aen)
        {
            if(!enableLB) return dstApp;

            if(!dstApp.compare("AppErr"))
                return dstApp;
            std::string app, aename, availableApp = dstApp;
            int minLoad = MAX_LOAD;
            int appLoad = 0;
            bool ok = false;
            bool aenFound = false;
            //std::cout <<"Ehsanz: AEN: "<<aen<<std::endl;
            for ( unsigned int row = 1; row < m_nRows; row++ )
            {
                aename = m_oData[std::make_pair(2, row)];
                //std::cout <<"Ehsanz: AENAME: "<<aename<<std::endl;
                if(!aename.compare(aen))
                {
                    app = m_oData[std::make_pair(0, row)];
                  //  std::cout <<"Ehsanz: App: "<<app<<std::endl;
                }
                else
                {
                    continue;
                }
                aenFound = true;
                if (!srcApp.compare(app))
                {
                    continue;
                }
                if(m_oData[std::make_pair(6, row)]=="N")
                {
                    continue;
                }
                else
                {
                    appLoad = toInt(m_oData[std::make_pair(4, row)]);
                    ok = true;
                    //std::cout <<"Ehsanz: Selection of App: " << app << " Load:" << appLoad<<" "<<std::endl;;
                    if(minLoad > appLoad)
                    {
                        minLoad = appLoad;
                        availableApp = app;
                    }
                }
            }
            if(ok)
            {
                //std::cout << " Min load:" << minLoad << " App:"<< availableApp<<std::endl;
                return availableApp;
            }
            else
            {
                //std::cout << " Min load:" << minLoad << " App: AppErr"<<std::endl;
                if (aenFound)
                    return "AppErr";
                else
                    return dstApp;
            }
        }


    void Stats::printStatus()
    {
        std::cout<<"Ehsanz: Printing Status File: Rows="<<staticRows<<" Cols="<<staticCols<<std::endl;
        for ( unsigned int nRow = 0; nRow < m_nRows; nRow++ )
        {
            for ( unsigned int nCol = 0; nCol < m_nCols; nCol++ )
            {
                std::cout << trim( Stats::staticData[std::make_pair( nCol, nRow )] );
                    if ( (nCol+1) < m_nCols )
                    {
                        std::cout << ",";
                    }
                    else
                    {
                        std::cout << std::endl;
                    }
            }
        }
    }
