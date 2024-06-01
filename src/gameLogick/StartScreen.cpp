#include "gameLogick/StartScreen.hpp"

StartScreen::StartScreen(sf::Vector2f& wndSize) {
    background = sf::RectangleShape(wndSize);
    background.setTexture(&AssetsManager::getInstance().loadTexture(START_SCREEN_BACKGROUND));
    
    btnBG = sf::Color(51,51,51,229);
    load = Button({250, 660}, {0, 0}, btnBG);
    load.setLabel(AssetsManager::getInstance().loadFont(MONTSERRAT_FONT), "New Game", sf::Color::White, 24, ALIGN_CENTER);

    newGame = Button({400, 400}, {0, 0}, btnBG);
    newGame.setLabel(AssetsManager::getInstance().loadFont(MONTSERRAT_FONT), "New Game", sf::Color::White, 24, ALIGN_CENTER);

    settings = Button({400, 100}, {0, 0}, btnBG);
    settings.setLabel(AssetsManager::getInstance().loadFont(MONTSERRAT_FONT), "New Game", sf::Color::White, 24, ALIGN_CENTER);
    
    exit = Button({400, 100}, {0, 0}, btnBG);
    exit.setLabel(AssetsManager::getInstance().loadFont(MONTSERRAT_FONT), "New Game", sf::Color::White, 24, ALIGN_CENTER);

    resize(wndSize);
}

void StartScreen::draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const {
    target.draw(background);
    target.draw(load);
    target.draw(newGame);
    target.draw(settings);
    target.draw(exit);
}

void StartScreen::resize(sf::Vector2f& wndSize) {
    settings.setPosition({1481.f, 519.f});
    newGame.setPosition({1481.f, 89.f});
    load.setPosition({1200.f, 89.f});
    exit.setPosition({1481.f, 649.f});
}