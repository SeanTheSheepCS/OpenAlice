#include "farm_screen.h"

FarmScreen::FarmScreen(int x, int y, unsigned int width, unsigned int height): 
    OAEScreen(x, y, width, height),
    background(x, y, width, height, nullptr),
    displaysTheWordDay(x, y, (width*0.2), height*0.1, nullptr),
    dayNumberDisplay(x+(width*0.2), y, (width*0.4), height*0.1, 4),
    displaysAMoneySign(x+(width*0.6), y, (width*0.1), height*0.1, nullptr),
    moneyDisplay(x+(width*0.7), y, width*0.3, (height*0.1), 8),
    mainMenuButton(x, y+(height*0.9), width*0.3, height*0.1, nullptr), 
    marketButton(x+(width*0.7), y+(height*0.9), width*0.3, height*0.1, nullptr),
    groundTileMap(x, y+(height*0.1), width, (height*0.9), 40, 40),
	plantTileMap(x, y+(height*0.1), width, (height*0.9), 40, 40),
    alice(x+(width*0.45), y+(height*0.4), width*0.1, height*0.2)
{
    shouldSwitchToMainMenuScreenFlag = false;
    shouldSwitchToMarketScreenFlag = false;
	plantTileMap.setTileWidth(100);
	plantTileMap.setTileHeight(100);
    groundTileMap.setTileWidth(100);
    groundTileMap.setTileHeight(100);
    initializeWorldObjectsInGroundTileMap();
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
				case sf::Keyboard::Q:
					this->handlePickUpEvent(window);
					break;
				case sf::Keyboard::E:
					this->handleItemUseEvent(window);
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
        		if(mainMenuButton.theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(mouseX, mouseY))
				{
					this->shouldSwitchToMainMenuScreenFlag = true;
				}
            }
            break;
        default:
            //
            break;
    }
}

void FarmScreen::handlePickUpEvent(sf::RenderWindow& windowToDrawIn)
{
	std::map<int, WorldObject> worldObjectsAndRefNumbersThatAreIntersectingWithAlice = groundTileMap.getAllWorldObjectsWithRefNumbersWhoAreCurrentlyTriggeredByDrawableObject(alice);
	bool hasPickedUpObjectThisTime = false;
    for(auto const& [refNum, currentObject] : worldObjectsAndRefNumbersThatAreIntersectingWithAlice) //This line iterates through the map, you can think of this as for(currentObject in map)
	{
		std::vector<WorldObjectProperty> worldObjectProperties = currentObject.getProperties();
		for(int j = 0; j < worldObjectProperties.size(); j++)
		{
			if(worldObjectProperties.at(j) == WORLD_OBJECT_PROPERTY_PICKUPABLE)
			{
				hasPickedUpObjectThisTime = true;
				alice.putDownObject(groundTileMap);
				alice.pickUpObject(refNum, groundTileMap);

        		associateAliceWithCorrectAnimation(); 

				drawAllObjectsALayerAboveAlice(windowToDrawIn);
			}
		}
		if(alice.isHoldingObject())
		{
			break;
		}
	}
	if(hasPickedUpObjectThisTime == false)
	{
		alice.putDownObject(groundTileMap);

       	associateAliceWithCorrectAnimation(); 
    	alice.draw(windowToDrawIn);

		drawAllObjectsALayerAboveAlice(windowToDrawIn);
	}
	this->forceFullDraw(windowToDrawIn);
}

