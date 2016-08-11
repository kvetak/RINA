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
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <climits>
#include "CW.h"

using namespace std;
#define INFINITY INT_MAX
struct shortDist
{
  int distance; 	//Shorter Distance
  int nh; 		//Next hop
  
};

//Small world graph construction:
//1) First step connstruct the graph;

//2) Second step call CW.findclusters algorithm;
//3) Slection in each sub-graph of the Group Leaders;
//4) Build a new graph between selected Group Leaders;
//5) Call step 2: rerun the CW algorithm for the new graph (constructed in the previous step);

  
struct node* getNode(int id, std::vector<struct node>  nodes)
{
   for (std::vector<struct node>::iterator it = nodes.begin() ; it != nodes.end(); ++it)
   {
     if ((*it).id == id)
     {
	struct node * nodepoint = new node;
	nodepoint->id = (*it).id; 
	nodepoint->nb_links = (*it).nb_links;
	nodepoint->available_resources = (*it).available_resources;
        return nodepoint;
     }
   }   
   return NULL;
}


map <int,struct shortDist>  BellmanFord(Graph graph, Graph graph2, int src,  std::vector<struct node>  nodes) 
{
    int i, j;
    map <int,struct shortDist>  d;
   
    //merge two graphs together
    Graph graphmerged (1024*1024, 10);
    vector <Edge> edges;
    for (int k = 0 ; k < graph.getNodes().size(); k++)
    {      
	  struct node * n = getNode (graph.getNodes()[k].id, nodes); 
	  if (n!=NULL)
	  {
	    edges.clear();
	    edges = graph.getEdges(n);
	    for (int l=0; l < (graph2.getEdges(n)).size() ; l++)
	    {
	     edges.push_back((graph2.getEdges(n))[l]); 
	    }
	    graphmerged.addNode (n);
	    graphmerged.addNode (n, edges);
	  }
    }
    
    
    for (int k = 0 ; k < graphmerged.getNodes().size(); k++)
    {
	    d[graphmerged.getNodes()[k].id].distance = INT_MAX;
	    d[graphmerged.getNodes()[k].id].nh = -1;
    }
    
    d[src].distance = 0;
    d[src].nh = src;
    float weight;
 
    for (int k = 0 ; k < graphmerged.getNodes().size(); k++)
    {
      struct node * nl = getNode (graphmerged.getNodes()[k].id, nodes);
      if (nl != NULL)
      {
      for (int l=0; l < (graphmerged.getEdges(nl)).size() ; l++)
      {
	    weight = (graphmerged.getEdges(nl))[l].getWeigth()->latency;
            if (d[graphmerged.getNodes()[k].id].distance + weight < d[((graphmerged.getEdges(nl)[l].getSource())->id)].distance) {
                d[(graphmerged.getEdges(nl)[l].getSource())->id].distance = d[graphmerged.getNodes()[k].id].distance + weight;
		d[(graphmerged.getEdges(nl)[l].getSource())->id].nh = graphmerged.getNodes()[k].id;
	    }
            if (d[((graphmerged.getEdges(nl)[l].getSource())->id)].distance + weight < d[graphmerged.getNodes()[k].id].distance) {
                d[graphmerged.getNodes()[k].id].distance = d[((graphmerged.getEdges(nl)[l].getSource())->id)].distance + weight;
		d[graphmerged.getNodes()[k].id].nh = ((graphmerged.getEdges(nl)[l].getSource())->id);
	    }
      }
      }
    }
      return d;
}


int main (int argc, char *argv[])

