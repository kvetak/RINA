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

#include <stdio.h>    
#include <stdlib.h>    
#include <time.h> 
#include <algorithm> 
#include <vector>
#include <map>


#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;
struct node
{
  int id; 			//Index of the node
  int nb_links; 		//Number of Links/Edges per node
  double available_resources; 	//Percentage of the capacity of the node
};

struct weight
{
  float latency; 		//Latency of the link
  float bandwidth; 		//Bandwidth of the link
  float ber;			//Ber of the link
};

struct phy
{
  int dst; 		
  float phy; 		
};


class Edge
{
private:
  
    struct node* m_source;
    struct weight* m_weight; //Capacity of the link
    
    
public:
    Edge (); 
    Edge (struct node* source, struct weight* weight); 
    node * getSource () const; 
    struct weight* getWeigth () const;    
//     bool operator== (const Edge & other); 
    bool operator== ( const Edge &e2);
};


class Graph
{
private:
    int m_size;
    std::vector <struct node > m_nodes;
    std::map <int, std::vector <Edge> > m_edges;
    int m_initialNumEdgesperNode;
    Graph * subGraph;
    
    
public:
    Graph (int init, int initnb);
    Graph ();
    int GetSize ();    
    void ensureCapacity (int minSize);
    void addNode (struct node * node);
    void addNode (struct node * from, struct node * to, struct weight* weight);
    void addNode (struct node * node, std::vector<Edge> edges);    
    bool hasNode (struct node * n);    
    void addEdgeUnDirected (struct node * from, struct node * to, struct weight* weight);
    std::vector<int>  getNeighbors (struct node * n);
    
    int getNodeId (struct node * n);
    std::vector<struct node > getNodes ();
    std::vector<Edge> getEdges (struct node * n);
    Graph undirectedSubGraph (std::vector<struct node > subgraphNodes);
 
};


class CW
{
private:
    Graph m_graph;
    double m_rand;
    std::vector <struct node> nodes;
    std::map <int, int> nodeLabels;// map int nodeid to label
    bool changeInPrevStep;
    std::map <int, float> labelScores;
    
    
public:
    CW (); 
    CW (double random); 
    void initialise (Graph graph);
    
    void relabelNode (struct node * n);
    
    int getKeywithMaxValue(std::map<int, float> scores);
    void step ();
    
    int getNodeLabel (struct node * n);
    
    std::map<int, std::vector<struct node> > getClusters (); //nodes with the same nodeLabel
      
    std::map<int, std::vector<struct node> > findClusters(Graph graph);
 
};
