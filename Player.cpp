#include "Player.h"
#include "Game.h"
#include <cmath>
//#include <iostream>

// Constructor
Player::Player() :
_direction(Down),
_positionX(10),
_positionY(10),
_movementSpeed(100.0f),
_isMoving(false)
{
	Load("character3.png");
	_animation[0].Init(3, 1, 3, 0, 0, 16, 16, 6);		// Moving Down
	_animation[1].Init(3, 1, 3, 0, 16, 16, 16, 6);		// Moving Left
	_animation[2].Init(3, 1, 3, 0, 32, 16, 16, 6);		// Moving Right
	_animation[3].Init(3, 1, 3, 0, 48, 16, 16, 6);		// Moving Up
	_animation[4].Init(1, 1, 1, 16, 0, 16, 16, 1);		// Idle Down
	_animation[5].Init(1, 1, 1, 16, 16, 16, 16,  1);	// Idle Left
	_animation[6].Init(1, 1, 1, 16, 32, 16, 16, 1);		// Idle Right
	_animation[7].Init(1, 1, 1, 16, 48, 16, 16, 1);		// Idle Up
}

// Destructor
Player::~Player()
{
}

// Draws the player's sprite to the screen
void Player::Draw(sf::RenderWindow& window)
{
	/* Internal Testing Stuff */
	/*sf::Text textPositionX;
	sf::Text textPositionY;
	sf::Text delta;

	textPositionY.setPosition(textPositionX.getLocalBounds().left, textPositionX.getLocalBounds().top + 30);
	delta.setPosition(textPositionX.getLocalBounds().left, textPositionX.getLocalBounds().top + 60);

	textPositionX.setString(_spositionX);
	textPositionY.setString(_spositionY);
	delta.setString(_selapsedTime);*/
	/* End Internal Testing Stuff */

	GetSprite().setPosition(_positionX * Game::GetBackground().GetTileWidth(), _positionY * Game::GetBackground().GetTileHeight());		// Set the position of the sprite
	_animation[0].Draw(GetSprite());																									// Draw the sprite
	
	/* Internal Testing Stuff */
	/*window.draw(textPositionX);
	window.draw(textPositionY);	
	window.draw(delta);*/
	/* End Internal Testing Stuff */
}

// Loads the texture of the player's sprite
void Player::Load(const std::string fileName)
{
	GameObject::Load(fileName);
}

