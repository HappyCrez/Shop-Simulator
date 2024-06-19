
/*
*   Singleton Class inhereted Drawable 
*   Funcs: Controls on simulation, buttons, bars, etc.
*/
#pragma once
#include "dep.hpp"
#include "gameLogick/GameField.hpp"
#include "loaders/AssetsManager.hpp"
#include "UI/ScrollBar.hpp"
#include "UI/Button.hpp"

enum class LabelType {
    day_count, day_time,
    income, clients, discont,
    clients_max_count, clients_serve_time, clients_spawn_time,
    time_speed, size
    };

enum class ScrollBarType {
    timeSpeed, discont,
    maxClients, clientServeTime, clientSpawnTime, size
    };

struct Label {
    sf::Text text;
    std::string before;
    std::string after;
    int prevValue;
};

class ControlPanel : public sf::Drawable {
    inline static sf::RectangleShape background {{860.f, 1080.f}};
    inline static std::vector<Label> labels;
    inline static std::vector<ScrollBar> scrollBars;
    inline static bool isVisible;
    inline static sf::Vector2f panelSize;

    inline static float timeNow = 0.f;
    inline static int dayCount = 0;
    
    inline static int discontStepVal = 4;
    inline static int maxClientsStepVal = 2;
    inline static int minClientsCount = 2;
    inline static int minServeTime = 1;
    inline static int minSpawnTime = 1;
    inline static GameSpeed gameSpeedState = GameSpeed::slow;

    inline static Button collapse;
    inline static Button dayDialog;
    inline static bool dayDialogVisible;

    inline static sf::Color btnBG;
    inline static sf::Color btnHoverBG;
    inline static sf::Color outlineColor;
    inline static float outlineSize = 1.f;
    inline static float outlineHoverSize = 2.f;

    // Texts funcs
    static sf::Text createText(sf::Vector2f position);
    
    // Texts update ever game day
    static void updateTimeText(float time);
    static void newDay();

    // Buttons Funcs
    static Button createButton();
    static void updateCollapseButton();
    static void onHover(Button& btn);
    static void dropHover(Button& btn);
    static void dayDialogTransparency(float time);
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    static void showPanel();
    static void hidePanel();

    ControlPanel();
    ControlPanel( const ControlPanel& );  
    ControlPanel& operator=( ControlPanel& );
public:
    static ControlPanel& getInstance();

    static void initialize(sf::Vector2f wndSize);

    static void render(sf::Event& event);
    static void update(float dt);
    static void restartGame();
};