#include "Transition/OscillatingValueInterpreter.hpp"

OscillatingValueInterpreter::OscillatingValueInterpreter( const double &amplitude, const double &origin, const double &oscillationsCount ) :
    amplitude( amplitude ),
    origin( origin ),
    oscillationsCount( abs( oscillationsCount ) ){
}

void OscillatingValueInterpreter::setAmplitude( const double &amplitude ){
    this->amplitude = amplitude;
}

double OscillatingValueInterpreter::getAmplitude(){
    return amplitude;
}

void OscillatingValueInterpreter::setOrigin( const double &origin ){
    this->origin = origin;
}

double OscillatingValueInterpreter::getOrigin(){
    return origin;
}

void OscillatingValueInterpreter::setOscillationsCount( const double &oscillationsCount ){
    this->oscillationsCount = abs( oscillationsCount );
}

double OscillatingValueInterpreter::getOscillationsCount(){
    return oscillationsCount;
}

double OscillatingValueInterpreter::operator () ( Transition &transition ){
    return origin + cos( toRadians( transition.getIndex() * 180 * oscillationsCount / transition.limit ) ) * amplitude;
}