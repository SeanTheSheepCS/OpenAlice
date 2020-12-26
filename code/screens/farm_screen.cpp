#include "farm_screen.h"

#include <thread>

FarmScreen::FarmScreen(int x, int y, unsigned int width, unsigned int height): 
	OAEScreen(x, y, width, height),
	background(x, y, width, height, nullptr),
	displaysTheWordDay(x, y, (width*0.2), height*0.1, nullptr),
	dayNumberDisplay(x+(width*0.2), y, (width*0.4), height*0.1, 4),
	displaysAMoneySign(x+(width*0.6), y, (width*0.1), height*0.1, nullptr),
	moneyDisplay(x+(width*0.7), y, width*0.3, (height*0.1), 8),
	displaysTheWordSaving(x+(width*0.7), y+(height*0.9), width*0.3, height*0.1),
	mainMenuButton(x, y+(height*0.9), width*0.3, height*0.1, nullptr), 
	marketButton(x+(width*0.7), y+(height*0.9), width*0.3, height*0.1, nullptr),
	groundTileMap(x, y+(height*0.1), width, (height*0.9), 40, 40),
	plantTileMap(x, y+(height*0.1), width, (height*0.9), 40, 40),
	alice(x+(width*0.45), y+(height*0.4), width*0.1, height*0.2),
	dayNightCircle(x-(width*0.75), y-(height*0.25), width*2.5, height*2.5, nullptr)
{
	this->isSaveThreadValid = false;
	this->pathToSaveFileUsed = "";
	this->isInSleepState = false;
	this->isSaving = false;
	this->dayNightCircle.addPeriodicRotation(NUMBER_OF_MILLISECONDS_TO_SLEEP_FOR);
	this->dayNightCircle.setDegreeInterval(45.0);
	this->shouldSwitchToMainMenuScreenFlag = false;
	this->shouldSwitchToMarketScreenFlag = false;
	this->plantTileMap.setTileWidth(100);
	this->plantTileMap.setTileHeight(100);
	this->groundTileMap.setTileWidth(100);
	this->groundTileMap.setTileHeight(100);
	this->initializeWorldObjectsInGroundTileMap();
}

std::vector<unsigned char> FarmScreen::toWriteableForm()
{
	std::vector<unsigned char> returnValue;

	std::vector<unsigned char> moneyAsUnsignedCharArray = unsignedIntToUnsignedCharVector(moneyDisplay.getNumber());
	returnValue.insert(returnValue.end(), moneyAsUnsignedCharArray.begin(), moneyAsUnsignedCharArray.end());

	std::vector<unsigned char> dayAsUnsignedCharArray = unsignedIntToUnsignedCharVector(dayNumberDisplay.getNumber());
	returnValue.insert(returnValue.end(), dayAsUnsignedCharArray.begin(), dayAsUnsignedCharArray.end());

	std::vector<unsigned char> groundTileMapAsUnsignedCharArray = groundTileMap.toWriteableForm();
	returnValue.insert(returnValue.end(), groundTileMapAsUnsignedCharArray.begin(), groundTileMapAsUnsignedCharArray.end());

	std::vector<unsigned char> plantTileMapAsUnsignedCharArray = plantTileMap.toWriteableForm();
	returnValue.insert(returnValue.end(), plantTileMapAsUnsignedCharArray.begin(), plantTileMapAsUnsignedCharArray.end());

	return returnValue;
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
	std::map<WorldObjectReferenceNumber, WorldObject> worldObjectsAndRefNumbersThatAreIntersectingWithAlice = groundTileMap.getAllWorldObjectsWithRefNumbersWhoAreCurrentlyTriggeredByDrawableObject(alice);
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

				alice.associateWithCorrectAnimation();

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

		alice.associateWithCorrectAnimation();
		alice.draw(windowToDrawIn);

		drawAllObjectsALayerAboveAlice(windowToDrawIn);
	}
	this->forceFullDraw(windowToDrawIn);
}

