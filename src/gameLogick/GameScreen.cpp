#include "gameLogick/GameScreen.hpp"

GameScreen::GameScreen(sf::RenderWindow &wnd, Screens& screenState) : Screen(wnd, screenState) {
    sf::Vector2f wndSize = sf::Vector2f(wnd.getSize());
    
    background = sf::RectangleShape(wndSize);
    background.setFillColor(sf::Color(39,39,39,1)); // dark gray

    
    for (int i = 0; i < 1; i++)
        bots.push_back(Bot(i % BOT_TEXTURES_CNT + 1));

    resize(wndSize);
}

void GameScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background);
    target.draw(GameField::getInstance());
}

void GameScreen::render(sf::Event& event) {

}

void GameScreen::resize(sf::Vector2f wndSize) {
    GameField::setPosition({100.f, 100.f});
    for (Bot &bot : bots)
        bot.setPosition(GameField::getBotSpawnPos());
}