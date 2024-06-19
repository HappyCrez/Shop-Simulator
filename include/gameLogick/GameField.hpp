/*
*   Class inhereted Drawable interface
*   Funcs: Game field  
*/
#pragma once
#include "dep.hpp"
#include "gameLogick/Bot.hpp"
#include "gameLogick/Tile.hpp"
#include "loaders/AssetsManager.hpp"

class GameField : public sf::Drawable {
    inline static int income = 0;
    inline static int visits = 0;

    inline static float timeSpeed = 1.f;
    inline static float discont = 0.f;
    inline static int maxClients = 10; 
    inline static float clientSpawnTime = 10.f;
    inline static float serveTime = 10.f;

    inline static sf::Sprite shopBG;
    inline static std::vector<std::vector<Tile>> grid = std::vector(WORLD_HEIGHT, std::vector<Tile>(WORLD_WIDTH));
    inline static std::vector<Tile> spawnTiles;

    inline static std::vector<Bot> bots;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    void createTiles();
    static void spawnClient();

    GameField();
    GameField( const GameField& );  
    GameField& operator=( GameField& );
public:
    static GameField& getInstance();

    static void update(float dt);
    static void restartDay();
    static void dropValues();
    
    static void setPosition(sf::Vector2f position);
    static void setClientSpawnTime(float clientSpawnTime);
    static void setServeTime(float serveTime);
    static void setTimeSpeed(GameSpeed state);
    static void setDiscont(float discont);
    static void setMaxClients(int maxClients);

    static int getClientsCount();
    static int getIncome();
    static float getDiscont();
    static int getMaxClients();
    static float getClientSpawnTime();
    static float getServeTime();
};