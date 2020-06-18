#include "Transition/TranslationInterpreter.hpp"

TranslationInterpreter::TranslationInterpreter( const sf::Vector2f &p1, const sf::Vector2f &p2 ) :
    p1( p1 ),
    p2( p2 ){
}

void TranslationInterpreter::setPoint1( const sf::Vector2f &p1 ){
    this->p1 = p1;
}

sf::Vector2f TranslationInterpreter::getPoint1(){
    return p1;
}

void TranslationInterpreter::setPoint2( const sf::Vector2f &p2 ){
    this->p2 = p2;
}

sf::Vector2f TranslationInterpreter::getPoint2(){
    return p2;
}

sf::Vector2f TranslationInterpreter::operator () ( Transition &transition ){
    sf::Vector2f &&v( p2 - p1 );
    float &&m( getMagnitude( v ) );
    return m == 0 ? p1 : p1 + ( v / m ) * transition.getIndex() * ( m / transition.limit );
}