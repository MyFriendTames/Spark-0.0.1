#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <SFML/Graphics.hpp>

#include "Util.hpp"

class GameObject{
    public:
        virtual ~GameObject();

        virtual sf::FloatRect getBounds() = 0;
        virtual void setPosition( const sf::Vector2f &position ) = 0;
        virtual sf::Vector2f getPosition() = 0;
        virtual void setRotation( const float &rotation ) = 0;
        virtual float getRotation() = 0;
        virtual void setScale( const sf::Vector2f &scale ) = 0;
        virtual sf::Vector2f getScale() = 0;
        virtual void setOrigin( const sf::Vector2f &origin ) = 0;
        virtual sf::Vector2f getOrigin() = 0;

        virtual void process( sf::RenderTarget &target ) = 0;

        void setPosition( const float &x, const float &y );
        void setScale( const float &x, const float &y );
        void setScale( const float &scale );
        void setOrigin( const float &x, const float &y );

        sf::Vector2f getDimensions( const bool &scaled = true );
        bool isInside( const sf::Vector2f &point );
};

#endif