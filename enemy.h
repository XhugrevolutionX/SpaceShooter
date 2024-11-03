#ifndef ENEMIES_H
#define ENEMIES_H
#include "projectile_manager.h"
#include "Ship.h"

class enemy : public ship
{

private:
	static int counter_;

	sf::Vector2f direction_;

	bool is_dead_ = false;

public:
	enemy();
	void Move(float dt, const sf::Vector2u& window_size);
	bool IsDead() const { return is_dead_; }

	void check_collision(float dt, ProjectileManager& projectile_manager_);

};




#endif
