#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include "main.h"

OAEAnimationBank initializeOAEAnimationBank(const TextureBank& textureBankToUse)
{
    OAEAnimationBank returnValue;
    OAEAnimation aliceWalkDownAnimation = OAEAnimation(DEFAULT_ANIMATION_SPEED);
	OAEAnimation aliceWalkDownAnimationHoe = OAEAnimation(DEFAULT_ANIMATION_SPEED);
    OAEAnimation aliceWalkUpAnimation = OAEAnimation(DEFAULT_ANIMATION_SPEED);
	OAEAnimation aliceWalkUpAnimationHoe = OAEAnimation(DEFAULT_ANIMATION_SPEED);
    OAEAnimation aliceWalkLeftAnimation = OAEAnimation(DEFAULT_ANIMATION_SPEED);
    OAEAnimation aliceWalkLeftAnimationHoe = OAEAnimation(DEFAULT_ANIMATION_SPEED);
    OAEAnimation aliceWalkRightAnimation = OAEAnimation(DEFAULT_ANIMATION_SPEED);
    OAEAnimation aliceWalkRightAnimationHoe = OAEAnimation(DEFAULT_ANIMATION_SPEED);

    aliceWalkDownAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE));
    aliceWalkDownAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO));

    aliceWalkDownAnimationHoe.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE_HOE));
    aliceWalkDownAnimationHoe.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_HOE));

    aliceWalkUpAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE));
    aliceWalkUpAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO));

    aliceWalkUpAnimationHoe.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE_HOE));
    aliceWalkUpAnimationHoe.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO_HOE));

    aliceWalkLeftAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE));
    aliceWalkLeftAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE));
    aliceWalkLeftAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE));
    aliceWalkLeftAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO));

    aliceWalkLeftAnimationHoe.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_HOE));
    aliceWalkLeftAnimationHoe.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE_HOE));
    aliceWalkLeftAnimationHoe.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_HOE));
    aliceWalkLeftAnimationHoe.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO_HOE));

    aliceWalkRightAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE));
    aliceWalkRightAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE));
    aliceWalkRightAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE));
    aliceWalkRightAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO));

    aliceWalkRightAnimationHoe.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_HOE));
    aliceWalkRightAnimationHoe.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE_HOE));
    aliceWalkRightAnimationHoe.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_HOE));
    aliceWalkRightAnimationHoe.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO_HOE));

    returnValue.saveOAEAnimationWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK, aliceWalkDownAnimation);
    returnValue.saveOAEAnimationWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_HOE, aliceWalkDownAnimationHoe);
    returnValue.saveOAEAnimationWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK, aliceWalkUpAnimation);
    returnValue.saveOAEAnimationWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_HOE, aliceWalkUpAnimationHoe);
    returnValue.saveOAEAnimationWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK, aliceWalkLeftAnimation);
    returnValue.saveOAEAnimationWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_HOE, aliceWalkLeftAnimationHoe);
    returnValue.saveOAEAnimationWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK, aliceWalkRightAnimation);
    returnValue.saveOAEAnimationWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_HOE, aliceWalkRightAnimationHoe);

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
