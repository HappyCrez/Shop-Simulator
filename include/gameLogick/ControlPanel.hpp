
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
    inline static sf::Text timeSpeedText;

    inline static sf::Text dayTimeText;
    inline static sf::Text dayText;

    // Income text
    inline static sf::Text lastIncomeText;
    inline static sf::Text incomeText;
    inline static int lastIncome = 0;
    inline static int todayIncome = 0;
    
    // Discont text
    inline static sf::Text lastDiscontText;
    inline static sf::Text discontText;
    inline static sf::Text nextDayDiscontText;
    inline static float lastDiscont = 0.f;
    inline static float todayDiscont = 0.f;
    inline static float nextDiscont = 0.f;
    inline static int discontStep = 4;
    
    // Visits text
    inline static sf::Text lastVisitsText;
    inline static sf::Text visitsText;
    inline static int lastVisits;
    
    inline static sf::Text dayStatsText;
    
    inline static ScrollBar timeSpeedBar;
    inline static ScrollBar discontBar;
    inline static GameSpeed gameSpeedState;

    inline static float timeNow = 0.f;
    inline static int dayCount = 0;

    inline static sf::Color btnBG;
    inline static sf::Color btnHoverBG;
    inline static sf::Color outlineColor;
    inline static int outlineSize = 1;
    inline static int outlineHoverSize = 2;

    // Texts update every frame
    static void updateIncomeText(int income);
    static void updateVisitsText(int visits);
    static void updateNextDayDiscontText(int discont);
    static void updateDayTimeText(float time);
    
    // Texts update ever game day
    static void updateDiscontText(int discont);
    static void updateLastDiscontText(int discont);
    static void updateLastIncomeText(int income);
    static void updateLastVisitsText(int visits);
    static void updateDayText();
    static void newDay();

    static Button createButton(sf::Vector2f position, std::string str);
    static void createText(sf::Text& text, sf::Vector2f position);
    
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