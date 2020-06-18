#ifndef CONTEXT_3D_HPP
#define CONTEXT_3D_HPP

#include <iostream>

#include <Spark.hpp>

#include "Camera3D.hpp"
#include "LightPoint3D.hpp"
#include "Quad3D.hpp"
#include "Object3D.hpp"

class Quad3D;

class Context3D{
    friend Quad3D;
    private:
        bool ignoreOpposites;
        bool anyTargeted;
        bool lightEnabled;
        Camera3D *camera;
        LightPoint3D lightPoint;
        List< Quad3D > quads;
        Quad3D *buffer;
    public:
        Context3D( Camera3D &camera, const LightPoint3D &lightPoint );
        Context3D( Camera3D &camera );
        ~Context3D();
        void setIgnoreOppositesEnabled( const bool &state );
        bool isIgnoreOppositesEnabled();
        bool isAnyTargeted();
        void setCamera( Camera3D &camera );
        Camera3D &getCamera();
        void setLightEnabled( const bool &state );
        bool isLightEnabled();
        void setLightPoint( const LightPoint3D &lightPoint );
        LightPoint3D getLightPoint();
        Context3D &operator << ( Quad3D &quad );
        Context3D &operator << ( Object3D &object );
        void process( sf::RenderTarget &target, const sf::Vector2f &fieldOfView, const sf::Vector2f &pointer );
        void process( Canvas &canvas, const sf::Vector2f &fieldOfView, const sf::Vector2f &pointer );
};

#endif