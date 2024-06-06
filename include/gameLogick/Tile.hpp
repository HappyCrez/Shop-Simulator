/*
*   Class inhereted Drawable interface
*   Funcs: Game field  
*/
#pragma once
#include "dep.hpp"

class Tile : public sf::Drawable {
    sf::RectangleShape rect;
    Tiles tileType;
    sf::Vector2f position;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
public:
    Tile(Tiles type);
    Tile(Tiles type, sf::Vector2f pos);

    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition();
    Tiles getType();
};