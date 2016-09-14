#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdexcept>
#include <list>

namespace cop4530 {

  template <typename T, class Container = std::list<T> >
  class Queue {
  
    protected:
      Container c;
 
    public:
      Queue(); // default zero parameter constructor
      Queue( const Queue &rhs ); // copy constructor
      Queue( Queue &&rhs ); // move constructor

      ~Queue(); // destructor

      // operators
      Queue& operator=( const Queue &rhs );
      Queue& operator=( Queue &&rhs );

      // accessor member functions
      int size() const; // number of elements
      bool empty() const; // check if list is empty

      T& back();
      const T& back() const;

      T& front();
      const T& front() const;

      // mutator member functions 
      void push( const T & val ); // insert to the end
      void push( T&& val );
      void pop(); // delete first element

  }; // end of class Queue

// include the implementation file here
#include "Queue.hpp"

} // end of namespace COP4530
#endif
