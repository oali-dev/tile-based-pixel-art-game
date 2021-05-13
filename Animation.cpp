#include "Animation.h"
#include "Game.h"
#include <iostream>

// Constructor
Animation::Animation()
{
}

// Destructor
Animation::~Animation()
{
}

// Initializes the animation, since we cannot initialize it in the constructor due 
// to us using an array to store the animations in the container class
void Animation::Init(int numFrames, int numRows, int numColumns, 
					 int startPositionX, int startPositionY, int spriteWidth, int spriteHeight, 
					 float framesPerSecond)
{
	_index = 0;
	_numFrames = numFrames;
	_numRows = numRows;
	_numColumns = numColumns;
	_startPositionX = startPositionX;
	_startPositionY = startPositionY;
	_spriteWidth = spriteWidth;
	_spriteHeight = spriteHeight;
	_framesPerSecond = framesPerSecond;
	_sourceRect = sf::Rect<int>(startPositionX, startPositionY, spriteWidth, spriteHeight);
}

// Updates the frame of animation
void Animation::Update(float time, sf::Sprite& sprite)
{
	_index = time * _framesPerSecond;
	_index %= _numFrames;
	_sourceRect.left = _startPositionX + (_spriteWidth * (_index % _numColumns));
	_sourceRect.top = _startPositionY + (_spriteHeight * (_index / _numColumns));
	sprite.setTextureRect(_sourceRect);
}

// Draws the animation
void Animation::Draw(sf::Sprite& sprite)
{
	Game::GetWindow().draw(sprite);
}