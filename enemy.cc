#include "enemy.h"

int enemy::counter_ = 0;

enemy::enemy()
{
	std::string path0 = "Assets/ship.png";
	sf::Vector2i pos = { 0,0 };
	sf::Vector2i size = { 64,64 };

	set_sprites(path0, pos, size, 1);

	direction_ = { 0, 200 };
	counter_++;
}
void enemy::Move(float dt, const sf::Vector2u& window_size)
{
	set_position(getPosition() + direction_ * dt, 1);

	sf::Vector2f pos = getPosition();

	if (pos.y > window_size.y)
	{
		is_dead_ = true;
	}
}

void enemy::check_collision(float dt, ProjectileManager& projectile_manager_)
{
	for (Projectile p : projectile_manager_.get_projectiles())
	{
		if (getPosition() == p.get_hitbox().getPosition())
		{
			is_dead_ = true;
		}
	}
		
}
