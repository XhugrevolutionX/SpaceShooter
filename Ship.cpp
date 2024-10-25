#include "Ship.h"

void ship::set_sprite(std::string &text1_path)
{
	this->sprites.resize(1);

	sf::Texture text1;

	text1.loadFromFile(text1_path);


	this->sprites.at(0).setTexture(text1);
}
void ship::set_sprite(std::string &text1_path, std::string &text2_path)
{
	this->sprites.resize(2);

	sf::Texture text1;
	sf::Texture text2;

	text1.loadFromFile(text1_path);
	text2.loadFromFile(text2_path);


	this->sprites.at(0).setTexture(text1);
	this->sprites.at(1).setTexture(text2);
}
void ship::set_sprite(std::string &text1_path, std::string &text2_path, std::string &text3_path)
{
	this->sprites.resize(3);

	sf::Texture text1;
	sf::Texture text2;
	sf::Texture text3;

	text1.loadFromFile(text1_path);
	text2.loadFromFile(text2_path);
	text3.loadFromFile(text3_path);

	this->sprites.at(0).setTexture(text1);
	this->sprites.at(1).setTexture(text2);
	this->sprites.at(2).setTexture(text3);
}

void ship::draw_ship(sf::RenderWindow &window, int frame)
{
	window.draw(this->sprites.at(frame));
}

void ship::set_position(sf::Vector2f pos, int nb_sprites)
{
	for (int n = 0; n < nb_sprites; n++)
	{
		this->sprites.at(n).setPosition(pos);
	}
}

sf::Vector2f ship::get_position()
{
	return this->sprites.at(0).getPosition();
}