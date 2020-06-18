#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

#include "Container/BinaryTree.hpp"
#include "Container/KeyNode.hpp"
#include "Util.hpp"
#include "InputSource.hpp"
#include "DataSource.hpp"
#include "Screen.hpp"
#include "GameObject/Canvas.hpp"

class Screen;
class DropFilesCallback;

class Game{
    friend DropFilesCallback;
    private:
        static Screen *screen;
        static Screen *previousScreen;
        static InputSource keyboard [];
        static InputSource mouse [];
        static int mouseWheelScroll [];
        static bool focused;
        static bool loading;
        static BinaryTree< std::string, KeyNode< Screen > > screens;
        static BinaryTree< std::string, KeyNode< sf::Font > > fonts;
        static BinaryTree< std::string, KeyNode< sf::Texture > > textures;
        static BinaryTree< std::string, KeyNode< sf::Music > > soundtracks;
        static BinaryTree< std::string, KeyNode< sf::SoundBuffer > > sounds;
        static BinaryTree< std::string, KeyNode< DataSource > > data;
        static void resizeCanvas( const float &width, const float &height );
    public:
        Game() = delete;
        static sf::RenderWindow window;
        static sf::Color windowColor;
        static Canvas canvas;
        static sf::Color canvasColor;
        static float deltaTime;
        static bool removeScreen( const std::string &key );
        static Screen *getScreen( const std::string &key );
        static bool loadFont( const std::string &key, const std::string &path );
        static bool removeFont( const std::string &key );
        static sf::Font *getFont( const std::string &key );
        static bool loadTexture( const std::string &key, const std::string &path );
        static bool removeTexture( const std::string &key );
        static sf::Texture *getTexture( const std::string &key );
        static bool loadSoundtrack( const std::string &key, const std::string &path );
        static bool removeSoundtrack( const std::string &key );
        static sf::Music *getSoundtrack( const std::string &key );
        static bool loadSound( const std::string &key, const std::string &path );
        static bool removeSound( const std::string &key );
        static sf::SoundBuffer *getSound( const std::string &key );
        template < typename D, typename ... Types > static D *addData( const std::string &key, Types ... args );
        static bool removeData( const std::string &key );
        template < typename D = DataSource > static D *getData( const std::string &key );
        static void loadKeyboardData();
        static void loadMouseData();
        static void load( const sf::VideoMode &videoMode, const std::string &title, const unsigned int &width, const unsigned int &height, const sf::Uint32 &style = sf::Style::Default );
        static void load( const sf::VideoMode &videoMode, const std::string &title, const sf::Uint32 &style = sf::Style::Default );
        static void unload();
        template < typename S, typename ... Types > static S *loadScreen( const std::string &key = "", Types ... args );
        static void start();
        template < typename S, typename ... Types > static void process( const sf::VideoMode &videoMode, const std::string &title, const unsigned int &width, const unsigned int &height, const sf::Uint32 &style, const std::function< void () > &body = [] () {}, const std::string &screenName = "", Types ... args );
        template < typename S, typename ... Types > static void process( const sf::VideoMode &videoMode, const std::string &title, const unsigned int &width, const unsigned int &height, const sf::Uint32 &style, const std::string &screenName, Types ... args );
        template < typename S, typename ... Types > static void process( const sf::VideoMode &videoMode, const std::string &title, const unsigned int &width, const unsigned int &height, const std::function< void () > &body, const std::string &screenName = "", Types ... args );
        template < typename S, typename ... Types > static void process( const sf::VideoMode &videoMode, const std::string &title, const unsigned int &width, const unsigned int &height, const std::string &screenName = "", Types ... args );

        template < typename S, typename ... Types > static void process( const sf::VideoMode &videoMode, const std::string &title, const sf::Uint32 &style, const std::function< void () > &body = [] () {}, const std::string &screenName = "", Types ... args );
        template < typename S, typename ... Types > static void process( const sf::VideoMode &videoMode, const std::string &title, const sf::Uint32 &style, const std::string &screenName, Types ... args );
        template < typename S, typename ... Types > static void process( const sf::VideoMode &videoMode, const std::string &title, const std::function< void () > &body, const std::string &screenName = "", Types ... args );
        template < typename S, typename ... Types > static void process( const sf::VideoMode &videoMode, const std::string &title, const std::string &screenName = "", Types ... args );
        static InputSource &getKeyboardKey( const sf::Keyboard::Key &key );
        static InputSource &getMouseButton( const sf::Mouse::Button &button );
        static sf::Vector2f getMousePosition();
        static int getMouseWheelScroll( const sf::Mouse::Wheel &wheel );
};

