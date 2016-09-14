#ifndef As_H

#define As_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>
#include <string.h>
#include <sstream>
#include <iterator>

using namespace std;

class AS {

  public:


    AS( string = "Error" );

    string getAS( );
    int getASint( );
    void writeAS( string num );

    void writeNeighbor( string num );

    int getNumNeighbors( );

    void print( );
    bool neighbor2int(string s1, string s2);
    bool isDuplicate(string num);
    bool isAS(string num);



  private:


    string ASnum;

    int numNeighbors;

    vector<int> neighborList;
};



#endif
