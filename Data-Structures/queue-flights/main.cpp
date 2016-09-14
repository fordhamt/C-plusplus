#include <string>
#include <cstdlib>
#include <fstream>  
#include <string.h>
#include <sstream>
#include <iterator>

#include "Queue.h"

using namespace std;
using namespace cop4530;

// function declarations
void BFS( Queue<int> & prices, Queue<string> & cities );
void Success( Queue<string> & cities, Queue<int> & prices, Queue<string> & path);
void Failure( Queue<string> & f);

// command line input program
// ex. ./prog.x input.txt
int main( int argc, char* argv[] ) {
  
  // exit if no input file
  if ( argc < 2 ) {
    cout << "Example usage: ./proj3.x input.txt" << endl;
    return 1;
  }

  int numCities = 0;
  int price = 0;
  
  char choice = 'n';
 
  bool searchAgain = true;
  bool firstRun = true;

  string line = "Error";
  string city = "Error";

  Queue<string> cities;
  Queue<string> tempCities;
  Queue<string> tempC;
  Queue<int> prices;
  Queue<int> tempPrices;

  // set file to command line input
  string file = argv[ 1 ];
  ifstream inFile;
   
  // open the file or return an error
  inFile.open( file ); 
  if( !inFile )
    return 1;
 
  // first line of file is number of cities
  // grab as a string and convert to integer
  getline( inFile, line );
  numCities = atoi( line.c_str() );
  cout << numCities << " cities:" << endl;

  // store the cities and prices
  while ( inFile ) {

    // grab each city
    if( firstRun ) {
      for( int i = 0; i != numCities; ++i) {
      
        getline( inFile, city );
        cities.push( city );
    
        cout << "    " << city << endl;
        firstRun = false;
      }
    }

    // grab each price
    inFile >> price;
    prices.push( price );
  }

  cout << "\ndirect flights between cities" << endl;
  cout << "-------------------------" << endl;

  tempPrices = prices;
  tempCities = cities;

  // display city and its neighbors  
  for(int g = 0; g != numCities; ++g) {
    
    // reset cities
    tempC = cities;

    // output parent city
    cout << tempCities.front() << ':' << endl;
   
    // check each city if it has direct flight to parent
    for(int j = 0; j != numCities; ++j) {

      if( (tempPrices.front() != 0) && (tempPrices.front() != -1) )
       cout << "    " << tempC.front() << ", $" << tempPrices.front() << endl;

      tempC.pop();
      tempPrices.pop();
    }
    
    // get next parent city
    tempCities.pop();
  }

  cout << "------------------------" << endl << endl;

  // route search loop
  do {
    tempPrices = prices;
    tempCities = cities;

    // Breadth First Search
    BFS( tempPrices, tempCities );
    
    cout << "Search another route? (Y/N) ";
    cin >> choice;

    if( choice == 'Y' || choice == 'y' )
      searchAgain = true;
    else
      searchAgain = false;

  } while( searchAgain );

  // EXIT program
  return ( 0 );
}

