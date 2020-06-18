#include "Util.hpp"

bool operator < ( const std::string &left, const std::string &right ){
    //return left.length() < right.length();
    return strcmp( left.c_str(), right.c_str() ) < 0;
}

double toDegrees( const double &radians ){
    return radians * 180 / PI;
}

double toRadians( const double &degrees ){
    return degrees * PI / 180;
}

double getAngle( const sf::Vector2f &p1, const sf::Vector2f &p2 ){
    sf::Vector2f &&p( p2 - p1 );
    double d( sqrt( pow( p.x, 2 ) + pow( p.y, 2 ) ) );
    double angle( d == 0 ? 0 : toDegrees( acos( abs( p.x ) / d ) ) );
    angle = ( p.x >= 0 ? angle : 180 - angle );
    angle *= ( p.y < 0 ? -1 : 1 );
    return angle;
}

bool isAtLeft( const sf::Vector2f &point, const sf::Vector2f &p1, const sf::Vector2f &p2 ){
    bool state( false );
    if ( point.y > std::min( p1.y, p2.y ) && point.y <= std::max( p1.y, p2.y ) ){
        double &&angle( toRadians( getAngle( p1, p2 ) ) );
        double &&d( ( point.y - p1.y ) / sin( angle ) );
        state = p1.x + cos( angle ) * d >= point.x;
    }
    return state;
}

bool isInside( const sf::Vector2f &point, const sf::VertexArray &shape ){
    unsigned int count( 0 );
    unsigned int &&n( shape.getVertexCount() );
    for ( unsigned int i( 0 ); i < n && n > 2; ++i ){
        count += isAtLeft( point, shape[ i ].position, shape[ i != n - 1 ? i + 1 : 0 ].position );
    }
    return ( count % 2 != 0 );
}

bool isInside( const sf::Vector2f &point, const sf::Vector2f &p1, const sf::Vector2f &p2, const sf::Vector2f &p3, const sf::Vector2f &p4 ){
    unsigned int count( 0 );
    count += isAtLeft( point, p1, p2 );
    count += isAtLeft( point, p2, p3 );
    count += isAtLeft( point, p3, p4 );
    count += isAtLeft( point, p4, p1 );
    return ( count % 2 != 0 );
}