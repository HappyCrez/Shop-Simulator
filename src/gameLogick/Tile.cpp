#include "gameLogick/Tile.hpp"

Tile::Tile(Tiles type) : Tile (type, {0, 0}) { }

Tile::Tile(Tiles type, sf::Vector2f pos) {
    rect.setPosition(pos);
    rect.setSize({TILE_SIZE, TILE_SIZE});
    switch(type) {
     case Tiles::no_tile:
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

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(rect);
}
    