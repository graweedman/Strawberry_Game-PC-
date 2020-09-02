#include "Game.h"
//Constructors / Destructors

//Init functions
void Game::initVariables()
{
	this->window = nullptr;
	this->dt = 0.f;
}
void Game::initWindow()
{
	std::ifstream ifs("Config/window.ini");
	this->videoModes = sf::VideoMode::getFullscreenModes();

	std::string title = "None";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	bool fullscreen = false;
	unsigned framerate_limit = 120;
	bool vertical_sync_enable = false;
	unsigned antialiasing_level = 0;

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> fullscreen;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enable;
		ifs >> antialiasing_level;
	}
	ifs.close();
	
	windowSettings.antialiasingLevel = antialiasing_level;
	if (fullscreen)
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
	else
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
	
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enable);
}
void Game::initKeys()
{
	std::ifstream ifs("Config/Supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;

		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}
	}
	ifs.close();

	this->supportedKeys["Escape"] = sf::Keyboard::Key::Escape;
	this->supportedKeys["A"] = sf::Keyboard::Key::A;
	this->supportedKeys["D"] = sf::Keyboard::Key::D;
	this->supportedKeys["W"] = sf::Keyboard::Key::W;
	this->supportedKeys["S"] = sf::Keyboard::Key::S; 
//Debug REMOVE LATER
	for (auto i : this->supportedKeys)
	{
		std::cout << i.first << " " << i.second << "\n";

	}
}
void Game::initStates()
{
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
	//this->states.push(new GameState(this->window, &this->supportedKeys));
}

//Constructors / Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initKeys();
	this->initStates();
	
	
}
Game::~Game()
{
	delete this->window;

	//Deletes all the states from memory
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

//Accesors
const bool Game::running() const
{
	return this->window->isOpen();
}
//Functions

//Regulars
void Game::endApplication()
{
	std::cout << "Ending Apllication" << "\n";
}

void Game::updateDt()
{
	/*Updates dt variable with the time it takes to update and render one frame. */
	this->dt = dtClock.restart().asSeconds();
}

void Game::pollEvents()
{
	//Event polling 
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
		}
	}
}

void Game::Update()
{
	this->pollEvents();

	//Update states
	if (!this->states.empty())
	{
		this->states.top()->Update(this->dt);
		//Exits top state doing the end State function
		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}

	//Aplication End
	else
	{
		this->endApplication();
		this->window->close();
	}

	//Update mouse position
	//Relatvie to the screen
	//std::cout << "Mouse pos: " << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << std::endl;
	//Relative to the window
	/*std::cout << "Mouse pos: "
		<< sf::Mouse::getPosition(*this->window).x << " "
		<< sf::Mouse::getPosition(*this->window).y << std::endl;*/
}

void Game::render()
{
	/*
	*  -clear old frame
	*  -render objects
	*  -display frame in window
	* 
	*  Render game objects
	*/
	this->window->clear(); //Clear old frame

		//Draw Game
	//Render states
	if (!this->states.empty())
	{
		this->states.top()->render(this->window);//render top State
	}

	this->window->display(); //Tell app that window is done drawing
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->Update();
		this->render(); 
	}
}
