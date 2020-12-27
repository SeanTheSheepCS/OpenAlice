#include "tile_map.h"

TileMap::TileMap(int x, int y, unsigned int width, unsigned int height, unsigned int rowCountArg, unsigned int colCountArg): DrawableObject(x,y,width,height)
{
	this->rowCount = rowCountArg;
	this->colCount = colCountArg;
	this->setTileWidth(width/rowCount);
	this->setTileHeight(height/colCount);
	(this->centreOffsetTileCountX).float_form = 0.0f;
	(this->centreOffsetTileCountY).float_form = 0.0f;
	this->offsetToMakeScreenStartCenteredX = 0;
	this->offsetToMakeScreenStartCenteredY = 0;

	referenceNumberTwoDimensionArrayRepresentingTileMap = new int*[rowCountArg];
	for(unsigned int i = 0; i < rowCountArg; i++)
	{
		referenceNumberTwoDimensionArrayRepresentingTileMap[i] = new int[colCountArg];
	} 
}

TileMap::TileMap(int x, int y, unsigned int width, unsigned int height, unsigned int rowCountArg, unsigned int colCountArg, int** twoDArrayRepresentingTileMapArg):
	TileMap(x,y,width,height,rowCountArg,colCountArg)
{
	for(unsigned int i = 0; i < rowCountArg; i++)
	{
		for(unsigned int j = 0; j < colCountArg; j++)
		{
			referenceNumberTwoDimensionArrayRepresentingTileMap[i][j] = twoDArrayRepresentingTileMapArg[i][j];
		}
	}
}

TileMap::TileMap(const TileMap& other): DrawableObject(other.x, other.y, other.width, other.height)
{
	this->setTileWidth(other.tileWidth);
	this->setTileHeight(other.tileHeight);
	(this->centreOffsetTileCountX).float_form = other.centreOffsetTileCountX.float_form;
	(this->centreOffsetTileCountY).float_form = other.centreOffsetTileCountY.float_form;
	this->offsetToMakeScreenStartCenteredX = other.offsetToMakeScreenStartCenteredX;
	this->offsetToMakeScreenStartCenteredY = other.offsetToMakeScreenStartCenteredY;
	referenceNumberTwoDimensionArrayRepresentingTileMap = new int*[other.rowCount];
	for(unsigned int i = 0; i < rowCount; i++)
	{
		referenceNumberTwoDimensionArrayRepresentingTileMap[i] = new int[other.colCount];
	}

	for(unsigned int row = 0; row < other.rowCount; row++)
	{
		for(unsigned int col = 0; col < other.colCount; col++)
		{
			referenceNumberTwoDimensionArrayRepresentingTileMap[row][col] = other.referenceNumberTwoDimensionArrayRepresentingTileMap[row][col];
		}
	}

	this->referenceNumberToTexturePointerMap = other.referenceNumberToTexturePointerMap;
	this->rowCount = other.rowCount;
	this->colCount = other.colCount;
}

TileMap::~TileMap()
{
	deleteTileMap();
}

TileMap& TileMap::operator=(const TileMap& rhs)
{
	deleteTileMap();
	DrawableObject::operator=(rhs);
	this->setTileWidth(rhs.tileWidth);
	this->setTileHeight(rhs.tileHeight);
	(this->centreOffsetTileCountX).float_form = rhs.centreOffsetTileCountX.float_form;
	(this->centreOffsetTileCountY).float_form = rhs.centreOffsetTileCountY.float_form;
	this->offsetToMakeScreenStartCenteredX = rhs.offsetToMakeScreenStartCenteredX;
	this->offsetToMakeScreenStartCenteredY = rhs.offsetToMakeScreenStartCenteredY;
	referenceNumberTwoDimensionArrayRepresentingTileMap = new int*[rhs.rowCount];
	for(unsigned int i = 0; i < rhs.rowCount; i++)
	{
		referenceNumberTwoDimensionArrayRepresentingTileMap[i] = new int[rhs.colCount];
	}

	for(unsigned int row = 0; row < rhs.rowCount; row++)
	{
		for(unsigned int col = 0; col < rhs.colCount; col++)
		{
			referenceNumberTwoDimensionArrayRepresentingTileMap[row][col] = rhs.referenceNumberTwoDimensionArrayRepresentingTileMap[row][col];
		}
	}

	this->referenceNumberToTexturePointerMap = rhs.referenceNumberToTexturePointerMap;
	this->rowCount = rhs.rowCount;
	this->colCount = rhs.colCount;

	return (*this);
}

