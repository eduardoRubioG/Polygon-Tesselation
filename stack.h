using namespace std;
#include "sexceptions.h"
#include <vector>

// stack class -- array implementation
//
// CONSTRUCTION: with or without a capacity; default is 10
//
// ******************PUBLIC OPERATIONS*********************
// void push( x )         --> Insert x
// void pop( )            --> Remove most recently inserted item
// Object top( )          --> Return most recently inserted item
// Object topAndPop( )    --> Return and remove most recently inserted item
// bool isEmpty( )        --> Return true if empty; else false
// bool isFull( )         --> Return true if full; else false
// void makeEmpty( )      --> Remove all items
// ******************ERRORS********************************
// Overflow and Underflow thrown as needed

template <class Object>
class stack
{
public:
    explicit stack( int capacity = 10 );
    
    bool isEmpty( ) const;
    bool isFull( ) const;
    const Object & top( ) const;
    
    void makeEmpty( );
    void pop( );
    void push( const Object & x );
    Object topAndPop( );
    
private:
    vector<Object> theArray;
    int topOfstack;
};

#include "stack.cpp"

