/*
*   Class inhereted Drawable
*   Funcs: Create bot with simple AI and requires
*/
#pragma once
#include "dep.hpp"
#include "loaders/AssetsManager.hpp"

class Bot : public sf::Drawable {
    sf::Sprite sprite;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    Bot(int textureNum);
    Bot(sf::Vector2f pos, int textureNum);
    void setPosition(sf::Vector2f pos);
};