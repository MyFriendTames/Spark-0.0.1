#include "GameObject/GameObject.hpp"

GameObject::~GameObject(){
}

void GameObject::setPosition( const float &x, const float &y ){
    setPosition( sf::Vector2f( x, y ) );
}

void GameObject::setScale( const float &x, const float &y ){
    setScale( sf::Vector2f( x, y ) );
}

void GameObject::setScale( const float &scale ){
    setScale( sf::Vector2f( scale, scale ) );
}

void GameObject::setOrigin( const float &x, const float &y ){
    setOrigin( sf::Vector2f( x, y ) );
}

sf::Vector2f GameObject::getDimensions( const bool &scaled ){
    sf::FloatRect &&bounds( getBounds() );
    sf::Vector2f &&scale( scaled ? getScale() : sf::Vector2f( 1, 1 ) );
    return sf::Vector2f( ( bounds.left + bounds.width ) * abs( scale.x ), ( bounds.top + bounds.height ) * abs( scale.y ) );
}

bool GameObject::isInside( const sf::Vector2f &point ){
    sf::Vector2f &&dimensions( getDimensions( false ) );
    sf::Vector2f &&position( getPosition() );
    sf::Vector2f &&scale( getScale() );
    sf::Vector2f origin( getOrigin().x, getOrigin().y );
    float &&rotation( getRotation() );
    sf::Vector2f zero( 0, 0 );
    sf::Vector2f p1( rotate( zero, - origin, rotation ) );
    sf::Vector2f p2( rotate( zero, sf::Vector2f( - origin.x + dimensions.x, - origin.y ), rotation ) );
    sf::Vector2f p3( rotate( zero, sf::Vector2f( - origin + dimensions ), rotation ) );
    sf::Vector2f p4( rotate( zero, sf::Vector2f( - origin.x, - origin.y + dimensions.y ), rotation ) );
    return ::isInside( point,
        position + sf::Vector2f( p1.x * scale.x, p1.y * scale.y ),
        position + sf::Vector2f( p2.x * scale.x, p2.y * scale.y ),
        position + sf::Vector2f( p3.x * scale.x, p3.y * scale.y ),
        position + sf::Vector2f( p4.x * scale.x, p4.y * scale.y )
    );
}