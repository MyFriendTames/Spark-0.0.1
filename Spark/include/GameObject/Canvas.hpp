#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <SFML/Graphics.hpp>

#include "GameObject/GameObject.hpp"
#include "Color/FullColor.hpp"

class Context3D;

class Canvas : public GameObject, public FullColor{
    friend Context3D;
    private:
        sf::RenderTexture canvas;
        sf::RectangleShape shape;
    public:
        Canvas();
        Canvas( const unsigned int &width, const unsigned int &height );
        Canvas( const sf::Vector2u &size );
        Canvas( const sf::Texture &texture );
        void create( const unsigned int &width, const unsigned int &height );
        void create( const sf::Vector2u &size );
        void create( const sf::Texture &texture );
        bool loadFromFile( const std::string &path );
        sf::Vector2u getSize();
        void setView( const sf::View &view );
        sf::View getView();
        void setSmooth( const bool &state );
        bool isSmooth();
        const sf::Texture &getTexture();
        void clear( const sf::Color &color = sf::Color::Transparent );
        void draw( sf::Drawable &object );
        void process( GameObject &object );
        void display();

        void operator *= ( const sf::Texture &texture );
        void operator *= ( const sf::RenderTexture &texture );
        void operator *= ( const Canvas &canvas );

        sf::FloatRect getBounds();
        void setPosition( const sf::Vector2f &position );
        sf::Vector2f getPosition();
        void setRotation( const double &rotation );
        double getRotation();
        void setScale( const sf::Vector2f &scale );
        sf::Vector2f getScale();
        void setOrigin( const sf::Vector2f &origin );
        sf::Vector2f getOrigin();

        void process( sf::RenderTarget &target );

        void setFillColor( const sf::Color &color );
        sf::Color getFillColor();
        void setOutlineColor( const sf::Color &color );
        sf::Color getOutlineColor();
        void setOutlineSize( const float &outlineSize );
        float getOutlineSize();
};

#endif