/*
*   Defenitions of program
*   Most common enums, paths, etc.
*/
#define INT_MAX 0x7FFFFFFF

enum class Screens : int {no_screen = -1, start, settings, load, game, size};
enum class Align {top_left, top_right, bottom_left, bottom_right, center};

// Tiles types
#define ZONES_MAP               "./assets/files/ZonesMap.txt"
#define TILE_SIZE               32
enum class Tiles {
    no_tile = -3, obstacle, buy, // special tiles
    lettuce, carrot, tomato, eggplant, potato, grape, banana, foodTilesSize // food tiles 
};

// Textures
#define START_SCREEN_BACKGROUND "./assets/images/Start_screen_bg.jpeg"
#define GAME_FIELD_BACKGROUND   "./assets/images/Shop.png"

enum class BotTurn {down, left, right, up};
#define BOT_TEXTURE_MOVE_BASE   "./assets/images/Char_00"
#define BOT_TEXTURE_IDLE_BASE   "./assets/images/Char_idle_00"
#define BOT_FRAME_COLS          4
#define BOT_FRAME_ROWS          4
#define BOT_TEXTURES_CNT        1
#define BOT_SIZE                72
#define BOT_WAIT_BAR_HEIGHT     4.f
#define TARGET_OFFSET           5


// Fonts
#define MONTSERRAT_FONT     "./assets/fonts/Montserrat.ttf"
#define ROBOTO_BOLD_FONT    "./assets/fonts/Roboto-Bold.ttf"
#define BLAZMA_FONT         "./assets/fonts/Blazma-Regular.ttf"