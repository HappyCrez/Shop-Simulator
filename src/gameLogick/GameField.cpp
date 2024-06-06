#include "gameLogick/GameField.hpp"

GameField::GameField() {
    shopBG.setTexture(AssetsManager::loadTexture(GAME_FIELD_BACKGROUND));
    originalPos = {0, 0};
    setPosition(originalPos);

    createTiles();
}

GameField& GameField::getInstance() {
    static GameField instance;
    return instance;
}

void GameField::createTiles() {
    std::string zonesMap = AssetsManager::loadTextFile(ZONES_MAP);
    int rowCnt, colCnt, tileType;
    rowCnt = atoi(zonesMap.data());
    zonesMap.erase(zonesMap.begin(), std::find(zonesMap.begin(), zonesMap.end(), ',') + 1);
    colCnt = atoi(zonesMap.data());

    for (int i = 0; i < rowCnt; i++) {
        for (int j = 0; j < colCnt; j++) {
            zonesMap.erase(zonesMap.begin(), std::find(zonesMap.begin(), zonesMap.end(), ',') + 1);
            tileType = atoi(zonesMap.data()) + (int)Tiles::no_tile;

            Tile tile((Tiles)tileType, {
                static_cast<float>(j * TILE_SIZE),
                static_cast<float>(i * TILE_SIZE)
                });
            switch ((Tiles)tileType) {
            // proceed special tiles
            case Tiles::no_tile:
                break;
            case Tiles::obstacle:
                obstackles.push_back(tile);
                break;
            case Tiles::spawn: // copy in two vectors (spawnTiles, actionTiles)
                spawnTiles.push_back(tile);
            default: // food and buy tiles
                actionTiles.push_back(tile);
                break;
            }
        }
    }
}

void GameField::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shopBG);
    for (int i = 0; i < bots.size(); i++)
        target.draw(bots[i]);
    /*
        ==   DEBUG   ==
    for (Tile &tile : buyTiles)
        target.draw(tile);
    for (Tile &tile : foodTiles)
        target.draw(tile);
    for (Tile &tile : obstackles)
        target.draw(tile);
    */
}    

void GameField::update(float dt) {
    static float spawnTime = 0.f;
    spawnTime += dt;
    if (spawnTime > botSpawnTime) {
        spawnTime = 0.f;
        spawnBot();
    }
    for (int i = 0; i < bots.size(); i++) {
        bots[i].update(dt, actionTiles, obstackles);
        if (bots[i].isDied()) {
            bots.erase(bots.begin() + i);
            i--;
        }
    }
}

void GameField::restart() {
    bots.clear();
}

void GameField::spawnBot() {
    int botSpeed = BOT_MIN_SPEED + rand() % 2;
    int botSkin = rand()%BOT_TEXTURES_CNT + 1;
    int ordersCnt = rand() % (int)Tiles::foodTilesSize + 1; // 1 <= orders <= zones::foodTilesSize
    sf::Vector2f botSpawnPos = spawnTiles[rand()%spawnTiles.size()].getPosition();
    bots.push_back(Bot(botSpawnPos, botSkin, ordersCnt, botSpeed));
}

void GameField::setPosition(sf::Vector2f pos) {
    shopBG.setPosition(pos);
    
    for (Tile &tile : actionTiles)
        tile.setPosition(tile.getPosition()+pos-originalPos);
    for (Tile &tile : obstackles)
        tile.setPosition(tile.getPosition()+pos-originalPos);
    originalPos = pos;
}

void GameField::setBotSpawnTime(float time) {
    botSpawnTime = time;
}