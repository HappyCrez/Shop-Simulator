#include "gameLogick/GameScreen.hpp"

GameScreen::GameScreen(sf::RenderWindow &wnd, Screens& screenState) : Screen(wnd, screenState) {
    sf::Vector2f wndSize = sf::Vector2f(wnd.getSize());
    
    background = sf::RectangleShape(wndSize);
    background.setFillColor(sf::Color(39,39,39,1)); // dark gray

    shopBG = sf::Sprite(AssetsManager::loadTexture(GAME_FIELD_BACKGROUND));

    resize(wndSize);
}


void GameScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background);
    target.draw(shopBG);
}

void GameScreen::render(sf::Event& event) {

}


void GameScreen::resize(sf::Vector2f wndSize) {
    shopBG.setPosition({100, 100});
}