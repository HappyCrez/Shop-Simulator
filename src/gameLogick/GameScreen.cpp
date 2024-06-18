#include "gameLogick/GameScreen.hpp"

GameScreen::GameScreen(sf::RenderWindow &wnd, Screens& screenState) : Screen(wnd, screenState) {
    sf::Vector2f wndSize = sf::Vector2f(wnd.getSize());
    
    background = sf::RectangleShape(wndSize);
    background.setFillColor(sf::Color(68,89,93)); // dark blue

    sf::Vector2f center = sf::Vector2f((wnd.getSize() - sf::Vector2u(WORLD_WIDTH*TILE_SIZE, WORLD_HEIGHT*TILE_SIZE)) / 2u);
    gameField.setPosition(center);
    
    panel.initialize(wndSize);
    resize(wndSize);
}

void GameScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background);
    target.draw(gameField);
    target.draw(panel);
}

void GameScreen::update(float dt) {
    gameField.update(dt);
    panel.update(dt);
}

void GameScreen::render(sf::Event& event) {
    panel.render(event);
}

void GameScreen::resize(sf::Vector2f wndSize) {
    // TODO::View port
    // TODO::Position of control panel
}