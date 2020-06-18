#ifndef SPRITE_ANIMATION_HPP
#define SPRITE_ANIMATION_HPP

#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "Util.hpp"
#include "GameObject/GameSprite.hpp"

class SpriteAnimation{
    public:
        enum Direction{
            Forward = 0,
            Backward
        };
        enum LoopType{
            None = 0,
            Restart,
            Reverse
        };
    private:
        sf::IntRect rect;
        unsigned int index;
        unsigned int rows;
        unsigned int columns;
        float time;
        float timeInterval;
        Direction direction;
        LoopType loopType;
        bool ending;
        std::function< void () > endingAction;
    public:
        SpriteAnimation( const sf::IntRect &rect, const unsigned int &rows, const unsigned int &columns, const float &timeInterval = 0.5F, const Direction &direction = Direction::Forward, const LoopType &loopType = LoopType::Restart );
        SpriteAnimation( const sf::IntRect &rect, const unsigned int &rows, const unsigned int &columns, const float &timeInterval, const LoopType &loopType );
        SpriteAnimation( const sf::IntRect &rect, const unsigned int &rows, const unsigned int &columns, const LoopType &loopType );
        SpriteAnimation();
        void initialize( const sf::IntRect &rect, const unsigned int &rows, const unsigned int &columns, const float &timeInterval = 0.5F, const Direction &direction = Direction::Forward, const LoopType & loopType = LoopType::Restart );
        void initialize( const sf::IntRect &rect, const unsigned int &rows, const unsigned int &columns, const float &timeInterval, const LoopType &loopType );
        void initialize( const sf::IntRect &rect, const unsigned int &rows, const unsigned int &columns, const LoopType &loopType );
        void setRect( const sf::IntRect &rect );
        sf::IntRect getRect();
        void setIndex( const unsigned int &index );
        unsigned int getIndex();
        unsigned int getMaxIndex();
        void setRows( const unsigned int &rows );
        unsigned int getRows();
        void setColumns( const unsigned int &columns );
        unsigned int getColumns();
        void setTimeInterval( const float &timeInterval );
        float getTimeInterval();
        void setDirection( const Direction &direction );
        Direction getDirection();
        void reverse();
        void setLoopType( const LoopType &loopType );
        LoopType getLoopType();
        void setEndingAction( const std::function< void () > &endingAction );
        void removeEndingAction();
        void apply( sf::Sprite &sprite );
        void apply( GameSprite &sprite );
        void process();
};

#endif