void FarmScreen::handleItemUseEvent(sf::RenderWindow& windowToDrawIn)
{
	if(alice.isHoldingObject())
	{
		std::pair<unsigned int, unsigned int> rowAndColGroundTileMap = groundTileMap.getRowAndColOfTileNearestToDrawableObject(alice);
		std::pair<unsigned int, unsigned int> rowAndColPlantTileMap = plantTileMap.getRowAndColOfTileNearestToDrawableObject(alice);
		unsigned int rowToUseItemOnGroundTileMap = rowAndColGroundTileMap.first;
		unsigned int colToUseItemOnGroundTileMap = rowAndColGroundTileMap.second;
		unsigned int rowToUseItemOnPlantTileMap = rowAndColPlantTileMap.first;
		unsigned int colToUseItemOnPlantTileMap = rowAndColPlantTileMap.second;
		const std::vector<WorldObjectProperty> worldObjectPropertiesOfTheObjectAliceIsHolding = alice.returnPropertiesOfHeldWorldObject();
		for(int i = 0; i < worldObjectPropertiesOfTheObjectAliceIsHolding.size(); i++)
		{
			switch(worldObjectPropertiesOfTheObjectAliceIsHolding.at(i))
			{
				case WORLD_OBJECT_PROPERTY_ACTION_TILL:
					if(groundTileMap.getReferenceNumberAtIndices(rowToUseItemOnGroundTileMap, colToUseItemOnGroundTileMap) == TEXTURE_BANK_REF_NUMBER_IN_BOUNDS_GRASS)
					{
						groundTileMap.setTileAtIndicesToReferenceNumberAndPartialDraw(rowToUseItemOnGroundTileMap, colToUseItemOnGroundTileMap, TEXTURE_BANK_REF_NUMBER_UNWATERED_TILLED_DIRT, windowToDrawIn);
						alice.associateWithCorrectAnimation();
						alice.draw(windowToDrawIn);
						drawAllObjectsALayerAboveAlice(windowToDrawIn);
						i = worldObjectPropertiesOfTheObjectAliceIsHolding.size(); //Break out of the outer loop too.
					}
					break;
				case WORLD_OBJECT_PROPERTY_ACTION_WATERCROP:
					{
					    std::map<WorldObjectReferenceNumber, WorldObject> worldObjectsAndRefNumbersThatAreIntersectingWithAlice = groundTileMap.getAllWorldObjectsWithRefNumbersWhoAreCurrentlyTriggeredByDrawableObject(alice);
		                for(auto const& [refNum, currentObject] : worldObjectsAndRefNumbersThatAreIntersectingWithAlice) //This line iterates through the map, you can think of this as for(currentObject in map)
		                {
                            std::vector<WorldObjectProperty> worldObjectProperties = currentObject.getProperties();
	                        for(int j = 0; j < worldObjectProperties.size(); j++)
	                        {
	                        	switch(worldObjectProperties.at(j))
	                        	{
	                        		case WORLD_OBJECT_PROPERTY_ACTION_FILL_WATER_CONTAINER:
	                        			runFillWaterContainerSequence(windowToDrawIn);
	                        			break;
	                        	}
	                        }
	                    }
					    if(groundTileMap.getReferenceNumberAtIndices(rowToUseItemOnGroundTileMap, colToUseItemOnGroundTileMap) == TEXTURE_BANK_REF_NUMBER_UNWATERED_TILLED_DIRT)
					    {
					    	if(alice.returnFilledAmountPropertyOfHeldWorldObject() != 0)
					    	{
					    	    alice.decrementFilledAmountPropertyOfHeldWorldObject();
					    	    groundTileMap.setTileAtIndicesToReferenceNumberAndPartialDraw(rowToUseItemOnGroundTileMap, colToUseItemOnGroundTileMap, TEXTURE_BANK_REF_NUMBER_WATERED_TILLED_DIRT, windowToDrawIn);
					    	}
							alice.associateWithCorrectAnimation();
					    	alice.draw(windowToDrawIn);
					    	drawAllObjectsALayerAboveAlice(windowToDrawIn);
					    	i = worldObjectPropertiesOfTheObjectAliceIsHolding.size(); //Break out of the outer loop too.
					    }
					}
					break;
				case WORLD_OBJECT_PROPERTY_ACTION_PLANT_SEEDS_TOMATO:
					if((groundTileMap.getReferenceNumberAtIndices(rowToUseItemOnGroundTileMap, colToUseItemOnGroundTileMap) == TEXTURE_BANK_REF_NUMBER_UNWATERED_TILLED_DIRT) || (groundTileMap.getReferenceNumberAtIndices(rowToUseItemOnGroundTileMap, colToUseItemOnGroundTileMap) == TEXTURE_BANK_REF_NUMBER_WATERED_TILLED_DIRT))
					{
						if(plantTileMap.getReferenceNumberAtIndices(rowToUseItemOnPlantTileMap, colToUseItemOnPlantTileMap) == TEXTURE_BANK_REF_NUMBER_INVISIBLE)
						{
						    alice.decrementFilledAmountPropertyOfHeldWorldObject();
						    plantTileMap.setTileAtIndicesToReferenceNumberAndPartialDraw(rowToUseItemOnPlantTileMap, colToUseItemOnPlantTileMap, TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_ONE_TEXTURE, windowToDrawIn);
						}
					    alice.associateWithCorrectAnimation(); 
						alice.draw(windowToDrawIn);
						drawAllObjectsALayerAboveAlice(windowToDrawIn);
						i = worldObjectPropertiesOfTheObjectAliceIsHolding.size(); //Break out of the outer loop too.
					}
					break;
				case WORLD_OBJECT_PROPERTY_ACTION_PLANT_SEEDS_CUCUMBER:
					if((groundTileMap.getReferenceNumberAtIndices(rowToUseItemOnGroundTileMap, colToUseItemOnGroundTileMap) == TEXTURE_BANK_REF_NUMBER_UNWATERED_TILLED_DIRT) || (groundTileMap.getReferenceNumberAtIndices(rowToUseItemOnGroundTileMap, colToUseItemOnGroundTileMap) == TEXTURE_BANK_REF_NUMBER_WATERED_TILLED_DIRT))
					{
						if(plantTileMap.getReferenceNumberAtIndices(rowToUseItemOnPlantTileMap, colToUseItemOnPlantTileMap) == TEXTURE_BANK_REF_NUMBER_INVISIBLE)
						{
						    alice.decrementFilledAmountPropertyOfHeldWorldObject();
						    plantTileMap.setTileAtIndicesToReferenceNumberAndPartialDraw(rowToUseItemOnPlantTileMap, colToUseItemOnPlantTileMap, TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_ONE_TEXTURE, windowToDrawIn);
						}
					    alice.associateWithCorrectAnimation(); 
						alice.draw(windowToDrawIn);
						drawAllObjectsALayerAboveAlice(windowToDrawIn);
						i = worldObjectPropertiesOfTheObjectAliceIsHolding.size(); //Break out of the outer loop too.
					}
					break;
				case WORLD_OBJECT_PROPERTY_ACTION_PLANT_SEEDS_CARROT:
					if((groundTileMap.getReferenceNumberAtIndices(rowToUseItemOnGroundTileMap, colToUseItemOnGroundTileMap) == TEXTURE_BANK_REF_NUMBER_UNWATERED_TILLED_DIRT) || (groundTileMap.getReferenceNumberAtIndices(rowToUseItemOnGroundTileMap, colToUseItemOnGroundTileMap) == TEXTURE_BANK_REF_NUMBER_WATERED_TILLED_DIRT))
					{
						if(plantTileMap.getReferenceNumberAtIndices(rowToUseItemOnPlantTileMap, colToUseItemOnPlantTileMap) == TEXTURE_BANK_REF_NUMBER_INVISIBLE)
						{
						    alice.decrementFilledAmountPropertyOfHeldWorldObject();
						    plantTileMap.setTileAtIndicesToReferenceNumberAndPartialDraw(rowToUseItemOnPlantTileMap, colToUseItemOnPlantTileMap, TEXTURE_BANK_REF_NUMBER_CARROTS_STAGE_ONE_TEXTURE, windowToDrawIn);
						}
						alice.associateWithCorrectAnimation();
						alice.draw(windowToDrawIn);
						drawAllObjectsALayerAboveAlice(windowToDrawIn);
						i = worldObjectPropertiesOfTheObjectAliceIsHolding.size(); //Break out of the outer loop too.
					}
					break;
				case WORLD_OBJECT_PROPERTY_ACTION_HARVEST_TOMATO:
					//If the tomato is ready to be harvested...
					if((plantTileMap.getReferenceNumberAtIndices(rowToUseItemOnPlantTileMap, colToUseItemOnPlantTileMap) == TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FIVE_HARVEST_ONE_TEXTURE) || (plantTileMap.getReferenceNumberAtIndices(rowToUseItemOnPlantTileMap, colToUseItemOnPlantTileMap) == TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FIVE_HARVEST_TWO_TEXTURE))
					{
						this->runHarvestSequence(rowToUseItemOnPlantTileMap, colToUseItemOnPlantTileMap, windowToDrawIn);
					}

					break;
				case WORLD_OBJECT_PROPERTY_ACTION_HARVEST_CUCUMBER:

					//If the cucumber is ready to be harvested...
					if((plantTileMap.getReferenceNumberAtIndices(rowToUseItemOnPlantTileMap, colToUseItemOnPlantTileMap) == TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TEN_HARVEST_ONE_TEXTURE) || (plantTileMap.getReferenceNumberAtIndices(rowToUseItemOnPlantTileMap, colToUseItemOnPlantTileMap) == TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TEN_HARVEST_TWO_TEXTURE) || (plantTileMap.getReferenceNumberAtIndices(rowToUseItemOnPlantTileMap, colToUseItemOnPlantTileMap) == TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TEN_HARVEST_THREE_TEXTURE))
					{
						this->runHarvestSequence(rowToUseItemOnPlantTileMap, colToUseItemOnPlantTileMap, windowToDrawIn);
					}
					break;
				case WORLD_OBJECT_PROPERTY_ACTION_HARVEST_CARROT:
					//If the carrot is ready to be harvested...
					if((plantTileMap.getReferenceNumberAtIndices(rowToUseItemOnPlantTileMap, colToUseItemOnPlantTileMap) == TEXTURE_BANK_REF_NUMBER_CARROTS_STAGE_THREE_TEXTURE))
					{
						this->runHarvestSequence(rowToUseItemOnPlantTileMap, colToUseItemOnPlantTileMap, windowToDrawIn);
					}
					break;
				default:
					break;
			}
		}
	}
	else
	{
		std::map<WorldObjectReferenceNumber, WorldObject> worldObjectsAndRefNumbersThatAreIntersectingWithAlice = groundTileMap.getAllWorldObjectsWithRefNumbersWhoAreCurrentlyTriggeredByDrawableObject(alice);
		for(auto const& [refNum, currentObject] : worldObjectsAndRefNumbersThatAreIntersectingWithAlice) //This line iterates through the map, you can think of this as for(currentObject in map)
		{
			std::vector<WorldObjectProperty> worldObjectProperties = currentObject.getProperties();
			for(int j = 0; j < worldObjectProperties.size(); j++)
			{
				switch(worldObjectProperties.at(j))
				{
					case WORLD_OBJECT_PROPERTY_ACTION_SLEEP:
						runSleepSequence(windowToDrawIn);
						break;
					case WORLD_OBJECT_PROPERTY_ACTION_FILL_WATER_CONTAINER:
						runFillWaterContainerSequence(windowToDrawIn);
						break;
				}
			}
		}
	}
}

