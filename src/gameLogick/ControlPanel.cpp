#include "gameLogick/ControlPanel.hpp"

// Singleton
ControlPanel& ControlPanel::getInstance() {
    static ControlPanel instance;
    return instance;
}

ControlPanel::ControlPanel() {
    bg.setFillColor(sf::Color(39,39,39));
    bg.setPosition({WORLD_X + WORLD_WIDTH*TILE_SIZE, WORLD_Y});

    restartGame();

    createText(dayText,     {100.f, 20.f});
    createText(dayTimeText, {400.f, 20.f});
    
    createText(incomeText,  {100.f, 60.f});
    createText(discontText, {400.f, 60.f});
    createText(visitsText,  {100.f, 100.f});

    createText(timeSpeedText, {100.f, 140.f});
    timeSpeedText.setString("Time speed");
    
    gameSpeedState = GameSpeed::slow;
    GameField::setTimeSpeed(gameSpeedState);
    timeSpeedBar = ScrollBar(
        bg.getPosition() + sf::Vector2f(110.f, 190.f), {200.f, 20.f}, (int)GameSpeed::size, (int)gameSpeedState,
        sf::Color::Transparent, sf::Color::White, 1, sf::Color::White, sf::Color::White
        );

    createText(nextDayDiscontText,    {100.f, 200.f});
    float discontVal = 0.f;
    GameField::setDiscont(discontVal);
    discontBar = ScrollBar(
        bg.getPosition() + sf::Vector2f(110.f, 250.f), {500.f, 20.f}, 25, (int)discontVal,
        sf::Color::Transparent, sf::Color::White, 1, sf::Color::White, sf::Color::White
        ); 

    createText(dayStatsText,   {100.f, 400.f});
    dayStatsText.setString("PREV DAY STATS");
    createText(lastIncomeText, {100.f, 460.f});
    createText(lastVisitsText, {400.f, 460.f});
    createText(lastDiscontText,{100.f, 490.f});

    btnBG = sf::Color(120, 120, 120);
    btnHoverBG = sf::Color(130, 130, 130);
    outlineColor = sf::Color(255, 255, 255);
}

void ControlPanel::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(bg);
    
    // texts
    target.draw(dayText);
    target.draw(dayTimeText);
    target.draw(dayStatsText);
    target.draw(timeSpeedText);
    
    // Income text
    target.draw(lastIncomeText);
    target.draw(incomeText);
    
    // Discont text
    target.draw(lastDiscontText);
    target.draw(discontText);
    target.draw(nextDayDiscontText);
    
    // Visits text
    target.draw(lastVisitsText);
    target.draw(visitsText);

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
    updateIncomeText(GameField::getIncome());
    updateNextDayDiscontText(discontBar.getStep()*discontStep);
    updateDayTimeText(timeNow);
    updateVisitsText(GameField::getVisits());
}

void ControlPanel::render(sf::Event& event) {
    sf::Vector2i mouseCoord;

    timeSpeedBar.update(event);
    gameSpeedState = (GameSpeed)timeSpeedBar.getStep();
    GameField::setTimeSpeed(gameSpeedState);

    discontBar.update(event);
}

void ControlPanel::newDay() {
    dayCount++;
    dayText.setString("Day #" + std::to_string(dayCount));

    updateLastDiscontText(GameField::getDiscont());
    updateLastIncomeText(GameField::getIncome());
    updateLastVisitsText(GameField::getVisits());
    GameField::restartDay();
 
    float discont = discontBar.getStep()/100.f*discontStep;
    GameField::setDiscont(discont);
    updateDiscontText(discont);
}

void ControlPanel::restartGame() {
    dayCount = 0;
    timeNow = 0.f;
    discontBar.setStep(0); // set discont to zero
    newDay();
}

//
//  Buttons (create and hover funcs)
//
Button ControlPanel::createButton(sf::Vector2f position, std::string text) {
    Button btn({110, 35}, position, btnBG);
    btn.setLabel(AssetsManager::loadFont(BLAZMA_FONT), text, sf::Color::White, 24, Align::center, sf::Text::Style::Regular);
    btn.setOutline(outlineSize, outlineColor);
    return btn;
}

void ControlPanel::onHover(Button& btn) {
    btn.setBGColor(btnHoverBG);
    btn.setOutline(outlineHoverSize, outlineColor);
}

void ControlPanel::dropHover(Button& btn) {
    btn.setBGColor(btnBG);
    btn.setOutline(outlineSize, outlineColor);
}


//
//  Text funcs
//
void ControlPanel::createText(sf::Text& text, sf::Vector2f position) {
    text.setPosition(bg.getPosition() + position);
    text.setFont(AssetsManager::loadFont(BLAZMA_FONT));
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(24);
}

//
//  Update every frame
//
void ControlPanel::updateDayTimeText(float time) {
    int hours = static_cast<int>(time/60.f) + SHOP_OPEN_TIME;
    int minutes = static_cast<int>(time) % 60;
    std::string hoursStr = hours > 9 ? std::to_string(hours) : "0" + std::to_string(hours);
    std::string minutesStr = minutes > 9 ? std::to_string(minutes) : "0" + std::to_string(minutes);
    dayTimeText.setString("Time " + hoursStr + "h " + minutesStr + "m");
}

void ControlPanel::updateNextDayDiscontText(int discont) {
    static int prevDiscont = -1;
    if (prevDiscont == discont) return;
    nextDayDiscontText.setString("Next day discont: " + std::to_string(discont) + "%");
    prevDiscont = discont;
}

void ControlPanel::updateIncomeText(int income) {
    static int prevIncome = -1;
    if (prevIncome == income) return;
    incomeText.setString("Shop income: " + std::to_string(income));
    prevIncome = income;
}

void ControlPanel::updateVisitsText(int visits) {
    static int prevVisits = -1;
    if (prevVisits == visits) return;
    visitsText.setString("Clients count: " + std::to_string(visits));
    prevVisits = visits;
}

//
//  Update ever game day
//
void ControlPanel::updateDiscontText(int discont) {
    discontText.setString("Today discont: " + std::to_string(discont) + "%");
}

void ControlPanel::updateLastDiscontText(int discont) {
    lastDiscontText.setString("Last discont: " + std::to_string(discont) + "%");
}

void ControlPanel::updateLastIncomeText(int income) {
    lastIncomeText.setString("Last income: " + std::to_string(income));
}

void ControlPanel::updateLastVisitsText(int visits) {
    lastVisitsText.setString("Last clients count: " + std::to_string(visits));
}

void ControlPanel::updateDayText() {
    dayText.setString("Day #: " + std::to_string(dayCount));
}