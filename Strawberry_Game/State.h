#pragma once

#include "Entity.h"

class State
{
private:
	
	
	
	

	//Resources
	std::vector<sf::Texture> textures;
	//Functions
	virtual void initKeybinds() = 0;

protected:
	sf::RenderWindow* window;
	std::stack<State*>* states;
	bool quit;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;	

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	

public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	//Functions
	const bool& getQuit() const;

	virtual void checkForQuit();

	virtual void endState() = 0;
	virtual void updateMousePositions();
	virtual void updateInput(const float& dt) = 0;
	virtual void Update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

