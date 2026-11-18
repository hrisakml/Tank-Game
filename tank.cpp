#include "tank.hpp"
#include <cmath>

Tank::Tank(sf::Vector2f startPos)
        : body({65.f, 45.f}), turret({25.f, 25.f}), gun({30.f, 10.f})
{
    body.setOrigin(body.getSize()/2.f);
    turret.setOrigin(turret.getSize()/2.f);
    gun.setOrigin(gun.getSize()/2.f);

    body.setFillColor(sf::Color(10, 110, 22));
    turret.setFillColor(sf::Color(7, 84, 16));
    gun.setFillColor(sf::Color(3, 51, 9));

    body.setPosition(startPos);
};

void Tank::handleInput(float dt){
    using K = sf::Keyboard::Key;

    if (sf::Keyboard::isKeyPressed(K::D)) bodyAngle += sf::degrees(turnSpeed * dt);
    if (sf::Keyboard::isKeyPressed(K::A)) bodyAngle += sf::degrees(-turnSpeed * dt);

    sf::Vector2f foward(std::cos(bodyAngle.asRadians()), std::sin(bodyAngle.asRadians()));
    if (sf::Keyboard::isKeyPressed(K::W)) body.move(foward * moveSpeed * dt);
    if (sf::Keyboard::isKeyPressed(K::S)) body.move(-foward * moveSpeed * dt);

    if (sf::Keyboard::isKeyPressed(K::Right)) turretAngle += sf::degrees(turnSpeed * dt);
    if (sf::Keyboard::isKeyPressed(K::Left)) turretAngle += sf::degrees(-turnSpeed * dt);
}

void Tank::update(float dt){
    sf::Vector2f aim(std::cos(turretAngle.asRadians()), std::sin(turretAngle.asRadians()));

    body.setRotation(bodyAngle);
    turret.setRotation(turretAngle);
    turret.setPosition(body.getPosition());

    gun.setRotation(turretAngle);
    gun.setPosition(body.getPosition() + aim * (gun.getSize().x/2.f));
}

void Tank::draw(sf::RenderTarget& target) const{
    target.draw(body);
    target.draw(gun);
    target.draw(turret);
}

sf::Vector2f Tank::muzzlePos() const{
    sf::Angle a = aimAngle();
    sf::Vector2f dir({std::cos(a.asRadians()), std::sin(a.asRadians())});
    return body.getPosition() + dir * gun.getSize().x;
}