#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SFML/Graphics.hpp"

class GameObject
{
public:
	explicit GameObject();								// Constructor
	virtual ~GameObject();								// Destructor
	virtual void Draw(sf::RenderWindow& window);		// Draws the object to the screen
	virtual void Load(const std::string fileName);		// Loads from the texture file to the sprite
	virtual void Update(float elapsedTime);				// Updates the object (i.e. position, animation state, etc.)
	void SetIsLoaded(bool isLoaded);					// Sets if the object was successfully loaded or not
	bool IsLoaded();									// Returns whether the object was successfully loaded or not

protected:
	sf::Sprite& GetSprite();							// Gets the sprite
	sf::Texture& GetTexture();							// Gets the texture
	sf::Rect<int> GetSpriteLocation();					// Returns a rect that contains the location of the sprite on the texture (i.e. the sprite sheet)
	
private:
	sf::Sprite _sprite;									// Sprite object
	sf::Texture _texture;								// Texture object (i.e. sprite sheet)
	bool _isLoaded;										// Is the object loaded?
	sf::Rect<int> _spriteLocation;						// location of the sprite on the texture (i.e. the sprite sheet)
};

#endif