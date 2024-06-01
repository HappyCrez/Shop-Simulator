/*
*   Singleton class
*   Funcs: loads and store textures in dict by they filename
*/
#pragma once
#include "dep.hpp"

class AssetsManager {
    std::map<std::string, sf::Texture> dict;

    AssetsManager() { /* Singleton */ }
public:
    static AssetsManager& getInstance();
    sf::Texture& loadTexture(std::string filename);

};