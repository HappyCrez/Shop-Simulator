#include "gameLogick/StartScreen.hpp"

StartScreen::StartScreen(sf::RenderWindow& wnd, Screens& screenState) : wnd(wnd), screenState(screenState) {
    sf::Vector2f wndSize = sf::Vector2f(wnd.getSize());
    background = sf::RectangleShape(wndSize);
    background.setTexture(&AssetsManager::loadTexture(START_SCREEN_BACKGROUND));
    
    btnBG = sf::Color(51,51,51,229);        // deep-gray with 0.9 transparency
    hoverBG = sf::Color(51,51,51,255);      // deep-gray no transparency
    outlineColor = sf::Color(255, 255, 255);// white
    
    btns.resize((int)Btns::size);
    btns[(int)Btns::loadSave]    = createButton({250, 660}, "Load Game");
    btns[(int)Btns::startGame]   = createButton({400, 400}, "Start new\nsimulation");
    btns[(int)Btns::settings]    = createButton({400, 100}, "Settings");
    btns[(int)Btns::exit]        = createButton({400, 100}, "Exit");
    
    resize(wndSize);
}

Button StartScreen::createButton(sf::Vector2f size, std::string label) {
    Button btn(size, {0, 0}, btnBG);
    btn.setLabel(AssetsManager::loadFont(ROBOTO_BOLD_FONT), label, sf::Color::White, 22, ALIGN_CENTER, sf::Text::Style::Regular);
    btn.setOutline(outlineSize, outlineColor);
    return btn;
}

void StartScreen::render(sf::Event& event) {
    sf::Vector2i mouseCoord;
    switch (event.type) {
    case sf::Event::MouseMoved:
        mouseCoord = {event.mouseMove.x, event.mouseMove.y};
        for (Button& btn : btns) {
            if (btn.isInBounds(mouseCoord)) { onHover(btn); }
            else dropHover(btn);
        }
        break;
    case sf::Event::MouseButtonPressed:
        mouseCoord = {event.mouseButton.x, event.mouseButton.y};
        if      (btns[(int)Btns::loadSave].isInBounds(mouseCoord))   { screenState = Screens::load_save; }
        else if (btns[(int)Btns::settings].isInBounds(mouseCoord))   { screenState = Screens::settings; }
        else if (btns[(int)Btns::startGame].isInBounds(mouseCoord))  { screenState = Screens::game; }
        else if (btns[(int)Btns::exit].isInBounds(mouseCoord))       { wnd.close(); }
        break;
    }
}

void StartScreen::draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const {
    target.draw(background);
    for (int i = 0; i < btns.size(); i++)
        target.draw(btns[i]);
}

void StartScreen::dropHover(Button& btn) {
    btn.setBGColor(btnBG);
    btn.setOutline(outlineSize, outlineColor);
}

void StartScreen::onHover(Button& btn) {
    btn.setBGColor(hoverBG);
    btn.setOutline(outlineHoverSize, outlineColor);
}

void StartScreen::resize(sf::Vector2f& wndSize) {
    // TODO::Resize logick
    sf::Vector2f rightTopBound = {wndSize.x - btns[(int)Btns::startGame].getSize().x - 100.f, 100.f};
    static int spaceBeetwenBtns = 30;
    btns[(int)Btns::loadSave].setPosition({
        rightTopBound.x - btns[(int)Btns::loadSave].getSize().x - spaceBeetwenBtns,
        rightTopBound.y
        });
    btns[(int)Btns::startGame].setPosition(rightTopBound);
    btns[(int)Btns::settings].setPosition({
        btns[(int)Btns::startGame].getPosition().x,
        btns[(int)Btns::startGame].getPosition().y + + btns[(int)Btns::startGame].getSize().y + spaceBeetwenBtns
        });
    btns[(int)Btns::exit].setPosition({
        btns[(int)Btns::settings].getPosition().x,
        btns[(int)Btns::settings].getPosition().y + btns[(int)Btns::settings].getSize().y + spaceBeetwenBtns
        });
}