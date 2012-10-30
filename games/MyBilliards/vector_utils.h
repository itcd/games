#pragma once

#include "parameter.h"

glm::vec3 normalize(const glm::vec3 &v)
{
	glm::vec3 r;
	float mod = sqrt(v.x*v.x + v.y*v.y +v.z*v.z);
	if(mod > std::numeric_limits<float>::epsilon())
	{
		r.x = v.x / mod;
		r.y = v.y / mod;
		r.z = v.z / mod;
	}
	return r;
}

float dot_product(const glm::vec3 &v1, const glm::vec3 &v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

glm::vec3 cross_product(const glm::vec3 &v1, const glm::vec3 &v2)
{
	glm::vec3 v;
	v.x = v1.y*v2.z-v1.z*v2.y;
	v.y = v1.z*v2.x-v1.x*v2.z;
	v.z = v1.x*v2.y-v1.y*v2.x;
	return v;
}

float modulus_square(const glm::vec3 &v)
{
	return v.x*v.x+v.y*v.y+v.z*v.z;
}

float modulus(const glm::vec3 &v)
{
	return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}

float cos(const glm::vec3 &v1, const glm::vec3 &v2)
{
	if (modulus(v1)==0 || modulus(v2)==0)
		return 0;
	else
		return dot_product(v1,v2)/(modulus(v1)*modulus(v2));
}

void print(const glm::vec3 &v)
{
	std::cout<<"["<<v.x<<","<<v.y<<","<<v.z<<"]"<<std::endl;
}