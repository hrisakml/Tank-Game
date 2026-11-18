#pragma once
#include <SFML/Graphics.hpp>

class Tank{
    public:
        Tank(sf::Vector2f startPos);

        void handleInput(float dt);
        void update(float dt);
        void draw(sf::RenderTarget& target) const;

        sf::Vector2f getPosition() const { return body.getPosition(); }
        sf::Angle bodyRot() const { return bodyAngle; }
        sf::Angle turRot() const { return turretAngle; }

        sf::Angle aimAngle() const {return turretAngle;}
        sf::Vector2f muzzlePos() const;
    private:
        sf::RectangleShape body, turret, gun;
        sf::Angle bodyAngle = sf::degrees(0.f);
        sf::Angle turretAngle = sf::degrees(0.f);
        float moveSpeed = 150.f;
        float turnSpeed = 150.f;
};