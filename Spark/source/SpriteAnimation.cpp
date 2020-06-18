#include "SpriteAnimation.hpp"

SpriteAnimation::SpriteAnimation( const sf::IntRect &rect, const unsigned int &rows, const unsigned int &columns, const float &timeInterval, const Direction &direction, const LoopType &loopType ) :
    rect( rect ),
    index( 0 ),
    rows( rows ),
    columns( columns ),
    time( 0 ),
    timeInterval( abs( timeInterval ) ),
    direction( direction ),
    loopType( loopType ),
    ending( false ),
    endingAction( [] () {} ){
}

SpriteAnimation::SpriteAnimation( const sf::IntRect &rect, const unsigned int &rows, const unsigned int &columns, const float &timeInterval, const LoopType &loopType ) :
    SpriteAnimation( rect, rows, columns, timeInterval, Direction::Forward, loopType ){
}

SpriteAnimation::SpriteAnimation( const sf::IntRect &rect, const unsigned int &rows, const unsigned int &columns, const LoopType &loopType ) :
    SpriteAnimation( rect, rows, columns, 0.5F, Direction::Forward, loopType ){
}

SpriteAnimation::SpriteAnimation() :
    SpriteAnimation( sf::IntRect( 0, 0, 0, 0 ), 1, 1 ){
}

void SpriteAnimation::initialize( const sf::IntRect &rect, const unsigned int &rows, const unsigned int &columns, const float &timeInterval, const Direction &direction, const LoopType &loopType ){
    this->rect = rect;
    index = 0;
    this->rows = rows;
    this->columns = columns;
    time = 0;
    this->timeInterval = abs( timeInterval );
    this->direction = direction;
    this->loopType = loopType;
    ending = false;
    endingAction = [] () {};
}

void SpriteAnimation::initialize( const sf::IntRect &rect, const unsigned int &rows, const unsigned int &columns, const float &timeInterval, const LoopType &loopType ){
    initialize( rect, rows, columns, timeInterval, Direction::Forward, loopType );
}

void SpriteAnimation::initialize( const sf::IntRect &rect, const unsigned int &rows, const unsigned int &columns, const LoopType &loopType ){
    initialize( rect, rows, columns, 0.5F, Direction::Forward, loopType );
}

void SpriteAnimation::setRect( const sf::IntRect &rect ){
    this->rect = rect;
}

sf::IntRect SpriteAnimation::getRect(){
    return rect;
}

void SpriteAnimation::setIndex( const unsigned int &index ){
    this->index = std::min( index, getMaxIndex() );
    ending = false;
}

unsigned int SpriteAnimation::getIndex(){
    return index;
}

unsigned int SpriteAnimation::getMaxIndex(){
    return rows * columns - 1;
}

void SpriteAnimation::setRows( const unsigned int &rows ){
    this->rows = rows;
    unsigned int &&maxIndex( getMaxIndex() );
    index = std::min( index, maxIndex );
    ending = index == maxIndex;
}

unsigned int SpriteAnimation::getRows(){
    return rows;
}

void SpriteAnimation::setColumns( const unsigned int &columns ){
    this->columns = columns;
    unsigned int &&maxIndex( getMaxIndex() );
    index = std::min( index, maxIndex );
    ending = index == maxIndex;
}

unsigned int SpriteAnimation::getColumns(){
    return columns;
}

void SpriteAnimation::setTimeInterval( const float &timeInterval ){
    this->timeInterval = abs( timeInterval );
}

float SpriteAnimation::getTimeInterval(){
    return timeInterval;
}

void SpriteAnimation::setDirection( const Direction &direction ){
    this->direction = direction;
}

SpriteAnimation::Direction SpriteAnimation::getDirection(){
    return direction;
}

void SpriteAnimation::reverse(){
    direction = Direction( !direction );
}

void SpriteAnimation::setLoopType( const LoopType &loopType ){
    this->loopType = loopType;
}

SpriteAnimation::LoopType SpriteAnimation::getLoopType(){
    return loopType;
}

void SpriteAnimation::setEndingAction( const std::function< void () > &endingAction ){
    this->endingAction = endingAction;
}

void SpriteAnimation::removeEndingAction(){
    endingAction = [] () {};
}

void SpriteAnimation::apply( sf::Sprite &sprite ){
    unsigned int row( index / columns );
    sprite.setTextureRect( sf::IntRect( rect.left + rect.width * ( index - row * columns ), rect.top + row * rect.height, rect.width, rect.height ) );
}

void SpriteAnimation::apply( GameSprite &sprite ){
    unsigned int row( index / columns );
    sprite.sprite.setTextureRect( sf::IntRect( rect.left + rect.width * ( index - row * columns ), rect.top + row * rect.height, rect.width, rect.height ) );
}

void SpriteAnimation::process(){
    bool next;
    unsigned int &&maxIndex( getMaxIndex() );
    time += Game::deltaTime;
    while ( time >= timeInterval ){
        time -= timeInterval;
        next = true;
        if ( ending ){
            ending = false;
            switch ( loopType ){
                case LoopType::Restart:
                    index = ( direction == Direction::Forward ? 0 : maxIndex );
                    next = false;
                break;
                case LoopType::Reverse:
                    direction = Direction( !direction );
                    next = true;
                break;
                case LoopType::None:
                    index = ( direction == Direction::Forward ? maxIndex : 0 );
                    endingAction();
                    return;
                break;
            }
            endingAction();
        }
        if ( maxIndex > 0 && next && !( index == 0 && direction == Direction::Backward ) && !( index == maxIndex && direction == Direction::Forward ) ){
            index += ( direction == Direction::Forward ? 1 : -1 );
            ending = ( ( direction == Direction::Forward && index == maxIndex ) || ( direction == Direction::Backward && index == 0 ) );
        }
    }
}