{
    
//1) First step construct the graph;
  
  int maxnumbEdgespNode = 5;
  Graph graph (1024*1024, maxnumbEdgespNode);
  CW cw; //You get the error because compiler thinks of function declaration
  
  int lastNode=0;
  int numEdgesCurrNode = 0;
  double minEdgeWeight = 0;
  std::map<int, vector <Edge > > edges, edges2, edges3;
  std::map<int, vector<Edge> > conciselist;
  std::vector<int>  nodes;
  std::vector<struct node>  nodesdata;

    srand (time(NULL));

     cout <<"heeerre "<<argv[0]<<endl;
  ifstream edgesfile (argv[1]);// ("swgraph.txt");
  ifstream nodesfile (argv[2]);// ("swnodes.txt");
  string line;
  float from, to, latency, bandwidth, ber;

  if (nodesfile.is_open())
  {
    while ( getline (nodesfile,line) )
    {
      istringstream ss(line);
      int id, nblinks, cap;

      ss >> id >> nblinks >> cap;
      struct node n;
      n.id = id;
      n.nb_links = nblinks;
      n.available_resources = cap;
      nodesdata.push_back (n);
    }    
    nodesfile.close();
  }
  

  if (edgesfile.is_open())
  {
    while (getline (edgesfile,line) )
    {
      istringstream ss(line);

      ss >> from >> to >> latency >> bandwidth >> ber;
            
      lastNode = from;

      if ((latency >= minEdgeWeight)  && (bandwidth >= minEdgeWeight)  && (ber >= minEdgeWeight))
      { 
	if (to != from)
	{
	  vector<int>::iterator it = std::find(nodes.begin(), nodes.end(), to);

	  if(it==nodes.end()){

          nodes.push_back (to);
	  }
	  it =  std::find(nodes.begin(), nodes.end(), from);
	  if(it==nodes.end()){
	  nodes.push_back (from);
	  }
	  struct node * tonnode = getNode (to, nodesdata);
      
	  struct weight* m_weight = new weight;
	  m_weight->latency = latency;
	  m_weight->bandwidth = bandwidth;
	  m_weight->ber = ber;
	  Edge e (tonnode , m_weight);
	  edges[from].push_back(e);
	  
	    struct node * fromnnode = getNode (from, nodesdata);
	    struct weight* m_weightf = new weight;
	    m_weightf->latency = latency;
	    m_weightf->bandwidth = bandwidth;
	    m_weightf->ber = ber;
	    Edge ef (fromnnode , m_weightf);
	    edges[to].push_back(ef);
	}
      }
      
    }   
    
    for (std::vector<int>::iterator it=nodes.begin(); it!=nodes.end(); ++it) 
    {      
	  graph.addNode (getNode(*it, nodesdata));
	  graph.addNode (getNode(*it, nodesdata), edges[*it]);
    }

    edgesfile.close();
  }
  
// //2) Second step call CW.findclusters algorithm; 
   map<int, vector<struct node > > clusters = cw.findClusters(graph);
   
   bool ok = false;
   vector <int> disconnect;
   //Make sure that in each clusters nodes are connected otherwise move the "not connected" node to its neighbor's group
   for (std::map<int, vector<struct node > >::iterator itcluster=clusters.begin(); itcluster!=clusters.end(); ++itcluster) 
   {
      for (int m = 0; m<((*itcluster).second).size(); m++)
      {
	struct node * nod1 = getNode (((*itcluster).second)[m].id/*itnode1->id*/, nodesdata);
	for (int l = 0; l<((*itcluster).second).size(); l++)
	{
	    struct node * nod2 = getNode (((*itcluster).second)[l].id/*itnode2->id*/, nodesdata);
	    if (nod1->id != nod2->id)
	    {
	      for (int i = 0; i < (graph.getEdges(nod1)).size() ; i++)
	      {
		if ((graph.getEdges(nod1))[i].getSource ()->id == nod2->id)
		  ok = true;
	      }
	    }
	}
	if (ok == false)
	{
	  disconnect.push_back(nod1->id);
	}
	ok = false;
      }
   
   }
   
   int cluster_neigh, cluster, id_cluster;
   for (int i = 0; i<disconnect.size(); i++)
   {
     struct node * nn = getNode (disconnect[i], nodesdata);
     int r = rand() % (graph.getEdges(nn)).size();
     struct node * nnn = getNode ((graph.getEdges(nn))[r].getSource ()->id, nodesdata);

     for (std::map<int, vector<struct node > >::iterator itcluster=clusters.begin(); itcluster!=clusters.end(); ++itcluster) 
     {
       for (int m = 0; m<((*itcluster).second).size(); m++)
      {
	if(((*itcluster).second)[m].id == nnn->id)
	  cluster_neigh = (*itcluster).first;
	if(((*itcluster).second)[m].id == nn->id)
	{
	  cluster = (*itcluster).first;
	  id_cluster = m;
	}
      }
     }
     //remove the disconnected node from the old culster
     clusters[cluster].erase(clusters[cluster].begin()+id_cluster);
     
     //add the disconnected node to the picked cluster
     clusters[cluster_neigh].push_back(*nn);
   }
   
//3) Slection in each su-graph of the Group Leaders;
   double maxcap = -10000, maxlinks = 0, cap =0, lat = 0;
   int idmaxcap = 0, idmaxcapcan=0;
   std::map <int,int> groupLeaders;
   std::map <int,int> candidateLeaders;
   int nbGL = 0;
   
   for (std::map<int, vector<struct node > >::iterator itcluster=clusters.begin(); itcluster!=clusters.end(); ++itcluster) 
   {
      for (std::vector<struct node >::iterator itnode = ((*itcluster).second).begin() ; itnode != ((*itcluster).second).end(); ++itnode)
      {
      
	struct node * nod = getNode (itnode->id, nodesdata);
	if ((graph.getEdges(nod)).size() > maxlinks)
	{
	  maxlinks = graph.getEdges(nod).size();
	  for (int i =0; i < (graph.getEdges(nod)).size() ; i++)
	  {
	    lat += (((graph.getEdges(nod))[i].getWeigth()->latency));
	  }
	  cap = (-0.5 * lat) + (0.5* maxlinks);
	  if (cap > maxcap)
	  {
	    maxcap = cap;
	    idmaxcap = itnode->id;
	  }
	  lat = 0;
	}
      }
      groupLeaders[(*itcluster).first]=idmaxcap;
      maxlinks = 0;
      maxcap = -10000;
      
   }
   
      
   //To avoid failure: Elect group Candidate
   idmaxcapcan=0;
      for (std::map<int, vector<struct node > >::iterator itcluster=clusters.begin(); itcluster!=clusters.end(); ++itcluster) 
      {
      for (std::vector<struct node >::iterator itnode = ((*itcluster).second).begin() ; itnode != ((*itcluster).second).end(); ++itnode)
      {
	if (itnode->id!=groupLeaders[(*itcluster).first])
	{
	struct node * nod = getNode (itnode->id, nodesdata);
	if ((graph.getEdges(nod)).size() > maxlinks)
	{
	  maxlinks = graph.getEdges(nod).size();
	  lat = 0;
	  for (int i =0; i < (graph.getEdges(nod)).size() ; i++)
	  {
	    lat += (((graph.getEdges(nod))[i].getWeigth()->latency));
	  }
	  cap = (-0.5 * lat) + (0.5* maxlinks);
	  if (cap > maxcap)
	  {
	    maxcap = cap;
	    idmaxcapcan = itnode->id;
	  }
	}
	}
      }
      maxlinks = 0;
      maxcap = -10000;
   }
   
    
    
  ifstream phyfile  (argv[3]);//("swphy.txt");
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
    }    
  }
   
    phyfile.close();
