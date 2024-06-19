/*
*   Class inhereted Drawable interface
*   Funcs: Settings wnd to control sounds  
*/
#pragma once
#include "dep.hpp"
#include "gameLogick/Screen.hpp"
#include "loaders/AssetsManager.hpp"
#include "UI/Button.hpp"
#include "UI/ScrollBar.hpp"

class SettingsScreen : public Screen {
    sf::RectangleShape background;

    Button backToMenu;
    sf::Color btnBG;
    sf::Color hoverBG;
    sf::Color outlineColor;
    float outlineSize = 1.f;
    float outlineHoverSize = 2.f;

    sf::Text soundLabel;
    ScrollBar soundVolume;
    float curSoundVolume = -1.f;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void render(sf::Event& event);

    void resize(sf::Vector2f wndSize);

    void onHover(Button& btn);
    void dropHover(Button& btn);

public:
    SettingsScreen(sf::RenderWindow &wnd, Screens& screenState);

    void update(float dt);
};