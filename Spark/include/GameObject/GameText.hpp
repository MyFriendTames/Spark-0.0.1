#ifndef GAME_TEXT_HPP
#define GAME_TEXT_HPP

#include <SFML/Graphics.hpp>
#include <string>

#include "GameObject/GameObject.hpp"
#include "Color/FullColor.hpp"

class GameText : public GameObject, public FullColor{
    private:
        sf::Text text;
    public:
        GameText( const std::string &text = "", const unsigned int &characterSize = 30 );
        GameText( const sf::Font &font, const std::string &text = "", const unsigned int &characterSize = 30 );
        void setFont( const sf::Font &font );
        const sf::Font *getFont();
        void setText( const std::string &text );
        std::string getText();
        void setCharacterSize( const unsigned int &characterSize );
        unsigned int getCharacterSize();
        void setStyle( const sf::Text::Style &style );
        sf::Text::Style getStyle();

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