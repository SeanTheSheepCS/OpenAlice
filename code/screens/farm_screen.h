#ifndef FARM_SCREEN_H
#define FARM_SCREEN_H

#include <SFML/Graphics.hpp>
#include <utility>
#include <vector>
#include <thread>
#include <fstream>
#include <iterator>
#include "oae_screen.h"
#include "market_screen.h"
#include "../engine/primitive_classes/textured_object.h"
#include "../engine/primitive_classes/textured_and_animated_object.h"
#include "../engine/primitive_classes/textured_button_object.h"
#include "../engine/primitive_classes/world_object.h"
#include "../engine/primitive_classes/collision_box.h"
#include "../engine/primitive_classes/world_object_properties.h"
#include "../engine/advanced_classes/number_display_module/number_display_module.h"
#include "../engine/advanced_classes/tile_map_module/tile_map_module.h"
#include "../engine/advanced_classes/player_object_module/player_object_module.h"
#include "../engine/utilities/utilities.h"
#include "../actors/alice.h"
#include "../texture_bank.h"
#include "../save_file.h"
#include "../oae_animation_bank.h"
#include "../reference_number_enums.h"

#ifndef NUMBER_OF_MILLISECONDS_TO_SLEEP_FOR
#define NUMBER_OF_MILLISECONDS_TO_SLEEP_FOR 8000
#endif

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
		
		std::vector<unsigned char> toWriteableForm();

		void handleEvent(sf::Event event, sf::RenderWindow& window); 
		void forceFullDraw(sf::RenderWindow& windowToDrawIn);
		void update(sf::Int32 millisecondsElapsedSinceLastUpdate, sf::RenderWindow& windowToDrawIn);

		void associateWithTexturesInBank(const TextureBank& textureBankToTakeFrom);
		void associateWithAnimationsInBank(const OAEAnimationBank& animationBankToTakeFrom);
		void initializeWorldObjectsInGroundTileMap();

		void runSleepSequence(sf::RenderWindow& windowToDrawIn);
		void runFillWaterContainerSequence(sf::RenderWindow& windowToDrawIn);

		void loadSaveFile(const SaveFile& saveFileToLoad);

		bool returnIfShouldSwitchToMarketScreen() const;
		void acknowledgeShouldSwitchToMarketScreen();

		bool returnIfShouldSwitchToMainMenuScreen() const;
		void acknowledgeShouldSwitchToMainMenuScreen();

		bool returnIfShouldUpdateMarketScreen() const;
		void acknowledgeShouldUpdateMarketScreen();

		unsigned int getDay() const;
		unsigned int getMoneyAmount() const;
		void setMoneyDisplayAmount(unsigned int moneyDisplayAmount);
		void setDayDisplayAmount(unsigned int dayDisplayAmount);
	protected:
		//
	private:
		void associateAliceWithCorrectAnimation(); //HELPER FUNCTION FOR UPDATE
		void handlePickUpEvent(sf::RenderWindow& windowToDrawIn); //HELPER FUNCTION FOR HANDLEEVENT
		void handleItemUseEvent(sf::RenderWindow& windowToDrawIn); //HELPER FUNCTION FOR HANDLEEVENT
		void runHarvestSequence(unsigned int plantTileMapRow, unsigned int plantTileMapCol, sf::RenderWindow& windowToDrawIn);
		void updateTheFollowingRowsInThePlantTileMapBothBoundsInclusive(unsigned int lowerBound, unsigned int upperBound); //HELPER FUNCTION FOR UPDATE WHEN IN THE SLEEP STATE.
		void drawAllObjectsALayerBelowAlice(sf::RenderWindow& windowToDrawIn); //HELPER FUNCTION FOR A LOT OF FUNCTIONS
		void drawAllObjectsALayerAboveAlice(sf::RenderWindow& windowToDrawIn); //HELPER FUNCTION FOR A LOT OF FUNCTIONS

		//FLAGS FOR INTERACTING WITH OTHER SCREENS
		bool shouldSwitchToMarketScreenFlag;
		bool shouldSwitchToMainMenuScreenFlag;
		bool shouldUpdateMarketScreenFlag;

		std::string pathToSaveFileUsed;

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

		//SLEEP SCREEN AND VARIABLES
		TexturedObject dayNightCircle;
		bool isInSleepState;

		//SAVING SCREEN AND VARIABLES
		TexturedAndAnimatedObject displaysTheWordSaving;
		bool isSaveThreadValid;
		std::thread saveThread;
		void runSaveProcedure(); 
		bool isSaving;

		//LOADING VARIABLES
		bool isLoading;
		void runLoadProcedure(std::string pathOfFileToLoad);
};

#endif