// Updates the player
void Player::Update(float elapsedTime)
{
	/* Information data for internal use */
	ss << _positionX;
	ss >> _spositionX;
	ss.clear();

	ss << _positionY;
	ss >> _spositionY;
	ss.clear();

	ss << elapsedTime;
	ss >> _selapsedTime;
	ss.clear();
	/* End Information data for internal use */

	_animation[_direction].Update(_clock.getElapsedTime().asSeconds(), GetSprite());

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))					// If the ESC key is pressed
	{
		Game::GetWindow().close();											// Close the window
	} // if

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))							// If the 'A' key is pressed
	{
		Game::GetBackground().Load("sewer1.tmx");							// Loads a test map
		_positionX = 16;
		_positionY = 14;
	} // if

	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))					// If the 'S' key is pressed
	{
		Game::GetBackground().Load("cave1.tmx");							// Loads a test map
		_positionX = 16;
		_positionY = 12;
	} // if

	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))					// If the '1' key is pressed
	{
		Load("character1.png");												// Loads a test map
		//_positionX = 16;
		//_positionY = 12;
	} // if

	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))					// If the '1' key is pressed
	{
		Load("character2.png");												// Loads a test map
		//_positionX = 16;
		//_positionY = 12;
	} // if

	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))					// If the '1' key is pressed
	{
		Load("character3.png");												// Loads a test map
		//_positionX = 16;
		//_positionY = 12;
	} // if

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !_isMoving)			// If the Up arrow is pressed and we're not currently moving
	{
		_direction = Up;													// Set the direction to Up
		if(!Game::GetBackground().IsCollidable(_positionX, _positionY - 1)) // Can we move into the next tile?
		{
			_nextPositionY = _positionY - 1;								// Set the target tile to be one tile Up
			_isMoving = true;												// We are now moving Up
		} // if

		else																// We can't move into the tile i.e. it is collidable
		{
			return;															// So we don't do anything
		} // else
	} // else if

	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !_isMoving)	// If the Down arrow is pressed and we're not currently moving
	{
		_direction = Down;													// Set the direction to Down
		if(!Game::GetBackground().IsCollidable(_positionX, _positionY + 1))	// Can we move into the next tile?
		{
			_nextPositionY = _positionY + 1;								// Set the target tile to be one tile Down
			_isMoving = true;												// We are now moving Down
		}

		else																// We can't move into the tile i.e. it is collidable
		{
			return;															// So we don't do anything
		}
	} // else if

	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !_isMoving)	// If the Left arrow is pressed and we're not currently moving
	{
		_direction = Left;													// Set the direction to Left
		if(!Game::GetBackground().IsCollidable(_positionX - 1, _positionY))	// Can we move into the next tile?
		{
			_nextPositionX = _positionX - 1;								// Set the target tile to be one tile to the Left
			_isMoving = true;												// We are now moving Left
		}

		else																// We can't move into the tile i.e. it is collidable
		{
			return;															// So we don't do anything
		}
	} // else if

	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !_isMoving)	// If the Right arrow is pressed and we're not currently moving
	{
		_direction = Right;													// Set the direction to Right
		if(!Game::GetBackground().IsCollidable(_positionX + 1, _positionY))	// Can we move into the next tile?
		{
			_nextPositionX = _positionX + 1;								// Set the target tile to be one tile to the Right
			_isMoving = true;												// We are now moving Right
		}

		else																// We can't move into the tile i.e. it is collidable
		{
			return;															// So we don't do anything
		}
	} // else if

	if(_isMoving)															// If we are moving
	{
		MoveToNextTile(elapsedTime);										// Move to the corresponding tile
	}

	else																	// Else we're not moving
	{
		if(_direction == Up)												// Set the idle state for when the character is facing Up
			_direction = Direction::IdleUp;
		if(_direction == Down)												// Set the idle state for when the character is facing Down
			_direction = Direction::IdleDown;
		if(_direction == Left)												// Set the idle state for when the character is facing Left
			_direction = Direction::IdleLeft;
		if(_direction == Right)												// Set the idle state for when the character is facing Right
			_direction = Direction::IdleRight;
	} // else

	_camera.Update(_positionX, _positionY);									// Move the position of the camera as well
}

// Moves the player to the next tile, depending on which key is pressed
void Player::MoveToNextTile(float elapsedTime)
{
	// Moving Up
	if(_direction == Up)
	{
		_positionY -= (_movementSpeed * elapsedTime) / Game::GetBackground().GetTileWidth();		// Decrement the Y position
		if(_positionY <= _nextPositionY)															// If we have reached the next tile
		{
			_isMoving = false;																		// Make it so we are no longer moving
			_positionY = _nextPositionY;															// Update our current position to the new tile
		}
	}

	// Moving Down
	else if(_direction == Down)
	{
		_positionY += (_movementSpeed * elapsedTime) / Game::GetBackground().GetTileWidth();		// Increment the Y position
		if(_positionY >= _nextPositionY)															// If we have reached the next tile
		{
			_isMoving = false;																		// Make it so we are no longer moving
			_positionY = _nextPositionY;															// Update our current position to the new tile
		}
	}

	// Moving Left
	else if(_direction == Left)
	{
		_positionX -= (_movementSpeed * elapsedTime) / Game::GetBackground().GetTileWidth();		// Decrement the X position
		if(_positionX <= _nextPositionX)															// If we have reached the next tile
		{
			_isMoving = false;																		// Make it so we are no longer moving
			_positionX = _nextPositionX;															// Update our current position to the new tile
		}
	}

	// Moving Right
	else if(_direction == Right)
	{
		_positionX += (_movementSpeed * elapsedTime) / Game::GetBackground().GetTileWidth();		// Increment the X position
		if(_positionX >= _nextPositionX)															// If we have reached the next tile
		{
			_isMoving = false;																		// Make it so we are no longer moving
			_positionX = _nextPositionX;															// Update our current position to the new tile
		}
	}
}