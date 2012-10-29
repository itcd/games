
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cmath>      // For sin(), cos() etc.
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Image.hpp>
#include "Scene.h"

////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main()
{
	// Create the main window
	sf::Window window(sf::VideoMode(800, 600, 32), "SFML OpenGL");

	// Create a clock for measuring time elapsed
	sf::Clock Clock;

	// call it once, after creating the window
	window.setVerticalSyncEnabled(true);

	// Set color and depth clear value
	glClearDepth(1.f);
	glClearColor(0.f, 0.f, 0.f, 0.f);

	// Enable Z-buffer read and write
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	Scene scene;
	//LookAt(App.GetWidth(), App.GetHeight(), Clock.GetElapsedTime());

	// Start game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit
			if (Event.type == sf::Event::Closed)
				window.close();

			// Escape key : exit
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();

			// Resize event : adjust viewport
			if (Event.type == sf::Event::Resized)
				glViewport(0, 0, Event.size.width, Event.size.height);

			scene.process_input(Event);
		}

		// Set the active window before using OpenGL commands
		// It's useless here because active window is always the same,
		// but don't forget it if you use multiple windows or controls
		//App.SetActive();

		// Call our rendering function
		scene.display(window.getSize().x, window.getSize().y, 1.f/60, Clock.getElapsedTime().asMilliseconds()/1000.f);

		// Finally, display rendered frame on screen
		window.display();
	}

	return EXIT_SUCCESS;
}
