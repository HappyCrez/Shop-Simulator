#include "gameLogick/ControlPanel.hpp"

ControlPanel::ControlPanel() {
    bg.setFillColor(sf::Color(39,39,39));
    bg.setSize({860, 800});
    bg.setPosition({WORLD_X + WORLD_WIDTH*TILE_SIZE, WORLD_Y});

    moneyLabel.setPosition(bg.getPosition() + sf::Vector2f(200.f, 50.f));
    moneyLabel.setCharacterSize(24);
    moneyLabel.setFont(AssetsManager::loadFont(BLAZMA_FONT));
    moneyLabel.setFillColor(sf::Color::White);
    moneyLabel.setString("Shop income: " + std::to_string(lastIncomeVal));

    btnBG = sf::Color(120, 120, 120);
    btnHoverBG = sf::Color(130, 130, 130);
    outlineColor = sf::Color(255, 255, 255);

    btnsPlay.resize((int)BtnsPlay::size);
    btnsPlay[(int)BtnsPlay::pause  ] = createButton(bg.getPosition() + sf::Vector2f(200, 100), "stop");
    btnsPlay[(int)BtnsPlay::play   ] = createButton(bg.getPosition() + sf::Vector2f(400, 100), "play");
    btnsPlay[(int)BtnsPlay::speedUp] = createButton(bg.getPosition() + sf::Vector2f(600, 100), "speed up");
}

Button ControlPanel::createButton(sf::Vector2f pos, std::string label) {
    Button btn({110, 35}, pos, btnBG);
    btn.setLabel(AssetsManager::loadFont(BLAZMA_FONT), label, sf::Color::White, 24, Align::center, sf::Text::Style::Regular);
    btn.setOutline(outlineSize, outlineColor);
    return btn;
}

void ControlPanel::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(bg);
    target.draw(moneyLabel);
    for (int i = 0; i < btnsPlay.size(); i++)
        target.draw(btnsPlay[i]);
}

void ControlPanel::update() {
    updateIncomeLabel();

}

void ControlPanel::updateIncomeLabel() {
    if (lastIncomeVal == GameField::getIncome()) return;
    lastIncomeVal = GameField::getIncome();
    moneyLabel.setString("Shop income: " + std::to_string(lastIncomeVal));
}

void ControlPanel::render(sf::Event& event) {
    sf::Vector2i mouseCoord;
    switch (event.type) {
    case sf::Event::MouseMoved:
        mouseCoord = {event.mouseMove.x, event.mouseMove.y};
        for (Button& btn : btnsPlay) {
            if (btn.isInBounds(mouseCoord)) { onHover(btn); }
            else dropHover(btn);
        }
        break;
    case sf::Event::MouseButtonPressed:
        mouseCoord = {event.mouseButton.x, event.mouseButton.y};
        if      (btnsPlay[(int)BtnsPlay::pause  ].isInBounds(mouseCoord)) { GameField::setTimeSpeed(0.f); }
        else if (btnsPlay[(int)BtnsPlay::play   ].isInBounds(mouseCoord)) { GameField::setTimeSpeed(1.f); }
        else if (btnsPlay[(int)BtnsPlay::speedUp].isInBounds(mouseCoord)) { GameField::setTimeSpeed(3.f); }
        break;
    }
}

void ControlPanel::onHover(Button& btn) {
    btn.setBGColor(btnHoverBG);
    btn.setOutline(outlineHoverSize, outlineColor);
}

void ControlPanel::dropHover(Button& btn) {
    btn.setBGColor(btnBG);
    btn.setOutline(outlineSize, outlineColor);
}