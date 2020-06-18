#ifndef OBJECT_3D_HPP
#define OBJECT_3D_HPP

#include <Spark.hpp>

#include "Camera3D.hpp"

class Object3D{
    public:
        virtual ~Object3D();
        virtual void addTo( Context3D &context ) = 0;
        virtual void rotate( const sf::Vector3f &axis, const sf::Vector3f &origin, const double &rotation ) = 0;
        virtual void translate( const sf::Vector3f &translation ) = 0;
        virtual bool isTargeted() = 0;
};

#endif