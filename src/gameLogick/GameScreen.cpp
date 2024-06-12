#include "gameLogick/GameScreen.hpp"

GameScreen::GameScreen(sf::RenderWindow &wnd, Screens& screenState) : Screen(wnd, screenState) {
    sf::Vector2f wndSize = sf::Vector2f(wnd.getSize());
    
    background = sf::RectangleShape(wndSize);
    background.setFillColor(sf::Color(39,39,39,1)); // dark gray
    
    // TODO::Control panel

    resize(wndSize);
}

void GameScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background);
    target.draw(GameField::getInstance());
    // TODO::Draw control panel
}

void GameScreen::render(sf::Event& event) {
    // TODO::Action on control panel
}

void GameScreen::resize(sf::Vector2f wndSize) {
    // TODO::View port
    // TODO::Position of control panel
}