/*
*   Class inhereted Drawable
*   Funcs: Create bot with simple AI and orders queue
*/
#pragma once
#include "dep.hpp"
#include "gameLogick/Tile.hpp"
#include "loaders/AssetsManager.hpp"

class Bot : public sf::Drawable {
    float movementSpeed;
    float waitSpeed;
    int textureNum;

    bool Die = false;
    bool lastStateMove = false;
    BotTurn turn = BotTurn::up;
    float frameTime = 0.f;
    float timeOnTarget = 0.f;

    float frameSpeed = 6.f;
    sf::Sprite sprite;
    sf::RectangleShape waitBar;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    std::map<Tiles, sf::Vector2f> ordersInfo;
    std::vector<Tiles> orders;

public:
    Bot(int textureNum, int ordersCnt, float movementSpeed);
    Bot(sf::Vector2f pos, int textureNum, int ordersCnt, float movementSpeed);
    
    void update(float dt, std::vector<Tile>& actionTiles, std::vector<Tile>& obstackles);
    void fillOrderQueue(int ordersCnt);
    
    void onTheDestProceed(float dt, Tiles purpose);
    void moveToTarget(float dt, sf::Vector2f& target, Tiles purpose);
    sf::Vector2f getTarget(Tiles tile, std::vector<Tile>& actionTiles, std::vector<Tile>& obstackles);

    void setPosition(sf::Vector2f pos);
    
    bool isDied();
};