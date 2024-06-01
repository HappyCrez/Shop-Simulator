#include "dep.hpp"
#include "loaders/AssetsManager.hpp"
#include "gameLogick/StartScreen.hpp"

void loadAllReferences() {
    AssetsManager manager = AssetsManager::getInstance();
    // manager.loadTexture("image.png");
}

int main() {
    sf::RenderWindow wnd(sf::VideoMode(640, 480), "Shop simulator");
    
    loadAllReferences();

    sf::Vector2f wndSize = sf::Vector2f(wnd.getSize());
    StartScreen startScreen(wndSize);

    while (wnd.isOpen()) {
        sf::Event event;
        while (wnd.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                wnd.close();
        }
        wnd.clear(sf::Color::Black);
        wnd.draw(startScreen);
        wnd.display();
    }
    return 0;
}