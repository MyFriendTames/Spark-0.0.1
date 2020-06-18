#include "LightPoint3D.hpp"

LightPoint3D::LightPoint3D( const sf::Vector3f &position, const float &reach, const float &intensity, const sf::Color &color ) :
    position( position ),
    reach( abs( reach ) ),
    intensity( abs( intensity ) ),
    color( sf::Color( color.r, color.g, color.b ) ){
}

void LightPoint3D::setPosition( const sf::Vector3f &position ){
    this->position = position;
}

sf::Vector3f LightPoint3D::getPosition(){
    return position;
}

void LightPoint3D::setReach( const float &reach ){
    this->reach = abs( reach );
}

float LightPoint3D::getReach(){
    return reach;
}

void LightPoint3D::setIntensity( const float &intensity ){
    this->intensity = abs( intensity );
}

float LightPoint3D::getIntensity(){
    return intensity;
}

void LightPoint3D::setColor( const sf::Color &color ){
    this->color.r = color.r;
    this->color.g = color.g;
    this->color.b = color.b;
}

sf::Color LightPoint3D::getColor(){
    return color;
}

sf::Color LightPoint3D::getColor( sf::Color color, const float &magnitude ){
    color *= this->color;
    sf::Vector3f origin( color.r, color.g, color.b );
    sf::Vector3f &&v( getMagnitude( origin ) == 0 ? sf::Vector3f( 0, 0, 0 ) : -origin / getMagnitude( origin ) );
    sf::Vector3f p( origin + v * ( magnitude * ( getMagnitude( origin ) / reach ) ) );
    return sf::Color( std::max( 0.0f, std::min( 255.0f, p.x * intensity ) ), std::max( 0.0f, std::min( 255.0f, p.y * intensity ) ), std::max( 0.0f, std::min( 255.0f, p.z * intensity ) ), color.a );
}