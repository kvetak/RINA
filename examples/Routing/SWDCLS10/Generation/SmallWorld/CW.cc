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
#include "CW.h"

  using namespace std;

  
    //Edge Class
    Edge::Edge ()
    {
        struct node* m_source = new node;
	struct weight* m_weight = new weight;
    }
 
    Edge::Edge (struct node* source, struct weight* weight)
    {
        m_source = source;
	m_weight = weight;
    }
 
    struct node * Edge::getSource () const
    {
      if (m_source != NULL)
        return m_source;
      else
	return NULL;
    }
 
    struct weight* Edge::getWeigth  () const
    {
      if (m_weight != NULL)
        return m_weight;
      else
	return NULL;
    }
    
    bool Edge::operator== (const Edge &e2) 
    {
        if((this->getSource()->id == e2.getSource()->id)  && (this->getWeigth()->latency==e2.getWeigth()->latency))
	return true;
	else
	return false;
    }
    
   /* bool Edge::operator== (const Edge & other)
    {
      if ((this->getSource() == other.getSource()) && (this->getWeigth() == other.getWeigth()))
	return true;
      else
	return false;
    } */


    //Graph Class
    Graph::Graph ()
    {
    }
    
    Graph::Graph (int init, int initnb)
    {
       m_size = init;
       m_initialNumEdgesperNode = initnb;
       m_nodes.clear();
    }
 
    int Graph::GetSize ()
    {
        return m_nodes.size();
    }
    
    void Graph::ensureCapacity (int minSize)
    {
      if (minSize > m_size)
      {
	int newSize = max (minSize, m_size*2);
	m_size = newSize;
      }
    }
 
    void Graph::addNode (struct node * node)
    {
      ensureCapacity (m_size + 1);
/*      for (std::vector<struct node >::iterator it = m_nodes.begin() ; it != m_nodes.end(); ++it)
      {
// 	if ((*it).id == node->id)
	{
	  return;
	}
      }*/  
      struct node n;
      n.id = node->id;
      n.nb_links = node->nb_links;
      n.available_resources = node->available_resources;

      m_nodes.push_back (n);
    }
    
 /*   void Graph::addNode (struct node * from, struct node * to, double weight)
    {
      ensureCapacity (m_size + 1);
      for (std::vector<struct node>::iterator it = m_nodes.begin() ; it != m_nodes.end(); ++it)
      {
	if (((*it).id == from->id)  || ((*it).id == to->id))
	{
	  return;
	}
      } 
      m_nodes.push_back (*from);
      m_nodes.push_back (*to);
      m_edges[node->id] = edges;
    }*/
    
    void Graph::addNode (struct node * node, vector<Edge> edges)
    {
      ensureCapacity (m_size + 1);
//       for (std::vector<struct node >::iterator it = m_nodes.begin() ; it != m_nodes.end(); ++it)
//       {
// 	if (((*it).id == node->id))
// 	{
// 	  return;
// 	}
//       } 
//       m_nodes.push_back (*node);
//       for (std::vector<struct Edge >::iterator it1 = edges.begin() ; it1 != edges.end(); ++it1)
//       {	
//         m_nodes.push_back (*((*it1).getSource()));
//       }

      m_edges.insert (pair<int, vector <Edge > > (node->id ,edges));
    }
    
    /*bool Graph::hasNode (struct node * n)
    {
      std::vector<struct node>::iterator it;
      it = std::find (m_nodes.begin(), m_nodes.end(), *n);
      if (it != m_nodes.end())
               return true;
      else
               return false;
    }*/
    
    int Graph::getNodeId (struct node * n)
    {
      return n->id;
    }
    
    void Graph::addEdgeUnDirected (struct node * from, struct node * to, struct weight* weight)
    {
      addNode(from);
      addNode(to);
      Edge edto (to, weight);
      m_edges[from->id].push_back(edto);     
      Edge edfrom (from, weight);
      m_edges[to->id].push_back(edfrom);    
    }
    
    std::vector<int> Graph::getNeighbors (struct node * n)
    {
      std::vector<int> output;
      
	for (std::vector<Edge>::iterator it = m_edges[n->id].begin() ; it != m_edges[n->id].end(); ++it)
	{
	  output.push_back(((*it).getSource())->id);
	}      
    }
    
    std::vector<Edge> Graph::getEdges (struct node * n)
    {
      return m_edges[n->id];
    }
    
    std::vector<struct node> Graph::getNodes ()
    {
      return m_nodes;
    }
    
 /*   Graph * Graph::undirectedSubGraph (std::vector<struct node> subgraphNodes)
    {
      if (subGraph == NULL)
      {
	subGraph = new Graph (m_size, m_initialNumEdgesperNode);
        subGraph.m_nodes = new std::vector<struct node*>();
        subGraph.m_edges = new std::map<int, vector <Edge *> >();
      }
      else
      {
	subGraph.m_nodes.clear();
	subGraph.m_edges.clear();
      }
      
      for (std::vector<struct node *>::iterator it = subgraphNodes.begin() ; it != subgraphNodes.end(); ++it)
      {
	subGraph.addNode(*it);
	int numEdges = m_edges[*it].size();
	for (std::vector<Edge*>::iterator it1 = m_edges[n].begin() ; it1 != m_edges[n].end(); ++it1)
	{
	  subGraph.addEdgeUnDirected((*it).id, (*it1)->getSource(), (*it1)->getWeigth());
	}
      }
      
      return subGraph;      
    }*/



   CW::CW ()
    {
        srand (time(NULL));
        m_rand = rand();
    }
 
    CW::CW (double random)
    {
        m_rand = random;
    }
 
    void CW::initialise (Graph graph)
    {
      m_graph = graph;
      nodes = graph.getNodes();
      for (std::vector<struct node>::iterator it = nodes.begin() ; it != nodes.end(); ++it)
      {
	nodeLabels.insert(pair<int, int> ((*it).id, (*it).id));
      }
    }
    
    void CW::relabelNode (struct node * n)
    {
      labelScores.clear();
      int oldlabel = nodeLabels[n->id];
      std::vector <Edge> edges= m_graph.getEdges(n);
      
      if (edges.size() == 0)
      {
	return;
      }
      
      for (std::vector<struct Edge >::iterator it = edges.begin() ; it != edges.end(); ++it)
      {
	int label = nodeLabels [(*it).getSource()->id];
	
	labelScores[label]=(-((*it).getWeigth()->latency))/* + (0.5*((*it).getWeigth()->bandwidth))*/;
      } 
      
      if (!labelScores.empty())
      {
	int newLabel = getKeywithMaxValue (labelScores);
	if (oldlabel!=newLabel)
	{
	  nodeLabels[n->id]=newLabel;
	  changeInPrevStep = true;
	}
      }      
    }
    
    int CW::getKeywithMaxValue(map<int, float> scores)
    {
      int maxKey = 0;
      float maxValue = -10000;
      for (std::map<int, float>::iterator it=scores.begin(); it!=scores.end(); ++it) 
      {

	if (it->second > maxValue)
	{
	  maxKey = it->first;
	  maxValue = it->second;
	}
      }
      return maxKey;
    }
    
    void CW::step()
    {
      std::random_shuffle(nodes.begin(), nodes.end()) ;
      for (std::vector<struct node>::iterator it = nodes.begin() ; it != nodes.end(); ++it)
      {
	struct node * nodepoint = new node;
	nodepoint->id = (*it).id; //see if this work otherwise assign field by field
	nodepoint->nb_links = (*it).nb_links;
	nodepoint->available_resources = (*it).available_resources;
	relabelNode(nodepoint);
      }
    }
    
    int CW::getNodeLabel (struct node * n)
    {
      return (nodeLabels [n->id]);
    }
    
    map<int, vector<struct node> > CW::getClusters () //nodes with the same nodeLabel
    {
      std::map<int, vector <struct node> > clusters;
      for (std::vector<struct node >::iterator it = nodes.begin() ; it != nodes.end(); ++it)
      {
	struct node * nodepoint = new node;
	*nodepoint = (*it); //see if this work otherwise assign field by field
	int label = getNodeLabel (nodepoint);
	clusters[label].push_back(*it);	
      }
      return clusters;      
    }
    
    map<int, vector<struct node> > CW::findClusters(Graph graph)
    {     
      initialise (graph);
      int numIterations = 0;
      do
      {
	 if (numIterations>100)
	 {
	   std::cout<<"Too many steps"<<std::endl;
	 }
	 changeInPrevStep = false;	 
	 step();
	 numIterations++;
      } while (numIterations<20);
//       while (changeInPrevStep==true);
      
      return getClusters();
    }
 
