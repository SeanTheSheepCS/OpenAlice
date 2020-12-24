#include "save_file.h"

SaveFile::SaveFile(std::string pathToSaveFile)
{
	this->pathToFile = pathToSaveFile;
	std::ifstream saveFileToReadFrom(pathToSaveFile);
	if(saveFileToReadFrom.is_open())
	{
		this->isEmptySaveFileFlag = false;
		this->loadFromSaveFile(saveFileToReadFrom);
		saveFileToReadFrom.close();
	}
	else
	{
		this->isEmptySaveFileFlag = true;
		this->loadDefaultSaveFile();
	}
}

SaveFile::SaveFile(const SaveFile& other)
{
	isEmptySaveFileFlag = other.isEmptySaveFileFlag;
	referenceNumberTwoDArrayGroundTileMap = new int*[other.getReferenceNumberTwoDArrayRowCountGroundAndPlantTileMap()];
	referenceNumberTwoDArrayPlantTileMap = new int*[other.getReferenceNumberTwoDArrayRowCountGroundAndPlantTileMap()];
	for(unsigned int i = 0; i < other.getReferenceNumberTwoDArrayRowCountGroundAndPlantTileMap(); i++)
	{
		referenceNumberTwoDArrayGroundTileMap[i] = new int[other.getReferenceNumberTwoDArrayColCountGroundAndPlantTileMap()];
		referenceNumberTwoDArrayPlantTileMap[i] = new int[other.getReferenceNumberTwoDArrayColCountGroundAndPlantTileMap()];
		for(unsigned int j = 0; j < other.getReferenceNumberTwoDArrayColCountGroundAndPlantTileMap(); j++)
		{
			referenceNumberTwoDArrayGroundTileMap[i][j] = other.getReferenceNumberAtRowAndColGroundTileMap(i,j);
			referenceNumberTwoDArrayPlantTileMap[i][j] = other.getReferenceNumberAtRowAndColPlantTileMap(i,j);
		}
	}
	this->referenceNumberTwoDArrayRowCountGroundAndPlantTileMap = other.referenceNumberTwoDArrayRowCountGroundAndPlantTileMap;
	this->referenceNumberTwoDArrayColCountGroundAndPlantTileMap = other.referenceNumberTwoDArrayColCountGroundAndPlantTileMap;
	this->pathToFile = other.pathToFile;
}

SaveFile::~SaveFile()
{
	deleteSaveFile();
}

SaveFile& SaveFile::operator=(const SaveFile& rhs)
{
	deleteSaveFile();
	isEmptySaveFileFlag = rhs.isEmptySaveFileFlag;
	referenceNumberTwoDArrayGroundTileMap = new int*[rhs.getReferenceNumberTwoDArrayRowCountGroundAndPlantTileMap()];
	referenceNumberTwoDArrayPlantTileMap = new int*[rhs.getReferenceNumberTwoDArrayRowCountGroundAndPlantTileMap()];
	for(unsigned int i = 0; i < rhs.getReferenceNumberTwoDArrayRowCountGroundAndPlantTileMap(); i++)
	{
		referenceNumberTwoDArrayGroundTileMap[i] = new int[rhs.getReferenceNumberTwoDArrayColCountGroundAndPlantTileMap()];
		referenceNumberTwoDArrayPlantTileMap[i] = new int[rhs.getReferenceNumberTwoDArrayColCountGroundAndPlantTileMap()];
		for(unsigned int j = 0; j < rhs.getReferenceNumberTwoDArrayColCountGroundAndPlantTileMap(); j++)
		{
			referenceNumberTwoDArrayGroundTileMap[i][j] = rhs.getReferenceNumberAtRowAndColGroundTileMap(i,j);
			referenceNumberTwoDArrayPlantTileMap[i][j] = rhs.getReferenceNumberAtRowAndColPlantTileMap(i,j);
		}
	}
	this->referenceNumberTwoDArrayRowCountGroundAndPlantTileMap = rhs.referenceNumberTwoDArrayRowCountGroundAndPlantTileMap;
	this->referenceNumberTwoDArrayColCountGroundAndPlantTileMap = rhs.referenceNumberTwoDArrayColCountGroundAndPlantTileMap;
	this->pathToFile = rhs.pathToFile;
	return *this;
}

bool SaveFile::isEmpty() const
{
	return isEmptySaveFileFlag;
}

int SaveFile::getReferenceNumberAtRowAndColGroundTileMap(unsigned int row, unsigned int col) const
{
	return referenceNumberTwoDArrayGroundTileMap[row][col];
}

