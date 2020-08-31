#pragma once

#include "GameState.h"
/* Class that acts as game engine */

class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* window; //Window class
	
	sf::Event ev; //Event

	sf::Clock dtClock;
	float dt; //Delta time

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;


	//GameObjects
	sf::Sprite enemy;
	sf::Texture enemyTexture;
	
	


	//private functions
	//Init
	void initVariables();
	void initWindow();
	void initKeys();
	void initStates();
	

public:
	//Constructors / Destructors
	Game();
	virtual ~Game();
	//Accesors
	const bool running() const;
	 
	//Functions

	//Regular
	void endApplication();


	//Update
	void updateDt();
	void pollEvents();
	void Update();
	
	//Render
	void render();

	//Core
	void run();
};

