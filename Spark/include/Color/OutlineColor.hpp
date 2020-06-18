#ifndef OUTLINE_COLOR_HPP
#define OUTLINE_COLOR_HPP

#include <SFML/Graphics.hpp>

class OutlineColor{
    public:
        virtual ~OutlineColor();

        virtual void setOutlineColor( const sf::Color &color ) = 0;
        virtual sf::Color getOutlineColor() = 0;
        virtual void setOutlineSize( const float &outlineSize ) = 0;
        virtual float getOutlineSize() = 0;

        void setOutlineColor( const unsigned int &red, const unsigned int &green, const unsigned int &blue, const unsigned int &alpha = 255 );
};

#endif