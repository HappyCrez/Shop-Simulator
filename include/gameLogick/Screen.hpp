/*
*   Class is parent for each screen and adds render interface + inhereted the drawable interface 
*   Funcs: Screens Interface
*/
#pragma once
#include "dep.hpp"

class Screen : public sf::Drawable {
public:
    Screen(sf::RenderWindow& wnd, Screens& screenState);

    sf::RenderWindow& wnd;
    Screens& screenState;

    virtual void render(sf::Event& event) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};