#include "Ship.h"

void ship::set_sprite(std::string &texture1_path)
{
	sprites.resize(1);

	texture1.loadFromFile(texture1_path);

	sprites.at(0).setTexture(texture1);
	sprites.at(0).setOrigin(0, 0);
}
void ship::set_sprite(std::string &texture1_path, std::string &texture2_path)
{
	sprites.resize(2);

	texture1.loadFromFile(texture1_path);
	texture2.loadFromFile(texture2_path);

	sprites.at(0).setTexture(texture1);
	sprites.at(0).setOrigin(0, 0);
	sprites.at(1).setTexture(texture2);
	sprites.at(1).setOrigin(0, 0);
}
void ship::set_sprite(std::string &texture1_path, std::string &texture2_path, std::string &texture3_path)
{
	sprites.resize(3);

	texture1.loadFromFile(texture1_path);
	texture2.loadFromFile(texture2_path);
	texture3.loadFromFile(texture3_path);

	sprites.at(0).setTexture(texture1);
	sprites.at(0).setOrigin(0, 0);
	sprites.at(1).setTexture(texture2);
	sprites.at(1).setOrigin(0, 0);
	sprites.at(2).setTexture(texture3);
	sprites.at(2).setOrigin(0, 0);
}

void ship::draw_ship(sf::RenderWindow &window, int frame)
{
	window.draw(sprites.at(frame));
}

void ship::set_position(sf::Vector2f pos, int nb_sprites)
{
	for (int n = 0; n < nb_sprites; n++)
	{
		sprites.at(n).setPosition(pos);
	}
}

sf::Vector2f ship::get_position()
{
	return sprites.at(0).getPosition();
}
