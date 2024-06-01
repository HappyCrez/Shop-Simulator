#include "UI/Button.hpp"

Button::Button() { }

Button::Button(sf::Vector2f size, sf::Vector2f pos) {
    rect = sf::RectangleShape(size);
    setPosition(pos);
    this->align = align; 
}

Button::Button(sf::Vector2f size, sf::Vector2f pos, sf::Color bgColor) : Button(size, pos) {
    rect.setFillColor(bgColor);
}

Button::Button(sf::Vector2f size, sf::Vector2f pos, sf::Texture* texture) : Button(size, pos) {
    rect.setTexture(texture);
}

// Action on click
void Button::actionEvent(std::function<void(void)> action) { action(); }

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

void Button::setOutline(int size, sf::Color color) {
    rect.setOutlineThickness(size);
    rect.setOutlineColor(color);
}

//TODO::Update label pos by align
void Button::updateLabelPos() {
    sf::Vector2f pos;
    switch (align) {
        case ALIGN_BOTTOM_LEFT:

        break;
        case ALIGN_BOTTOM_RIGHT:
        
        break;
        case ALIGN_TOP_LEFT:
        
        break;
        case ALIGN_TOP_RIGHT:
        
        break;
        case ALIGN_CENTER:
            pos = rect.getPosition()+rect.getSize()/2.f;
            pos = {pos.x - label.getLocalBounds().width/2, pos.y - label.getCharacterSize()/2.f};
        break;
        default: throw;
    }
    label.setPosition(pos);
}

void Button::setLabel(sf::Font& font, std::string content, sf::Color color, int fontSize, int align) {
    label.setFont(font);
    label.setString(content);
    label.setCharacterSize(fontSize);
    label.setFillColor(color);
    this->align = align;
    updateLabelPos();
}

void Button::setFont(sf::Font& font) {
    label.setFont(font);
    updateLabelPos();
}

void Button::setLabelContent(std::string content) {
    label.setString(content);
    updateLabelPos();
}

void Button::setFontSize(int fontSize) {
    label.setCharacterSize(fontSize);
    updateLabelPos();
}

void Button::setAlign(int align) {
    this->align = align;
    updateLabelPos();
}

void Button::setTextColor(sf::Color color) {
    label.setFillColor(color);
}