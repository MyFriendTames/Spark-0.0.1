#include "Game.hpp"

Screen *Game::screen( 0 );
Screen *Game::previousScreen( 0 );
InputSource Game::keyboard [ sf::Keyboard::KeyCount ];
InputSource Game::mouse [ sf::Mouse::ButtonCount ];
int Game::mouseWheelScroll [] { 0, 0 };
bool Game::loading( false );
namespace {
    auto formatter( [] ( auto &n ) -> std::string& { return n.getKey(); } );
    auto comparator( [] ( auto &n1, auto &n2 ) { return strcmp( n1.c_str(), n2.c_str() ); } );
}
BinaryTree< std::string, KeyNode< Screen > > Game::screens{ formatter, comparator };
BinaryTree< std::string, KeyNode< sf::Font > > Game::fonts{ formatter, comparator };
BinaryTree< std::string, KeyNode< sf::Texture > > Game::textures{ formatter, comparator };
BinaryTree< std::string, KeyNode< sf::Music > > Game::soundtracks{ formatter, comparator };
BinaryTree< std::string, KeyNode< sf::SoundBuffer > > Game::sounds{ formatter, comparator };
BinaryTree< std::string, KeyNode< DataSource > > Game::data{ formatter, comparator };
sf::RenderWindow Game::window;
sf::Color Game::windowColor( sf::Color::Black );
Canvas Game::canvas;
sf::Color Game::canvasColor( 92, 120, 165 );
float Game::deltaTime( 0 );

void Game::resizeCanvas( const float &width, const float &height ){
    sf::Vector2f canvasSize( Game::canvas.getSize() );
    float scale( std::min( width / canvasSize.x, height / canvasSize.y ) );
    Game::canvas.GameObject::setScale( scale, scale );
    Game::canvas.GameObject::setPosition( ( width - canvasSize.x * scale ) / 2, ( height - canvasSize.y * scale ) / 2 );
    Game::window.setView( sf::View( sf::FloatRect( 0, 0, width, height ) ) );
}

bool Game::removeScreen( const std::string &key ){
    return Game::screens.remove( Game::screens.find( key ) );
}

Screen *Game::getScreen( const std::string &key ){
    auto node( screens.find( key ) );
    return ( node != 0 ? node->getElement()->getElement() : 0 );
}

bool Game::loadFont( const std::string &key, const std::string &path ){
    sf::Font *font( new sf::Font );
    bool state( font->loadFromFile( path ) );
    if ( state ){
        state = Game::fonts.insert( new KeyNode< sf::Font >( key, font ) ) != 0;
    }
    if ( !state ){
        delete font;
    }
    return state;
}

bool Game::removeFont( const std::string &key ){
    return Game::fonts.remove( Game::fonts.find( key ) );
}

sf::Font *Game::getFont( const std::string &key ){
    auto node( fonts.find( key ) );
    return ( node != 0 ? node->getElement()->getElement() : 0 );
}

bool Game::loadTexture( const std::string &key, const std::string &path ){
    sf::Texture *texture( new sf::Texture );
    bool state( texture->loadFromFile( path ) );
    if ( state ){
        state = Game::textures.insert( new KeyNode< sf::Texture >( key, texture ) ) != 0;
    }
    if ( !state ){
        delete texture;
    }
    return state;
}

bool Game::removeTexture( const std::string &key ){
    return Game::textures.remove( Game::textures.find( key ) );
}

sf::Texture *Game::getTexture( const std::string &key ){
    auto node( textures.find( key ) );
    return ( node != 0 ? node->getElement()->getElement() : 0 );
}

bool Game::loadSoundtrack( const std::string &key, const std::string &path ){
    sf::Music *soundtrack( new sf::Music );
    bool state( soundtrack->openFromFile( path ) );
    if ( state ){
        state = Game::soundtracks.insert( new KeyNode< sf::Music >( key, soundtrack ) ) != 0;
    }
    if ( !state ){
        delete soundtrack;
    }
    return state;
}

