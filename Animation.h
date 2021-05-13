#ifndef ANIMATION_H
#define ANIMATION_H

#include "SFML/Graphics.hpp"

class Animation
{
public:
	explicit Animation();																			// Constructor
	~Animation();																					// Destructor
	void Init(int numFrames, int numRows, int numColumns,											// Initializes the animation class
			  int startPositionX, int startPositionY, int spriteWidth, int spriteHeight, 
			  float framesPerSecond);
	void Update(float time, sf::Sprite& sprite);													// Updates the frame of animation
	void Draw(sf::Sprite& sprite);																	// Draws the animation

private:
	int _index;					// Frame number that we are currently on
	int _numFrames;				// Total number of frames in the animation
	int _numRows;				// Number of rows of the animation
	int _numColumns;			// Number of columns of the animation
	int _startPositionX;		// x-coord of the starting frame on the sprite sheet in pixels
	int _startPositionY;		// y-coord of the starting frame on the sprite sheet in pixels
	int _spriteWidth;			// The width of the sprite in pixels
	int _spriteHeight;			// The height of the sprite in pixels
	float _framesPerSecond;		// How fast you want the animation to play
	sf::Rect<int> _sourceRect;	// Where the sprite is being drawn from on the sprite sheet
};

#endif