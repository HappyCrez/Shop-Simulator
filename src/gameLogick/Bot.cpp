#include "gameLogick/Bot.hpp"

Bot::Bot(int textureNum, int ordersCnt) : Bot({0, 0}, textureNum, ordersCnt) { }

Bot::Bot(sf::Vector2f pos, int textureNum, int ordersCnt) {
    sprite.setPosition(pos);
    sprite.setTexture(AssetsManager::loadTexture(BOT_TEXTURE_BASE + std::to_string(textureNum) + ".png"));
    fillOrderQueue(ordersCnt);
}

void Bot::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite);
}

void Bot::setPosition(sf::Vector2f pos) {
    sprite.setPosition(pos);
}

void Bot::update(float dt) {

}

// ordersCnt must be in bounds [0; foodTilesSize] 
void Bot::fillOrderQueue(int ordersCnt) {
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