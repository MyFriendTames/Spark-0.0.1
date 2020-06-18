#include "Color/FillColor.hpp"

FillColor::~FillColor(){

}

void FillColor::setFillColor( const unsigned char &red, const unsigned char &green, const unsigned char &blue, const unsigned char &alpha ){
    setFillColor( sf::Color( red, green, blue, alpha ) );
}