bool Game::removeSoundtrack( const std::string &key ){
    return Game::soundtracks.remove( Game::soundtracks.find( key ) );
}

sf::Music *Game::getSoundtrack( const std::string &key ){
    auto node( soundtracks.find( key ) );
    return ( node != 0 ? node->getElement()->getElement() : 0 );
}

bool Game::loadSound( const std::string &key, const std::string &path ){
    sf::SoundBuffer *sound( new sf::SoundBuffer );
    bool state( sound->loadFromFile( path ) );
    if ( state ){
        state = Game::sounds.insert( new KeyNode< sf::SoundBuffer >( key, sound ) ) != 0;
    }
    if ( !state ){
        delete sound;
    }
    return state;
}

bool Game::removeSound( const std::string &key ){
    return Game::sounds.remove( Game::sounds.find( key ) );
}

sf::SoundBuffer *Game::getSound( const std::string &key ){
    auto node( sounds.find( key ) );
    return ( node != 0 ? node->getElement()->getElement() : 0 );
}

bool Game::removeData( const std::string &key ){
    return Game::data.remove( Game::data.find( key ) );
}

void Game::loadKeyboardData(){
    Game::keyboard[ sf::Keyboard::A ].name = "A";
    Game::keyboard[ sf::Keyboard::B ].name = "B";
    Game::keyboard[ sf::Keyboard::C ].name = "C";
    Game::keyboard[ sf::Keyboard::D ].name = "D";
    Game::keyboard[ sf::Keyboard::E ].name = "E";
    Game::keyboard[ sf::Keyboard::F ].name = "F";
    Game::keyboard[ sf::Keyboard::G ].name = "G";
    Game::keyboard[ sf::Keyboard::H ].name = "H";
    Game::keyboard[ sf::Keyboard::I ].name = "I";
    Game::keyboard[ sf::Keyboard::J ].name = "J";
    Game::keyboard[ sf::Keyboard::K ].name = "K";
    Game::keyboard[ sf::Keyboard::L ].name = "L";
    Game::keyboard[ sf::Keyboard::M ].name = "M";
    Game::keyboard[ sf::Keyboard::N ].name = "N";
    Game::keyboard[ sf::Keyboard::O ].name = "O";
    Game::keyboard[ sf::Keyboard::P ].name = "P";
    Game::keyboard[ sf::Keyboard::Q ].name = "Q";
    Game::keyboard[ sf::Keyboard::R ].name = "R";
    Game::keyboard[ sf::Keyboard::S ].name = "S";
    Game::keyboard[ sf::Keyboard::T ].name = "T";
    Game::keyboard[ sf::Keyboard::U ].name = "U";
    Game::keyboard[ sf::Keyboard::V ].name = "V";
    Game::keyboard[ sf::Keyboard::W ].name = "W";
    Game::keyboard[ sf::Keyboard::X ].name = "X";
    Game::keyboard[ sf::Keyboard::Y ].name = "Y";
    Game::keyboard[ sf::Keyboard::Z ].name = "Z";
    Game::keyboard[ sf::Keyboard::Num0 ].name = "Num0";
    Game::keyboard[ sf::Keyboard::Num1 ].name = "Num1";
    Game::keyboard[ sf::Keyboard::Num2 ].name = "Num2";
    Game::keyboard[ sf::Keyboard::Num3 ].name = "Num3";
    Game::keyboard[ sf::Keyboard::Num4 ].name = "Num4";
    Game::keyboard[ sf::Keyboard::Num5 ].name = "Num5";
    Game::keyboard[ sf::Keyboard::Num6 ].name = "Num6";
    Game::keyboard[ sf::Keyboard::Num7 ].name = "Num7";
    Game::keyboard[ sf::Keyboard::Num8 ].name = "Num8";
    Game::keyboard[ sf::Keyboard::Num9 ].name = "Num9";
    Game::keyboard[ sf::Keyboard::Escape ].name = "Escape";
    Game::keyboard[ sf::Keyboard::LControl ].name = "LControl";
    Game::keyboard[ sf::Keyboard::LShift ].name = "LShift";
    Game::keyboard[ sf::Keyboard::LAlt ].name = "LAlt";
    Game::keyboard[ sf::Keyboard::LSystem ].name = "LSystem";
    Game::keyboard[ sf::Keyboard::RControl ].name = "RControl";
    Game::keyboard[ sf::Keyboard::RShift ].name = "RShift";
    Game::keyboard[ sf::Keyboard::RAlt ].name = "RAlt";
    Game::keyboard[ sf::Keyboard::RSystem ].name = "RSystem";
    Game::keyboard[ sf::Keyboard::Menu ].name = "Menu";
    Game::keyboard[ sf::Keyboard::LBracket ].name = "LBracket";
    Game::keyboard[ sf::Keyboard::RBracket ].name = "RBracket";
    Game::keyboard[ sf::Keyboard::Semicolon ].name = "Semicolon";
    Game::keyboard[ sf::Keyboard::Comma ].name = "Comma";
    Game::keyboard[ sf::Keyboard::Period ].name = "Period";
    Game::keyboard[ sf::Keyboard::Quote ].name = "Quote";
    Game::keyboard[ sf::Keyboard::Slash ].name = "Slash";
    Game::keyboard[ sf::Keyboard::Backslash ].name = "Backslash";
    Game::keyboard[ sf::Keyboard::Tilde ].name = "Tilde";
    Game::keyboard[ sf::Keyboard::Equal ].name = "Equal";
    Game::keyboard[ sf::Keyboard::Hyphen ].name = "Hyphen";
    Game::keyboard[ sf::Keyboard::Space ].name = "Space";
    Game::keyboard[ sf::Keyboard::Enter ].name = "Enter";
    Game::keyboard[ sf::Keyboard::Backspace ].name = "Backspace";
    Game::keyboard[ sf::Keyboard::Tab ].name = "Tab";
    Game::keyboard[ sf::Keyboard::PageUp ].name = "PageUp";
    Game::keyboard[ sf::Keyboard::PageDown ].name = "PageDown";
    Game::keyboard[ sf::Keyboard::End ].name = "End";
    Game::keyboard[ sf::Keyboard::Home ].name = "Home";
    Game::keyboard[ sf::Keyboard::Insert ].name = "Insert";
    Game::keyboard[ sf::Keyboard::Delete ].name = "Delete";
    Game::keyboard[ sf::Keyboard::Add ].name = "Add";
    Game::keyboard[ sf::Keyboard::Subtract ].name = "Subtract";
    Game::keyboard[ sf::Keyboard::Multiply ].name = "Multiply";
    Game::keyboard[ sf::Keyboard::Divide ].name = "Divide";
    Game::keyboard[ sf::Keyboard::Left ].name = "Left";
    Game::keyboard[ sf::Keyboard::Right ].name = "Right";
    Game::keyboard[ sf::Keyboard::Up ].name = "Up";
    Game::keyboard[ sf::Keyboard::Down ].name = "Down";
    Game::keyboard[ sf::Keyboard::Numpad0 ].name = "Numpad0";
    Game::keyboard[ sf::Keyboard::Numpad1 ].name = "Numpad1";
    Game::keyboard[ sf::Keyboard::Numpad2 ].name = "Numpad2";
    Game::keyboard[ sf::Keyboard::Numpad3 ].name = "Numpad3";
    Game::keyboard[ sf::Keyboard::Numpad4 ].name = "Numpad4";
    Game::keyboard[ sf::Keyboard::Numpad5 ].name = "Numpad5";
    Game::keyboard[ sf::Keyboard::Numpad6 ].name = "Numpad6";
    Game::keyboard[ sf::Keyboard::Numpad7 ].name = "Numpad7";
    Game::keyboard[ sf::Keyboard::Numpad8 ].name = "Numpad8";
    Game::keyboard[ sf::Keyboard::Numpad9 ].name = "Numpad9";
    Game::keyboard[ sf::Keyboard::F1 ].name = "F1";
    Game::keyboard[ sf::Keyboard::F2 ].name = "F2";
    Game::keyboard[ sf::Keyboard::F3 ].name = "F3";
    Game::keyboard[ sf::Keyboard::F4 ].name = "F4";
    Game::keyboard[ sf::Keyboard::F5 ].name = "F5";
    Game::keyboard[ sf::Keyboard::F6 ].name = "F6";
    Game::keyboard[ sf::Keyboard::F7 ].name = "F7";
    Game::keyboard[ sf::Keyboard::F8 ].name = "F8";
    Game::keyboard[ sf::Keyboard::F9 ].name = "F9";
    Game::keyboard[ sf::Keyboard::F10 ].name = "F10";
    Game::keyboard[ sf::Keyboard::F11 ].name = "F11";
    Game::keyboard[ sf::Keyboard::F12 ].name = "F12";
    Game::keyboard[ sf::Keyboard::F13 ].name = "F13";
    Game::keyboard[ sf::Keyboard::F14 ].name = "F14";
    Game::keyboard[ sf::Keyboard::F15 ].name = "F15";
    Game::keyboard[ sf::Keyboard::Pause ].name = "Pause";
}

