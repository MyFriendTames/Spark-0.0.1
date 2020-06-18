#ifndef BINARY_TREE_NODE_HPP
#define BINARY_TREE_NODE_HPP

#include <iostream>

template < typename K, typename T > class BinaryTree;

template < typename K, typename T > class BinaryTreeNode{
    friend BinaryTree< K, T >;
    private:
        unsigned long treeIndex;
        bool temporal;
        T *element;
        BinaryTreeNode *parent;
        BinaryTreeNode *left;
        BinaryTreeNode *right;
        unsigned int height;
        short balanceFactor;
        void recalculate();
        BinaryTreeNode( const unsigned long &treeIndex, T *element, const bool &temporal );
    public:
        ~BinaryTreeNode();
        void unlink();
        T *getElement();
        BinaryTreeNode< K, T > *getLeftNode();
        BinaryTreeNode< K, T > *getRightNode();
};

template < typename K, typename T > void BinaryTreeNode< K, T >::recalculate(){
    long leftHeight( left != 0 ? left->height : 0 ), rightHeight( right != 0 ? right->height : 0 );
    height = 1 + std::max( leftHeight, rightHeight );
    balanceFactor = rightHeight - leftHeight;
}

template < typename K, typename T > BinaryTreeNode< K, T >::BinaryTreeNode( const unsigned long &treeIndex, T *element, const bool &temporal ) :
    treeIndex( treeIndex ),
    temporal( temporal ),
    element( element ),
    parent( 0 ),
    left( 0 ),
    right( 0 ),
    height( 1 ),
    balanceFactor( 0 ){
}

template < typename K, typename T > BinaryTreeNode< K, T >::~BinaryTreeNode(){
    treeIndex = 0;
    if ( !temporal ){
        delete element;
    }
    element = 0;
    parent = 0;
    left = 0;
    right = 0;
    height = 1;
    balanceFactor = 0;
}

template < typename K, typename T > void BinaryTreeNode< K, T >::unlink(){
    treeIndex = 0;
    element = 0;
    parent = 0;
    left = 0;
    right = 0;
    height = 1;
    balanceFactor = 0;
}

template < typename K, typename T > T *BinaryTreeNode< K, T >::getElement(){
    return element;
}

template < typename K, typename T > BinaryTreeNode< K, T > *BinaryTreeNode< K, T >::getLeftNode(){
    return left;
}

template < typename K, typename T > BinaryTreeNode< K, T > *BinaryTreeNode< K, T >::getRightNode(){
    return right;
}

#endif