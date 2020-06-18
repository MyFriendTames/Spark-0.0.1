#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <functional>

#include "Container/BinaryTreeNode.hpp"

template < typename K, typename T > class BinaryTree{
    private:
        static unsigned long globalIndex;
        unsigned long index;
        bool temporal;
        unsigned long size;
        BinaryTreeNode< K, T > *root;
        std::function< K &( T& ) > formatter;
        std::function< int ( K&, K& ) > comparator;
        void balance( BinaryTreeNode< K, T > *&subtree );
        void clear( BinaryTreeNode< K, T > *&subtree, const bool &unlink );
        void insert( BinaryTreeNode< K, T > *&subtree, BinaryTreeNode< K, T > *parent, BinaryTreeNode< K, T > *&node );
        void leftRotation( BinaryTreeNode< K, T > *&subtree );
        void rightRotation( BinaryTreeNode< K, T > *&subtree );
        BinaryTreeNode< K, T > *find( BinaryTreeNode< K, T > *subtree, const K &key );
    public:
        BinaryTree( const std::function< K &( T& ) > &formatter, const std::function< int ( K&, K& ) > &comparator, const bool &temporal = false );
        ~BinaryTree();
        unsigned int getSize();
        unsigned int getHeight();
        void clear( const bool &unlink = false );
        BinaryTreeNode< K, T > *insert( T *element, const bool &temporal = false );
        bool remove( BinaryTreeNode< K, T > *node, const bool &unlink = false );
        BinaryTreeNode< K, T > *find( const K &key );
};

template < typename K, typename T > unsigned long BinaryTree< K, T >::globalIndex( 1 );

template < typename K, typename T > void BinaryTree< K, T >::balance( BinaryTreeNode< K, T > *&subtree ){
    if ( subtree != 0 ){
        balance( subtree->left );
        balance( subtree->right );
        subtree->recalculate();
        if ( subtree->balanceFactor < -1 ){
            if ( subtree->left->balanceFactor > 0 ){
                rightRotation( subtree->left );
            }
            leftRotation( subtree );
        }else if ( subtree->balanceFactor > 1 ){
            if ( subtree->right->balanceFactor < 0 ){
                leftRotation( subtree->right );
            }
            rightRotation( subtree );
        }
    }
}

template < typename K, typename T > void BinaryTree< K, T >::clear( BinaryTreeNode< K, T > *&subtree, const bool &unlink ){
    if ( subtree != 0 ){
        clear( subtree->left, unlink );
        clear( subtree->right, unlink );
        if ( unlink || temporal ){
            subtree->unlink();
        }
        delete subtree;
        subtree = 0;
    }
}

template < typename K, typename T > void BinaryTree< K, T >::insert( BinaryTreeNode< K, T > *&subtree, BinaryTreeNode< K, T > *parent, BinaryTreeNode< K, T > *&node ){
    if ( subtree == 0 ){
        node->parent = parent;
        subtree = node;
        size++;
    }else{
        insert( comparator( formatter( *node->element ), formatter( *subtree->element ) ) < 0 ? subtree->left : subtree->right, subtree, node );
        subtree->recalculate();
        if ( subtree->balanceFactor < -1 ){
            if ( subtree->left->balanceFactor > 0 ){
                rightRotation( subtree->left );
            }
            leftRotation( subtree );
        }else if ( subtree->balanceFactor > 1 ){
            if ( subtree->right->balanceFactor < 0 ){
                leftRotation( subtree->right );
            }
            rightRotation( subtree );
        }
    }
}

template < typename K, typename T > void BinaryTree< K, T >::leftRotation( BinaryTreeNode< K, T > *&subtree ){
    subtree->left->parent = subtree->parent;
    subtree->parent = subtree->left;
    subtree->left = subtree->left->right;
    subtree->parent->right = subtree;
    subtree = subtree->parent;
    subtree->right->recalculate();
    subtree->recalculate();
}

template < typename K, typename T > void BinaryTree< K, T >::rightRotation( BinaryTreeNode< K, T > *&subtree ){
    subtree->right->parent = subtree->parent;
    subtree->parent = subtree->right;
    subtree->right = subtree->right->left;
    subtree->parent->left = subtree;
    subtree = subtree->parent;
    subtree->left->recalculate();
    subtree->recalculate();
}

template < typename K, typename T > BinaryTreeNode< K, T > *BinaryTree< K, T >::find( BinaryTreeNode< K, T > *subtree, const K &key ){
    BinaryTreeNode< K, T > *node( 0 );
    if ( subtree != 0 ){
        int &&comparation( comparator( const_cast< K& >( key ), formatter( *subtree->element ) ) );
        node = ( comparation == 0 ? subtree : find( comparation < 0 ? subtree->left : subtree->right, key ) );
    }
    return node;
}

template < typename K, typename T > BinaryTree< K, T >::BinaryTree( const std::function< K &( T & ) > &formatter, const std::function< int ( K&, K& ) > &comparator, const bool &temporal ) :
    index( BinaryTree::globalIndex++ ),
    temporal( temporal ),
    size( 0 ),
    root( 0 ),
    formatter( formatter ),
    comparator( comparator ){
}

template < typename K, typename T > BinaryTree< K, T >::~BinaryTree(){
    clear();
}

template < typename K, typename T > unsigned int BinaryTree< K, T >::getSize(){
    return size;
}

template < typename K, typename T > unsigned int BinaryTree< K, T >::getHeight(){
    return ( root != 0 ? root->height : 0 );
}

template < typename K, typename T > void BinaryTree< K, T >::clear( const bool &unlink ){
    clear( root, unlink );
}

template < typename K, typename T > BinaryTreeNode< K, T > *BinaryTree< K, T >::insert( T *element, const bool &temporal ){
    BinaryTreeNode< K, T > *node( new BinaryTreeNode< K, T >( index, element, temporal ) );
    insert( root, 0, node );
    return node;
}

template < typename K, typename T > bool BinaryTree< K, T >::remove( BinaryTreeNode< K, T > *node, const bool &unlink ){
    bool state( false );
    if ( node != 0 && node->treeIndex == index ){
        if ( node->left != 0 && node->right != 0 ){
            insert( node->left, node->left, node->right );
        }
        BinaryTreeNode< K, T > *&joint( node->parent == 0 ? root : ( node->parent->left == node ? node->parent->left : node->parent->right ) );
        joint = ( node->left != 0 ? node->left : node->right );
        if ( joint != 0 ){
            joint->parent = node->parent;
        }
        if ( unlink || temporal ){
            node->unlink();
        }
        delete node;
        balance( root );
        size--;
        state = true;
    }
    return state;
}

template < typename K, typename T > BinaryTreeNode< K, T > *BinaryTree< K, T >::find( const K &key ){
    return find( root, key );
}

#endif