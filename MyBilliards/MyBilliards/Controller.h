#pragma once

#include "parameter.h"

class Controller
{
protected:
	int oldx;
	int oldy;
	int oldz;
	int width;
	int height;
	int drag_mode;
	float rotate_radius;
	glm::vec3 stick_direction;
	glm::vec3 old_stick_direction;

public:
	glm::vec3 Stick_direction() const { return stick_direction; }
	void Stick_direction(const glm::vec3 &val) { stick_direction = val; }

	glm::vec3 Old_stick_direction() const { return old_stick_direction; }
	void Old_stick_direction(const glm::vec3 &val) { old_stick_direction = val; }

	Controller(void)
	{
		/*old.x = old.y = old.z = */oldx = oldy = oldz = drag_mode = 0;
		width = height = 1000;
		rotate_radius = TABLE_WIDTH / 2;
		stick_direction = old_stick_direction = glm::vec3(0, 1, 0);
	}

	virtual ~Controller(void)
	{
	}



	//def rotate_scene(self, x, y):
	//''' rotate the scene by grasping a imaginary sphere '''        
	void rotate_scene(int x, int y)
	{
		x = (int)((x - width/2)*1.0/width*TABLE_WIDTH);
		y = (int)((-y + height/2)*1.0/height*TABLE_WIDTH);
		if (rotate_radius*rotate_radius - x*x - y*y<0)
			return;
		int z = (int)sqrt(rotate_radius*rotate_radius - x*x - y*y);

		if (oldx==-1 || oldy==-1)
		{
			oldx = x;
			oldy = y;
			oldz = z;
			return;
		}

		glm::vec3 position(x,y,z);
		glm::vec3 old_position(oldx, oldy, oldz);
		float a = cos(position, old_position);
		a>1 ? 1 : (a<-1 ? -1 : a);
		float angle = acos(a)*180/PI;
		glm::vec3 rotate_axis = normalize(cross_product(old_position, position));

		oldx = x;
		oldy = y;
		oldz = z;

		glMatrixMode (GL_MODELVIEW);

		//''' first rotate the scene, then multiply the previous saved matrix '''
		float mat[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, mat);

		glLoadIdentity();
		glRotatef(angle, rotate_axis.x, rotate_axis.y, rotate_axis.z);
		glMultMatrixf(mat);

		//''' reset the stick direction '''
		stick_direction = old_stick_direction = glm::vec3(0, 1, 0);
	}



	//def rotate_stick(self, x, y):
	//''' not actually rotate the stick, but collect stick_direction for redrawing the stick'''
	void rotate_stick(int x, int y)
	{
		x = (int)((x - width/2)*1.0/width*TABLE_WIDTH);
		y = (int)((-y + height/2)*1.0/height*TABLE_WIDTH);
		if (rotate_radius*rotate_radius - x*x - y*y<0)
			return;
		int z = (int)sqrt(rotate_radius*rotate_radius - x*x - y*y);

		if (oldx==-1 || oldy==-1)
		{
			oldx = x;
			oldy = y;
			oldz = z;
			return;
		}

		stick_direction.x = (float)oldx;
		stick_direction.y = (float)oldy;
		stick_direction.z = (float)oldz;
		oldx = x;
		oldy = y;
		oldz = z;
	}

	//def drag(self, x, y):
	//''' mouse left button for rotating scene, mouse right button for rotating stick '''
	void drag(int x, int y)
	{
		if (drag_mode == 1)
		{
			rotate_scene(x, y);
		} 
		else
		{
			if (drag_mode == 2)
			{
				rotate_stick(x, y);
			}
		}
	}


	//def process_input(self):
	void process_input(sf::Event e, Ball &cueball)
	{
		double scale_factor = 1.2;

		//	e = pygame.event.poll()
		//	if e.Type == QUIT or (e.Type == KEYDOWN and e.key == K_ESCAPE):
		//return 0
		if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::S)
		{
			float m[16];
			glGetFloatv(GL_MODELVIEW_MATRIX, m);
			glm::mat4 a(
				m[0],m[1],m[2],m[3],
				m[4],m[5],m[6],m[7],
				m[8],m[9],m[10],m[11],
				m[12],m[13],m[14],m[15]
				);
			glm::mat4 b = glm::inverse(a);
			glm::vec3 v;
			v.x = b[0][0] * stick_direction.x + b[1][0] * stick_direction.y + b[2][0] * stick_direction.z + b[3][0];
			v.y = b[0][1] * stick_direction.x + b[1][1] * stick_direction.y + b[2][1] * stick_direction.z + b[3][1];
			v.z = b[0][2] * stick_direction.x + b[1][2] * stick_direction.y + b[2][2] * stick_direction.z + b[3][2];
			v = normalize(v);
			v *= -20;
			//cueball.velocity = v;

			cueball.velocity.x = v.x;
			cueball.velocity.y = v.y;
			cueball.velocity.z = 0;
			cueball.angular_velocity = glm::vec3(0);
			std::cout<<"<hit the ball>"<<std::endl;
			cueball.time = 0;
		}

