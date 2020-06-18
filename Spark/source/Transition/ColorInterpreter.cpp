#include "Transition/ColorInterpreter.hpp"

ColorInterpreter::ColorInterpreter( const sf::Color &c1, const sf::Color &c2 ) :
    c1( c1.r, c1.g, c1.b ),
    c2( c2.r, c2.g, c2.b ){
}

void ColorInterpreter::setColor1( const sf::Color &c1 ){
    this->c1 = sf::Vector3f( c1.r, c1.g, c1.b );
}

sf::Color ColorInterpreter::getColor1(){
    return sf::Color( c1.x, c1.y, c1.z );
}

void ColorInterpreter::setColor2( const sf::Color &c2 ){
    this->c2 = sf::Vector3f( c2.r, c2.g, c2.b );
}

sf::Color ColorInterpreter::getColor2(){
    return sf::Color( c2.x, c2.y, c2.z );
}

sf::Color ColorInterpreter::operator () ( Transition &transition ){
    sf::Vector3f &&v( c2 - c1 );
    float &&m( getMagnitude( v ) );
    sf::Vector3f &&color( m == 0 ? c1 : c1 + ( v / m ) * transition.getIndex() * ( m / transition.limit ) );
    return sf::Color( abs( color.x ), abs( color.y ), abs( color.z ) );
}