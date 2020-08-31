#pragma once

#include "Entity.h"

class State
{
private:
	
	sf::RenderWindow* window;
	bool quit;
	//Resources
	std::vector<sf::Texture> textures;
	//Functions
	virtual void initKeybinds() = 0;

protected:
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;	
	

public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~State();

	//Functions
	const bool& getQuit() const;

	virtual void checkForQuit();

	virtual void endState() = 0;

	virtual void updateInput(const float& dt) = 0;
	virtual void Update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

