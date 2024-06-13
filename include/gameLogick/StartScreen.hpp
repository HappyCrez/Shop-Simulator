/*
*   Class inhereted Drawable interface
*   Funcs: Main game menu with references to SaveScreen, LoadSaveScreen, NewGameScreen, etc.  
*/
#pragma once
#include "dep.hpp"
#include "gameLogick/Screen.hpp"
#include "gameLogick/ControlPanel.hpp"
#include "loaders/AssetsManager.hpp"
#include "UI/Button.hpp"

enum class Btns {load = 0, startGame, settings, exit, size};

class StartScreen : public Screen {
    sf::RectangleShape background;
    std::vector<Button> btns;
    
    sf::Color btnBG;
    sf::Color hoverBG;
    sf::Color outlineColor;
    int outlineSize = 1;
    int outlineHoverSize = 2;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void render(sf::Event& event);

    void resize(sf::Vector2f &wndSize);

    Button createButton(sf::Vector2f size, std::string label);
    void onHover(Button& btn);
    void dropHover(Button& btn);
    
public:
    StartScreen(sf::RenderWindow &wnd, Screens& screenState);
};
