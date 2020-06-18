#ifndef INPUT_SOURCE_HPP
#define INPUT_SOURCE_HPP

#include <string>

class Game;

class InputSource{
    friend Game;
    private:
        std::string name;
        bool pressed;
        bool down;
        bool released;
        InputSource();
    public:
        const std::string &getName();
        bool isPressed();
        bool isDown();
        bool isReleased();
};

#endif