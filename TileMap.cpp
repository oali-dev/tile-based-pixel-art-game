#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "TileMap.h"
#include "tinyxml.h"

// Default Constructor
TileMap::TileMap()
{
}

// Constructor
TileMap::TileMap(const std::string fileName)
{
	Load(fileName);
}

// Destructor
TileMap::~TileMap()
{
}

// Loads a tile map from a given xml file
void TileMap::Load(const std::string fileName)
{
	// Try and load the file and if it fails, set the load status to false
	TiXmlDocument doc;
	if(!doc.LoadFile(fileName))
	{
		std::cerr << doc.ErrorDesc() << std::endl;
		SetIsLoaded(false);
		return;
	} // if

	// Check to see if the file isn't empty
	TiXmlElement* map = doc.FirstChildElement();				// Points to our root note, labelled "map"
	if(map == NULL)
	{
		std::cerr << "Failed to load file: No root element." << std::endl;
		doc.Clear();
		SetIsLoaded(false);
		return;
	} // if

	const char* width = map->Attribute("width");				// Get the "width" value from the map (the width of the map in tiles)
	const char* height = map->Attribute("height");				// Get the "height" value from the map (the height of the map in tiles)
	const char* tileWidth = map->Attribute("tilewidth");		// Get the "tilewidth" value from the map (the width of each tile in pixels)
	const char* tileHeight = map->Attribute("tileheight");		// Get the "tileheight" value from the map (the height of each tile in pixels)

	std::stringstream ss;										// Declaring a string stream that will convert the strings from the xml file to integers

	// Converting all the string values to usable integers
	ss << width;
	ss >> _numTilesWidth;
	ss.clear();

	ss << height;
	ss >> _numTilesHeight;
	ss.clear();

	ss << tileWidth;
	ss >> _tileWidth;
	ss.clear();

	ss << tileHeight;
	ss >> _tileHeight;
	ss.clear();

	map = map->FirstChildElement();														// map should now point to the "tileset" node, which is always the first child of "map"
	std::string sourceImage = map->FirstChildElement("image")->Attribute("source");		// Get the file location of the source image 
	_fileName = sourceImage;															// Set _filename of the TileMap to the source image

	// Load the texture (i.e. the tileset)
	GetTexture().loadFromFile(_fileName);

	// We read all the tile indices from each layer and store them in a 3D vector of layers
	int layer = 1;																		// Keeps track of which layer we're reading from
	int tileIndexRow = 0;																// Keeps track of which row we're reading from in that specific layer
	int tileIndexColumn = 0;															// Keeps track of which column we're reading from in that specific layer
	_collisionLayerIndex = 0;															// The index of the layer that has the collision info
	
	for(map = map->NextSiblingElement(/*"layer"*/); map != NULL; map = map->NextSiblingElement(/*"layer"*/))		// For each layer in the map...
	{
		tileMap.resize(layer);																						// Create room for a new layer vector in the tileMap vector
		tileMap[layer - 1].resize(_numTilesHeight);																	// Create room in that newly allocated layer vector for the number of rows

		for(std::vector< std::vector<int> >::iterator it = tileMap[layer - 1].begin(); it < tileMap[layer - 1].end(); it++)
		{
			it->resize(_numTilesWidth);																				// Create room in that newly allocated layer vector for the number of columns
		}

		TiXmlElement* data = map->FirstChildElement("data");														// Reading from the data node nested in the layer node
		std::string layerName = map->Attribute("name");																// Get the name of the layer, used to check for the collision layer

		if(layerName == "Collision")
		{
			_collisionLayerIndex = layer - 1;																					// Save the index that we can use to access the collision layer
			for(TiXmlElement* tile = data->FirstChildElement("tile"); tile != NULL;  tile = tile->NextSiblingElement("tile"))	// For each tile in the layer...
			{
				if(atoi(tile->Attribute("gid")) != 0)											// If there's an entry in the collision layer in the xml file
				{
					tileMap[layer - 1][tileIndexRow][tileIndexColumn % _numTilesWidth] = 1;		// Set the corresponding index in the tile map as 1 to show that it's not passable
				}

				else																			// Otherwise if there's nothing there
				{
					tileMap[layer - 1][tileIndexRow][tileIndexColumn % _numTilesWidth] = 0;		// Set the corresponding index in the tile map to 0 to show that it is passable
				}

				tileIndexColumn++;																// Move onto the next column
				tileIndexRow = tileIndexColumn / _numTilesWidth;								// Move onto the next row
			} // for
		}
		
		else
		{
			for(TiXmlElement* tile = data->FirstChildElement("tile"); tile != NULL;  tile = tile->NextSiblingElement("tile"))	// For each tile in the layer...
			{
				tileMap[layer - 1][tileIndexRow][tileIndexColumn % _numTilesWidth] = atoi(tile->Attribute("gid"));				// Read the tile index (or grid ID) from the xml file into the tileMap
				tileIndexColumn++;																								// Move onto the next column, the modulo above will take care of resetting the column after it reaches the end
				tileIndexRow = tileIndexColumn / _numTilesWidth;																// Move onto the next row if we've reached the last column
			} // for
		}

		layer++;						// Move on to the next layer
		tileIndexRow = 0;				// Resetting the tile indices
		tileIndexColumn = 0;			// Resetting the tile indices
	} // for

	if(_collisionLayerIndex == 0)		// If there is no layer that was named Collision
	{
		_collisionLayerIndex = 99999;	// Set the index to some ridiculous value, i.e. 99999
	}
	/*
	for(std::vector< std::vector< std::vector<int> > >::iterator it1 = tileMap.begin(); it1 < tileMap.end(); it1++)
	{
		for(std::vector< std::vector<int> >::iterator it2 = it1->begin(); it2 < it1->end(); it2++)
		{
			for(std::vector<int>::iterator it3 = it2->begin(); it3 < it2->end(); it3++)
			{
				std::cout << " " << *it3;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << std::endl << std::endl;
	}*/

	doc.Clear();			// We're done, clear the document
	SetIsLoaded(true);		// We have finished loading the tile map, so set loaded status to true
}

