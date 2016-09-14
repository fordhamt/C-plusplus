#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
#include <queue>
#include <sstream>
using namespace std;

namespace cop4530 {
const int default_threshold_value = 1;

template <typename T>
class BST {
  public:
    BST( int th = default_threshold_value );
    BST( const string input, int th = default_threshold_value );
    BST( const BST & rhs );
    BST( BST && rhs );
    
    ~BST();

    void buildFromInputString( const string input );
    const BST & operator=( const BST & rhs );
    const BST & operator=( BST && rhs );
    bool empty() const;

    // the following call private recursive versions
    void printInOrder( ostream & out = cout ) const;
    void printLevelOrder( ostream & out = cout ) const;
    int numOfNodes() const;
    int height() const;
    void makeEmpty();
    void insert( const T & val );
    void insert( T && val );
    void remove( const T & val );
    bool contains( const T & val );
 
    const T & min() const;
    const T & max() const;
  private:
    // member data
    struct BSTNode {
      T element;

      BSTNode * left;
      BSTNode * right;

      int searchCount;
      int height;

      BSTNode( const T & ele, BSTNode *lt, BSTNode *rt, int count, int h = 0 )
        : element{ ele }, left{ lt }, right{ rt }, searchCount{ count }, height{ h } { }

      BSTNode( const T && ele, BSTNode *lt, BSTNode *rt, int count, int h = 0 )
        : element{ std::move( ele ) }, left{ lt }, right{ rt }, searchCount{ count }, height{ h } { }

    };

    BSTNode * root;

    int threshold;

    // correspond to the public functions
    void printInOrder( BSTNode * subtree, ostream & out ) const;
    void printLevelOrder( BSTNode * subtree, ostream & out ) const;
    void makeEmpty( BSTNode * &subtree );
    void insert( const T & val, BSTNode * &subtree );
    void insert( T && val, BSTNode * &subtree );
    void remove( const T & val, BSTNode * &subtree );
    bool contains( const T & val, BSTNode * &subtree ); // HINT: mabye 3rd para
    int numOfNodes( BSTNode * subtree ) const;
    int height( BSTNode * subtree ) const;
    BSTNode * clone( BSTNode * subtree ) const;

    // extra methods
    BSTNode * min( BSTNode * subtree ) const;
    BSTNode * max( BSTNode * subtree ) const;
   
    void rotateLeft( BSTNode * &subtree );
    void rotateRight( BSTNode * &subtree );    
    int max( int lh, int rh );
};

#include "bst.cpp"
} // end namespace cop4530
#endif
