#include "gameLogick/GameScreen.hpp"

GameScreen::GameScreen(sf::RenderWindow &wnd, Screens& screenState) : Screen(wnd, screenState) {
    sf::Vector2f wndSize = sf::Vector2f(wnd.getSize());
    
    background = sf::RectangleShape(wndSize);
    background.setFillColor(sf::Color(39,39,39,1)); // dark gray

    resize(wndSize);
}

void GameScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background);
    target.draw(gameField);
    target.draw(panel);
}

void GameScreen::update(float dt) {
    gameField.update(dt);
    panel.update();
}

void GameScreen::render(sf::Event& event) {
    panel.render(event);
}

void GameScreen::resize(sf::Vector2f wndSize) {
    // TODO::View port
    // TODO::Position of control panel
}