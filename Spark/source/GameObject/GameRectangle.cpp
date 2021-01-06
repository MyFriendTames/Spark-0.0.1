#include "GameObject/GameRectangle.hpp"

GameRectangle::GameRectangle( const sf::Vector2f &size ) :
    shape( size ){
}

sf::FloatRect GameRectangle::getBounds(){
    return shape.getLocalBounds();
}

void GameRectangle::setPosition( const sf::Vector2f &position ){
    shape.setPosition( position );
}

sf::Vector2f GameRectangle::getPosition(){
    return shape.getPosition();
}

void GameRectangle::setRotation( const float &rotation ){
    shape.setRotation( rotation );
}

float GameRectangle::getRotation(){
    return shape.getRotation();
}

void GameRectangle::setScale( const sf::Vector2f &scale ){
    shape.setScale( scale );
}

sf::Vector2f GameRectangle::getScale(){
    return shape.getScale();
}

void GameRectangle::setOrigin( const sf::Vector2f &origin ){
    shape.setOrigin( origin );
}

sf::Vector2f GameRectangle::getOrigin(){
    return shape.getOrigin();
}

void GameRectangle::process( sf::RenderTarget &target ){
    target.draw( shape );
}

void GameRectangle::setFillColor( const sf::Color &color ){
    shape.setFillColor( color );
}

sf::Color GameRectangle::getFillColor(){
    return shape.getFillColor();
}

void GameRectangle::setOutlineColor( const sf::Color &color ){
    shape.setOutlineColor( color );
}

sf::Color GameRectangle::getOutlineColor(){
    return shape.getOutlineColor();
}

void GameRectangle::setOutlineSize( const float &outlineSize ){
    shape.setOutlineThickness( outlineSize );
}

float GameRectangle::getOutlineSize(){
    return shape.getOutlineThickness();
}