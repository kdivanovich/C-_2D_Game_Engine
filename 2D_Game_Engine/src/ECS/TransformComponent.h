#pragma once

#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component
{

public:
	Vector2D position;
	Vector2D velocity;

	int height = 32; 
	int width = 32; 
	int scale = 1;

	int speed = 3;

	TransformComponent()
	{
		position.ZeroFloat();
	}

	TransformComponent(int sc)
	{
		position.Zero();
		scale = sc;
	}

	TransformComponent(float x, float y)
	{
		position.ZeroFloat();
	}

	TransformComponent(float x, float y, int h, int w, int sc)		// sc = scale
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override
	{
		velocity.Zero();	 
	}

	void update() override
	{
		position.x += velocity.x * speed; 
		position.y += velocity.y * speed;
	}

	/*void setPos(int x, int y)
	{
		xPos = x;
		yPos = y;
	}*/

	/*void init() override
	{
		xPos = 0;
		yPos = 0;
	}*/
};