std::vector<unsigned char> TileMap::toWriteableForm() const
{
	std::vector<unsigned char> returnValue;

	std::vector<unsigned char> offsetToMakeScreenStartCenteredXAsUnsignedCharVector = intToUnsignedCharVector(offsetToMakeScreenStartCenteredX);
	returnValue.insert(returnValue.end(), offsetToMakeScreenStartCenteredXAsUnsignedCharVector.begin(), offsetToMakeScreenStartCenteredXAsUnsignedCharVector.end());

	std::vector<unsigned char> offsetToMakeScreenStartCenteredYAsUnsignedCharVector = intToUnsignedCharVector(offsetToMakeScreenStartCenteredY);
	returnValue.insert(returnValue.end(), offsetToMakeScreenStartCenteredYAsUnsignedCharVector.begin(), offsetToMakeScreenStartCenteredYAsUnsignedCharVector.end());

	std::vector<unsigned char> tileWidthAsUnsignedCharVector = unsignedIntToUnsignedCharVector(tileWidth);
	returnValue.insert(returnValue.end(), tileWidthAsUnsignedCharVector.begin(), tileWidthAsUnsignedCharVector.end());

	std::vector<unsigned char> tileHeightAsUnsignedCharVector = unsignedIntToUnsignedCharVector(tileHeight);
	returnValue.insert(returnValue.end(), tileHeightAsUnsignedCharVector.begin(), tileHeightAsUnsignedCharVector.end());

	std::vector<unsigned char> centreOffsetTileCountXAsUnsignedCharArray = unsignedIntToUnsignedCharVector(centreOffsetTileCountX.unsigned_int_form);
	returnValue.insert(returnValue.end(), centreOffsetTileCountXAsUnsignedCharArray.begin(), centreOffsetTileCountXAsUnsignedCharArray.end());

	std::vector<unsigned char> centreOffsetTileCountYAsUnsignedCharArray = unsignedIntToUnsignedCharVector(centreOffsetTileCountY.unsigned_int_form);
	returnValue.insert(returnValue.end(), centreOffsetTileCountYAsUnsignedCharArray.begin(), centreOffsetTileCountYAsUnsignedCharArray.end());

	std::vector<unsigned char> rowCountAsUnsignedCharArray = unsignedIntToUnsignedCharVector(rowCount);
	returnValue.insert(returnValue.end(), rowCountAsUnsignedCharArray.begin(), rowCountAsUnsignedCharArray.end());

	std::vector<unsigned char> colCountAsUnsignedCharArray = unsignedIntToUnsignedCharVector(colCount);
	returnValue.insert(returnValue.end(), colCountAsUnsignedCharArray.begin(), colCountAsUnsignedCharArray.end());

	for(unsigned int row = 0; row < rowCount; row++)
	{
		for(unsigned int col = 0; col < colCount; col++)
		{
			std::vector<unsigned char> currentReferenceNumberAsUnsignedCharArray = intToUnsignedCharVector(referenceNumberTwoDimensionArrayRepresentingTileMap[row][col]);
			returnValue.insert(returnValue.end(), currentReferenceNumberAsUnsignedCharArray.begin(), currentReferenceNumberAsUnsignedCharArray.end());
		}
	}

	//TEXTURES ARE NOT SAVED...
	
	unsigned int numberOfElementsInReferenceNumberToWorldObjectMap = 0;
	for(auto const& [refNum, currentObject] : referenceNumberToWorldObjectMap) //This line iterates through the map, you can think of this as for(currentObject in map)
	{
		numberOfElementsInReferenceNumberToWorldObjectMap++;
	}

	std::vector<unsigned char> numberOfElementsInReferenceNumberToWorldObjectReferenceMapAsUnsignedCharArray = unsignedIntToUnsignedCharVector(numberOfElementsInReferenceNumberToWorldObjectMap);
	returnValue.insert(returnValue.end(), numberOfElementsInReferenceNumberToWorldObjectReferenceMapAsUnsignedCharArray.begin(), numberOfElementsInReferenceNumberToWorldObjectReferenceMapAsUnsignedCharArray.end());

	for(auto const& [refNum, currentObject] : referenceNumberToWorldObjectMap) //This line iterates through the map, you can think of this as for(currentObject in map)
	{
		std::vector<unsigned char> refNumAsUnsignedCharArray = intToUnsignedCharVector((int)refNum);
		returnValue.insert(returnValue.end(), refNumAsUnsignedCharArray.begin(), refNumAsUnsignedCharArray.end());

		std::vector<unsigned char> currentObjectAsUnsignedCharArray = currentObject.toWriteableForm();
		returnValue.insert(returnValue.end(), currentObjectAsUnsignedCharArray.begin(), currentObjectAsUnsignedCharArray.end());
	}

	return returnValue;
}

