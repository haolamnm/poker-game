/*
FILE: include/pch.h

DESCRIPTION: Precompiled header file for the project. This file 
contains the necessary header files and constants for game 
assets such as images, sounds, and fonts.

NOTE: There are lots of constexprs, which are used to define
constants at compile time, avoid using #define macros. These
constants can be used in multiple files.

AUTHOR: Le Nguyen Anh Tri.
*/

#ifndef PCH_H
#define PCH_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <string>

/*
NOTE: The following constants are used for colors in the game.
PURPOSE: Handle the debug messages when running the game.
*/
#define RED_TEXT    "\033[1;31m"
#define GREEN_TEXT  "\033[1;32m"
#define YELLOW_TEXT "\033[1;33m"
#define BLUE_TEXT   "\033[1;34m"
#define RESET_TEXT  "\033[0m"

/*
NOTE: The following constants are used for define dimensions of 
the window and buttons in the game.
*/
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

constexpr int SMALL_BUTTON_WIDTH = 50;
constexpr int SMALL_BUTTON_HEIGHT = 50;
constexpr int SMALL_BUTTON_SPACING = 20;
constexpr int BOTTOM_MARGIN = 20;
constexpr int START_X = 20;
constexpr int START_Y = 600 - (5 * SMALL_BUTTON_HEIGHT + 4 * SMALL_BUTTON_SPACING + BOTTOM_MARGIN);

constexpr int BIG_BUTTON_WIDTH = 240;
constexpr int BIG_BUTTON_HEIGHT = 80;
constexpr int BIG_BUTTON_SPACING = 20;

constexpr int PVP_BUTTON_X = 280;
constexpr int PVP_BUTTON_Y = 370;
constexpr int PVE_BUTTON_X = 280;
constexpr int PVE_BUTTON_Y = 470;

constexpr int NEXT_BUTTON_X = 730;
constexpr int NEXT_BUTTON_Y = 530;

constexpr int PREV_BUTTON_X = 20;
constexpr int PREV_BUTTON_Y = 530;

constexpr int FOLD_BUTTON_X = 20;
constexpr int FOLD_BUTTON_Y  = 530;

constexpr int CALL_BUTTON_X = 90;
constexpr int CALL_BUTTON_Y = 530;

constexpr int RAISE_BUTTON_X = 20;
constexpr int RAISE_BUTTON_Y = 460;

constexpr int DRAW_BUTTON_X = 90;
constexpr int DRAW_BUTTON_Y = 460;

constexpr int CARD_WIDTH = 100;
constexpr int CARD_HEIGHT = 150;

/*
NOTE: The following constants are used for define the paths of
the game assets such as images, sounds, and fonts.
*/
constexpr const char* CARD_A_C = "assets/imgs/cards/A-C.png";
constexpr const char* CARD_A_D = "assets/imgs/cards/A-D.png";
constexpr const char* CARD_A_H = "assets/imgs/cards/A-H.png";
constexpr const char* CARD_A_S = "assets/imgs/cards/A-S.png";

constexpr const char* CARD_2_C = "assets/imgs/cards/2-C.png";
constexpr const char* CARD_2_D = "assets/imgs/cards/2-D.png";
constexpr const char* CARD_2_H = "assets/imgs/cards/2-H.png";
constexpr const char* CARD_2_S = "assets/imgs/cards/2-S.png";

constexpr const char* CARD_3_C = "assets/imgs/cards/3-C.png";
constexpr const char* CARD_3_D = "assets/imgs/cards/3-D.png";
constexpr const char* CARD_3_H = "assets/imgs/cards/3-H.png";
constexpr const char* CARD_3_S = "assets/imgs/cards/3-S.png";

constexpr const char* CARD_4_C = "assets/imgs/cards/4-C.png";
constexpr const char* CARD_4_D = "assets/imgs/cards/4-D.png";
constexpr const char* CARD_4_H = "assets/imgs/cards/4-H.png";
constexpr const char* CARD_4_S = "assets/imgs/cards/4-S.png";

