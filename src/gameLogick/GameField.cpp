#include "gameLogick/GameField.hpp"

GameField::GameField() {
    shopBG.setTexture(AssetsManager::loadTexture(GAME_FIELD_BACKGROUND));
    setPosition({0, 0});
}

GameField& GameField::getInstance() {
    static GameField instance;
    return instance;
}

void GameField::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shopBG);
}
    

sf::Vector2f GameField::getBotSpawnPos() {
    return botSpawnPos;
}

void GameField::setPosition(sf::Vector2f pos) {
    shopBG.setPosition(pos);
    botSpawnPos = {pos.x + shopBG.getLocalBounds().width/2.f + BOT_WIDTH/2, pos.y + shopBG.getLocalBounds().height + BOT_HEIGHT};
    for (Tile &tile : tiles) {
        // TODO::Update tile positions
    }
}