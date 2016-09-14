template<typename T>
cop4530::BST< T >::BST( int th ) {
  threshold = th;
  root = nullptr;
}

template<typename T>
cop4530::BST< T >::BST( const string input, int th ) {
  threshold = th;
  root = nullptr;
  buildFromInputString( input );
}

template<typename T>
cop4530::BST< T >::BST( const BST & rhs ) {
  threshold = rhs.threshold;
  root = clone( rhs.root );
}

template<typename T>    
cop4530::BST< T >::BST( BST && rhs ) {
  threshold = std::move( rhs.threshold );
  root = clone( std::move( rhs.root ) );
  
  rhs.root = nullptr;
}

template<typename T>
cop4530::BST< T >::~BST() {
  makeEmpty();
}

template<typename T>
void cop4530::BST< T >::buildFromInputString( const string input ) {
  makeEmpty();
  istringstream iss( input );
  while( iss ) {
    T val;

    iss >> val;
    insert( val );
  }
}

template<typename T>
const BST< T > & cop4530::BST< T >::operator=( const BST & rhs ) {
  if( this != &rhs ) {
    makeEmpty();
    root = nullptr;
    threshold = rhs.threshold;
    root = clone( rhs.root );
  } 

  return *this; 
}

template<typename T>
const BST< T > & cop4530::BST< T >::operator=( BST && rhs ) {
  if( this != &rhs ) {
    makeEmpty();
    root = nullptr;
    threshold = std::move( rhs.threshold );
    root = clone( std::move( rhs.root ) );
  }

  rhs.root = nullptr;

  return *this;
}

template<typename T>
bool cop4530::BST< T >::empty() const {
  return root == nullptr;
}

/****** 
*** public functions below  call private recursive versions
*/

template<typename T>
void cop4530::BST< T >::printInOrder( ostream & out ) const {
  if( !empty() ) 
     printInOrder( root, out );

  out << endl; 
}

template<typename T>
void cop4530::BST< T >::printLevelOrder( ostream & out ) const { 
  if( !empty() ) 
     printLevelOrder( root, out );
  
  out << endl;
}

template<typename T>
int cop4530::BST< T >::numOfNodes() const { return numOfNodes( root ); }

template<typename T>
int cop4530::BST< T >::height() const { return height( root ); }

template<typename T>
void cop4530::BST< T >::makeEmpty() { makeEmpty( root ); }

template<typename T>
void cop4530::BST< T >::insert( const T & val ) { insert( val, root ); }

template<typename T>   
void cop4530::BST< T >::insert( T && val ) { insert( val, root ); }

template<typename T>
void cop4530::BST< T >::remove( const T & val ) { remove( val, root ); }

template<typename T>
bool cop4530::BST< T >::contains( const T & val ) { return contains( val, root ); }

/** extra functions */

template<typename T>
const T & cop4530::BST< T >::min() const { return min( root ); }

template<typename T>
const T & cop4530::BST< T >::max() const { return max( root ); }

/****** 
*** private recursive functions below
*/

template<typename T>
void cop4530::BST< T >::printInOrder( BSTNode * subtree, ostream & out) const {
  if( subtree != nullptr ) {
    printInOrder( subtree->left, out );
    out << subtree->element << ' ';
    printInOrder( subtree->right, out );
  }
}

/******
** void printLevelOrder( BSTNode * subtree ) const;
	does NOT need to be recursive ****/
template<typename T>
void cop4530::BST< T >::printLevelOrder( BSTNode * subtree, ostream & out ) const {
  if( subtree == nullptr )
    return;

  queue<BSTNode*> nodes;

  nodes.push( subtree );
  while( !nodes.empty() ) {
    BSTNode * currentNode = nodes.front();
    nodes.pop();
    
    out << currentNode->element << ' ';

    if( currentNode->left != nullptr ) 
      nodes.push( currentNode->left );

    if( currentNode->right != nullptr )
      nodes.push( currentNode->right );
  } 
}

template<typename T>
void cop4530::BST< T >::makeEmpty( BSTNode * &subtree ) {
  if( subtree != nullptr ) {
    makeEmpty( subtree->left );
    makeEmpty( subtree->right );
    
    delete subtree;
  }

  subtree = nullptr;
}

template<typename T>
void cop4530::BST< T >::insert( const T & val, BSTNode * &subtree ) {
  if( subtree == nullptr )
    subtree = new BSTNode( val, nullptr, nullptr, 0 );
  else if( val < subtree->element )
    insert( val, subtree->left );
  else if( val > subtree->element )
    insert( val, subtree->right );
  else
    ; // duplicate do nothing

  subtree->height = max( height( subtree->left ), height( subtree->right ) ) + 1;
}

template<typename T>
void cop4530::BST< T >::insert( T && val, BSTNode * &subtree ) {
  if( subtree == nullptr )
    subtree = new BSTNode( std::move( val ), nullptr, nullptr, 0 );
  else if( val < subtree->element )
    insert( val, subtree->left );
  else if( val > subtree->element )
    insert( val, subtree->right );
  else
    ; // duplicate do nothing
  
  subtree->height = max( height( subtree->left ), height( subtree->right ) ) + 1;
}

template<typename T>
void cop4530::BST< T >::remove( const T & val, BSTNode * &subtree ) {
  if( subtree == nullptr )
    return;

  if( val < subtree->element )
    remove( val, subtree->left );
  else if( val > subtree->element )
    remove( val, subtree->right );
  else if( subtree->left != nullptr && subtree->right != nullptr ) {
    subtree->element = min( subtree->right )->element;
    remove( subtree->element, subtree->right );
  } 
  else{ 
    BSTNode * oldNode = subtree;
    subtree = ( subtree->left != nullptr ) ? subtree->left : subtree->right;
    delete oldNode;
  }
}

