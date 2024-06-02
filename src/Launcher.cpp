#include "dep.hpp"
#include "loaders/AssetsManager.hpp"
#include "gameLogick/StartScreen.hpp"

void loadAllReferences() {
    AssetsManager::loadTexture(START_SCREEN_BACKGROUND);
    AssetsManager::loadFont(MONTSERRAT_FONT);
}

int main() {
    sf::RenderWindow wnd(sf::VideoMode(), "Shop simulator", sf::Style::Fullscreen);
    wnd.setVerticalSyncEnabled(true);
    
    loadAllReferences();

    int screenState = SCREEN_START_MENU;
    sf::Vector2f wndSize = sf::Vector2f(wnd.getSize());
    StartScreen startScreen(wnd, screenState);
    
    while (wnd.isOpen()) {
        sf::Event event;
        while (wnd.pollEvent(event)) {
            // In depend of what screen now is renders
            // we render it and send it events
            switch (screenState) {
                case SCREEN_START_MENU:
                    startScreen.render(event);
                    break;
                case SCREEN_SETTINGS:
                    std::cout << "Settings\n";
                    screenState = SCREEN_START_MENU;
                    break;
                case SCREEN_LOAD_SAVE:
                    std::cout << "SaveLoad\n";
                    screenState = SCREEN_START_MENU;
                    break;
                case SCREEN_GAME:
                    std::cout << "Game\n";
                    screenState = SCREEN_START_MENU;
                    break;
                default: screenState = SCREEN_START_MENU;
            }
            
            if (event.type == sf::Event::Closed)
                wnd.close();
        }
        wnd.clear(sf::Color::Black);
        switch (screenState) {
            case SCREEN_START_MENU:
                wnd.draw(startScreen);
                break;
            case SCREEN_SETTINGS:

                break;
            case SCREEN_LOAD_SAVE:

                break;
            case SCREEN_GAME:

                break;
            default: screenState = SCREEN_START_MENU;
        }
        wnd.display();
    }
    return 0;
}