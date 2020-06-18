#include "Quad3D.hpp"

Quad3D::Quad3D( const sf::Vector3f &p1, const sf::Vector3f &p2, const sf::Vector3f &p3, const sf::Vector3f &p4, const sf::Color &color, sf::Texture *texture, const bool &oppositeIgnorable ) :
    context( 0 ),
    nextQuad( 0 ),
    targeted( false ),
    oppositeIgnorable( oppositeIgnorable ),
    points( { p1, p2, p3, p4 } ),
    quad( sf::PrimitiveType::Quads, 4 ),
    color( color ),
    texture( texture ){
}

Quad3D::Quad3D( const sf::Vector3f &p1, const sf::Vector3f &p2, const sf::Vector3f &p3, const sf::Vector3f &p4, const sf::Color &color, const bool &oppositeIgnorable ) :
    Quad3D( p1, p2, p3, p4, color, 0, oppositeIgnorable ){
}

Quad3D::Quad3D( const sf::Vector3f &p1, const sf::Vector3f &p2, const sf::Vector3f &p3, const sf::Vector3f &p4, sf::Texture *texture, const bool &oppositeIgnorable ) :
    Quad3D( p1, p2, p3, p4, sf::Color::White, texture, oppositeIgnorable ){
}

Quad3D::Quad3D( const sf::Color &color, const bool &oppositeIgnorable ) :
    Quad3D( sf::Vector3f( -1, 1, 0 ), sf::Vector3f( -1, -1, 0 ), sf::Vector3f( 1, -1, 0 ), sf::Vector3f( 1, 1, 0 ), color, 0, oppositeIgnorable ){
}

Quad3D::Quad3D( const Quad3D &other, const bool &oppositeIgnorable ) :
    context( 0 ),
    nextQuad( 0 ),
    targeted( false ),
    oppositeIgnorable( oppositeIgnorable ),
    points( { other.points[ 0 ], other.points[ 1 ], other.points[ 2 ], other.points[ 3 ] } ),
    quad( other.quad.getPrimitiveType(), 4 ),
    color( other.color ),
    texture( other.texture ){
    quad[ 0 ] = other.quad[ 0 ];
    quad[ 1 ] = other.quad[ 1 ];
    quad[ 2 ] = other.quad[ 2 ];
    quad[ 3 ] = other.quad[ 3 ];
}

Quad3D::Quad3D( const Quad3D &other ) :
    Quad3D( other, other.oppositeIgnorable ){
}

Quad3D::~Quad3D(){
    context = 0;
    nextQuad = 0;
}

void Quad3D::setEdgeViewEnabled( const bool &state ){
    quad.setPrimitiveType( state ? sf::PrimitiveType::LineStrip : sf::PrimitiveType::Quads );
}

bool Quad3D::isEdgeViewEnabled(){
    return quad.getPrimitiveType() == sf::PrimitiveType::LineStrip;
}

void Quad3D::setFillColor( const sf::Color &color ){
    this->color = color;
    if ( context != 0 ){
        for ( unsigned int i( 0 ); i < 4; ++i ){
            quad[ i ].color = context->lightEnabled ? context->lightPoint.getColor( color, getMagnitude( context->lightPoint.position - points[ i ] ) ) : color;
        }
    }
}

sf::Color Quad3D::getFillColor(){
    return color;
}

void Quad3D::setTexture( sf::Texture *texture ){
    this->texture = texture;
}

sf::Texture *Quad3D::getTexture(){
    return texture;
}

void Quad3D::setTextureCoords( const sf::Vector2f &p1, const sf::Vector2f &p2, const sf::Vector2f &p3, const sf::Vector2f &p4 ){
    quad[ 0 ].texCoords = p1;
    quad[ 1 ].texCoords = p2;
    quad[ 2 ].texCoords = p3;
    quad[ 3 ].texCoords = p4;
}

void Quad3D::setOppositeIgnorable( const bool &state ){
    oppositeIgnorable = state;
    if ( context != 0 ){
        context->camera->updated = false;
    }
}

bool Quad3D::isOppositeIgnorable(){
    return oppositeIgnorable;
}

bool Quad3D::isOpposite( const sf::Vector3f &point ){
    bool state( true );
    if ( context != 0 ){
        sf::Vector3f v( points[ 0 ] - points[ 1 ] ); //Vertical
        v /= getMagnitude( v );
        sf::Vector3f h( points[ 2 ] - points[ 1 ] ); //Horizontal
        h /= getMagnitude( h );
        sf::Vector3f n( h % v );
        state = point * n < points[ 1 ] * n;
    }
    return state;
}