// Draw the tile map
void TileMap::Draw(sf::RenderWindow& window)
{
	if(!IsLoaded())												// If we somehow haven't loaded the map yet, the return
		return;

	// Load the texture (i.e. the tileset)
	//GetTexture().loadFromFile(_fileName);
	
	int windowPixelPositionX = 0;								// x-coord in the window where the current tile is to be drawn to
	int windowPixelPositionY = 0;								// y-coord in the window where the current tile is to be drawn to
	int texturePixelPositionX = 0;								// x-coord in the texture where the tile is to be drawn from
	int texturePixelPositionY = 0;								// y-coord in the texture where the tile is to be drawn from
	int mapLengthInPixels = _tileWidth * _numTilesWidth;		// Length of the map in pixels
	int textureLengthInPixels = GetTexture().getSize().x;		// Length of the texture in pixels
	int tileIndex = 0;											// The index of the tile that we are drawing from our texture (i.e. index 17 is tile 17 in the tileset)
	int layerIndex = 0;											// Which layer we are looking at

	for(std::vector< std::vector< std::vector<int> > >::iterator it1 = tileMap.begin(); it1 < tileMap.end(); it1++)	// For each layer in the tile map...
	{
		for(std::vector< std::vector<int> >::iterator it2 = it1->begin(); it2 < it1->end(); it2++)					// For each tile in the layer..
		{
			if(layerIndex == _collisionLayerIndex)																		// If the layer is the collision layer
			{
				break;																									// Break out since we don't want to draw it
			}
			for(std::vector<int>::iterator it3 = it2->begin(); it3 < it2->end(); it3++)
			{
				tileIndex = *it3;																			// Get the index of the current tile in the map
				if(tileIndex != 0)																			// Check if the tile isn't empty
				{
					tileIndex -= 1;																			// Subtract 1 to get the correct coordinates (since we start at 0,0)

					texturePixelPositionX = tileIndex % (textureLengthInPixels / _tileWidth);				// Find the x-coord of the tile in the texture
					texturePixelPositionX *= _tileWidth;

					texturePixelPositionY = tileIndex / (textureLengthInPixels / _tileWidth);				// Find the y-coord of the tile in the texture
					texturePixelPositionY *= _tileHeight;

					sf::Sprite sprite;																		// Create a sprite to be drawn
					sprite.setTexture(GetTexture());																// Set the sprite's texture to the tileset
					sprite.setTextureRect(sf::IntRect(texturePixelPositionX, texturePixelPositionY, _tileWidth, _tileHeight));	// Set the area of the tileset that we are drawing from
					sprite.setPosition(windowPixelPositionX % mapLengthInPixels, windowPixelPositionY);		// Set the place in the window that we are drawing to

					window.draw(sprite);																	// Draw the sprite (tile) to the screen
				} // if
				// Move the window position to the next spot to draw
				windowPixelPositionX += _tileWidth;
				windowPixelPositionY = (windowPixelPositionX / mapLengthInPixels);
				windowPixelPositionY *= _tileWidth;
			} // for
		} // for
		windowPixelPositionX = 0;																		// Reset the window x-coord for the next layer
		windowPixelPositionY = 0;																		// reset the window y-coord for the next layer
		layerIndex++;																					// Increment the layer index
	} // for
}

// Returns the width of a tile in pixels
int TileMap::GetTileWidth()
{
	return static_cast<int>(_tileWidth);
}

// Returns the height of a tile in pixels
int TileMap::GetTileHeight()
{
	return static_cast<int>(_tileHeight);
}

// Returns whether or not a tile cannot be moved in it
bool TileMap::IsCollidable(int positionX, int positionY)
{
	if(_collisionLayerIndex == 99999)									// If we don't have a collision layer, return false right away
	{
		return false;
	}

	else
	{
		if(tileMap[_collisionLayerIndex][positionY][positionX] == 1)	// Check if the tile is impassable
			return true;

		else															// Otherwise we can move through it
			return false;
	}
}