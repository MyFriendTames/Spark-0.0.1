#ifndef FILL_COLOR_HPP
#define FILL_COLOR_HPP

#include <SFML/Graphics.hpp>

class FillColor{
    public:
        virtual ~FillColor();

        virtual void setFillColor( const sf::Color &color ) = 0;
        virtual sf::Color getFillColor() = 0;

        void setFillColor( const unsigned char &red, const unsigned char &green, const unsigned char &blue, const unsigned char &alpha = 255 );
};

#endif