template<typename T>
bool cop4530::BST< T >::contains( const T & val, BSTNode * &subtree ) {
 // HINT: mabye 3rd para
  if( subtree == nullptr )
    return false;
  else if( val < subtree->element ) {
    if( subtree->left->element == val ) {
      subtree->left->searchCount++;
      if( subtree->left->searchCount >= threshold )
        rotateLeft( subtree );
    
      return true;
    }
    return contains( val, subtree->left );
  }
  else if( val > subtree->element ) {
    if( subtree->right->element == val ) {
      subtree->right->searchCount++;
      if( subtree->right->searchCount >= threshold )
        rotateRight( subtree );

      return true;
    }
    return contains( val, subtree->right );
  }
  else 
    return true;
}

template<typename T>
int cop4530::BST< T >::numOfNodes( BSTNode * subtree ) const {
  if( subtree == nullptr )
    return 0;

  return 1 + numOfNodes( subtree->left) + numOfNodes( subtree->right );
}

template<typename T>
int cop4530::BST< T >::height( BSTNode * subtree ) const {
  if( subtree == nullptr )
    return -1;

  return subtree->height;
}

template<typename T>
typename cop4530::BST< T >::BSTNode * cop4530::BST< T >::clone(BSTNode * subtree ) const {
  if( subtree == nullptr )
    return nullptr;

  return new BSTNode( subtree->element, clone( subtree->left ), 
		clone( subtree->right ), subtree->searchCount, subtree->height );
}

/// extra functions

template<typename T>
int cop4530::BST< T >::max( int leftHeight, int rightHeight ) {
  if( leftHeight > rightHeight )
    return leftHeight;
  else
    return rightHeight;
}

template<typename T>
typename cop4530::BST< T >::BSTNode * cop4530::BST< T >::min(BSTNode * subtree ) const {
  if( subtree == nullptr )
    return nullptr;
  
  if( subtree->left == nullptr )
    return subtree;

  return min( subtree->left );
}

template<typename T>
typename cop4530::BST< T >::BSTNode * cop4530::BST< T >::max( BSTNode * subtree) const { 
  if( subtree == nullptr )
    return nullptr;
  
  if( subtree->right == nullptr )
    return subtree;

  return max( subtree->right );
}

template<typename T>
void cop4530::BST< T >::rotateLeft( BSTNode * &subtree ) {
  BSTNode * parent;
  BSTNode * node;

  parent = subtree;
  if( subtree->left != nullptr ) {
    node = subtree->left;
    subtree = nullptr;

    if( node->right != nullptr )
      parent->left = node->right;
    else
      parent->left = nullptr;
    
    node->right = parent;
    subtree = node;
    subtree->searchCount = 0;
  }		
}

template<typename T>
void BST< T >::rotateRight( BSTNode * &subtree) {
  BSTNode * parent;
  BSTNode * node;

  parent = subtree;
  if( subtree->right != nullptr ) {
    node = subtree->right;
    subtree = nullptr;

    if( node->left != nullptr )
      parent->right = node->left;
    else
      parent->right = nullptr;

    node->left = parent;
    subtree = node;
    subtree->searchCount = 0;
  }

}

/**
template<typename T>
void cop4530::BST< T >::balance( BSTNode * &subtree ) {
  if( subtree == nullptr )
    return;

  if( height( subtree->left ) - height( subtree->right ) > threshold ) {
    if( height( subtree->left->left ) >= height( subtree->left->right ) )
      rotateWithLeftChild( subtree );
    else
      doubleWithLeftChild( subtree );
  }
  else {
    if( height( subtree->right ) - height( subtree->left ) > threshold ) {
      if( height( subtree->right->right ) >= height( subtree->right->left ) )
        rotateWithRightChild( subtree );
      else
        doubleWithRightChild( subtree );
    }
  }

  subtree->height = max( height( subtree->left ), height( subtree->right ) ) + 1;
}


template<typename T>
void cop4530::BST< T >::rotateWithLeftChild( BSTNode * &k2 ) {
  BSTNode * k1 = k2->left;
  k2->left = k1->right;  // set subtree Y to be left child of k2
  k1->right = k2;  // set node k2 to be right child of node k1
  k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
  k1->height = max( height( k1->left ), k2->height ) + 1;
  k2 = k1; // replace node k2 by node k1
}

template<typename T>
void cop4530::BST< T >::doubleWithLeftChild( BSTNode * &k3 ) {
  rotateWithRightChild( k3->left );
  rotateWithLeftChild( k3 );
}

template<typename T>
void cop4530::BST< T >::rotateWithRightChild( BSTNode * &k1 ) {
  BSTNode * k2 = k1->right;
  k1->right = k2->left; // set subtree Y to be right child of node k1
  k2->left = k1;  // set node k1 to be left child of node k2
  k1->height = max( height( k1->right ), height( k1->left ) ) + 1;
  k2->height = max( height( k2->right ), k1->height ) + 1;
  k1 = k2; // replace the node k1 by node k2
}

template<typename T>
void cop4530::BST< T >::doubleWithRightChild( BSTNode * &k1 ) {
  rotateWithLeftChild( k1->right );
  rotateWithRightChild( k1 );
}

template<typename T>
typename cop4530::BST< T >::BSTNode * cop4530::BST< T >::min(BSTNode * subtree ) const {
  if( subtree == nullptr )
    return nullptr;
  
  if( subtree->left == nullptr )
    return subtree;

  return min( subtree->left );
}

template<typename T>
typename cop4530::BST< T >::BSTNode * cop4530::BST< T >::max( BSTNode * subtree) const { 
  if( subtree == nullptr )
    return nullptr;
  
  if( subtree->right == nullptr )
    return subtree;

  return max( subtree->right );
}

**/
