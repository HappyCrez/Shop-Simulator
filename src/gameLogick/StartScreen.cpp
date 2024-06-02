#include "gameLogick/StartScreen.hpp"

StartScreen::StartScreen(sf::RenderWindow& wnd, int& screenState) : wnd(wnd), screenState(screenState) {
    sf::Vector2f wndSize = sf::Vector2f(wnd.getSize());
    background = sf::RectangleShape(wndSize);
    background.setTexture(&AssetsManager::loadTexture(START_SCREEN_BACKGROUND));
    
    btnBG = sf::Color(51,51,51,229);
    hoverBG = sf::Color(51,51,51,255);
    outlineColor = sf::Color(255, 255, 255);

    load = Button({250, 660}, {0, 0}, btnBG);
    load.setLabel(AssetsManager::loadFont(ROBOTO_FONT), "Load Game", sf::Color::White, 22, ALIGN_CENTER, sf::Text::Style::Regular);
    load.setOutline(outlineSize, outlineColor);

    startGame = Button({400, 400}, {0, 0}, btnBG);
    startGame.setLabel(AssetsManager::loadFont(ROBOTO_FONT), "Start new\nsimulation", sf::Color::White, 22, ALIGN_CENTER, sf::Text::Style::Regular);
    startGame.setOutline(outlineSize, outlineColor);
    
    settings = Button({400, 100}, {0, 0}, btnBG);
    settings.setLabel(AssetsManager::loadFont(ROBOTO_FONT), "Settings", sf::Color::White, 22, ALIGN_CENTER, sf::Text::Style::Regular);
    settings.setOutline(outlineSize, outlineColor);
    
    exit = Button({400, 100}, {0, 0}, btnBG);
    exit.setLabel(AssetsManager::loadFont(ROBOTO_FONT), "Exit", sf::Color::White, 22, ALIGN_CENTER, sf::Text::Style::Regular);
    exit.setOutline(outlineSize, outlineColor);
    
    resize(wndSize);
}

void StartScreen::render(sf::Event& event) {
    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2i mouseCoord = {event.mouseMove.x, event.mouseMove.y};
        if (settings.isInBounds(mouseCoord)) { onHover(settings); }
        else dropHover(settings);
        if (startGame.isInBounds(mouseCoord)) { onHover(startGame); }
        else dropHover(startGame);
        if (load.isInBounds(mouseCoord)) { onHover(load); }
        else dropHover(load);
        if (exit.isInBounds(mouseCoord)) { onHover(exit); }
        else dropHover(exit);
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mouseCoord = {event.mouseButton.x, event.mouseButton.y};
        if (settings.isInBounds(mouseCoord))    { screenState = SCREEN_SETTINGS; }
        else if (load.isInBounds(mouseCoord))   { screenState = SCREEN_LOAD_SAVE; }
        else if (startGame.isInBounds(mouseCoord)){ screenState = SCREEN_GAME; }
        else if (exit.isInBounds(mouseCoord))   { wnd.close(); }
    }
}

void StartScreen::dropHover(Button& btn) {
    btn.setBGColor(btnBG);
    btn.setOutline(outlineSize, outlineColor);
}

void StartScreen::onHover(Button& btn) {
    btn.setBGColor(hoverBG);
    btn.setOutline(outlineHoverSize, outlineColor);
}

void StartScreen::draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const {
    target.draw(background);
    target.draw(load);
    target.draw(startGame);
    target.draw(settings);
    target.draw(exit);
}

void StartScreen::resize(sf::Vector2f& wndSize) {
    // TODO::Resize logick
    sf::Vector2f rightTopBound = {wndSize.x - startGame.getSize().x - 100.f, 100.f};
    startGame.setPosition(rightTopBound);
    settings.setPosition({rightTopBound.x, rightTopBound.y + startGame.getSize().y + 30});
    exit.setPosition({rightTopBound.x, rightTopBound.y + startGame.getSize().y + settings.getSize().y + 30*2});
    load.setPosition({rightTopBound.x - load.getSize().x - 30, rightTopBound.y});
}