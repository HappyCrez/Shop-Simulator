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
    int money;
    BotState state;

    bool leaveStatus = false;
    bool lastStateMove = false;
    BotTurn turn = BotTurn::up;
    float frameTime = 0.f;
    float timeOnTarget = 0.f;
    float frameSpeed = 6.f;
    
    sf::Sprite sprite;
    sf::Vector2i posInGrid;
    sf::Vector2f posOnScreen;
    sf::RectangleShape waitBar;
    std::vector<Tiles> orders;
    std::vector<sf::Vector2i> path;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void fillOrderQueue(int ordersCnt);
    
    sf::Vector2i getNextTarget(std::vector<std::vector<Tile>>& grid, Tiles& purpose);
    void generatePathToTarget(sf::Vector2i& target, std::vector<std::vector<Tile>>& grid, Tiles& purpose);
    void moveToTarget(float dt, sf::Vector2i& target, std::vector<std::vector<Tile>>& grid);
    void onTheDestProceed(float dt, Tiles purpose);
    void moveDirection(BotTurn turn, float dt);

public:
    Bot(int textureNum, int ordersCnt, float movementSpeed);
    Bot(sf::Vector2i pos, int textureNum, int ordersCnt, float movementSpeed);
    
    void update(float dt, std::vector<std::vector<Tile>>& grid);

    void setPosition(sf::Vector2f pos);
    
    int pay();
    bool isLeaved();
};