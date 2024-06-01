#include "loaders/AssetsManager.hpp"


AssetsManager& AssetsManager::getInstance() {
    static AssetsManager instance = AssetsManager(); 
    return instance;
}

sf::Texture& AssetsManager::loadTexture(std::string filename) {
    if (textureFiles.find(filename) != textureFiles.end()) return textureFiles[filename];
    sf::Texture texture;
    texture.loadFromFile(filename);
    return textureFiles[filename] = texture;
}

sf::Font& AssetsManager::loadFont(std::string filename) {
    if (fontFiles.find(filename) != fontFiles.end()) return fontFiles[filename];
    sf::Font font;
    font.loadFromFile(filename);
    return fontFiles[filename] = font;
}