template < typename D, typename ... Types > D *Game::addData( const std::string &key, Types ... args ){
    D *data( new D( args ... ) );
    auto *node( Game::data.insert( new KeyNode< DataSource >( key, data ) ) );
    if ( node == 0 ){
        delete data;
        data = 0;
    }
    return data;
}

template < typename D > D *Game::getData( const std::string &key ){
    auto *node( Game::data.find( key ) );
    return dynamic_cast< D* >( node != 0 ? node->getElement()->getElement() : 0 );
}

template < typename S, typename ... Types > S *Game::loadScreen( const std::string &key, Types ... args ){
    S *screen( 0 );
    if ( !Game::loading ){
        screen = ( !key.empty() ? static_cast< S* >( getScreen( key ) ) : 0 );
        if ( screen == 0 ){
            screen = new S( args ... );
            screen->cacheable = !key.empty();
            if ( !key.empty() ){
                Game::screens.insert( new KeyNode< Screen >( key, screen ) );
            }
        }
        Game::previousScreen = Game::screen;
        Game::screen = screen;
        Game::loading = true;
    }else{
        std::cout << "Error trying to load a screen, reason: only one screen can be loaded at time." << std::endl;
    }
    return screen;
}

template < typename S, typename ... Types > void Game::process( const sf::VideoMode &videoMode, const std::string &title, const unsigned int &width, const unsigned int &height, const sf::Uint32 &style, const std::function< void () > &body, const std::string &screenName, Types ... args ){
    Game::load( videoMode, title, width, height, style );
    body();
    Game::loadScreen< S, Types ... >( screenName, args ... );
    Game::start();
    Game::unload();
}

template < typename S, typename ... Types > void Game::process( const sf::VideoMode &videoMode, const std::string &title, const unsigned int &width, const unsigned int &height, const sf::Uint32 &style, const std::string &screenName, Types ... args ){
    Game::process< S, Types ... >( videoMode, title, width, height, style, [] () {}, screenName, args ... );
}

template < typename S, typename ... Types > void Game::process( const sf::VideoMode &videoMode, const std::string &title, const unsigned int &width, const unsigned int &height, const std::function< void () > &body, const std::string &screenName, Types ... args ){
    Game::process< S, Types ... >( videoMode, title, width, height, sf::Style::Default, body, screenName, args ... );
}

template < typename S, typename ... Types > void Game::process( const sf::VideoMode &videoMode, const std::string &title, const unsigned int &width, const unsigned int &height, const std::string &screenName, Types ... args ){
    Game::process< S, Types ... >( videoMode, title, width, height, sf::Style::Default, [] () {}, screenName, args ... );
}


template < typename S, typename ... Types > void Game::process( const sf::VideoMode &videoMode, const std::string &title, const sf::Uint32 &style, const std::function< void () > &body, const std::string &screenName, Types ... args ){
    Game::load( videoMode, title, style );
    body();
    Game::loadScreen< S, Types ... >( screenName, args ... );
    Game::start();
    Game::unload();
}

template < typename S, typename ... Types > void Game::process( const sf::VideoMode &videoMode, const std::string &title, const sf::Uint32 &style, const std::string &screenName, Types ... args ){
    Game::process< S, Types ... >( videoMode, title, style, [] () {}, screenName, args ... );
}

template < typename S, typename ... Types > void Game::process( const sf::VideoMode &videoMode, const std::string &title, const std::function< void () > &body, const std::string &screenName, Types ... args ){
    Game::process< S, Types ... >( videoMode, title, sf::Style::Default, body, screenName, args ... );
}

template < typename S, typename ... Types > void Game::process( const sf::VideoMode &videoMode, const std::string &title, const std::string &screenName, Types ... args ){
    Game::process< S, Types ... >( videoMode, title, sf::Style::Default, [] () {}, screenName, args ... );
}

#endif