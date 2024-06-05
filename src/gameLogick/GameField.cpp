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
            case Tiles::buy:
                buyTiles.push_back(tile);
                break;
            default: // food tiles
                foodTiles.push_back(tile);
                break;
            }
        }
    }
}

void GameField::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shopBG);

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
    
void GameField::setPosition(sf::Vector2f pos) {
    shopBG.setPosition(pos);
    botSpawnPos = {pos.x + shopBG.getLocalBounds().width/2.f + BOT_WIDTH/2, pos.y + shopBG.getLocalBounds().height + BOT_HEIGHT};
    
    for (Tile &tile : buyTiles)
        tile.setPosition(tile.getPosition()+pos-originalPos);
    for (Tile &tile : foodTiles)
        tile.setPosition(tile.getPosition()+pos-originalPos);
    for (Tile &tile : obstackles)
        tile.setPosition(tile.getPosition()+pos-originalPos);
    originalPos = pos;
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