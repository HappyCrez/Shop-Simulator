/*
*   Defenitions of program
*   Most common enums, paths, etc.
*/

enum class Screens : int {no_screen = -1, start, settings, load, game, size};
enum class Align {top_left, top_right, bottom_left, bottom_right, center};

// Tiles types
#define ZONES_MAP               "./assets/files/ZonesMap.txt"
#define TILE_SIZE               32
enum class Tiles {
    no_tile = -3, obstacle, buy, // special tiles
    tomato, potato, banana, lettuce, grape, eggplant, carrot, foodTilesSize // food tiles 
};

// Textures
#define START_SCREEN_BACKGROUND "./assets/images/Start_screen_bg.jpeg"
#define GAME_FIELD_BACKGROUND   "./assets/images/Shop.png"

#define BOT_TEXTURE_BASE        "./assets/images/bot"
#define BOT_TEXTURES_CNT        1
#define BOT_WIDTH               32
#define BOT_HEIGHT              64


// Fonts
#define MONTSERRAT_FONT     "./assets/fonts/Montserrat.ttf"
#define ROBOTO_BOLD_FONT    "./assets/fonts/Roboto-Bold.ttf"
#define BLAZMA_FONT         "./assets/fonts/Blazma-Regular.ttf"