void FarmScreen::runHarvestSequence(unsigned int plantTileMapRow, unsigned int plantTileMapCol, sf::RenderWindow& windowToDrawIn)
{
	//Determine capacity of held object
	int capacity = alice.returnCapacityOfHeldWorldObject();
	int filled_amount = alice.returnFilledAmountPropertyOfHeldWorldObject();
	if(capacity > filled_amount)
	{
		filled_amount++;
		alice.incrementFilledAmountPropertyOfHeldWorldObject();
	    int referenceNumberAtPlantTileMapIndices = plantTileMap.getReferenceNumberAtIndices(plantTileMapRow, plantTileMapCol);
	    plantTileMap.setTileAtIndicesToReferenceNumberAndPartialDraw(plantTileMapRow, plantTileMapCol, ++referenceNumberAtPlantTileMapIndices, windowToDrawIn);
		if(filled_amount >= capacity)
		{
			switch(alice.returnReferenceNumberOfHeldObject())
			{
				case WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_ONE:
                    alice.setReferenceNumberOfHeldWorldObject(WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_ONE_FILLED);
					break;
				case WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_TWO:
                    alice.setReferenceNumberOfHeldWorldObject(WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_TWO_FILLED);
					break;
				case WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_THREE:
                    alice.setReferenceNumberOfHeldWorldObject(WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_THREE_FILLED);
					break;
				case WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_ONE:
                    alice.setReferenceNumberOfHeldWorldObject(WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_ONE_FILLED);
					break;
				case WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_TWO:
                    alice.setReferenceNumberOfHeldWorldObject(WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_TWO_FILLED);
					break;
				case WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_THREE:
                    alice.setReferenceNumberOfHeldWorldObject(WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_THREE_FILLED);
					break;
				case WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_ONE:
                    alice.setReferenceNumberOfHeldWorldObject(WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_ONE_FILLED);
					break;
				case WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_TWO:
                    alice.setReferenceNumberOfHeldWorldObject(WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_TWO_FILLED);
					break;
				case WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_THREE:
                    alice.setReferenceNumberOfHeldWorldObject(WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_THREE_FILLED);
					break;
			}
		}
	}
	alice.associateWithCorrectAnimation();
}

