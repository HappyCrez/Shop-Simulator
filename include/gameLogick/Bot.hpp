/*
*   Class inhereted Drawable
*   Funcs: Create bot with simple AI and orders queue
*/
#pragma once
#include "dep.hpp"
#include "loaders/AssetsManager.hpp"

class Bot : public sf::Drawable {
    sf::Sprite sprite;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    std::vector<Tiles> orders;

public:
    Bot(int textureNum, int ordersCnt);
    Bot(sf::Vector2f pos, int textureNum, int ordersCnt);
    void setPosition(sf::Vector2f pos);
    void update(float dt);
    void fillOrderQueue(int ordersCnt);
};