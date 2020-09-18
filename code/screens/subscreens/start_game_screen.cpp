#include "start_game_screen.h"

StartGameScreen::StartGameScreen(int x, int y, unsigned int width, unsigned int height):
    OAEScreen(x,y,width,height),
    background(x,y,width,height,nullptr),
    exitScreenButton(x+(width*0.9),y,(width*0.1),(height*0.1),nullptr),
    selectFileOneButton(x+(width*0.1),y+(height*0.125),(width*0.8),(height*0.25),nullptr),
    deleteFileOneButton(x+(width*0.65),y+(height*0.2),(width*0.1),(height*0.1),nullptr),
    selectFileTwoButton(x+(width*0.1),y+(height*0.375),(width*0.8),(height*0.25),nullptr),
    deleteFileTwoButton(x+(width*0.65),y+(height*0.45),(width*0.1),(height*0.1),nullptr),
    selectFileThreeButton(x+(width*0.1),y+(height*0.625),(width*0.8),(height*0.25),nullptr),
    deleteFileThreeButton(x+(width*0.65),y+(height*0.7),(width*0.1),(height*0.1),nullptr)
{
    bool closeScreenRequestFlag = false;
    int chosenSavegameIsZeroIfNoSavegameHasBeenChosen = 0;
}

void StartGameScreen::handleEvent(sf::Event event, sf::RenderWindow& window)
{
    switch(event.type)
    {
        case sf::Event::MouseButtonPressed:
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                int mouseX = mousePosition.x;
                int mouseY = mousePosition.y;
                if(selectFileOneButton.theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(mouseX, mouseY))
                {
                    chosenSavegameIsZeroIfNoSavegameHasBeenChosen = 1;
                }
                else if(selectFileTwoButton.theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(mouseX, mouseY))
                {
                    chosenSavegameIsZeroIfNoSavegameHasBeenChosen = 2;
                }
                else if(selectFileThreeButton.theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(mouseX, mouseY))
                {
                    chosenSavegameIsZeroIfNoSavegameHasBeenChosen = 3;
                }
                else if(exitScreenButton.theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(mouseX, mouseY))
                {
                    closeScreenRequestFlag = true;
                }
            }
            break;
        default:
            break;
    }
}

void StartGameScreen::forceFullDraw(sf::RenderWindow& windowToDrawIn)
{
    background.draw(windowToDrawIn);
    exitScreenButton.draw(windowToDrawIn);
    selectFileOneButton.draw(windowToDrawIn);
    deleteFileOneButton.draw(windowToDrawIn);
    selectFileTwoButton.draw(windowToDrawIn);
    deleteFileTwoButton.draw(windowToDrawIn);
    selectFileThreeButton.draw(windowToDrawIn);
    deleteFileThreeButton.draw(windowToDrawIn);
}

void StartGameScreen::update(sf::Int32 millisecondsElapsedSinceLastUpdate, sf::RenderWindow& window)
{
    //
}

bool StartGameScreen::hasCloseScreenRequestBeenMade()
{
    return closeScreenRequestFlag;
}

void StartGameScreen::acknowledgeCloseScreenRequest()
{
    closeScreenRequestFlag = false;
}

int StartGameScreen::whichSaveGameHasBeenChosenReturnsZeroIfNoSavegameHasBeenChosen()
{
    return chosenSavegameIsZeroIfNoSavegameHasBeenChosen;
}

void StartGameScreen::acknowledgeChosenSavegame()
{
    chosenSavegameIsZeroIfNoSavegameHasBeenChosen = 0;
}