void FarmScreen::runSleepSequence(sf::RenderWindow& windowToDrawIn)
{
	dayNumberDisplay.incrementNumberDisplayByAmount(1);
	this->dayNightCircle.setRotationAroundCentre(180.0);
	this->isInSleepState = true;
}

void FarmScreen::runSaveProcedure()
{
	this->isSaving = true;

	std::ofstream fileToWriteSaveTo(pathToSaveFileUsed, std::ofstream::binary);
	std::ostream_iterator<unsigned char> fileToWriteSaveToIterator(fileToWriteSaveTo);

	std::vector<unsigned char> dayAsUnsignedCharArray = unsignedIntToUnsignedCharVector(dayNumberDisplay.getNumber());
	std::copy(dayAsUnsignedCharArray.begin(), dayAsUnsignedCharArray.end(), fileToWriteSaveToIterator);

	std::vector<unsigned char> moneyAsUnsignedCharArray = unsignedIntToUnsignedCharVector(moneyDisplay.getNumber());
	std::copy(moneyAsUnsignedCharArray.begin(), moneyAsUnsignedCharArray.end(), fileToWriteSaveToIterator);

	std::vector<unsigned char> groundTileMapAsUnsignedCharArray = groundTileMap.toWriteableForm();
	std::copy(groundTileMapAsUnsignedCharArray.begin(), groundTileMapAsUnsignedCharArray.end(), fileToWriteSaveToIterator);

	std::vector<unsigned char> plantTileMapAsUnsignedCharArray = plantTileMap.toWriteableForm();
	std::copy(plantTileMapAsUnsignedCharArray.begin(), plantTileMapAsUnsignedCharArray.end(), fileToWriteSaveToIterator);

	fileToWriteSaveTo.close();
	this->isSaving = false;
}

void FarmScreen::runLoadProcedure(std::string pathOfFileToLoad)
{
	this->isLoading = true;
	std::ifstream fileToReadFrom(pathOfFileToLoad, std::ifstream::binary);
	fileToReadFrom >> std::noskipws; //DO NOT REMOVE THIS LINE. This line means that if the file contains a 0x09 or a 0x0a which are considered white space, they will not be skipped over. If you omit this line both 0x09 and 0x0a and their family become 0x00! The flag noskipws means do not skip WHITESPACE. DO NOT REMOVE ME.
	std::istream_iterator<unsigned char> fileToReadFromIterator(fileToReadFrom);
	
	unsigned int day = readUnsignedIntFromUnsignedCharIterator(fileToReadFromIterator);
	dayNumberDisplay.setNumberDisplayAmount(day);
	unsigned int money = readUnsignedIntFromUnsignedCharIterator(fileToReadFromIterator);
	moneyDisplay.setNumberDisplayAmount(money);
	groundTileMap.fillWithDataFromWriteableForm(fileToReadFromIterator);
	plantTileMap.fillWithDataFromWriteableForm(fileToReadFromIterator);

	fileToReadFrom.close();
	this->isLoading = false;
}

