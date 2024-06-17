#include "gameLogick/ControlPanel.hpp"

// Singleton
ControlPanel& ControlPanel::getInstance() {
    static ControlPanel instance;
    return instance;
}

ControlPanel::ControlPanel() {
    background.setFillColor(sf::Color(39,39,39, 125));

    labels.resize((int)Label::size);
    labels[(int)Label::day_count    ] = createText({20.f, 20.f});
    labels[(int)Label::day_time     ] = createText({300.f, 20.f});
    labels[(int)Label::day_stats    ] = createText({20.f, 400.f});
    labels[(int)Label::last_income  ] = createText({20.f, 460.f});
    labels[(int)Label::today_income ] = createText({20.f, 60.f});
    labels[(int)Label::last_visits  ] = createText({300.f, 460.f});
    labels[(int)Label::today_visits ] = createText({20.f, 100.f});
    labels[(int)Label::last_discont ] = createText({20.f, 490.f});
    labels[(int)Label::today_discont] = createText({300.f, 60.f});
    labels[(int)Label::next_discont ] = createText({20.f, 200.f});
    labels[(int)Label::time_speed   ] = createText({20.f, 140.f});
    
    labels[(int)Label::time_speed   ].setString("Time speed");
    labels[(int)Label::day_stats    ].setString("PREV DAY STATS");
    
    gameSpeedState = GameSpeed::slow;
    GameField::setTimeSpeed(gameSpeedState);
    timeSpeedBar = ScrollBar(
        sf::Vector2f(30.f, 190.f), {200.f, 20.f}, (int)GameSpeed::size, (int)gameSpeedState,
        sf::Color::Transparent, sf::Color::White, 1, sf::Color::White, sf::Color::White
        );

    float discontVal = 0.f;
    GameField::setDiscont(discontVal);
    discontBar = ScrollBar(
        sf::Vector2f(30.f, 250.f), {500.f, 20.f}, 25, (int)discontVal,
        sf::Color::Transparent, sf::Color::White, 1, sf::Color::White, sf::Color::White
        ); 

    btnBG = sf::Color::Black;
    btnHoverBG = sf::Color(10, 10, 10);
    outlineColor = sf::Color(255, 255, 255);

    collapse = createButton();
    dayDialog = createButton();

    showPanel();
}

void ControlPanel::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(collapse);

    target.draw(dayDialog);

    if (!isVisible) return;
    target.draw(background);
    
    for (sf::Text& label : labels)
        target.draw(label);

    // scrollbars
    target.draw(timeSpeedBar);
    target.draw(discontBar);
}

void ControlPanel::update(float dt) {
    static float animationTime = 0;
    static bool dayState = false;

    dt *= (int)gameSpeedState;

    // Day change animation
    if (dayDialogVisible) {
        animationTime += dt;
        
        if (animationTime > DAY_CHANGE_ANIMATION) {
            animationTime = 0.f;
            dayDialogVisible = false;
        }
        dayDialogTransparency(animationTime);
    } 
    // Stop time then animation play
    else {
        timeNow += dt;
    }

    if (timeNow >= DAY_WORK_TIME) {
        timeNow = 0.f;
        newDay();
    }
    updateDayTimeText(timeNow);
    updateIncomeText(GameField::getIncome());
    updateVisitsText(GameField::getVisits());
}

void ControlPanel::render(sf::Event& event) {
    sf::Vector2i mouseCoord;

    switch (event.type) {
    case sf::Event::MouseButtonPressed:
        if (event.mouseButton.button != sf::Mouse::Left) return;
        mouseCoord = {event.mouseButton.x, event.mouseButton.y};
        if (collapse.isInBounds(mouseCoord) ) {
            if (isVisible) hidePanel();
            else showPanel();
        }
        break;
    case sf::Event::MouseMoved:
        mouseCoord = {event.mouseMove.x, event.mouseMove.y};
        if (collapse.isInBounds(mouseCoord) ) {
            onHover(collapse);
        }
        else {
            dropHover(collapse);
        }
        break;
    }
    collapse.isInBounds(mouseCoord);

    timeSpeedBar.update(event);
    gameSpeedState = (GameSpeed)timeSpeedBar.getStep();
    GameField::setTimeSpeed(gameSpeedState);

    discontBar.update(event);
    updateNextDayDiscontText(discontBar.getStep()*discontStep);
}

void ControlPanel::newDay() {
    dayDialogVisible = true;
    dayCount++;
    dayDialog.setString("Day #" + std::to_string(dayCount));
    labels[(int)Label::day_count].setString("Day #" + std::to_string(dayCount));

    updateLastDiscontText(GameField::getDiscont());
    updateLastIncomeText(GameField::getIncome());
    updateLastVisitsText(GameField::getVisits());
    GameField::restartDay();
 
    int discont = discontBar.getStep()*discontStep;
    updateDiscontText(discont);
    GameField::setDiscont(discont/100.f);
}

