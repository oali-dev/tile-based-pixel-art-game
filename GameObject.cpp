#include "GameObject.h"

// Constructor
GameObject::GameObject() :
_isLoaded(false)
{
}

// Destructor
GameObject::~GameObject()
{
}

// Draws the object to the screen
void GameObject::Draw(sf::RenderWindow& window)
{
	if(IsLoaded())										// Is the texture for our sprite loaded?
	{
		window.draw(_sprite);							// Draw our sprite to the screen
	}
}

// Loads the texture into the sprite
void GameObject::Load(const std::string fileName)
{
	// Checks if the texture exists and if it doesn't, sets the loaded status to false
	if(!_texture.loadFromFile(fileName))
	{
		SetIsLoaded(false);
	}

	else
	{
		_sprite.setTexture(_texture);					// Set the sprite's texture
		SetIsLoaded(true);								// Set the loaded status to true
		//_sprite.setOrigin(0, 7);
	}
}

// Update function that gets called in the game loop
void GameObject::Update(float elapsedTime)
{
}

// Set the load state of the object
void GameObject::SetIsLoaded(bool isLoaded)
{
	_isLoaded = isLoaded;
}

// Returns the loaded status of the sprite (either true or false)
bool GameObject::IsLoaded()
{
	return _isLoaded;
}

// Returns a reference to the game object's sprite
sf::Sprite& GameObject::GetSprite()
{
	return _sprite;
}

// Returns a reference to the game object's sprite sheet
sf::Texture& GameObject::GetTexture()
{
	return _texture;
}