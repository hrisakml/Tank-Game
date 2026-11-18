#pragma once
#include <SFML/Graphics.hpp>

class Tile{
    public:
        Tile(sf::Vector2u windowSize, int cellSize);
        int getCellSize() const {return cellSize;}
        int getCols() const {return cols;}
        int getRows() const {return rows;}

        sf::Vector2f cellToPixel(int cols, int rows) const;
        sf::Vector2i pixelToCell(sf::Vector2f pixel) const;

        void draw(sf::RenderTarget &target);
    private:
        sf::RectangleShape tile;
        int cellSize;
        int cols;
        int rows;
};