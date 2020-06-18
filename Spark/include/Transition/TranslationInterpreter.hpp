#ifndef TRANSLATION_INTERPRETER_HPP
#define TRANSLATION_INTERPRETER_HPP

#include "Transition/Transition.hpp"

class TranslationInterpreter{
    private:
        sf::Vector2f p1;
        sf::Vector2f p2;
    public:
        TranslationInterpreter( const sf::Vector2f &p1 = sf::Vector2f( 0, 0 ), const sf::Vector2f &p2 = sf::Vector2f( 1, 1 ) );
        void setPoint1( const sf::Vector2f &p1 );
        sf::Vector2f getPoint1();
        void setPoint2( const sf::Vector2f &p2 );
        sf::Vector2f getPoint2();
        sf::Vector2f operator () ( Transition &transition );
};

#endif