#ifndef DATA_VALUE_HPP
#define DATA_VALUE_HPP

#include "DataSource.hpp"

template < typename T > class DataValue : public DataSource{
    public:
        T value;
        DataValue( const T &value );
};

template < typename T > DataValue< T >::DataValue( const T &value ) :
    value( value ){
}

#endif