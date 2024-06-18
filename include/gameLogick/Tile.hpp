/*
*   Class inhereted Drawable interface
*   Funcs: Game field  
*/
#pragma once
#include "dep.hpp"

class Tile {
    sf::RectangleShape rect;
    Tiles tileType;
    sf::Vector2f position;
    
public:
    Tile() { };
    Tile(Tiles type, sf::Vector2f pos);

    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition();
    Tiles getType();

    static sf::Vector2f getScreenPosition(sf::Vector2i gridPosition);
    static sf::Vector2i getGridPosition(sf::Vector2f screenPosition);
};