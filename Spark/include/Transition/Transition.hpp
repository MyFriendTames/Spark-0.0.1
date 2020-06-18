#ifndef TRANSITION_HPP
#define TRANSITION_HPP

#include <functional>

#include "Game.hpp"
#include "Util.hpp"

class TranslationInterpreter;
class ColorInterpreter;
class DoubleValueInterpreter;
class OscillatingValueInterpreter;

class Transition{
    friend TranslationInterpreter;
    friend ColorInterpreter;
    friend DoubleValueInterpreter;
    friend OscillatingValueInterpreter;
    private:
        float index;
        float limit;
        bool inverse;
        std::function< void () > endingAction;
    public:
        Transition( const float &duration = 0, const bool &inverse = false, const std::function< void () > &endingAction = [] () {} );
        Transition( const float &duration, const std::function< void () > &endingAction );
        void initialize( const float &duration, const bool &inverse = false, const std::function< void () > &endingAction = [] () {} );
        void initialize( const float &duration, const std::function< void () > &endingAction );
        void setIndex( const float &index );
        float getIndex();
        void setDuration( const float &duration );
        float getDuration();
        void setInverse( const bool &inverse );
        bool isInverse();
        void setEndingAction( const std::function< void () > &endingAction );
        void removeEndingAction();
        void invert();
        bool isInProcess();
        void process();
};

#endif