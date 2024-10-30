#include "Player.h"

player::player()
{

	std::string path0 = "Assets/ship.png";
	std::string path1 = "Assets/ship_right.png";
	std::string path2 = "Assets/ship_left.png";

	set_sprite(path0, path1, path2);

	set_position({ 960,810 }, get_sprite().size());


}

void player::movePlayer(sf::Vector2f direction, float dt)
{
	set_position(get_position() + speed * direction * dt, (int)get_sprite().size());
}

