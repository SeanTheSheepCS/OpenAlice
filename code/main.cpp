#include <SFML/Graphics.hpp>
#include <X11/Xlib.h>
#include <iostream>
#include "main.h"

TextureBank initializeTextureBank()
{
    TextureBank returnValue;    
    sf::Texture outOfBoundsGrassTexture;
    sf::Texture inBoundsGrassTexture;
    sf::Texture unwateredTilledDirtTexture;
    sf::Texture wateredTilledDirtTexture;
    if(!(outOfBoundsGrassTexture.loadFromFile("../sprites/grass_out_of_bounds.png")))
    {
        std::cout << "Failed to load texture: ../sprites/grass_out_of_bounds.png" << std::endl;
        outOfBoundsGrassTexture.loadFromFile("../sprites/invalid_texture.png");
        if(!(outOfBoundsGrassTexture.loadFromFile("../sprites/invalid_texture.png")))
        {
            std::cout << "Failed to load texture: ../sprites/invalid_texture.png" << std::endl;
        }
    }
    if(!(inBoundsGrassTexture.loadFromFile("../sprites/grass.png")))
    {
        std::cout << "Failed to load texture: ../sprites/grass.png" << std::endl;
        inBoundsGrassTexture.loadFromFile("../sprites/invalid_texture.png");
        if(!(inBoundsGrassTexture.loadFromFile("../sprites/invalid_texture.png")))
        {
            std::cout << "Failed to load texture: ../sprites/invalid_texture.png" << std::endl;
        }
    }
    if(!(unwateredTilledDirtTexture.loadFromFile("../sprites/dirt_tilled_unwatered.png")))
    {
        std::cout << "Failed to load texture: ../sprites/dirt_tilled_unwatered.png" << std::endl;
        if(!(unwateredTilledDirtTexture.loadFromFile("../sprites/invalid_texture.png")))
        {
            std::cout << "Failed to load texture: ../sprites/invalid_texture.png" << std::endl;
        }
    }
    if(!(wateredTilledDirtTexture.loadFromFile("../sprites/dirt_tilled_watered.png")))
    {
        std::cout << "Failed to load texture: ../sprites/dirt_tilled_watered.png" << std::endl;
        if(!(wateredTilledDirtTexture.loadFromFile("../sprites/invalid_texture.png")))
        {
            std::cout << "Failed to load texture: ../sprites/invalid_texture.png" << std::endl;
        }
    }
    returnValue.saveTextureWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_OUT_OF_BOUNDS_GRASS, outOfBoundsGrassTexture);
    returnValue.saveTextureWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_IN_BOUNDS_GRASS, inBoundsGrassTexture);
    returnValue.saveTextureWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_UNWATERED_TILLED_DIRT, unwateredTilledDirtTexture);
    returnValue.saveTextureWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_WATERED_TILLED_DIRT, wateredTilledDirtTexture);
    return returnValue;
}

int main()
{
    //TEXTURE VARS
    TextureBank textureBankForApplication = initializeTextureBank();

    //SCREEN STATE MACHINE VARS
    ScreenEnum screenDisplayedOnLastIteration = NULL_SCREEN;
    ScreenEnum currentScreenToDisplay = MAIN_MENU_SCREEN;
    MainMenuScreen mainMenuScreenVar(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    FarmScreen farmScreenVar(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    farmScreenVar.associateWithTexturesInBank(textureBankForApplication);
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
