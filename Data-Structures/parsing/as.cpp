#include "as.h"
/**
#include<ostream>
#include<algorithm>
#include<cstdlib>
#include<iostream>
#include<vector>
#include<string>

using namespace std;

**/

//#include<algorithm>
//#include<cstdlib>
//using namespace std;

AS::AS( string num ) {
  string ASnum = num;
  int numNeighbors = 0;

  vector<int> neighborList( numNeighbors );
}

string AS::getAS() {
 
    return ASnum;

}

int AS::getNumNeighbors( ) {
  
  numNeighbors = neighborList.size( );

  return numNeighbors;
}

bool AS::isAS(string num) {

	if (num == ASnum)
		return true;

	return false;
}

void AS::writeNeighbor( string num ) {

  int tempInt = atoi(num.c_str());
  neighborList.push_back( tempInt );

}

bool AS::isDuplicate(string num) {

	for (int i = 0; i < neighborList.size(); i++) {
string Result;          
ostringstream convert;   
convert << neighborList[i];   
Result = convert.str();
		if (Result == num)
			return true;
	}

	return false;
}

void AS::writeAS( string num ) {
  
  ASnum = num;
}

int AS::getASint( ) {

	return atoi(ASnum.c_str());
}

bool AS::neighbor2int(string s1, string s2) {

        int i1 = atoi(s1.c_str());
        int i2 = atoi(s2.c_str());
        
 	return i1 < i2;
}

void AS::print( ) {

  numNeighbors = getNumNeighbors( );

  sort(neighborList.begin(), neighborList.end());

  cout << ASnum << ' ' << numNeighbors << ' ';
  for(int i = 0; i < neighborList.size(); i++){
    if(i == neighborList.size() - 1)
      cout << neighborList[i] << endl;
    else
      cout << neighborList[i] << '|';	
  }
  cout << endl;
}
