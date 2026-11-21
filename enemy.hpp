#pragma once
#include <SFML/Graphics.hpp>

class Tile;

class Tank;

class Enemy{
    public:
        Enemy(const Tile& tile, const sf::Font& font, int col, int row);

        void update(sf::Vector2f targetPos, float dt);
        void enemyAim(sf::Vector2f pos, float dt);
        void enemyAimIdle(sf::Vector2f pos, float dt);
        void draw(sf::RenderTarget& target) const;

        void takeDamage(int amount);
        bool isDead() const {return health<=0;}

        sf::Vector2f getPosition() const {return body.getPosition(); }
        float getAOErad() { return AOErad; }
        sf::FloatRect getBounds() const {return body.getGlobalBounds();}
    private:
        void refreshHealthText();
        sf::RectangleShape body, gun;
        sf::Text healthText;
        sf::CircleShape AOE;
        sf::Vector2f bodySize = {25.f, 25.f};
        float AOErad = 150.f;
        float cooldownTimer = 0.0f;
        float turretAngle = 0.f;
        float TARGET_ANGLE = 0.f;
        float turnSpeed = 50.f;
        int health = 100;
};