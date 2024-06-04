/*
*   Class inhereted Drawable interface
*   Funcs: Main game menu with references to SaveScreen, LoadSaveScreen, NewGameScreen, etc.  
*/
#pragma once
#include "dep.hpp"
#include "gameLogick/Screen.hpp"
#include "loaders/AssetsManager.hpp"
#include "UI/Button.hpp"

class GameScreen : public Screen {
    sf::RectangleShape background;
    sf::Sprite shopBG;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void render(sf::Event& event);

    void resize(sf::Vector2f wndSize);

public:
    GameScreen(sf::RenderWindow &wnd, Screens& screenState);

};