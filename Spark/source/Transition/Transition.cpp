#include "Transition/Transition.hpp"

Transition::Transition( const float &duration, const bool &inverse, const std::function< void () > &endingAction ) :
    index( 0 ),
    limit( duration ),
    inverse( inverse ),
    endingAction( endingAction ){
}

Transition::Transition( const float &duration, const std::function< void () > &endingAction ) :
    Transition( duration, false, endingAction ){
}

void Transition::initialize( const float &duration, const bool &inverse, const std::function< void () > &endingAction ){
    index = 0;
    this->limit = duration;
    this->inverse = inverse;
    this->endingAction = endingAction;
}

void Transition::initialize( const float &duration, const std::function< void () > &endingAction ){
    initialize( duration, false, endingAction );
}

void Transition::setIndex( const float &index ){
    this->index = ( inverse ? limit : 0 ) + std::min( index, limit ) * ( inverse ? -1 : 1 );
}

float Transition::getIndex(){
    return ( inverse ? limit : 0 ) + std::min( index, limit ) * ( inverse ? -1 : 1 );
}

void Transition::setDuration( const float &duration ){
    limit = duration;
    index = std::min( index, duration );
}

float Transition::getDuration(){
    return limit;
}

void Transition::setInverse( const bool &inverse ){
    if ( this->inverse != inverse ){
        index = abs( limit - index );
    }
    this->inverse = inverse;
}

bool Transition::isInverse(){
    return inverse;
}

void Transition::setEndingAction( const std::function< void () > &endingAction ){
    this->endingAction = endingAction;
}

void Transition::removeEndingAction(){
    endingAction = [] () {};
}

void Transition::invert(){
    index = abs( limit - index );
    inverse = !inverse;
}

bool Transition::isInProcess(){
    return index != limit;
}

void Transition::process(){
    if ( index < limit ){
        index += Game::deltaTime;
        if ( index >= limit ){
            index = limit;
            endingAction();
        }
    }
}