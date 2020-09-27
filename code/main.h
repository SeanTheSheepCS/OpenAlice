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
    TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO = 6,
    TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE = 7,
    TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE = 8,
    TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO = 9,
    TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE = 8,
    TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE = 10,
    TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO = 11,
    TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE = 12,
    TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE = 13,
    TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO = 14
};

enum animationBankReferenceNumbers
{
    ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK = 0,
    ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK = 1,
    ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK = 2,
    ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK = 3
};

TextureBank initializeTextureBank();
OAEAnimationBank initializeOAEAnimationBank();

#endif
