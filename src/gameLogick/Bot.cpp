#include "gameLogick/Bot.hpp"

Bot::Bot(int textureNum, int ordersCnt, float movementSpeed) : Bot({0, 0}, {0, 0}, textureNum, ordersCnt, movementSpeed, serveTime) { }

Bot::Bot(sf::Vector2i position, sf::Vector2f offset, int textureNum, int ordersCnt, float movementSpeed, float serveTime) {
    this->movementSpeed = movementSpeed*10.f;
    this->serveTime = serveTime;
    this->textureNum = textureNum;
    state = BotState::alive;
    money = 0;

    sprite.setPosition(Tile::getScreenPosition(position) + offset - sf::Vector2f(0, BOT_SIZE));
    posOnScreen = sprite.getPosition() + sf::Vector2f(BOT_SIZE/2.f, BOT_SIZE/2.f);
    posInGrid = position;
    
    waitBar.setFillColor(sf::Color::Green);
    
    fillOrderQueue(ordersCnt);
    
}

// ordersCnt must be in bounds [0; foodTilesSize] 
void Bot::fillOrderQueue(int ordersCnt) {
    orders.push_back(Tiles::spawn);
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

void Bot::update(float dt, sf::Vector2f offset, std::vector<std::vector<Tile>>& grid) {
    if (state == BotState::leaved) return; // don't update leaved bot
    posOnScreen = sprite.getPosition() + sf::Vector2f(BOT_SIZE/2.f, BOT_SIZE/4.f*3.f);
    posInGrid = sf::Vector2i(posOnScreen - offset) / TILE_SIZE;

    sf::Vector2i target = getNextTarget(grid, orders.back());
    moveToTarget(dt, target, offset, grid);
    waitBar.setPosition(sprite.getPosition()); // update bar position
}

// Get next coords of tile in path
sf::Vector2i Bot::getNextTarget(std::vector<std::vector<Tile>>& grid, Tiles& purpose) {
    if (!path.empty()) return path.back();
    
    // find neareast purpose tile
    sf::Vector2i target;
    int dist = INT32_MAX;
    for (int i = 0; i < WORLD_HEIGHT; i++) {
        for (int j = 0; j < WORLD_WIDTH; j++) {
            if (grid[i][j].getType() != purpose) continue;

            sf::Vector2f curVec = sprite.getPosition()-grid[i][j].getPosition();
            int currDist = static_cast<int>(std::hypot(curVec.x, curVec.y));
            if (dist > currDist) {
                dist = currDist;
                target = {j, i};
            }
        }
    }
    generatePathToTarget(target, grid, orders.back());
    return path.back();
}

void Bot::generatePathToTarget(sf::Vector2i& target, std::vector<std::vector<Tile>>& grid, Tiles& purpose) {
    std::queue<sf::Vector2i> q;
    std::vector<std::vector<sf::Vector2i>> prev(WORLD_HEIGHT, std::vector(WORLD_WIDTH, sf::Vector2i(-1, -1)));
    int dx[4] = { -1, 0, 1, 0 };
    int dy[4] = { 0, 1, 0, -1 };
    
    q.push(posInGrid);
    while (!q.empty()) {
        sf::Vector2i curPos = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int col = curPos.x + dx[i];
            int row = curPos.y + dy[i];

            if (col <= 0 || col >= WORLD_WIDTH  ||
                row <= 0 || row >= WORLD_HEIGHT ||
                (prev[row][col].x != -1 && prev[row][col].y != -1) ||
                (grid[row][col].getType() != Tiles::no_tile && grid[row][col].getType() != purpose))
                { continue; }

            prev[row][col] = curPos;
            q.push({col,row});
        }
    }

    path.clear();
    sf::Vector2i cur = target;
    prev[posInGrid.y][posInGrid.x] = {-1, -1};
    
    path.push_back(cur);
    while (prev[cur.y][cur.x] != sf::Vector2i(-1, -1)) {
        cur = prev[cur.y][cur.x];
        path.push_back(cur);
    }
    path.pop_back();
}

