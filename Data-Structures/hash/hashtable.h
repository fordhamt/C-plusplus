#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <cstdlib> 
#include <algorithm> 

using namespace std;

namespace cop4530 {

template <typename T>
class HashTable {
  public:
  
    HashTable( size_t size = 101 );
    ~HashTable();
    
    bool contains( const T &x );
    bool insert( const T &x );
    bool insert( T && x );
    bool remove( const T &x );
    void clear();
    bool load( const char * filename );
    void dump();
    bool write_to_file( const char * filename );

  private:
    vector<list<T> > theLists;
    int currentSize;

    void makeEmpty();
    void rehash();
    size_t myhash( const T &x );
  
    // used when improper size is given (for example
    // size is 0 or negatiave)
    static const unsigned int default_capacity = 11;
    static const unsigned int max_prime = 1301081;

    unsigned long prime_below(unsigned long);
    void setPrimes(std::vector<unsigned long> &);
};

#include "hashtable.hpp"
} // end namespace cop4530
#endif
