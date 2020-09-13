#include <SFML/Graphics.hpp>
#include <X11/Xlib.h>
#include <iostream>
#include "main.h"

int main()
{
    ScreenEnum screenDisplayedOnLastIteration = NULL_SCREEN;
    ScreenEnum currentScreenToDisplay = MAIN_MENU_SCREEN;
    MainMenuScreen mainMenuScreenVar(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    FarmScreen farmScreenVar(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    MarketScreen marketScreenVar(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    OAEScreen* pointerToCurrentlyActiveScreen = nullptr;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "OpenAlice V1.0");
    sf::Clock clockForApplication;

    while(window.isOpen())
    {
        switch(currentScreenToDisplay)
        {
            case MAIN_MENU_SCREEN:
                pointerToCurrentlyActiveScreen = &mainMenuScreenVar;
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
                break;
            case MARKET_SCREEN:
                pointerToCurrentlyActiveScreen = &marketScreenVar;
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
        pointerToCurrentlyActiveScreen->update(timeElapsed.asMilliseconds());

        window.display();
    }
}
