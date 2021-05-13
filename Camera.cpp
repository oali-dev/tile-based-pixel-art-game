#include "Camera.h"
#include "Game.h"

// Constructor
Camera::Camera() :
_scrollSpeed(100.0f)
{
}

// Deconstructor
Camera::~Camera()
{
}

void Camera::Update(float positionX, float positionY)
{
	Game::GetView().setCenter(positionX * Game::GetBackground().GetTileWidth(), positionY * Game::GetBackground().GetTileHeight());
}

void Camera::GoToPoint(float xCoord, float yCoord, double speed)
{
	// TODO
}

void Camera::ReturnToCharacter()
{
	// TODO
}