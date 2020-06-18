#ifndef UTIL_3D_HPP
#define UTIL_3D_HPP

#include <cmath>

#include <Spark.hpp>

template < typename T > double getInnerAngle( const sf::Vector3< T > &v1, const sf::Vector3< T > &v2 ){
    return toDegrees( acos( ( v1 * v2 ) / ( getMagnitude( v1 ) * getMagnitude( v2 ) ) ) );
}

template < typename T > sf::Vector3< T > rotate( const sf::Vector3< T > &axis, const sf::Vector3< T > &origin, sf::Vector3< T > v, double rotation ){
    v -= origin;
    rotation = toRadians( rotation );
    double COS( cos( rotation ) );
    double SIN( sin( rotation ) );
    double N( v * axis * ( 1 - COS ) );
    return sf::Vector3< T >(
        axis.x * N + SIN * ( -v.y * axis.z + v.z * axis.y ) + v.x * COS,
        axis.y * N + SIN * ( v.x * axis.z - v.z * axis.x ) + v.y * COS,
        axis.z * N + SIN * ( -v.x * axis.y + v.y * axis.x ) + v.z * COS
    ) + origin;
}

#endif