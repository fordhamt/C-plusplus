#include <iostream>
using namespace std;

template<typename T>
cop4530::Vector< T >::Vector() {

	theSize = 0;
	theCapacity = 0; 
	array = nullptr; 
}

template<typename T>
cop4530::Vector< T >::Vector( const Vector &rhs ) {

	theSize = rhs.theSize;
	theCapacity = rhs.theCapacity;
	array = new T[ theCapacity ];
	for( int i = 0; i != size(); ++i )
		array[ i ] = rhs.array[ i ];
}

template<typename T>
cop4530::Vector< T >::Vector( Vector &&rhs ) {
	 
	theSize = rhs.theSize;
	theCapacity = rhs.theCapacity;
	array = rhs.array;

	rhs.array = nullptr;
	rhs.theSize = 0;
	rhs.theCapacity = 0;
}

template<typename T>
cop4530::Vector< T >::Vector( int initSize, const T &val ) {
	
	theSize = initSize;
	theCapacity = theSize * 2 + 1;
	array = new T[ theCapacity ];

	for(int i = 0; i != theSize; i++) 
		array[i] = val;

}

template<typename T>
cop4530::Vector< T >::Vector( const_iterator start, const_iterator end ) {

		
	theSize = end - start;
	theCapacity = theSize * 2 + 1;
	array = new T[ theCapacity ];
	int i = 0;
	for(auto itr = start; itr != end; ++itr)
		array[ i++ ] = *start++;
}

template<typename T>
cop4530::Vector< T >::~Vector() {

	delete [] array;
}

template<typename T>
T & cop4530::Vector< T >::operator[]( int index ) {

	return array[ index ];
}

template<typename T>
const T & cop4530::Vector< T >::operator[]( int index ) const {

	return array[ index ];
}

template<typename T>
const Vector< T > & cop4530::Vector< T >::operator=( const Vector &rhs ) {

	if (this != &rhs) {

		delete [] array;
		theSize = rhs.size();
		theCapacity = rhs.theCapacity;

		array = new T[ capacity() ];
		for ( int i = 0; i != size(); ++i )
			array[ i ] = rhs.array[ i ];
	}

	return *this;
}

template<typename T>
Vector< T > & cop4530::Vector< T >::operator=( Vector &&rhs ) {

	std::swap( theSize, rhs.theSize );
	std::swap( theCapacity, rhs.theCapacity );
	std::swap( array, rhs.array );
}

template<typename T>
T & cop4530::Vector< T >::at( int loc ) {
	try {
		if( loc > size() )
			throw std::out_of_range("Out of range\n");
	
		return array[ loc ];
	} catch( int error_code) {
        	cout << "Error: " << error_code;
    	}
}

template<typename T>
const T & cop4530::Vector< T >::at( int loc ) const {

	try {
                if( loc > size() )
                        throw std::out_of_range("Out of range\n");

                return array[ loc ];
        } catch( int error_code) {
                cout << "Error: " << error_code;
        }
}

template<typename T>
T & cop4530::Vector< T >::front() {

	return array[ 0 ];
}

template<typename T>
const T & cop4530::Vector< T >::front() const {

	return array[ 0 ];
}

template<typename T>
T & cop4530::Vector< T >::back() {

	return array[ size() - 1 ];
}

template<typename T>
const T & cop4530::Vector< T >::back() const {

	return array[ size() - 1 ];
}

template<typename T>
int cop4530::Vector< T >::size() const {
	
	return theSize;
}

template<typename T>
int cop4530::Vector< T >::capacity() const {

	return theCapacity;
}

template<typename T>
bool cop4530::Vector< T >::empty() const {

	return size() == 0;
}

template<typename T>
void cop4530::Vector< T >::clear() {

	theSize = 0;
}

template<typename T>
void cop4530::Vector< T >::push_back( const T &val ) {

	if( theSize == theCapacity )
		reserve( 2 * theCapacity + 1 );

	array[ theSize++ ] = val;
}

template<typename T>
void cop4530::Vector< T >::pop_back() {

	theSize--;
}

template<typename T>
void cop4530::Vector< T >::resize( int newSize, T val) {

	if ( newSize > theCapacity )
		reserve( 2 * theCapacity + 1 );

	if ( newSize > theSize) {
		for(int i = theSize; i != newSize; i++)
			array[ i ] = val;
	}

	theSize = newSize;
}

template<typename T>
void cop4530::Vector< T >::reserve( int newCapacity ) {

	if ( newCapacity < theCapacity )
		return;

	T *oldArray = array;

	theCapacity = newCapacity;
	array = new T[ theCapacity ];

	for(int i = 0; i < size(); i++) 
		array[ i ] = oldArray[ i ];

	delete [] oldArray;
}

template<typename T>
void cop4530::Vector< T >::print(std::ostream& os, char ofc) const {

	typename cop4530::Vector< T >::const_iterator start = begin();
	while( start != end() )
		os << *start++ << ' ';

}

template<typename T>
T * cop4530::Vector< T >::begin() {

	return &array[ 0 ];
}

template<typename T>
const T * cop4530::Vector< T >::begin() const {

	return &array[ 0 ];
}

template<typename T>
T * cop4530::Vector< T >::end() {

	return &array[ size() ];
}

template<typename T>
const T * cop4530::Vector< T >::end() const {

	return &array[ size() ];
}

template<typename T>
typename cop4530::Vector< T >::iterator Vector< T >::insert( iterator itr, const T& val ) {


	if( itr == end() ) {
		if( size() == theCapacity )
                reserve( 2 * theCapacity + 1 );
		cout << "IF size: " << theSize << endl;
		array[ theSize++ ] = val;
		return itr;
	}
	
	if( size() == theCapacity )
                reserve( 2 * theCapacity + 1 );
	int k = 0;
	
	T * oldArray = array;
	array = new T[ theCapacity ];

	theSize++;
	cout << "size: " << theSize << endl;
	for(int i = 0; i != size() ; ++i) {

		if( itr == &oldArray[ i ] ) 
			array[ i ] = val;
		else
			array[ i ] = oldArray[ k++ ];	
	}

	delete [] oldArray;

	return itr;
}

template<typename T>
typename cop4530::Vector< T >::iterator Vector< T >::erase(iterator itr) {
	
	auto firstAdr = itr;
	auto next = ++itr;

	auto index = firstAdr - begin();

	if( firstAdr == end() ) {
		--theSize;
		return iterator( firstAdr );
	}

        std::copy(array + index, array + (theSize + 2), array); 

	--theSize;

	return next;
}

template<typename T>
typename cop4530::Vector< T >::iterator Vector< T >::erase( iterator start, iterator end ) {
	
	while( start != end ) 
		start = erase( start );

	return start;
}

template<typename T>
void cop4530::Vector< T >::doubleCapacity() {

	theCapacity = 2 * theCapacity + 1;
}

template<typename T>
bool operator==(const Vector< T > & lhs, const Vector< T > & rhs) {
	
	if(lhs.size() != rhs.size())
		return false;

	auto itr = lhs.begin();
	auto ritr = rhs.begin();

	while( itr != lhs.end() ) {
		if( *itr++ != *ritr++)
			return false;
	}

	return true;
}

template<typename T>
bool operator!=(const Vector< T > & lhs, const Vector< T > & rhs) {

	return !( lhs == rhs );
}

template<typename T>
std::ostream & operator<<(std::ostream & os, const Vector< T > & v) {

	v.print( os );

	return os;
}
