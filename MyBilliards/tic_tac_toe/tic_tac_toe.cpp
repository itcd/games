#include <iostream>
#include <string>
#include <cstdlib>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

const int SPRITE_NUM = 3;
const int BOARD_SIZE = 3;
int board[BOARD_SIZE * BOARD_SIZE] = {0};
const int IMAGE_SIZE = 256;

int get_index(int i, int j)
{
	return i * BOARD_SIZE + j;
}

bool check_win(int row, int column)
{
	const int DIRECTIONS = 4;
	int dx[] = {0, 1, 1, -1};
	int dy[] = {1, 0, 1, 1};
	for (int i=0; i<DIRECTIONS; i++)
	{
		int centre = board[get_index(row, column)];
		int pieces[2], pieces_count = 0;
		for (int j=-2; j<=2; j++)
		{
			if (j != 0)
			{
				int row_new = row+dx[i]*j;
				int column_new = column+dy[i]*j;
				if (row_new >=0 && row_new < BOARD_SIZE && column_new >=0 && column_new < BOARD_SIZE)
				{
					pieces[pieces_count++] = board[get_index(row_new, column_new)];
				}
			}
		}
		if (pieces_count == 2 && centre == pieces[0] && centre == pieces[1])
		{
			return true;
		}
	}
	return false;
}

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(IMAGE_SIZE * SPRITE_NUM, IMAGE_SIZE * SPRITE_NUM), "tic-tac-toe");

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

	int count = 0;
	bool is_over = false;

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

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left && !is_over)
				{
					int row = event.mouseButton.y / IMAGE_SIZE;
					int column = event.mouseButton.x / IMAGE_SIZE;
					std::cout<< "row="<<row<<" column="<<column<<std::endl;
					int index = row * BOARD_SIZE + column;
					if (board[index] == 0)
					{
						board[index] = (count % 2) + 1;
						count++;
						std::cout<<"count="<<count<<std::endl;
						if (check_win(row, column))
						{
							std::cout<<"Player "<<board[index]<<" won!"<<std::endl;
							char s[256];
							itoa(board[index], s, 10);
							window.setTitle("Player " + std::string(s) + " won!");
							is_over = true;
						} 
						else
						{
							if (count >= BOARD_SIZE * BOARD_SIZE)
							{
								std::cout<<"Draw!"<<std::endl;
								window.setTitle("Draw!");
								is_over = true;
							}
						}
					} 
					else
					{
						std::cout<<"row "<<row<<" column "<<column<<" is already taken. Please choose another position."<<std::endl;
					}
				}
			}
		}

		// Clear screen
		window.clear();

		// Draw the sprites
		for (int i=0; i<BOARD_SIZE; i++)
		{
			for (int j=0; j<BOARD_SIZE; j++)
			{
				sf::Transform t;
				t.translate((float)j*IMAGE_SIZE, (float)i*IMAGE_SIZE);
				window.draw(sprites[board[i*BOARD_SIZE+j]], sf::RenderStates(t));
			}
		}

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
}
