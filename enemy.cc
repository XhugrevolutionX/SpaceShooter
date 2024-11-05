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
	sf::Vector2f enemy_pos = get_hitbox().getPosition();
	sf::Vector2f enemy_scale = get_hitbox().getScale();
	sf::Vector2f enemy_lower_bounds = { enemy_pos.x - (enemy_pos.x * enemy_scale.x), enemy_pos.y - (enemy_pos.y * enemy_scale.y) };
	sf::Vector2f enemy_upper_bounds = { enemy_pos.x * enemy_scale.x, enemy_pos.y * enemy_scale.y };


	for (Projectile p : projectile_manager_.get_projectiles())
	{
		sf::Vector2f p_pos = p.get_hitbox().getPosition();
		sf::Vector2f p_scale = p.get_hitbox().getScale();
		sf::Vector2f p_lower_bounds = { p_pos.x - (p_pos.x * p_scale.x), p_pos.y - (p_pos.y * p_scale.y) };
		sf::Vector2f p_upper_bounds = { p_pos.x * p_scale.x, p_pos.y * p_scale.y };

		//not working
		if (p_lower_bounds.x > enemy_upper_bounds.x && p_upper_bounds.x < enemy_lower_bounds.x && p_lower_bounds.y > enemy_upper_bounds.y && p_upper_bounds.y < enemy_lower_bounds.y)
		{
			is_dead_ = true;
		}
	}
		
}