//4) Build a new graph between selected Group Leaders;
    nodes.clear();
    //edges.clear(); //maintain edges to see if the new edge exist!
    Graph graph2 (1024*1024, maxnumbEdgespNode);
    Graph graph3 (1024*1024, maxnumbEdgespNode);
    int i,j; 
    float latencyy= 10;
    bool there = false, there1 = false, itshere=false;
    
    for (std::map<int, int>::iterator it=groupLeaders.begin();it!=groupLeaders.end();it++)
    {
	//getNode (it->second, nodesdata);
	from = it->second;	
        for ( std::map<int, int>::iterator it2=groupLeaders.begin();it2!=groupLeaders.end();it2++)
	{
	to = it2->second;
	
	if (to != from)
	{

	  if(std::find(nodes.begin(), nodes.end(), to) == nodes.end()){
          nodes.push_back (to);
	  }
	  if(std::find(nodes.begin(), nodes.end(), from) == nodes.end()){
	  nodes.push_back (from);
	  }
	  struct node * tonnode = getNode (to, nodesdata);
	  if (tonnode!=NULL)
	  {
	  
	  struct weight* m_weight = new weight;
	  for (int s =0; s<phydata[from].size(); s++)
	  {
	    if (to == phydata[from][s].dst)
	      latencyy = phydata[from][s].phy;
	  }
	  for (int s =0; s<phydata[to].size(); s++)
	  {
	    if (from == phydata[to][s].dst)
	      latencyy = phydata[to][s].phy;
	  }
	  m_weight->latency = latencyy/*10*/;
	  m_weight->bandwidth = 100;
	  m_weight->ber = 0;
	  Edge e (tonnode , m_weight);
	  itshere = false;
	  for (int b = 0; b< edges3[from].size(); b++)
	  {
	    if (edges3[from][b].getSource()->id == e.getSource()->id)
	      itshere = true;
	  }
	  if (itshere == false)
	    edges3[from].push_back(e);
	  struct node * fromnnode = getNode (from, nodesdata);
	  struct weight* m_weightf = new weight;
	  m_weightf->latency = latency;
	  m_weightf->bandwidth = bandwidth;
	  m_weightf->ber = ber;
	  Edge ef (fromnnode , m_weightf);
	  itshere = false;
	  for (int b = 0; b< edges3[to].size(); b++)
	  {
	    if (edges3[to][b].getSource()->id == ef.getSource()->id)
	      itshere = true;
	  }
	  if (itshere == false)
	    edges3[to].push_back(ef);
	  
	  
	  if (edges.find(from) == edges.end()) 
	  {
	    edges2[from].push_back(e);
	  } 
	  else
	  {
	    there = false;
	    for (int k = 0; k< edges[from].size(); k++)
	    {
	      if (to == edges[from][k].getSource()->id)
		there=true;
	    }
	    for (int k = 0; k< edges2[to].size(); k++)
	    {
	      if (from == edges2[to][k].getSource()->id)
		there=true;
	    }
	     if (there != true)
	     {
	      edges2[from].push_back(e);
	     }
	    }
	  
	}
	}
	}
    }
    
    for(std::map<int, int>::iterator it=candidateLeaders.begin();it!=candidateLeaders.end();it++)
    {

	from = it->second;
	
        for ( std::map<int, int>::iterator it2=candidateLeaders.begin();it2!=candidateLeaders.end();it2++)
	{
	to = it2->second;
	if (to != from)
	{

	  if(std::find(nodes.begin(), nodes.end(), to) == nodes.end()){
          nodes.push_back (to);
	  }
	  if(std::find(nodes.begin(), nodes.end(), from) == nodes.end()){
	  nodes.push_back (from);
	  }
	  struct node * tonnode = getNode (to, nodesdata);
	  if (tonnode!=NULL)
	  {
	  
	  struct weight* m_weight = new weight;
	  for (int s =0; s<phydata[from].size(); s++)
	  {
	    if (to == phydata[from][s].dst)
	      latencyy = phydata[from][s].phy;
	  }
	  for (int s =0; s<phydata[to].size(); s++)
	  {
	    if (from == phydata[to][s].dst)
	      latencyy = phydata[to][s].phy;
	  }
	  m_weight->latency = latencyy/*10*/;
	  m_weight->bandwidth = 100;
	  m_weight->ber = 0;
	  Edge e (tonnode , m_weight);
	  itshere = false;
	  for (int b = 0; b< edges3[from].size(); b++)
	  {
	    if (edges3[from][b].getSource()->id == e.getSource()->id)
	      itshere = true;
	  }
	  if (itshere == false)
	    edges3[from].push_back(e);
	  struct node * fromnnode = getNode (from, nodesdata);
	  struct weight* m_weightf = new weight;
	  m_weightf->latency = latency;
	  m_weightf->bandwidth = bandwidth;
	  m_weightf->ber = ber;
	  Edge ef (fromnnode , m_weightf);
	  itshere = false;
	  for (int b = 0; b< edges3[to].size(); b++)
	  {
	    if (edges3[to][b].getSource()->id == ef.getSource()->id)
	      itshere = true;
	  }
	  if (itshere == false)
	    edges3[to].push_back(ef);
	  if (edges.find(from) == edges.end()) 
	  {
	    edges2[from].push_back(e);
	  } 
	  else
	  {
	    there = false;
	    for (int k = 0; k< edges[from].size(); k++)
	    {
	      if (to == edges[from][k].getSource()->id)
		there=true;
	    }
	    for (int k = 0; k< edges2[to].size(); k++)
	    {
	      if (from == edges2[to][k].getSource()->id)
		there=true;
	    }
	     if (there != true)
	     {
	      edges2[from].push_back(e);
	     }
	    }
	  }
	  
	  }

	}
	
    }

     for(std::map<int, int>::iterator it=candidateLeaders.begin();it!=candidateLeaders.end();it++)
      {

	from = it->second;
	
        for ( std::map<int, int>::iterator it2=groupLeaders.begin();it2!=groupLeaders.end();it2++)
	{
	to = it2->second;
	if (to != from)
	{

	  if(std::find(nodes.begin(), nodes.end(), to) == nodes.end()){
          nodes.push_back (to);
	  }
	  if(std::find(nodes.begin(), nodes.end(), from) == nodes.end()){
	  nodes.push_back (from);
	  }
	  struct node * tonnode = getNode (to, nodesdata);
	  if (tonnode!=NULL)
	  {
  
	  struct weight* m_weight = new weight;
	    for (int s =0; s<phydata[from].size(); s++)
	  {
	    if (to == phydata[from][s].dst)
	      latencyy = phydata[from][s].phy;
	  }
	  for (int s =0; s<phydata[to].size(); s++)
	  {
	    if (from == phydata[to][s].dst)
	      latencyy = phydata[to][s].phy;
	  }
	  m_weight->latency = latencyy/*10*/;
	  m_weight->bandwidth = 100;
	  m_weight->ber = 0;
	  Edge e (tonnode , m_weight);
	  itshere = false;
	  for (int b = 0; b< edges3[from].size(); b++)
	  {
	    if (edges3[from][b].getSource()->id == e.getSource()->id)
	      itshere = true;
	  }
	  if (itshere == false)
	    edges3[from].push_back(e);
	  struct node * fromnnode = getNode (from, nodesdata);
	  struct weight* m_weightf = new weight;
	  m_weightf->latency = latency;
	  m_weightf->bandwidth = bandwidth;
	  m_weightf->ber = ber;
	  Edge ef (fromnnode , m_weightf);
	  itshere = false;
	  for (int b = 0; b< edges3[to].size(); b++)
	  {
	    if (edges3[to][b].getSource()->id == ef.getSource()->id)
	      itshere = true;
	  }
	  if (itshere == false)
	    edges3[to].push_back(ef);
	  if (edges.find(from) == edges.end()) 
	  {
	    edges2[from].push_back(e);
	  } 
	  else
	  {
	    there = false;
	    for (int k = 0; k< edges[from].size(); k++)
	    {
	      if (to == edges[from][k].getSource()->id)
		there=true;
	    }
	    for (int k = 0; k< edges2[to].size(); k++)
	    {
	      if (from == edges2[to][k].getSource()->id)
		there=true;
	    }
	     if (there != true)
	     {
	      edges2[from].push_back(e);
	     }
	  }
	  
	  }
	}
	}
    }

    
    for (std::vector<int>::iterator it=nodes.begin(); it!=nodes.end(); ++it) 
    {      
	  graph2.addNode (getNode(*it, nodesdata));
	  graph2.addNode (getNode(*it, nodesdata), edges2[*it]);
    }    
    
    for (std::vector<int>::iterator it=nodes.begin(); it!=nodes.end(); ++it) 
    {      
	  graph3.addNode (getNode(*it, nodesdata));
	  graph3.addNode (getNode(*it, nodesdata), edges3[*it]);
    }
    

    //Configuration Files Generation for simulation run
    //Generate ned file for RINASim
    ofstream ned_file ("sw150test.ned.txt");
    j=0;
    
    ned_file<<"network Scenario"<<std::endl;
    ned_file<<"{"<<std::endl;
    ned_file<<"    submodules:"<<std::endl;
    
    ned_file<<std::endl;
    ned_file<<std::endl;
    ned_file<<std::endl;
    ned_file<<std::endl;
    ned_file<<std::endl;
    ned_file<<std::endl;
	
    int index=1;
    for (std::map<int, vector<struct node > >::iterator itcluster=clusters.begin(); itcluster!=clusters.end(); ++itcluster) 
    {
      for (std::vector<struct node >::iterator itnode = ((*itcluster).second).begin() ; itnode != ((*itcluster).second).end(); ++itnode)
      {
	struct node * n = getNode (itnode->id, nodesdata);
	int s = (graph.getEdges(n)).size() + (graph2.getEdges(n)).size();

	 for (int m = 0; m<(graph2.getNodes()).size(); m++)
	  {
	  struct node * ng2 = getNode ((graph2.getNodes())[m].id, nodesdata);
	  if (ng2!=NULL)
	  {
	    for (int a = 0; a < (graph2.getEdges(ng2)).size() ; a++)
	    {
	      if (((graph2.getEdges(ng2))[a].getSource())->id == n->id)
		s++;
	      
	    }
	  }
	  }
      ned_file<<"        VIFIBN"<<itnode->id<<": VIFIBNode"<< s<<" {"<<std::endl;
      if ((index % 2)  != 0)
      ned_file<<"        @display(\"p="<<(100*index)+(rand() % (10) )<<","<<(rand() % (100) )<<"\");"<<std::endl;
      else
      ned_file<<"        @display(\"p="<<(300*index)+(rand() % (10) )<<","<<(rand() % (100)) + 500<<"\");"<<std::endl;
      ned_file<<"        }"<<std::endl;    
      }
      index++;
      
    }
    
        ned_file<<std::endl;
        ned_file<<std::endl;
        ned_file<<std::endl;
        ned_file<<std::endl;
        ned_file<<std::endl;
        ned_file<<std::endl;
      ned_file<<"      connections:"<<std::endl;
      conciselist.clear();
    for (int l =0; l < (graph.getNodes()).size() ; l++)
    {
      struct node * nn = getNode ((graph.getNodes())[l].id, nodesdata);
      if (nn!=NULL)
      {
	for (i =0; i < (graph.getEdges(nn)).size() ; i++)
	{
	    there1 = false;
	    for (map<int, vector<Edge> >::iterator it = conciselist.begin(); it != conciselist.end(); ++it)
	    {
	      if (nn->id == it->first)
		there1=true;
	    }
	    there = false;
	    for (int k = 0; k< conciselist[nn->id].size(); k++)
	    {
	      if (((graph.getEdges(nn))[i].getSource())->id == conciselist[nn->id][k].getSource()->id)
		there=true;
	    }
	    for (int k = 0; k< conciselist[((graph.getEdges(nn))[i].getSource())->id].size(); k++)
	    {
	      if (nn->id == conciselist[((graph.getEdges(nn))[i].getSource())->id][k].getSource()->id)
		there=true;
	    }
	     if (there != true)
	     {
		conciselist[nn->id].push_back((graph.getEdges(nn))[i]);
	     }
	 }	
      }
    }  

    
    int index1;
    for (std::map<int, vector<Edge > >::iterator itmap=conciselist.begin(); itmap!=conciselist.end(); ++itmap) 
    {
	for (std::vector<Edge>::iterator itvect = itmap->second.begin(); itvect != itmap->second.end() ; ++itvect)
	{
	    ned_file<<"        VIFIBN"<<itmap->first<<".medium++"<<" <--> DatarateChannel {  delay = "<<(itvect->getWeigth()->latency)<<"ms; datarate ="<< (itvect->getWeigth()->bandwidth)<<"Mbps; ber = 0;} <--> VIFIBN"<<(itvect->getSource())->id<<".medium++;"<<std::endl;
	}	
    } 
      
    for (int l =0; l < (graph2.getNodes()).size() ; l++)
    {   
	  struct node * nn = getNode ((graph2.getNodes())[l].id, nodesdata);
          if (nn!=NULL)
	  {
	    for (i =0; i < (graph2.getEdges(nn)).size() ; i++)
	    {
	      ned_file<<"        VIFIBN"<<nn->id<<".medium++"<<" <--> DatarateChannel {  delay = "<<((graph2.getEdges(nn))[i].getWeigth()->latency)<<"ms; datarate ="<< ((graph2.getEdges(nn))[i].getWeigth()->bandwidth)<<"Mbps; ber = 0;} <--> VIFIBN"<<((graph2.getEdges(nn))[i].getSource())->id<<".medium++;"<<std::endl;
	    }
	  }
    }
    
    ned_file.close();
  
    //Generate ini file for RINASim
    ofstream ini_file ("sw150test.ini.txt");
    
    //APP
    for (int l =0; l < (graph.getNodes()).size() ; l++)
    {
      ini_file<<" **.VIFIBN"<<graph.getNodes()[l].id<<".AP.apName = \"App"<<graph.getNodes()[l].id<<"\""<<std::endl;
    }
    ini_file<<"**.applicationEntity.aeType 	= \"AEMyPing\""<<std::endl;
    ini_file<<"**.iae.aeName 			= \"MyPing\""<<std::endl;
    //ini_file<<<<std::endl;
    
    ini_file<<std::endl;
    ini_file<<std::endl;
    
    //ShimDIF
    map<int,int> increment;
    for (std::map<int, vector<Edge > >::iterator itmap=conciselist.begin(); itmap!=conciselist.end(); ++itmap) 
    {
	for (std::vector<Edge>::iterator itvect = itmap->second.begin(); itvect != itmap->second.end() ; ++itvect)
	{
	  ini_file<<"**.VIFIBN"<<itmap->first<<".ShimIPC"<<increment[itmap->first]<<".difName 		= \"Shim"<<itmap->first<<"To"<<(itvect->getSource())->id<<"\""<<std::endl;
	  ini_file<<"**.VIFIBN"<<itmap->first<<".ShimIPC"<<increment[itmap->first]<<".ipcAddress 	 	    = \"1\""<<std::endl;
	  ini_file<<"**.VIFIBN"<<(itvect->getSource())->id<<".ShimIPC"<<increment[(itvect->getSource())->id]<<".difName 		= \"Shim"<<itmap->first<<"To"<<(itvect->getSource())->id<<"\""<<std::endl;
	  ini_file<<"**.VIFIBN"<<(itvect->getSource())->id<<".ShimIPC"<<increment[(itvect->getSource())->id]<<".ipcAddress 	 	    = \"2\""<<std::endl;
	  increment[itmap->first]++;
	  increment[(itvect->getSource())->id]++;
	}	
    } 
    
    
    ini_file<<std::endl;
    ini_file<<std::endl;
    for (int l =0; l < (graph2.getNodes()).size() ; l++)
    {   
	  struct node * nn = getNode ((graph2.getNodes())[l].id, nodesdata);
          if (nn!=NULL)
	  {
	    for (i =0; i < (graph2.getEdges(nn)).size() ; i++)
	    {
	      ini_file<<"**.VIFIBN"<<nn->id<<".ShimIPC"<<increment[nn->id]<<".difName 		= \"Shim"<<nn->id<<"To"<<((graph2.getEdges(nn))[i].getSource())->id<<"\""<<std::endl;
	      ini_file<<"**.VIFIBN"<<nn->id<<".ShimIPC"<<increment[nn->id]<<".ipcAddress 	 	    = \"1\""<<std::endl;
	      ini_file<<"**.VIFIBN"<<((graph2.getEdges(nn))[i].getSource())->id<<".ShimIPC"<<increment[((graph2.getEdges(nn))[i].getSource())->id]<<".difName 		= \"Shim"<<nn->id<<"To"<<((graph2.getEdges(nn))[i].getSource())->id<<"\""<<std::endl;
	      ini_file<<"**.VIFIBN"<<((graph2.getEdges(nn))[i].getSource())->id<<".ShimIPC"<<increment[((graph2.getEdges(nn))[i].getSource())->id]<<".ipcAddress 	 	   = \"2\""<<std::endl;
	      
	      increment[nn->id]++;
	      increment[((graph2.getEdges(nn))[i].getSource())->id]++;
	    }
	  }
    }
    
    
    ini_file<<std::endl;
    ini_file<<std::endl;
    
    //GDIF
    index=1;
    for (std::map<int, vector<struct node > >::iterator itcluster=clusters.begin(); itcluster!=clusters.end(); ++itcluster) 
    {
      ini_file<<"#G"<<index<<"DIF"<<std::endl;
      for (std::vector<struct node >::iterator itnode = ((*itcluster).second).begin() ; itnode != ((*itcluster).second).end(); ++itnode)
      {
	ini_file<<"**.VIFIBN"<<itnode->id<<".GIPC.difName 		= \"G"<<index<<"DIF\""<<std::endl;
	ini_file<<"**.VIFIBN"<<itnode->id<<".GIPC.ipcAddress 	 	    = \""<<itnode->id<<"\""<<std::endl;
      }
      index++;
      
    }
    ini_file<<std::endl;
    ini_file<<std::endl;
    //IGDIF
    for(std::map<int, int>::iterator it=groupLeaders.begin();it!=groupLeaders.end();it++)
    {
	ini_file<<"**.VIFIBN"<<it->second<<".IGIPC0.difName 		= \"IGDIF1.1\""<<std::endl;
	ini_file<<"**.VIFIBN"<<it->second<<".IGIPC0.ipcAddress  		= \""<<it->second<<"\""<<std::endl;
    }
        
    for(std::map<int, int>::iterator it=candidateLeaders.begin();it!=candidateLeaders.end();it++)
    {
	ini_file<<"**.VIFIBN"<<it->second<<".IGIPC0.difName 		= \"IGDIF1.1\""<<std::endl;
	ini_file<<"**.VIFIBN"<<it->second<<".IGIPC0.ipcAddress  		= \""<<it->second<<"\""<<std::endl;
    }
    
    ini_file<<std::endl;
    ini_file<<std::endl;
    //TenantDIF  
    for (int l =0; l < (graph.getNodes()).size() ; l++)
    {
      ini_file<<"**.VIFIBN"<<graph.getNodes()[l].id<<".TenantIPC.difName = \"TenantDIF\""<<std::endl;
      ini_file<<"**.VIFIBN"<<graph.getNodes()[l].id<<".TenantIPC.ipcAddress = \""<<graph.getNodes()[l].id<<"\""<<std::endl;
    }
    ini_file<<std::endl;
    ini_file<<std::endl;
    ini_file<<"**.ra.qoscubesData = xmldoc(\"config.xml\", \"Configuration/QoSCubesSet2\")"<<std::endl;
    ini_file<<"**.ra.qosReqData = xmldoc(\"QoS.xml\", \"Configuration/QoSReqSet\")"<<std::endl;
    ini_file<<"**.ra.preallocation =  xmldoc(\"config.xml\", \"Configuration/ConnectionSets/ConnectionSet[@id='all']/\")"<<std::endl;
    ini_file<<"**.difAllocator.directory.configData = xmldoc(\"config.xml\", \"Configuration/DA\")"<<std::endl;
    ini_file<<"**.relayAndMux.ForwardingPolicyName  = \"SimpleTable\""<<std::endl;
    ini_file<<"**.resourceAllocator.pdufgPolicyName = \"SimpleGenerator\""<<std::endl;
    ini_file<<"**.routingPolicyName = \"SimpleDV\""<<std::endl;
    ini_file<<std::endl;
    ini_file<<std::endl;
    
    //Enrolment Configuration
    for (int l =0; l < (graph.getNodes()).size() ; l++)
    {
      ini_file<<"**.VIFIBN"<<graph.getNodes()[l].id<<".difAllocator.configData = xmldoc(\"config.xml\", \"Configuration/Host[@id='host"<<graph.getNodes()[l].id<<"']/DA\")"<<std::endl;
    }
    ini_file<<std::endl;
    ini_file<<std::endl;
    for (int l =0; l < (graph.getNodes()).size() ; l++)
    {
      ini_file<<"**.VIFIBN"<<graph.getNodes()[l].id<<".GIPC.enrollment.configData = xmldoc(\"config.xml\", \"Configuration/Host[@id='host"<<graph.getNodes()[l].id<<"']/Enrollment[@id='GIPC']\")"<<std::endl;
      ini_file<<"**.VIFIBN"<<graph.getNodes()[l].id<<".TenantIPC.enrollment.configData = xmldoc(\"config.xml\", \"Configuration/Host[@id='host"<<graph.getNodes()[l].id<<"']/Enrollment[@id='tenant']\")"<<std::endl;
       
      //GroulLeaders enrolment config Self enrolment is to set hard coded
       for(std::map<int, int>::iterator it=groupLeaders.begin();it!=groupLeaders.end();it++)
	{
	  if (graph.getNodes()[l].id == it->second)
	  {
	    ini_file<<"**.VIFIBN"<<it->second<<".IGIPC0.enrollment.configData = xmldoc(\"config.xml\", \"Configuration/Host[@id='host"<<it->second<<"']/Enrollment[@id='IGIPC']\")"<<std::endl;
	  }
	}
	for(std::map<int, int>::iterator it=candidateLeaders.begin();it!=candidateLeaders.end();it++)
	{
	  if (graph.getNodes()[l].id == it->second)
	  {
	    ini_file<<"**.VIFIBN"<<it->second<<".IGIPC0.enrollment.configData = xmldoc(\"config.xml\", \"Configuration/Host[@id='host"<<it->second<<"']/Enrollment[@id='IGIPC']\")"<<std::endl;
	  }
	}
      
    }
    
    
    ini_file<<std::endl;
    ini_file<<std::endl;
    ini_file<<"**.printAtEnd = true"<<std::endl;
    ini_file<<std::endl;
    ini_file<<std::endl;
    int randdest;
    std::map <int,int> Destination;
    for (int i =1; i <= (graph.getNodes()).size() ; i++)
    {
      randdest = rand() % (graph.getNodes()).size() +1; 
      while (randdest ==i)
      {
	randdest = rand() % (graph.getNodes()).size() +1; 
      }
      Destination[i] = randdest;
      ini_file<<"[Config Flow"<<i<<"]"<<std::endl;
      ini_file<<"**.VIFIBN"<<i<<".AP.applicationEntity.iae.dstApName	= \"App"<<randdest<<"\""<<std::endl;
      ini_file<<"**.VIFIBN"<<i<<".AP.applicationEntity.iae.dstAeName 	= \"Ping\""<<std::endl;
      ini_file<<"**.VIFIBN"<<i<<".AP.applicationEntity.iae.startAt 	= 10s"<<std::endl;     
      ini_file<<"**.VIFIBN"<<i<<".AP.applicationEntity.iae.pingAt 	= 15s"<<std::endl;  
      ini_file<<"**.VIFIBN"<<i<<".AP.applicationEntity.iae.rate 	= 15"<<std::endl;  
      ini_file<<"**.VIFIBN"<<i<<".AP.applicationEntity.iae.stopAt 	= 1000s"<<std::endl;
      ini_file<<std::endl;
      
    }  
    
    ini_file.close();
    
    
    //Generate config.xml file for RINASim
    ofstream config_file ("sw150test.xml.txt");
    




    
    config_file<<"    <?xml version=\"1.0\"?>"<<std::endl;
    config_file<<"<Configuration>"<<std::endl;
    config_file<<std::endl;  
    config_file<<std::endl;     
    
    config_file<<"       <ConnectionSets>"<<std::endl;
    config_file<<"        <ConnectionSet id=\"all\">"<<std::endl;
    config_file<<std::endl;  
    
    config_file<<"            <SimTime t=\"1\">"<<std::endl;
    config_file<<"            </SimTime>"<<std::endl;
    config_file<<std::endl;  
    
    config_file<<"            <SimTime t=\"2\">"<<std::endl;
    config_file<<"            </SimTime>"<<std::endl;
    config_file<<std::endl;  
    
    config_file<<"        </ConnectionSet>"<<std::endl;
    config_file<<"    </ConnectionSets>"<<std::endl;
    config_file<<std::endl;      
    
    config_file<<"        <DA>"<<std::endl;
    config_file<<"        <Directory>"<<std::endl;
    config_file<<std::endl;      
    //APP
    for (int l =0; l < (graph.getNodes()).size() ; l++)
    {          
      config_file<<"               <APN apn=\"App"<<graph.getNodes()[l].id<<"\">"<<std::endl;
      config_file<<"                    <DIF difName=\"TenantDIF\"  ipcAddress=\""<<graph.getNodes()[l].id<<"\"/>"<<std::endl;
      config_file<<"                </APN>"<<std::endl;
    }
    config_file<<std::endl;      
    config_file<<std::endl;      
    //TENANT
    index=1;
    for (std::map<int, vector<struct node > >::iterator itcluster=clusters.begin(); itcluster!=clusters.end(); ++itcluster) 
    {
      config_file<<"//G"<<index<<"DIF"<<std::endl;
      for (std::vector<struct node >::iterator itnode = ((*itcluster).second).begin() ; itnode != ((*itcluster).second).end(); ++itnode)
      {
	config_file<<"                <APN apn=\""<<itnode->id<<"_TenantDIF\">"<<std::endl;
	config_file<<"                    <DIF difName=\"G"<<index<<"DIF\" ipcAddress=\""<<itnode->id<<"\"/>"<<std::endl;
	config_file<<"                </APN>"<<std::endl;
      }
      index++;      
    }

    config_file<<std::endl;  
    
    config_file<<std::endl;      
    config_file<<std::endl;  
    //GROUP  
    index=1;
    for (std::map<int, vector<struct node > >::iterator itcluster=clusters.begin(); itcluster!=clusters.end(); ++itcluster) 
    {
      for (std::vector<struct node >::iterator itnode = ((*itcluster).second).begin() ; itnode != ((*itcluster).second).end(); ++itnode)
      {
	config_file<<"                <APN apn=\""<<itnode->id<<"_G"<<index<<"DIF\">"<<std::endl;
	std::map<int, vector<Edge > >::iterator itmap = conciselist.find(itnode->id);
	  for (std::vector<Edge>::iterator itvect = itmap->second.begin(); itvect != itmap->second.end() ; ++itvect)
	  {
	    config_file<<"                    <DIF difName= \"Shim"<<itmap->first<<"To"<<(itvect->getSource())->id<<"\" ipcAddress= \"1\"/>"<<std::endl;
	  }
	  
	  
	  for (std::map<int, vector<Edge > >::iterator itmap=conciselist.begin(); itmap!=conciselist.end(); ++itmap) 
	  {
	      for (std::vector<Edge>::iterator itvect = itmap->second.begin(); itvect != itmap->second.end() ; ++itvect)
	      {
		if (itnode->id == (itvect->getSource())->id)
		config_file<<"                    <DIF difName= \"Shim"<<itmap->first<<"To"<<(itvect->getSource())->id<<"\" ipcAddress= \"2\"/>"<<std::endl;
	      }	
	  } 
	config_file<<"                </APN>"<<std::endl;   	
      }
      index++; 
    }
    

    
    //InterGroup
    
    for(std::map<int, int>::iterator it=groupLeaders.begin();it!=groupLeaders.end();it++)
    {
	  config_file<<"                <APN apn=\""<<it->second<<"_IGDIF1.1\">"<<std::endl;
	  	  struct node * nn = getNode (it->second, nodesdata);
          if (nn!=NULL)
	  {
	    for (int i =0; i < (graph2.getEdges(nn)).size() ; i++)
	    {
	      config_file<<"                    <DIF difName= \"Shim"<<nn->id<<"To"<<((graph2.getEdges(nn))[i].getSource())->id<<"\" ipcAddress= \"1\"/>"<<std::endl;
	    }
	  }
	  
	  
	  for (int l =0; l < (graph2.getNodes()).size() ; l++)
	  {   
		struct node * nn = getNode ((graph2.getNodes())[l].id, nodesdata);
		if (nn!=NULL)
		{
		  for (int i =0; i < (graph2.getEdges(nn)).size() ; i++)
		  {
		      if (it->second == ((graph2.getEdges(nn))[i].getSource())->id)
		      config_file<<"                    <DIF difName= \"Shim"<<nn->id<<"To"<<((graph2.getEdges(nn))[i].getSource())->id<<"\" ipcAddress= \"2\"/>"<<std::endl;
		  }
		}
	  }
	  
	  std::map<int, vector<Edge > >::iterator itmap = conciselist.find(it->second );
	  for (std::vector<Edge>::iterator itvect = itmap->second.begin(); itvect != itmap->second.end() ; ++itvect)
	  {
	    config_file<<"                    <DIF difName= \"Shim"<<itmap->first<<"To"<<(itvect->getSource())->id<<"\" ipcAddress= \"1\"/>"<<std::endl;
	  }
	  
	  
	  for (std::map<int, vector<Edge > >::iterator itmap=conciselist.begin(); itmap!=conciselist.end(); ++itmap) 
	  {
	      for (std::vector<Edge>::iterator itvect = itmap->second.begin(); itvect != itmap->second.end() ; ++itvect)
	      {
		if (it->second  == (itvect->getSource())->id)
		config_file<<"                    <DIF difName= \"Shim"<<itmap->first<<"To"<<(itvect->getSource())->id<<"\" ipcAddress= \"2\"/>"<<std::endl;
	      }	
	  } 
    
	config_file<<"                </APN>"<<std::endl;
    }
    
    
    
 
    for(std::map<int, int>::iterator it=candidateLeaders.begin();it!=candidateLeaders.end();it++)
    {
	  config_file<<"                <APN apn=\""<<it->second<<"_IGDIF1.1\">"<<std::endl;
	  	  struct node * nn = getNode (it->second, nodesdata);
          if (nn!=NULL)
	  {
	    for (int i =0; i < (graph2.getEdges(nn)).size() ; i++)
	    {
	      config_file<<"                    <DIF difName= \"Shim"<<nn->id<<"To"<<((graph2.getEdges(nn))[i].getSource())->id<<"\" ipcAddress= \"1\"/>"<<std::endl;
	    }
	  }
	  
	  
	  for (int l =0; l < (graph2.getNodes()).size() ; l++)
	  {   
		struct node * nn = getNode ((graph2.getNodes())[l].id, nodesdata);
		if (nn!=NULL)
		{
		  for (int i =0; i < (graph2.getEdges(nn)).size() ; i++)
		  {
		      if (it->second == ((graph2.getEdges(nn))[i].getSource())->id)
		      config_file<<"                    <DIF difName= \"Shim"<<nn->id<<"To"<<((graph2.getEdges(nn))[i].getSource())->id<<"\" ipcAddress= \"2\"/>"<<std::endl;
		  }
		}
	  }
	  	  
	  std::map<int, vector<Edge > >::iterator itmap = conciselist.find(it->second );
	  for (std::vector<Edge>::iterator itvect = itmap->second.begin(); itvect != itmap->second.end() ; ++itvect)
	  {
	    config_file<<"                    <DIF difName= \"Shim"<<itmap->first<<"To"<<(itvect->getSource())->id<<"\" ipcAddress= \"1\"/>"<<std::endl;
	  }
	  
	  
	  for (std::map<int, vector<Edge > >::iterator itmap=conciselist.begin(); itmap!=conciselist.end(); ++itmap) 
	  {
	      for (std::vector<Edge>::iterator itvect = itmap->second.begin(); itvect != itmap->second.end() ; ++itvect)
	      {
		if (it->second  == (itvect->getSource())->id)
		config_file<<"                    <DIF difName= \"Shim"<<itmap->first<<"To"<<(itvect->getSource())->id<<"\" ipcAddress= \"2\"/>"<<std::endl;
	      }	
	  }
    
	config_file<<"                </APN>"<<std::endl;
    }
    config_file<<std::endl;  
    config_file<<std::endl;  
    config_file<<"            </Directory>"<<std::endl;
    config_file<<"        </DA>"<<std::endl;
    

	
    int group1, group2, in;
    map <int,struct shortDist> d;
    int src;
    map<int,std::string> toadd;
    
    for (int i =1; i <= (graph.getNodes()).size() ; i++)
    {
      config_file<<"    	<Host id=\"host"<<i<<"\">"<<std::endl;
      config_file<<"	  <DA>"<<std::endl;  
      config_file<<"	    <NeighborTable>"<<std::endl;  
      std::map<int, int>::iterator it = Destination.find(i);
      if (it != Destination.end())
      {	
	    index=1;
	   for (std::map<int, vector<struct node > >::iterator itcluster=clusters.begin(); itcluster!=clusters.end(); ++itcluster) 
	   {
		for (std::vector<struct node >::iterator itnode = ((*itcluster).second).begin() ; itnode != ((*itcluster).second).end(); ++itnode)
		{
		  if (itnode->id == i)
		  {
		    group1 = index;
		    in = itcluster->first;
		  }
		  if (itnode->id == it->second)
		    group2 = index;
		}
		index++;
	   }
	   if (group1 == group2)
	   {
	     config_file<<"			<APN apn=\""<<it->second<<"_G"<<group1<<"DIF\">"<<std::endl; 
	     d.clear();
	     d = BellmanFord(graph, graph3, it->second, nodesdata); 
	     config_file<<"				<Neighbor apn=\""<<d[i].nh<<"_G"<<group1<<"DIF\"/>"<<std::endl;  
	      
	      if (it->second != d[i].nh)
	      {
		std::ostringstream oss;
		oss<<"			<APN apn=\"" << it->second << "_G" << group1 << "DIF\">"<<endl;
		oss<<"				<Neighbor apn=\"" << d[d[i].nh].nh << "_G"+group1 << "DIF\"/>"<<endl;
		oss<<"			</APN>"<<endl;
		toadd[d[i].nh] += oss.str();
		//TODO il faut stocker et apres fill in the file + do the same for GDIF of tenant!
	      }
	     config_file<<"			</APN>"<<std::endl; 
	   }
	   else
	   {
	     config_file<<"			<APN apn=\""<<it->second<<"_TenantDIF\">"<<std::endl; 
	     config_file<<"				<Neighbor apn=\""<<groupLeaders[in]<<"_TenantDIF\"/>"<<std::endl;  
	     config_file<<"			</APN>"<<std::endl; 
	     
	     config_file<<"			<APN apn=\""<<groupLeaders[in]<<"_G"<<group1<<"DIF\">"<<std::endl;
	     d.clear();
	     int dest = groupLeaders[in];
	     d = BellmanFord(graph, graph3, dest, nodesdata); 
	     config_file<<"				<Neighbor apn=\""<<d[i].nh<<"_G"<<group1<<"DIF\"/>"<<std::endl;  
	     config_file<<"			</APN>"<<std::endl; 
	   }
	 
      }
      
      config_file<<toadd[i]<<std::endl; 
      config_file<<"		</NeighborTable>"<<std::endl;
      
      config_file<<"	  </DA>	"<<std::endl;
      
      config_file<<"	   <Enrollment id=\"GIPC\">"<<std::endl;
      config_file<<"			<Preenrollment>"<<std::endl;
      config_file<<"	            <SimTime t=\"3.5\">"<<std::endl;
      config_file<<"	            </SimTime>"<<std::endl;
      config_file<<"			</Preenrollment>"<<std::endl;
      config_file<<"		</Enrollment> "<<std::endl;
      
      config_file<<"	   <Enrollment id=\"tenant\">"<<std::endl;
      config_file<<"			<Preenrollment>"<<std::endl;
      config_file<<"	            <SimTime t=\"6\">"<<std::endl;
      config_file<<"	            </SimTime>"<<std::endl;
      config_file<<"			</Preenrollment>"<<std::endl;
      config_file<<"		</Enrollment> "<<std::endl;
      
      config_file<<"	   <Enrollment id=\"IGIPC\">"<<std::endl;
      config_file<<"			<Preenrollment>"<<std::endl;
      config_file<<"	            <SimTime t=\"5\">"<<std::endl;
      config_file<<"	            </SimTime>"<<std::endl;
      config_file<<"			</Preenrollment>"<<std::endl;
      config_file<<"		</Enrollment> "<<std::endl;
      
      config_file<<"	</Host>"<<std::endl;
    }
    
    config_file<<"</Configuration>"<<std::endl;  
    config_file.close();
  
}
