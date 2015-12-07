#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

int main()
{
  int i;

  //Creates an instance of ofstream, and opens example.txt
  ofstream a_file ( "example.txt" );

for (i =0; i<123; i++)
{
      a_file<<" **.VIFIBN"<<i<<".TenantIPC.difName = \"TenantDIF\""<<endl;
      a_file<<"**.VIFIBN"<<i<<".TenantIPC.ipcAddress = \""<<i<<"\""<<endl;
 }
  a_file.close();
}