void Game::loadMouseData(){
    Game::mouse[ sf::Mouse::Left ].name = "Left";
    Game::mouse[ sf::Mouse::Right ].name = "Right";
    Game::mouse[ sf::Mouse::Middle ].name = "Middle";
    Game::mouse[ sf::Mouse::XButton1 ].name = "XButton1";
    Game::mouse[ sf::Mouse::XButton2 ].name = "XButton2";
}

void Game::load( const sf::VideoMode &videoMode, const std::string &title, const unsigned int &width, const unsigned int &height, const sf::Uint32 &style ){
    Game::window.create( videoMode, title, style );
    Game::window.setKeyRepeatEnabled( false );
    Game::canvas.create( width, height );
    Game::canvas.setSmooth( true );
    sf::Vector2u &&windowSize( Game::window.getSize() );
    Game::resizeCanvas( windowSize.x, windowSize.y );
    Game::loadKeyboardData();
    Game::loadMouseData();
}

void Game::load( const sf::VideoMode &videoMode, const std::string &title, const sf::Uint32 &style ){
    Game::load( videoMode, title, videoMode.width, videoMode.height, style );
}

void Game::unload(){
    if ( Game::window.isOpen() ){
        Game::window.close();
    }
    Game::mouseWheelScroll[ 0 ] = 0;
    Game::mouseWheelScroll[ 1 ] = 0;
    Game::deltaTime = 0;
    Game::loading = false;
    if ( Game::previousScreen != 0 ){
        Game::previousScreen->unload();
        if ( !Game::previousScreen->cacheable ){
            delete Game::previousScreen;
        }
        Game::previousScreen = 0;
    }
    if ( Game::screen != 0 ){
        Game::screen->unload();
        if ( !Game::screen->cacheable ){
            delete Game::screen;
        }
        Game::screen = 0;
    }
    Game::screens.clear();
}

