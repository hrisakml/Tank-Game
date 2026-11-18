#pragma once
#include <SFML/Graphics.hpp>

class Enemy{
    public:
        Enemy(sf::Vector2f startPos);

        void update(float dt);
        void enemyAim(sf::Vector2f pos, float dt);
        void draw(sf::RenderTarget& target) const;

        sf::Vector2f getPosition() const {return body.getPosition(); }
    private:
        sf::RectangleShape body, gun;
        float cooldownTimer = 0.0f;
        float turretAngle = 0.f;
        float TARGET_ANGLE = 0.f;
        float turnSpeed = 100.f;
        int health = 100;
};