void FarmScreen::runFillWaterContainerSequence(sf::RenderWindow& windowToDrawIn)
{
	const std::vector<WorldObjectProperty> worldObjectPropertiesOfTheObjectAliceIsHolding = alice.returnPropertiesOfHeldWorldObject();
	for(int i = 0; i < worldObjectPropertiesOfTheObjectAliceIsHolding.size(); i++)
	{
        switch(worldObjectPropertiesOfTheObjectAliceIsHolding.at(i))
		{
			case WORLD_OBJECT_PROPERTY_ACTION_WATERCROP:
				alice.fillHeldWorldObjectToCapacity();
				break;
		}
	}
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
	groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_ONE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_TOMATO_CRATE_TEXTURE));
	groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_TWO, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_TOMATO_CRATE_TEXTURE));
	groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_THREE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_TOMATO_CRATE_TEXTURE));
	groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_ONE_FILLED, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_TOMATO_CRATE_FILLED_TEXTURE));
	groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_TWO_FILLED, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_CUCUMBER_CRATE_FILLED_TEXTURE));
	groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_THREE_FILLED, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_CARROT_CRATE_FILLED_TEXTURE));

	groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_CUCUMBER_SEED_PACKET_ONE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_CUCUMBER_SEED_PACKET_TEXTURE));
	groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_CUCUMBER_SEED_PACKET_TWO, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_CUCUMBER_SEED_PACKET_TEXTURE));
	groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_CUCUMBER_SEED_PACKET_THREE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_CUCUMBER_SEED_PACKET_TEXTURE));
	groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_ONE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_CUCUMBER_CRATE_TEXTURE));
	groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_TWO, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_CUCUMBER_CRATE_TEXTURE));
	groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_THREE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_CUCUMBER_CRATE_TEXTURE));

	groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_CARROT_SEED_PACKET_ONE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_CARROT_SEED_PACKET_TEXTURE));
	groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_CARROT_SEED_PACKET_TWO, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_CARROT_SEED_PACKET_TEXTURE));
	groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_CARROT_SEED_PACKET_THREE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_CARROT_SEED_PACKET_TEXTURE));
	groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_ONE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_CARROT_CRATE_TEXTURE));
	groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_TWO, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_CARROT_CRATE_TEXTURE));
	groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_THREE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_CARROT_CRATE_TEXTURE));
	groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_ONE_FILLED, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_CARROT_CRATE_FILLED_TEXTURE));
	groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_TWO_FILLED, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_CARROT_CRATE_FILLED_TEXTURE));
	groundTileMap.associateWorldObjectWithReferenceNumberWithTexturePointer(WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_THREE_FILLED, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber((int)TEXTURE_BANK_REF_NUMBER_CARROT_CRATE_FILLED_TEXTURE));

	//PLANT TILE MAP TEXTURE ASSOCIATIONS
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_ONE_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_ONE_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_TWO_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_TWO_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_THREE_HARVEST_ONE_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_THREE_HARVEST_ONE_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FOUR_HARVEST_ONE_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FOUR_HARVEST_ONE_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FIVE_HARVEST_ONE_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FIVE_HARVEST_ONE_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FIVE_HARVESTED_ONE_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FIVE_HARVESTED_ONE_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_THREE_HARVEST_TWO_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_THREE_HARVEST_TWO_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FOUR_HARVEST_TWO_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FOUR_HARVEST_TWO_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FIVE_HARVEST_TWO_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FIVE_HARVEST_TWO_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FIVE_HARVESTED_TWO_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FIVE_HARVESTED_TWO_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_SIX_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_SIX_TEXTURE));

	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_ONE_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_ONE_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TWO_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TWO_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_THREE_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_THREE_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_FOUR_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_FOUR_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_FIVE_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_FIVE_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_SIX_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_SIX_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_SEVEN_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_SEVEN_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_EIGHT_HARVEST_ONE_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_EIGHT_HARVEST_ONE_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_NINE_HARVEST_ONE_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_NINE_HARVEST_ONE_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TEN_HARVEST_ONE_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TEN_HARVEST_ONE_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TEN_HARVESTED_ONE_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TEN_HARVESTED_ONE_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_EIGHT_HARVEST_TWO_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_EIGHT_HARVEST_TWO_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_NINE_HARVEST_TWO_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_NINE_HARVEST_TWO_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TEN_HARVEST_TWO_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TEN_HARVEST_TWO_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TEN_HARVESTED_TWO_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TEN_HARVESTED_TWO_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_EIGHT_HARVEST_THREE_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_EIGHT_HARVEST_THREE_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_NINE_HARVEST_THREE_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_NINE_HARVEST_THREE_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TEN_HARVEST_THREE_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TEN_HARVEST_THREE_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TEN_HARVESTED_THREE_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TEN_HARVESTED_THREE_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_ELEVEN_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_ELEVEN_TEXTURE));

	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CARROTS_STAGE_ONE_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CARROTS_STAGE_ONE_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CARROTS_STAGE_TWO_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CARROTS_STAGE_TWO_TEXTURE));
	plantTileMap.associateReferenceNumberWithTexture(TEXTURE_BANK_REF_NUMBER_CARROTS_STAGE_THREE_TEXTURE, textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CARROTS_STAGE_THREE_TEXTURE));
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

	//DAY NIGHT CIRCLE
	dayNightCircle.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_DAY_NIGHT_CIRCLE_TEXTURE));

	//DAY NUMBER DISPLAY AND MONEY NUMBER DISPLAY
	dayNumberDisplay.associateWithTexturesInBank(textureBankToTakeFrom);
	moneyDisplay.associateWithTexturesInBank(textureBankToTakeFrom);
	displaysTheWordDay.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_DISPLAYS_THE_WORD_DAY_TEXTURE));
	displaysAMoneySign.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_MONEY_SIGN_DISPLAY_TEXTURE));
	mainMenuButton.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_BACK_TO_MAIN_MENU_BUTTON_TEXTURE));
	marketButton.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_GO_TO_MARKET_BUTTON_TEXTURE));
}

