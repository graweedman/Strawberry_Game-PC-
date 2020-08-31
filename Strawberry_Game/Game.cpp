#include "Game.h"
//Constructors / Destructors

//Private functions
void Game::initVariables()
{
	this->window = nullptr;
}
void Game::initWindow()
{
	std::ifstream ifs("Config/window.ini");

	std::string title = "None";
	sf::VideoMode window_bounds(800, 600);
	unsigned framerate_limit = 120;
	bool vertical_sync_enable = false;

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enable;
	}
	ifs.close();

	this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enable);
}

void Game::initKeys()
{
	this->supportedKeys.emplace("Escape", sf::Keyboard::Key::Escape);
	this->supportedKeys.emplace("A", sf::Keyboard::Key::A);
	this->supportedKeys.emplace("D", sf::Keyboard::Key::D);
	this->supportedKeys.emplace("W", sf::Keyboard::Key::W);
	this->supportedKeys.emplace("S", sf::Keyboard::Key::S);

	std::cout << this->supportedKeys.at("A") << "\n";
}

void Game::initStates()
{
	this->states.push(new GameState(this->window, &this->supportedKeys));
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
