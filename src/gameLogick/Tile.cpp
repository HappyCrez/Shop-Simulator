#include "gameLogick/Tile.hpp"

Tile::Tile(Tiles type, sf::Vector2f pos) {
    rect.setPosition(pos);
    rect.setSize({TILE_SIZE, TILE_SIZE});
    tileType = type;
}

void Tile::setPosition(sf::Vector2f pos) {
    rect.setPosition(pos);
}

sf::Vector2f Tile::getPosition() {
    return rect.getPosition();
}

Tiles Tile::getType() {
    return tileType;
}

sf::Vector2f Tile::getScreenPosition(sf::Vector2i gridPosition) {
    return sf::Vector2f(gridPosition * TILE_SIZE); 
}

sf::Vector2i Tile::getGridPosition(sf::Vector2f screenPosition) {
    return sf::Vector2i(screenPosition) / TILE_SIZE;
}