void Bot::moveToTarget(float dt, sf::Vector2i& target, sf::Vector2f& offset, std::vector<std::vector<Tile>>& grid) {
    frameTime += dt * frameSpeed;
    if (int(frameTime) >= BOT_FRAME_COLS) frameTime = 0;

    bool isMove = true;
    int col = int(frameTime) * BOT_SIZE;

    sf::Vector2f targetPos = Tile::getScreenPosition(target) + offset + sf::Vector2f(TILE_SIZE/2.f, TILE_SIZE/2.f);

    if (posOnScreen.y < targetPos.y - TARGET_OFFSET) {
        turn = BotTurn::down;
        moveDirection(turn, dt);
    }
    else if (posOnScreen.y > targetPos.y + TARGET_OFFSET) {
        turn = BotTurn::up;
        moveDirection(turn, dt);
    }
    else if (posOnScreen.x < targetPos.x - TARGET_OFFSET) {
        turn = BotTurn::right;
        moveDirection(turn, dt);
    }
    else if (posOnScreen.x > targetPos.x + TARGET_OFFSET) {
        turn = BotTurn::left;
        moveDirection(turn, dt);
    }
    else {
        // Path point
        if (grid[posInGrid.y][posInGrid.x].getType() == Tiles::no_tile)
        {   path.pop_back(); }
        else  { // Idle
            isMove = false;
            onTheDestProceed(dt, grid[posInGrid.y][posInGrid.x].getType());
        }
    }
    
    // Change texture only when move state change
    if (lastStateMove != isMove){
        if (isMove) sprite.setTexture(AssetsManager::loadTexture(BOT_TEXTURE_MOVE_BASE + std::to_string(textureNum) + ".png"));
        else sprite.setTexture(AssetsManager::loadTexture(BOT_TEXTURE_IDLE_BASE + std::to_string(textureNum) + ".png"));
        lastStateMove = isMove;    
    }
    sprite.setTextureRect(sf::IntRect(col, (int)turn * BOT_SIZE, BOT_SIZE, BOT_SIZE));
}

void Bot::moveDirection(BotTurn turn, float dt) {
    switch (turn) {
    case BotTurn::down:
        sprite.move(sf::Vector2f(0.f, 1.f) * movementSpeed * dt);
        break;
    case BotTurn::up:
        sprite.move(sf::Vector2f(0.f, -1.f) * movementSpeed * dt);
        break;
    case BotTurn::left:
        sprite.move(sf::Vector2f(-1.f, 0.f) * movementSpeed * dt);
        break;
    case BotTurn::right:
        sprite.move(sf::Vector2f(1.f, 0.f) * movementSpeed * dt);
        break;
    }
}

void Bot::onTheDestProceed(float dt, Tiles purpose) {
    if (purpose == Tiles::no_tile) {
        path.pop_back();
        return;
    }
    // Bot return to spawn -> change state
    else if (purpose == Tiles::spawn) {
        state = BotState::leaved;
        return;
    }
    // Else calculate time on target
    timeOnTarget += dt;

    // Bot do smthng on the tile
    if (timeOnTarget >= serveTime) {
        timeOnTarget = 0.f;
        orders.pop_back();
        path.clear();
        switch (purpose) {
        case Tiles::buy:
            state = BotState::pay;
            break;
        default:
            money += ((int)purpose + 1) * 4;
        }
    }
    waitBar.setSize({timeOnTarget * BOT_WAIT_BAR_WIDTH_COEF, BOT_WAIT_BAR_HEIGHT});
}

void Bot::setPosition(sf::Vector2f pos) {
    sprite.setPosition(pos);
    waitBar.setPosition(pos);
}

int Bot::pay() {
    if (state != BotState::pay) return 0;
    state = BotState::alive;
    return money;
}

bool Bot::isLeaved() {
    if (state != BotState::leaved) return false;
    state = BotState::alive;
    return true;
}

sf::Vector2f Bot::getPosition() {
    return sprite.getPosition();
}