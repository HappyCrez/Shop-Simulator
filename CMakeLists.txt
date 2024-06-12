cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
project(GameProject)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(sources src/Launcher.cpp
            
            # File loaders
            src/loaders/AssetsManager.cpp
            
            # GameLogick
            # Screens
            src/gameLogick/Screen.cpp
            src/gameLogick/StartScreen.cpp
            src/gameLogick/GameScreen.cpp
            # Logick
            src/gameLogick/GameField.cpp
            src/gameLogick/ControlPanel.cpp
            src/gameLogick/Bot.cpp
            src/gameLogick/Tile.cpp
            
            # User Interface
            src/UI/Button.cpp
            src/UI/ScrollBar.cpp)

add_executable("${PROJECT_NAME}" "${sources}")
target_link_libraries("${PROJECT_NAME}" sfml-graphics sfml-audio sfml-network sfml-window sfml-system)
target_include_directories("${PROJECT_NAME}" PRIVATE include)