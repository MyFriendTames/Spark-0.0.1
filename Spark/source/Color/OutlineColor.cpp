#include "Color/OutlineColor.hpp"

OutlineColor::~OutlineColor(){

}

void OutlineColor::setOutlineColor( const unsigned int &red, const unsigned int &green, const unsigned int &blue, const unsigned int &alpha ){
    setOutlineColor( sf::Color( red, green, blue, alpha ) );
}