/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

/** Copyright (c) 2015-2016, IMT-TSP, EU FP7 PRISTINE project
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation;
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*
* Author: Fatma Hrizi <fatma.hrizi@telecom-sudparis.eu>
*/ 

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <map>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

int checkconnections (int n, map <int, vector<int> > conn)
{
      return conn[n].size();
}

struct phy
{
  int dst; 		
  float phy; 		
};


int main(int argc, char *argv[])
{
  int numnodes = atoi (argv [1]);
  int numlinks = atoi (argv [2]);
  int randnblinks;
  int randresource, randlink, randlatency, randband;
  float latency;
  string line;
  int j = 0;
  map <int, vector<int> > conn;

  ofstream g_file (argv[3]);//"graph1.txt"
  ofstream n_file (argv[4]);//"nodes1.txt"
  // Outputs to example.txt through a_file
  
    /* initialize random seed: */  
  srand (time(NULL));
  
  
  //Generate nodes file
  for (int k = 1 ; k<= numnodes; k++)
  {
      randresource = rand() % 100; 
      n_file<<k<<" "<<numlinks<<" "<<randresource<<endl; //nodeID--NbLinks--availableResources
  }

  
  ifstream phyfile ("swphy150.txt");
  map<int, vector<struct phy> > phydata;
  int origin, dst, value, originold;
  
   if (phyfile.is_open())
  {
    while ( getline (phyfile,line) )
    {
      istringstream ss(line);

      ss >> origin >> dst >> value;
      struct phy p;
      p.dst = dst;
      p.phy = value;
      phydata[origin].push_back(p);
//       cout << origin<<" " <<p.dst<<" "<<p.phy<<endl;
//       cout << line << '\n';
    }    
  }
  
  //Generate graph file
	std::vector<int>::iterator it;
  for (int i = 1 ; i<= numnodes; i++)
  {
      //random number of links = rand()
      randnblinks = rand() % (numlinks-5) + 2;
      
      if (checkconnections (i, conn) == 0)
      {
      while (j<randnblinks)
      {
	randlink = rand() % numnodes + 1;
	it = find (conn[i].begin(), conn[i].end(), randlink);
	while (checkconnections (randlink, conn) >= randnblinks  /*|| (it != conn[i].end())*/ )
	{  cout<<"i is "<<i<<"randnblinks "<<randnblinks<<endl;
	  randlink = rand() % numnodes + 1;
	}
	if (i != randlink)
	{
	    for (int s =0; s<phydata[i].size(); s++)
	    {
		if (randlink == phydata[i][s].dst)
		  latency = phydata[i][s].phy;
	    }
// 	    randlatency = rand() % 100;
	    randband = rand()% 100;
	    g_file<<i<<" "<<randlink<<" "<<latency<<" "<<randband<<" 0"<<endl; //from--to--weight
	    conn[i].push_back(randlink);
	    conn[randlink].push_back(i);
	}
	j++;  
      }
      j=0;
      }
      else if (checkconnections (i, conn) >= 1)
      {
      j = checkconnections (i, conn);
      while (j<randnblinks)
      {
	randlink = rand() % numnodes + 1;
	it = find (conn[i].begin(), conn[i].end(), randlink);
	while ((checkconnections (randlink, conn) >= randnblinks) || (it != conn[i].end())  )
	{  cout<<"randlink"<<endl;
	  randlink = rand() % numnodes + 1;
	  it = find (conn[i].begin(), conn[i].end(), randlink);
	}
	if (i != randlink)
	{
	    for (int s =0; s<phydata[i].size(); s++)
	    {
		if (randlink == phydata[i][s].dst)
		  latency = phydata[i][s].phy;
	    }
// 	    randlatency = rand() % 100;
	    randband = rand()% 100;
	    g_file<<i<<" "<<randlink<<" "<<latency<<" "<<randband<<" 0"<<endl; //from--to--weight
	    conn[i].push_back(randlink);
	    conn[randlink].push_back(i);
	}
	j++; 
      }
	j=0;
      }
      else
      {
	j=0;
	continue;
      }
  }
  cout<<"end"<<endl;
  n_file.close();
  g_file.close();
    phyfile.close();
}
