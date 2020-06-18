#ifndef CAMERA_3D_HPP
#define CAMERA_3D_HPP

#include <cmath>

#include "Util3D.hpp"

class Context3D;
class Quad3D;

class Camera3D{
    friend Context3D;
    friend Quad3D;
    private:
        bool updated;
        sf::Vector3f position;
        sf::Vector3f axes [ 3 ];
        float eyeDistance;
    public:
        Camera3D( const sf::Vector3f &position, const float &eyeDistance );
        void setPosition( const sf::Vector3f &position );
        sf::Vector3f getPosition();
        sf::Vector3f getAxis( unsigned int axis );
        void rotate( const sf::Vector3f &axis, const double &rotation );
        void rotate( const unsigned int &axis, const double &rotation );
        void translate( const sf::Vector3f &translation );
        void translate( const unsigned int &axis, const float &offset );
        void setEyeDistance( const float &eyeDistance );
        float getEyeDistance();
        sf::Vector2f to2D( sf::Vector3f point );
};

#endif