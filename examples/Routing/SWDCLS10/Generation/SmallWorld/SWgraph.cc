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

struct nbs
{
  int shortlinks;
  int longlinks; 
};

struct tup
{
  int node;
  int lat; 
};

// Calculates the degree of a node
unsigned int get_degree(map <int, vector <int> > list_neigh, map <int, vector <int> > list_neigh_neigh, int node)
{
  unsigned int d = 0;
  d += list_neigh[node].size() + list_neigh_neigh[node].size();
  return d;
}

int main(int argc, char *argv[])
{
  int numnodes = atoi (argv [1]);
  int numlinks = atoi (argv [2]);
  int longlinks = atoi (argv [3]);
  int randnblinks, randnbLlinks, shortlinks, randlonglinks, randshortlinks;
  int randresource, randlink, randlatency, randband;
  int j = 0;
  map <int, vector<int> > conn;

  ofstream g_file (argv[4]);//"graph1.txt"
  ofstream n_file (argv[5]);//"nodes1.txt"
  ofstream p_file (argv[6]);//"phy1.txt"
  // Outputs to example.txt through a_file
  /* initialize random seed: */  
  srand (time(NULL));
  map<int, /*vector<struct tup*>*/map<int, float> > phy_topology;

  float threshold_closeness;
  std::map<int, float>::iterator it;
  //First Step: Randomly give an estimation of the physical topology between each two nodes in the network: this could be don eby probing between nodes: or we can do it like this:
  //select random nodes from the network and assess the closeness between these nodes and accordingly define the neighbors of the given node
  
  for (int l = 1 ; l<= numnodes; l++)
  {
      for (int m = 1 ; m<= numnodes; m++)
      {
	if (m!=l)
	{
	  randlatency = rand() % 90 + 10; //10 is the minimum and optimal latency between two nodes
	  it = phy_topology[m].find(l); //find (phy_topology[m].begin(), phy_topology[m].end(), l);
	  if ((it != phy_topology[m].end()) /*&& (l==(*it).first)*/)
	  {
	    phy_topology[l][m] = (*it).second;

	  }
	  else
	  {
	    phy_topology[l][m] = randlatency;

	  }
	}
	else
	{
	    phy_topology[l][m] = 0;
	}
	
      } 
  }
  
  for (map<int, map<int, float> >::iterator it = phy_topology.begin(); it != phy_topology.end(); it++)
  {

    for (map<int, float>::iterator itt = it->second.begin(); itt != it->second.end(); itt++)
    {
	p_file<<it->first<<" "<<itt->first<<" "<<itt->second<<endl;
	cout<<it->first<<" "<<itt->first<<"  "<<itt->second<<endl;
    }
  }
  
  //Generate nodes file: with number of links + capacity for each node
  map <int, struct nbs > nb_links;
  for (int k = 1 ; k<= numnodes; k++)
  {
      randresource = rand() % 100; 
      randnblinks = rand() % (numlinks-5) + 20;//5 minimum of links for 10 nodes in the overlay//10 for 50 nodes// 15 for 100 nodes
      do
      {
      randlonglinks = rand() % (longlinks-1) + 2; // 1 is minimum of long links for 10 nodes in the overlay  2 for 100 nodes
      }while (randlonglinks >= randnblinks);
      randshortlinks = /*rand() % */(randnblinks - randlonglinks);
      cout<<"numlinks "<<numlinks<<" randnblinks "<<randnblinks<<" randlonglinks "<<randlonglinks<<" randshortlinks "<<randshortlinks<<endl;
      n_file<<k<<" "<<randnblinks<<" "<<randresource<<endl; //nodeID--NbLinks--availableResources
      nb_links[k].shortlinks = randshortlinks;
      nb_links[k].longlinks = randlonglinks;
  }

  //Generate small-world like graph file
  //First Iteration Connect each node to its neighbors: the output is a list of neighbors for each node
  threshold_closeness = 30;
  map<int, int> links;
  map <int, vector <int> > list_neigh;
  
  //Initialization of Links
  for (int l = 1 ; l<= numnodes; l++)
  {
    links[l] = 0;
  }
  
  for (int l = 1 ; l<= numnodes; l++)
  {
     
      for (int m = 1 ; m<= numnodes; m++)
      {
	if (phy_topology[l][m] <= threshold_closeness)
	{
	  if(links[l]<(nb_links[l].shortlinks) && (l!=m) && links[m]<(nb_links[m].shortlinks))
	  {
	    if (find (list_neigh[l].begin(), list_neigh[l].end(), m) == list_neigh[l].end())
	    {
	      list_neigh[l].push_back(m);
	      list_neigh[m].push_back(l);
	      randband = rand()% 20 + 80;
	      g_file<<l<<" "<<m<<" "<<phy_topology[l][m]<<" "<<randband<<" 0"<<endl; 
	      j++;
	      links[l]++;
	      links[m]++;
	    }
	  }
	}
      }
  }

  //Second Iteration: Connect with the closest neighbors of neighbors
  threshold_closeness = 50;
  map <int, vector <int> > list_neigh_neigh;
  for (int i = 1 ; i<= numnodes; i++)
  {
//     j = links[i]/*nb_links[i].shortlinks-1*/;
      for (int j = 1 ; j<= list_neigh[i].size(); j++)
      {
	if (j!=i)
	{
	for (int a = 1 ; a<= list_neigh[j].size(); a++)
	{
	if (i!=a)
	{
	  if ((phy_topology[i][a] <= threshold_closeness)   && (links[a]<(nb_links[a].shortlinks + nb_links[a].longlinks)))  
	  {
	    if(links[i]<(nb_links[i].shortlinks + nb_links[i].longlinks) /*&& (i!=a) *//*&& (links[a]<(nb_links[a].shortlinks + nb_links[a].longlinks))*/)
	    {
	      if ((find (list_neigh[i].begin(), list_neigh[i].end(), a) == list_neigh[i].end()) && (find (list_neigh_neigh[i].begin(), list_neigh_neigh[i].end(), a) == list_neigh_neigh[i].end()))
	      {
		/*list_neigh_neigh*/list_neigh[i].push_back(a);
		/*list_neigh_neigh*/list_neigh[a].push_back(i);
		randband = rand()% 20 + 80;
		g_file<<i<<" "<<a<<" "<<phy_topology[i][a]<<" "<<randband<<" 0"<<endl; 
// 		j++;
		links[i]++;
		links[a]++;
	      }
	    }
	  }
	}
	}
	}
      }    
  }

  //Third Step:  Rewire the edges of each node with a probabilty beta to other nodes in the overlay (not neighbors or neighbors of neighbors)
  //To avoid network partitionning instead of rewire: add edges??
  float p = 0.5;
  for (int i = 1 ; i<= numnodes; i++)
  {    
//       j = links[i]/*nb_links[i].shortlinks + nb_links[i].longlinks*/;
      for (int j = 1 ; j<= list_neigh[i].size(); j++)
      {
	float prob = (float)rand()/(float)RAND_MAX;
	
	if ((prob < p)  && get_degree(list_neigh, list_neigh_neigh, j) > 1 /*&& get_degree(list_neigh, list_neigh_neigh, i) != g->size-1*/)  
	{
	    //Disconnect this edge between i and j: either try to find away to remove it from the file or just add this links!!  whthout removing them !!
	   // list_neigh[i].erase(std::remove(list_neigh[i].begin(), list_neigh[i].end(), j), list_neigh[i].end());
	   // list_neigh[j].erase(std::remove(list_neigh[j].begin(), list_neigh[j].end(), i), list_neigh[j].end());
	    
	  //Find another node to build the new edge: random?
	    do
	    {	      
	      randlink = rand() % (numnodes-1) + 1;
	    }while (randlink == i /*|| links[randlink] < numlinks */ || (find (list_neigh[i].begin(), list_neigh[i].end(), randlink) != list_neigh[i].end()));
	    
	    if (links[i] < numlinks   && links[randlink] < numlinks)
	    {
	      cout<<"nodes "<<i<<" "<<randlink<<" "<<links[i]<<" numlinks "<<numlinks<<endl;
	      list_neigh/*_neigh*/[i].push_back(randlink);
	      list_neigh/*_neigh*/[randlink].push_back(i);
	      randband = rand()% 20 + 80;
	      g_file<<i<<" "<<randlink<<" "<<phy_topology[i][randlink]<<" "<<randband<<" 0"<<endl; 	  
// 	      j++;
	      links[i]++;
	      links[randlink]++;
	    }
	}
      }
  }
  
  

  n_file.close();
  g_file.close();
  p_file.close();
}
