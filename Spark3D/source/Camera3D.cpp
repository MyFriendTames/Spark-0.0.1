#include "Camera3D.hpp"

Camera3D::Camera3D( const sf::Vector3f &position, const float &eyeDistance ) :
    updated( true ),
    position( position ),
    axes( { sf::Vector3f( 1, 0, 0 ), sf::Vector3f( 0, 1, 0 ), sf::Vector3f( 0, 0, 1 ) } ),
    eyeDistance( eyeDistance ){
}

void Camera3D::setPosition( const sf::Vector3f &position ){
    if ( this->position != position ){
        this->position = position;
        updated = false;
    }
}

sf::Vector3f Camera3D::getPosition(){
    return position;
}

sf::Vector3f Camera3D::getAxis( unsigned int axis ){
    return axes[ std::min( 3u, axis ) ];
}

void Camera3D::rotate( const sf::Vector3f &axis, const double &rotation ){
    if ( rotation != 0 ){
        axes[ 0 ] = ::rotate( axis, sf::Vector3f( 0, 0, 0 ), axes[ 0 ], rotation );
        axes[ 1 ] = ::rotate( axis, sf::Vector3f( 0, 0, 0 ), axes[ 1 ], rotation );
        axes[ 2 ] = ::rotate( axis, sf::Vector3f( 0, 0, 0 ), axes[ 2 ], rotation );
        updated = false;
    }
}

void Camera3D::rotate( const unsigned int &axis, const double &rotation ){
    rotate( axes[ std::min( 3u, axis ) ], rotation );
}

void Camera3D::translate( const sf::Vector3f &translation ){
    position += translation;
    updated = false;
}

void Camera3D::translate( const unsigned int &axis, const float &offset ){
    if ( offset != 0 ){
        translate( axes[ std::min( 3u, axis ) ] * offset );
    }
}

void Camera3D::setEyeDistance( const float &eyeDistance ){
    this->eyeDistance = eyeDistance;
}

float Camera3D::getEyeDistance(){
    return eyeDistance;
}

sf::Vector2f Camera3D::to2D( sf::Vector3f point ){
    point -= position - axes[ 2 ] * eyeDistance;
    sf::Vector3f &&eye( axes[ 2 ] * eyeDistance * 100.0f );
    sf::Vector3f &&v( point * 100.0f - eye );
    sf::Vector3f &&p( eye + v * ( -axes[ 2 ] * eye ) / ( axes[ 2 ] * v ) );
    return sf::Vector2f( ( axes[ 0 ] * p ) / ( axes[ 0 ] * axes[ 0 ] ), -( axes[ 1 ] * p ) / ( axes[ 1 ] * axes[ 1 ] ) );
}