void FarmScreen::handleItemUseEvent(sf::RenderWindow& windowToDrawIn)
{
	if(alice.isHoldingObject())
	{
		std::pair<int, int> rowAndCol = groundTileMap.getRowAndColOfTileNearestToDrawableObject(alice);
		int rowToUseItemOn = rowAndCol.first;
		int colToUseItemOn = rowAndCol.second;
		std::vector<WorldObjectProperty> worldObjectPropertiesOfTheObjectAliceIsHolding = alice.returnPropertiesOfHeldWorldObject();
		for(int i = 0; i < worldObjectPropertiesOfTheObjectAliceIsHolding.size(); i++)
		{
			switch(worldObjectPropertiesOfTheObjectAliceIsHolding.at(i))
			{
				case WORLD_OBJECT_PROPERTY_ACTION_TILL:
					if(groundTileMap.getReferenceNumberAtIndices(rowToUseItemOn, colToUseItemOn) == TEXTURE_BANK_REF_NUMBER_IN_BOUNDS_GRASS)
					{
						groundTileMap.setTileAtIndicesToReferenceNumberAndPartialDraw(rowToUseItemOn, colToUseItemOn, TEXTURE_BANK_REF_NUMBER_UNWATERED_TILLED_DIRT, windowToDrawIn);
    	    			associateAliceWithCorrectAnimation(); 
    					alice.draw(windowToDrawIn);
						drawAllObjectsALayerAboveAlice(windowToDrawIn);
						i = worldObjectPropertiesOfTheObjectAliceIsHolding.size(); //Break out of the outer loop too.
					}
					break;
				case WORLD_OBJECT_PROPERTY_ACTION_WATERCROP:
					if(groundTileMap.getReferenceNumberAtIndices(rowToUseItemOn, colToUseItemOn) == TEXTURE_BANK_REF_NUMBER_UNWATERED_TILLED_DIRT)
					{
						groundTileMap.setTileAtIndicesToReferenceNumberAndPartialDraw(rowToUseItemOn, colToUseItemOn, TEXTURE_BANK_REF_NUMBER_WATERED_TILLED_DIRT, windowToDrawIn);
    	    			associateAliceWithCorrectAnimation(); 
    					alice.draw(windowToDrawIn);
						drawAllObjectsALayerAboveAlice(windowToDrawIn);
						i = worldObjectPropertiesOfTheObjectAliceIsHolding.size(); //Break out of the outer loop too.
					}
					break;
				case WORLD_OBJECT_PROPERTY_ACTION_PLANT_SEEDS_TOMATO:
					if((groundTileMap.getReferenceNumberAtIndices(rowToUseItemOn, colToUseItemOn) == TEXTURE_BANK_REF_NUMBER_UNWATERED_TILLED_DIRT) || (groundTileMap.getReferenceNumberAtIndices(rowToUseItemOn, colToUseItemOn) == TEXTURE_BANK_REF_NUMBER_UNWATERED_TILLED_DIRT))
					{
						plantTileMap.setTileAtIndicesToReferenceNumberAndPartialDraw(rowToUseItemOn, colToUseItemOn, TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_ONE_TEXTURE, windowToDrawIn);
    	    			associateAliceWithCorrectAnimation(); 
    					alice.draw(windowToDrawIn);
						drawAllObjectsALayerAboveAlice(windowToDrawIn);
						i = worldObjectPropertiesOfTheObjectAliceIsHolding.size(); //Break out of the outer loop too.
					}
					break;
				default:
					break;
			}
		}
	}
	else
	{
		std::map<int, WorldObject> worldObjectsAndRefNumbersThatAreIntersectingWithAlice = groundTileMap.getAllWorldObjectsWithRefNumbersWhoAreCurrentlyTriggeredByDrawableObject(alice);
    	for(auto const& [refNum, currentObject] : worldObjectsAndRefNumbersThatAreIntersectingWithAlice) //This line iterates through the map, you can think of this as for(currentObject in map)
		{
			std::vector<WorldObjectProperty> worldObjectProperties = currentObject.getProperties();
			for(int j = 0; j < worldObjectProperties.size(); j++)
			{
				switch(worldObjectProperties.at(j))
				{
					case WORLD_OBJECT_PROPERTY_ACTION_SLEEP:
						runSleepSequence();
						break;
					case WORLD_OBJECT_PROPERTY_ACTION_FILL_WATER_CONTAINER:
						runFillWaterContainerSequence();
						break;
				}
			}
		}
	}
}

void FarmScreen::runSleepSequence()
{
	printf("TODO: Sleep Sequence");
}

void FarmScreen::runFillWaterContainerSequence()
{
	printf("TODO: FillWater Sequence");
}

