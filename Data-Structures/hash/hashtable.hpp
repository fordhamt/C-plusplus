template <typename T>
cop4530::HashTable< T >::HashTable( size_t size ) {
  theLists.reserve( size );
  clear();
}

template <typename T>
cop4530::HashTable< T >::~HashTable() {
  clear();
}

template <typename T>
bool cop4530::HashTable< T >::contains( const T &x ) {
  const list< T > & subList = theLists[ myhash( x ) ];

  return find( subList.begin(), subList.end(), x ) != subList.end();
}

template <typename T>
bool cop4530::HashTable< T >::insert( const T &x ) {
  list< T > & subList = theLists[ myhash( x ) ];

  if( find( subList.begin(), subList.end(), x ) != subList.end() )
    return false;

  subList.push_back( x );
  
  if( ++currentSize > theLists.size() )
    rehash();

  return true;
}

template <typename T>
bool cop4530::HashTable< T >::insert( T && x ) {
  list< T > & subList = std::move( theLists[ myhash( x ) ] );

  if( find( subList.begin(), subList.end(), x ) != subList.end() )
    return false;

  subList.push_back( std::move( x ) );

  if( ++currentSize > theLists.size() )
    rehash();

  return true;

}

template <typename T>
bool cop4530::HashTable< T >::remove( const T &x ) {
  list< T > & subList = theLists[ myhash( x ) ];
  auto itr = find( subList.begin(), subList.end(), x );
  
  if( itr == subList.end() )
    return false;

  subList.erase( x );
  --currentSize;

  return true;
}

template <typename T>
void cop4530::HashTable< T >::clear() { 
  makeEmpty();
}

template <typename T>
bool cop4530::HashTable< T >::load( const char * filename ) {
  cout << "IN";
  ifstream inFile;
  inFile.open( filename );    
  if( !inFile )
    return false;

  T val;
  while( inFile >> val ) 
    insert( val );

  inFile.close();
  return true;
  cout << "IN";
}

template <typename T>
void cop4530::HashTable< T >::dump() { 
// do stuff
;  
}
 
template <typename T>
bool cop4530::HashTable< T >::write_to_file( const char * filename ) {
  ofstream outFile;
  outFile.open( filename );
  if( !outFile )
    return false;

  for( int i = 0; i < theLists.size(); ++i ){
    auto itr = theLists[ i ].begin();

    while( itr != theLists[ i ].end() )
     outFile << *itr++ << endl; 
  }

  outFile.close();
  return true;

}

template <typename T>
void cop4530::HashTable< T >::makeEmpty() {
  for( int i = 0; i < theLists.size(); ++i ) 
    theLists[ i ].clear();
}

template <typename T>
void cop4530::HashTable< T >::rehash() { 
  vector<list<T> > oldLists = theLists;

  // create next table with dobule the size
  theLists.resize( prime_below( 2 * theLists.size() ) );

  for( int i = 0; i < theLists.size(); ++i )
    theLists[ i ].clear();
   
  currentSize = 0;
  for( int k = 0; k < oldLists.size(); ++k ) {
    auto itr = oldLists[ k ].begin();
    
    while( itr != oldLists[ k ].end() )
      insert( *itr++ );
  }
}

template <typename T>
size_t cop4530::HashTable< T >::myhash( const T &x ) {
  static hash< T > hf;

  return hf( x ) % theLists.size();
}

/**********************************************************************/

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename T>
unsigned long cop4530::HashTable<T>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename T>
void cop4530::HashTable<T>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

