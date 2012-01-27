#pragma once
#include <vector>
#include "Ball.h"
#include "PhysicsEngine.h"
#include "Controller.h"
#include "Texture.h"

class Scene
{
protected:
	std::vector<Ball> balls;
	PhysicsEngine physics;
	Texture textures;
	Controller control;

public:
	Scene(void)
	{
		//pygame.init();
		//pygame.display.set_mode((1000,1000), OPENGL|DOUBLEBUF);
		//glEnable(GL_DEPTH_TEST);
		//#glutSolidSphere(1,50,50)

		init();
		//#pygame.mixer.pre_init(buffersize=256)
		//#pygame.mixer.init(buffer = 256)

		//controller = Controller(self);
		//bounce_sound = load_sound('bounce.wav');
		//yay_sound = load_sound('yay.wav');
		//oops_sound = load_sound('oops.wav');
	}

	virtual ~Scene(void)
	{
	}



	//	def make_lights(self):
	//''' make three light sources for the scene '''
	void make_lights()
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1);

		float light_ambient[] =  {0.3f, 0.3f, 0.3f, 0.3f};
		float light_diffuse[] =  {0.3f, 0.3f, 0.3f, 0.3f};
		float light_specular[] = {1, 1, 1, 1};

		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
		float light0[] = {0.0, 0.0, 10.0, 0.0};
		glLightfv(GL_LIGHT0, GL_POSITION, light0);
		glEnable(GL_LIGHT0);


		glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
		float light1[] = {0.0, 0.0, -10.0, 0.0};
		glLightfv(GL_LIGHT1, GL_POSITION, light1);
		glEnable(GL_LIGHT1);


		glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
		float light2[] = {10.0, 0.0, 0.0, 0.0};
		glLightfv(GL_LIGHT2, GL_POSITION, light2);
		glEnable(GL_LIGHT2);

		glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular);
		float light3[] = {-10.0, 0.0, 0.0, 0.0};
		glLightfv(GL_LIGHT3, GL_POSITION, light3);
		glEnable(GL_LIGHT3);
	}



	//def make_balls(self, num):
	//''' make all the balls and init the physics engine '''
	void make_balls()
	{
		const float y0 = TABLE_LENGTH / 4;
		const float dx[] = {0,
			0,
			-0.5f, 0.5f,
			-1, 0, 1,
			-1.5f, 1.5f, -0.5f, 0.5f,
			-2, -1, 0, 1, 2
		};
		const float dy[] = {-TABLE_LENGTH/2,
			0,
			SQRT3/2, SQRT3/2,
			SQRT3, SQRT3, SQRT3,
			1.5f*SQRT3, 1.5f*SQRT3, 1.5f*SQRT3, 1.5f*SQRT3,
			2*SQRT3, 2*SQRT3, 2*SQRT3, 2*SQRT3, 2*SQRT3
		};

		// 12 7 14 15 5
		//  4 13 6 11
		//   10 8 3
		//    2 9
		//     1
		const int ball_number[] = {0, 1, 2, 9, 10, 8, 3, 4, 13, 6, 11, 12, 7, 14, 15, 5};

		for (int i=0; i<BALL_NUM; i++)
		{
			Ball ball;
			ball.position.x = dx[i];
			ball.position.y = y0 + dy[i];
			ball.position.z = 0;
			ball.number = ball_number[i];
			ball.texture = textures.getTexture(texture_ball, ball.number);
			balls.push_back(ball);
		}

		// for test
		balls[1].position = glm::vec3(0);
	}



	//	def init(self):
	//''' init texture, light and balls in the scene '''  
	void init()
	{
		//load_textures();

		make_lights();
		//make_ball([1,1,1,1], [0,0,0], 0);
		make_balls();

		//''' reset the stick direction '''
		//stick_direction = [0,0,1]
		//old_stick_direction = [0,0,1]
	}



	void process_input(sf::Event e)
	{
		if (!balls[0].living)
		{
			balls[0].position.x = balls[0].position.y = balls[0].position.z = balls[0].velocity.x = balls[0].velocity.y = balls[0].velocity.z = 0;
			balls[0].living=true;
		}
		control.process_input(e, balls[0]);

		if (e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Key::Return)
		{
			balls[0].velocity = glm::vec3(0,20,0);
			balls[0].angular_velocity = glm::vec3(0);
			std::cout<<"<hit the ball>"<<std::endl;
			balls[0].time = 0;
		}
		if (e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Key::Space)
		{
			balls[0].position = glm::vec3(0, -TABLE_LENGTH / 4, 0);
			balls[0].velocity = glm::vec3(0);
			balls[0].angular_velocity = glm::vec3(0);
			balls[0].time = 0;
			balls[1].position = glm::vec3(0);
			balls[1].velocity = glm::vec3(0);
			balls[1].angular_velocity = glm::vec3(0);
			balls[1].time = 0;
		}
	}

	//def run(self):
	//void run()
	//{
