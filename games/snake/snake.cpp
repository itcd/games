#include <iostream>
#include <vector>
#include <list>
#include <ctime>
#include <cstdlib>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

const int BLOCK_SIZE = 20;
const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;
const int BOARD_WIDTH = WINDOW_WIDTH / BLOCK_SIZE;
const int BOARD_HEIGHT = WINDOW_HEIGHT / BLOCK_SIZE;

int main()
{
	srand((unsigned)time(NULL));

	// Create the main window
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake");

	// call it once, after creating the window
	window.setVerticalSyncEnabled(true);

	std::list<sf::Vector2i> snake;
	snake.push_back(sf::Vector2i(BOARD_WIDTH / 2 + 1, BOARD_HEIGHT / 2 + 1));
	snake.push_back(sf::Vector2i(BOARD_WIDTH / 2 + 1, BOARD_HEIGHT / 2 + 2));
	snake.push_back(sf::Vector2i(BOARD_WIDTH / 2 + 1, BOARD_HEIGHT / 2 + 3));
	snake.push_back(sf::Vector2i(BOARD_WIDTH / 2 + 1, BOARD_HEIGHT / 2 + 4));

	std::vector<sf::Vector2i> baits;
	baits.push_back(sf::Vector2i(0, 0));
	baits.push_back(sf::Vector2i(BOARD_WIDTH / 2, BOARD_HEIGHT / 2));
	baits.push_back(sf::Vector2i(BOARD_WIDTH - 1, BOARD_HEIGHT - 1));
	baits.push_back(sf::Vector2i(0, BOARD_HEIGHT - 1));
	baits.push_back(sf::Vector2i(BOARD_WIDTH - 1, 0));

	sf::Vector2i direction;
	switch (rand() % 4)
	{
	case 0:
		direction = sf::Vector2i(0, -1);
		break;
	case 1:
		direction = sf::Vector2i(0, 1);
		break;
	case 2:
		break;
		direction = sf::Vector2i(-1, 0);
	case 3:
		break;
		direction = sf::Vector2i(1, 0);
	}

	sf::Clock clock;

	// Start the game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window : exit
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					direction = sf::Vector2i(0, -1);
					break;
				case sf::Keyboard::Down:
					direction = sf::Vector2i(0, 1);
					break;
				case sf::Keyboard::Left:
					direction = sf::Vector2i(-1, 0);
					break;
				case sf::Keyboard::Right:
					direction = sf::Vector2i(1, 0);
					break;
				default:
					break;
				}
			}
		}

		// Clear screen
		window.clear();

		if (clock.getElapsedTime().asMilliseconds() > 150)
		{
			auto new_node = snake.back() + direction;
			snake.push_back(new_node);
			snake.pop_front();
			for (auto i=baits.begin(); i!=baits.end(); i++)
			{
				if (new_node == *i)
				{
					snake.push_back(new_node + direction);
					(*i).x = rand() % BOARD_WIDTH;
					(*i).y = rand() % BOARD_HEIGHT;
				}
			}
			clock.restart();
		}

		sf::Vector2f block_size(BLOCK_SIZE, BLOCK_SIZE);
		for (auto i=snake.begin(); i!=snake.end(); i++)
		{
			sf::RectangleShape rectangle(block_size);
			rectangle.setOutlineColor(sf::Color::Green);
			rectangle.setOutlineThickness(1);
			rectangle.setPosition((*i).x * BLOCK_SIZE, (*i).y * BLOCK_SIZE);
			window.draw(rectangle);
		}

		for (auto i=baits.begin(); i!=baits.end(); i++)
		{
			sf::RectangleShape rectangle(block_size);
			rectangle.setOutlineColor(sf::Color::Magenta);
			rectangle.setOutlineThickness(1);
			rectangle.setPosition((*i).x * BLOCK_SIZE, (*i).y * BLOCK_SIZE);
			window.draw(rectangle);
		}

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
}
