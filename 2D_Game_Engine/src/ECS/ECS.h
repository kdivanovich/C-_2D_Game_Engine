#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

// Entity Component System 

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T>											// short function so I made it inline 
inline ComponentID getComponentTypeID() noexcept				// noexcept performs a compile-time check that returns true if 
{																// an expression is declared to not throw any exceptions.
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32; 

using ComponentBitSet = std::bitset<maxComponents>;				// declare it this way to use it as an obj "type" of sorts 
using ComponentArray = std::array<Component*, maxComponents>;	// check if an entity has got a selection of components

class Component													// make "final" if you want to prevent inheritance 
{
public:
	Entity* entity;

	virtual void init() {}		// to override
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}
};

class Entity
{
private:
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;

public:
	void update()		// the entity will loop through its components calling update() and draw()
	{
		for (auto& c : components) c->update();
	}

	void draw() 
	{
		for (auto& c : components) c->draw();
	}
	bool isActive() { return active; }
	void destroy() { active = false; }

	template<typename T> 
	bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}

	template<typename T, typename... TArgs>		// TArgs for a variadic template parameter
	T& addComponent(TArgs&&... MArgs)			// The && indicates that the arguments are forwarding references, which means they can bind to both lvalues and rvalues, preserving the value category of the argument.
	{
		T* c(new T(std::forward<TArgs>(MArgs)...));		// Dynamically allocates a new obj of type T on the heap and constructs it using perfect forwarding for MArgs
		c->entity = this;						// This line sets a member variable named entity in the newly created component c to the current entity (this). 
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;	// add a position component -> gets put in the same position in the array
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template<typename T> 
	T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager
{
private:
	std::vector <std::unique_ptr<Entity>> entities;
public:
	void update()
	{
		for (auto& e : entities) e->update();
	}

	void draw()
	{
		for (auto& e : entities) e->draw();
	}

	void refresh()		// remove entities if they are not active 
	{
		// erase() - Removes all elements satisfying specific criteria from the range[first, last) and returns a past-the-end iterator for the new end of the range.
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
	}

	Entity& addEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}

};