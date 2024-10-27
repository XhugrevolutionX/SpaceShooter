#include "Player.h"

player::player()
{

	std::string path0 = "./Assets/Player0.png";
	std::string path1 = "./Assets/Player1.png";
	std::string path2 = "./Assets/Player2.png";

	
	set_sprite(path0, path1, path2);

	set_position({ 960,540 }, 3);
}

void player::movePlayer(sf::Vector2f direction, float dt)
{
	set_position(get_position() + speed * direction * dt, (int)get_sprite().size());
}

