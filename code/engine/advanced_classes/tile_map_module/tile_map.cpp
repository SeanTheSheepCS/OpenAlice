#include "tile_map.h"

TileMap::TileMap(int x, int y, unsigned int width, unsigned int height, unsigned int rowCountArg, unsigned int colCountArg): DrawableObject(x,y,width,height)
{
    this->rowCount = rowCountArg;
    this->colCount = colCountArg;
    this->tileWidth = (width/rowCount);
    this->tileHeight = (height/colCount);
    this->centreOffsetTileCountX = 0.0;
    this->centreOffsetTileCountY = 0.0;

    referenceNumberTwoDimensionArrayRepresentingTileMap = new int*[rowCountArg];
    for(unsigned int i = 0; i < rowCountArg; i++)
    {
        referenceNumberTwoDimensionArrayRepresentingTileMap[i] = new int[colCountArg];
    } 
}

TileMap::TileMap(const TileMap& other): DrawableObject(other.x, other.y, other.width, other.height)
{
    this->tileWidth = other.tileWidth;
    this->tileHeight = other.tileHeight;
    this->centreOffsetTileCountX = other.centreOffsetTileCountX;
    this->centreOffsetTileCountY = other.centreOffsetTileCountY;
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
    this->tileWidth = rhs.tileWidth;
    this->tileHeight = rhs.tileHeight;
    this->centreOffsetTileCountX = rhs.centreOffsetTileCountX;
    this->centreOffsetTileCountY = rhs.centreOffsetTileCountY;
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

void TileMap::associateReferenceNumberWithTexture(int referenceNumber, sf::Texture* texture)
{
    referenceNumberToTexturePointerMap.insert(std::pair<int, sf::Texture*>(referenceNumber, texture));
}

void TileMap::deassociateTextureWithSpecificReferenceNumber(int referenceNumber)
{
    referenceNumberToTexturePointerMap.erase(referenceNumber);
}

void TileMap::setTileAtIndicesToReferenceNumberAndPartialDraw(unsigned int row, unsigned int col, int referenceNumber, sf::RenderWindow& windowToPartialDrawIn)
{
    if((row >= 0) && (row < rowCount) && (col >= 0) && (col <= colCount))
    {
        referenceNumberTwoDimensionArrayRepresentingTileMap[row][col] = referenceNumber;
        drawTileAtRowAndColInWindow(row, col, windowToPartialDrawIn);
    }
    else
    {
        std::cout << "Bad request: writing to row " << row << " and col " << col << " in an array with " << rowCount << " rows and " << colCount << " columns." << std::endl;
    }
}

int TileMap::getReferenceNumberAtIndices(unsigned int row, unsigned int col)
{
    return referenceNumberTwoDimensionArrayRepresentingTileMap[row][col];
}

void TileMap::setTileWidth(int tileWidthArg)
{
    this->tileWidth = tileWidthArg;
}

void TileMap::setTileHeight(int tileHeightArg)
{
    this->tileHeight = tileHeightArg;
}

void TileMap::setCentreOffsetTileCountX(float newCentreOffsetTileCountX)
{
    this->centreOffsetTileCountX = newCentreOffsetTileCountX;
}

void TileMap::setCentreOffsetTileCountY(float newCentreOffsetTileCountY)
{
    this->centreOffsetTileCountY = newCentreOffsetTileCountY;
}

void TileMap::changeCentreOffsetTileCountXByAmount(float amountToChangeCentreOffsetTileCountXBy)
{
    (this->centreOffsetTileCountX) = (this->centreOffsetTileCountX) + amountToChangeCentreOffsetTileCountXBy;
}

void TileMap::changeCentreOffsetTileCountYByAmount(float amountToChangeCentreOffsetTileCountYBy)
{
    (this->centreOffsetTileCountY) = (this->centreOffsetTileCountY) + amountToChangeCentreOffsetTileCountYBy;
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
}

void TileMap::deleteTileMap() //Helper function for ~TileMap() and TileMap& operator=(...)
{
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
    this->tileWidth = 0;
    this->tileHeight = 0;
    this->centreOffsetTileCountX = 0.0;
    this->centreOffsetTileCountY = 0.0;
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
    //
}
