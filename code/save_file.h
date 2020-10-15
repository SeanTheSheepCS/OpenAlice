#ifndef SAVE_FILE_H
#define SAVE_FILE_H

#include "reference_number_enums.h"

#define DEFAULT_SAVE_FILE_NUMBER_OF_COLS 40
#define DEFAULT_SAVE_FILE_NUMBER_OF_ROWS 40
#define DEFAULT_SAVE_FILE_INPASSIBLE_GRASS_BORDER_LEFTMOST_INDEX_X 5
#define DEFAULT_SAVE_FILE_INPASSIBLE_GRASS_BORDER_RIGHTMOST_INDEX_X (DEFAULT_SAVE_FILE_NUMBER_OF_COLS-5)
#define DEFAULT_SAVE_FILE_INPASSIBLE_GRASS_BORDER_TOPMOST_INDEX_Y 5
#define DEFAULT_SAVE_FILE_INPASSIBLE_GRASS_BORDER_BOTTOMMOST_INDEX_Y (DEFAULT_SAVE_FILE_NUMBER_OF_ROWS-5)

class SaveFile
{
    public:
        SaveFile();
		SaveFile(const SaveFile& other);
		~SaveFile();
		SaveFile& operator=(const SaveFile& rhs);
		bool isEmpty() const;
		int getReferenceNumberAtRowAndColGroundTileMap(unsigned int row, unsigned int col) const;
		unsigned int getReferenceNumberTwoDArrayRowCountGroundTileMap() const;
		unsigned int getReferenceNumberTwoDArrayColCountGroundTileMap() const;
    protected:
        //
    private:
		void deleteSaveFile(); //Helper function for ~SaveFile and operator=
        bool isEmptySaveFileFlag;
		int** referenceNumberTwoDArrayGroundTileMap;
		unsigned int referenceNumberTwoDArrayRowCountGroundTileMap;
		unsigned int referenceNumberTwoDArrayColCountGroundTileMap;
};

#endif
