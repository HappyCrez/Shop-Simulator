/*
*   Singleton class
*   Funcs: loads and store textures in dict by they filename
*/
#pragma once
#include "dep.hpp"

class AssetsManager {
    std::map<std::string, sf::Texture> textureFiles;
    std::map<std::string, sf::Font> fontFiles;
    std::map<std::string, sf::SoundBuffer> soundBufferFiles;
    std::map<std::string, sf::Sound> soundsFiles;

    AssetsManager() { /* Singleton */ }
    AssetsManager( const AssetsManager& );  
    AssetsManager& operator=( AssetsManager& );
public:
    static AssetsManager& getInstance();
    static sf::Texture& loadTexture(std::string filename);
    static sf::Font&    loadFont(std::string filename);
    static sf::Sound&   loadSound(std::string filename);
    static std::string  loadTextFile(std::string filename);
};