#include "gameLogick/ControlPanel.hpp"

// Singleton
ControlPanel& ControlPanel::getInstance() {
    static ControlPanel instance;
    return instance;
}

ControlPanel::ControlPanel() {
    background.setFillColor(sf::Color(39,39,39, 125));

    labels.resize((int)Label::size);
    labels[(int)Label::day_count    ] = {createText({20.f, 20.f}), "Day #", "", -1};
    labels[(int)Label::day_time     ] = {createText({300.f, 20.f}), "Time: ", "", -1};
    
    labels[(int)Label::income ] = {createText({20.f, 60.f}), "Income: ", "", -1};
    labels[(int)Label::clients ] = {createText({20.f, 100.f}), "Clients: ", "", -1};
    
    // Scroll bars labels
    labels[(int)Label::time_speed        ] = {createText({20.f, 140.f}), "Time speed: ", "", -1};
    labels[(int)Label::discont           ] = {createText({20.f, 240.f}), "Discont: ", "%", -1};
    labels[(int)Label::clients_max_count ] = {createText({20.f, 340.f}), "Max client count: ", "", -1};
    labels[(int)Label::clients_serve_time] = {createText({20.f, 440.f}), "Clients serve time: ", "s", -1};
    labels[(int)Label::clients_spawn_time] = {createText({20.f, 540.f}), "Clients come time: ", "s", -1};
    
    gameSpeedState = GameSpeed::slow;
    GameField::setTimeSpeed(gameSpeedState);
    timeSpeedBar = ScrollBar(
        sf::Vector2f(30.f, 190.f), {200.f, 20.f}, (int)GameSpeed::size, (int)gameSpeedState,
        sf::Color::Transparent, sf::Color::White, 1, sf::Color::White, sf::Color::White
        );

    float discontVal = 0.f;
    GameField::setDiscont(discontVal);
    discontBar = ScrollBar(
        sf::Vector2f(30.f, 290.f), {500.f, 20.f}, 25, (int)discontVal,
        sf::Color::Transparent, sf::Color::White, 1, sf::Color::White, sf::Color::White
        );

    maxClientsBar = ScrollBar(
        sf::Vector2f(30.f, 390.f), {500.f, 20.f}, 25, 10,
        sf::Color::Transparent, sf::Color::White, 1, sf::Color::White, sf::Color::White
        );
    clientServeTimeBar = ScrollBar(
        sf::Vector2f(30.f, 490.f), {500.f, 20.f}, 25, 10,
        sf::Color::Transparent, sf::Color::White, 1, sf::Color::White, sf::Color::White
        );
    clientSpawnTimeBar = ScrollBar(
        sf::Vector2f(30.f, 590.f), {500.f, 20.f}, 25, 10,
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
    
    for (LabelInfo& labelInfo : labels)
        target.draw(labelInfo.label);

    // scrollbars
    target.draw(timeSpeedBar);
    target.draw(discontBar);
    target.draw(maxClientsBar);
    target.draw(clientServeTimeBar);
    target.draw(clientSpawnTimeBar);
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
    // Stop game time then animation play
    else {
        timeNow += dt;
    }

    if (timeNow >= DAY_WORK_TIME) {
        timeNow = 0.f;
        newDay();
    }

    for (int i = 0; i < (int)Label::size; i++) {
        LabelInfo& labelInfo = labels[i];
        int curValue = -1;
        switch((Label)i) {
        case Label::day_count:
            curValue = dayCount;
            break;
        case Label::day_time:
            updateTimeText(timeNow);
            curValue = -1;
            break;
        case Label::income:
            curValue = GameField::getIncome();
            break;
        case Label::clients:
            curValue = GameField::getClientsCount();
            break;
        case Label::discont:
            curValue = discontBar.getStep() * discontStepVal;
            GameField::setDiscont(discontBar.getStep()*discontStepVal/100.f);
            break;
        case Label::clients_max_count:
            curValue = maxClientsBar.getStep() * maxClientsStepVal + minClientsCount;
            GameField::setMaxClients(curValue);
            break;
        case Label::clients_serve_time:
            curValue = clientServeTimeBar.getStep();
            GameField::setServeTime(curValue);
            break;
        case Label::clients_spawn_time:
            curValue = clientSpawnTimeBar.getStep();
            GameField::setClientSpawnTime(curValue);
            break;
        case Label::time_speed:
            curValue = timeSpeedBar.getStep();
            GameField::setTimeSpeed((GameSpeed)curValue);
            break;
        }
        if (curValue == -1 || labelInfo.prevValue == curValue) continue;
        labelInfo.label.setString(labelInfo.before + std::to_string(curValue) + labelInfo.after);
    }
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
    discontBar.update(event);
    maxClientsBar.update(event);
    clientServeTimeBar.update(event);
    clientSpawnTimeBar.update(event);
}

void ControlPanel::newDay() {
    dayDialogVisible = true;
    dayCount++;
    dayDialog.setString("Day #" + std::to_string(dayCount));
    GameField::restartDay();
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

void ControlPanel::updateTimeText(float time) {
    LabelInfo& labelInfo = labels[(int)Label::day_time];
    
    // if minutes don't changed time is the same -> don't update it
    int minutes = static_cast<int>(time) % 60;
    if (labelInfo.prevValue == minutes) return;

    labelInfo.prevValue = minutes;
    int hours = static_cast<int>(time/60.f) + SHOP_OPEN_TIME;
    std::string hoursStr = hours > 9 ? std::to_string(hours) : "0" + std::to_string(hours);
    std::string minutesStr = minutes > 9 ? std::to_string(minutes) : "0" + std::to_string(minutes);
    labelInfo.label.setString(labelInfo.before + hoursStr + "h " + minutesStr + "m");
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