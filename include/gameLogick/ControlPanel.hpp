
/*
*   Class inhereted Drawable
*   Funcs: Controls on simulation, buttons, bars, etc.
*/
#pragma once
#include "dep.hpp"
#include "gameLogick/GameField.hpp"
#include "UI/Button.hpp"
#include "UI/ScrollBar.hpp"
#include "loaders/AssetsManager.hpp"

class ControlPanel : public sf::Drawable {
    sf::RectangleShape bg;
    sf::Text moneyLabel;
    sf::Text timeSpeedLabel;
    int lastIncomeVal = 0;

    ScrollBar timeline;
    GameSpeed gameSpeedState;

    sf::Color btnBG;
    sf::Color btnHoverBG;
    sf::Color outlineColor;
    int outlineSize = 1;
    int outlineHoverSize = 2;

    void updateIncomeLabel();
    Button createButton(sf::Vector2f position, std::string label);
    void createText(sf::Text& text, sf::Vector2f position, std::string label);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void onHover(Button& btn);
    void dropHover(Button& btn);

public:
    ControlPanel();
    
    void render(sf::Event& event);
    void update();
};