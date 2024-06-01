#include "loaders/AssetsManager.hpp"


AssetsManager& AssetsManager::getInstance() {
    static AssetsManager instance = AssetsManager(); 
    return instance;
}

sf::Texture& AssetsManager::loadTexture(std::string filename) {
    if (dict.find(filename) != dict.end()) return dict[filename];
    sf::Texture texture;
    texture.loadFromFile(filename);
    return dict[filename] = texture;
}