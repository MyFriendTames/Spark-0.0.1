#ifndef DOUBLE_VALUE_INTERPRETER_HPP
#define DOUBLE_VALUE_INTERPRETER_HPP

#include "Transition/Transition.hpp"

class DoubleValueInterpreter{
    private:
        double v1;
        double v2;
    public:
        DoubleValueInterpreter( const double &v1 = 0, const double &v2 = 1 );
        void setValue1( const double &v1 );
        double getValue1();
        void setValue2( const double &v2 );
        double getValue2();
        double operator () ( Transition &transition );
};

#endif