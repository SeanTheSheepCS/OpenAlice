#ifndef MAIN_H
#define MAIN_H

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#include "screens/screen_enum.h"
#include "screens/oae_screen.h"
#include "screens/main_menu_screen.h"
#include "screens/farm_screen.h"
#include "screens/market_screen.h"
#include "save_game_helper.h"
#include "save_file.h"
#include "texture_bank.h"
#include "oae_animation_bank.h"

#define DEFAULT_ANIMATION_SPEED 300

enum textureBankReferenceNumbers
{
    TEXTURE_BANK_REF_NUMBER_OUT_OF_BOUNDS_GRASS = 0,
    TEXTURE_BANK_REF_NUMBER_IN_BOUNDS_GRASS = 1,
    TEXTURE_BANK_REF_NUMBER_UNWATERED_TILLED_DIRT = 2,
    TEXTURE_BANK_REF_NUMBER_WATERED_TILLED_DIRT = 3,
    TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE = 4,
    TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE = 5,
    TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO = 6
};

enum animationBankReferenceNumbers
{
    ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK = 0,
};

TextureBank initializeTextureBank();
OAEAnimationBank initializeOAEAnimationBank();

#endif
