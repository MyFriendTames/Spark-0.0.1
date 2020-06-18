#ifndef GAME_SPRITE_HPP
#define GAME_SPRITE_HPP

#include <SFML/Graphics.hpp>

#include "GameObject/GameObject.hpp"
#include "Color/FillColor.hpp"

class SpriteAnimation;

class GameSprite : public GameObject, public FillColor{
    friend SpriteAnimation;
    private:
        sf::Sprite sprite;
    public:
        GameSprite() = default;
        GameSprite( const sf::Texture &texture );
        GameSprite( const sf::Texture &texture, const sf::IntRect &rect );
        void setTexture( const sf::Texture &texture, const bool &resetRect = false );
        const sf::Texture *getTexture();
        void setTextureRect( const sf::IntRect &rect );
        sf::IntRect getTextureRect();

        virtual sf::FloatRect getBounds();
        virtual void setPosition( const sf::Vector2f &position );
        virtual sf::Vector2f getPosition();
        virtual void setRotation( const double &rotation );
        virtual double getRotation();
        virtual void setScale( const sf::Vector2f &scale );
        virtual sf::Vector2f getScale();
        virtual void setOrigin( const sf::Vector2f &origin );
        virtual sf::Vector2f getOrigin();
        virtual void process( sf::RenderTarget &target );

        virtual void setFillColor( const sf::Color &color );
        virtual sf::Color getFillColor();
};

#endif