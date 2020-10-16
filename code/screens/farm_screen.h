#ifndef FARM_SCREEN_H
#define FARM_SCREEN_H

#include <SFML/Graphics.hpp>
#include <utility>
#include "oae_screen.h"
#include "../engine/primitive_classes/textured_object.h"
#include "../engine/primitive_classes/textured_button_object.h"
#include "../engine/primitive_classes/world_object.h"
#include "../engine/primitive_classes/collision_box.h"
#include "../engine/primitive_classes/world_object_properties.h"
#include "../engine/advanced_classes/number_display_module/number_display_module.h"
#include "../engine/advanced_classes/tile_map_module/tile_map_module.h"
#include "../engine/advanced_classes/player_object_module/player_object_module.h"
#include "../actors/alice.h"
#include "../texture_bank.h"
#include "../save_file.h"
#include "../oae_animation_bank.h"
#include "../reference_number_enums.h"

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

		void loadSaveFile(const SaveFile& saveFileToLoad);

        bool returnIfShouldSwitchToMarketScreen();
        void acknowledgeShouldSwitchToMarketScreen();

        bool returnIfShouldSwitchToMainMenuScreen();
        void acknowledgeShouldSwitchToMainMenuScreen();
    protected:
        //
    private:
        void associateAliceWithCorrectAnimation(); //HELPER FUNCTION FOR UPDATE
		void handlePickUpEvent(sf::RenderWindow& windowToDrawIn); //HELPER FUNCTION FOR HANDLEEVENT
		void handleItemUseEvent(sf::RenderWindow& windowToDrawIn); //HELPER FUNCTION FOR HANDLEEVENT
		void drawAllObjectsALayerBelowAlice(sf::RenderWindow& windowToDrawIn); //HELPER FUNCTION FOR A LOT OF FUNCTIONS
		void drawAllObjectsALayerAboveAlice(sf::RenderWindow& windowToDrawIn); //HELPER FUNCTION FOR A LOT OF FUNCTIONS

        bool shouldSwitchToMarketScreenFlag;
        bool shouldSwitchToMainMenuScreenFlag;

        TexturedObject displaysTheWordDay;
        NumberDisplay dayNumberDisplay;
        TexturedObject displaysAMoneySign;
        NumberDisplay moneyDisplay;
        TexturedObject background;
        TexturedButtonObject marketButton;
        TexturedButtonObject mainMenuButton;
        TileMap groundTileMap;
		TileMap plantTileMap;
        Alice alice;
};

#endif
