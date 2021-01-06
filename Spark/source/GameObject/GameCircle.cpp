#include "GameObject/GameCircle.hpp"

GameCircle::GameCircle( const float &radius, const size_t &pointCount ) :
    shape( radius, pointCount ){
}

void GameCircle::setRadius( const float &radius ){
    shape.setRadius( radius );
}

float GameCircle::getRadius(){
    return shape.getRadius();
}

void GameCircle::setPointCount( const size_t &pointCount ){
    shape.setPointCount( pointCount );
}

size_t GameCircle::getPointCount(){
    return shape.getPointCount();
}

sf::FloatRect GameCircle::getBounds(){
    return shape.getLocalBounds();
}

void GameCircle::setPosition( const sf::Vector2f &position ){
    shape.setPosition( position );
}

sf::Vector2f GameCircle::getPosition(){
    return shape.getPosition();
}

void GameCircle::setRotation( const float &rotation ){
    shape.setRotation( rotation );
}

float GameCircle::getRotation(){
    return shape.getRotation();
}

void GameCircle::setScale( const sf::Vector2f &scale ){
    shape.setScale( scale );
}

sf::Vector2f GameCircle::getScale(){
    return shape.getScale();
}

void GameCircle::setOrigin( const sf::Vector2f &origin ){
    shape.setOrigin( origin );
}

sf::Vector2f GameCircle::getOrigin(){
    return shape.getOrigin();
}

void GameCircle::process( sf::RenderTarget &target ){
    target.draw( shape );
}

void GameCircle::setFillColor( const sf::Color &color ){
    shape.setFillColor( color );
}

sf::Color GameCircle::getFillColor(){
    return shape.getFillColor();
}

void GameCircle::setOutlineColor( const sf::Color &color ){
    shape.setOutlineColor( color );
}

sf::Color GameCircle::getOutlineColor(){
    return shape.getOutlineColor();
}

void GameCircle::setOutlineSize( const float &outlineSize ){
    shape.setOutlineThickness( outlineSize );
}

float GameCircle::getOutlineSize(){
    return shape.getOutlineThickness();
}