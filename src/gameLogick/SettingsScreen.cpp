#include "gameLogick/SettingsScreen.hpp"

SettingsScreen::SettingsScreen(sf::RenderWindow &wnd, Screens& screenState) : Screen(wnd, screenState) {
    sf::Vector2f wndSize = sf::Vector2f(wnd.getSize());
    
    background = sf::RectangleShape(wndSize);
    background.setFillColor(sf::Color(68,89,93)); // dark blue

    sf::Vector2f center = sf::Vector2f(wnd.getSize()) / 2.f;
    
    btnBG = sf::Color(51,51,51,229);        // deep-gray with 0.9 transparency
    hoverBG = sf::Color(51,51,51,255);      // deep-gray no transparency
    outlineColor = sf::Color(255, 255, 255);// white
    
    sf::Vector2f backToMenuSize = {300.f, 60.f};
    backToMenu = Button(backToMenuSize, {center.x - backToMenuSize.x/2.f, center.y + 60.f}, btnBG);
    backToMenu.setLabel(AssetsManager::loadFont(BLAZMA_FONT), "Back to menu", sf::Color::White, 24, Align::center, sf::Text::Style::Regular);
    backToMenu.setOutline(outlineSize, outlineColor);

    sf::Vector2f scrollBarSize = {500.f, 30.f};
    soundLabel.setString("Sound volume");
    soundLabel.setFillColor(sf::Color::White);
    soundLabel.setCharacterSize(24);
    soundLabel.setFont(AssetsManager::loadFont(BLAZMA_FONT));
    soundLabel.setPosition({center.x - scrollBarSize.x/2.f, center.y - 60.f});
    soundVolume = ScrollBar({center.x - scrollBarSize.x/2.f + 10.f, center.y}, scrollBarSize, 101, 51, sf::Color::Transparent, sf::Color::Black,
        1, sf::Color::White, sf::Color::Transparent);
    
    resize(wndSize);
}

void SettingsScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background);
    target.draw(soundLabel);
    target.draw(soundVolume);
    target.draw(backToMenu);
}

void SettingsScreen::update(float dt) {
    
}

void SettingsScreen::render(sf::Event& event) {
    sf::Vector2i mouseCoord;
    switch(event.type) {
    case sf::Event::MouseMoved:
        mouseCoord = {event.mouseMove.x, event.mouseMove.y};
        if (backToMenu.isInBounds(mouseCoord))
            onHover(backToMenu);
        else dropHover(backToMenu);
        break;
    case sf::Event::MouseButtonPressed:
        mouseCoord = {event.mouseButton.x, event.mouseButton.y};
        if (backToMenu.isInBounds(mouseCoord))
            screenState = Screens::start;
        break;
    }

    soundVolume.update(event);
    if (curSoundVolume != soundVolume.getStep()) {
        curSoundVolume = static_cast<float>(soundVolume.getStep());
        AssetsManager::loadSound(MUSIC_ABSTRACT).setVolume(curSoundVolume);
    }
}

void SettingsScreen::dropHover(Button& btn) {
    btn.setBGColor(btnBG);
    btn.setOutline(outlineSize, outlineColor);
}

void SettingsScreen::onHover(Button& btn) {
    btn.setBGColor(hoverBG);
    btn.setOutline(outlineHoverSize, outlineColor);
}

void SettingsScreen::resize(sf::Vector2f wndSize) {
    
}