void FarmScreen::associateWithTexturesInBank(const TextureBank& textureBankToTakeFrom)
{
    //GROUND TILE MAP TEXTURE ASSOCIATIONS
    groundTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_OUT_OF_BOUNDS_GRASS, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_OUT_OF_BOUNDS_GRASS));
    groundTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_IN_BOUNDS_GRASS, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_IN_BOUNDS_GRASS));
    groundTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_UNWATERED_TILLED_DIRT, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_UNWATERED_TILLED_DIRT));
    groundTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_WATERED_TILLED_DIRT, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_WATERED_TILLED_DIRT));
    groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_HOE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_WORLD_OBJECT_HOE));
    groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_HOUSE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_WORLD_OBJECT_HOUSE));
    groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_WELL, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_WORLD_OBJECT_WELL));
    groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_WATERING_CAN, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_WORLD_OBJECT_WATERING_CAN));

    groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_TOMATO_SEED_PACKET_ONE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_TOMATO_SEED_PACKET_TEXTURE));
    groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_TOMATO_SEED_PACKET_TWO, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_TOMATO_SEED_PACKET_TEXTURE));
    groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_TOMATO_SEED_PACKET_THREE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_TOMATO_SEED_PACKET_TEXTURE));

    groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_CUCUMBER_SEED_PACKET_ONE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_CUCUMBER_SEED_PACKET_TEXTURE));
    groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_CUCUMBER_SEED_PACKET_TWO, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_CUCUMBER_SEED_PACKET_TEXTURE));
    groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_CUCUMBER_SEED_PACKET_THREE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_CUCUMBER_SEED_PACKET_TEXTURE));
	
    groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_CARROT_SEED_PACKET_ONE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_CARROT_SEED_PACKET_TEXTURE));
    groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_CARROT_SEED_PACKET_TWO, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_CARROT_SEED_PACKET_TEXTURE));
    groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_CARROT_SEED_PACKET_THREE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_CARROT_SEED_PACKET_TEXTURE));


	//PLANT TILE MAP TEXTURE ASSOCIATIONS
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_ONE_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_ONE_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_TWO_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_TWO_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_THREE_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_THREE_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FOUR_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FOUR_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FIVE_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FIVE_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_SIX_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_SIX_TEXTURE));

	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_ONE_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_ONE_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TWO_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TWO_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_THREE_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_THREE_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_FOUR_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_FOUR_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_FIVE_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_FIVE_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_SIX_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_SIX_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_SEVEN_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_SEVEN_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_EIGHT_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_EIGHT_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_NINE_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_NINE_TEXTURE));
    
    //ALICE TEXTURE ASSOCIATIONS
	
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_HOE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_HOE));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_WATERING_CAN, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_WATERING_CAN));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_WATERING_CAN_EMPTY, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_WATERING_CAN_EMPTY));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_SEEDS, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_SEEDS));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_SEEDS, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_SEEDS));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_SEEDS, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_SEEDS));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_CRATE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_CRATE));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_CRATE_FILLED, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_CRATE_FILLED));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_CRATE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_CRATE));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_CRATE_FILLED, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_CRATE_FILLED));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_CRATE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_CRATE));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_CRATE_FILLED, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_CRATE_FILLED));

    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_HOE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_HOE));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_WATERING_CAN, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_WATERING_CAN));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_WATERING_CAN_EMPTY, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_WATERING_CAN_EMPTY));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_TOMATO_SEEDS, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_TOMATO_SEEDS));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CUCUMBER_SEEDS, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CUCUMBER_SEEDS));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CARROT_SEEDS, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CARROT_SEEDS));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_TOMATO_CRATE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_TOMATO_CRATE));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_TOMATO_CRATE_FILLED, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_TOMATO_CRATE_FILLED));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CUCUMBER_CRATE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CUCUMBER_CRATE));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CUCUMBER_CRATE_FILLED, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CUCUMBER_CRATE_FILLED));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CARROT_CRATE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CARROT_CRATE));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CARROT_CRATE_FILLED, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CARROT_CRATE_FILLED));

    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_HOE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_HOE));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_WATERING_CAN, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_WATERING_CAN));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_WATERING_CAN_EMPTY, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_WATERING_CAN_EMPTY));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_TOMATO_SEEDS, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_TOMATO_SEEDS));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CUCUMBER_SEEDS, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CUCUMBER_SEEDS));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CARROT_SEEDS, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CARROT_SEEDS));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_TOMATO_CRATE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_TOMATO_CRATE));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_TOMATO_CRATE_FILLED, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_TOMATO_CRATE_FILLED));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CUCUMBER_CRATE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CUCUMBER_CRATE));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CUCUMBER_CRATE_FILLED, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CUCUMBER_CRATE_FILLED));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CARROT_CRATE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CARROT_CRATE));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CARROT_CRATE_FILLED, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CARROT_CRATE_FILLED));

    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_HOE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_HOE));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_WATERING_CAN, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_WATERING_CAN));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_WATERING_CAN_EMPTY, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_WATERING_CAN_EMPTY));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_TOMATO_SEEDS, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_TOMATO_SEEDS));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CUCUMBER_SEEDS, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CUCUMBER_SEEDS));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CARROT_SEEDS, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CARROT_SEEDS));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_TOMATO_CRATE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_TOMATO_CRATE));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_TOMATO_CRATE_FILLED, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_TOMATO_CRATE_FILLED));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CUCUMBER_CRATE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CUCUMBER_CRATE));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CUCUMBER_CRATE_FILLED, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CUCUMBER_CRATE_FILLED));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CARROT_CRATE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CARROT_CRATE));
    alice.associateReferenceNumberWithTexturePointer(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CARROT_CRATE_FILLED, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CARROT_CRATE_FILLED));

    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE); //SETS DEFAULT TEXTURE FOR ALICE
}

