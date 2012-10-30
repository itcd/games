#pragma once

#include <glm/glm.hpp>

class NPC
{
protected:
	glm::vec2 pos;
	int index;

public:

	NPC(void)
	{
		index = 0;
	}

	NPC(float x, float y)
	{
		pos.x = x;
		pos.y = y;
		index = 0;
	}

	NPC(float x, float y, int sprite_index)
	{
		pos.x = x;
		pos.y = y;
		this->index = sprite_index;
	}

	NPC(const NPC & npc)
	{
		this->pos = npc.pos;
		this->index = npc.index;
	}

	~NPC(void)
	{
	}

	void position(float x, float y)
	{
		pos.x = x;
		pos.y = y;
	}

	void position(glm::vec2 pos)
	{
		this->pos = pos;
	}

	glm::vec2 position()
	{
		return pos;
	}

	int sprite_index()
	{
		return this->index;
	}

	void sprite_index(int index)
	{
		this->index = index;
	}
};
