/*
*   Class inhereted Drawable interface
*   Funcs: Game field  
*/
#pragma once
#include "dep.hpp"
#include "gameLogick/Screen.hpp"
#include "gameLogick/Bot.hpp"
#include "gameLogick/Tile.hpp"
#include "loaders/AssetsManager.hpp"

class GameField : public sf::Drawable {
    inline static sf::Sprite shopBG;

    // buy and food tiles
    inline static std::vector<Tile> actionTiles;
    inline static std::vector<Tile> spawnTiles;
    inline static std::vector<Tile> obstackles;

    inline static std::vector<Bot> bots;
    inline static sf::Vector2f originalPos;
    
    inline static float botSpawnTime = 10.f;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    void createTiles();
    static void spawnBot();

    GameField();
    GameField( const GameField& );  
    GameField& operator=( GameField& );
public:
    static GameField& getInstance();

    static void update(float dt);
    static void restart();
    
    static void setPosition(sf::Vector2f pos);
    static void setBotSpawnTime(float time);
};