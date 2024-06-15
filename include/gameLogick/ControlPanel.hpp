
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

enum class Label {
    day_count, day_time, day_stats,
    last_income, today_income,
    last_visits, today_visits,
    last_discont, today_discont, next_discont,
    time_speed, size};

class ControlPanel : public sf::Drawable {
    inline static sf::RectangleShape bg {{860, 1080}};
    inline static std::vector<sf::Text> labels;
    inline static bool isVisible;
    inline static sf::Vector2f panelSize;

    inline static Button collapse;

    // values
    inline static float lastDiscont = 0.f;
    inline static int lastVisits;
    inline static int lastIncome = 0;
    inline static int todayIncome = 0;
    inline static float todayDiscont = 0.f;
    inline static float nextDiscont = 0.f;
    
    inline static float timeNow = 0.f;
    inline static int dayCount = 0;
    
    inline static ScrollBar timeSpeedBar;
    inline static ScrollBar discontBar;
    inline static int discontStep = 4;
    inline static GameSpeed gameSpeedState;

    inline static sf::Color btnBG;
    inline static sf::Color btnHoverBG;
    inline static sf::Color outlineColor;
    inline static int outlineSize = 1;
    inline static int outlineHoverSize = 2;

    // Texts funcs
    static sf::Text createText(sf::Vector2f position);
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

    // Buttons Funcs
    static Button createButton();
    static void updateCollapseButton();
    static void onHover(Button& btn);
    static void dropHover(Button& btn);
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    static void show();
    static void hide();

    ControlPanel();
    ControlPanel( const ControlPanel& );  
    ControlPanel& operator=( ControlPanel& );
public:
    static ControlPanel& getInstance();

    static void setPosition(sf::Vector2f position);
    static void setSize(sf::Vector2f size);

    static void render(sf::Event& event);
    static void update(float dt);
    static void restartGame();
};