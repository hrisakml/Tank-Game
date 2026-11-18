#include <SFML/Graphics.hpp>
#include "tank.hpp"
#include "tile.hpp"
#include "bullet.hpp"
#include "enemy.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>

const std::string ASSET_DIR = "assets/";
std::vector<Bullet> bullets;
float shootCD = 0.f;
const float shootDelay = 0.3f;

int main(){
    sf::RenderWindow window(sf::VideoMode({900, 600}), "Game");

    Tile tiles(window.getSize(), 30);

    std::cout << "window: " << window.getSize().x << "x" << window.getSize().y
          << "  cols=" << tiles.getCols()
          << "  rows=" << tiles.getRows()
          << "  cell=" << tiles.getCellSize() << "\n";

    //Debug Text
    sf::Font font;
    if (!font.openFromFile(ASSET_DIR + "font.ttf")) return 1;
    sf::Text debug(font, "", 14);
    debug.setPosition({10.f, 10.f});
    debug.setFillColor(sf::Color::Black);

    Tank tank({400.f, 300.f});
    Enemy enemy({120.f, 120.f});
    Enemy enemy2({120.f, 400.f});
    Enemy enemy3({400.f, 400.f});
    Enemy enemy4({400.f, 120.f});
    Enemy enemy5({680.f, 120.f});
    Enemy enemy6({680.f, 400.f});
    
    sf::Clock clock;
    while(window.isOpen()){
        float dt = clock.restart().asSeconds();
        while(const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()){
                window.close();
            }
        }
        shootCD -= dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && shootCD <= 0.f){
            bullets.emplace_back(tank.muzzlePos(), tank.aimAngle());
            shootCD = shootDelay;
        }

        for (Bullet& b:bullets) b.update(dt, window.getSize());

        bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [&](const Bullet& b) {return b.isOutside(window.getSize()); }),
                bullets.end());

        tank.handleInput(dt);
        tank.update(dt);

        enemy.enemyAim(tank.getPosition(), dt);
        enemy2.enemyAim(tank.getPosition(), dt);
        enemy3.enemyAim(tank.getPosition(), dt);
        enemy4.enemyAim(tank.getPosition(), dt);
        enemy5.enemyAim(tank.getPosition(), dt);
        enemy6.enemyAim(tank.getPosition(), dt);

        debug.setString("Pos: " + std::to_string(tank.getPosition().x) + ", " + std::to_string(tank.getPosition().y) + 
                    "\nRot: " + std::to_string(tank.bodyRot().asDegrees()) + 
                    "\nbarRot: " + std::to_string(tank.turRot().asDegrees()));
        
        window.clear();
        tiles.draw(window);
        window.draw(debug);
        tank.draw(window);

        enemy.draw(window);
        enemy2.draw(window);
        enemy3.draw(window);
        enemy4.draw(window);
        enemy5.draw(window);
        enemy6.draw(window);
        
        for (const Bullet &b:bullets) b.draw(window);
        window.display();
    }
}