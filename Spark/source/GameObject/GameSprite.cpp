#include "GameObject/GameSprite.hpp"

GameSprite::GameSprite( const sf::Texture &texture ) :
    sprite( texture ){
}

GameSprite::GameSprite( const sf::Texture &texture, const sf::IntRect &rect ) :
    sprite( texture, rect ){
}

void GameSprite::setTexture( const sf::Texture &texture, const bool &resetRect ){
    sprite.setTexture( texture, resetRect );
}

const sf::Texture *GameSprite::getTexture(){
    return sprite.getTexture();
}

void GameSprite::setTextureRect( const sf::IntRect &rect ){
    sprite.setTextureRect( rect );
}

sf::IntRect GameSprite::getTextureRect(){
    return sprite.getTextureRect();
}

sf::FloatRect GameSprite::getBounds(){
    return sprite.getLocalBounds();
}

void GameSprite::setPosition( const sf::Vector2f &position ){
    sprite.setPosition( position );
}

sf::Vector2f GameSprite::getPosition(){
    return sprite.getPosition();
}

void GameSprite::setRotation( const float &rotation ){
    sprite.setRotation( rotation );
}

float GameSprite::getRotation(){
    return sprite.getRotation();
}

void GameSprite::setScale( const sf::Vector2f &scale ){
    sprite.setScale( scale );
}

sf::Vector2f GameSprite::getScale(){
    return sprite.getScale();
}

void GameSprite::setOrigin( const sf::Vector2f &origin ){
    sprite.setOrigin( origin );
}

sf::Vector2f GameSprite::getOrigin(){
    return sprite.getOrigin();
}

void GameSprite::process( sf::RenderTarget &target ){
    target.draw( sprite );
}

void GameSprite::setFillColor( const sf::Color &color ){
    sprite.setColor( color );
}

sf::Color GameSprite::getFillColor(){
    return sprite.getColor();
}