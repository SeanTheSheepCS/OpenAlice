#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include "main.h"

void addTextureToTextureBank(int referenceNumber, std::string path, TextureBank* bankToWriteTo)
{
    sf::Texture textureToAdd;
    std::string fullPath = std::string("../sprites/").append(path);
    if(!(textureToAdd.loadFromFile(fullPath)))
    {
        std::cout << "Failed to load texture: " << fullPath << std::endl;
        std::string invalidTexturePath = std::string("../sprites/").append("invalid_texture.png");
        if(!(textureToAdd.loadFromFile(invalidTexturePath)))
        {
            std::cout << "Failed to load texture: " << invalidTexturePath << std::endl;
        }
    }
    bankToWriteTo->saveTextureWithReferenceNumber(referenceNumber, textureToAdd);
}

TextureBank initializeTextureBank()
{
    TextureBank returnValue;    
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_OUT_OF_BOUNDS_GRASS, "grass_out_of_bounds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_IN_BOUNDS_GRASS, "grass.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_UNWATERED_TILLED_DIRT, "dirt_tilled_unwatered.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_WATERED_TILLED_DIRT, "dirt_tilled_watered.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_WATERED_TILLED_DIRT, "dirt_tilled_watered.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE, "alice_down_base.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE, "alice_down_walk_cycle_1.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO, "alice_down_walk_cycle_2.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE, "alice_up_base.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE, "alice_up_walk_cycle_1.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO, "alice_up_walk_cycle_2.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE, "alice_left_base.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE, "alice_left_walk_cycle_1.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO, "alice_left_walk_cycle_2.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE, "alice_right_base.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE, "alice_right_walk_cycle_1.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO, "alice_right_walk_cycle_2.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_WORLD_OBJECT_HOE, "hoe.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_WORLD_OBJECT_HOUSE, "house.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_WORLD_OBJECT_WELL, "well.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_WORLD_OBJECT_WATERING_CAN, "watering_can.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_SELECT_GAME_BUTTON, "start_game_button.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_CREDITS_BUTTON, "credits_button.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_EXIT_BUTTON, "exit_button.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_WINDOW_X, "x_icon.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_BACKGROUND, "main_menu_background.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_SAVE_GAME_ONE_BACKGROUND_TEXTURE, "save_one_background.png", &returnValue); 
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_SAVE_GAME_TWO_BACKGROUND_TEXTURE, "save_two_background.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_SAVE_GAME_THREE_BACKGROUND_TEXTURE, "save_three_background.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_DELETE_SAVE_GAME_ICON_TEXTURE, "delete_save_button.png", &returnValue);
    return returnValue;
}

OAEAnimationBank initializeOAEAnimationBank(const TextureBank& textureBankToUse)
{
    OAEAnimationBank returnValue;
    OAEAnimation aliceWalkDownAnimation = OAEAnimation(DEFAULT_ANIMATION_SPEED);
    OAEAnimation aliceWalkUpAnimation = OAEAnimation(DEFAULT_ANIMATION_SPEED);
    OAEAnimation aliceWalkLeftAnimation = OAEAnimation(DEFAULT_ANIMATION_SPEED);
    OAEAnimation aliceWalkRightAnimation = OAEAnimation(DEFAULT_ANIMATION_SPEED);

    aliceWalkDownAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE));
    aliceWalkDownAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO));

    aliceWalkUpAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE));
    aliceWalkUpAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO));

    aliceWalkLeftAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE));
    aliceWalkLeftAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE));
    aliceWalkLeftAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE));
    aliceWalkLeftAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO));

    aliceWalkRightAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE));
    aliceWalkRightAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE));
    aliceWalkRightAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE));
    aliceWalkRightAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO));

    returnValue.saveOAEAnimationWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK, aliceWalkDownAnimation);
    returnValue.saveOAEAnimationWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK, aliceWalkUpAnimation);
    returnValue.saveOAEAnimationWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK, aliceWalkLeftAnimation);
    returnValue.saveOAEAnimationWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK, aliceWalkRightAnimation);

    return returnValue;
}

