#pragma once
#include <iostream>
#include <fstream>
#include <sstream>


#include <sfml/Graphics.hpp>
#include <sfml/System.hpp>
#include <sfml/Window.hpp>
#include <sfml/Audio.hpp>

enum button_states{ BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};
class Button
{
private:
	short unsigned buttonState;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	//Functions
	

public:
	Button(float x, float y, float width, float height,
		sf::Font* font, std::string text,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	~Button();
	//Accesors
	const bool isPressed() const;

	//Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
};

