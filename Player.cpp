#include "Player.h"

void player::initialize()
{
	sf::Vector2f pos = { 960,540 };
	std::string path0 = "./Assets/Player0.png";
	std::string path1 = "./Assets/Player1.png";
	std::string path2 = "./Assets/Player2.png";

	this->set_sprite(path0, path1, path2);
	this->set_position(pos, 3);
}