constexpr const char* CARD_5_C = "assets/imgs/cards/5-C.png";
constexpr const char* CARD_5_D = "assets/imgs/cards/5-D.png";
constexpr const char* CARD_5_H = "assets/imgs/cards/5-H.png";
constexpr const char* CARD_5_S = "assets/imgs/cards/5-S.png";

constexpr const char* CARD_6_C = "assets/imgs/cards/6-C.png";
constexpr const char* CARD_6_D = "assets/imgs/cards/6-D.png";
constexpr const char* CARD_6_H = "assets/imgs/cards/6-H.png";
constexpr const char* CARD_6_S = "assets/imgs/cards/6-S.png";

constexpr const char* CARD_7_C = "assets/imgs/cards/7-C.png";
constexpr const char* CARD_7_D = "assets/imgs/cards/7-D.png";
constexpr const char* CARD_7_H = "assets/imgs/cards/7-H.png";
constexpr const char* CARD_7_S = "assets/imgs/cards/7-S.png";

constexpr const char* CARD_8_C = "assets/imgs/cards/8-C.png";
constexpr const char* CARD_8_D = "assets/imgs/cards/8-D.png";
constexpr const char* CARD_8_H = "assets/imgs/cards/8-H.png";
constexpr const char* CARD_8_S = "assets/imgs/cards/8-S.png";

constexpr const char* CARD_9_C = "assets/imgs/cards/9-C.png";
constexpr const char* CARD_9_D = "assets/imgs/cards/9-D.png";
constexpr const char* CARD_9_H = "assets/imgs/cards/9-H.png";
constexpr const char* CARD_9_S = "assets/imgs/cards/9-S.png";

constexpr const char* CARD_10_C = "assets/imgs/cards/10-C.png";
constexpr const char* CARD_10_D = "assets/imgs/cards/10-D.png";
constexpr const char* CARD_10_H = "assets/imgs/cards/10-H.png";
constexpr const char* CARD_10_S = "assets/imgs/cards/10-S.png";

constexpr const char* CARD_J_C = "assets/imgs/cards/J-C.png";
constexpr const char* CARD_J_D = "assets/imgs/cards/J-D.png";
constexpr const char* CARD_J_H = "assets/imgs/cards/J-H.png";
constexpr const char* CARD_J_S = "assets/imgs/cards/J-S.png";

constexpr const char* CARD_Q_C = "assets/imgs/cards/Q-C.png";
constexpr const char* CARD_Q_D = "assets/imgs/cards/Q-D.png";
constexpr const char* CARD_Q_H = "assets/imgs/cards/Q-H.png";
constexpr const char* CARD_Q_S = "assets/imgs/cards/Q-S.png";

constexpr const char* CARD_K_C = "assets/imgs/cards/K-C.png";
constexpr const char* CARD_K_D = "assets/imgs/cards/K-D.png";
constexpr const char* CARD_K_H = "assets/imgs/cards/K-H.png";
constexpr const char* CARD_K_S = "assets/imgs/cards/K-S.png";

constexpr const char* CARD_JOKER = "assets/imgs/cards/JOKER.png";
constexpr const char* CARD_BACK = "assets/imgs/cards/BACK.png";

/*
NOTE: The following constants are used for define the icon and
cursor of the game.
*/
constexpr const char* ICON_PATH = "assets/imgs/icon/icon.png";
constexpr const char* CURSOR_PATH = "assets/imgs/cursor/cursor.png";

/*
NOTE: The following constants are used for define the audio
settings in the game.
*/
constexpr int AUDIO_FREQUENCY = 44100;
constexpr int AUDIO_CHANNELS = 2;
constexpr int AUDIO_CHUNK_SIZE = 2048;
constexpr int BACKGROUND_MUSIC_VOLUME = 16; // 0 to 128
constexpr const char* BUTTON_CLICK_SOUND_PATH = "assets/audios/button_click.wav";
constexpr const char* BACKGROUND_MUSIC_PATH = "assets/audios/background_music.mp3";

