#include "save_file.h"

SaveFile::SaveFile()
{
    isEmptySaveFileFlag = true;
	referenceNumberTwoDArrayGroundTileMap = new int*[DEFAULT_SAVE_FILE_NUMBER_OF_ROWS];
    for(unsigned int i = 0; i < DEFAULT_SAVE_FILE_NUMBER_OF_ROWS; i++)
    {
        referenceNumberTwoDArrayGroundTileMap[i] = new int[DEFAULT_SAVE_FILE_NUMBER_OF_COLS];
    }

    for(unsigned int i = 0; i < DEFAULT_SAVE_FILE_NUMBER_OF_ROWS; i++)
    {
        if(( i <= DEFAULT_SAVE_FILE_INPASSIBLE_GRASS_BORDER_TOPMOST_INDEX_Y) || ( i >= DEFAULT_SAVE_FILE_INPASSIBLE_GRASS_BORDER_BOTTOMMOST_INDEX_Y))
        {
            for(unsigned int j = 0; j < DEFAULT_SAVE_FILE_NUMBER_OF_COLS; j++)
            {
                referenceNumberTwoDArrayGroundTileMap[i][j] = TEXTURE_BANK_REF_NUMBER_OUT_OF_BOUNDS_GRASS;
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
            }
        }
    }

    this->referenceNumberTwoDArrayRowCountGroundTileMap = DEFAULT_SAVE_FILE_NUMBER_OF_ROWS;
    this->referenceNumberTwoDArrayColCountGroundTileMap = DEFAULT_SAVE_FILE_NUMBER_OF_COLS;
}

SaveFile::SaveFile(const SaveFile& other)
{
    isEmptySaveFileFlag = other.isEmptySaveFileFlag;
    referenceNumberTwoDArrayGroundTileMap = new int*[other.getReferenceNumberTwoDArrayRowCountGroundTileMap()];
    for(unsigned int i = 0; i < other.getReferenceNumberTwoDArrayRowCountGroundTileMap(); i++)
    {
        referenceNumberTwoDArrayGroundTileMap[i] = new int[other.getReferenceNumberTwoDArrayColCountGroundTileMap()];
        for(unsigned int j = 0; j < other.getReferenceNumberTwoDArrayColCountGroundTileMap(); j++)
        {
            referenceNumberTwoDArrayGroundTileMap[i][j] = other.getReferenceNumberAtRowAndColGroundTileMap(i,j);
        }
    }
    this->referenceNumberTwoDArrayRowCountGroundTileMap = other.referenceNumberTwoDArrayRowCountGroundTileMap;
    this->referenceNumberTwoDArrayColCountGroundTileMap = other.referenceNumberTwoDArrayColCountGroundTileMap;
}

SaveFile::~SaveFile()
{
    deleteSaveFile();
}

SaveFile& SaveFile::operator=(const SaveFile& rhs)
{
    deleteSaveFile();
    isEmptySaveFileFlag = rhs.isEmptySaveFileFlag;
    referenceNumberTwoDArrayGroundTileMap = new int*[rhs.getReferenceNumberTwoDArrayRowCountGroundTileMap()];
    for(unsigned int i = 0; i < rhs.getReferenceNumberTwoDArrayRowCountGroundTileMap(); i++)
    {
        referenceNumberTwoDArrayGroundTileMap[i] = new int[rhs.getReferenceNumberTwoDArrayColCountGroundTileMap()];
        for(unsigned int j = 0; j < rhs.getReferenceNumberTwoDArrayColCountGroundTileMap(); j++)
        {
            referenceNumberTwoDArrayGroundTileMap[i][j] = rhs.getReferenceNumberAtRowAndColGroundTileMap(i,j);
        }
    }
    this->referenceNumberTwoDArrayRowCountGroundTileMap = rhs.referenceNumberTwoDArrayRowCountGroundTileMap;
    this->referenceNumberTwoDArrayColCountGroundTileMap = rhs.referenceNumberTwoDArrayColCountGroundTileMap;
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

unsigned int SaveFile::getReferenceNumberTwoDArrayRowCountGroundTileMap() const
{
    return referenceNumberTwoDArrayRowCountGroundTileMap;
}

unsigned int SaveFile::getReferenceNumberTwoDArrayColCountGroundTileMap() const
{
    return referenceNumberTwoDArrayColCountGroundTileMap;
}

void SaveFile::deleteSaveFile()
{
    isEmptySaveFileFlag = true;
    for(unsigned int i = 0; i < DEFAULT_SAVE_FILE_NUMBER_OF_ROWS; i++)
    {
        delete[] referenceNumberTwoDArrayGroundTileMap[i];
    }
    delete[] referenceNumberTwoDArrayGroundTileMap;
}
