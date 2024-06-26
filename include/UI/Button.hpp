/*
*   Class inhereted Drawable interface
*   Funcs: Click to action  
*/
#pragma once
#include "dep.hpp"

class Button : public sf::Drawable {
    sf::RectangleShape rect;
    sf::Vector2f size;
    sf::Vector2f pos;
    sf::Text label;
    Align align = Align::bottom_left;

    void updateLabelPos();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    Button();
    Button(sf::Vector2f size, sf::Vector2f pos);
    Button(sf::Vector2f size, sf::Vector2f pos, sf::Color bgColor);
    Button(sf::Vector2f size, sf::Vector2f pos, sf::Texture* texture);
    
    bool isInBounds(sf::Vector2i point);

    // Rectangle
    void setSize(sf::Vector2f size);
    void setPosition(sf::Vector2f size);
    void setBGTexture(sf::Texture* texture);
    void setBGColor(sf::Color color);
    void setOutline(float size, sf::Color color);
    
    // Label
    void setLabel(sf::Font& font, std::string content, sf::Color color, int fontSize, Align align, sf::Text::Style style);
    void setFont(sf::Font& font);
    void setTextColor(sf::Color color);
    void setFontSize(int size);
    void setAlign(Align align);
    void setStyle(sf::Text::Style style);
    void setString(std::string str);

    sf::Vector2f getSize();
    sf::Vector2f getPosition();
};