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
#include "reference_number_enums.h"
#include "initialize_texture_bank.h"
#include "initialize_oae_animation_bank.h"

void syncFarmScreenWithMarketScreen(FarmScreen& farmScreenVar, MarketScreen& marketScreenVar);
void syncMarketScreenWithFarmScreen(MarketScreen& marketScreenVar, FarmScreen& farmScreenVar);

#endif
