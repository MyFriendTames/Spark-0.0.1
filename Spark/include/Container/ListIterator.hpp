#ifndef LIST_ITERATOR_HPP
#define LIST_ITERATOR_HPP

#include <iterator>

template < typename T > class List;

template < typename T > class ListIterator : public std::iterator< std::bidirectional_iterator_tag, T, ptrdiff_t, ListNode< T >*, ListNode< T >& >{
    friend List< T >;
    private:
        ListNode< T > *node;
        ListNode< T > *previousNode;
        ListNode< T > *nextNode;
    public:
        ListIterator( ListNode< T > *node );
        ListIterator( const ListIterator< T > &other );
        ListIterator< T > &operator ++ ();
        ListIterator< T > operator ++ ( int );
        ListIterator< T > &operator -- ();
        ListIterator< T > operator -- ( int );
        bool operator == ( const ListIterator< T > &other );
        bool operator != ( const ListIterator< T > &other );
        T &operator * ();
};

template < typename T > ListIterator< T >::ListIterator( ListNode< T > *node ) :
    node( node ), previousNode( node != 0 ? node->previousNode : 0 ), nextNode( node != 0 ? node->nextNode : 0 ){
}

template < typename T > ListIterator< T >::ListIterator( const ListIterator< T > &other ) :
    node( other.node ), previousNode( other.previousNode ), nextNode( other.nextNode ){
}

template < typename T > ListIterator< T > &ListIterator< T >::operator ++ (){
    previousNode = node;
    node = nextNode;
    nextNode = node != 0 ? node->nextNode : 0;
    return *this;
}

template < typename T > ListIterator< T > ListIterator< T >::operator ++ ( int ){
    return ListIterator< T >( nextNode );
}

template < typename T > ListIterator< T > &ListIterator< T >::operator -- (){
    nextNode = node;
    node = previousNode;
    previousNode = node != 0 ? node->previousNode : 0;
    return *this;
}

template < typename T > ListIterator< T > ListIterator< T >::operator -- ( int ){
    return ListIterator< T >( previousNode );
}

template < typename T > bool ListIterator< T >::operator == ( const ListIterator< T > &other ){
    return node == other.node;
}

template < typename T > bool ListIterator< T >::operator != ( const ListIterator< T > &other ){
    return node != other.node;
}

template < typename T > T &ListIterator< T >::operator * (){
    return *node->element;
}

#endif