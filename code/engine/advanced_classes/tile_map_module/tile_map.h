#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../../primitive_classes/drawable_object.h"
#include "../../primitive_classes/textured_object.h"
#include "../../primitive_classes/world_object.h"

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

        //FOR ADDING AND REMOVING AND MANIPULATING WORLD OBJECTS
        void addWorldObjectWithReferenceNumber(int referenceNumber, WorldObject objectToAdd);
        void addWorldObjectWithReferenceNumber(int referenceNumber, WorldObject objectToAdd, int screenX, int screenY);
        void removeWorldObjectWithReferenceNumber(int referenceNumber);
        void associateWorldObjectWithReferenceNumberWithTexturePointer(int referenceNumber, const sf::Texture* texturePointer);
        void deassociateWorldObjectWithReferenceNumberWithItsTexturePointer(int referenceNumber);
        WorldObject getWorldObjectWithReferenceNumber(int referenceNumber);

		//SPECIAL FUNCTIONS
        void draw(sf::RenderWindow& windowToDrawIn);
		std::map<int, WorldObject> getAllWorldObjectsWithRefNumbersWhoAreCurrentlyTriggeredByDrawableObject(const DrawableObject& objectToCheck);
		bool returnTrueIfDrawableObjectIntersectsWithAnyCollisionBoxes(const DrawableObject& objectTocheck);
    protected:
	    //
    private:
        void deleteTileMap(); //Helper function for ~TileMap() and TileMap& operator=(...)

        void drawTileAtRowAndColInWindow(int row, int col, sf::RenderWindow& windowToDrawIn); //Helper function for draw(...) and setTileAtIndicesToReferenceNumberAndPartialDraw(...).
        void drawWorldObjects(sf::RenderWindow& windowToDrawIn); //Helper function for draw(...)

        int offsetToMakeScreenStartCenteredX;
        int offsetToMakeScreenStartCenteredY;
        int tileWidth;
        int tileHeight;

        float centreOffsetTileCountX;
        float centreOffsetTileCountY;

        int rowCount;
        int colCount;
    	int** referenceNumberTwoDimensionArrayRepresentingTileMap;
        std::map<int, const sf::Texture*> referenceNumberToTexturePointerMap;

    	std::map<int, WorldObject> referenceNumberToWorldObjectMap;
};

#endif
