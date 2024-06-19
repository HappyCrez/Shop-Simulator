#include "UI/Button.hpp"

Button::Button() { }

Button::Button(sf::Vector2f size, sf::Vector2f pos) {
    rect = sf::RectangleShape();
    setSize(size);
    setPosition(pos);
}

Button::Button(sf::Vector2f size, sf::Vector2f pos, sf::Color bgColor) : Button(size, pos) {
    rect.setFillColor(bgColor);
}

Button::Button(sf::Vector2f size, sf::Vector2f pos, sf::Texture* texture) : Button(size, pos) {
    rect.setTexture(texture);
}

bool Button::isInBounds(sf::Vector2i point) {
    if (point.x > pos.x && point.x < pos.x+size.x &&
        point.y > pos.y && point.y < pos.y+size.y)
        return true;
    return false;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const {
    target.draw(rect, states);
    target.draw(label, states);
}

void Button::setSize(sf::Vector2f size) {
    this->size = size;
    rect.setSize(this->size);
    updateLabelPos();
}

void Button::setPosition(sf::Vector2f pos) {
    this->pos = pos;
    rect.setPosition(this->pos);
    updateLabelPos();
}

void Button::setBGTexture(sf::Texture* texture) {
    rect.setTexture(texture);
}

void Button::setBGColor(sf::Color color) {
    rect.setFillColor(color);
}

void Button::setOutline(float size, sf::Color color) {
    rect.setOutlineThickness(size);
    rect.setOutlineColor(color);
}

void Button::updateLabelPos() {
    sf::Vector2f pos;
    switch (align) {
        case Align::bottom_left:

            break;
        case Align::bottom_right:
        
            break;
        case Align::top_left:
        
            break;
        case Align::top_right:
        
            break;
        case Align::center:
            pos = rect.getPosition()+rect.getSize()/2.f;
            pos = {round(pos.x-label.getLocalBounds().width/2.f), round(pos.y-label.getLocalBounds().height/2.f-10)};
            break;
        default: throw;
    }
    label.setPosition(pos);
}

void Button::setLabel(sf::Font& font, std::string content, sf::Color color, int fontSize, Align align, sf::Text::Style style) {
    label.setFont(font);
    label.setString(content);
    label.setCharacterSize(fontSize);
    label.setFillColor(color);
    label.setStyle(style);
    this->align = align;
    updateLabelPos();
}

void Button::setFont(sf::Font& font) {
    label.setFont(font);
    updateLabelPos();
}

void Button::setFontSize(int fontSize) {
    label.setCharacterSize(fontSize);
    updateLabelPos();
}

void Button::setAlign(Align align) {
    this->align = align;
    updateLabelPos();
}

void Button::setTextColor(sf::Color color) {
    label.setFillColor(color);
}

void Button::setStyle(sf::Text::Style style) {
    label.setStyle(style);
}

void Button::setString(std::string str) {
    label.setString(str);
    updateLabelPos();
}

sf::Vector2f Button::getSize() {
    return size;
}

sf::Vector2f Button::getPosition() {
    return pos;
}