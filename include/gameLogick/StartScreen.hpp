/*
*   Class inhereted Drawable interface
*   Funcs: Main game menu with references to SaveScreen, LoadSaveScreen, NewGameScreen, etc.  
*/
#pragma once
#include "dep.hpp"
#include "loaders/AssetsManager.hpp"
#include "UI/Button.hpp"

class StartScreen : public sf::Drawable {
    sf::RectangleShape background;
    Button load;
    Button newGame;
    Button settings;
    Button exit;
    
    sf::Color btnBG;
    sf::Color hoverBG;
    sf::Color outline;
    sf::Color hoverOutline;

    void resize(sf::Vector2f &wndSize);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
public:
    StartScreen(sf::Vector2f &wndSize);
};