void TileMap::fillWithDataFromWriteableForm(std::istream_iterator<unsigned char>& writeableFormIterator)
{
	this->offsetToMakeScreenStartCenteredX = readIntFromUnsignedCharIterator(writeableFormIterator);
	this->offsetToMakeScreenStartCenteredY = readIntFromUnsignedCharIterator(writeableFormIterator);
	this->tileWidth = readIntFromUnsignedCharIterator(writeableFormIterator);
	this->tileHeight = readIntFromUnsignedCharIterator(writeableFormIterator);
	this->centreOffsetTileCountX.unsigned_int_form = readIntFromUnsignedCharIterator(writeableFormIterator);
	this->centreOffsetTileCountY.unsigned_int_form = readIntFromUnsignedCharIterator(writeableFormIterator);

	for(unsigned int i = 0; i < this->rowCount; i++)
	{
		delete[] referenceNumberTwoDimensionArrayRepresentingTileMap[i];
	}
	delete[] referenceNumberTwoDimensionArrayRepresentingTileMap;

	this->rowCount = readUnsignedIntFromUnsignedCharIterator(writeableFormIterator);
	this->colCount = readUnsignedIntFromUnsignedCharIterator(writeableFormIterator);

	referenceNumberTwoDimensionArrayRepresentingTileMap = new int*[rowCount];
	for(unsigned int i = 0; i < this->rowCount; i++)
	{
		referenceNumberTwoDimensionArrayRepresentingTileMap[i] = new int[colCount];
	}

	for(unsigned int row = 0; row < rowCount; row++)
	{
		for(unsigned int col = 0; col < colCount; col++)
		{
			referenceNumberTwoDimensionArrayRepresentingTileMap[row][col] = readIntFromUnsignedCharIterator(writeableFormIterator);
		}
	}

	//TEXTURES ARE NOT LOADED...
	
	referenceNumberToWorldObjectMap.clear();
	unsigned int numberOfElementsInReferenceNumberToWorldObjectMap = readUnsignedIntFromUnsignedCharIterator(writeableFormIterator);
	for(unsigned int worldObjectCount = 0; worldObjectCount < numberOfElementsInReferenceNumberToWorldObjectMap; worldObjectCount++)
	{
		WorldObjectReferenceNumber referenceNumber = (WorldObjectReferenceNumber)readIntFromUnsignedCharIterator(writeableFormIterator);
		WorldObject elementToInsert = WorldObject();
		elementToInsert.fillWithDataFromWriteableForm(writeableFormIterator);
		referenceNumberToWorldObjectMap.insert(std::pair<WorldObjectReferenceNumber,WorldObject>(referenceNumber,elementToInsert));
	}
}

void TileMap::associateReferenceNumberWithTexture(int referenceNumber, const sf::Texture* texture)
{
	if(referenceNumberToTexturePointerMap.count(referenceNumber) == 1)
	{
		referenceNumberToTexturePointerMap.erase(referenceNumber);
	}
	referenceNumberToTexturePointerMap.insert(std::pair<int, const sf::Texture*>(referenceNumber, texture));
}

void TileMap::deassociateTextureWithSpecificReferenceNumber(int referenceNumber)
{
	referenceNumberToTexturePointerMap.erase(referenceNumber);
}

void TileMap::addWorldObjectWithReferenceNumber(WorldObjectReferenceNumber referenceNumber, WorldObject objectToAdd)
{
	/* HIGHLY EXPERIMENTAL, UNCOMMENT FOR WEIRDNESS 

	   for(auto const& [refNum, currentObject] : referenceNumberToWorldObjectMap) //This line iterates through the map, you can think of this as for(currentObject in map)
	   {
	   currentObject.pushDrawableObjectOutOfCollisionZoneIfItIntersects(objectToAdd);
	   }
	   */
	if(referenceNumberToWorldObjectMap.count(referenceNumber) == 1)
	{
		referenceNumberToWorldObjectMap.erase(referenceNumber);
	}
	referenceNumberToWorldObjectMap.insert(std::pair<WorldObjectReferenceNumber, WorldObject>(referenceNumber, objectToAdd));
}

