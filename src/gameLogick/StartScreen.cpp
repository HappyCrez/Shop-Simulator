#include "gameLogick/StartScreen.hpp"

StartScreen::StartScreen(sf::Vector2f& wndSize) {
    background = sf::RectangleShape(wndSize);
    background.setTexture(&AssetsManager::getInstance().loadTexture(START_SCREEN_BACKGROUND));
    
    btnBG = sf::Color(51,51,51,229);
    btn = Button({400, 400}, {0, 0}, btnBG);
    btn.setLabel(AssetsManager::getInstance().loadFont(MONTSERRAT_FONT), "New Game", sf::Color::White, 24, ALIGN_CENTER);

    resize(wndSize);
}

void StartScreen::draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const {
    target.draw(background);
    target.draw(btn);
}

void StartScreen::resize(sf::Vector2f& wndSize) {

}