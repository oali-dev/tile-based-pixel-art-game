#ifndef GAME_H
#define GAME_H

#include "TileMap.h"
#include "SFML/Graphics.hpp"

class Game
{
public:
	explicit Game();						// Constructor
	~Game();								// Destructor
	void StartGame();						// Starts the game
	static sf::RenderWindow& GetWindow();	// Returns a reference to the game window
	static TileMap& GetBackground();		// Returns a reference to the currently tile map
	static sf::View& GetView();				// Returns a reference to the current view
	static sf::Time GetElapsedTime();		// Returns the delta time

private:
	void GameLoop();						// Loop where all the important events happen
	static sf::Clock _clock;				// Game Clock, used to get the delta time
	static TileMap _background;				// The currently loaded tile map
	static sf::View _view;					// The current view of the screen
	static sf::RenderWindow _window;		// The game window
};

#endif