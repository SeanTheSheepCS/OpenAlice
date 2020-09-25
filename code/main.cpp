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
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_FOUR, "alice_down_walk_cycle_2_4.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_THREE, "alice_down_walk_cycle_3.png", &returnValue);
    return returnValue;
}

OAEAnimationBank initializeOAEAnimationBank(const TextureBank& textureBankToUse)
{
    OAEAnimationBank returnValue;
    OAEAnimation aliceWalkDownAnimation = OAEAnimation(DEFAULT_ANIMATION_SPEED);
    aliceWalkDownAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE));
    aliceWalkDownAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_FOUR));
    aliceWalkDownAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_THREE));
    aliceWalkDownAnimation.appendTextureToAnimation(textureBankToUse.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_FOUR));
    returnValue.saveOAEAnimationWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK, aliceWalkDownAnimation);
    return returnValue;
}

int main()
{
    //TEXTURE VARS
    TextureBank textureBankForApplication = initializeTextureBank();
    OAEAnimationBank animationBankForApplication = initializeOAEAnimationBank(textureBankForApplication);

    //MUSIC VARS
    sf::Music mainMenuMusic;
    if(!(mainMenuMusic.openFromFile("../music/main_menu_music.wav")))
    {
        std::cout << "Failed to open music music/main_menu_music.wav" << std::endl;
    }
    mainMenuMusic.play();

    //SCREEN STATE MACHINE VARS
    ScreenEnum screenDisplayedOnLastIteration = NULL_SCREEN;
    ScreenEnum currentScreenToDisplay = MAIN_MENU_SCREEN;
    MainMenuScreen mainMenuScreenVar(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    FarmScreen farmScreenVar(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    farmScreenVar.associateWithTexturesInBank(textureBankForApplication);
    farmScreenVar.associateWithAnimationsInBank(animationBankForApplication);

    MarketScreen marketScreenVar(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
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
                if(mainMenuScreenVar.returnSavegameThatShouldBeLoadedReturnsZeroIfNoSavegameIsChosenYet() == 0)
                {
                    pointerToCurrentlyActiveScreen = &mainMenuScreenVar;
                }
                else
                {
                    SaveFile fileToLoad = SaveGameHelper::loadSaveFile(mainMenuScreenVar.returnSavegameThatShouldBeLoadedReturnsZeroIfNoSavegameIsChosenYet());
                    mainMenuScreenVar.acknowledgeSavegameChoice();
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
