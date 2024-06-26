#include "dep.hpp"
#include "loaders/AssetsManager.hpp"
#include "gameLogick/Screen.hpp"
#include "gameLogick/StartScreen.hpp"
#include "gameLogick/GameScreen.hpp"
#include "gameLogick/SettingsScreen.hpp"

void loadAllReferences() {
    AssetsManager::loadTexture(START_SCREEN_BACKGROUND);
    AssetsManager::loadFont(BLAZMA_FONT);
    AssetsManager::loadTexture(GAME_FIELD_BACKGROUND);
    for (int textureNum = 1; textureNum <= BOT_TEXTURES_CNT; textureNum++) {
        AssetsManager::loadTexture(BOT_TEXTURE_MOVE_BASE + std::to_string(textureNum) + ".png");
        AssetsManager::loadTexture(BOT_TEXTURE_IDLE_BASE + std::to_string(textureNum) + ".png");
    }

    // Background music
    sf::Sound& sound = AssetsManager::loadSound(MUSIC_ABSTRACT);
    sound.setLoop(true);
    sound.setVolume(50.f);
    sound.play();

    // Singleton with deffered initialization,
    // so first configuration should be in launcher
    GameField::getInstance();
    ControlPanel::getInstance();
}

std::vector<Screen*> GameScreens((int)Screens::size);

int main() {
    sf::RenderWindow wnd(sf::VideoMode(), "Shop simulator", sf::Style::Fullscreen);
    sf::Vector2f wndSize = sf::Vector2f(wnd.getSize());
    wnd.setVerticalSyncEnabled(true);
    
    loadAllReferences();

    sf::Clock deltaClock;
    srand(static_cast<unsigned int>(time(0)));  // set rand seed

    Screens screenState = Screens::start;
    StartScreen startScreen(wnd, screenState);
    GameScreen gameScreen(wnd, screenState);
    SettingsScreen settingsScreen(wnd, screenState);
    
    GameScreens[(int)Screens::start]    = &startScreen;
    GameScreens[(int)Screens::game]     = &gameScreen;
    GameScreens[(int)Screens::settings] = &settingsScreen;
    
    while (wnd.isOpen()) {
        sf::Event event;
        while (wnd.pollEvent(event)) {
            // In depend of what screen now is renders
            // we render it and send it events
            GameScreens[(int)screenState]->render(event);
            
            // TODO::Controll function/class
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Escape)
                    screenState = Screens::start;

            if (event.type == sf::Event::Closed)
                wnd.close();
        }
        wnd.clear(sf::Color::Black);
        // The same thing as render is draw
        // It depends of what screen is now showing
        wnd.draw(*GameScreens[(int)screenState]);
        wnd.display();

        // Get delta time - time beetwen frames
        // Update game screen only when game is shows
        float dt = deltaClock.restart().asSeconds();
        if (screenState == Screens::game)
            gameScreen.update(dt);
    }
    return 0;
}