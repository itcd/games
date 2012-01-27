#pragma once
#include "parameter.h"
#include "Ball.h"

class PhysicsEngine
{
protected:

public:

	PhysicsEngine(void)
	{
	}

	virtual ~PhysicsEngine(void)
	{
	}


	//def __init__(self, scene):
	//self.scene = scene


	//	def reset(self):
	void reset(std::vector<Ball> &balls)
	{
		for (std::vector<Ball>::iterator i = balls.begin(); i!=balls.end(); i++)
		{
			(*i).responsed = false;
		}
	}


	//def check_rebounce(self, ball):
	void check_rebounce(Ball &ball)
	{
		glm::vec3 rebound_velocity = ball.velocity;
		if(ball.position.x<=MIN_X+BALL_RADIUS)
		{
			ball.position.x=2*(MIN_X+BALL_RADIUS)-ball.position.x;
			rebound_velocity.x = -rebound_velocity.x;
			//self.scene.bounce_sound.play()
		}
		if(ball.position.x>=MAX_X-BALL_RADIUS)
		{
			ball.position.x=2*(MAX_X-BALL_RADIUS)-ball.position.x;
			rebound_velocity.x = -rebound_velocity.x;
			//self.scene.bounce_sound.play()
		}

		if(ball.position.y<=MIN_Y+BALL_RADIUS)
		{
			ball.position.y=2*(MIN_Y+BALL_RADIUS)-ball.position.y;
			rebound_velocity.y = -rebound_velocity.y;
			//self.scene.bounce_sound.play()
		}
		if(ball.position.y>=MAX_Y-BALL_RADIUS)
		{
			ball.position.y=2*(MAX_Y-BALL_RADIUS)-ball.position.y;
			rebound_velocity.y = -rebound_velocity.y;
			//self.scene.bounce_sound.play()
		}
		ball.velocity = RESTITUTION * rebound_velocity;
	}


	//def check_fell(self, ball):
	void check_fell(const Ball &ball)
	{
		//glm::vec3 p = ball.position;
		//const int N= 2;
		//double x[N] = {MIN_X, MAX_X};
		//double y[N] = {MIN_Y, MAX_Y};
		//double z[N] = {MIN_Z, MAX_Z};
		//for (int i=0; i<N; i++)
		//{
		//	for (int j=0; j<N; j++)
		//	{
		//		for (int k=0; k<N; k++)
		//		{
		//			double dx = (p.x - x[i]) * (p.x - x[i]);
		//			double dy = (p.y - y[j]) * (p.y - y[j]);
		//			double dz = (p.z - z[k]) * (p.z - z[k]);
		//			if (dx + dy + dz < R * R)
		//			{
		//				ball.living = false;
		//				//if (ball.number == 0)
		//				//{
		//				//	// cue ball
		//				//	//self.scene.oops_sound.play()
		//				//} 
		//				//else
		//				//{
		//				//	// other ball
		//				//	//self.scene.yay_sound.play()
		//				//}
		//				goto out_of_loop;
		//			}
		//		}
		//	}
		//}
		//out_of_loop: 1+1; // just for go out of the loops
	}



	//def collide(self, ball1, ball2):
	//bool collide(const Ball &ball1, const Ball &ball2)
	//{
	//	static const float d = (2 * BALL_RADIUS) * (2 * BALL_RADIUS);
	//	//return (ball1.position[0]-ball2.position[0])**2+(ball1.position[1]-ball2.position[1])**2+(ball1.position[2]-ball2.position[2])**2<(2*R)**2
	//	float dx = (ball1.position.x - ball2.position.x) * (ball1.position.x - ball2.position.x);
	//	float dy = (ball1.position.y - ball2.position.y) * (ball1.position.y - ball2.position.y);
	//	float dz = (ball1.position.z - ball2.position.z) * (ball1.position.z - ball2.position.z);
	//	return dx + dy + dz < d;
	//}



