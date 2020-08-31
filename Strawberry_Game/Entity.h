#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <vector>


#include <sfml/Graphics.hpp>
#include <sfml/System.hpp>
#include <sfml/Window.hpp>
#include <sfml/Audio.hpp>
#include <sfml/Network.hpp>
class Entity
{
private:

protected:
	sf::RectangleShape shape;
	float movementSpeed;

public:
	Entity();
	virtual ~Entity();

	//Functions
	virtual void move(const float& dt, const float x, const float y);

	virtual void Update(const float& dt);
	virtual void render(sf::RenderTarget* target);

};

