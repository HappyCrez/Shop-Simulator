
/*
*   Singleton Class inhereted Drawable 
*   Funcs: Controls on simulation, buttons, bars, etc.
*/
#pragma once
#include "dep.hpp"
#include "gameLogick/GameField.hpp"
#include "UI/Button.hpp"
#include "UI/ScrollBar.hpp"
#include "loaders/AssetsManager.hpp"

class ControlPanel : public sf::Drawable {
    inline static sf::RectangleShape bg {{860, 800}};
    inline static sf::Text timeSpeedLabel;

    inline static sf::Text dayTimeLabel;
    inline static sf::Text dayLabel;
    inline static sf::Text incomeLabel;
    inline static sf::Text discontLabel;
    inline static int curIncomeVal = 0;
    inline static float curDiscontVal = 0.f;
    inline static int discontStep = 4;
    
    inline static sf::Text dayStatsLabel;
    inline static sf::Text lastIncomeLabel;
    inline static sf::Text lastDiscontLabel;
    inline static int lastIncomeVal = 0;
    inline static float lastDiscontVal = 0.f;
    
    inline static ScrollBar timeSpeedBar;
    inline static ScrollBar discontBar;
    inline static GameSpeed gameSpeedState;
    

    inline static float timeNow = 0.f;
    inline static int dayCount;

    inline static sf::Color btnBG;
    inline static sf::Color btnHoverBG;
    inline static sf::Color outlineColor;
    inline static int outlineSize = 1;
    inline static int outlineHoverSize = 2;

    static void updateIncomeLabel();
    static void updateDiscontLabel();
    static void updateDayTimeLabel(float time);
    static void newDay();

    static Button createButton(sf::Vector2f position, std::string label);
    static void createText(sf::Text& text, sf::Vector2f position, std::string label);
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    static void onHover(Button& btn);
    static void dropHover(Button& btn);

    ControlPanel();
    ControlPanel( const ControlPanel& );  
    ControlPanel& operator=( ControlPanel& );
public:
    static ControlPanel& getInstance();

    static void render(sf::Event& event);
    static void update(float dt);
    static void restartGame();
};