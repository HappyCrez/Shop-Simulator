#include "gameLogick/ControlPanel.hpp"

// Singleton
ControlPanel& ControlPanel::getInstance() {
    static ControlPanel instance;
    return instance;
}

ControlPanel::ControlPanel() {
    background.setFillColor(sf::Color(39,39,39, 125));

    labels.resize((int)LabelType::size);
    labels[(int)LabelType::day_count] = {createText({20.f, 20.f}), "Day #"  , "", -1};
    labels[(int)LabelType::day_time ] = {createText({300.f, 20.f}), "Time: ", "", -1};
    
    labels[(int)LabelType::income ] = {createText({20.f, 60.f}), "Income: "  , "", -1};
    labels[(int)LabelType::clients] = {createText({20.f, 100.f}), "Clients: ", "", -1};
    
    // Scroll bars labels
    labels[(int)LabelType::time_speed        ] = {createText({20.f, 140.f}), "Time speed: " , "" , -1};
    labels[(int)LabelType::discont           ] = {createText({20.f, 240.f}), "Discont: "    , "%", -1};
    labels[(int)LabelType::clients_max_count ] = {createText({20.f, 340.f}), "Max client count: "  , "" , -1};
    labels[(int)LabelType::clients_serve_time] = {createText({20.f, 440.f}), "Clients serve time: ", "s", -1};
    labels[(int)LabelType::clients_spawn_time] = {createText({20.f, 540.f}), "Clients come time: " , "s", -1};

    scrollBars.resize((int)ScrollBarType::size);
    for (int i = 0; i < (int)ScrollBarType::size; i++) {
        int stepsCount = 25;
        sf::Vector2f barSize (500.f, 20.f);
        if (i == (int)ScrollBarType::timeSpeed) {
            stepsCount = (int)GameSpeed::size;
            barSize.x = 150.f;
        }

        scrollBars[i] = ScrollBar(
            sf::Vector2f(30.f, i*100.f + 190.f), barSize, stepsCount, 0,
            sf::Color::Transparent, sf::Color::White, 1, sf::Color::White, sf::Color::White
        );
    }

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
    
    for (Label& label : labels)
        target.draw(label.text);

    for (ScrollBar& scrollBar : scrollBars)
        target.draw(scrollBar);
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

    for (int i = 0; i < (int)LabelType::size; i++) {
        int curValue = -1;
        switch((LabelType)i) {
        case LabelType::day_count:
            curValue = dayCount;
            break;
        case LabelType::day_time:
            updateTimeText(timeNow);
            curValue = -1;
            break;
        case LabelType::income:
            curValue = GameField::getIncome();
            break;
        case LabelType::clients:
            curValue = GameField::getClientsCount();
            break;
        case LabelType::discont:
            curValue = scrollBars[(int)ScrollBarType::discont].getStep() * discontStepVal;
            GameField::setDiscont(static_cast<float>(curValue)/100.f);
            break;
        case LabelType::clients_max_count:
            curValue = scrollBars[(int)ScrollBarType::maxClients].getStep() * maxClientsStepVal + minClientsCount;
            GameField::setMaxClients(curValue);
            break;
        case LabelType::clients_serve_time:
            curValue = scrollBars[(int)ScrollBarType::clientServeTime].getStep() + minServeTime;
            GameField::setServeTime(curValue);
            break;
        case LabelType::clients_spawn_time: 
            curValue = scrollBars[(int)ScrollBarType::clientSpawnTime].getStep() + minSpawnTime +
                (100 - labels[(int)LabelType::discont].prevValue) / 5 / discontStepVal ; // attractive depend of discont value
            GameField::setClientSpawnTime(curValue);
            break;
        case LabelType::time_speed:
            curValue = scrollBars[(int)ScrollBarType::timeSpeed].getStep();
            gameSpeedState = (GameSpeed)curValue;
            GameField::setTimeSpeed((GameSpeed)curValue);
            break;
        }
        Label& label = labels[i];
        if (curValue == -1 || label.prevValue == curValue) continue;
        label.prevValue = curValue;
        label.text.setString(label.before + std::to_string(curValue) + label.after);
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

    for (ScrollBar& scrollBar : scrollBars)
        scrollBar.update(event);
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
    for (ScrollBar& scrollBar : scrollBars)
        scrollBar.setStep(0); // drop all params
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
    Label& label = labels[(int)LabelType::day_time];
    
    // if minutes don't changed time is the same -> don't update it
    int minutes = static_cast<int>(time) % 60;
    if (label.prevValue == minutes) return;

    label.prevValue = minutes;
    int hours = static_cast<int>(time/60.f) + SHOP_OPEN_TIME;
    std::string hoursStr = hours > 9 ? std::to_string(hours) : "0" + std::to_string(hours);
    std::string minutesStr = minutes > 9 ? std::to_string(minutes) : "0" + std::to_string(minutes);
    label.text.setString(label.before + hoursStr + "h " + minutesStr + "m");
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