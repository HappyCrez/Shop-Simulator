#include "dep.hpp"
#include "Renderable.hpp"
#include "loaders/AssetsManager.hpp"
#include "gameLogick/StartScreen.hpp"

void loadAllReferences() {
    AssetsManager::loadTexture(START_SCREEN_BACKGROUND);
    AssetsManager::loadFont(MONTSERRAT_FONT);
}

std::vector<Renderable*> GameScreens((int)Screens::size);

int main() {
    sf::RenderWindow wnd(sf::VideoMode(), "Shop simulator", sf::Style::Fullscreen);
    wnd.setVerticalSyncEnabled(true);
    
    loadAllReferences();

    sf::Vector2f wndSize = sf::Vector2f(wnd.getSize());
    Screens screenState = Screens::start;
    StartScreen startScreen(wnd, screenState);
    GameScreens[(int)Screens::start] = &startScreen;
    
    while (wnd.isOpen()) {
        sf::Event event;
        while (wnd.pollEvent(event)) {
            // In depend of what screen now is renders
            // we render it and send it events
            GameScreens[(int)screenState]->render(event);
            if (screenState != Screens::start) screenState = Screens::start;
            
            if (event.type == sf::Event::Closed)
                wnd.close();
        }
        wnd.clear(sf::Color::Black);
        // The same thing as render is draw
        // It depends of what screen is now showing
        wnd.draw(*GameScreens[(int)screenState]);
        wnd.display();
    }
    return 0;
}