//		while 1:
//#check for quit'n events
//		if not self.controller.process_input():
//		break
//
//			self.reshape(1000, 1000)
//			self.display()
//
//			pygame.display.flip()
//			pygame.time.wait(10)

	//}



	//def display_hole(self, position):
	void display_pockets()
	{
		glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);
		glEnable(GL_TEXTURE_2D);

		// binds the texture for pockets
		glBindTexture(GL_TEXTURE_2D, textures.getTexture(texture_pocket));

		// two middle pockets
		GLUquadric * quadric = gluNewQuadric();

		glPushMatrix();
		glTranslatef(MIN_X - POCKET_DIAMETER/2, 0, -0.5f);
		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluQuadricTexture(quadric, GL_TRUE);
		gluDisk(quadric, 0, POCKET_DIAMETER/2, 50, 10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(MAX_X + POCKET_DIAMETER/2, 0, -0.5f);
		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluQuadricTexture(quadric, GL_TRUE);
		gluDisk(quadric, 0, POCKET_DIAMETER/2, 50, 10);
		glPopMatrix();

		// four corner pockets
		glPushMatrix();
		glTranslatef(MIN_X, MIN_Y, -0.5f);
		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluQuadricTexture(quadric, GL_TRUE);
		gluDisk(quadric, 0, POCKET_DIAMETER/2, 50, 10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(MAX_X, MIN_Y, -0.5f);
		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluQuadricTexture(quadric, GL_TRUE);
		gluDisk(quadric, 0, POCKET_DIAMETER/2, 50, 10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(MAX_X, MAX_Y, -0.5f);
		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluQuadricTexture(quadric, GL_TRUE);
		gluDisk(quadric, 0, POCKET_DIAMETER/2, 50, 10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(MIN_X, MAX_Y, -0.5f);
		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluQuadricTexture(quadric, GL_TRUE);
		gluDisk(quadric, 0, POCKET_DIAMETER/2, 50, 10);
		glPopMatrix();

		gluDeleteQuadric(quadric);

		glDisable(GL_TEXTURE_2D);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}



	//def display_stick(self):
	void display_stick()
	{
		const Ball &ball = balls[0];			

		glm::vec3 position = control.Stick_direction();
		glm::vec3 old_position = control.Old_stick_direction();
		float angle = acos(cos(position, old_position))*180/PI;
		glm::vec3 rotate_axis = normalize(cross_product(old_position, position));

		float m[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
		glm::mat4 a(
			m[0],m[1],m[2],m[3],
			m[4],m[5],m[6],m[7],
			m[8],m[9],m[10],m[11],
			m[12],m[13],m[14],m[15]
			);

		glm::vec3 v;     
		v.x = a[0][0]*ball.position.x + a[1][0]*ball.position.y + a[2][0]*ball.position.z + a[3][0];
		v.y = a[0][1]*ball.position.x + a[1][1]*ball.position.y + a[2][1]*ball.position.z + a[3][1];
		v.z = a[0][2]*ball.position.x + a[1][2]*ball.position.y + a[2][2]*ball.position.z + a[3][2];		

		glEnable(GL_TEXTURE_2D);

		glPushMatrix();
		glLoadIdentity();
		glTranslatef(v.x, v.y, v.z);
		glRotatef(angle, rotate_axis.x, rotate_axis.y, rotate_axis.z);

		// binds the texture for the table frame
		glBindTexture(GL_TEXTURE_2D, textures.getTexture(texture_frame));

		glTranslatef(0,0,1);
		GLUquadric * quadric = gluNewQuadric();
		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluQuadricTexture(quadric, GL_TRUE);
		gluCylinder(quadric, 0.1, 0.2, 5, 50, 50);
		gluSphere(quadric, 0.1, 50, 50);
		glTranslatef(0,0,5);
		gluSphere(quadric, 0.2, 50, 50);

		glDisable(GL_TEXTURE_2D);

		glBegin(GL_LINES);
		glVertex3f(0,0,0);
		glVertex3f(0,0,-100);
		glEnd();
		float params1[] = {1,1,1,1};

		glPopMatrix();

	}



	//	def display_walls(self):
	//''' make six walls, let the front faces of the walls be transparent '''
	void display_table()
	{
		glEnable (GL_BLEND);
		glDepthMask (GL_FALSE);
		glEnable(GL_TEXTURE_2D);

		// binds the texture for the table surface
		glBindTexture(GL_TEXTURE_2D, textures.getTexture(texture_desktop));
		float mat_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
		float mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, 128);

		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(MIN_X, MIN_Y, -0.5f);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(MAX_X, MIN_Y, -0.5f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(MAX_X, MAX_Y, -0.5f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(MIN_X, MAX_Y, -0.5f);
		glEnd();

		// binds the texture for the table frame
		glBindTexture(GL_TEXTURE_2D, textures.getTexture(texture_frame));

		// width
		glBegin(GL_QUAD_STRIP);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(MIN_X + POCKET_RADIUS_DIVIDED_BY_SQRT2, MIN_Y -POCKET_RADIUS_DIVIDED_BY_SQRT2, -0.5f);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(MIN_X + POCKET_RADIUS_DIVIDED_BY_SQRT2, MIN_Y -POCKET_RADIUS_DIVIDED_BY_SQRT2,  0.5f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(MIN_X + POCKET_DIAMETER_DIVIDED_BY_SQRT2, MIN_Y, -0.5f);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(MIN_X + POCKET_DIAMETER_DIVIDED_BY_SQRT2, MIN_Y,  0.5f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(MAX_X - POCKET_DIAMETER_DIVIDED_BY_SQRT2, MIN_Y, -0.5f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(MAX_X - POCKET_DIAMETER_DIVIDED_BY_SQRT2, MIN_Y,  0.5f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(MAX_X - POCKET_RADIUS_DIVIDED_BY_SQRT2, MIN_Y - POCKET_RADIUS_DIVIDED_BY_SQRT2, -0.5f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(MAX_X - POCKET_RADIUS_DIVIDED_BY_SQRT2, MIN_Y - POCKET_RADIUS_DIVIDED_BY_SQRT2,  0.5f);
		glEnd();

		// length
		glBegin(GL_QUAD_STRIP);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(MAX_X + POCKET_RADIUS_DIVIDED_BY_SQRT2, MIN_Y + POCKET_RADIUS_DIVIDED_BY_SQRT2, -0.5f);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(MAX_X + POCKET_RADIUS_DIVIDED_BY_SQRT2, MIN_Y + POCKET_RADIUS_DIVIDED_BY_SQRT2, 0.5f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(MAX_X, MIN_Y + POCKET_DIAMETER_DIVIDED_BY_SQRT2, -0.5f);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(MAX_X, MIN_Y + POCKET_DIAMETER_DIVIDED_BY_SQRT2, 0.5f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(MAX_X, -MIDDLE_POCKET_ENTRANCE_RADIUS, -0.5f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(MAX_X, -MIDDLE_POCKET_ENTRANCE_RADIUS,  0.5f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(MAX_X + POCKET_RADIUS, -POCKET_RADIUS,  -0.5f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(MAX_X + POCKET_RADIUS, -POCKET_RADIUS,  0.5f);
		glEnd();

		glBegin(GL_QUAD_STRIP);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(MAX_X + POCKET_RADIUS, POCKET_RADIUS,  -0.5f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(MAX_X + POCKET_RADIUS, POCKET_RADIUS,  0.5f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(MAX_X, MIDDLE_POCKET_ENTRANCE_RADIUS, -0.5f);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(MAX_X, MIDDLE_POCKET_ENTRANCE_RADIUS, 0.5f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(MAX_X, MAX_Y - POCKET_DIAMETER_DIVIDED_BY_SQRT2, -0.5f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(MAX_X, MAX_Y - POCKET_DIAMETER_DIVIDED_BY_SQRT2,  0.5f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(MAX_X + POCKET_RADIUS_DIVIDED_BY_SQRT2, MAX_Y - POCKET_RADIUS_DIVIDED_BY_SQRT2,  -0.5f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(MAX_X + POCKET_RADIUS_DIVIDED_BY_SQRT2, MAX_Y - POCKET_RADIUS_DIVIDED_BY_SQRT2,  0.5f);
		glEnd();

		// width
		glBegin(GL_QUAD_STRIP);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(MIN_X + POCKET_RADIUS_DIVIDED_BY_SQRT2, MAX_Y +POCKET_RADIUS_DIVIDED_BY_SQRT2, -0.5f);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(MIN_X + POCKET_RADIUS_DIVIDED_BY_SQRT2, MAX_Y +POCKET_RADIUS_DIVIDED_BY_SQRT2, 0.5f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(MIN_X + POCKET_DIAMETER_DIVIDED_BY_SQRT2, MAX_Y, -0.5f);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(MIN_X + POCKET_DIAMETER_DIVIDED_BY_SQRT2, MAX_Y,  0.5f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(MAX_X - POCKET_DIAMETER_DIVIDED_BY_SQRT2, MAX_Y, -0.5f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(MAX_X - POCKET_DIAMETER_DIVIDED_BY_SQRT2, MAX_Y,  0.5f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(MAX_X - POCKET_RADIUS_DIVIDED_BY_SQRT2, MAX_Y + POCKET_RADIUS_DIVIDED_BY_SQRT2, -0.5f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(MAX_X - POCKET_RADIUS_DIVIDED_BY_SQRT2, MAX_Y + POCKET_RADIUS_DIVIDED_BY_SQRT2,  0.5f);
		glEnd();

		// length
		glBegin(GL_QUAD_STRIP);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(MIN_X - POCKET_RADIUS_DIVIDED_BY_SQRT2, MIN_Y + POCKET_RADIUS_DIVIDED_BY_SQRT2, -0.5f);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(MIN_X - POCKET_RADIUS_DIVIDED_BY_SQRT2, MIN_Y + POCKET_RADIUS_DIVIDED_BY_SQRT2, 0.5f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(MIN_X, MIN_Y + POCKET_DIAMETER_DIVIDED_BY_SQRT2, -0.5f);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(MIN_X, MIN_Y + POCKET_DIAMETER_DIVIDED_BY_SQRT2, 0.5f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(MIN_X, -MIDDLE_POCKET_ENTRANCE_RADIUS, -0.5f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(MIN_X, -MIDDLE_POCKET_ENTRANCE_RADIUS,  0.5f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(MIN_X - POCKET_RADIUS, -POCKET_RADIUS,  -0.5f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(MIN_X - POCKET_RADIUS, -POCKET_RADIUS,  0.5f);
		glEnd();

		glBegin(GL_QUAD_STRIP);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(MIN_X - POCKET_RADIUS, POCKET_RADIUS,  -0.5f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(MIN_X - POCKET_RADIUS, POCKET_RADIUS,  0.5f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(MIN_X, MIDDLE_POCKET_ENTRANCE_RADIUS, -0.5f);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(MIN_X, MIDDLE_POCKET_ENTRANCE_RADIUS, 0.5f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(MIN_X, MAX_Y - POCKET_DIAMETER_DIVIDED_BY_SQRT2, -0.5f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(MIN_X, MAX_Y - POCKET_DIAMETER_DIVIDED_BY_SQRT2,  0.5f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(MIN_X - POCKET_RADIUS_DIVIDED_BY_SQRT2, MAX_Y - POCKET_RADIUS_DIVIDED_BY_SQRT2,  -0.5f);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(MIN_X - POCKET_RADIUS_DIVIDED_BY_SQRT2, MAX_Y - POCKET_RADIUS_DIVIDED_BY_SQRT2,  0.5f);
		glEnd();

		glDisable(GL_TEXTURE_2D);
		glDepthMask (GL_TRUE);
		glDisable(GL_BLEND);
	}



	//	def display(self):
	//''' draw the whole scene '''
	// drawing function that is called each frame
	void display(int width, int height, float frameTime, float elapsedTime)
	{
		control.lookAt(width, height, elapsedTime, balls.front());

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode (GL_PROJECTION);
		glPushMatrix();
		//glTranslatef(0, 0, -20);
		glMatrixMode (GL_MODELVIEW);

		physics.reset(balls);



		for (std::vector<Ball>::iterator i = balls.begin(); i!=balls.end(); i++)
		{
			if ((*i).living)
			{
				if (modulus((*i).velocity) > VELOCITY_ZERO)
					physics.move(*i, balls, frameTime);
				(*i).draw();
			}
		}

		if (modulus(balls[0].velocity) <= VELOCITY_ZERO)
			display_stick();
		display_table();
		display_pockets();

		glMatrixMode (GL_PROJECTION);
		glPopMatrix();
		glMatrixMode (GL_MODELVIEW);
		glFlush();
	}



	//def reshape(self, w, h):
	//''' reset the clipping volume using glFrustum '''
	//void reshape(int w, int h)
	//{
//		self.width = w
//		self.height = h
//		glViewport(0, 0, w, h)
//
//		glMatrixMode (GL_PROJECTION)
//#gluPerspective(45, 1, 0.1, 100)
//		glLoadIdentity()
//
//		scale = 0.1
//		if w <= h:
//	glFrustum(scale*MIN_X, scale*MAX_X, scale*MIN_X*h/w, scale*MAX_X*h/w, 1, 100)
//		else: 
//	glFrustum(scale*MIN_X*w/h, scale*MAX_X*w/h, scale*MIN_X, scale*MAX_X, 1, 100)
//
//		glMatrixMode(GL_MODELVIEW)
	//}



	//def load_sound(self, name):
	//void load_sound(std::string name)
	//{
//		pygame.mixer.quit()
//			pygame.mixer.init(22050, -16, 2, 64)
//
//		class NoneSound:
//			def play(self): pass
//			if not pygame.mixer or not pygame.mixer.get_init():
//		return NoneSound()
//
//			fullname = os.path.join('data', name)
//#fullname = name
//			print fullname
//			try:
//		sound = pygame.mixer.Sound(fullname)
//			except pygame.error, message:
//		print 'Cannot load sound:', fullname
//			raise SystemExit, message
//			return sound
	//}

};
