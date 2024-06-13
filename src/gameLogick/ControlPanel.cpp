#include "gameLogick/ControlPanel.hpp"

// Singleton
ControlPanel& ControlPanel::getInstance() {
    static ControlPanel instance;
    return instance;
}

ControlPanel::ControlPanel() {
    bg.setFillColor(sf::Color(39,39,39));
    bg.setSize({860, 800});
    bg.setPosition({WORLD_X + WORLD_WIDTH*TILE_SIZE, WORLD_Y});

    restartGame();

    createText(dayLabel,        {100.f, 20.f},  "Day #: " + std::to_string(dayCount));
    createText(dayTimeLabel,    {400.f, 20.f},  "Time  0h  0m");
    createText(incomeLabel,     {100.f, 60.f},  "Shop income: " + std::to_string(curIncomeVal));
    createText(lastDiscontLabel,{400.f, 60.f},  "Current discont: 0%");
    createText(timeSpeedLabel,  {100.f, 100.f}, "Time speed");
    createText(discontLabel,    {100.f, 200.f}, "Next discont: 0%");

    createText(dayStatsLabel,   {100.f, 400.f}, "PREV DAY STATS");
    createText(lastIncomeLabel, {100.f, 460.f}, "Last day income: 0");

    gameSpeedState = GameSpeed::slow;
    GameField::setTimeSpeed(gameSpeedState);
    timeSpeedBar = ScrollBar(
        bg.getPosition() + sf::Vector2f(110.f, 150.f), {200.f, 20.f}, (int)GameSpeed::size, (int)gameSpeedState,
        sf::Color::Transparent, sf::Color::White, 1, sf::Color::White, sf::Color::White
        );

    float discontVal = 0.f;
    GameField::setDiscont(discontVal);
    discontBar = ScrollBar(
        bg.getPosition() + sf::Vector2f(110.f, 250.f), {500.f, 20.f}, 25, (int)discontVal,
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
    
    // labels
    target.draw(dayLabel);
    target.draw(dayTimeLabel);
    target.draw(incomeLabel);
    target.draw(timeSpeedLabel);
    target.draw(discontLabel);
    target.draw(dayStatsLabel);
    target.draw(lastIncomeLabel);
    target.draw(lastDiscontLabel);

    // scrollbars
    target.draw(timeSpeedBar);
    target.draw(discontBar);
}

void ControlPanel::update(float dt) {
    dt *= (int)gameSpeedState;
    timeNow += dt;
    if (timeNow >= DAY_WORK_TIME) {
        timeNow = 0.f;
        newDay();
    }
    updateIncomeLabel();
    updateDiscontLabel();
    updateDayTimeLabel(timeNow);
}

void ControlPanel::newDay() {
    dayCount++;
    GameField::restartDay();
    GameField::setDiscont(curDiscontVal);
    dayLabel.setString("Day #" + std::to_string(dayCount));
    lastIncomeLabel.setString("Last day income: " + std::to_string(curIncomeVal));
    lastDiscontLabel.setString("Current discont: " + std::to_string(static_cast<int>(curDiscontVal*100)) + "%");
}

void ControlPanel::restartGame() {
    dayCount = 0;
    timeNow = 0.f;
    updateDayTimeLabel(timeNow);
    discontBar.setStep(0); // set bar to zero
    updateDiscontLabel();  // set discont to zero
    GameField::restartDay();
    updateIncomeLabel();
    newDay();
}

void ControlPanel::updateDayTimeLabel(float time) {
    int hours = static_cast<int>(time/60.f) + SHOP_OPEN_TIME;
    int minutes = static_cast<int>(time) % 60;
    std::string hoursStr = hours > 9 ? std::to_string(hours) : "0" + std::to_string(hours);
    std::string minutesStr = minutes > 9 ? std::to_string(minutes) : "0" + std::to_string(minutes);
    dayTimeLabel.setString("Time " + hoursStr + "h " + minutesStr + "m");
}

void ControlPanel::updateDiscontLabel() {
    if (discontBar.getStep()/100.f*discontStep == curDiscontVal) return;
    curDiscontVal = discontBar.getStep()/100.f*discontStep;
    discontLabel.setString("Next discont: " + std::to_string(static_cast<int>(curDiscontVal*100)) + "%");
}

void ControlPanel::updateIncomeLabel() {
    if (curIncomeVal == GameField::getIncome()) return;
    curIncomeVal = GameField::getIncome();
    incomeLabel.setString("Shop income: " + std::to_string(curIncomeVal));
}

void ControlPanel::render(sf::Event& event) {
    sf::Vector2i mouseCoord;

    timeSpeedBar.update(event);
    gameSpeedState = (GameSpeed)timeSpeedBar.getStep();
    GameField::setTimeSpeed(gameSpeedState);

    discontBar.update(event);
}

void ControlPanel::onHover(Button& btn) {
    btn.setBGColor(btnHoverBG);
    btn.setOutline(outlineHoverSize, outlineColor);
}

void ControlPanel::dropHover(Button& btn) {
    btn.setBGColor(btnBG);
    btn.setOutline(outlineSize, outlineColor);
}