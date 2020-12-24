#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>
#include "../../primitive_classes/drawable_object.h"
#include "../../primitive_classes/textured_object.h"
#include "../../primitive_classes/world_object.h"
#include "../../utilities/utilities.h"
#include "../../../reference_number_enums.h"

union ufloat 
{
	float float_form;
	unsigned int unsigned_int_form;
};

class TileMap: public DrawableObject
{
	public:
		//CONSTRUCTORS AND DESTRUCTORS
		TileMap(int x, int y, unsigned int width, unsigned int height, unsigned int rowCount, unsigned int colCount);
		TileMap(int x, int y, unsigned int width, unsigned int height, unsigned int rowCount, unsigned int colCount, int** twoDArrayRepresentingTileMapArg);
		TileMap(const TileMap& other);
		~TileMap();

		//OPERATOR OVERLOADS
		TileMap& operator=(const TileMap& rhs);

		//FOR READING AND WRITING TILEMAPS TO FILES
		std::vector<unsigned char> toWriteableForm() const;
		void fillWithDataFromWriteableForm(std::istream_iterator<unsigned char>& writeableFormIterator);

		//FOR ASSOCIATING AND DEASSOCIATING TEXTURES
		void associateReferenceNumberWithTexture(int referenceNumber, const sf::Texture* texture);
		void deassociateTextureWithSpecificReferenceNumber(int referenceNumber);

		//FOR WRITING/READING AT INDICES
		void setTileAtIndicesToReferenceNumberAndPartialDraw(unsigned int row, unsigned int col, int referenceNumber, sf::RenderWindow& windowToPartialDrawIn);
		int getReferenceNumberAtIndices(unsigned int row, unsigned int col);
		void setReferenceNumberAtIndicesAndDoNotPartialDraw(unsigned int row, unsigned int col, int referenceNumber);

		//FOR CHANGING THE VIEW SETTINGS
		void setTileWidth(int tileWidth);
		void setTileHeight(int tileHeight);
		void setCentreOffsetTileCountX(float newCentreOffsetTileCountX);
		void setCentreOffsetTileCountY(float newCentreOffsetTileCountY);
		void changeCentreOffsetTileCountXByAmount(float amountToChangeCentreOffsetTileCountXBy);
		void changeCentreOffsetTileCountYByAmount(float amountToChangeCentreOffsetTileCountYBy);

		//FOR ADDING AND REMOVING AND MANIPULATING WORLD OBJECTS USING THE MAP
		void addWorldObjectWithReferenceNumber(WorldObjectReferenceNumber referenceNumber, WorldObject objectToAdd);
		void addWorldObjectWithReferenceNumber(WorldObjectReferenceNumber referenceNumber, WorldObject objectToAdd, int screenX, int screenY);
		void removeWorldObjectWithReferenceNumber(WorldObjectReferenceNumber referenceNumber);
		void associateWorldObjectWithReferenceNumberWithTexturePointer(WorldObjectReferenceNumber referenceNumber, const sf::Texture* texturePointer);
		void deassociateWorldObjectWithReferenceNumberWithItsTexturePointer(WorldObjectReferenceNumber referenceNumber);
		WorldObject getWorldObjectWithReferenceNumber(WorldObjectReferenceNumber referenceNumber);

		//FUNCTIONS FOR COORDINATE CONVERSIONS
		int screenXToWorldX(int screenX);
		int worldXToScreenX(int worldX);
		int screenYToWorldY(int screenY);
		int worldYToScreenY(int worldY);

		//GETTERS
		unsigned int getRowCount();
		unsigned int getColCount();

		//SPECIAL FUNCTIONS
		void draw(sf::RenderWindow& windowToDrawIn);
		std::map<WorldObjectReferenceNumber, WorldObject> getAllWorldObjectsWithRefNumbersWhoAreCurrentlyTriggeredByDrawableObject(const DrawableObject& objectToCheck);
		bool returnTrueIfDrawableObjectIntersectsWithAnyCollisionBoxes(const DrawableObject& objectTocheck);
		std::pair<unsigned int, unsigned int> getRowAndColOfTileNearestToDrawableObject(const DrawableObject& objectToCheckProximityOf);

	protected:
		// 
	private:
		void deleteTileMap(); //Helper function for ~TileMap() and TileMap& operator=(...)

		void drawTileAtRowAndColInWindow(int row, int col, sf::RenderWindow& windowToDrawIn); //Helper function for draw(...) and setTileAtIndicesToReferenceNumberAndPartialDraw(...).
		void drawWorldObjects(sf::RenderWindow& windowToDrawIn); //Helper function for draw(...)
		int roundFloat(float floatToRound); //Helper function for getRowAndColOfTileNearestToDrawableObject(...)

		int offsetToMakeScreenStartCenteredX;
		int offsetToMakeScreenStartCenteredY;
		int tileWidth;
		int tileHeight;

		ufloat centreOffsetTileCountX;
		ufloat centreOffsetTileCountY;

		unsigned int rowCount;
		unsigned int colCount;
		int** referenceNumberTwoDimensionArrayRepresentingTileMap;
		std::map<int, const sf::Texture*> referenceNumberToTexturePointerMap;

		std::map<WorldObjectReferenceNumber, WorldObject> referenceNumberToWorldObjectMap;
};

#endif
