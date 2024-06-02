/*
*   Class inhereted Drawable interface
*   Funcs: Main game menu with references to SaveScreen, LoadSaveScreen, NewGameScreen, etc.  
*/
#pragma once
#include "dep.hpp"
#include "Renderable.hpp"
#include "loaders/AssetsManager.hpp"
#include "UI/Button.hpp"

class StartScreen : public Renderable {
    sf::RenderWindow& wnd;
    int& screenState;
    sf::RectangleShape background;
    Button load;
    Button startGame;
    Button settings;
    Button exit;
    
    sf::Color btnBG;
    sf::Color hoverBG;
    sf::Color outlineColor;
    int outlineSize = 1;
    int outlineHoverSize = 2;

    void resize(sf::Vector2f &wndSize);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void onHover(Button& btn);
    void dropHover(Button& btn);
    
public:
    StartScreen(sf::RenderWindow &wnd, int& screenState);
    virtual void render(sf::Event& event);
};
