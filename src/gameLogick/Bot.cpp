#include "gameLogick/Bot.hpp"

Bot::Bot(int textureNum, int ordersCnt, float movementSpeed) : Bot({0, 0}, textureNum, ordersCnt, movementSpeed) { }

Bot::Bot(sf::Vector2f pos, int textureNum, int ordersCnt, float movementSpeed) {
    this->movementSpeed = movementSpeed;
    this->waitSpeed = 5;
    this->textureNum = textureNum;

    sprite.setPosition(pos);
    fillOrderQueue(ordersCnt);

    waitBar.setFillColor(sf::Color::Green);
}

// ordersCnt must be in bounds [0; foodTilesSize] 
void Bot::fillOrderQueue(int ordersCnt) {
    orders.clear();
    orders.push_back(Tiles::buy);
    int i = 0;
    while (i < ordersCnt) {
        Tiles random = (Tiles)(rand() % (int)Tiles::foodTilesSize);
        if (std::find(orders.begin(), orders.end(), random) != orders.end())
            continue;
        orders.push_back(random);
        i++;
    }
}

void Bot::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite);
    target.draw(waitBar);
}

void Bot::setPosition(sf::Vector2f pos) {
    sprite.setPosition(pos);
    waitBar.setPosition(pos);
}

void Bot::update(float dt, std::vector<Tile>& buyTiles, std::vector<Tile>& foodTiles, std::vector<Tile>& obstackles) {
    sf::Vector2f target = getTarget(orders.back(), buyTiles, foodTiles, obstackles);
    moveToTarget(dt, target);
    waitBar.setPosition(sprite.getPosition()); // update bar position
}

void Bot::moveToTarget(float dt, sf::Vector2f& target) {
    static bool lastStateMove = false;
    static BotTurn turn = BotTurn::up;
    static float frameCurrentTime = 0;
    frameCurrentTime += dt * frameSpeed;
    if (int(frameCurrentTime) >= BOT_FRAME_COLS) frameCurrentTime = 0;

    bool isMove = true;
    int col = int(frameCurrentTime) * BOT_SIZE;

    if (sprite.getPosition().y + BOT_SIZE/2 < target.y - TARGET_OFFSET) {
        sprite.move(sf::Vector2f(0.f, 1.f) * movementSpeed * dt);
        turn = BotTurn::down;
    }
    else if (sprite.getPosition().y > target.y + TARGET_OFFSET) {
        sprite.move(sf::Vector2f(0.f, -1.f) * movementSpeed * dt);
        turn = BotTurn::up;
    }
    else if (sprite.getPosition().x + BOT_SIZE/2 < target.x - TARGET_OFFSET) {
        sprite.move(sf::Vector2f(1.f, 0.f) * movementSpeed * dt);
        turn = BotTurn::right;
    }
    else if (sprite.getPosition().x > target.x + TARGET_OFFSET) {
        sprite.move(sf::Vector2f(-1.f, 0.f) * movementSpeed * dt);
        turn = BotTurn::left;
    }
    else { // Idle
        isMove = false;
        onTheDestProceed(dt);
    }
    
    // Optimization, change texture only when move state change
    if (lastStateMove != isMove){
        if (isMove) sprite.setTexture(AssetsManager::loadTexture(BOT_TEXTURE_MOVE_BASE + std::to_string(textureNum) + ".png"));
        else sprite.setTexture(AssetsManager::loadTexture(BOT_TEXTURE_IDLE_BASE + std::to_string(textureNum) + ".png"));
        isMove = lastStateMove;    
    }
    
    sprite.setTextureRect(sf::IntRect(col, (int)turn * BOT_SIZE, BOT_SIZE, BOT_SIZE));
}

sf::Vector2f Bot::getTarget(Tiles purpose, std::vector<Tile>& buyTiles, std::vector<Tile>& foodTiles, std::vector<Tile>& obstackles) {
    if (ordersInfo.find(purpose) != ordersInfo.end()) return ordersInfo[purpose];

    sf::Vector2f target = {0, 0};

    if (purpose == Tiles::buy) return buyTiles[0].getPosition();
    int dist = INT_MAX;
    for (Tile &i : foodTiles) {
        if (i.getType() != purpose) continue;
        int currDist = vecLen(sprite.getPosition()-i.getPosition());
        if (dist > currDist) {
            dist = currDist;
            target = i.getPosition() - sf::Vector2f(0, TILE_SIZE);
        }
    }
    return ordersInfo[purpose] = target;
}

void Bot::onTheDestProceed(float dt) {
    static float currentWait = 0.f;
    if (currentWait < BOT_SIZE) {
        currentWait += dt * waitSpeed;
    } else {
        currentWait = 0.f;
        orders.pop_back();
    }
    waitBar.setSize({currentWait, BOT_WAIT_BAR_HEIGHT});
}

int Bot::vecLen(sf::Vector2f vec) {
    return std::hypot(vec.x, vec.y);
}