int main()
{
    //TEXTURE VARS
    TextureBank textureBankForApplication = initializeTextureBank();
    OAEAnimationBank animationBankForApplication = initializeOAEAnimationBank(textureBankForApplication);

    //MUSIC VARS
    sf::Music mainMenuMusicStart;
    if(!(mainMenuMusicStart.openFromFile("../music/main_menu_music_start.wav")))
    {
        std::cout << "Failed to open music music/main_menu_music_start.wav" << std::endl;
    }
    sf::Music mainMenuMusicMain;
    if(!(mainMenuMusicMain.openFromFile("../music/main_menu_music_main.wav")))
    {
        std::cout << "Failed to open music music/main_menu_music_main.wav" << std::endl;
    }
    mainMenuMusicStart.play();

    //SCREEN STATE MACHINE VARS
    ScreenEnum screenDisplayedOnLastIteration = NULL_SCREEN;
    ScreenEnum currentScreenToDisplay = MAIN_MENU_SCREEN;

    MainMenuScreen mainMenuScreenVar(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    mainMenuScreenVar.associateWithTexturesInBank(textureBankForApplication);

    FarmScreen farmScreenVar(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    farmScreenVar.associateWithTexturesInBank(textureBankForApplication);
    farmScreenVar.associateWithAnimationsInBank(animationBankForApplication);

    MarketScreen marketScreenVar(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	marketScreenVar.populateMarketWithGarbageData();
    OAEScreen* pointerToCurrentlyActiveScreen = nullptr;

    //VARS FOR SFML
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "OpenAlice V1.0");
    window.setFramerateLimit(60);
    sf::Clock clockForApplication;

    while(window.isOpen())
    {
        switch(currentScreenToDisplay)
        {
            case MAIN_MENU_SCREEN:
				if((mainMenuMusicMain.getStatus() == sf::SoundSource::Stopped) && (mainMenuMusicStart.getStatus() == sf::SoundSource::Stopped))
				{
					mainMenuMusicMain.play();
				}
                if(mainMenuScreenVar.returnSavegameThatShouldBeLoadedReturnsZeroIfNoSavegameIsChosenYet() == 0)
                {
                    pointerToCurrentlyActiveScreen = &mainMenuScreenVar;
                }
                else
                {
					mainMenuMusicStart.stop();
					mainMenuMusicMain.stop();
                    SaveFile fileToLoad = SaveGameHelper::loadSaveFile(mainMenuScreenVar.returnSavegameThatShouldBeLoadedReturnsZeroIfNoSavegameIsChosenYet());
                    mainMenuScreenVar.acknowledgeSavegameChoice();
					farmScreenVar.loadSaveFile(fileToLoad);
                    pointerToCurrentlyActiveScreen = &farmScreenVar;
                    currentScreenToDisplay = FARM_SCREEN;
                }
                break;
            case FARM_SCREEN:
                pointerToCurrentlyActiveScreen = &farmScreenVar;
                if(farmScreenVar.returnIfShouldSwitchToMarketScreen())
                {
                    pointerToCurrentlyActiveScreen = &marketScreenVar;
                    currentScreenToDisplay = MARKET_SCREEN;
                    farmScreenVar.acknowledgeShouldSwitchToMarketScreen();
                }
				else if(farmScreenVar.returnIfShouldSwitchToMainMenuScreen())
				{
					mainMenuMusicMain.play();
					pointerToCurrentlyActiveScreen = &mainMenuScreenVar;
					currentScreenToDisplay = MAIN_MENU_SCREEN;
					farmScreenVar.acknowledgeShouldSwitchToMainMenuScreen();
				}
                break;
            case MARKET_SCREEN:
                pointerToCurrentlyActiveScreen = &marketScreenVar;
                if(marketScreenVar.returnIfShouldSwitchToFarmScreen())
                {
                    pointerToCurrentlyActiveScreen = &farmScreenVar;
                    currentScreenToDisplay = FARM_SCREEN;
                    marketScreenVar.acknowledgeShouldSwitchToFarmScreen();
                }
                break;
            default:
                pointerToCurrentlyActiveScreen = nullptr;
                break;
        }

        if(screenDisplayedOnLastIteration != currentScreenToDisplay)
        {
            if(pointerToCurrentlyActiveScreen != nullptr)
            {
                pointerToCurrentlyActiveScreen->forceFullDraw(window);
            }
        }
        screenDisplayedOnLastIteration = currentScreenToDisplay;

        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            else
            {
                if(pointerToCurrentlyActiveScreen != nullptr)
                {
                    pointerToCurrentlyActiveScreen->handleEvent(event, window);
                }
            }
        }


        sf::Time timeElapsed = clockForApplication.restart();
        pointerToCurrentlyActiveScreen->update(timeElapsed.asMilliseconds(), window);

        window.display();
    }
}
