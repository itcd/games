#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "NPC.h"

int main()
{
	srand( (unsigned)time( NULL ) );

	const int IMAGE_SIZE = 256;
	const float STEP_SIZE = IMAGE_SIZE / 32.f;

	// Create the main window
	sf::RenderWindow window(sf::VideoMode(IMAGE_SIZE * 3, IMAGE_SIZE * 3), "NPC");

	// call it once, after creating the window
	window.setVerticalSyncEnabled(true);

	const int SPRITE_NUM = 3;

	std::string filenames[SPRITE_NUM] = {"0.bmp", "1.bmp", "2.bmp"};
	sf::Texture textures[SPRITE_NUM];
	for (int i=0; i<SPRITE_NUM; i++)
	{
		if (!textures[i].loadFromFile(filenames[i]))
			return EXIT_FAILURE;
	}
	sf::Sprite sprites[SPRITE_NUM];
	for (int i=0; i<SPRITE_NUM; i++)
	{
		sprites[i].setTexture(textures[i]);
	}

	// Load a sprite to display
	sf::Texture texture;
	if (!texture.loadFromFile("1.bmp"))
		return EXIT_FAILURE;
	sf::Sprite sprite(texture);

	std::vector<NPC> npcs;
	npcs.push_back(NPC(0, 0, 0));
	npcs.push_back(NPC(256, 256, 1));
	npcs.push_back(NPC(512, 512, 2));

	// Load a music to play
	sf::Music music;
	if (!music.openFromFile("Silencer.ogg"))
		return EXIT_FAILURE;

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
				auto p = npcs[0].position();
				switch (event.key.code)
				{
				case sf::Keyboard::Up:	
					p.y -= STEP_SIZE;
					npcs[0].position(p);
					break;
				case sf::Keyboard::Down:
					p.y += STEP_SIZE;
					npcs[0].position(p);
					break;
				case sf::Keyboard::Left:
					p.x -= STEP_SIZE;
					npcs[0].position(p);
					break;
				case sf::Keyboard::Right:
					p.x += STEP_SIZE;
					npcs[0].position(p);
					break;
				default:
					break;
				}
				if (event.key.code == sf::Keyboard::Space)
				{
					NPC new_one(npcs[0]);
					new_one.sprite_index(rand() % 3);
					npcs.push_back(new_one);
					music.play();
				}
			}
		}

		// Clear screen
		window.clear();

		for (auto i=++npcs.begin(); i!=npcs.end(); i++)
		{
			int offset = (rand() % 11) - 5;
			auto p = (*i).position();
			if (rand() % 2 == 0)
			{
				p.x += offset;
			} 
			else
			{
				p.y += offset;
			}
			(*i).position(p);
		}

		for (auto i=npcs.begin(); i!=npcs.end(); i++)
		{
			auto npc = *i;
			sf::Transform t;
			t.translate(npc.position().x, npc.position().y);
			t.scale(0.25f, 0.25f);
			// Draw the sprite
			window.draw(sprites[npc.sprite_index()], sf::RenderStates(t));
		}

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
}
