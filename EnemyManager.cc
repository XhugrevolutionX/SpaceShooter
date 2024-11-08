#include "EnemyManager.h"

#include "ProjectileManager.h"
#include "random"



constexpr float kSpawnPeriod = 1.5f;

void EnemyManager::Refresh(float dt_, const sf::Vector2u& window_size, ProjectileManager& enemy_projectiles_)
{
	std::random_device rn_device;
	std::default_random_engine engine(rn_device());

	spawn_timer += dt_;
	if (spawn_timer > kSpawnPeriod)
	{
		std::uniform_real_distribution<float> uniform_dist_dir(-50, 50);
		sf::Vector2f dir = { uniform_dist_dir(engine), 200};

		enemies_.emplace_back(dir);

		std::uniform_real_distribution<float> uniform_dist_pos(0, window_size.x);
		enemies_.back().SetPosition(uniform_dist_pos(engine), 0);

		spawn_timer = 0;
	}

	//Clean unused enemies
	auto removed_elt = std::remove_if(enemies_.begin(), enemies_.end(), [](const Entity& e) { return e.IsDead(); });/*change to IsReallyDead*/
	if (removed_elt != enemies_.end())
	{
		enemies_.erase(removed_elt, enemies_.end());
	}

	//Move remaining not dead enemies
	for (Enemy& e : enemies_)
	{
		if (!e.IsDead())
		{
			e.Refresh(dt_);
			e.Move(dt_, window_size);

			if (e.IsShootReady())
			{
				float dir_y = 750;
				std::uniform_real_distribution<float> enemy_projectiles_angle(-300, 300);
				float dir_x = enemy_projectiles_angle(engine);
				enemy_projectiles_.Spawn(e.GetPosition(), { dir_x, dir_y }, 180 - (atan(dir_x / dir_y) * 180 / 3.1415), 0);
			}
		}
	}
}

void EnemyManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (Enemy e : enemies_)
	{
		if (!e.IsDead())
		{
			target.draw(e);
		}
	}
}
