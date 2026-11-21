#include <SFML/Graphics.hpp>
#include "tank.hpp"
#include "tile.hpp"
#include "bullet.hpp"
#include "enemy.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

const std::string ASSET_DIR = "assets/";
std::vector<Bullet> bullets;
std::vector<Enemy> enemies;
float shootCD = 0.f;
const float shootDelay = 0.3f;

int main(){
    sf::RenderWindow window(sf::VideoMode({900, 600}), "Game");

    Tile tiles(window.getSize(), 30);

    sf::Font font;
    if (!font.openFromFile(ASSET_DIR + "font.ttf")) return 1;

    const std::vector<sf::Vector2i> enemyCells = {{10, 4}, {20, 4}, {10, 15}, {20, 15}};
    for (const sf::Vector2i& c:enemyCells)
        enemies.emplace_back(tiles, font, c.x, c.y);

    std::cout << "window: " << window.getSize().x << "x" << window.getSize().y
          << "  cols=" << tiles.getCols()
          << "  rows=" << tiles.getRows()
          << "  cell=" << tiles.getCellSize() << "\n";

    //Debug Text
    sf::Text debug(font, "", 14);
    debug.setPosition({10.f, 10.f});
    debug.setFillColor(sf::Color::Black);

    Tank tank({400.f, 300.f});
    
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)){
            if (enemies.size() == 0)
            for (const sf::Vector2i& c:enemyCells)
                enemies.emplace_back(tiles, font, c.x, c.y);
        }

        //Bullet update
        for (Bullet& b:bullets) 
            b.update(dt, window.getSize());

        tank.handleInput(dt);
        tank.update(dt);

        //Enemy Aim
        for (Enemy &e:enemies)
            e.update(tank.getPosition(), dt);

        //Bullet Collision
        for (Enemy &e:enemies){
            for (Bullet &b:bullets){
                if (e.isDead()) continue;
                if (b.getBounds().findIntersection(e.getBounds())){
                    e.takeDamage(10);
                    b.markHit();
                    break;
                }
            }
        }
        bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [&](const Bullet& b) {return b.isOutside(window.getSize()) || b.isHit(); }),
        bullets.end());

        enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [&](const Enemy &e) {return e.isDead();}), enemies.end());

        debug.setString("Pos: " + std::to_string(tank.getPosition().x) + ", " + std::to_string(tank.getPosition().y) + 
                    "\nRot: " + std::to_string(tank.bodyRot().asDegrees()) + 
                    "\nbarRot: " + std::to_string(tank.turRot().asDegrees()) +
                    "\nPress R to Respawn Enemies");
        
        window.clear();
        tiles.draw(window);
        window.draw(debug);
        tank.draw(window);

        //Draw Enemies
        for (Enemy &e:enemies)
            e.draw(window);
        
        for (const Bullet &b:bullets) b.draw(window);
        window.display();
    }
}