void TileMap::addWorldObjectWithReferenceNumber(WorldObjectReferenceNumber referenceNumber, WorldObject objectToAdd, int screenX, int screenY)
{
	int worldX = screenXToWorldX(screenX);
	int worldY = screenYToWorldY(screenY);
	objectToAdd.setX(worldX);
	objectToAdd.setY(worldY);
	this->addWorldObjectWithReferenceNumber(referenceNumber, objectToAdd);
}

void TileMap::removeWorldObjectWithReferenceNumber(WorldObjectReferenceNumber referenceNumber)
{
	referenceNumberToWorldObjectMap.erase(referenceNumber);
}

void TileMap::associateWorldObjectWithReferenceNumberWithTexturePointer(WorldObjectReferenceNumber referenceNumber, const sf::Texture* texturePointer)
{
	try
	{
		referenceNumberToWorldObjectMap.at(referenceNumber).associateWithNewTexture(texturePointer);
	}
	catch(std::exception& e)
	{
		std::cout << "failed to access referencenumber " << referenceNumber << " in tilemap referencenumbertoworldobjectmap." << std::endl;
	}
}

void TileMap::deassociateWorldObjectWithReferenceNumberWithItsTexturePointer(WorldObjectReferenceNumber referenceNumber)
{
	try
	{
		referenceNumberToWorldObjectMap.at(referenceNumber).decoupleObjectFromItsTexture();
	}
	catch(std::exception& e)
	{
		std::cout << "Failed to access referenceNumber " << referenceNumber << " in TileMap referenceNumberToWorldObjectMap." << std::endl;
	}
}

WorldObject TileMap::getWorldObjectWithReferenceNumber(WorldObjectReferenceNumber referenceNumber)
{
	try
	{
		return referenceNumberToWorldObjectMap.at(referenceNumber);
	}
	catch(std::exception& e)
	{
		std::cout << "failed to access referencenumber " << referenceNumber << " in tilemap referencenumbertoworldobjectmap." << std::endl;
		return WorldObject();
	}
}

void TileMap::setTileAtIndicesToReferenceNumberAndPartialDraw(unsigned int row, unsigned int col, int referenceNumber, sf::RenderWindow& windowToPartialDrawIn)
{
	if((row >= 0) && (row < rowCount) && (col >= 0) && (col <= colCount))
	{
		referenceNumberTwoDimensionArrayRepresentingTileMap[row][col] = referenceNumber;
		drawTileAtRowAndColInWindow(row, col, windowToPartialDrawIn);
		drawWorldObjects(windowToPartialDrawIn);
	}
	else
	{
		std::cout << "Bad request: writing to row " << row << " and col " << col << " in an array with " << rowCount << " rows and " << colCount << " columns." << std::endl;
	}
}

void TileMap::setReferenceNumberAtIndicesAndDoNotPartialDraw(unsigned int row, unsigned int col, int referenceNumber)
{
	if((row >= 0) && (row < rowCount) && (col >= 0) && (col <= colCount))
	{
		referenceNumberTwoDimensionArrayRepresentingTileMap[row][col] = referenceNumber;
	}
	else
	{
		std::cout << "Bad request: writing to row " << row << " and col " << col << " in an array with " << rowCount << " rows and " << colCount << " columns." << std::endl;
	}
}

int TileMap::getReferenceNumberAtIndices(unsigned int row, unsigned int col)
{
	if((row >= 0) && (row < rowCount) && (col >= 0) && (col <= colCount))
	{
		return referenceNumberTwoDimensionArrayRepresentingTileMap[row][col];
	}
	{
		std::cout << "Bad request: reading from row " << row << " and col " << col << " in an array with " << rowCount << " rows and " << colCount << " columns." << std::endl;
	}
}

void TileMap::setTileWidth(int tileWidthArg)
{
	this->tileWidth = tileWidthArg;
	int totalLengthOfAllTilesX = (tileWidthArg * (this->rowCount));
	this->offsetToMakeScreenStartCenteredX = (totalLengthOfAllTilesX - width) / 2;
}

