#include "bullet.hpp"
#include "enemy.hpp"
#include <cmath>

namespace {
    constexpr float BULLET_SPEED = 500.f;
    constexpr float BULLET_RADIUS = 4.f;
}

Bullet::Bullet(sf::Vector2f startPos, sf::Angle angle)
            :shape({8.f, 8.f})
{
    shape.setOrigin(shape.getPosition()/2.f);
    shape.setPosition(startPos);
    shape.setRotation(angle);
    shape.setFillColor(sf::Color(255,0,0));

    sf::Vector2f dir({std::cos(angle.asRadians()), std::sin(angle.asRadians())});
    velocity += dir*BULLET_SPEED;
};

void Bullet::update(float dt, sf::Vector2u windowSize){
    shape.move(velocity * dt);

    bool hitX = bounceX(windowSize);
    bool hitY = bounceY(windowSize);

    if (hitX){
        velocity.x = -velocity.x;
        bounceCount--;
    }else if (hitY){
        velocity.y = -velocity.y;
        bounceCount--;
    }
}

void Bullet::draw(sf::RenderTarget& target) const{
    target.draw(shape);
}

bool Bullet::bounceX(sf::Vector2u windowSize) const{
    sf::Vector2f pos = shape.getPosition();
    return (pos.x + BULLET_RADIUS > windowSize.x || pos.x - BULLET_RADIUS < 0) && bounceCount > 0; 
}

bool Bullet::bounceY(sf::Vector2u windowSize) const{
    sf::Vector2f pos = shape.getPosition();
    return (pos.y + BULLET_RADIUS > windowSize.y || pos.y - BULLET_RADIUS < 0) && bounceCount > 0; 
}

bool Bullet::isOutside(sf::Vector2u windowSize) const{
    sf::Vector2f pos = shape.getPosition();
    return pos.x > windowSize.x || pos.y > windowSize.y || pos.x < 0 || pos.y < 0;
}