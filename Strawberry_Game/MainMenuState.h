#pragma once

#include "GameState.h"
#include "Button.h"
class MainMenuState :
	public State
{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	//Objects
	std::map<std::string, Button*> buttons;

	//Initializer Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();
	//Constructor/Deconsturctor
public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();
	//Functions
	void endState();
	void updateInput(const float& dt);
	void updateButtons();
	void Update(const float& dt);
	void renderButtons(sf::RenderTarget* target = nullptr);
	void render(sf::RenderTarget* target = nullptr); 
};