void FarmScreen::associateWithAnimationsInBank(const OAEAnimationBank& animationBankToTakeFrom)
{
	//ALICE TEXTURE ASSOCIATIONS
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_HOE, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_HOE)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_WATERING_CAN, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_WATERING_CAN)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_WATERING_CAN_EMPTY, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_WATERING_CAN_EMPTY)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_SEEDS, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_SEEDS)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_SEEDS, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_SEEDS)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_SEEDS, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_SEEDS)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_CRATE, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_CRATE)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_CRATE_FILLED, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_CRATE_FILLED)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_CRATE, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_CRATE)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_CRATE_FILLED, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_CRATE_FILLED)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_CRATE, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_CRATE)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_CRATE_FILLED, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_CRATE_FILLED)));

	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_HOE, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_HOE)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_WATERING_CAN, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_WATERING_CAN)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_WATERING_CAN_EMPTY, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_WATERING_CAN_EMPTY)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_TOMATO_SEEDS, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_TOMATO_SEEDS)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CUCUMBER_SEEDS, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CUCUMBER_SEEDS)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CARROT_SEEDS, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CARROT_SEEDS)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_TOMATO_CRATE, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_TOMATO_CRATE)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_TOMATO_CRATE_FILLED, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_TOMATO_CRATE_FILLED)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CUCUMBER_CRATE, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CUCUMBER_CRATE)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CUCUMBER_CRATE_FILLED, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CUCUMBER_CRATE_FILLED)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CARROT_CRATE, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CARROT_CRATE)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CARROT_CRATE_FILLED, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CARROT_CRATE_FILLED)));

	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_HOE, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_HOE)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_WATERING_CAN, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_WATERING_CAN)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_WATERING_CAN_EMPTY, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_WATERING_CAN_EMPTY)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_TOMATO_SEEDS, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_TOMATO_SEEDS)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CUCUMBER_SEEDS, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CUCUMBER_SEEDS)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CARROT_SEEDS, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CARROT_SEEDS)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_TOMATO_CRATE, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_TOMATO_CRATE)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_TOMATO_CRATE_FILLED, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_TOMATO_CRATE_FILLED)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CUCUMBER_CRATE, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CUCUMBER_CRATE)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CUCUMBER_CRATE_FILLED, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CUCUMBER_CRATE_FILLED)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CARROT_CRATE, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CARROT_CRATE)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CARROT_CRATE_FILLED, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CARROT_CRATE_FILLED)));

	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_HOE, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_HOE)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_WATERING_CAN, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_WATERING_CAN)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_WATERING_CAN_EMPTY, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_WATERING_CAN_EMPTY)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_TOMATO_SEEDS, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_TOMATO_SEEDS)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CUCUMBER_SEEDS, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CUCUMBER_SEEDS)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CARROT_SEEDS, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CARROT_SEEDS)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_TOMATO_CRATE, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_TOMATO_CRATE)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_TOMATO_CRATE_FILLED, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_TOMATO_CRATE_FILLED)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CUCUMBER_CRATE, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CUCUMBER_CRATE)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CUCUMBER_CRATE_FILLED, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CUCUMBER_CRATE_FILLED)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CARROT_CRATE, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CARROT_CRATE)));
	alice.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CARROT_CRATE_FILLED, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CARROT_CRATE_FILLED)));

	alice.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK); //SETS DEFAULT TEXTURE FOR ALICE

	//SET ANIMATION FOR THE WORD SAVING
	displaysTheWordSaving.associateReferenceNumberWithAnimationInstance(ANIMATION_BANK_REF_NUMBER_SAVE_WARNING, OAEAnimationInstance(animationBankToTakeFrom.getAnimationAssociatedWithReferenceNumber(ANIMATION_BANK_REF_NUMBER_SAVE_WARNING)));

	displaysTheWordSaving.setCurrentAnimationInstanceReferenceNumber(ANIMATION_BANK_REF_NUMBER_SAVE_WARNING); //SETS THE DEFAULT TEXTURE FOR THE WORD SAVING
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
	wateringCan.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_FILLED_WITH_10);
	groundTileMap.addWorldObjectWithReferenceNumber(WORLD_OBJECT_REF_NUMBER_WATERING_CAN, wateringCan);

	WorldObject initialTomatoSeeds = WorldObject(1800,2000,40,40,nullptr);
	TriggerZone initialTomatoSeedsTriggerZone = TriggerZone(1800,2000,40,40,true);
	initialTomatoSeeds.attachTriggerZone(initialTomatoSeedsTriggerZone);
	initialTomatoSeeds.setVisibility(true);
	initialTomatoSeeds.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_PICKUPABLE);
	initialTomatoSeeds.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_ACTION_PLANT_SEEDS_TOMATO);
	initialTomatoSeeds.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_CAPACITY_10);
	initialTomatoSeeds.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_FILLED_WITH_10);
	initialTomatoSeeds.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_DELETES_WHEN_FILLED_WITH_0);
	groundTileMap.addWorldObjectWithReferenceNumber(WORLD_OBJECT_REF_NUMBER_TOMATO_SEED_PACKET_ONE, initialTomatoSeeds);

	WorldObject initialTomatoCrate = WorldObject(2000, 2100, 100, 100, nullptr);
	TriggerZone initialTomatoCrateTriggerZone = TriggerZone(2000, 2100, 100, 100, true);
	initialTomatoCrate.attachTriggerZone(initialTomatoCrateTriggerZone);
	initialTomatoCrate.setVisibility(true);
	initialTomatoCrate.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_PICKUPABLE);
	initialTomatoCrate.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_ACTION_HARVEST_TOMATO);
	initialTomatoCrate.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_CAPACITY_10);
	initialTomatoCrate.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_FILLED_WITH_0);
	groundTileMap.addWorldObjectWithReferenceNumber(WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_ONE, initialTomatoCrate);

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
	if(this->isInSleepState)
	{
		dayNightCircle.draw(windowToDrawIn);
	}
	else
	{
		drawAllObjectsALayerBelowAlice(windowToDrawIn);
		alice.draw(windowToDrawIn);
		drawAllObjectsALayerAboveAlice(windowToDrawIn);
	}

	if(this->isSaving)
	{
		displaysTheWordSaving.draw(windowToDrawIn);
	}
}

