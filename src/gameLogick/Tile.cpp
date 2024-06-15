#include "gameLogick/Tile.hpp"

Tile::Tile(Tiles type, sf::Vector2f pos) {
    rect.setPosition(pos);
    rect.setSize({TILE_SIZE, TILE_SIZE});
    tileType = type;
    switch(type) {
     case Tiles::no_tile:
        rect.setFillColor(sf::Color::White);
        break;
    case Tiles::obstacle:
        rect.setFillColor(sf::Color::Red);
        break;
    case Tiles::buy:
        rect.setFillColor(sf::Color::Yellow);
        break;
    default: // food tiles
        rect.setFillColor(sf::Color::Green);
        break;
    }
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

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(rect);
}

sf::Vector2f Tile::getScreenPosition(sf::Vector2i gridPosition) {
    return sf::Vector2f(gridPosition * TILE_SIZE); 
}

sf::Vector2i Tile::getGridPosition(sf::Vector2f screenPosition) {
    return sf::Vector2i(screenPosition) / TILE_SIZE;
}