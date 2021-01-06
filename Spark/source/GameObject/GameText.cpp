#include "GameObject/GameText.hpp"

GameText::GameText( const std::string &text, const unsigned int &characterSize ){
    this->text.setString( text );
    this->text.setCharacterSize( characterSize );
}

GameText::GameText( const sf::Font &font, const std::string &text, const unsigned int &characterSize ) :
    text( text, font, characterSize ){
}

void GameText::setFont( const sf::Font &font ){
    text.setFont( font );
}

const sf::Font *GameText::getFont(){
    return text.getFont();
}

void GameText::setText( const std::string &text ){
    this->text.setString( text );
}

std::string GameText::getText(){
    return text.getString().toAnsiString();
}

void GameText::setCharacterSize( const unsigned int &characterSize ){
    text.setCharacterSize( characterSize );
}

unsigned int GameText::getCharacterSize(){
    return text.getCharacterSize();
}

void GameText::setStyle( const sf::Text::Style &style ){
    text.setStyle( style );
}

sf::Text::Style GameText::getStyle(){
    return sf::Text::Style( text.getStyle() );
}

sf::FloatRect GameText::getBounds(){
    return text.getLocalBounds();
}

void GameText::setPosition( const sf::Vector2f &position ){
    text.setPosition( position );
}

sf::Vector2f GameText::getPosition(){
    return text.getPosition();
}

void GameText::setRotation( const float &rotation ){
    text.setRotation( rotation );
}

float GameText::getRotation(){
    return text.getRotation();
}

void GameText::setScale( const sf::Vector2f &scale ){
    text.setScale( scale );
}

sf::Vector2f GameText::getScale(){
    return text.getScale();
}

void GameText::setOrigin( const sf::Vector2f &origin ){
    text.setOrigin( origin );
}

sf::Vector2f GameText::getOrigin(){
    return text.getOrigin();
}

void GameText::process( sf::RenderTarget &target ){
    target.draw( text );
}

void GameText::setFillColor( const sf::Color &color ){
    text.setFillColor( color );
}

sf::Color GameText::getFillColor(){
    return text.getFillColor();
}

void GameText::setOutlineColor( const sf::Color &color ){
    text.setOutlineColor( color );
}

sf::Color GameText::getOutlineColor(){
    return text.getOutlineColor();
}

void GameText::setOutlineSize( const float &outlineSize ){
    text.setOutlineThickness( outlineSize );
}

float GameText::getOutlineSize(){
    return text.getOutlineThickness();
}