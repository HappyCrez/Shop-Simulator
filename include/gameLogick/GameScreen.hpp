/*
*   Class inhereted Drawable interface
*   Funcs: Game wnd with control panel  
*/
#pragma once
#include "dep.hpp"
#include "gameLogick/Screen.hpp"
#include "gameLogick/GameField.hpp"
#include "gameLogick/Bot.hpp"
#include "loaders/AssetsManager.hpp"
#include "UI/Button.hpp"

class GameScreen : public Screen {
    sf::RectangleShape background;
    
    std::vector<Bot> bots;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void render(sf::Event& event);

    void resize(sf::Vector2f wndSize);

public:
    GameScreen(sf::RenderWindow &wnd, Screens& screenState);

};