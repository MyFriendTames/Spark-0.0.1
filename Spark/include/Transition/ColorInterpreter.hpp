#ifndef COLOR_INTERPRETER_HPP
#define COLOR_INTERPRETER_HPP

#include "Transition/Transition.hpp"

class ColorInterpreter{
    private:
        sf::Vector3f c1;
        sf::Vector3f c2;
    public:
        ColorInterpreter( const sf::Color &c1 = sf::Color::Black, const sf::Color &c2 = sf::Color::White );
        void setColor1( const sf::Color &c1 );
        sf::Color getColor1();
        void setColor2( const sf::Color &c2 );
        sf::Color getColor2();
        sf::Color operator () ( Transition &transition );
};

#endif