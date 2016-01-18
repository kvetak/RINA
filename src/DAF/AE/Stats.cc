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

#include "Stats.h"


    Stats::Stats(void)
    {
        m_nCols = 0; m_nRows = 0;

        filename = "stats.txt";
        delim = ',';
        this->open( );
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

    /* Load the file in MAP data structure */
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
                nCol++;
            }
            m_nCols = std::max( m_nCols, nCol );
            m_nRows++;
        }
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

    /* save the contents of MAP data structure into a txt file */
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
            //EV << "Ehsanz: App found";
            return toInt(m_oData[std::make_pair(4, row)]);
        }
        else // App name not available, create a new row
        {
            //EV << "Ehsanz: App Not found";
            return 0;
        }
    }

    void Stats::updateLoad(std::string apn, std::string api, std::string aen, std::string aei, bool increment)
    {
        std::pair<unsigned int, unsigned int> p = searchPair(apn);
        int col = p.first;
        int row = p.second;
        int load = 0;
        if(col == 0 && row != 0) // // This Server App already having more than one connections, update the load info
        {
            EV << "Ehsanz: App found"<<std::endl;
            load = toInt(m_oData[std::make_pair(4, row)]);
            if(increment)
            {
                EV << "Ehsanz: Incrementing "<<load<<std::endl;
                m_oData[std::make_pair(4, row)] = this->toString(++load);
            }
            else
            {
                if(--load==0)
                {
                    this->rowErase(row);
                }
                else
                {
                    EV << "Ehsanz: Decremented "<<load<<std::endl;
                    m_oData[std::make_pair(4, row)] = this->toString(load);
                }
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
                m_nRows++;
            }
        }
        this->save();
    }

    /* looks for the column and row number of the APN */
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


    /* Erase a particular row if the APN is no more in use by any client App  */
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

    std::string Stats::getBestApp(std::string srcApp, std::string dstApp, std::string allApps)
    {
        if(!allApps.compare("AppErr"))
            return dstApp;
        std::istringstream    lineStream(allApps);
        std::string app, availableApp = dstApp;
        //std::map<std::string, int> appsMap;
        int minLoad = MAX_LOAD;
        int appLoad = 0;
        int appCount = 0;
        //int dstLoad = 0;

        while( std::getline( lineStream, app, ',' ) )
        {
            app = trim(app);
            if (!srcApp.compare(app))
            {
                continue;
            }
            else
            {
                appLoad = getLoad(app);
                //appsMap[app] = appLoad;
                appCount++;
                EV <<"Ehsanz: Selection of App: " << app << "Load:" << appLoad;
                if(minLoad > appLoad)
                {
                    minLoad = appLoad;
                    availableApp = app;
                }
            }
        }
        EV << " Min load:" << minLoad << " App:"<< availableApp<<std::endl;
        return availableApp;
    }
