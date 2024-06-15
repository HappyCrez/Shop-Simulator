#include "gameLogick/GameField.hpp"

GameField::GameField() {
    shopBG.setTexture(AssetsManager::loadTexture(GAME_FIELD_BACKGROUND));
    createTiles();

    setPosition({0, 0});
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
            tileType = atoi(zonesMap.data()) + (int)Tiles::no_tile; // some tiles are special

            Tile tile((Tiles)tileType, {
                static_cast<float>(j * TILE_SIZE),  // Position on the screen 
                static_cast<float>(i * TILE_SIZE)}  //
                );
            switch ((Tiles)tileType) {
            // proceed special tiles
            case Tiles::spawn: // copy in two vectors
                spawnTiles.push_back(tile);
                break;
            }
            grid[i][j] = tile;
        }
    }
}

void GameField::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shopBG);
    /*  =====DEBUG======
        TODO::Delete
    for (std::vector<Tile> &vec : grid)
        for (Tile &tile : vec)
            target.draw(tile);
    */
    for (int i = 0; i < bots.size(); i++)
        target.draw(bots[i]);
}    

void GameField::update(float dt) {
    static float spawnTime = 0.f;
    dt *= timeSpeed;

    spawnTime += dt;
    if (spawnTime > botSpawnTime) {
        spawnTime = 0.f;
        spawnBot();
    }
    for (int i = 0; i < bots.size(); i++) {
        bots[i].update(dt, shopBG.getPosition(), grid);
        
        // add money then bot pay
        income += (bots[i].pay() - bots[i].pay() * discont);

        // delete bot then it leave
        if (bots[i].isLeaved()) {
            bots.erase(bots.begin() + i);
            i--;
        }
    }
}

void GameField::restartDay() {
    bots.clear();
    visits = 0;
    income = 0;
    spawnBot();
}

void GameField::spawnBot() {
    visits++;
    int botSpeed = BOT_MIN_SPEED + rand() % 2;
    int botSkin = rand()%BOT_TEXTURES_CNT + 1;
    int ordersCnt = rand() % (int)Tiles::foodTilesSize + 1; // 1 <= orders <= zones::foodTilesSize
    sf::Vector2i botSpawnPos = Tile::getGridPosition(spawnTiles[rand()%spawnTiles.size()].getPosition() - shopBG.getPosition());
    bots.push_back(Bot(botSpawnPos, shopBG.getPosition(), botSkin, ordersCnt, botSpeed));
}

void GameField::setPosition(sf::Vector2f position) {
    // calculate offset relative last position
    sf::Vector2f offset = position - shopBG.getPosition();
    shopBG.setPosition(position);
    for (std::vector<Tile>& vec : grid) 
        for (Tile &tile : vec)
            tile.setPosition(tile.getPosition() + offset);
    for (Tile& tile : spawnTiles)
        tile.setPosition(tile.getPosition() + offset); 
    for (Bot& bot : bots)
        bot.setPosition(bot.getPosition() + offset);
}

void GameField::setBotSpawnTime(float time) {
    botSpawnTime = time;
}

int GameField::getVisits() {
    return visits;
}

int GameField::getIncome() {
    return income;
}

float GameField::getDiscont() {
    return discont;
}

void GameField::setTimeSpeed(GameSpeed state) {
    timeSpeed = static_cast<float>(state);
}

void GameField::setDiscont(float discont) {
    GameField::discont = discont;
}