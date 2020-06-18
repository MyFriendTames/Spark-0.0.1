#include "Context3D.hpp"

Context3D::Context3D( Camera3D &camera, const LightPoint3D &lightPoint ) :
    ignoreOpposites( true ),
    anyTargeted( false ),
    lightEnabled( true ),
    camera( &camera ),
    lightPoint( lightPoint ),
    quads( true ),
    buffer( 0 ){
}

Context3D::Context3D( Camera3D &camera ) :
    Context3D( camera, LightPoint3D( camera.position, camera.eyeDistance ) ){
}

Context3D::~Context3D(){
    camera = 0;
    buffer = 0;
}

void Context3D::setIgnoreOppositesEnabled( const bool &state ){
    if ( ignoreOpposites != state ){
        camera->updated = false;
    }
    ignoreOpposites = state;
}

bool Context3D::isIgnoreOppositesEnabled(){
    return ignoreOpposites;
}

bool Context3D::isAnyTargeted(){
    return anyTargeted;
}

void Context3D::setCamera( Camera3D &camera ){
    this->camera = &camera;
    camera.updated = false;
}

Camera3D &Context3D::getCamera(){
    return *camera;
}

void Context3D::setLightEnabled( const bool &state ){
    lightEnabled = state;
    if ( camera != 0 ){
        camera->updated = false;
    }
}

bool Context3D::isLightEnabled(){
    return lightEnabled;
}

void Context3D::setLightPoint( const LightPoint3D &lightPoint ){
    this->lightPoint = lightPoint;
}

LightPoint3D Context3D::getLightPoint(){
    return lightPoint;
}

Context3D &Context3D::operator << ( Quad3D &quad ){
    if ( quad.context == 0 ){
        quad.context = this;
        quads.insert( &quad );
        camera->updated = false;
    }
    return *this;
}

Context3D &Context3D::operator << ( Object3D &object ){
    object.addTo( *this );
    return *this;
}

void Context3D::process( sf::RenderTarget &target, const sf::Vector2f &fieldOfView, const sf::Vector2f &pointer ){
    Quad3D *targetedQuad( 0 ), *quad( 0 ), *aux( 0 );
    if ( !camera->updated ){
        buffer = 0;
        for ( ListNode< Quad3D > *node( quads.getFirstNode() ); node != 0; node = node->getNextNode() ){
//            nextNode = node->getNextNode();
            quad = node->getElement();
            if ( !( ignoreOpposites && quad->oppositeIgnorable && quad->isOpposite( camera->position ) ) && quad->isVisible( fieldOfView ) ){
                aux = buffer;
                while ( aux != 0 && quad->compare( aux ) >= 0 && aux->nextQuad != 0 && quad->compare( aux->nextQuad ) >= 0 ){
                    aux = aux->nextQuad;
                }
                if ( aux == 0 || ( aux == buffer && quad->compare( buffer ) < 0 ) ){
                    quad->nextQuad = buffer;
                    buffer = quad;
                }else{
                    quad->nextQuad = aux->nextQuad;
                    aux->nextQuad = quad;
                }
            }else{
                quad->targeted = false;
            }
        }
    }
    quad = buffer;
    while ( quad != 0 ){
        quad->process( target );
        quad->targeted = false;
        if ( isInside( pointer, quad->quad[ 0 ].position, quad->quad[ 1 ].position, quad->quad[ 2 ].position, quad->quad[ 3 ].position ) ){
            targetedQuad = quad;
        }
        quad = quad->nextQuad;
    }
    if ( targetedQuad != 0 ){
        targetedQuad->targeted = true;
        anyTargeted = true;
    }else{
        anyTargeted = false;
    }
    if ( !camera->updated ){
        camera->updated = true;
    }
}

void Context3D::process( Canvas &canvas, const sf::Vector2f &fieldOfView, const sf::Vector2f &pointer ){
    process( canvas.canvas, fieldOfView, pointer );
}