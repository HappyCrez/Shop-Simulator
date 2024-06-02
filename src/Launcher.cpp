#include "dep.hpp"
#include "Renderable.hpp"
#include "loaders/AssetsManager.hpp"
#include "gameLogick/StartScreen.hpp"

void loadAllReferences() {
    AssetsManager::loadTexture(START_SCREEN_BACKGROUND);
    AssetsManager::loadFont(MONTSERRAT_FONT);
}

std::vector<Renderable*> GameScreens(SCREENS_COUNT);

int main() {
    sf::RenderWindow wnd(sf::VideoMode(), "Shop simulator", sf::Style::Fullscreen);
    wnd.setVerticalSyncEnabled(true);
    
    loadAllReferences();

    int screenState = SCREEN_START_MENU;
    sf::Vector2f wndSize = sf::Vector2f(wnd.getSize());
    StartScreen startScreen(wnd, screenState);
    GameScreens[SCREEN_START_MENU] = &startScreen;
    
    while (wnd.isOpen()) {
        sf::Event event;
        while (wnd.pollEvent(event)) {
            // In depend of what screen now is renders
            // we render it and send it events
            GameScreens[screenState]->render(event);
            if (screenState != SCREEN_START_MENU) screenState = SCREEN_START_MENU;
            
            if (event.type == sf::Event::Closed)
                wnd.close();
        }
        wnd.clear(sf::Color::Black);
        // The same thing as render is draw
        // It depends of what screen is now showing
        wnd.draw(*GameScreens[screenState]);
        wnd.display();
    }
    return 0;
}