void FarmScreen::associateWithAnimationsInBank(const OAEAnimationBank& animationBankToTakeFrom)
{
    //ALICE TEXTURE ASSOCIATIONS
    alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK)));
    alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_HOE, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_HOE)));
    alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK)));
    alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_HOE, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_HOE)));
    alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK)));
    alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_HOE, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_HOE)));
    alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK)));
    alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_HOE, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_HOE)));
    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK); //SETS DEFAULT TEXTURE FOR ALICE
}

void FarmScreen::initializeWorldObjectsInGroundTileMap()
{
    WorldObject well = WorldObject(1800,1800,100,200,nullptr);
    TriggerZone wellTriggerZone = TriggerZone(1800,1800,100,200,true);
	CollisionBox wellCollisionBox = CollisionBox(1800,1800,100,100,true);
    well.attachTriggerZone(wellTriggerZone);
	well.attachCollisionBox(wellCollisionBox);
    well.setVisibility(true);
	well.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_ACTION_FILL_WATER_CONTAINER);
    groundTileMap.addWorldObjectWithReferenceNumber(WORLD_OBJECT_REF_NUMBER_WELL, well);

    WorldObject house = WorldObject(2100,1800,300,200,nullptr);
    TriggerZone houseTriggerZone = TriggerZone(2100,1800,300,200,true);
	CollisionBox houseCollisionBox = CollisionBox(2100,1800,300,100,true);
    house.attachTriggerZone(houseTriggerZone);
	house.attachCollisionBox(houseCollisionBox);
    house.setVisibility(true);
	house.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_ACTION_SLEEP);
    groundTileMap.addWorldObjectWithReferenceNumber(WORLD_OBJECT_REF_NUMBER_HOUSE, house);

    WorldObject hoe = WorldObject(1800,2100,80,80,nullptr);
    TriggerZone hoeTriggerZone = TriggerZone(1800,2100,80,80,true);
    hoe.attachTriggerZone(hoeTriggerZone);
    hoe.setVisibility(true);
	hoe.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_PICKUPABLE);
	hoe.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_ACTION_TILL);
    groundTileMap.addWorldObjectWithReferenceNumber(WORLD_OBJECT_REF_NUMBER_HOE, hoe);

    WorldObject wateringCan = WorldObject(1900,2100,80,80,nullptr);
    TriggerZone wateringCanTriggerZone = TriggerZone(1900,2100,80,80,true);
    wateringCan.attachTriggerZone(wateringCanTriggerZone);
    wateringCan.setVisibility(true);
	wateringCan.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_PICKUPABLE);
	wateringCan.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_ACTION_WATERCROP);
	wateringCan.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_CAPACITY_10);
	wateringCan.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_CURRENT_USES_LEFT_10);
    groundTileMap.addWorldObjectWithReferenceNumber(WORLD_OBJECT_REF_NUMBER_WATERING_CAN, wateringCan);

	WorldObject initialTomatoSeeds = WorldObject(1800,2000,40,40,nullptr);
	TriggerZone initialTomatoSeedsTriggerZone = TriggerZone(1800,2000,40,40,true);
    initialTomatoSeeds.attachTriggerZone(initialTomatoSeedsTriggerZone);
    initialTomatoSeeds.setVisibility(true);
	initialTomatoSeeds.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_PICKUPABLE);
	initialTomatoSeeds.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_ACTION_PLANT_SEEDS_TOMATO);
	initialTomatoSeeds.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_CAPACITY_10);
	initialTomatoSeeds.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_CURRENT_USES_LEFT_10);
    groundTileMap.addWorldObjectWithReferenceNumber(WORLD_OBJECT_REF_NUMBER_TOMATO_SEED_PACKET_ONE, initialTomatoSeeds);

	WorldObject topBorder = WorldObject(0,0,4000,500,nullptr);
	CollisionBox topBorderCollisionBox = CollisionBox(0,0,4000,500,true);
	topBorder.attachCollisionBox(topBorderCollisionBox);
	topBorder.setVisibility(false);
	groundTileMap.addWorldObjectWithReferenceNumber(WORLD_OBJECT_REF_NUMBER_TOP_BORDER_COLLISION_BOX, topBorder);

	WorldObject leftBorder = WorldObject(0,500,600,3000,nullptr);
	CollisionBox leftBorderCollisionBox = CollisionBox(0,500,600,3000,true);
	leftBorder.attachCollisionBox(leftBorderCollisionBox);
	leftBorder.setVisibility(false);
	groundTileMap.addWorldObjectWithReferenceNumber(WORLD_OBJECT_REF_NUMBER_LEFT_BORDER_COLLISION_BOX, leftBorder);

	WorldObject rightBorder = WorldObject(3500,500,500,3000,nullptr);
	CollisionBox rightBorderCollisionBox = CollisionBox(3500,500,500,3000,true);
	rightBorder.attachCollisionBox(rightBorderCollisionBox);
	rightBorder.setVisibility(false);
	groundTileMap.addWorldObjectWithReferenceNumber(WORLD_OBJECT_REF_NUMBER_RIGHT_BORDER_COLLISION_BOX, rightBorder);

	WorldObject bottomBorder = WorldObject(0,3500,4000,500,nullptr);
	CollisionBox bottomBorderCollisionBox = CollisionBox(0,3500,4000,500,true);
	bottomBorder.attachCollisionBox(bottomBorderCollisionBox);
	bottomBorder.setVisibility(false);
	groundTileMap.addWorldObjectWithReferenceNumber(WORLD_OBJECT_REF_NUMBER_BOTTOM_BORDER_COLLISION_BOX, bottomBorder);

}

