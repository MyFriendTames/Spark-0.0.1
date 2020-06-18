#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Util.hpp"

class Game;
class DropFilesCallback;

class Screen{
    friend Game;
    friend DropFilesCallback;
    private:
        bool cacheable;
    protected:
        Screen();
        virtual void fileDroped( const std::string &path, const sf::Vector2f &position );
        virtual void resized( const unsigned int &width, const unsigned int &height );
        virtual void keyTyped( const char &key );
        virtual void keyPressed( const sf::Keyboard::Key &key );
        virtual void keyReleased( const sf::Keyboard::Key &key );
        virtual void mouseButtonPressed( const sf::Mouse::Button &button );
        virtual void mouseButtonReleased( const sf::Mouse::Button &button );
        virtual void mouseMoved( const sf::Vector2f &mouse );
        virtual void mouseWheelScrolled( const int &delta );
        virtual void load();
        virtual void unload();
        virtual void loop() = 0;
    public:
        virtual ~Screen();
};

#endif