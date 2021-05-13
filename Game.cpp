#include "Game.h"
#include "Player.h"
//#include <iostream>

Player player;

// Constructor
Game::Game()
{
}

// Destructor
Game::~Game()
{
}

// Starts our game
void Game::StartGame()
{
	_window.create(sf::VideoMode(640,480), "SFML works!", sf::Style::Fullscreen);		// Instantiate our window
	_view.reset(sf::FloatRect(0, 0, _window.getSize().x, _window.getSize().y));			// Reset the view to 0,0
	_view.zoom(0.5);
	_window.setMouseCursorVisible(false);
	_background.Load("cave1.tmx");														// Loads the test map

	// Game Loop
    while(_window.isOpen())
    {
		GameLoop();
    } // while
	//int stop;
	//std::cin >> stop;
}

void Game::GameLoop()
{
	float deltaTime = _clock.restart().asSeconds();											// Get the delta time
	player.Update(deltaTime);																// Update using the delta time

	Game::GetWindow().setView(Game::GetView());												// Set the view

	_window.clear();																		// Clear the screen
	_background.Draw(_window);																// Draw the background
	player.Draw(_window);																	// Draw the player
	_window.display();																		// Display the screen
}

// Returns a reference to the game window
sf::RenderWindow& Game::GetWindow()
{
	return _window;
}

// Returns a reference to the currently loaded tile map
TileMap& Game::GetBackground()
{
	return _background;
}

// Returns a reference to the current view
sf::View& Game::GetView()
{
	return _view;
}

// Returns the deltaTime
sf::Time Game::GetElapsedTime()
{
	return _clock.getElapsedTime();
}


// Declarations for the compiler
sf::Clock Game::_clock;
TileMap Game::_background;
sf::View Game::_view;
sf::RenderWindow Game::_window;
