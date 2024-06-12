#include "UI/ScrollBar.hpp"

ScrollBar::ScrollBar() { }

ScrollBar::ScrollBar(
    sf::Vector2f position, sf::Vector2f size, int stepCount, int stepIdx, sf::Color boxClr, sf::Color thumbClr,
    int outlineThickness, sf::Color boxOutlineClr, sf::Color thumbOutlineClr)
{
    this->stepCount = stepCount;
    this->stepIdx = stepIdx;
    this->dist = size.x / (stepCount-1);

    scrollbox.setSize({size.x, size.y / 10.f});
    scrollbox.setFillColor(boxClr);
    scrollbox.setOutlineColor(boxOutlineClr);
    scrollbox.setOutlineThickness(outlineThickness);

    float stepSize = size.y/2.f;
    float stepCenter = stepSize/2.f;

    thumb.setRadius(stepSize);
    thumb.setOrigin({stepSize, stepSize}); // center of circle
    thumb.setFillColor(thumbClr);
    thumb.setOutlineColor(thumbOutlineClr);
    thumb.setOutlineThickness(outlineThickness);

    for (int i = 0; i < stepCount; i++) {
        sf::RectangleShape step ({stepSize, stepSize});
        step.setOrigin({stepCenter, stepCenter}); // center of rect
        step.rotate(45.f);
        steps.push_back(step);
    }
    setPosition(position);
}

void ScrollBar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(scrollbox);
    for (auto& step : steps)
        target.draw(step);
    target.draw(thumb);
}


void ScrollBar::update(sf::Event& event) {
    // TODO::Scroll logick
    sf::Vector2i mousePos;
    sf::Vector2i thumbPos;
    int thumbSize;

    switch(event.type) {
    case sf::Event::MouseButtonPressed:
        if (event.mouseButton.button != sf::Mouse::Left) break;
        clickedMousePos = {event.mouseButton.x, event.mouseButton.y};
        thumbPos = sf::Vector2i(thumb.getPosition());
        thumbSize = thumb.getRadius();
        // check click on thumb bounds
        if (thumbPos.x - thumbSize < clickedMousePos.x && thumbPos.x + thumbSize > clickedMousePos.x &&
            thumbPos.y + thumbSize > clickedMousePos.y && thumbPos.y - thumbSize < clickedMousePos.y)
            { isMouseClick = true; }
        
        break;
    case sf::Event::MouseButtonReleased:
        if (event.mouseButton.button != sf::Mouse::Left) break;
        isMouseClick = false;
        break;
    case sf::Event::MouseMoved:
        if (!isMouseClick) break;
        mousePos = {event.mouseMove.x, event.mouseMove.y};
        int dx = mousePos.x - clickedMousePos.x;
        int dsteps = static_cast<int>(dx/dist);
        if (dsteps != 0) {
            clickedMousePos = mousePos;
            stepIdx += dsteps;
            if (stepIdx < 0) stepIdx = 0;
            else if (stepIdx >= stepCount) stepIdx = stepCount-1;
            updateThumbPosition();
        }
        break;
    }
}

void ScrollBar::setPosition(sf::Vector2f position) {
    float centerCoordY = position.y + scrollbox.getSize().y/2.f; 
    
    scrollbox.setPosition(position);
    
    updateThumbPosition();
    for (int i = 0; i < steps.size(); i++)
        steps[i].setPosition({position.x + i*dist, centerCoordY});
}

void ScrollBar::updateThumbPosition() {
    float centerCoordY = scrollbox.getPosition().y + scrollbox.getSize().y/2.f; 
    thumb.setPosition({scrollbox.getPosition().x + stepIdx*dist, centerCoordY});
}

sf::Vector2f ScrollBar::getPosition() {
    return scrollbox.getPosition();
}

int ScrollBar::getStep() {
    return stepIdx;
}

void ScrollBar::setStep(int stepIdx) {
    this->stepIdx = stepIdx;
    updateThumbPosition();
}