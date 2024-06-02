#include "loaders/AssetsManager.hpp"

AssetsManager& AssetsManager::getInstance() {
    static AssetsManager instance = AssetsManager(); 
    return instance;
}

sf::Texture& AssetsManager::loadTexture(std::string filename) {
    auto& textureMap = getInstance().textureFiles;
    if (textureMap.find(filename) != textureMap.end()) return textureMap[filename];
    sf::Texture texture;
    texture.loadFromFile(filename);
    return textureMap[filename] = texture;
}

sf::Font& AssetsManager::loadFont(std::string filename) {
    auto& fontMap = getInstance().fontFiles;
    if (fontMap.find(filename) != fontMap.end()) return fontMap[filename];
    sf::Font font;
    font.loadFromFile(filename);
    return fontMap[filename] = font;
}