	//def response(self, ball1, ball2):
	void response(Ball &ball1, Ball &ball2)
	{
		glm::vec3 collision_vector = normalize(ball2.position - ball1.position);
		glm::vec3 collision_vector2 = -collision_vector;
		float d1 = dot_product(ball1.velocity, collision_vector);
		glm::vec3 p1 = d1 * collision_vector;
		float d2 = dot_product(ball2.velocity, collision_vector2);
		glm::vec3 p2 = d2 * collision_vector2;
		if (dot_product(p1-p2, collision_vector) < 0)
		{
			return;
		}



		// rotation
		glm::vec3 r1 = BALL_RADIUS * collision_vector;
		glm::vec3 r2 = -r1;
		glm::vec3 perimeter_velocity1, perimeter_velocity2;

		if (modulus(ball1.angular_velocity) > VELOCITY_ZERO)
			perimeter_velocity1 = cross_product(ball1.angular_velocity,r1) + ball1.velocity;
		else
			perimeter_velocity1 = ball1.velocity;
		if (modulus(ball2.angular_velocity) > VELOCITY_ZERO)
			perimeter_velocity2 = cross_product(ball2.angular_velocity,r2) + ball2.velocity;
		else
			perimeter_velocity2 = ball2.velocity;

		glm::vec3 v1_relative = perimeter_velocity1 - perimeter_velocity2;
		glm::vec3 v2_relative = -v1_relative;



		ball1.velocity = ball1.velocity - p1 + p2;
		ball2.velocity = ball2.velocity - p2 + p1;
		ball1.velocity = RESTITUTION * modulus(ball1.velocity) * normalize(ball1.velocity);
		ball2.velocity = RESTITUTION * modulus(ball2.velocity) * normalize(ball2.velocity);
	}



	void apply_friction(Ball &ball, float frameTime)
	{
		ball.time += frameTime;

		glm::vec3 r = glm::vec3(0,0,-BALL_RADIUS);
		glm::vec3 perimeter_velocity;
		if (modulus(ball.angular_velocity) > VELOCITY_ZERO)
		{
			perimeter_velocity = cross_product(ball.angular_velocity,r)+ball.velocity;
		}
		else
			perimeter_velocity = ball.velocity;

		float modulus_perimeter_velocity = modulus(perimeter_velocity);

		// for test
		std::cout<<"\nperimeter_velocity "<<modulus_perimeter_velocity<<"\t";
		print(perimeter_velocity);

		if (modulus_perimeter_velocity > VELOCITY_SLIDING_MIN)
		{
			// sliding friction
			// the direction of friction force is opposite to that of perimeter_velocity
			float u_g_dt = SLIDING_FRICTION * GRAVITY_ACCELERATION * frameTime;
			std::cout<<"sliding u_g_dt "<<u_g_dt<<"\t";
			ball.velocity -= u_g_dt * normalize(perimeter_velocity);
			ball.angular_velocity -= (u_g_dt*5.f/2.f/BALL_RADIUS)*normalize(cross_product(r, perimeter_velocity));
		}else
		{
			// rolling friction
			float u_g_dt = ROLLING_FRICTION * GRAVITY_ACCELERATION * frameTime;
			std::cout<<"rolling u_g_dt "<<u_g_dt<<"\t";
			if (modulus(ball.velocity) > u_g_dt)
			{
				ball.velocity -= u_g_dt * normalize(ball.velocity);
				ball.angular_velocity = modulus(ball.velocity)/BALL_RADIUS*normalize(cross_product(ball.velocity, r));
			}else
			{
				ball.velocity = glm::vec3(0);
				ball.angular_velocity = glm::vec3(0);
				std::cout<<"motion time\t"<<ball.time<<std::endl;
			}
		}

		// for test
		std::cout<<"velocity ";
		print(ball.velocity);
		std::cout<<"angular ";
		print(ball.angular_velocity);
		std::cout<<std::endl;
	}

	//def move(self, ball):
	void move(Ball &ball, std::vector<Ball> &balls, float frameTime)
	{
		ball.position += ball.velocity * glm::vec3(frameTime);

		apply_friction(ball, frameTime);

		// rotation
		ball.rotation = glm::cross(ball.rotation, glm::normalize(glm::angleAxis(frameTime*modulus(ball.angular_velocity), ball.angular_velocity)));
		ball.rotation = glm::normalize(ball.rotation);

		std::cout<<"<rotation> "<<glm::angle(ball.rotation)<<"\t"<<glm::angle(ball.rotation)/PI*180<<"\t";
		glm::vec3 axis = glm::axis(ball.rotation);
		print(axis);
		print(ball.position);

		glm::vec3 dist = balls[0].position-balls[1].position;
		std::cout<<"\ndist "<<modulus(dist)<<"\n";

		check_fell(ball);
		//check_rebounce(ball);

		if (ball.responsed || !ball.living)
		{
			return;
		}

		const float collide_dist = BALL_DIAMETER * BALL_DIAMETER;
		for (std::vector<Ball>::iterator i = balls.begin(); i!=balls.end(); i++)
		{
			if (ball.number != (*i).number)
			{
				if (modulus_square(ball.position - (*i).position) <= collide_dist)
				{
					response(ball, *i);
					ball.responsed = true;
					(*i).responsed = true;
					//self.scene.bounce_sound.play()
				}
				//if (collide(ball, *i))
				//{
				//}
			}
		}
	}

};
