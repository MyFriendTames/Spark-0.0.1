#include "InputSource.hpp"

InputSource::InputSource() :
    name( "Undefined" ),
    pressed( false ),
    down( false ),
    released( false ){
}

const std::string &InputSource::getName(){
    return name;
}

bool InputSource::isPressed(){
    return pressed;
}

bool InputSource::isDown(){
    return down;
}

bool InputSource::isReleased(){
    return released;
}