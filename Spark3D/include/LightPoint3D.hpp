#ifndef LIGHT_POINT_3D_HPP
#define LIGHT_POINT_3D_HPP

#include <Spark.hpp>

#include "Util3D.hpp"

class Quad3D;

class LightPoint3D{
    friend Quad3D;
    private:
        sf::Vector3f position;
        float reach;
        float intensity;
        sf::Color color;
        sf::Color getColor( sf::Color color, const float &magnitude );
    public:
        LightPoint3D( const sf::Vector3f &position, const float &reach = 1, const float &intensity = 1, const sf::Color &color = sf::Color::White );
        void setPosition( const sf::Vector3f &position );
        sf::Vector3f getPosition();
        void setReach( const float &reach );
        float getReach();
        void setIntensity( const float &intensity );
        float getIntensity();
        void setColor( const sf::Color &color );
        sf::Color getColor();
};

#endif