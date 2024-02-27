#pragma once

#include <string>
#include "SDL.h"
//#include "Components.h"
#include "ECS.h"

class ColliderComponent : public Component 
{
public:
	SDL_Rect collider;		// collider dimensions
	std::string tag;		// when we detect the collision grab the tag to determine type of action to happen (i.e. player-enemy, player-scenery, etc.)

	TransformComponent* transform;

	ColliderComponent(std::string t)
	{
		tag = t;
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}

		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override
	{
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;
	}

};
