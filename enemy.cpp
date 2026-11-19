#include "enemy.hpp"
#include "tile.hpp"
#include <cmath>
#include <numbers>
#include <algorithm>

namespace {
    constexpr float CD = 0.75f;
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

Enemy::Enemy(const Tile& tiles, int col, int row)
    : gun({30.f, 10.f})
{
    float half = tiles.getCellSize()/2.f;
    sf::Vector2f pos = tiles.cellToPixel(col, row) + sf::Vector2f(half, half);
    body.setOrigin(bodySize/2.f);
    body.setSize(bodySize);
    body.setPosition(pos);
    body.setFillColor(sf::Color(89, 97, 89));

    gun.setOrigin({0.f, 5.f});
    gun.setPosition(body.getPosition());
    gun.setFillColor(sf::Color(61, 66, 61));

    AOE.setRadius(AOErad);
    AOE.setOrigin(AOE.getGeometricCenter());
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

    AOE.setPosition(body.getPosition());
    AOE.setFillColor(sf::Color(255, 0, 0, 100));
}

void Enemy::enemyAimIdle(sf::Vector2f pos, float dt){
    turretAngle += turnSpeed * dt;
    gun.setRotation(sf::degrees(turretAngle));
    AOE.setFillColor(sf::Color(sf::Color::Transparent));
}

void Enemy::update(sf::Vector2f targetPos, float dt){
    sf::Vector2f dif(std::abs(targetPos.x - body.getPosition().x), std::abs(targetPos.y - body.getPosition().y));
    if (dif.x < getAOErad() && dif.y < getAOErad()){
        enemyAim(targetPos, dt);
    }else{
        enemyAimIdle(targetPos, dt);
    }
}

void Enemy::draw(sf::RenderTarget& target) const{
    target.draw(AOE);
    target.draw(body);
    target.draw(gun);
}