void TileMap::setTileHeight(int tileHeightArg)
{
	this->tileHeight = tileHeightArg;
	int totalLengthOfAllTilesY = (tileHeightArg * (this->colCount));
	this->offsetToMakeScreenStartCenteredY = (totalLengthOfAllTilesY - height) / 2;
}

void TileMap::setCentreOffsetTileCountX(float newCentreOffsetTileCountX)
{
	(this->centreOffsetTileCountX).float_form = newCentreOffsetTileCountX;
}

void TileMap::setCentreOffsetTileCountY(float newCentreOffsetTileCountY)
{
	(this->centreOffsetTileCountY).float_form = newCentreOffsetTileCountY;
}

void TileMap::changeCentreOffsetTileCountXByAmount(float amountToChangeCentreOffsetTileCountXBy)
{
	(this->centreOffsetTileCountX).float_form = ((this->centreOffsetTileCountX).float_form) + amountToChangeCentreOffsetTileCountXBy;
}

void TileMap::changeCentreOffsetTileCountYByAmount(float amountToChangeCentreOffsetTileCountYBy)
{
	((this->centreOffsetTileCountY).float_form) = ((this->centreOffsetTileCountY).float_form) + amountToChangeCentreOffsetTileCountYBy;
}

void TileMap::draw(sf::RenderWindow& windowToDrawIn)
{
	for(int row = 0; row < rowCount; row++)
	{
		for(int col = 0; col < colCount; col++)
		{
			drawTileAtRowAndColInWindow(row, col, windowToDrawIn);
		}
	}
	drawWorldObjects(windowToDrawIn);
}

void TileMap::deleteTileMap() //Helper function for ~TileMap() and TileMap& operator=(...)
{
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
	this->tileWidth = 0;
	this->tileHeight = 0;
	(this->centreOffsetTileCountX).float_form = 0.0f;
	(this->centreOffsetTileCountY).float_form = 0.0f;
	this->offsetToMakeScreenStartCenteredX = 0;
	this->offsetToMakeScreenStartCenteredY = 0;
	for(unsigned int i = 0; i < rowCount; i++)
	{
		delete[] referenceNumberTwoDimensionArrayRepresentingTileMap[i];
	}
	delete[] referenceNumberTwoDimensionArrayRepresentingTileMap;
	this->rowCount = 0;
	this->colCount = 0;
	this->referenceNumberToTexturePointerMap.clear();
}

void TileMap::drawTileAtRowAndColInWindow(int row, int col, sf::RenderWindow& windowToDrawIn)
{
	if(getReferenceNumberAtIndices(row, col) != 0)
	{
		int tileX = worldXToScreenX(tileWidth*row);
		int tileY = worldYToScreenY(tileHeight*col);
		if( (tileX >= (x-(tileWidth))) && (tileX <= (x + ((int)width))) && (tileY >= (y-(2*tileHeight))) && (tileY <= (y + ((int)height))))
		{
			const sf::Texture* textureToUse = referenceNumberToTexturePointerMap[getReferenceNumberAtIndices(row, col)];
			TexturedObject objectToDraw = TexturedObject(tileX, tileY, tileWidth, tileHeight, textureToUse);
			objectToDraw.draw(windowToDrawIn);
		}
	}
}

void TileMap::drawWorldObjects(sf::RenderWindow& windowToDrawIn) //Helper function for draw(...)
{
	for(auto const& [refNum, currentObject] : referenceNumberToWorldObjectMap) //This line iterates through the map, you can think of this as for(currentObject in map)
	{
		if(currentObject.getVisibility() == true)
		{
			int screenX = worldXToScreenX(currentObject.getX());
			int screenY = worldYToScreenY(currentObject.getY());
			if((screenX >= (x- ((int)currentObject.getWidth()))) && (screenX <= (x + ((int)width))) && (screenY >= (y - ((int)currentObject.getHeight()))) && (screenY <= (y + ((int)height))))
			{
				WorldObject worldObjectWithFakeCoords = WorldObject(screenX, screenY, currentObject.getWidth(), currentObject.getHeight(), currentObject.getCurrentTexturePointer());
				worldObjectWithFakeCoords.draw(windowToDrawIn);
			}
		}
	}
}

