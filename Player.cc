#include "Player.h"

#include <iostream>

player::player()
{

	std::string path0 = "Assets/ship.png";
	std::string path1 = "Assets/ship_right.png";
	std::string path2 = "Assets/ship_left.png";

	set_sprite(path0, path1, path2);
}

void player::movePlayer(sf::Vector2f direction, float dt, const sf::Vector2u& window_size)
{
	sf::Vector2f new_pos = get_position() + speed * direction * dt;


	if (!(new_pos.x > window_size.x - get_sprite().at(0).getGlobalBounds().width || new_pos.x < 0))
	{
		set_position(new_pos, (int)get_sprite().size());
	}
}