void BFS( Queue<int> & prices, Queue<string> & cities ) {

  int pfront = 0;  
  int count = 0;
  int neighborCount = 0;
  int price = 0;
  const int sourcePrice = 0;
 
  bool isDest = false;
  bool isSource = false;

  string front = "Error";
  string city = "Error";
  string destCity = "Error";
  string sourceCity = "Error";

  Queue<string> Q;
  Queue<string> tempCities;
  Queue<string> path;
  Queue<string> frontque;
  Queue<int> tempPrices;
  Queue<int> finalPrice;
  Queue<int> priceque;
  Queue<int> P;
  Queue<int> neighborQue;

  // ask user for input
  cout << "Source city: ";
  ws(cin);
  getline( cin, sourceCity );

  cout << "Destination city: ";
  ws(cin);
  getline( cin, destCity );
	
  cout << "finding min_hop route...." << endl;

  // verify input on source and destination city
  tempCities = cities;
  while( !tempCities.empty() ) {
    if( tempCities.front() == destCity )
      isDest = true;

    if( tempCities.front() == sourceCity )
      isSource = true;

    tempCities.pop();
  }

  // return if city does not exist
  if( !isDest ) {
    cout << "path not found, destination city, " << destCity << " not on the map" << endl;
    return;
  }

  if( !isSource ) {
    cout << "path not found, source city, " << sourceCity << " not on the map" << endl;
    return;
  }

  // make a copy of the city and price ques to work with
  tempPrices = prices;
  tempCities = cities;

  // mark the start location and price as visited
  path.push( sourceCity );
  Q.push( sourceCity );
  P.push( sourcePrice );

  while ( !Q.empty() ) {
    // get the front of price and city que
    front = Q.front();
    pfront = P.front();
  
    cities = tempCities;
    prices = tempPrices;

    // align the price cursor to the current city
    while( cities.front() != front ) {

      for(int k = 0;  k != tempCities.size(); ++k)
        prices.pop();

      cities.pop();
    }
		
    // reset city queue
    cities = tempCities;
  
    neighborCount = 0;

    // visit each city and check the price
    for ( int j = 0; j != tempCities.size(); ++j ) {
    
      // get current city and price
      city = cities.front(); 
      price = prices.front();

      // if price is not 0 or -1 current city is a neighbor
      if( ( prices.front() != 0) && (prices.front() != -1) ) {
	
        // count and push back the neighbor and its price
        neighborCount++;
        P.push( price );
        Q.push( city );
      }

      // if a neighbor is the destination city
      if ( (city == destCity) && ( ( prices.front() != 0) && (prices.front() != -1) ) ) {

	// push back neighbor and its price
        P.push( price );
        Q.push( city );

	// push back the neighbor and its parent
        finalPrice.push( pfront );
        finalPrice.push( price ); 
        path.push( front );
	path.push( city );

	// output the route and price
        Success( Q, finalPrice, path );

        // exit for loop upon success
        break;                          
      }
      else {
	// after each iteration of the for loop
        // if destination is not found get next neighbor and its price 
        prices.pop();
        cities.pop();
      }
    }

    // if not sourceCity
    // count each unsuccesful neighbor
    if( neighborQue.size() != 0 )
      ++count;

    // push back number of neighbors a city has
    neighborQue.push( neighborCount );

    // push back city that is at the front 
    if( !Q.empty() ) {
      frontque.push ( Q.front() );

      // get the next city
      Q.pop();
    }

    // push back corresponding price
    if( !P.empty() ) { 
        priceque.push( P.front() );
        P.pop();
    }

    // all the neighbors have checked their neighbors for the destination
    if( neighborQue.front() == count ) {
      
      // remove source city and its price from the front
      if( frontque.front() == sourceCity ) {
        frontque.pop();
        priceque.pop();
      }
  
      finalPrice.push( priceque.front() );
      path.push( frontque.front() );

      // reset neighbor passthrough count
      count = 0;

      // remove current. get next canidate city
      neighborQue.pop();
      priceque.pop();
      frontque.pop();
    }
  } // END of While loop
	
  // pop Q until empty
  Failure( Q ); 
}

void Success( Queue<string> & cities, Queue<int> & finalPrice, Queue<string> & path ) {
  
  int addPrice = 0;
  string prev = "Error";

  // output indent
  cout << "   ";

  // output path that was built
  while ( !path.empty() ) {
     
    if( path.size() != 1 && path.front() != prev ) 
      cout << path.front() << " -> ";
    else if ( path.front() != prev )
      cout << path.front();
    
    prev = path.front();
    path.pop();
  }

  // add price for each connection
  while( !finalPrice.empty() ){
    addPrice = addPrice + finalPrice.front();
    finalPrice.pop();
  }
   cout << ", $" << addPrice << endl;

  while ( !cities.empty() ) 
    cities.pop();  
}

void Failure( Queue<string> & Q ) {
  while ( !Q.empty() ) 
    Q.pop();
}