std::map<WorldObjectReferenceNumber, WorldObject> TileMap::getAllWorldObjectsWithRefNumbersWhoAreCurrentlyTriggeredByDrawableObject(const DrawableObject& objectToCheck)
{
	std::map<WorldObjectReferenceNumber, WorldObject> returnValue;
	for(auto const& [refNum, currentObject] : referenceNumberToWorldObjectMap) //This line iterates through the map, you can think of this as for(currentObject in map)
	{
		int screenX = worldXToScreenX(currentObject.getX());
		int screenY = worldYToScreenY(currentObject.getY());
		WorldObject worldObjectWithFakeCoords = currentObject;
		worldObjectWithFakeCoords.setX(screenX);
		worldObjectWithFakeCoords.setTriggerZoneX(screenX);
		worldObjectWithFakeCoords.setY(screenY);
		worldObjectWithFakeCoords.setTriggerZoneY(screenY);
		if(worldObjectWithFakeCoords.isDrawableObjectWithinTriggerZone(objectToCheck) == true)
		{
			returnValue.insert(std::pair<WorldObjectReferenceNumber, WorldObject>(refNum, currentObject));
		}
	}
	return returnValue;
}

bool TileMap::returnTrueIfDrawableObjectIntersectsWithAnyCollisionBoxes(const DrawableObject& objectToCheck)
{
	for(auto const& [refNum, currentObject] : referenceNumberToWorldObjectMap) //This line iterates through the map, you can think of this as for(currentObject in map)
	{
		int screenX = worldXToScreenX(currentObject.getX());
		int screenY = worldYToScreenY(currentObject.getY());
		WorldObject worldObjectWithFakeCoords = currentObject;
		worldObjectWithFakeCoords.setX(screenX);
		worldObjectWithFakeCoords.setCollisionBoxX(screenX);
		worldObjectWithFakeCoords.setY(screenY);
		worldObjectWithFakeCoords.setCollisionBoxY(screenY);
		if(worldObjectWithFakeCoords.isDrawableObjectWithinCollisionBox(objectToCheck) == true)
		{
			return true;
		}
	}
	return false;
}

std::pair<unsigned int, unsigned int> TileMap::getRowAndColOfTileNearestToDrawableObject(const DrawableObject& objectToCheckProximityOfInScreenCoordinates)
{
	std::pair<unsigned int, unsigned int> returnValue;

	int objectWorldCentreX = screenXToWorldX(objectToCheckProximityOfInScreenCoordinates.getX());
	int objectWorldCentreY = screenYToWorldY(objectToCheckProximityOfInScreenCoordinates.getY());

	float exactTileRow = ((float)objectWorldCentreX)/((float)tileHeight);
	float exactTileCol = ((float)objectWorldCentreY)/((float)tileWidth);

	returnValue.first = roundFloat(exactTileRow);
	returnValue.second = roundFloat(exactTileCol);
	return returnValue;
}

int TileMap::screenXToWorldX(int screenX)
{
	return -x + screenX - (((float) tileWidth)*(centreOffsetTileCountX.float_form)) + this->offsetToMakeScreenStartCenteredX;
}
int TileMap::worldXToScreenX(int worldX)
{
	return x + worldX + (((float) tileWidth)*(centreOffsetTileCountX.float_form)) - this->offsetToMakeScreenStartCenteredX;
}

int TileMap::screenYToWorldY(int screenY)
{
	return -y + screenY - (((float) tileHeight)*(centreOffsetTileCountY.float_form)) + this->offsetToMakeScreenStartCenteredY;
}

int TileMap::worldYToScreenY(int worldY)
{
	return y + worldY + (((float) tileHeight)*(centreOffsetTileCountY.float_form)) - this->offsetToMakeScreenStartCenteredY;
}

unsigned int TileMap::getRowCount()
{
	return rowCount;
}

unsigned int TileMap::getColCount()
{
	return colCount;
}

int TileMap::roundFloat(float floatToRound) //Helper function for getRowAndColOfTileNearestToDrawableObject(...)
{
	int bottomRoundingNumber = (int)floatToRound;
	int topRoundingNumber = ((int)floatToRound)+1;
	if((floatToRound - 0.5) < bottomRoundingNumber)
	{
		return bottomRoundingNumber;
	}
	else
	{
		return topRoundingNumber;
	}
}
