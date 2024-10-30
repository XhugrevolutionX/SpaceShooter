#ifndef PLAYER_H
#define PLAYER_H
#include "Ship.h"
#include "Projectile.h"

class player : public ship
{

private:
	const float speed = 400.0f;
public:

	player();
	void movePlayer(sf::Vector2f direction, float dt, const sf::Vector2u& window_size);
};






#endif
