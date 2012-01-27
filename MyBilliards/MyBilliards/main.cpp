
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cmath>      // For sin(), cos() etc.
#include <SFML/Window.hpp>
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
	sf::Window App(sf::VideoMode(800, 600, 32), "SFML OpenGL");

	// Create a clock for measuring time elapsed
	sf::Clock Clock;

	// Set color and depth clear value
	glClearDepth(1.f);
	glClearColor(0.f, 0.f, 0.f, 0.f);

	// Enable Z-buffer read and write
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	Scene scene;
	//LookAt(App.GetWidth(), App.GetHeight(), Clock.GetElapsedTime());

	// Start game loop
	while (App.IsOpened())
	{
		// Process events
		sf::Event Event;
		while (App.GetEvent(Event))
		{
			// Close window : exit
			if (Event.Type == sf::Event::Closed)
				App.Close();

			// Escape key : exit
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
				App.Close();

			// Resize event : adjust viewport
			if (Event.Type == sf::Event::Resized)
				glViewport(0, 0, Event.Size.Width, Event.Size.Height);

			scene.process_input(Event);
		}

		// Set the active window before using OpenGL commands
		// It's useless here because active window is always the same,
		// but don't forget it if you use multiple windows or controls
		//App.SetActive();

		// Call our rendering function
		scene.display(App.GetWidth(), App.GetHeight(), App.GetFrameTime(), Clock.GetElapsedTime());

		// Finally, display rendered frame on screen
		App.Display();
	}

	return EXIT_SUCCESS;
}
