#ifndef LIST_NODE_HPP
#define LIST_NODE_HPP

template < typename T > class List;
template < typename T > class ListIterator;

template < typename T > class ListNode{
    friend List< T >;
    friend ListIterator< T >;
    private:
        unsigned long listIndex;
        const bool temporal;
        T *element;
        ListNode< T > *previousNode, *nextNode;
        ListNode( const unsigned long &listIndex, T *element, const bool &temporal );
    public:
        ~ListNode();
        void setElement( T *element );
        T *getElement();
        void unlink();
        ListNode< T > *getPreviousNode();
        ListNode< T > *getNextNode();
};

template < typename T > ListNode< T >::ListNode( const unsigned long &listIndex, T *element, const bool &temporal ) :
    listIndex( listIndex ),
    temporal( temporal ),
    element( element ),
    previousNode( 0 ),
    nextNode( 0 ){
}

template < typename T > ListNode< T >::~ListNode(){
    listIndex = 0;
    if ( !temporal ){
        delete element;
    }
    element = 0;
    previousNode = 0;
    nextNode = 0;
}

template < typename T > void ListNode< T >::setElement( T *element ){
    this->element = element;
}

template < typename T > T *ListNode< T >::getElement(){
    return element;
}

template < typename T > void ListNode< T >::unlink(){
    element = 0;
    previousNode = 0;
    nextNode = 0;
}

template < typename T > ListNode< T > *ListNode< T >::getPreviousNode(){
    return previousNode;
}

template < typename T > ListNode< T > *ListNode< T >::getNextNode(){
    return nextNode;
}

#endif