void Game::start(){
    sf::Event event;
    sf::Clock deltaClock;

    while ( Game::window.isOpen() ){
        for ( unsigned int i( 0 ); i < sf::Keyboard::KeyCount; i++ ){
            Game::keyboard[ i ].pressed = false;
            Game::keyboard[ i ].down = sf::Keyboard::isKeyPressed( sf::Keyboard::Key( i ) );
            Game::keyboard[ i ].released = false;
        }
        for ( unsigned int i( 0 ); i < sf::Mouse::ButtonCount; i++ ){
            Game::mouse[ i ].pressed = false;
            Game::mouse[ i ].down = sf::Mouse::isButtonPressed( sf::Mouse::Button( i ) );
            Game::mouse[ i ].released = false;
        }
        Game::mouseWheelScroll[ 0 ] = 0;
        Game::mouseWheelScroll[ 1 ] = 0;
        while ( Game::window.pollEvent( event ) ){
            switch ( event.type ){
                case sf::Event::Closed:
                    Game::window.close();
                break;
                case sf::Event::Resized:
                    resizeCanvas( event.size.width, event.size.height );
                    if ( Game::screen != 0 ){
                        Game::screen->resized( event.size.width, event.size.height );
                    }
                break;
                case sf::Event::TextEntered:
                    if ( Game::screen != 0 ){
                        Game::screen->keyTyped( event.text.unicode );
                    }
                break;
                case sf::Event::KeyPressed:
                    Game::keyboard[ event.key.code ].pressed = true;
                    if ( Game::screen != 0 ){
                        Game::screen->keyPressed( event.key.code );
                    }
                break;
                case sf::Event::KeyReleased:
                    Game::keyboard[ event.key.code ].released = true;
                    if ( Game::screen != 0 ){
                        Game::screen->keyReleased( event.key.code );
                    }
                break;
                case sf::Event::MouseButtonPressed:
                    Game::mouse[ event.mouseButton.button ].pressed = true;
                    if ( Game::screen != 0 ){
                        Game::screen->mouseButtonPressed( event.mouseButton.button );
                    }
                break;
                case sf::Event::MouseButtonReleased:
                    Game::mouse[ event.mouseButton.button ].released = true;
                    if ( Game::screen != 0 ){
                        Game::screen->mouseButtonReleased( event.mouseButton.button );
                    }
                break;
                case sf::Event::MouseMoved:
                    if ( Game::screen != 0 ){
                        Game::screen->mouseMoved( Game::getMousePosition() );
                    }
                break;
                case sf::Event::MouseWheelScrolled:
                    Game::mouseWheelScroll[ event.mouseWheelScroll.wheel ] = event.mouseWheelScroll.delta;
                    if ( Game::screen != 0 ){
                        Game::screen->mouseWheelScrolled( event.mouseWheelScroll.delta );
                    }
                break;
                default: break;
            }
        }


        if ( Game::screen != 0 ){
            if ( Game::loading ){
                sf::Vector2f viewSize( Game::canvas.getView().getSize() );
                Game::canvas.setView( sf::View( sf::FloatRect( 0, 0, viewSize.x, viewSize.y ) ) );
                Game::screen->load();
                Game::deltaTime = 0;
                Game::loading = false;
            }
            Game::window.clear( Game::windowColor );
            if ( Game::canvasColor.a > 0 )
            Game::canvas.clear( Game::canvasColor );
            Game::screen->loop();
            if ( Game::previousScreen != 0 ){
                Game::previousScreen->unload();
                if ( !Game::previousScreen->cacheable ){
                    delete Game::previousScreen;
                }
                Game::previousScreen = 0;
            }
        }else{
            Game::window.clear( sf::Color( 50, 50, 50 ) );
            Game::canvas.clear( sf::Color( 135, 230, 139 ) );
        }
        if ( Game::canvasColor.a > 0 ){
            Game::canvas.display();
            Game::canvas.process( Game::window );
        }
        Game::window.display();

        Game::deltaTime = deltaClock.restart().asSeconds();
    }
}

InputSource &Game::getKeyboardKey( const sf::Keyboard::Key &key ){
    return keyboard[ key ];
}

InputSource &Game::getMouseButton( const sf::Mouse::Button &button ){
    return mouse[ button ];
}

sf::Vector2f Game::getMousePosition(){
    const sf::Vector2f &canvasPosition( Game::canvas.getPosition() );
    const sf::Vector2f &canvasScale( Game::canvas.getScale() );
    sf::Vector2i &&mousePosition( sf::Mouse::getPosition( Game::window ) );
    return sf::Vector2f( ( mousePosition.x - canvasPosition.x ) / canvasScale.x, ( mousePosition.y - canvasPosition.y ) / canvasScale.y );
}

int Game::getMouseWheelScroll( const sf::Mouse::Wheel &wheel ){
    return Game::mouseWheelScroll[ wheel ];
}