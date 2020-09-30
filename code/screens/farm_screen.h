#ifndef FARM_SCREEN_H
#define FARM_SCREEN_H

#include <SFML/Graphics.hpp>
#include "oae_screen.h"
#include "../engine/primitive_classes/textured_object.h"
#include "../engine/primitive_classes/textured_button_object.h"
#include "../engine/advanced_classes/number_display_module/number_display_module.h"
#include "../engine/advanced_classes/tile_map_module/tile_map_module.h"
#include "../engine/advanced_classes/player_object_module/player_object_module.h"
#include "../actors/alice.h"
#include "../texture_bank.h"
#include "../oae_animation_bank.h"
#include "../main.h"

enum TileMapReferenceNumbersForGroundEnum
{
    TILE_REF_NUM_OUT_OF_BOUNDS_GRASS = 0,
    TILE_REF_NUM_IN_BOUNDS_GRASS = 1,
    TILE_REF_NUM_UNWATERED_TILLED_DIRT = 2,
    TILE_REF_NUM_WATERED_TILLED_DIRT = 3,
};

class FarmScreen: public OAEScreen
{
    public:
        FarmScreen(int x, int y, unsigned int width, unsigned int height);
        void handleEvent(sf::Event event, sf::RenderWindow& window); 
        void forceFullDraw(sf::RenderWindow& windowToDrawIn);
        void update(sf::Int32 millisecondsElapsedSinceLastUpdate, sf::RenderWindow& windowToDrawIn);

        void associateWithTexturesInBank(const TextureBank& textureBankToTakeFrom);
        void associateWithAnimationsInBank(const OAEAnimationBank& animationBankToTakeFrom);
    	void initializeWorldObjectsInGroundTileMap();

        bool returnIfShouldSwitchToMarketScreen();
        void acknowledgeShouldSwitchToMarketScreen();
    protected:
        //
    private:
        void associateAliceWithCorrectAnimation(); //HELPER FUNCTION FOR UPDATE
        bool shouldSwitchToMarketScreenFlag;
        TexturedObject displaysTheWordDay;
        NumberDisplay dayNumberDisplay;
        TexturedObject displaysAMoneySign;
        NumberDisplay moneyDisplay;
        TexturedObject background;
        TexturedButtonObject marketButton;
        TileMap groundTileMap;
        Alice alice;
};

#endif
