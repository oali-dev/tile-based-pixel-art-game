#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "TileMap.h"
#include "Camera.h"
#include "Animation.h"
#include "SFML/Graphics.hpp"
#include <string>
#include <sstream>

class Player : public GameObject
{
public:
	explicit Player();										// Constructor
	~Player();												// Destructor
	void Draw(sf::RenderWindow& window);					// Draws the player to the screen
	void Load(const std::string fileName);					// Loads the player's sprite
	void Update(float elapsedTime);							// Update the player
	void MoveToNextTile(float elapsedTime);					// Moves the player to the next tile depending on what key is pressed

private:
	enum Direction { Down = 0, Left = 1, Right = 2, Up = 3,					// Direction that the player is moving/facing and idle states
					IdleDown = 4, IdleLeft = 5, IdleRight = 6, 
					IdleUp = 7 } _direction;
	float _positionX;														// X position of the player based on tile indices
	float _positionY;														// Y position of the player based on tile indices
	int _nextPositionX;														// The next horizontal tile that we want to move to
	int _nextPositionY;														// The next vertical tile that we want to move to
	float _movementSpeed;													// Speed that the player moves
	bool _isMoving;															// Is the player currently moving?
	Camera _camera;															// Camera view
	Animation _animation[8];												// Animations for walking, attacking, etc.
	sf::Clock _clock;														// Clock for the animations

	// Information variables for internal use
	std::stringstream ss;
	std::string _spositionX;
	std::string _spositionY;
	std::string _selapsedTime;
};

#endif