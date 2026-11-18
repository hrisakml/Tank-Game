#include "enemy.hpp"
#include <cmath>
#include <algorithm>

namespace {
    constexpr float CD = 1.f;
    float normalize(float angle){
        while (angle > 180.f) angle -= 360.f;
        while (angle < -180.f) angle += 360.f;
        return angle;
    }

    float rot(float cur, float tar, float tur, float dt){
        float MAX_STEP = tur * dt;
        float smooth = 5.f;
        float dif = normalize(tar - cur);

        if (std::abs(dif)<=MAX_STEP) return tar;

        return cur + dif * (1.f - std::exp(-smooth * dt));
    }
}

Enemy::Enemy(sf::Vector2f startPos)
    :body({25.f, 25.f}), gun({30.f, 10.f})
{
    body.setOrigin({8.f, 8.f});
    body.setPosition(startPos);
    body.setFillColor(sf::Color(89, 97, 89));

    gun.setOrigin({0.f, 5.f});
    gun.setPosition(body.getPosition());
    gun.setFillColor(sf::Color(61, 66, 61));
}

void Enemy::enemyAim(sf::Vector2f pos, float dt){
    sf::Vector2f ePos(body.getPosition());
    cooldownTimer -= dt;
    
    if(cooldownTimer<=0){
        sf::Vector2f direction = pos - ePos;
        const float PI = 3.14159265f;
        float angleRadians = std::atan2(direction.y, direction.x);
        TARGET_ANGLE = angleRadians * (180.f / PI);
        cooldownTimer = CD;
    }

    turretAngle = rot(turretAngle, TARGET_ANGLE, turnSpeed, dt);
    gun.setRotation(sf::degrees(turretAngle));
}

void Enemy::draw(sf::RenderTarget& target) const{
    target.draw(body);
    target.draw(gun);
}