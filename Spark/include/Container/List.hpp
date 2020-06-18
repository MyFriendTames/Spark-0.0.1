#ifndef LIST_HPP
#define LIST_HPP

#include <iterator>
#include <functional>

#include "Container/ListNode.hpp"
#include "Container/ListIterator.hpp"

template < typename T > class List{
    private:
        static unsigned long globalIndex;
        unsigned long index;
        unsigned long size;
        bool temporal;
        ListNode< T > *firstNode, *lastNode;
    public:
        enum Position{
            Front = 0,
            Back
        };
        enum Direction{
            Forward = 0,
            Backward
        };
        List( const bool &temporal = false );
        ~List();
        unsigned long getSize();
        void clear( const bool &unlink = false );
        void swap( List< T > &other );
        ListNode< T > *insert( T *element, const bool &temporal, const Position &position = Position::Back );
        ListNode< T > *insert( T *element, const Position &position = Position::Back );
        ListNode< T > *insert( T *element, const std::function< bool ( T&, T& ) > &comparator, const bool &temporal = false, const Direction &direction = Direction::Forward );
        bool remove( ListNode< T > *node, const bool &unlink = false );
        ListNode< T > *getFirstNode();
        ListNode< T > *getLastNode();
        ListNode< T > *find( const std::function< bool ( T& ) > &comparator, const Direction &direction = Direction::Forward );
        ListNode< T > *find( T *element, const Direction &direction = Direction::Forward );
        ListIterator< T > begin();
        ListIterator< T > end();
};

template < typename T > unsigned long List< T >::globalIndex( 1 );

template < typename T > List< T >::List( const bool &temporal ) :
    index( List< T >::globalIndex++ ),
    size( 0 ),
    temporal( temporal ),
    firstNode( 0 ),
    lastNode( 0 ){
}

template < typename T > List< T >::~List(){
    clear();
}

template < typename T > unsigned long List< T >::getSize(){
    return size;
}

template < typename T > void List< T >::clear( const bool &unlink ){
    for ( ListNode< T > *node( firstNode ), *nextNode( 0 ); node != 0; node = nextNode ){
        nextNode = node->nextNode;
        if ( unlink || temporal ){
            node->unlink();
        }
        delete node;
    }
    size = 0;
    firstNode = 0;
    lastNode = 0;
}

template < typename T > void List< T >::swap( List< T > &other ){
    unsigned int index( this->index );
    bool temporal( this->temporal );
    ListNode< T > *firstNode( this->firstNode );
    ListNode< T > *lastNode( this->lastNode );
    this->index = other.index;
    other.index = index;
    this->temporal = other.temporal;
    other.temporal = temporal;
    this->firstNode = other.firstNode;
    other.firstNode = firstNode;
    this->lastNode = other.lastNode;
    other.lastNode = lastNode;
}

template < typename T > ListNode< T > *List< T >::insert( T *element, const bool &temporal, const Position &position ){
    ListNode< T > *node( new ListNode< T >( index, element, temporal ) );
    size++;
    switch ( position ){
        case Position::Front:
            node->nextNode = firstNode;
            firstNode = node;
            if ( lastNode != 0 ){
                node->nextNode->previousNode = node;
            }else{
                lastNode = node;
            }
        break;
        case Position::Back:
            node->previousNode = lastNode;
            lastNode = node;
            if ( firstNode != 0 ){
                node->previousNode->nextNode = node;
            }else{
                firstNode = node;
            }
        break;
    }
    return node;
}

template < typename T > ListNode< T > *List< T >::insert( T *element, const Position &position ){
    return insert( element, false, position );
}

template < typename T > ListNode< T > *List< T >::insert( T *element, const std::function< bool ( T&, T& ) > &comparator, const bool &temporal, const Direction &direction ){
    ListNode< T > *node( new ListNode< T >( index, element, temporal ) ), *aux( direction == Direction::Forward ? firstNode : lastNode );
    size++;
    if ( aux == 0 ){
        firstNode = node;
        lastNode = node;
    }else{
        while ( ( direction == Direction::Forward ? aux->nextNode : aux->previousNode ) != 0 && !comparator( *element, *aux->element ) ){
            aux = ( direction == Direction::Forward ? aux->nextNode : aux->previousNode );
        }
        switch ( direction ){
            case Direction::Forward:
                if ( comparator( *element, *aux->element ) ){
                    if ( aux == firstNode ){
                        firstNode = node;
                    }else{
                        aux->previousNode->nextNode = node;
                        node->previousNode = aux->previousNode;
                    }
                    aux->previousNode = node;
                    node->nextNode = aux;
                }else{
                    aux->nextNode = node;
                    node->previousNode = aux;
                    lastNode = node;
                }
            break;
            case Direction::Backward:
                if ( comparator( *element, *aux->element ) ){
                    if ( aux == lastNode ){
                        lastNode = node;
                    }else{
                        aux->nextNode->previousNode = node;
                        node->nextNode = aux->nextNode;
                    }
                    aux->nextNode = node;
                    node->previousNode = aux;
                }else{
                    aux->previousNode = node;
                    node->nextNode = aux;
                    firstNode = node;
                }
            break;
        }
    }
    return node;
}

template < typename T > bool List< T >::remove( ListNode< T > *node, const bool &unlink ){
    bool state( false );
    if ( node != 0 && node->listIndex == index ){
        if ( node->previousNode != 0 ){
            node->previousNode->nextNode = node->nextNode;
        }else{
            firstNode = node->nextNode;
        }
        if ( node->nextNode != 0 ){
            node->nextNode->previousNode = node->previousNode;
        }else{
            lastNode = node->previousNode;
        }
        if ( unlink || temporal ){
            node->element = 0;
        }
        delete node;
        state = true;
        --size;
    }
    return state;
}

template < typename T > ListNode< T > *List< T >::getFirstNode(){
    return firstNode;
}

template < typename T > ListNode< T > *List< T >::getLastNode(){
    return lastNode;
}

template < typename T > ListNode< T > *List< T >::find( const std::function< bool ( T& ) > &comparator, const Direction &direction ){
    ListNode< T > *node( direction == Direction::Forward ? firstNode : lastNode );
    while ( node != 0 && !comparator( node->element ) ){
        node = ( direction == Direction::Forward ? node->nextNode : node->previousNode );
    }
    return node;
}

template < typename T > ListNode< T > *List< T >::find( T *element, const Direction &direction ){
    return find( [ &element ] ( T *other ) { return element == other; }, direction );
}

template < typename T > ListIterator< T > List< T >::begin(){
    return ListIterator< T >( firstNode );
}

template < typename T > ListIterator< T > List< T >::end(){
    return ++ListIterator< T >( lastNode );
}

#endif