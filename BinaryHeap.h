#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include "QuadraticProbing.h"

#include <vector>
#include <exception>
#include <limits>
#include <string>

// BinaryHeap class
//
// CONSTRUCTION: with an optional capacity (that defaults to 100)
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// deleteMin( minItem )   --> Remove (and optionally return) smallest item
// Comparable findMin( )  --> Return smallest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// ******************ERRORS********************************
// Throws std::exception() for  UnderflowException as warranted

 template <typename Comparable>
class BinaryHeap
{
  public:
    explicit BinaryHeap( int capacity = 100 )
      : array_( capacity + 1 ), currentSize_( 0 )
    {
    }

//     explicit BinaryHeap( const std::vector<Comparable> & items )
//       : array_( items.size( ) + 10 ), currentSize_( items.size( ) )
//     {
//         for( int i = 0; i < items.size( ); i++ )
//             array_[ i + 1 ] = items[ i ];
//         buildHeap( );
//     }

    bool isEmpty( ) const
      { return currentSize_ == 0; }

    /**
     * Find the smallest item in the priority queue.
     * Return the smallest item, or throw Underflow if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw std::exception();// UnderflowException( );
        return array_[ 1 ].key;
    }
    /**
     * Insert item x, allowing duplicates.
     */
    void insert( const Comparable & x, double y )
    {
	Node newNode(x,y,0);
        if( currentSize_ == array_.size( ) - 1 )
            array_.resize( array_.size( ) * 2 );

            // Percolate up
        int hole = ++currentSize_;
        for( ; hole > 1 && newNode.delta < array_[ hole / 2 ].delta; hole /= 2 )
	{
            array_[ hole ] = array_[ hole / 2 ];
	    
	}
	newNode.location = hole;
        array_[ hole ] = newNode;
	hashTable_.insert(newNode);

    }

    /**
     * Remove the minimum item.
     * Throws UnderflowException if empty.
     */
    void deleteMin( )
    {
        if( isEmpty( ) )
            throw std::exception();// UnderflowException( );

        array_[ 1 ] = array_[ currentSize_-- ];
        percolateDown( 1 );
    }

    /**
     * Remove the minimum item and place it in minItem.
     * Throws Underflow if empty.
     */
    void deleteMin( Comparable & minItem )
    {
        if( isEmpty( ) )
            throw std::exception();// UnderflowException( );

        minItem = array_[ 1 ].key;
        array_[ 1 ] = array_[ currentSize_-- ];
        percolateDown( 1 );
    }

    void makeEmpty( )
      { currentSize_ = 0; }

      
    void increaseKey(double delta, Comparable key)
    {
	Node newNode(key,0,0);
	int loc = hashTable_.findLocation(newNode);
	array_[loc].delta += delta;
	
	            // Percolate down
	newNode = percolateDown(loc);
	hashTable_.update(newNode);

    }
    void decreaseKey(double delta, Comparable key)
    {
	Node newNode(key,0,0);
	int loc = hashTable_.findLocation(newNode);
	array_[loc].delta -= delta;
	newNode = percolateUp(loc);
	
	hashTable_.update(newNode);
	
	
    }
    void removeKey(Comparable key)
    {
	Node newNode(key,0,0);
	if (hashTable_.contains(newNode))
	{
	int loc = hashTable_.findLocation(newNode);
	array_[loc].delta = std::numeric_limits<double>::min(); // minimum value of double
	newNode = percolateUp(loc);
	deleteMin();
	}
	// else do nothing
    }
    
    struct Node
    {
	Node()
	{
	    key = Comparable();
	    delta = double();
	    location = int();
	}
	Comparable key;
	double delta;
	int location;
	Node(Comparable newkey, double newdelta, int newlocation) : key(newkey), delta(newdelta), location(newlocation) {}
    };
   private:
  
      
      
    std::vector<Node>		array_;        // The heap array_
    int         		currentSize_;  // Number of elements in heap
    HashTable<Node>		hashTable_;
    /**
     * Establish heap order property from an arbitrary
     * arrangement of items. Runs in linear time.
     */
    
   
    
  private:
    
    void buildHeap( )
    {
        for( int i = currentSize_ / 2; i > 0; i-- )
            percolateDown( i );
    }

    /**
     * Internal method to percolate down in the heap.
     * hole is the index at which the percolate begins.
     */
    Node percolateDown( int hole )
    {
        int child;
	Node tmp = array_[ hole ];

        for( ; hole * 2 <= currentSize_; hole = child )
        {
            child = hole * 2;
            if( child != currentSize_ && array_[ child + 1 ].delta < array_[ child ].delta )
                child++;
            if( array_[ child ].delta < tmp.delta )
	    {
                array_[hole] = array_[ child ];
		array_[hole].location = hole;
		hashTable_.update(array_[hole]);
	    }
            else
                break;
        }
        tmp.location = hole;
        array_[ hole ] = tmp;
	hashTable_.update(tmp);
	return tmp;
    }
    
    Node percolateUp(int hole)
    {
	Node tmp = array_[hole];
	
        for( ; hole > 1 && tmp.delta < array_[ hole / 2 ].delta; hole /= 2 )
	{
            array_[ hole ] = array_[ hole / 2 ];
	    array_[hole].location = hole;
	    hashTable_.update(array_[hole]);
	}
	tmp.location = hole;
	array_[hole] = tmp;
	hashTable_.update(tmp);
	return tmp;
	
	
    }
    
};


#endif
