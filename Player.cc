#include "Player.h"

#include <iostream>

player::player()
{

	std::string path0 = "Assets/red_ship.png";
	sf::Vector2i pos = {0,0};
	sf::Vector2i size = {64,64 };

	set_sprite(path0, pos, size, 3);
}

void player::movePlayer(sf::Vector2f direction, float dt, const sf::Vector2u& window_size)
{
	sf::Vector2f new_pos = get_position() + speed * direction * dt;


	if (!(new_pos.x > window_size.x - get_sprite().at(0).getGlobalBounds().width || new_pos.x < 0 || new_pos.y > window_size.y - get_sprite().at(0).getGlobalBounds().height || new_pos.y < 700))
	{
		set_position(new_pos, static_cast<int>(get_sprite().size()));
	}

}
 
