#ifndef GAME_RECTANGLE_HPP
#define GAME_RECTANGLE_HPP

#include <SFML/Graphics.hpp>

#include "GameObject/GameObject.hpp"
#include "Color/FullColor.hpp"

class GameRectangle : public GameObject, FullColor{
    private:
        sf::RectangleShape shape;
    public:
        GameRectangle() = default;
        GameRectangle( const sf::Vector2f &size );

        virtual sf::FloatRect getBounds();
        virtual void setPosition( const sf::Vector2f &position );
        virtual sf::Vector2f getPosition();
        virtual void setRotation( const float &rotation );
        virtual float getRotation();
        virtual void setScale( const sf::Vector2f &scale );
        virtual sf::Vector2f getScale();
        virtual void setOrigin( const sf::Vector2f &origin );
        virtual sf::Vector2f getOrigin();
        virtual void process( sf::RenderTarget &target );

        virtual void setFillColor( const sf::Color &color );
        virtual sf::Color getFillColor();
        virtual void setOutlineColor( const sf::Color &color );
        virtual sf::Color getOutlineColor();
        virtual void setOutlineSize( const float &outlineSize );
        virtual float getOutlineSize();
};

#endif