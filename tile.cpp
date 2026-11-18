#include "tile.hpp"
#include <cmath>

Tile::Tile(sf::Vector2u windowSize, int cellSize)
        : cellSize(cellSize), 
        cols(windowSize.x/cellSize),
        rows(windowSize.y/cellSize),
        tile({static_cast<float>(cellSize), static_cast<float>(cellSize)})
{
}

sf::Vector2f Tile::cellToPixel(int col, int row) const{
    return {static_cast<float>(col*cellSize), static_cast<float>(row*cellSize)};
}

sf::Vector2i Tile::pixelToCell(sf::Vector2f pixel) const{
    return {static_cast<int>(std::floor(pixel.x / cellSize)), 
            static_cast<int>(std::floor(pixel.y / cellSize))};
}

void Tile::draw(sf::RenderTarget& target){
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            if ((i+j)%2==0) tile.setFillColor(sf::Color(170, 215, 81));
            else tile.setFillColor(sf::Color(255, 255 ,255));

            tile.setPosition(cellToPixel(j, i));
            target.draw(tile);
        }
    }
}