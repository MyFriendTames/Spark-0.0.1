#ifndef UTIL_HPP
#define UTIL_HPP

#define PI 3.141592653589793

#include <SFML/Graphics.hpp>
#include <sstream>
#include <cstring>
#include <cmath>

template < typename T > T abs( const T &value ){
    return ( value * ( value < 0 ? -1 : 1 ) );
}

template < typename T, typename F, typename ... Types > T format( const F &value, Types ... args ){
    std::stringstream buffer;
    T result( args ... );
    buffer << value;
    buffer >> result;
    return result;
}

bool operator < ( const std::string &left, const std::string &right );

double toDegrees( const double &radians );

double toRadians( const double &degrees );

double getAngle( const sf::Vector2f &p1, const sf::Vector2f &p2 );

bool isAtLeft( const sf::Vector2f &point, const sf::Vector2f &p1, const sf::Vector2f &p2 );

bool isInside( const sf::Vector2f &point, const sf::VertexArray &shape );

bool isInside( const sf::Vector2f &point, const sf::Vector2f &p1, const sf::Vector2f &p2, const sf::Vector2f &p3, const sf::Vector2f &p4 );

template < typename T > T operator * ( const sf::Vector2< T > &left, const sf::Vector2< T > &right ){
    return left.x * right.x + left.y * right.y;
}

template < typename T > T getMagnitude( const sf::Vector2< T > &v ){
    return sqrt( pow( v.x, 2 ) + pow( v.y, 2 ) );
}

template < typename T > sf::Vector2< T > toUnitary( const sf::Vector2< T > &v ){
    return v / getMagnitude( v );
}

template < typename T > double getInnerAngle( const sf::Vector2< T > &v1, const sf::Vector2< T > &v2 ){
    return toDegrees( acos( ( v1 * v2 ) / ( getMagnitude( v1 ) * getMagnitude( v2 ) ) ) );
}

template < typename T > sf::Vector2< T > rotate( const sf::Vector2< T > &origin, sf::Vector2< T > v, double rotation ){
    rotation = toRadians( getAngle( origin, v ) + rotation );
    v -= origin;
    float h( getMagnitude( v ) );
    return sf::Vector2< T >( origin.x + cos( rotation ) * h, origin.y + sin( rotation ) * h );
}

template < typename T > T operator * ( const sf::Vector3< T > &left, const sf::Vector3< T > &right ){
    return left.x * right.x + left.y * right.y + left.z * right.z;
}

template < typename T > sf::Vector3< T > operator % ( const sf::Vector3< T > &left, const sf::Vector3< T > &right ){
    return sf::Vector3< T >(
        left.y * right.z - left.z * right.y,
        left.z * right.x - left.x * right.z,
        left.x * right.y - left.y * right.x
    );
}

template < typename T > T getMagnitude( const sf::Vector3< T > &v ){
    return sqrt( pow( v.x, 2 ) + pow( v.y, 2 ) + pow( v.z, 2 ) );
}

template < typename T > sf::Vector3< T > toUnitary( const sf::Vector3< T > &v ){
    return v / getMagnitude( v );
}

#endif