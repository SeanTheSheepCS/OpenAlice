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

        //FOR CHANGING THE VIEW SETTINGS
        void setTileWidth(int tileWidth);
        void setTileHeight(int tileHeight);
        void setCentreOffsetTileCountX(float newCentreOffsetTileCountX);
        void setCentreOffsetTileCountY(float newCentreOffsetTileCountY);
        void changeCentreOffsetTileCountXByAmount(float amountToChangeCentreOffsetTileCountXBy);
        void changeCentreOffsetTileCountYByAmount(float amountToChangeCentreOffsetTileCountYBy);

        //FOR ADDING AND REMOVING WORLD OBJECTS
        void addWorldObjectWithReferenceNumber(int referenceNumber, WorldObject objectToAdd);
        void removeWorldObjectWithReferenceNumber(int referenceNumber);

        //DRAW FUNCTION
        void draw(sf::RenderWindow& windowToDrawIn);
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