void FarmScreen::forceFullDraw(sf::RenderWindow& windowToDrawIn)
{
	drawAllObjectsALayerBelowAlice(windowToDrawIn);
    alice.draw(windowToDrawIn);
	drawAllObjectsALayerAboveAlice(windowToDrawIn);
}

void FarmScreen::update(sf::Int32 millisecondsElapsedSinceLastUpdate, sf::RenderWindow& windowToDrawIn)
{
    static bool wasAliceDrawnMovingLastFrame = false;
    float aliceSpeedInTilesPerSecond = 1;
    int numberOfMillisecondsSinceLastUpdate = millisecondsElapsedSinceLastUpdate;
    if((alice.getXMovementAmount() != 0) || (alice.getYMovementAmount() != 0))
    {
        float numberOfSecondsSinceLastUpdate = ((float)numberOfMillisecondsSinceLastUpdate) / 1000.0;
        float tilesTravelledSinceLastUpdateX = numberOfSecondsSinceLastUpdate * (alice.getXMovementAmount()) * aliceSpeedInTilesPerSecond;
        float tilesTravelledSinceLastUpdateY = numberOfSecondsSinceLastUpdate * (alice.getYMovementAmount()) * aliceSpeedInTilesPerSecond;
        groundTileMap.changeCentreOffsetTileCountXByAmount(tilesTravelledSinceLastUpdateX);
        plantTileMap.changeCentreOffsetTileCountXByAmount(tilesTravelledSinceLastUpdateX);
        groundTileMap.changeCentreOffsetTileCountYByAmount(tilesTravelledSinceLastUpdateY);
        plantTileMap.changeCentreOffsetTileCountYByAmount(tilesTravelledSinceLastUpdateY);
		if(groundTileMap.returnTrueIfDrawableObjectIntersectsWithAnyCollisionBoxes(alice))
		{
        	groundTileMap.changeCentreOffsetTileCountXByAmount(-tilesTravelledSinceLastUpdateX);
        	plantTileMap.changeCentreOffsetTileCountXByAmount(-tilesTravelledSinceLastUpdateX);
        	groundTileMap.changeCentreOffsetTileCountYByAmount(-tilesTravelledSinceLastUpdateY);
        	plantTileMap.changeCentreOffsetTileCountYByAmount(-tilesTravelledSinceLastUpdateY);
		}
		drawAllObjectsALayerBelowAlice(windowToDrawIn);
        associateAliceWithCorrectAnimation(); 
        alice.drawAndUpdateSprite(windowToDrawIn, numberOfMillisecondsSinceLastUpdate);
		drawAllObjectsALayerAboveAlice(windowToDrawIn);
        wasAliceDrawnMovingLastFrame = true;
    }
    else if(wasAliceDrawnMovingLastFrame == true)
    {
		drawAllObjectsALayerBelowAlice(windowToDrawIn);
        associateAliceWithCorrectAnimation(); 
        alice.drawAndUpdateSprite(windowToDrawIn, numberOfMillisecondsSinceLastUpdate);
		drawAllObjectsALayerAboveAlice(windowToDrawIn);
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

bool FarmScreen::returnIfShouldSwitchToMainMenuScreen()
{
	return shouldSwitchToMainMenuScreenFlag;
}

void FarmScreen::acknowledgeShouldSwitchToMainMenuScreen()
{
	shouldSwitchToMainMenuScreenFlag = false;
}

void FarmScreen::associateAliceWithCorrectAnimation() //HELPER FUNCTION FOR UPDATE
{
	switch(alice.returnReferenceNumberOfHeldObject())
	{
		case WORLD_OBJECT_REF_NUMBER_HOE:
    		if(alice.getXMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_HOE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_HOE);
    		}
    		else if(alice.getXMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_HOE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_HOE);
    		}
    		else if(alice.getYMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_HOE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_HOE);
    		}
    		else if(alice.getYMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_HOE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_HOE);
    		}
    		else
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_HOE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_HOE);
    		}
			break;
		case WORLD_OBJECT_REF_NUMBER_WATERING_CAN:
    		if(alice.getXMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_WATERING_CAN);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_WATERING_CAN);
    		}
    		else if(alice.getXMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_WATERING_CAN);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_WATERING_CAN);
    		}
    		else if(alice.getYMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_WATERING_CAN);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_WATERING_CAN);
    		}
    		else if(alice.getYMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_WATERING_CAN);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_WATERING_CAN);
    		}
    		else
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_WATERING_CAN);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_WATERING_CAN);
    		}
			break;
		case WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_ONE:
    		if(alice.getXMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CUCUMBER_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CUCUMBER_CRATE);
    		}
    		else if(alice.getXMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CUCUMBER_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CUCUMBER_CRATE);
    		}
    		else if(alice.getYMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_CRATE);
    		}
    		else if(alice.getYMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CUCUMBER_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CUCUMBER_CRATE);
    		}
    		else
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_CRATE);
    		}
			break;
		case WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_TWO:
    		if(alice.getXMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CUCUMBER_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CUCUMBER_CRATE);
    		}
    		else if(alice.getXMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CUCUMBER_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CUCUMBER_CRATE);
    		}
    		else if(alice.getYMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_CRATE);
    		}
    		else if(alice.getYMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CUCUMBER_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CUCUMBER_CRATE);
    		}
    		else
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_CRATE);
    		}
			break;
		case WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_THREE:
    		if(alice.getXMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CUCUMBER_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CUCUMBER_CRATE);
    		}
    		else if(alice.getXMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CUCUMBER_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CUCUMBER_CRATE);
    		}
    		else if(alice.getYMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_CRATE);
    		}
    		else if(alice.getYMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CUCUMBER_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CUCUMBER_CRATE);
    		}
    		else
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_CRATE);
    		}
			break;
		case WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_ONE:
    		if(alice.getXMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CARROT_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CARROT_CRATE);
    		}
    		else if(alice.getXMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CARROT_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CARROT_CRATE);
    		}
    		else if(alice.getYMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_CRATE);
    		}
    		else if(alice.getYMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CARROT_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CARROT_CRATE);
    		}
    		else
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_CRATE);
    		}
			break;
		case WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_TWO:
    		if(alice.getXMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CARROT_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CARROT_CRATE);
    		}
    		else if(alice.getXMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CARROT_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CARROT_CRATE);
    		}
    		else if(alice.getYMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_CRATE);
    		}
    		else if(alice.getYMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CARROT_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CARROT_CRATE);
    		}
    		else
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_CRATE);
    		}
			break;
		case WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_THREE:
    		if(alice.getXMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CARROT_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CARROT_CRATE);
    		}
    		else if(alice.getXMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CARROT_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CARROT_CRATE);
    		}
    		else if(alice.getYMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_CRATE);
    		}
    		else if(alice.getYMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CARROT_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CARROT_CRATE);
    		}
    		else
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_CRATE);
    		}
			break;
		case WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_ONE:
    		if(alice.getXMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_TOMATO_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_TOMATO_CRATE);
    		}
    		else if(alice.getXMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_TOMATO_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_TOMATO_CRATE);
    		}
    		else if(alice.getYMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_CRATE);
    		}
    		else if(alice.getYMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_TOMATO_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_TOMATO_CRATE);
    		}
    		else
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_CRATE);
    		}
			break;
		case WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_TWO:
    		if(alice.getXMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_TOMATO_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_TOMATO_CRATE);
    		}
    		else if(alice.getXMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_TOMATO_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_TOMATO_CRATE);
    		}
    		else if(alice.getYMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_CRATE);
    		}
    		else if(alice.getYMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_TOMATO_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_TOMATO_CRATE);
    		}
    		else
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_CRATE);
    		}
			break;
		case WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_THREE:
    		if(alice.getXMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_TOMATO_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_TOMATO_CRATE);
    		}
    		else if(alice.getXMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_TOMATO_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_TOMATO_CRATE);
    		}
    		else if(alice.getYMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_CRATE);
    		}
    		else if(alice.getYMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_TOMATO_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_TOMATO_CRATE);
    		}
    		else
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_CRATE);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_CRATE);
    		}
			break;
		case WORLD_OBJECT_REF_NUMBER_CUCUMBER_SEED_PACKET_ONE:
    		if(alice.getXMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CUCUMBER_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CUCUMBER_SEEDS);
    		}
    		else if(alice.getXMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CUCUMBER_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CUCUMBER_SEEDS);
    		}
    		else if(alice.getYMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_SEEDS);
    		}
    		else if(alice.getYMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CUCUMBER_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CUCUMBER_SEEDS);
    		}
    		else
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_SEEDS);
    		}
			break;
		case WORLD_OBJECT_REF_NUMBER_CUCUMBER_SEED_PACKET_TWO:
    		if(alice.getXMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CUCUMBER_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CUCUMBER_SEEDS);
    		}
    		else if(alice.getXMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CUCUMBER_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CUCUMBER_SEEDS);
    		}
    		else if(alice.getYMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_SEEDS);
    		}
    		else if(alice.getYMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CUCUMBER_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CUCUMBER_SEEDS);
    		}
    		else
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_SEEDS);
    		}
			break;
		case WORLD_OBJECT_REF_NUMBER_CUCUMBER_SEED_PACKET_THREE:
    		if(alice.getXMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CUCUMBER_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CUCUMBER_SEEDS);
    		}
    		else if(alice.getXMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CUCUMBER_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CUCUMBER_SEEDS);
    		}
    		else if(alice.getYMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_SEEDS);
    		}
    		else if(alice.getYMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CUCUMBER_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CUCUMBER_SEEDS);
    		}
    		else
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_SEEDS);
    		}
			break;
		case WORLD_OBJECT_REF_NUMBER_CARROT_SEED_PACKET_ONE:
    		if(alice.getXMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CARROT_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CARROT_SEEDS);
    		}
    		else if(alice.getXMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CARROT_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CARROT_SEEDS);
    		}
    		else if(alice.getYMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_SEEDS);
    		}
    		else if(alice.getYMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CARROT_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CARROT_SEEDS);
    		}
    		else
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_SEEDS);
    		}
			break;
		case WORLD_OBJECT_REF_NUMBER_CARROT_SEED_PACKET_TWO:
    		if(alice.getXMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CARROT_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CARROT_SEEDS);
    		}
    		else if(alice.getXMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CARROT_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CARROT_SEEDS);
    		}
    		else if(alice.getYMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_SEEDS);
    		}
    		else if(alice.getYMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CARROT_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CARROT_SEEDS);
    		}
    		else
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_SEEDS);
    		}
			break;
		case WORLD_OBJECT_REF_NUMBER_CARROT_SEED_PACKET_THREE:
    		if(alice.getXMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CARROT_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CARROT_SEEDS);
    		}
    		else if(alice.getXMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CARROT_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CARROT_SEEDS);
    		}
    		else if(alice.getYMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_SEEDS);
    		}
    		else if(alice.getYMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CARROT_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CARROT_SEEDS);
    		}
    		else
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_SEEDS);
    		}
			break;
		case WORLD_OBJECT_REF_NUMBER_TOMATO_SEED_PACKET_ONE:
    		if(alice.getXMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_TOMATO_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_TOMATO_SEEDS);
    		}
    		else if(alice.getXMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_TOMATO_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_TOMATO_SEEDS);
    		}
    		else if(alice.getYMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_SEEDS);
    		}
    		else if(alice.getYMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_TOMATO_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_TOMATO_SEEDS);
    		}
    		else
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_SEEDS);
    		}
			break;
		case WORLD_OBJECT_REF_NUMBER_TOMATO_SEED_PACKET_TWO:
    		if(alice.getXMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_TOMATO_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_TOMATO_SEEDS);
    		}
    		else if(alice.getXMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_TOMATO_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_TOMATO_SEEDS);
    		}
    		else if(alice.getYMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_SEEDS);
    		}
    		else if(alice.getYMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_TOMATO_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_TOMATO_SEEDS);
    		}
    		else
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_SEEDS);
    		}
			break;
		case WORLD_OBJECT_REF_NUMBER_TOMATO_SEED_PACKET_THREE:
    		if(alice.getXMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_TOMATO_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_TOMATO_SEEDS);
    		}
    		else if(alice.getXMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_TOMATO_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_TOMATO_SEEDS);
    		}
    		else if(alice.getYMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_SEEDS);
    		}
    		else if(alice.getYMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_TOMATO_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_TOMATO_SEEDS);
    		}
    		else
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_SEEDS);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_SEEDS);
    		}
			break;
		case WORLD_OBJECT_REF_NUMBER_INVALID:
    		if(alice.getXMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE);
    		}
    		else if(alice.getXMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE);
    		}
    		else if(alice.getYMovementAmount() < 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE);
    		}
    		else if(alice.getYMovementAmount() > 0)
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE);
    		}
    		else
    		{
    		    alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK);
    		    alice.setCurrentTextureReferenceNumber(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE);
    		}
			break;
		default:
			break;
	}
}

