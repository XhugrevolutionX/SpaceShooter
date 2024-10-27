#ifndef PLAYER_H
#define PLAYER_H
#include "Ship.h"

class player : public ship
{

private:
	std::string name;
	const float speed = 200.0f;
public:

	player();
	void set_name(std::string name_) { name = name_; }
	std::string get_name() { return name; }
	void movePlayer(sf::Vector2f direction, float dt);
};






#endif
