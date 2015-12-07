#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

int main()
{
  char str[10];
  int i;
//  struct {
//  //int nodeid;
//  string content;
//  }sdif;
  vector <string> vect;

  //Creates an instance of ofstream, and opens example.txt
  ofstream a_file ( "example.txt" );
  // Outputs to example.txt through a_file

  std::string line, bla1, bla2, node, dif,address, tovect;
  std::ifstream infile("config.txt");
  int last_index;
  std::string result;
  while (!infile.eof())
  {
    std::getline(infile, line);
    std::istringstream iss(line);
    getline(iss, bla1, '.');
    getline(iss, node, '.');
    getline(iss, bla2, '=');
    getline(iss, dif, '\n');
    last_index = node.find_first_of(".0123456789");
    result = node.substr(last_index);
    int nodeid =atoi( result.c_str());

    std::getline(infile, line);
    std::istringstream iss1(line);
    getline(iss1, bla1, '.');
    getline(iss1, node, '.');
    getline(iss1, bla2, '=');
    getline(iss1, address, '\n');

      tovect="                <APN apn=\""+result+"_G4DIF\">"+"\n";
      tovect+="                    <DIF difName="+dif+" ipcAddress=\""+address+"\"/>"+"\n";
      tovect+="                </APN>\n";
      a_file<<"                <APN apn=\""<<result<<"_G1DIF\">"<<endl;
      a_file<<"                    <DIF difName="<<dif<<" ipcAddress="<<address<<"/>"<<endl;
      a_file<<"                </APN>"<<endl;
    vect.push_back(tovect);
  }

  for (int i =0 ; i< vect.size(); i++)
  {
    std::cout<<vect[i]<<endl;
//       std::istringstream iss(vect[i]);
//       getline(iss, bla1, '.');
//       getline(iss, node, '.');
//       getline(iss, bla2, '=');
//       getline(iss, dif, '\n');
//       last_index = node.find_first_of(".0123456789");
//       result = node.substr(last_index);
// 
//       a_file<<"                <APN apn=\""<<result<<"_G1DIF\">"<<endl;
//       a_file<<"                    <DIF difName="<<dif<<" ipcAddress=\""<<address<<"\"/>"<<endl;
//       a_file<<"                </APN>"<<endl;
// 
//       std::istringstream iss1(vect[i+1]);
//       getline(iss1, bla1, '.');
//       getline(iss1, node, '.');
//       getline(iss1, bla2, '=');
//       getline(iss1, dif, '\n');
//       last_index = node.find_first_of(".0123456789");
//       result = node.substr(last_index);
// 
//       a_file<<"                <APN apn=\""<<result<<"_G1DIF\">"<<endl;
//       a_file<<"                    <DIF difName="<<dif<<" ipcAddress=\""<<address<<"\"/>"<<endl;
//       a_file<<"                </APN>"<<endl;
  }
//  //fichier config tenant dif
//  for (i =1; i<=29; i++)
//  {
//     a_file<<"                <APN apn=\""<<i<<"_TenantDIF\">"<<endl;
//     a_file<<"                    <DIF difName=\"G1DIF\" ipcAddress=\""<<i<<"\"/>"<<endl;
//     a_file<<"                </APN>"<<endl;
//  }
//
//  for (i =30; i<=58; i++)
//  {
//     a_file<<"                <APN apn=\""<<i<<"_TenantDIF\">"<<endl;
//     a_file<<"                    <DIF difName=\"G2DIF\" ipcAddress=\""<<i<<"\"/>"<<endl;
//     a_file<<"                </APN>"<<endl;
//  }
//
//  for (i =59; i<=87; i++)
//  {
//     a_file<<"                <APN apn=\""<<i<<"_TenantDIF\">"<<endl;
//     a_file<<"                    <DIF difName=\"G3DIF\" ipcAddress=\""<<i<<"\"/>"<<endl;
//     a_file<<"                </APN>"<<endl;
//  }
//
//  for (i =88; i<=116; i++)
//  {
//     a_file<<"                <APN apn=\""<<i<<"_TenantDIF\">"<<endl;
//     a_file<<"                    <DIF difName=\"G4DIF\" ipcAddress=\""<<i<<"\"/>"<<endl;
//     a_file<<"                </APN>"<<endl;
//  }
//for (i =1; i<=29; i++)
//{
//   a_file<<"**.VIFIBN"<<i<<".GIPC.difName 			= \"G1DIF\""<<endl;
//   a_file<<"**.VIFIBN"<<i<<".GIPC.ipcAddress 	 	    = \""<<i<<"\""<<endl;
//}
//for (i =30; i<=58; i++)
//{
//   a_file<<"**.VIFIBN"<<i<<".GIPC.difName 			= \"G2DIF\""<<endl;
//   a_file<<"**.VIFIBN"<<i<<".GIPC.ipcAddress 	 	    = \""<<i<<"\""<<endl;
//}
//for ( i = 59; i<=87; i++)
//{
//   a_file<<"**.VIFIBN"<<i<<".GIPC.difName 			= \"G3DIF\""<<endl;
//   a_file<<"**.VIFIBN"<<i<<".GIPC.ipcAddress 	 	    = \""<<i<<"\""<<endl;
//}
//for ( i = 88; i<=116; i++)
//{
//   a_file<<"**.VIFIBN"<<i<<".GIPC.difName 			= \"G4DIF\""<<endl;
//   a_file<<"**.VIFIBN"<<i<<".GIPC.ipcAddress 	 	    = \""<<i<<"\""<<endl;
//}
  // Close the file stream explicitly
  a_file.close();
}
