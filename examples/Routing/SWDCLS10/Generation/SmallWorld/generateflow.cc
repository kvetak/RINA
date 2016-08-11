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


int main(int argc, char *argv[])
{
  int numnodes = atoi (argv [1]);
  int randdest;
  int j = 0;
  map <int, vector<int> > conn;

  ofstream flow_file ("flows.txt");
  
  /* initialize random seed: */  
  srand (time(NULL));
  for (int i =1; i <= numnodes ; i++)
  {
      randdest = rand() % 10 +1; 
      while (randdest ==i)
      {
	randdest = rand() % 10 +1; 
      }
      flow_file<<"[Config Flow"<<i<<"]"<<std::endl;
      flow_file<<"**.VIFIBN"<<i<<".AP.applicationEntity.iae.dstApName	= \"App"<<randdest<<"\""<<std::endl;
      flow_file<<"**.VIFIBN"<<i<<".AP.applicationEntity.iae.dstAeName 	= \"Ping\""<<std::endl;
      flow_file<<"**.VIFIBN"<<i<<".AP.applicationEntity.iae.startAt 	= 10s"<<std::endl;     
      flow_file<<"**.VIFIBN"<<i<<".AP.applicationEntity.iae.pingAt 	= 15s"<<std::endl;  
      flow_file<<"**.VIFIBN"<<i<<".AP.applicationEntity.iae.rate 	= 15"<<std::endl;  
      flow_file<<"**.VIFIBN"<<i<<".AP.applicationEntity.iae.stopAt 	= 1000s"<<std::endl;
      flow_file<<std::endl;
      
  }  
  flow_file.close();
}
