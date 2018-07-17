// Library Includes
// Library needed for creating and managing SFML windows
#include <SFML/Window.hpp>	
// Library needed for using sprites and textures
#include <SFML/Graphics.hpp>
// Library needed for playing music and sound effects
#include <SFML/Audio.hpp>
// Library for manipulating strings of text
#include <string>

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

	// Score
	// Declare an integer variable to hold the numerical score for our game to display
	int score = 0;
	sf::Text scoreText;
	scoreText.setFont(gameFont);
	scoreText.setString("Score: " + std::to_string(score));
	scoreText.setCharacterSize(16);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(30,30);

	// Timer
	sf::Text timerText;
	timerText.setFont(gameFont);
	timerText.setString("Time Remaining: 0");
	timerText.setCharacterSize(16);
	timerText.setFillColor(sf::Color::White);
	timerText.setPosition(gameWindow.getSize().x - timerText.getLocalBounds().width - 30, 30);

	// Create a time value to store the total time limit for our game
	sf::Time timeLimit = sf::seconds(10.0f);
	// Create a timer to store the time remaining for our game
	sf::Time timeRemaining = timeLimit;

	// Game Clock
	// Create a clock to track time passed each frame in the game
	sf::Clock gameClock;

	// Click Sound Effect
	// Create a sound buffer to hold our click sound's file information
	sf::SoundBuffer clickBuffer;
	// Tell the click sound buffer where the file is
	clickBuffer.loadFromFile("audio/buttonclick.ogg");
	// Create a click sound to hold the information about how the click sound should be played
	sf::Sound clickSound;
	// Associate our click sound with the click sound buffer
	clickSound.setBuffer(clickBuffer);

	// Game state
	bool playing = false;

	// Prompt text
	sf::Text promptText;
	promptText.setFont(gameFont);
	promptText.setString("Click the button to start the game!");
	promptText.setCharacterSize(16);
	promptText.setFillColor(sf::Color::White);
	promptText.setPosition(gameWindow.getSize().x / 2 - promptText.getLocalBounds().width / 2, 200);

	// Game Over Audio
	sf::SoundBuffer gameOverBuffer;
	gameOverBuffer.loadFromFile("audio/gameover.ogg");
	sf::Sound gameOverSound;
	gameOverSound.setBuffer(gameOverBuffer);

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

			// Did the player click the mouse?
			if (gameEvent.type == sf::Event::MouseButtonPressed)
			{
				// Did they click the button sprite?
				if (buttonSprite.getGlobalBounds().contains(gameEvent.mouseButton.x, gameEvent.mouseButton.y))
				{
					// They clicked it!

					// Play a click sound
					clickSound.play();

					// If the game is currently playing
					if (playing == true)
					{
						// Add to the score
						score = score + 1;
					}
					else
					{
						// We aren't playing, so we should start!
						playing = true;
						// Re-initialise the game
						score = 0;
						timeRemaining = timeLimit;
						promptText.setString("Click the button as fast as you can!");
					}
				}
			}

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
		// Get the time passed since the last frame and restart our game clock
		sf::Time frameTime = gameClock.restart();
		// Are we currently playing?
		if (playing == true)
		{
			// Update our time remaining based on how much time passed last frame
			timeRemaining = timeRemaining - frameTime;
			// Are we out of time?
			if (timeRemaining.asSeconds() <= 0)
			{
				// Set playing state to false
				playing = false;
				// Update the prompt
				promptText.setString("Your final score was: "+std::to_string((int)timeRemaining.asSeconds()) +". Click the button to start a new game!");
				// Play jingle
				gameOverSound.play();
			}
		}
		// Update our time display based on our time remaining
		timerText.setString("Time Remaining: " + std::to_string((int)timeRemaining.asSeconds()));
		// Update our score display text based on our current numerical score
		scoreText.setString("Score: " + std::to_string(score));

		// -----------------------------------------------
		// Draw Section
		// -----------------------------------------------
		// Clear the window to a single colour
		gameWindow.clear(sf::Color::Black);

		// Draw everything to the window
		gameWindow.draw(buttonSprite);
		gameWindow.draw(titleText);
		gameWindow.draw(authorText);
		gameWindow.draw(scoreText);
		gameWindow.draw(timerText);
		gameWindow.draw(promptText);

		// Display the window contents on the screen
		gameWindow.display();

	} // End of Game Loop
	return 0;

} // End of main() Function