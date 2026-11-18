#include "bullet.hpp"
#include <cmath>

namespace {
    constexpr float BULLET_SPEED = 500.f;
}

Bullet::Bullet(sf::Vector2f startPos, sf::Angle angle)
            :shape({14.f, 5.f})
{
    shape.setOrigin(shape.getPosition()/2.f);
    shape.setPosition(startPos);
    shape.setRotation(angle);
    shape.setFillColor(sf::Color(255,0,0));

    sf::Vector2f dir({std::cos(angle.asRadians()), std::sin(angle.asRadians())});
    velocity += dir*BULLET_SPEED;
};

void Bullet::update(float dt){
    shape.move(velocity * dt);
}

void Bullet::draw(sf::RenderTarget& target) const{
    target.draw(shape);
}

bool Bullet::isOutside(sf::Vector2u windowSize) const{
    sf::Vector2f pos = shape.getPosition();
    return pos.x > windowSize.x || pos.y > windowSize.y || pos.x < 0 || pos.y < 0;
}