#include "gameLogick/Bot.hpp"

Bot::Bot(int textureNum) : Bot({0, 0}, textureNum) { }

Bot::Bot(sf::Vector2f pos, int textureNum) {
    sprite.setPosition(pos);
    sprite.setTexture(AssetsManager::loadTexture(BOT_TEXTURE_BASE + std::to_string(textureNum) + ".png"));
}

void Bot::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite);
}

void Bot::setPosition(sf::Vector2f pos) {
    sprite.setPosition(pos);
}