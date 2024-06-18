/*
*   Class inhereted Drawable
*   Funcs: Controls on simulation, buttons, bars, etc.
*/
#pragma once
#include "dep.hpp"
#include "UI/Button.hpp"

class ScrollBar : public sf::Drawable {
    sf::RectangleShape scrollbox;
    sf::CircleShape thumb;
    std::vector<sf::RectangleShape> steps;
    int stepCount;
    int stepIdx;

    sf::Vector2i clickedMousePos;
    float dist;
    bool isMouseClick;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:

    ScrollBar();
    ScrollBar(
        sf::Vector2f position, sf::Vector2f size, int steps, int curStep, sf::Color boxClr, sf::Color thumbClr,
        float outlineThickness, sf::Color boxOutlineClr, sf::Color thumbOutlineClr
        );
    void update(sf::Event& event);
    void updateThumbPosition();
    
    void setPosition(sf::Vector2f position);
    void setStep(int stepIdx);
    
    sf::Vector2f getPosition();
    int getStep();
};