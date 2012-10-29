#pragma once

enum texture_type
{
	texture_ball,
	texture_desktop,
	texture_frame,
	texture_pocket
};

const int OTHER_TEXTURE_BEGIN = BALL_NUM;
const int TEXTURE_NUM = BALL_NUM + 3; // three textures for the billiards table

class Texture
{
protected:
	GLuint texture[TEXTURE_NUM];

public:

	Texture(void)
	{
		load_textures();
	}

	virtual ~Texture(void)
	{
	}

	GLuint getTexture(texture_type material, int index = 0)
	{
		switch (material)
		{
		// textures for the table surface
		case texture_desktop:
			return texture[OTHER_TEXTURE_BEGIN];

		// textures for the table frame
		case texture_frame:
			return texture[OTHER_TEXTURE_BEGIN + 1];

		// textures for pockets
		case texture_pocket:
			return texture[OTHER_TEXTURE_BEGIN + 2];

		// textures for balls
		default:
			return texture[index];
		}
	}

	//def load_textures(self):
	void load_textures()
	{
		std::string texture_file[TEXTURE_NUM] = {
			"textures/0.bmp",
			"textures/1.bmp",
			"textures/2.bmp",
			"textures/3.bmp",
			"textures/4.bmp",
			"textures/5.bmp",
			"textures/6.bmp",
			"textures/7.bmp",
			"textures/8.bmp",
			"textures/9.bmp",
			"textures/10.bmp",
			"textures/11.bmp",
			"textures/12.bmp",
			"textures/13.bmp",
			"textures/14.bmp",
			"textures/15.bmp",
			"textures/filzkachel.bmp",
			"textures/holz.bmp",
			"textures/target_320_320.png"
		};

		glGenTextures(TEXTURE_NUM, texture);
		for (int i=0; i<TEXTURE_NUM; i++)
		{
			sf::Image image;
			if (image.loadFromFile(texture_file[i]))
			{
				glBindTexture(GL_TEXTURE_2D, texture[i]);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x, image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
			}
		}
	}
};
