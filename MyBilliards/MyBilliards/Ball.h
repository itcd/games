#pragma once

#include "parameter.h"

struct Ball
{
public:
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 angular_velocity;
	glm::quat rotation;
	GLuint texture;
	bool responsed;
	bool living;
	int score;
	float time;
	// Each ball must has a unique number. It's used to identify a ball.
	int number;


	Ball(void)
	{
		position.x = position.y = position.z = velocity.x = velocity.y = velocity.z = 0;
		//color.r = color.g = color.b = 0;
		responsed = false;
		living = true;
		score = 0;
		number = -1;
		time = 0;
	}

	~Ball(void)
	{
	}

	void draw(void)
	{
		float mat_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
		float mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, 128);

		glPushMatrix();
		glTranslatef(position.x, position.y, position.z);

		glm::vec3 axis = glm::axis(rotation);
		glRotatef(glm::angle(rotation)/PI*180, axis.x, axis.y, axis.z);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);	
		GLUquadric * quadric = gluNewQuadric();
		gluQuadricDrawStyle(quadric, GLU_FILL); 
		gluQuadricNormals(quadric, GLU_SMOOTH);
		gluQuadricOrientation(quadric, GLU_OUTSIDE);
		gluQuadricTexture(quadric, GL_TRUE);      // Create Texture Coords
		gluSphere(quadric, BALL_RADIUS, 50, 50);

		gluDeleteQuadric(quadric);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
};
