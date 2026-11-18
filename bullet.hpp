#pragma once
#include <SFML/Graphics.hpp>

class Bullet{
    public:
        Bullet(sf::Vector2f startPos,sf::Angle angle);

        void update(float dt);
        void draw(sf::RenderTarget& target) const;
        bool isOutside(sf::Vector2u windowSize) const;

    private:
        sf::RectangleShape shape;
        sf::Vector2f velocity;
};