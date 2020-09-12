#include "main_menu_screen.h"

MainMenuScreen::MainMenuScreen(int x, int y, unsigned int width, unsigned int height): 
    OAEScreen(x, y, width, height),
    backgroundWithTitle(x,y,width,height,nullptr),
    startGameButton(x+(width*0.1),y+(height*0.55), (width*0.8), (height*0.15), nullptr),
    creditsButton(x+(width*0.1),y+(height*0.70), (width*0.8), (height*0.15), nullptr),
    exitGameButton(x+(width*0.1),y+(height*0.85), (width*0.8), (height*0.15), nullptr),
    startGameScreenVar(x+(width*0.1),y+(height*0.1),(width*0.8),(height*0.8)),
    creditsScreenVar(x+(width*0.1),y+(height*0.1),(width*0.8),(height*0.8))
{
    subscreenState = NO_SUBSCREEN_ACTIVE;
}

void MainMenuScreen::handleEvent(sf::Event event, sf::RenderWindow& window)
{
    switch(subscreenState)
    {
        case NO_SUBSCREEN_ACTIVE:
            switch(event.type)
            {
                case sf::Event::MouseButtonPressed:
                {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    int mouseX = mousePosition.x;
                    int mouseY = mousePosition.y;
                    if(startGameButton.theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(mouseX, mouseY))
                    {
                        subscreenState = START_GAME_SUBSCREEN_ACTIVE;
                        startGameScreenVar.forceFullDraw(window);
                    }
                    else if(creditsButton.theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(mouseX, mouseY))
                    {
                        subscreenState = CREDITS_SUBSCREEN_ACTIVE;
                        creditsScreenVar.forceFullDraw(window);
                    }
                    else if(exitGameButton.theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(mouseX, mouseY))
                    {
                        window.close();
                    }
                    break;
                }
                default:
                    break;
            }
            break;
        case START_GAME_SUBSCREEN_ACTIVE:
            startGameScreenVar.handleEvent(event, window);
            break;
        case CREDITS_SUBSCREEN_ACTIVE:
            creditsScreenVar.handleEvent(event, window);
            break;
        default:
            break;
    }
}

void MainMenuScreen::forceFullDraw(sf::RenderWindow& windowToDrawIn)
{
    backgroundWithTitle.draw(windowToDrawIn);
    startGameButton.draw(windowToDrawIn);
    creditsButton.draw(windowToDrawIn);
    exitGameButton.draw(windowToDrawIn);
}

void MainMenuScreen::update(sf::Int32 millisecondsElapsedSinceLastUpdate)
{

}
