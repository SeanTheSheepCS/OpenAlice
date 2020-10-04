#include "save_file.h"

SaveFile::SaveFile()
{
    isEmptySaveFileFlag = true;
	referenceNumberTwoDArray = new int*[DEFAULT_SAVE_FILE_NUMBER_OF_ROWS];
    for(unsigned int i = 0; i < DEFAULT_SAVE_FILE_NUMBER_OF_ROWS; i++)
    {
        referenceNumberTwoDArray[i] = new int[DEFAULT_SAVE_FILE_NUMBER_OF_COLS];
    }

    for(unsigned int i = 0; i < DEFAULT_SAVE_FILE_NUMBER_OF_ROWS; i++)
    {
        if(( i <= DEFAULT_SAVE_FILE_INPASSIBLE_GRASS_BORDER_TOPMOST_INDEX_Y) || ( i >= DEFAULT_SAVE_FILE_INPASSIBLE_GRASS_BORDER_BOTTOMMOST_INDEX_Y))
        {
            for(unsigned int j = 0; j < DEFAULT_SAVE_FILE_NUMBER_OF_COLS; j++)
            {
                referenceNumberTwoDArray[i][j] = TEXTURE_BANK_REF_NUMBER_OUT_OF_BOUNDS_GRASS;
            }
        }
        else
        {
            for(unsigned int j = 0; j < DEFAULT_SAVE_FILE_NUMBER_OF_COLS; j++)
            {
                if(( j <= DEFAULT_SAVE_FILE_INPASSIBLE_GRASS_BORDER_LEFTMOST_INDEX_X) || ( j >= DEFAULT_SAVE_FILE_INPASSIBLE_GRASS_BORDER_RIGHTMOST_INDEX_X))
                {
                    referenceNumberTwoDArray[i][j] = TEXTURE_BANK_REF_NUMBER_OUT_OF_BOUNDS_GRASS;
                }
                else
                {
                    referenceNumberTwoDArray[i][j] = TEXTURE_BANK_REF_NUMBER_IN_BOUNDS_GRASS;
                } 
            }
        }
    }

    this->referenceNumberTwoDArrayRowCount = DEFAULT_SAVE_FILE_NUMBER_OF_ROWS;
    this->referenceNumberTwoDArrayColCount = DEFAULT_SAVE_FILE_NUMBER_OF_COLS;
}

SaveFile::SaveFile(const SaveFile& other)
{
    isEmptySaveFileFlag = other.isEmptySaveFileFlag;
    referenceNumberTwoDArray = new int*[other.getReferenceNumberTwoDArrayRowCount()];
    for(unsigned int i = 0; i < other.getReferenceNumberTwoDArrayRowCount(); i++)
    {
        referenceNumberTwoDArray[i] = new int[other.getReferenceNumberTwoDArrayColCount()];
        for(unsigned int j = 0; j < other.getReferenceNumberTwoDArrayColCount(); j++)
        {
            referenceNumberTwoDArray[i][j] = other.getReferenceNumberAtRowAndCol(i,j);
        }
    }
    this->referenceNumberTwoDArrayRowCount = other.referenceNumberTwoDArrayRowCount;
    this->referenceNumberTwoDArrayColCount = other.referenceNumberTwoDArrayColCount;
}

SaveFile::~SaveFile()
{
    deleteSaveFile();
}

SaveFile& SaveFile::operator=(const SaveFile& rhs)
{
    deleteSaveFile();
    isEmptySaveFileFlag = rhs.isEmptySaveFileFlag;
    referenceNumberTwoDArray = new int*[rhs.getReferenceNumberTwoDArrayRowCount()];
    for(unsigned int i = 0; i < rhs.getReferenceNumberTwoDArrayRowCount(); i++)
    {
        referenceNumberTwoDArray[i] = new int[rhs.getReferenceNumberTwoDArrayColCount()];
        for(unsigned int j = 0; j < rhs.getReferenceNumberTwoDArrayColCount(); j++)
        {
            referenceNumberTwoDArray[i][j] = rhs.getReferenceNumberAtRowAndCol(i,j);
        }
    }
    this->referenceNumberTwoDArrayRowCount = rhs.referenceNumberTwoDArrayRowCount;
    this->referenceNumberTwoDArrayColCount = rhs.referenceNumberTwoDArrayColCount;
    return *this;
}

bool SaveFile::isEmpty() const
{
	return isEmptySaveFileFlag;
}

int SaveFile::getReferenceNumberAtRowAndCol(unsigned int row, unsigned int col) const
{
    return referenceNumberTwoDArray[row][col];
}

unsigned int SaveFile::getReferenceNumberTwoDArrayRowCount() const
{
    return referenceNumberTwoDArrayRowCount;
}

unsigned int SaveFile::getReferenceNumberTwoDArrayColCount() const
{
    return referenceNumberTwoDArrayColCount;
}

void SaveFile::deleteSaveFile()
{
    isEmptySaveFileFlag = true;
    for(unsigned int i = 0; i < DEFAULT_SAVE_FILE_NUMBER_OF_ROWS; i++)
    {
        delete[] referenceNumberTwoDArray[i];
    }
    delete[] referenceNumberTwoDArray;
}
