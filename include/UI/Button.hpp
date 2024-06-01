/*
*   Class inhereted Drawable interface
*   Funcs: Click to action  
*/
#pragma once
#include "dep.hpp"

class Button : public sf::Drawable {
    sf::RectangleShape rect;
    sf::Text label;
    int align = ALIGN_TOP_LEFT;

    void updateLabelPos();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    Button();
    Button(sf::Vector2f size, sf::Vector2f pos);
    Button(sf::Vector2f size, sf::Vector2f pos, sf::Color bgColor);
    Button(sf::Vector2f size, sf::Vector2f pos, sf::Texture* texture);
    
    void actionEvent(std::function<void(void)> action);
    
    // Rectangle
    void setSize(sf::Vector2f& size);
    void setPosition(sf::Vector2f& size);
    void setBGTexture(sf::Texture* texture);
    void setBGColor(sf::Color color);
    void setStroke(int size, sf::Color color);
    
    // Label
    void Button::setLabel(sf::Text& label);

    void setLabel(sf::Font& font, std::string content, sf::Color color, int fontSize, int align);
    void setFont(sf::Font& font);
    void setLabelContent(std::string content);
    void setTextColor(sf::Color color);
    void setFontSize(int size);
    void setAlign(int align);

};