bool Quad3D::isVisible( sf::Vector2f fieldOfView ){
    bool state( false );
    if ( context != 0 ){
        fieldOfView /= 100.0f;
        fieldOfView /= 2.0f;

        sf::Vector3f &&vZ( -context->camera->axes[ 2 ] * context->camera->eyeDistance );

        sf::Vector3f &&v1( vZ - context->camera->axes[ 0 ] * fieldOfView.x + context->camera->axes[ 1 ] * fieldOfView.y ), &&v2( vZ - context->camera->axes[ 0 ] * fieldOfView.x - context->camera->axes[ 1 ] * fieldOfView.y ), &&v3( vZ + context->camera->axes[ 0 ] * fieldOfView.x - context->camera->axes[ 1 ] * fieldOfView.y ), &&v4( vZ + context->camera->axes[ 0 ] * fieldOfView.x + context->camera->axes[ 1 ] * fieldOfView.y );
        v1 /= getMagnitude( v1 ); //Top-Left
        v2 /= getMagnitude( v2 ); //Bottom-Left
        v3 /= getMagnitude( v3 ); //Bottom-Right
        v4 /= getMagnitude( v4 ); //Top-Right

        sf::Vector3f &&n1( v2 % v1 ); //Left
        sf::Vector3f &&n2( v3 % v2 ); //Bottom
        sf::Vector3f &&n3( v4 % v3 ); //Right
        sf::Vector3f &&n4( v1 % v4 ); //Top

        for ( unsigned int i( 0 ); i < 4; ++i ){
            if ( !context->camera->updated ){
                quad[ i ].position = context->camera->to2D( points[ i ] );
            }
            if ( !state ){
                state = points[ i ] * n1 > context->camera->position * n1 &&
                        points[ i ] * n2 > context->camera->position * n2 &&
                        points[ i ] * n3 > context->camera->position * n3 &&
                        points[ i ] * n4 > context->camera->position * n4;
            }
        }
    }
    return state;
}

bool Quad3D::isTargeted(){
    return targeted;
}

float Quad3D::getDistance(){
    return ( context == 0 ? 0 : std::min( getMagnitude( points[ 0 ] - context->camera->position ), std::min( getMagnitude( points[ 1 ] - context->camera->position ), std::min( getMagnitude( points[ 2 ] - context->camera->position ), getMagnitude( points[ 3 ] - context->camera->position ) ) ) ) );
}

int Quad3D::compare( Quad3D *other ){
    int result( 0 );

    if ( context != 0 ){
        sf::Vector3f &&n1( toUnitary( ( points[ 0 ] - points[ 1 ] ) % ( points[ 2 ] - points[ 1 ] ) ) );
        sf::Vector3f &&n2( toUnitary( ( other->points[ 0 ] - other->points[ 1 ] ) % ( other->points[ 2 ] - other->points[ 1 ] ) ) );

        for ( unsigned int i( 0 ); i < 4; ++i ){
            if ( isInside( other->quad[ i ].position, quad ) ){
                sf::Vector3f &&v( toUnitary( other->points[ i ] - context->camera->position ) );
                float t1( ( n1 * context->camera->position - n1 * points[ i ] ) / ( n1 * v ) );
                float t2( ( n2 * context->camera->position - n2 * other->points[ i ] ) / ( n2 * v ) );
                result = t1 < t2 ? -1 : t1 > t2 ? 1 : 0;
                break;
            }
            if ( isInside( quad[ i ].position, other->quad ) ){
                sf::Vector3f &&v( toUnitary( points[ i ] - context->camera->position ) );
                float t1( ( n1 * context->camera->position - n1 * points[ i ] ) / ( n1 * v ) );
                float t2( ( n2 * context->camera->position - n2 * other->points[ i ] ) / ( n2 * v ) );
                result = t1 < t2 ? -1 : t1 > t2 ? 1 : 0;
                break;
            }
        }
    }

    return result;
}

void Quad3D::setVertex( const unsigned int &index, const sf::Vector3f &point ){
    if ( index < 4 ){
        points[ index ] = point;
        if ( context != 0 ){
            context->camera->updated = false;
        }
    }
}

sf::Vector3f Quad3D::getVertex( const unsigned int &index ){
    return index < 4 ? points[ index ] : sf::Vector3f( 0, 0, 0 );
}

void Quad3D::rotate( const sf::Vector3f &axis, const sf::Vector3f &origin, const double &rotation ){
    points[ 0 ] = ::rotate( axis, origin, points[ 0 ], rotation );
    points[ 1 ] = ::rotate( axis, origin, points[ 1 ], rotation );
    points[ 2 ] = ::rotate( axis, origin, points[ 2 ], rotation );
    points[ 3 ] = ::rotate( axis, origin, points[ 3 ], rotation );
    if ( context != 0 ){
        context->camera->updated = false;
    }
}

void Quad3D::translate( const sf::Vector3f &translation ){
    points[ 0 ] += translation;
    points[ 1 ] += translation;
    points[ 2 ] += translation;
    points[ 3 ] += translation;
    if ( context != 0 ){
        context->camera->updated = false;
    }
}

void Quad3D::process( sf::RenderTarget &target ){
    if ( context != 0 ){
        if ( !context->camera->updated ){
            for ( unsigned int i( 0 ); i < 4; ++i ){
                quad[ i ].color = context->lightEnabled ? context->lightPoint.getColor( color, getMagnitude( context->lightPoint.position - points[ i ] ) ) : color;
            }
        }
        if ( texture != 0 ){
            target.draw( quad, texture );
        }else{
            target.draw( quad );
        }
    }
}