// Queue defintion file

template <typename T, class Container >
cop4530::Queue< T, Container >::Queue()  {}

template <typename T, class Container >
cop4530::Queue< T, Container >::Queue( const Queue &rhs )  { c = rhs.c; }

template <typename T, class Container >
cop4530::Queue< T, Container >::Queue( Queue &&rhs )  { c = std::move( rhs.c ); }

template <typename T, class Container >
cop4530::Queue< T, Container >::~Queue() {  }

template <typename T, class Container >
Queue< T, Container > & cop4530::Queue< T, Container >::operator=( const Queue &rhs ) { 
  c = rhs.c; 
  return *this;
}

template <typename T, class Container >
Queue< T, Container > & cop4530::Queue< T, Container >::operator=( Queue &&rhs ) { 
  c = std::move( rhs.c );
  return *this;
 }

template <typename T, class Container >
T & cop4530::Queue< T, Container >::front() { return c.front(); }

template <typename T, class Container >
const T & cop4530::Queue< T, Container >::front() const { return c.front(); }

template <typename T, class Container >
T & cop4530::Queue< T, Container >::back() { return c.back(); }

template <typename T, class Container >
const T & cop4530::Queue< T, Container >::back() const { return c.back(); }

template <typename T, class Container >
int cop4530::Queue< T, Container >::size() const { return c.size(); }

template <typename T, class Container >
bool cop4530::Queue< T, Container >::empty() const { return c.empty(); }

template <typename T, class Container >
void cop4530::Queue< T, Container >::push( const T &val ) { c.push_back( val ); }

template <typename T, class Container >
void cop4530::Queue< T, Container >::push( T &&val ) { c.push_back( val ); }

template <typename T, class Container >
void cop4530::Queue< T, Container >::pop() { c.pop_front(); }
