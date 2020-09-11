#ifndef TILE_MAP_H
#define TILE_MAP_H

class TileMap
{
    public:
	TileMap(int rowCount, int colCount);
	void assignReferenceNumberToTexture(int referenceNumber, sf::Texture texture);
	void setTileAtIndicesToReferenceNumber(int row, int col, int referenceNumber);
	void getReferenceNumberAtIndices(int row, int col);
    protected:
	//
    private:
	//
};

#endif