void FarmScreen::update(sf::Int32 millisecondsElapsedSinceLastUpdate, sf::RenderWindow& windowToDrawIn)
{
	static unsigned int numberOfMillisecondsPassedInSleepStateSinceLastWakeUp = 0;
	static unsigned int lastRowOfPlantTileMapUpdatedInSleepCycle = -1;

	if(this->isInSleepState)
	{
		unsigned int numberOfMillisecondsSinceLastUpdate = millisecondsElapsedSinceLastUpdate;
		unsigned int numberOfMillisecondsPassedInSleepStateSinceLastWakeUpLastIteration = numberOfMillisecondsPassedInSleepStateSinceLastWakeUp;
		numberOfMillisecondsPassedInSleepStateSinceLastWakeUp += numberOfMillisecondsSinceLastUpdate;
		dayNightCircle.draw(windowToDrawIn, numberOfMillisecondsSinceLastUpdate);
		//Change the plant tile map while Alice sleeps, row by row...
		unsigned int startRowToChangeThisFrame = lastRowOfPlantTileMapUpdatedInSleepCycle+1;
		unsigned int endRowToChangeThisFrame = startRowToChangeThisFrame + ((unsigned int)(((float)numberOfMillisecondsSinceLastUpdate) / ((float)NUMBER_OF_MILLISECONDS_TO_SLEEP_FOR)) * ((float)plantTileMap.getRowCount()));

		//If you finished early and there is nothing to do this iteration, you can start the save thread!
		if(lastRowOfPlantTileMapUpdatedInSleepCycle == plantTileMap.getRowCount() + 1)
		{
			if((this->isSaveThreadValid) == false)
			{
				this->isSaveThreadValid = true;
				this->saveThread = std::thread(&(FarmScreen::runSaveProcedure), this);
			}
		}
		if(endRowToChangeThisFrame >= plantTileMap.getRowCount())
		{
			endRowToChangeThisFrame = plantTileMap.getRowCount()+1;
		}
		lastRowOfPlantTileMapUpdatedInSleepCycle = endRowToChangeThisFrame;
		//This next line checks if we are done sleeping (if this is our last iteration)
		if(numberOfMillisecondsPassedInSleepStateSinceLastWakeUp > NUMBER_OF_MILLISECONDS_TO_SLEEP_FOR)
		{
			if(endRowToChangeThisFrame != (plantTileMap.getRowCount() - 1))
			{
				//Clean up the rows if this is the last iteration, this is our last chance!
				this->updateTheFollowingRowsInThePlantTileMapBothBoundsInclusive(endRowToChangeThisFrame+1, plantTileMap.getRowCount() - 1);
				//We need to start the save thread here too, because if it didn't finish properly, we have not saved yet!
				if((this->isSaveThreadValid) == false)
				{
					this->isSaveThreadValid = true;
					this->saveThread = std::thread(&(FarmScreen::runSaveProcedure), this);
				}
			}
			if((this->isSaveThreadValid) == true)
			{
				(this->saveThread).join();
				this->isSaveThreadValid = false;
			}
			this->isInSleepState = false;
			numberOfMillisecondsPassedInSleepStateSinceLastWakeUp = 0;
			lastRowOfPlantTileMapUpdatedInSleepCycle = -1;
		}
		else
		{
			this->updateTheFollowingRowsInThePlantTileMapBothBoundsInclusive(startRowToChangeThisFrame, endRowToChangeThisFrame);
		}
	}
	else
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
			alice.associateWithCorrectAnimation();
			alice.drawAndUpdateSprite(windowToDrawIn, numberOfMillisecondsSinceLastUpdate);
			drawAllObjectsALayerAboveAlice(windowToDrawIn);
			wasAliceDrawnMovingLastFrame = true;
		}
		else if(wasAliceDrawnMovingLastFrame == true)
		{
			drawAllObjectsALayerBelowAlice(windowToDrawIn);
			alice.associateWithCorrectAnimation();
			alice.drawAndUpdateSprite(windowToDrawIn, numberOfMillisecondsSinceLastUpdate);
			drawAllObjectsALayerAboveAlice(windowToDrawIn);
			wasAliceDrawnMovingLastFrame = false;
		}
	}

	if(this->isSaving)
	{
		displaysTheWordSaving.draw(windowToDrawIn, millisecondsElapsedSinceLastUpdate);
	}
}

