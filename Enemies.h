#ifndef ENEMIES_H
#define ENEMIES_H
#include "Ship.h"

class enemies : public ship
{

private:
	static int counter_;

	sf::Vector2f direction_;

	bool is_dead_ = false;

public:
	enemies();
	void Move(float dt, const sf::Vector2u& window_size);
	bool IsDead() const { return is_dead_; }

	void check_collision(float dt);

};




#endif
