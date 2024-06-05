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
    
void GameField::setPosition(sf::Vector2f pos) {
    shopBG.setPosition(pos);
    botSpawnPos = {pos.x + shopBG.getLocalBounds().width/2.f + BOT_WIDTH/2, pos.y + shopBG.getLocalBounds().height + BOT_HEIGHT};
    
    for (Tile &tile : buyTiles) {
        // TODO::Update buyTiles positions
    }
    for (Tile &tile : foodTiles) {
        // TODO::Update foodTiles positions
    }
    for (Tile &tile : obstackles) {
        // TODO::Update obstackles positions
    }
}

void GameField::update(float dt) {
    for (int i = 0; i < bots.size(); i++)
        bots[i].update(dt);
}

void GameField::restart() {
    bots.clear();
    for (int i = 0; i < 1; i++) {
        // 1 <= orders <= zones::foodTilesSize
        int ordersCnt = rand() % (int)Tiles::foodTilesSize + 1;
        bots.push_back(Bot(i % BOT_TEXTURES_CNT + 1, ordersCnt));
    }
}