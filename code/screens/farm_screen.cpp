#include "farm_screen.h"

FarmScreen::FarmScreen(int x, int y, unsigned int width, unsigned int height): 
    OAEScreen(x, y, width, height),
    background(x, y, width, height, nullptr),
    displaysTheWordDay(x, y, (width*0.2), height*0.1, nullptr),
    dayNumberDisplay(x+(width*0.2), y, (width*0.4), height*0.1, 4),
    displaysAMoneySign(x+(width*0.6), y, (width*0.1), height*0.1, nullptr),
    moneyDisplay(x+(width*0.7), y, width*0.3, (height*0.1), 8),
    marketButton(x+(width*0.7), y+(height*0.9), width*0.3, height*0.1, nullptr),
    groundTileMap(x, y+(height*0.1), width, (height*0.9), 10, 10),
    alice(x+(width*0.45), y+(height*0.4), width*0.1, height*0.2, nullptr)
{
    shouldSwitchToMarketScreenFlag = false;
    groundTileMap.setTileWidth(100);
    groundTileMap.setTileHeight(100);
}

void FarmScreen::handleEvent(sf::Event event, sf::RenderWindow& window)
{
    switch(event.type)
    {
        case sf::Event::KeyPressed:
            switch(event.key.code)
            {
                case sf::Keyboard::A:
                    alice.setXMovementAmount(1.0);
                    break;
                case sf::Keyboard::D:
                    alice.setXMovementAmount(-1.0);
                    break;
                case sf::Keyboard::W:
                    alice.setYMovementAmount(1.0);
                    break;
                case sf::Keyboard::S:
                    alice.setYMovementAmount(-1.0);
                    break;
                default:
                    //
                    break;
            }
            break;
        case sf::Event::KeyReleased:
            switch(event.key.code)
            {
                case sf::Keyboard::A:
                    alice.setXMovementAmount(0.0);
                    break;
                case sf::Keyboard::D:
                    alice.setXMovementAmount(0.0);
                    break;
                case sf::Keyboard::W:
                    alice.setYMovementAmount(0.0);
                    break;
                case sf::Keyboard::S:
                    alice.setYMovementAmount(0.0);
                    break;
                default:
                    //
                    break;
            }
            break;
        case sf::Event::MouseButtonPressed:
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                int mouseX = mousePosition.x;
                int mouseY = mousePosition.y;
                if(marketButton.theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(mouseX, mouseY))
                {
                    this->shouldSwitchToMarketScreenFlag = true;
                }
            }
            break;
        default:
            //
            break;
    }
}

void FarmScreen::associateWithTexturesInBank(const TextureBank& textureBankToTakeFrom)
{
    groundTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_OUT_OF_BOUNDS_GRASS, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_OUT_OF_BOUNDS_GRASS));
    groundTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_IN_BOUNDS_GRASS, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_IN_BOUNDS_GRASS));
    groundTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_UNWATERED_TILLED_DIRT, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_UNWATERED_TILLED_DIRT));
    groundTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_WATERED_TILLED_DIRT, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_WATERED_TILLED_DIRT));
    alice.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE));
}

void FarmScreen::associateWithAnimationsInBank(const OAEAnimationBank& animationBankToTakeFrom)
{
    alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK)));
}

void FarmScreen::forceFullDraw(sf::RenderWindow& windowToDrawIn)
{
    background.draw(windowToDrawIn);
    groundTileMap.draw(windowToDrawIn);
    alice.draw(windowToDrawIn);
    displaysTheWordDay.draw(windowToDrawIn);
    dayNumberDisplay.draw(windowToDrawIn);
    displaysAMoneySign.draw(windowToDrawIn);
    moneyDisplay.draw(windowToDrawIn);
    marketButton.draw(windowToDrawIn);
}

void FarmScreen::update(sf::Int32 millisecondsElapsedSinceLastUpdate, sf::RenderWindow& windowToDrawIn)
{
    static bool wasAliceDrawnMovingLastFrame = false;
    float aliceSpeedInTilesPerSecond = 1;
    int numberOfMillisecondsSinceLastUpdate = millisecondsElapsedSinceLastUpdate;
    if((alice.getXMovementAmount() == 0) || (alice.getYMovementAmount() == 0))
    {
        float numberOfSecondsSinceLastUpdate = ((float)numberOfMillisecondsSinceLastUpdate) / 1000.0;
        float tilesTravelledSinceLastUpdateX = numberOfSecondsSinceLastUpdate * (alice.getXMovementAmount()) * aliceSpeedInTilesPerSecond;
        float tilesTravelledSinceLastUpdateY = numberOfSecondsSinceLastUpdate * (alice.getYMovementAmount()) * aliceSpeedInTilesPerSecond;
        groundTileMap.changeCentreOffsetTileCountXByAmount(tilesTravelledSinceLastUpdateX);
        groundTileMap.changeCentreOffsetTileCountYByAmount(tilesTravelledSinceLastUpdateY);
        groundTileMap.draw(windowToDrawIn);
        alice.drawAndUpdateSprite(windowToDrawIn, numberOfMillisecondsSinceLastUpdate);
        wasAliceDrawnMovingLastFrame = true;
        displaysTheWordDay.draw(windowToDrawIn);
        dayNumberDisplay.draw(windowToDrawIn);
        displaysAMoneySign.draw(windowToDrawIn);
        moneyDisplay.draw(windowToDrawIn);
        marketButton.draw(windowToDrawIn);
    }
    else if(wasAliceDrawnMovingLastFrame == true)
    {
        alice.drawAndUpdateSprite(windowToDrawIn, numberOfMillisecondsSinceLastUpdate);
        wasAliceDrawnMovingLastFrame = false;
    }
}

bool FarmScreen::returnIfShouldSwitchToMarketScreen()
{
    return shouldSwitchToMarketScreenFlag;
}

void FarmScreen::acknowledgeShouldSwitchToMarketScreen()
{
    shouldSwitchToMarketScreenFlag = false;
}
