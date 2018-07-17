// Library Includes
// Library needed for creating and managing SFML windows
#include <SFML/Window.hpp>	
// Library needed for using sprites and textures
#include <SFML/Graphics.hpp>

// The main() Function - entry point for our program
int main()
{
	// Declare our SFML window, called gameWindow
	sf::Window gameWindow;
	// Set up the SFML window, passing the dimmensions and the window name
	gameWindow.create(sf::VideoMode::getDesktopMode(), "Button Masher", sf::Style::Titlebar | sf::Style::Close);

	// -----------------------------------------------
	// Game Setup
	// -----------------------------------------------
	sf::Texture buttonTexture;
	buttonTexture.loadFromFile("button.png");

	// -----------------------------------------------
	// Game Loop
	// -----------------------------------------------
	// Repeat as long as the window is open
	while (gameWindow.isOpen())
	{
		// -----------------------------------------------
		// Input Section
		// -----------------------------------------------
		// Declare a variable to hold an Event, called gameEvent
		sf::Event gameEvent;
		// Loop through all events and poll them, putting each one into our gameEvent variable
		while (gameWindow.pollEvent(gameEvent))
		{
			// This section will be repeated for each event waiting to be processed

			// Did the player try to close the window?
			if (gameEvent.type == sf::Event::Closed)
			{
				// If so, call the close function on the window.
				gameWindow.close();
			}
		} // End event polling loop

		// -----------------------------------------------
		// Update Section
		// -----------------------------------------------
		// TODO: Update game state

		// -----------------------------------------------
		// Draw Section
		// -----------------------------------------------
		// TODO: Draw graphics

	} // End of Game Loop
	return 0;

} // End of main() Function