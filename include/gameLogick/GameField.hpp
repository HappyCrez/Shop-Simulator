/*
*   Class inhereted Drawable interface
*   Funcs: Game field  
*/
#pragma once
#include "dep.hpp"
#include "gameLogick/Screen.hpp"
#include "loaders/AssetsManager.hpp"
#include "gameLogick/Tile.hpp"

class GameField : public sf::Drawable {
    inline static sf::Sprite shopBG;
    inline static std::vector<Tile> tiles;
    inline static sf::Vector2f botSpawnPos;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    GameField();
    GameField( const GameField& );  
    GameField& operator=( GameField& );
public:
    static GameField& getInstance();

    static sf::Vector2f getBotSpawnPos();
    static void setPosition(sf::Vector2f pos);
};