void ControlPanel::restartGame() {
    dayCount = 0;
    timeNow = 0.f;
    discontBar.setStep(0); // set discont to zero
    GameField::dropValues();
    newDay();
}

void ControlPanel::showPanel() {
    isVisible = true;
    background.setSize(panelSize);
    updateCollapseButton();
    collapse.setString("hide");
}

void ControlPanel::hidePanel() {
    isVisible = false;
    background.setSize({0, 0});
    updateCollapseButton();
    collapse.setString("show");
}

void ControlPanel::updateCollapseButton() {
    collapse.setPosition({background.getPosition().x + background.getSize().x + 2, 2});
}

//
//  Buttons (create and hover funcs)
//
Button ControlPanel::createButton() {
    Button btn({110, 35}, {0, 0}, btnBG);
    btn.setLabel(AssetsManager::loadFont(BLAZMA_FONT), "", sf::Color::White, 24, Align::center, sf::Text::Style::Regular);
    btn.setBGColor(btnBG);
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

void ControlPanel::dayDialogTransparency(float time) {
    if (time > DAY_CHANGE_ANIMATION/2.f) time = std::abs(DAY_CHANGE_ANIMATION - time);
    sf::Uint8 transparency = static_cast<int>(time*(255.f/DAY_CHANGE_ANIMATION * 2.f)) % 255; 

    dayDialog.setOutline(outlineSize, {255, 255, 255, transparency});
    dayDialog.setBGColor({btnBG.r, btnBG.b, btnBG.g, transparency});
    dayDialog.setTextColor({255, 255, 255, transparency});
}

//
//  Text funcs
//
sf::Text ControlPanel::createText(sf::Vector2f position) {
    sf::Text text("", AssetsManager::loadFont(BLAZMA_FONT), 24);
    text.setPosition(background.getPosition() + position);
    text.setFillColor(sf::Color::White);
    return text;
}

//
//  Update every frame
//
void ControlPanel::updateDayTimeText(float time) {
    int hours = static_cast<int>(time/60.f) + SHOP_OPEN_TIME;
    int minutes = static_cast<int>(time) % 60;
    std::string hoursStr = hours > 9 ? std::to_string(hours) : "0" + std::to_string(hours);
    std::string minutesStr = minutes > 9 ? std::to_string(minutes) : "0" + std::to_string(minutes);
    labels[(int)Label::day_time].setString("Time " + hoursStr + "h " + minutesStr + "m");
}

void ControlPanel::updateNextDayDiscontText(int discont) {
    static int prevDiscont = -1;
    if (prevDiscont == discont) return;
    labels[(int)Label::next_discont].setString("Next day discont: " + std::to_string(discont) + "%");
    prevDiscont = discont;
}

void ControlPanel::updateIncomeText(int income) {
    static int prevIncome = -1;
    if (prevIncome == income) return;
    labels[(int)Label::today_income].setString("Shop income: " + std::to_string(income));
    prevIncome = income;
}

void ControlPanel::updateVisitsText(int visits) {
    static int prevVisits = -1;
    if (prevVisits == visits) return;
    labels[(int)Label::today_visits].setString("Clients count: " + std::to_string(visits));
    prevVisits = visits;
}

//
//  Update ever game day
//
void ControlPanel::updateDiscontText(int discont) {
    labels[(int)Label::today_discont].setString("Today discont: " + std::to_string(discont) + "%");
}

void ControlPanel::updateLastDiscontText(int discont) {
    labels[(int)Label::last_discont].setString("Last discont: " + std::to_string(discont) + "%");
}

void ControlPanel::updateLastIncomeText(int income) {
    labels[(int)Label::last_income].setString("Last income: " + std::to_string(income));
}

void ControlPanel::updateLastVisitsText(int visits) {
    labels[(int)Label::last_visits].setString("Last clients count: " + std::to_string(visits));
}

void ControlPanel::updateDayText() {
    labels[(int)Label::day_count].setString("Day #: " + std::to_string(dayCount));
}

//
//  Setters
//
void ControlPanel::initialize(sf::Vector2f wndSize) {
    background.setPosition({0, 0});
    panelSize = {wndSize.x / 3.f, wndSize.y};

    dayDialogVisible = false;
    sf::Vector2f dialogSize(wndSize / 5.f);
    dayDialog.setPosition((wndSize - dialogSize) / 2.f);
    dayDialog.setSize(dialogSize);
    dayDialogTransparency(0.f);
    showPanel();// update panel size
}