void FarmScreen::updateTheFollowingRowsInThePlantTileMapBothBoundsInclusive(unsigned int lowerBound, unsigned int upperBound)
{
	if((lowerBound <= 0) || (upperBound <= 0) || (lowerBound >= plantTileMap.getRowCount()) || (upperBound >= plantTileMap.getRowCount()))
	{
		return;
	}
	for(int row = lowerBound; row <= upperBound; row++)
	{
		for(int col = 0; col < plantTileMap.getColCount(); col++)
		{
			int currentTileReferenceNumber = plantTileMap.getReferenceNumberAtIndices(row, col);
			//THIS NEXT LINE IS MESSED UP AND IS PART OF THE CAUSE OF ISSUE #14, this causes bugs when the groundTileMap and plantTileMap are not perfectly superimposted!!!!! See Issue #14 for more details. If you are reading this comment, Issue #14 is still an existing problem.
            int currentTileReferenceNumberOnTheGroundTileMap = groundTileMap.getReferenceNumberAtIndices(row, col);
			if(currentTileReferenceNumberOnTheGroundTileMap == TEXTURE_BANK_REF_NUMBER_WATERED_TILLED_DIRT)
			{
			    //THIS NEXT LINE IS MESSED UP AND IS PART OF THE CAUSE OF ISSUE #14, this causes bugs when the groundTileMap and plantTileMap are not perfectly superimposted!!!!! See Issue #14 for more details. If you are reading this comment, Issue #14 is still an existing problem.
				groundTileMap.setReferenceNumberAtIndicesAndDoNotPartialDraw(row, col, TEXTURE_BANK_REF_NUMBER_UNWATERED_TILLED_DIRT);
			    if((currentTileReferenceNumber >= TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_ONE_TEXTURE) && (currentTileReferenceNumber < TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_SIX_TEXTURE))
			    {
			    	if((currentTileReferenceNumber != TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FIVE_HARVEST_ONE_TEXTURE) &&
			    		(currentTileReferenceNumber != TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FIVE_HARVEST_TWO_TEXTURE))
			    	{
			    		plantTileMap.setReferenceNumberAtIndicesAndDoNotPartialDraw(row, col, ++currentTileReferenceNumber);
			    	}
			    }
			    else if((currentTileReferenceNumber >= TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_ONE_TEXTURE) && (currentTileReferenceNumber < TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_ELEVEN_TEXTURE))
			    {
			    	if((currentTileReferenceNumber != TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TEN_HARVEST_ONE_TEXTURE) &&
			    		(currentTileReferenceNumber != TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TEN_HARVEST_TWO_TEXTURE) &&
			    		(currentTileReferenceNumber != TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TEN_HARVEST_THREE_TEXTURE))
			    	{
			    		plantTileMap.setReferenceNumberAtIndicesAndDoNotPartialDraw(row, col, ++currentTileReferenceNumber);
			    	}
			    }
			    else if((currentTileReferenceNumber >= TEXTURE_BANK_REF_NUMBER_CARROTS_STAGE_ONE_TEXTURE) && (currentTileReferenceNumber < TEXTURE_BANK_REF_NUMBER_CARROTS_STAGE_THREE_TEXTURE))
			    {
			    	if(currentTileReferenceNumber != TEXTURE_BANK_REF_NUMBER_CARROTS_STAGE_THREE_TEXTURE)
			    	{
			    		plantTileMap.setReferenceNumberAtIndicesAndDoNotPartialDraw(row, col, ++currentTileReferenceNumber);
			    	}
			    }
			}
		}
	}
}

bool FarmScreen::returnIfShouldSwitchToMarketScreen() const
{
	return shouldSwitchToMarketScreenFlag;
}

void FarmScreen::acknowledgeShouldSwitchToMarketScreen()
{
	shouldSwitchToMarketScreenFlag = false;
}

bool FarmScreen::returnIfShouldSwitchToMainMenuScreen() const
{
	return shouldSwitchToMainMenuScreenFlag;
}

void FarmScreen::acknowledgeShouldSwitchToMainMenuScreen()
{
	shouldSwitchToMainMenuScreenFlag = false;
}

void FarmScreen::loadSaveFile(const SaveFile& saveFileToLoad)
{
	this->pathToSaveFileUsed = saveFileToLoad.getPath();
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
		runLoadProcedure(this->pathToSaveFileUsed);
	}
}

unsigned int FarmScreen::getDay() const
{
	return dayNumberDisplay.getNumber();
}

unsigned int FarmScreen::getMoneyAmount() const
{
	return moneyDisplay.getNumber();
}

void FarmScreen::setMoneyDisplayAmount(unsigned int moneyDisplayAmount)
{
	moneyDisplay.setNumberDisplayAmount(moneyDisplayAmount);
}

void FarmScreen::setDayDisplayAmount(unsigned int dayDisplayAmount)
{
	dayNumberDisplay.setNumberDisplayAmount(dayDisplayAmount);
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

