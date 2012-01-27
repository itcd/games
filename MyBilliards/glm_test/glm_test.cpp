#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
using namespace std;
using namespace glm;

int foo()
{
	glm::vec4 Position = glm::vec4(glm:: vec3(0.0f), 1.0f);
	//glm::mat4 Model = glm::translate(1.0f, 1.0f, 1.0f);
	//glm::vec4 Transformed = Model * Position;
	return 0;
}

void print(vec3 v)
{
	cout<<"("<<v.x<<","<<v.y<<","<<v.z<<")"<<endl;
}

void main()
{
	vec4 Position = vec4(vec3(0.0), 1.0);
	mat4 Model = mat4(1.0);
	Model[4] = vec4(1.0, 1.0, 0.0, 1.0);
	vec4 Transformed = Model * Position;
	foo();

	glm::quat q;
	//mat4 m;
	//m[0][0] = 1;
	//cout<<m[0][0]<<endl<<endl;

	//1,0,1,
	//2,1,0,
	//-3,2,-5

	mat3 m3(	1,0,1,
	2,1,0,
	-3,2,-5);
	//mat3 m3(1,2,-3, 0,1,2, 1,0,-5);
	for (int i=0; i<3; i++)
	{
		vec3 v = m3[i];
		for (int j=0; j<3; j++)
		{
			cout<<v[j]<<ends;
		}
		cout<<endl;
	}
	cout<<endl;
	mat3 m3_i = glm::inverse(m3);
	//mat3 m3_i = m3._inverse();
	for (int i=0; i<3; i++)
	{
		vec3 v = m3_i[i];
		for (int j=0; j<3; j++)
		{
			cout<<v[j]<<ends;
		}
		cout<<endl;
	}

	vec3 a(1,2,3);
	vec3 b(4,5,6);
	vec3 c=a+b;
	vec3 d=a-b;
	vec3 e=a*b;
	vec3 f=a/b;
	a=2.0f*a*2.0f;
	//a/=3;
	print(a);
	print(b);
	print(c);
	print(d);
	print(e);
	print(f);
}