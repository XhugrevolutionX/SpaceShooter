#include "EnemyManager.h"

#include "projectile_manager.h"
#include "random"

constexpr float kSpawnPeriod = 1.5f;

void EnemyManager::Refresh(float dt_, const sf::Vector2u& window_size, ProjectileManager& enemy_projectiles_)
{
	spawn_timer += dt_;
	if (spawn_timer > kSpawnPeriod)
	{
		enemies_.emplace_back();

		// Seed with a real random value, if available
		std::random_device rn_device_x;
		// Choose a random mean between min and max
		std::default_random_engine engine_x(rn_device_x());
		std::uniform_real_distribution<float> uniform_dist_x(0, window_size.x);

		enemies_.back().SetPosition(uniform_dist_x(engine_x), 0);

		spawn_timer = 0;
	}

	//Clean unused projectiles
	auto removed_elt = std::remove_if(enemies_.begin(), enemies_.end(), [](const Entity& p) { return p.IsDead(); });
	if (removed_elt != enemies_.end())
	{
		enemies_.erase(removed_elt, enemies_.end());
	}

	//Move remaining projectiles
	for (Enemy& e : enemies_)
	{
		e.Refresh(dt_);
		e.Move(dt_, window_size);

		if (e.IsShootReady())
		{
			// Seed with a real random value, if available
			std::random_device rn_device;
			// Choose a random mean between min and max
			std::default_random_engine engine(rn_device());
			std::uniform_real_distribution<float> uniform_dist(-100, 100);


			enemy_projectiles_.Spawn(e.GetPosition(), { uniform_dist(engine), 750});
		}
	}
}

void EnemyManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (Enemy e : enemies_)
	{
		target.draw(e);
	}
}