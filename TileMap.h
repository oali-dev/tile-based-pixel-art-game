#ifndef TILEMAP_H
#define TILEMAP_H

#include <string>
#include <vector>
#include "GameObject.h"
#include "SFML/Graphics.hpp"


class TileMap : public GameObject
{
public:
	explicit TileMap();											// Default Constructor
	explicit TileMap(const std::string fileName);				// Constructor
	~TileMap();													// Deconstructor
	void Load(const std::string fileName);						// Loads a tile map from a given xml file
	void Draw(sf::RenderWindow& window);						// Draw function for TileMaps
	int GetTileWidth();											// Returns the width of a tile in pixels
	int GetTileHeight();										// Returns the height of a tile in pixels
	bool IsCollidable(int positionX, int positionY);			// Returns whether or not a tile cannot be moved in it
	
private:
	unsigned int _numTilesWidth;								// width of the map in tiles
	unsigned int _numTilesHeight;								// height of the map in tiles
	unsigned int _tileWidth;									// width of each tile in pixels
	unsigned int _tileHeight;									// height of each tile in pixels
	unsigned int _collisionLayerIndex;							// index in the tile map that has the collision information
	std::string _fileName;										// name of the XML file we are loading from
	std::vector< std::vector< std::vector<int> > > tileMap;		// 3D vector of layers that contains the tile indices corresponding to our sprite sheet
};

#endif