#include "Transition/DoubleValueInterpreter.hpp"

DoubleValueInterpreter::DoubleValueInterpreter( const double &v1, const double &v2 ) :
    v1( v1 ),
    v2( v2 ){
}

void DoubleValueInterpreter::setValue1( const double &v1 ){
    this->v1 = v1;
}

double DoubleValueInterpreter::getValue1(){
    return v1;
}

void DoubleValueInterpreter::setValue2( const double &v2 ){
    this->v2 = v2;
}

double DoubleValueInterpreter::getValue2(){
    return v2;
}

double DoubleValueInterpreter::operator () ( Transition &transition ){
    double &&m( abs( v2 - v1 ) );
    return v1 + ( v2 < v1 ? -1 : 1 ) * transition.getIndex() * ( m == 0 ? 0 : m / transition.limit );
}