#include "EnemyManager.h"
#include "random"



constexpr float kSpawnPeriod = 2.f;

void EnemyManager::Refresh(float dt_, const sf::Vector2u& window_size, ProjectileManager& enemy_projectiles_)
{
	std::random_device rn_device;
	std::default_random_engine engine(rn_device());

	spawn_timer += dt_;
	if (spawn_timer > kSpawnPeriod)
	{
		std::uniform_real_distribution<float> rng_enemies(0, 2);
		int enemy_type = static_cast<int>(rng_enemies(engine));

		switch (enemy_type)
		{
		case 0:

			green_ships_.emplace_back();

			enemies_.emplace_back(green_ships_.back());
			break;

		case 1:

			std::uniform_real_distribution<float> yellow_ship_rng_dir_x(-50, 50);
			float yellow_dir_x = yellow_ship_rng_dir_x(engine);
			sf::Vector2f yellow_dir = { yellow_dir_x, 200 };
			yellow_ships_.emplace_back(yellow_dir);

			//if (yellow_dir_x > 0)
			//{
			//	yellow_ships_.back().SetState(1);
			//}
			//else if (yellow_dir_x < 0)
			//{
			//	yellow_ships_.back().SetState(2);
			//}
			//else
			//{
			//	yellow_ships_.back().SetState(0);
			//}

			enemies_.emplace_back(yellow_ships_.back());

			break;
		}

		std::uniform_real_distribution<float> uniform_dist_pos(0, window_size.x);
		enemies_.back().SetPosition(uniform_dist_pos(engine), 0);

		spawn_timer = 0;
	}

	//Clean unused enemies
	auto removed_elt = std::remove_if(enemies_.begin(), enemies_.end(), [](const Enemy& e) { return e.IsReallyDead(); });
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
				std::random_device rn_device;
				std::default_random_engine engine(rn_device());
				std::uniform_real_distribution<float> enemy_projectiles_angle(-300, 300);
				float yellow_dir_x = enemy_projectiles_angle(engine);
				float green_dir_x = 300;
				float dir_y = 750;


				switch (e.GetType())
				{
				case 0:

					enemy_projectiles_.Spawn(e.GetPosition(), { green_dir_x, dir_y }, 180 - (atan(300 / dir_y) * 180 / 3.1415), 10, 1);
					enemy_projectiles_.Spawn(e.GetPosition(), { -green_dir_x, dir_y }, 180 - (atan(-300 / dir_y) * 180 / 3.1415), 10, 1);

					break;

				case 1:

					enemy_projectiles_.Spawn(e.GetPosition(), { yellow_dir_x, dir_y }, 180 - (atan(yellow_dir_x / dir_y) * 180 / 3.1415), 10, 2);
					break;

				default:
					break;
				}
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
