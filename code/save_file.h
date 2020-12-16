#ifndef SAVE_FILE_H
#define SAVE_FILE_H

#include "reference_number_enums.h"
#include <string>
#include <fstream>

#define DEFAULT_SAVE_FILE_NUMBER_OF_COLS 40
#define DEFAULT_SAVE_FILE_NUMBER_OF_ROWS 40
#define DEFAULT_SAVE_FILE_INPASSIBLE_GRASS_BORDER_LEFTMOST_INDEX_X 5
#define DEFAULT_SAVE_FILE_INPASSIBLE_GRASS_BORDER_RIGHTMOST_INDEX_X (DEFAULT_SAVE_FILE_NUMBER_OF_COLS-5)
#define DEFAULT_SAVE_FILE_INPASSIBLE_GRASS_BORDER_TOPMOST_INDEX_Y 5
#define DEFAULT_SAVE_FILE_INPASSIBLE_GRASS_BORDER_BOTTOMMOST_INDEX_Y (DEFAULT_SAVE_FILE_NUMBER_OF_ROWS-5)

class SaveFile
{
	public:
		SaveFile(std::string pathToSaveFile);
		SaveFile(const SaveFile& other);
		~SaveFile();
		SaveFile& operator=(const SaveFile& rhs);
		bool isEmpty() const;
		std::string getPath() const;
		int getReferenceNumberAtRowAndColGroundTileMap(unsigned int row, unsigned int col) const;
		int getReferenceNumberAtRowAndColPlantTileMap(unsigned int row, unsigned int col) const;
		unsigned int getReferenceNumberTwoDArrayRowCountGroundAndPlantTileMap() const;
		unsigned int getReferenceNumberTwoDArrayColCountGroundAndPlantTileMap() const;
	protected:
		//
	private:
		void loadFromSaveFile(std::ifstream& streamFromSaveFile);
		void loadDefaultSaveFile();

		void deleteSaveFile(); //Helper function for ~SaveFile and operator=
		bool isEmptySaveFileFlag;
		int** referenceNumberTwoDArrayGroundTileMap;
		int** referenceNumberTwoDArrayPlantTileMap;
		unsigned int referenceNumberTwoDArrayRowCountGroundAndPlantTileMap;
		unsigned int referenceNumberTwoDArrayColCountGroundAndPlantTileMap;
		std::string pathToFile;
};

#endif
