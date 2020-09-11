#include <SFML/Graphics.hpp>
#include <X11/Xlib.h>
#include <iostream>
#include "main.h"

ScreenEnum screenDisplayedOnLastIteration = NULL_SCREEN;
ScreenEnum currentScreenToDisplay = MAIN_MENU_SCREEN;
MainMenuScreen mainMenuScreenVar;
FarmScreen farmScreenVar;
MarketScreen marketScreenVar;
Screen* pointerToCurrentlyActiveScreen;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "OpenAlice V1.0");
    mainMenuScreenVar.initializeAssets(WINDOW_WIDTH, WINDOW_HEIGHT);
    farmScreenVar.initializeAssets(WINDOW_WIDTH, WINDOW_HEIGHT);
    marketScreenVar.initializeAssets(WINDOW_WIDTH, WINDOW_HEIGHT);
    while(window.isOpen())
    {
        switch(currentScreenToDisplay)
        {
            case MAIN_MENU_SCREEN:
                pointerToCurrentlyActiveScreen = &mainMenuScreenVar;
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
                pointerToCurrentlyActiveScreen->forceFullDraw();
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
                    screenToDisplay.handleEvent(event);
                }
            }
        }

        sf::Time timeElapsed = clock.restart();
        screenToDisplay.update(timeElapsed.asMilliseconds());
    }
}