void FarmScreen::loadSaveFile(const SaveFile& saveFileToLoad)
{
	if(saveFileToLoad.isEmpty())
	{
		for(unsigned int i = 0; i < saveFileToLoad.getReferenceNumberTwoDArrayRowCountGroundAndPlantTileMap(); i++)
		{
			for(unsigned int j = 0; j < saveFileToLoad.getReferenceNumberTwoDArrayColCountGroundAndPlantTileMap(); j++)
			{
    			groundTileMap.setReferenceNumberAtIndicesAndDoNotPartialDraw(i,j, saveFileToLoad.getReferenceNumberAtRowAndColGroundTileMap(i,j));
    			plantTileMap.setReferenceNumberAtIndicesAndDoNotPartialDraw(i,j, saveFileToLoad.getReferenceNumberAtRowAndColPlantTileMap(i,j));
			}
		}
	}
	else
	{
		//TODO
	}
}

void FarmScreen::drawAllObjectsALayerBelowAlice(sf::RenderWindow& windowToDrawIn) //HELPER FUNCTION FOR A LOT OF FUNCTIONS
{
    background.draw(windowToDrawIn);
    groundTileMap.draw(windowToDrawIn);
    plantTileMap.draw(windowToDrawIn);
}

void FarmScreen::drawAllObjectsALayerAboveAlice(sf::RenderWindow& windowToDrawIn) //HELPER FUNCTION FOR A LOT OF FUNCTIONS
{
    displaysTheWordDay.draw(windowToDrawIn);
    dayNumberDisplay.draw(windowToDrawIn);
    displaysAMoneySign.draw(windowToDrawIn);
    moneyDisplay.draw(windowToDrawIn);
    marketButton.draw(windowToDrawIn);
    mainMenuButton.draw(windowToDrawIn);
}
