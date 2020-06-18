#ifndef KEY_NODE_HPP
#define KEY_NODE_HPP

template < typename T > class KeyNode{
    private:
        bool temporal;
        std::string key;
        T *element;
    public:
        KeyNode( const std::string &key, T *element, const bool &temporal = false );
        ~KeyNode();
        void setTemporal( const bool &temporal );
        bool isTemporal();
        std::string &getKey();
        T *getElement();
};

template < typename T > KeyNode< T >::KeyNode( const std::string &key, T *element, const bool &temporal ) :
    temporal( temporal ),
    key( key ),
    element( element ){
}

template < typename T > KeyNode< T >::~KeyNode(){
    if ( !temporal ){
        delete element;
    }
    element = 0;
}

template < typename T > void KeyNode< T >::setTemporal( const bool &temporal ){
    this->temporal = temporal;
}

template < typename T > bool KeyNode< T >::isTemporal(){
    return temporal;
}

template < typename T > std::string &KeyNode< T >::getKey(){
    return key;
}

template < typename T > T *KeyNode< T >::getElement(){
    return element;
}

#endif