/*
NOTE: The following constants are used for define the font
settings in the game.
*/
constexpr int SMALL_FONT_SIZE = 18;
constexpr int MEDIUM_FONT_SIZE = 36;
constexpr int BIG_FONT_SIZE = 64;
constexpr const char* FONT_RETRON_PATH = "assets/fonts/SVN-Retron2000.otf";
constexpr const char* FONT_VINTAGE_PATH = "assets/fonts/SVN-Vintage.otf";
constexpr const char* FONT_DETERMINATION_PATH = "assets/fonts/SVN-DeterminationSans.otf";

/*
NOTE: The following constants are used for define the paths of
the buttons in the game.
*/
constexpr const char* BUTTON_HOME_PATH = "assets/imgs/buttons/home.png";
constexpr const char* BUTTON_FOLD_PATH = "assets/imgs/buttons/fold.png";
constexpr const char* BUTTON_CALL_PATH = "assets/imgs/buttons/call.png";
constexpr const char* BUTTON_DOWN_PATH = "assets/imgs/buttons/down.png";
constexpr const char* BUTTON_RESET_PATH = "assets/imgs/buttons/draw.png";
constexpr const char* BUTTON_RAISE_PATH = "assets/imgs/buttons/raise.png";
constexpr const char* BUTTON_ABOUT_PATH = "assets/imgs/buttons/about_us.png";
constexpr const char* BUTTON_PREV_PATH = "assets/imgs/buttons/arrow_left.png";
constexpr const char* BUTTON_NEXT_PATH = "assets/imgs/buttons/arrow_right.png";
constexpr const char* BUTTON_TUTORIAL_PATH = "assets/imgs/buttons/tutorial.png";
constexpr const char* BUTTON_SETTINGS_PATH = "assets/imgs/buttons/settings.png";
constexpr const char* BUTTON_USER_INFO_PATH = "assets/imgs/buttons/user_info.png";
constexpr const char* BUTTON_LEADERBOARD_PATH = "assets/imgs/buttons/leaderboard.png";
constexpr const char* BUTTON_SOUND_ON_PATH = "assets/imgs/buttons/sound_effects_on.png";
constexpr const char* BUTTON_SOUND_OFF_PATH = "assets/imgs/buttons/sound_effects_off.png";
constexpr const char* BUTTON_MUSIC_ON_PATH = "assets/imgs/buttons/background_music_on.png";
constexpr const char* BUTTON_MUSIC_OFF_PATH = "assets/imgs/buttons/background_music_off.png";

/*
NOTE: This is an array of the paths of the card images. We use 
this to easily retrieve the image of a card based on its suit 
and rank.
*/
const std::string CARD_FILES[52] = {
    CARD_2_C, CARD_2_D, CARD_2_H, CARD_2_S,
    CARD_3_C, CARD_3_D, CARD_3_H, CARD_3_S,
    CARD_4_C, CARD_4_D, CARD_4_H, CARD_4_S,
    CARD_5_C, CARD_5_D, CARD_5_H, CARD_5_S,
    CARD_6_C, CARD_6_D, CARD_6_H, CARD_6_S,
    CARD_7_C, CARD_7_D, CARD_7_H, CARD_7_S,
    CARD_8_C, CARD_8_D, CARD_8_H, CARD_8_S,
    CARD_9_C, CARD_9_D, CARD_9_H, CARD_9_S,
    CARD_10_C, CARD_10_D, CARD_10_H, CARD_10_S,
    CARD_J_C, CARD_J_D, CARD_J_H, CARD_J_S,
    CARD_Q_C, CARD_Q_D, CARD_Q_H, CARD_Q_S,
    CARD_K_C, CARD_K_D, CARD_K_H, CARD_K_S,
    CARD_A_C, CARD_A_D, CARD_A_H, CARD_A_S
};

#endif