		if (e.type == sf::Event::MouseButtonPressed)
		{
			if (e.mouseButton.button == sf::Mouse::Left)
			{
				drag_mode = 1;
				//#scene.bounce_sound.play()
				//#print "bang!"			
			}
			if (e.mouseButton.button == sf::Mouse::Right)
				drag_mode = 2;
			//if (e.MouseButton.Button == sf::Mouse::Middle)
			//{
			//	rotate_radius *= scale_factor;
			//	glScalef(scale_factor, scale_factor, scale_factor);
			//}
			//if (e.MouseButton.Button == sf::Mouse::Middle)
			//{
			//	rotate_radius /= scale_factor;
			//	glScalef(1 / scale_factor, 1 / scale_factor, 1 / scale_factor);
			//}
			oldx = - 1;
			oldy = - 1;
			oldz = - 1;
		} 
		else
		{
			if (e.type == sf::Event::MouseButtonReleased)
			{
				drag_mode = 0;
				oldx = - 1;
				oldy = - 1;
				oldz = - 1;
			}else
			{
				if (e.type == sf::Event::MouseWheelMoved)
				{
					std::cout<<e.mouseWheel.delta<<std::endl;

					//rotate_radius *= scale_factor;
					//glScalef(scale_factor, scale_factor, scale_factor);

					//rotate_radius /= scale_factor;
					//glScalef(1 / scale_factor, 1 / scale_factor, 1 / scale_factor);

				}
			}
		}

		//if (e.Type == sf::Event::Resized)
		//	win = display.set_mode(e.size, RESIZABLE);

		if (e.type == sf::Event::MouseMoved)
		{
			drag(e.mouseMove.x, e.mouseMove.y);
		}

		//return 1;
	}

	void lookAt(int width, int height, double elapsedTime, const Ball &cueball)
	{
		//int    width, height;  // Window dimensions
		//double t;              // Time (in seconds)
		//GLUquadric *quadric;   // GLU quadrics object
		double field_of_view;  // Camera field of view
		double camera_x, camera_y, camera_z; // Camera position
		//int    i;

		// Get current time
		//t = glfwGetTime();

		// Get window size
		//glfwGetWindowSize( &width, &height );

		// Make sure that height is non-zero to avoid division by zero
		height = height < 1 ? 1 : height;

		// Set viewport
		glViewport( 0, 0, width, height );

		// Clear color and depht buffers
		glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		// Calculate field of view as a function of time
		field_of_view = 30.0 + 30.0*sin( 0.1 * elapsedTime );

		// Set up projection matrix
		glMatrixMode( GL_PROJECTION );    // Select projection matrix
		glLoadIdentity();                 // Start with an identity matrix
		gluPerspective(                   // Set perspective view
			field_of_view,                // Field of view
			(double)width/(double)height, // Window aspect (assumes square pixels)
			1.0,                          // Near Z clipping plane
			100.0                         // Far Z clippling plane
			);

		// Calculate camera position
		camera_x = TABLE_WIDTH * cos( 0.1 * elapsedTime );
		camera_y = TABLE_LENGTH * sin( 0.1 * elapsedTime );
		camera_z = 4.0;
		//camera_z = 4.0 + 2.0 * sin( 1.0 * elapsedTime );

		// Set up modelview matrix
		glMatrixMode( GL_MODELVIEW );     // Select modelview matrix
		glLoadIdentity();                 // Start with an identity matrix
		gluLookAt(                        // Set camera position and orientation
			camera_x, camera_y, camera_z, // Camera position (x,y,z)
			0.0, 0.0, 0.0,                // View point (x,y,z)
			0.0, 0.0, 1.0                 // Up-vector (x,y,z)
			);
	}
};
