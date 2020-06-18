#ifndef OSCILLATING_VALUE_INTERPRETER_HPP
#define OSCILLATING_VALUE_INTERPRETER_HPP

#include "Transition/Transition.hpp"

class OscillatingValueInterpreter{
    private:
        double amplitude;
        double origin;
        double oscillationsCount;
    public:
        OscillatingValueInterpreter( const double &amplitude = 1, const double &origin = 0, const double &oscillationsCount = 1 );
        void setAmplitude( const double &amplitude );
        double getAmplitude();
        void setOrigin( const double &origin );
        double getOrigin();
        void setOscillationsCount( const double &oscillationsCount );
        double getOscillationsCount();
        double operator () ( Transition &transition );
};

#endif