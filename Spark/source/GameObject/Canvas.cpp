#include "GameObject/Canvas.hpp"

Canvas::Canvas(){

}

Canvas::Canvas( const unsigned int &width, const unsigned int &height ){
    create( width, height );
}

Canvas::Canvas( const sf::Vector2u &size ){
    create( size.x, size.y );
}

Canvas::Canvas( const sf::Texture &texture ){
    create( texture );
}

void Canvas::create( const unsigned int &width, const unsigned int &height ){
    canvas.create( width, height );
    shape.setSize( sf::Vector2f( width, height ) );
    shape.setTexture( &canvas.getTexture(), true );
}

void Canvas::create( const sf::Vector2u &size ){
    create( size.x, size.y );
}

void Canvas::create( const sf::Texture &texture ){
    create( texture.getSize() );
    sf::Sprite sprite( texture );
    canvas.draw( sprite );
}

bool Canvas::loadFromFile( const std::string &path ){
    sf::Texture texture;
    bool state( texture.loadFromFile( path ) );
    if ( state ){
        create( texture.getSize() );
        sf::Sprite sprite( texture );
        canvas.clear( sf::Color::Transparent );
        canvas.draw( sprite );
        canvas.display();
    }
    return state;
}

sf::Vector2u Canvas::getSize(){
    return canvas.getSize();
}

void Canvas::setView( const sf::View &view ){
    canvas.setView( view );
}

sf::View Canvas::getView(){
    return canvas.getView();
}

void Canvas::setSmooth( const bool &state ){
    canvas.setSmooth( state );
}

bool Canvas::isSmooth(){
    return canvas.isSmooth();
}

const sf::Texture &Canvas::getTexture(){
    return canvas.getTexture();
}

void Canvas::clear( const sf::Color &color ){
    canvas.clear( color );
}

void Canvas::draw( sf::Drawable &object ){
    canvas.draw( object );
}

void Canvas::process( GameObject &object ){
    object.process( canvas );
}

void Canvas::display(){
    canvas.display();
}

void Canvas::operator *= ( const sf::Texture &texture ){
    sf::Image &&canvasImage( canvas.getTexture().copyToImage() );
    sf::Image &&textureImage( texture.copyToImage() );
    canvas.clear( sf::Color::Transparent );
    sf::RectangleShape pixel( sf::Vector2f( 1, 1 ) );
    for ( unsigned int x( 0 ); x < canvas.getSize().x; ++x ){
        for ( unsigned int y( 0 ); y < canvas.getSize().y; ++y ){
            sf::Color &&color( canvasImage.getPixel( x, y ) );
            if ( color != sf::Color::Transparent ){
                pixel.setPosition( x, y );
                pixel.setFillColor( textureImage.getPixel( x, y ) * color );
                canvas.draw( pixel );
            }
        }
    }
}

void Canvas::operator *= ( const sf::RenderTexture &texture ){
    ( *this ) *= texture.getTexture();
}

void Canvas::operator *= ( const Canvas &canvas ){
    ( *this ) *= canvas.canvas.getTexture();
}

sf::FloatRect Canvas::getBounds(){
    return shape.getLocalBounds();
}

void Canvas::setPosition( const sf::Vector2f &position ){
    shape.setPosition( position );
}

sf::Vector2f Canvas::getPosition(){
    return shape.getPosition();
}

void Canvas::setRotation( const double &rotation ){
    shape.setRotation( rotation );
}

double Canvas::getRotation(){
    return shape.getRotation();
}

void Canvas::setScale( const sf::Vector2f &scale ){
    shape.setScale( scale );
}

sf::Vector2f Canvas::getScale(){
    return shape.getScale();
}

void Canvas::setOrigin( const sf::Vector2f &origin ){
    shape.setOrigin( origin );
}

sf::Vector2f Canvas::getOrigin(){
    return shape.getOrigin();
}

void Canvas::process( sf::RenderTarget &target ){
    target.draw( shape );
}

void Canvas::setFillColor( const sf::Color &color ){
    shape.setFillColor( color );
}

sf::Color Canvas::getFillColor(){
    return shape.getFillColor();
}

void Canvas::setOutlineColor( const sf::Color &color ){
    shape.setOutlineColor( color );
}

sf::Color Canvas::getOutlineColor(){
    return shape.getOutlineColor();
}

void Canvas::setOutlineSize( const float &outlineSize ){
    shape.setOutlineThickness( outlineSize );
}

float Canvas::getOutlineSize(){
    return shape.getOutlineThickness();
}