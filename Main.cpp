// Library Includes
// Library needed for creating and managing SFML windows
#include <SFML/Window.hpp>	
// Library needed for using sprites and textures
#include <SFML/Graphics.hpp>
// Library needed for playing music and sound effects
#include <SFML/Audio.hpp>

// The main() Function - entry point for our program
int main()
{
	// Declare our SFML window, called gameWindow
	sf::RenderWindow gameWindow;
	// Set up the SFML window, passing the dimmensions and the window name
	gameWindow.create(sf::VideoMode::getDesktopMode(), "Button Masher", sf::Style::Titlebar | sf::Style::Close);

	// -----------------------------------------------
	// Game Setup
	// -----------------------------------------------
	// Button Sprite
	// Declare a texture variable called buttonTexture
	sf::Texture buttonTexture;
	// Load up our texture from a file path
	buttonTexture.loadFromFile("graphics/button.png");
	// Create a sprite variable called buttonSprite
	sf::Sprite buttonSprite;
	// Link our sprite to the texture we created previously, so it knows what to draw
	buttonSprite.setTexture(buttonTexture);
	// Set our button's position to the centre of the screen.
	buttonSprite.setPosition(
		gameWindow.getSize().x / 2 - buttonTexture.getSize().x / 2, 
		gameWindow.getSize().y / 2 - buttonTexture.getSize().y / 2
	);

	// Game Music
	// Declare a music variable called gameMusic
	sf::Music gameMusic;
	// Load up our audio from a file path
	gameMusic.openFromFile("audio/music.ogg");
	// Start our music playing
	gameMusic.play();

	// Game Font
	// Declare a font variable called gameFont
	sf::Font gameFont;
	// Load up the font from a file path
	gameFont.loadFromFile("fonts/mainFont.ttf");

	// Title Text
	// Declare a text variable called titleText to hold our game title display
	sf::Text titleText;
	// Set the font our text should use
	titleText.setFont(gameFont);
	// Set the string of text that will be displayed by this text object
	titleText.setString("Button Masher!");
	// Set the size of our text, in pixels
	titleText.setCharacterSize(24);
	// Set the colour of our text
	titleText.setFillColor(sf::Color::Cyan);
	// Set the text style for the text
	titleText.setStyle(sf::Text::Bold | sf::Text::Italic);
	// Position our text in the top center of the screen
	titleText.setPosition(gameWindow.getSize().x / 2 - titleText.getLocalBounds().width / 2, 30);

	// Author Text
	sf::Text authorText;
	authorText.setFont(gameFont);
	authorText.setString("by Sarah Herzog");
	authorText.setCharacterSize(16);
	authorText.setFillColor(sf::Color::Magenta);
	authorText.setStyle(sf::Text::Italic);
	authorText.setPosition(gameWindow.getSize().x / 2 - authorText.getLocalBounds().width / 2, 60);

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
		// Clear the window to a single colour
		gameWindow.clear(sf::Color::Black);

		// Draw everything to the window
		gameWindow.draw(buttonSprite);
		gameWindow.draw(titleText);
		gameWindow.draw(authorText);
		// TODO: Draw more stuff

		// Display the window contents on the screen
		gameWindow.display();

	} // End of Game Loop
	return 0;

} // End of main() Function