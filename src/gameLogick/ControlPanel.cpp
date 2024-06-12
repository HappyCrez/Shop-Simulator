#include "gameLogick/ControlPanel.hpp"

ControlPanel::ControlPanel() {
    bg.setFillColor(sf::Color(39,39,39));
    bg.setSize({860, 800});
    bg.setPosition({WORLD_X + WORLD_WIDTH*TILE_SIZE, WORLD_Y});

    createText(moneyLabel, {200.f, 50.f}, "Shop income: " + std::to_string(lastIncomeVal));
    createText(timeSpeedLabel, {200.f, 120.f}, "Time speed");

    gameSpeedState = GameSpeed::slow;
    GameField::setTimeSpeed(gameSpeedState);
    timeline = ScrollBar(
        bg.getPosition() + sf::Vector2f(200.f, 170.f), {200.f, 20.f}, (int)GameSpeed::size, (int)gameSpeedState,
        sf::Color::Transparent, sf::Color::White, 1, sf::Color::White, sf::Color::White
        );


    btnBG = sf::Color(120, 120, 120);
    btnHoverBG = sf::Color(130, 130, 130);
    outlineColor = sf::Color(255, 255, 255);

}

Button ControlPanel::createButton(sf::Vector2f position, std::string label) {
    Button btn({110, 35}, position, btnBG);
    btn.setLabel(AssetsManager::loadFont(BLAZMA_FONT), label, sf::Color::White, 24, Align::center, sf::Text::Style::Regular);
    btn.setOutline(outlineSize, outlineColor);
    return btn;
}

void ControlPanel::createText(sf::Text& text, sf::Vector2f position, std::string label) {
    text.setPosition(bg.getPosition() + position);
    text.setFont(AssetsManager::loadFont(BLAZMA_FONT));
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(24);
    text.setString(label);
}

void ControlPanel::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(bg);
    target.draw(moneyLabel);
    target.draw(timeSpeedLabel);
    target.draw(timeline);
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

    timeline.update(event);
    GameSpeed state = (GameSpeed)timeline.getStep();
    if (state != gameSpeedState) {
        gameSpeedState = state;
        GameField::setTimeSpeed(state);
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