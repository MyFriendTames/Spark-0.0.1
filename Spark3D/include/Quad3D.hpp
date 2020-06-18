#ifndef QUAD_3D_HPP
#define QUAD_3D_HPP

#include <iostream>

#include <Spark.hpp>

#include "Util3D.hpp"
#include "Camera3D.hpp"
#include "Context3D.hpp"

class Context3D;

class Quad3D : public FillColor{
    friend Context3D;
    private:
        Context3D *context;
        Quad3D *nextQuad;
        bool targeted;
        bool oppositeIgnorable;
        sf::Vector3f points [ 4 ];
        sf::VertexArray quad;
        sf::Color color;
        sf::Texture *texture;
    public:
        Quad3D( const sf::Vector3f &p1, const sf::Vector3f &p2, const sf::Vector3f &p3, const sf::Vector3f &p4, const sf::Color &color = sf::Color::White, sf::Texture *texture = 0, const bool &oppositeIgnorable = true );
        Quad3D( const sf::Vector3f &p1, const sf::Vector3f &p2, const sf::Vector3f &p3, const sf::Vector3f &p4, const sf::Color &color, const bool &oppositeIgnorable );
        Quad3D( const sf::Vector3f &p1, const sf::Vector3f &p2, const sf::Vector3f &p3, const sf::Vector3f &p4, sf::Texture *texture, const bool &oppositeIgnorable = true );
        Quad3D( const sf::Color &color = sf::Color::White, const bool &oppositeIgnorable = true );
        Quad3D( const Quad3D &other, const bool &oppositeIgnorable );
        Quad3D( const Quad3D &other );
        ~Quad3D();
        void setEdgeViewEnabled( const bool &state );
        bool isEdgeViewEnabled();
        void setFillColor( const sf::Color &color );
        sf::Color getFillColor();
        void setTexture( sf::Texture *texture );
        sf::Texture *getTexture();
        void setTextureCoords( const sf::Vector2f &p1, const sf::Vector2f &p2, const sf::Vector2f &p3, const sf::Vector2f &p4 );
        void setOppositeIgnorable( const bool &state );
        bool isOppositeIgnorable();
        bool isOpposite( const sf::Vector3f &point );
        bool isVisible( sf::Vector2f fieldOfView );
        bool isTargeted();
        float getDistance();
        int compare( Quad3D *other );
        void setVertex( const unsigned int &index, const sf::Vector3f &point );
        sf::Vector3f getVertex( const unsigned int &index );
        void rotate( const sf::Vector3f &axis, const sf::Vector3f &origin, const double &rotation );
        void translate( const sf::Vector3f &translation );
        void process( sf::RenderTarget &target );
};

#endif