int SaveFile::getReferenceNumberAtRowAndColPlantTileMap(unsigned int row, unsigned int col) const
{
	return referenceNumberTwoDArrayPlantTileMap[row][col];
}

unsigned int SaveFile::getReferenceNumberTwoDArrayRowCountGroundAndPlantTileMap() const
{
	return referenceNumberTwoDArrayRowCountGroundAndPlantTileMap;
}

unsigned int SaveFile::getReferenceNumberTwoDArrayColCountGroundAndPlantTileMap() const
{
	return referenceNumberTwoDArrayColCountGroundAndPlantTileMap;
}

std::string SaveFile::getPath() const
{
	return pathToFile;
}

void SaveFile::loadFromSaveFile(std::ifstream& streamFromSaveFile)
{
	//IMPLEMENTATION WAS MOVED TO FARM SCREEN BECAUSE THAT IS WHERE THE SAVING FORMAT IS ALSO SAVED. A MORE FLEXIBLE IMPLEMENTATION WOULD PUT THE SAVING AND THE LOADING IN THIS CLASS.
	loadDefaultSaveFile();
}

void SaveFile::loadDefaultSaveFile()
{
	referenceNumberTwoDArrayGroundTileMap = new int*[DEFAULT_SAVE_FILE_NUMBER_OF_ROWS];
	referenceNumberTwoDArrayPlantTileMap = new int*[DEFAULT_SAVE_FILE_NUMBER_OF_ROWS];
	for(unsigned int i = 0; i < DEFAULT_SAVE_FILE_NUMBER_OF_ROWS; i++)
	{
		referenceNumberTwoDArrayGroundTileMap[i] = new int[DEFAULT_SAVE_FILE_NUMBER_OF_COLS];
		referenceNumberTwoDArrayPlantTileMap[i] = new int[DEFAULT_SAVE_FILE_NUMBER_OF_COLS];
	}

	for(unsigned int i = 0; i < DEFAULT_SAVE_FILE_NUMBER_OF_ROWS; i++)
	{
		if(( i <= DEFAULT_SAVE_FILE_INPASSIBLE_GRASS_BORDER_TOPMOST_INDEX_Y) || ( i >= DEFAULT_SAVE_FILE_INPASSIBLE_GRASS_BORDER_BOTTOMMOST_INDEX_Y))
		{
			for(unsigned int j = 0; j < DEFAULT_SAVE_FILE_NUMBER_OF_COLS; j++)
			{
				referenceNumberTwoDArrayGroundTileMap[i][j] = TEXTURE_BANK_REF_NUMBER_OUT_OF_BOUNDS_GRASS;
				referenceNumberTwoDArrayPlantTileMap[i][j] = TEXTURE_BANK_REF_NUMBER_INVISIBLE;
			}
		}
		else
		{
			for(unsigned int j = 0; j < DEFAULT_SAVE_FILE_NUMBER_OF_COLS; j++)
			{
				if(( j <= DEFAULT_SAVE_FILE_INPASSIBLE_GRASS_BORDER_LEFTMOST_INDEX_X) || ( j >= DEFAULT_SAVE_FILE_INPASSIBLE_GRASS_BORDER_RIGHTMOST_INDEX_X))
				{
					referenceNumberTwoDArrayGroundTileMap[i][j] = TEXTURE_BANK_REF_NUMBER_OUT_OF_BOUNDS_GRASS;
				}
				else
				{
					referenceNumberTwoDArrayGroundTileMap[i][j] = TEXTURE_BANK_REF_NUMBER_IN_BOUNDS_GRASS;
				} 
				referenceNumberTwoDArrayPlantTileMap[i][j] = TEXTURE_BANK_REF_NUMBER_INVISIBLE;
			}
		}
	}
	this->referenceNumberTwoDArrayRowCountGroundAndPlantTileMap = DEFAULT_SAVE_FILE_NUMBER_OF_ROWS;
	this->referenceNumberTwoDArrayColCountGroundAndPlantTileMap = DEFAULT_SAVE_FILE_NUMBER_OF_COLS;
}

void SaveFile::deleteSaveFile()
{
	isEmptySaveFileFlag = true;
	for(unsigned int i = 0; i < DEFAULT_SAVE_FILE_NUMBER_OF_ROWS; i++)
	{
		delete[] referenceNumberTwoDArrayGroundTileMap[i];
		delete[] referenceNumberTwoDArrayPlantTileMap[i];
	}
	delete[] referenceNumberTwoDArrayGroundTileMap;
	delete[] referenceNumberTwoDArrayPlantTileMap;
	this->pathToFile = "";
}
