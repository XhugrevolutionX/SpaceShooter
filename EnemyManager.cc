#include "EnemyManager.h"
#include "random"



constexpr float kSpawnPeriod = 2.f;


EnemyManager::EnemyManager()
{

	std::random_device rn_device;
	std::default_random_engine engine(rn_device());
	std::uniform_real_distribution<float> yellow_ship_rng_dir_x(-50, 50);
	float yellow_dir_x = yellow_ship_rng_dir_x(engine);

	green_ship_dir = { 0, 200 };
	yellow_ship_dir = { yellow_dir_x, 200 };
	purple_ship_dir = { 0, 200 };
	white_ship_dir = { 0, 200 };

}


void EnemyManager::Refresh(float dt_, const sf::Vector2u& window_size, ProjectileManager& enemy_projectiles_)
{
	std::random_device rn_device;
	std::default_random_engine engine(rn_device());

	spawn_timer += dt_;
	if (spawn_timer > kSpawnPeriod)
	{
		std::uniform_real_distribution<float> rng_enemies(0, 4);
		int enemy_type = static_cast<int>(rng_enemies(engine));

		switch (enemy_type)
		{
		case 0:

			green_ships_.emplace_back(green_ship_dir);

			//if (green_dir_x > 0)
			//{
			//	green_ships_.back().SetState(1);
			//}
			//else if (green_dir_x < 0)
			//{
			//	green_ships_.back().SetState(2);
			//}
			//else
			//{
			//	green_ships_.back().SetState(0);
			//}

			enemies_.emplace_back(green_ships_.back());
			break;

		case 1:

			yellow_ships_.emplace_back(yellow_ship_dir);

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

		case 2:

			purple_ships_.emplace_back(purple_ship_dir);

			//if (purple_dir_x > 0)
			//{
			//	purple_ships_.back().SetState(1);
			//}
			//else if (purple_dir_x < 0)
			//{
			//	purple_ships_.back().SetState(2);
			//}
			//else
			//{
			//	purple_ships_.back().SetState(0);
			//}

			enemies_.emplace_back(purple_ships_.back());
			break;

		case 3:

			white_ships_.emplace_back(white_ship_dir);

			//if (white_dir_x > 0)
			//{
			//	white_ships_.back().SetState(1);
			//}
			//else if (white_dir_x < 0)
			//{
			//	white_ships_.back().SetState(2);
			//}
			//else
			//{
			//	white_ships_.back().SetState(0);
			//}

			enemies_.emplace_back(white_ships_.back());
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

				switch (e.GetType())
				{
				case 0:

					enemy_projectiles_.Spawn(e.GetPosition(), { e.GetProjectileDir().x, e.GetProjectileDir().y }, 180 - (atan(e.GetProjectileDir().x / e.GetProjectileDir().y) * 180 / 3.1415), 10, 2);
					enemy_projectiles_.Spawn(e.GetPosition(), { -e.GetProjectileDir().x, e.GetProjectileDir().y }, 180 - (atan(-e.GetProjectileDir().x / e.GetProjectileDir().y) * 180 / 3.1415), 10, 2);

					break;

				case 1:
					e.SetProjectileDir({ enemy_projectiles_angle(engine),e.GetProjectileDir().y });
					enemy_projectiles_.Spawn(e.GetPosition(), { e.GetProjectileDir().x, e.GetProjectileDir().y }, 180 - (atan(e.GetProjectileDir().x / e.GetProjectileDir().y) * 180 / 3.1415), 10, 3);
					break;

				case 2:

					enemy_projectiles_.Spawn(e.GetPosition(), { e.GetProjectileDir().x, e.GetProjectileDir().y }, 180 - (atan(e.GetProjectileDir().x / e.GetProjectileDir().y) * 180 / 3.1415), 10, 4);
					enemy_projectiles_.Spawn(e.GetPosition(), { 0, e.GetProjectileDir().y }, 180 - (atan(0 / e.GetProjectileDir().y) * 180 / 3.1415), 10, 4);
					enemy_projectiles_.Spawn(e.GetPosition(), { -e.GetProjectileDir().x, e.GetProjectileDir().y }, 180 - (atan(-e.GetProjectileDir().x / e.GetProjectileDir().y) * 180 / 3.1415), 10, 4);
					break;

				case 3:

					enemy_projectiles_.Spawn(e.GetPosition(), { e.GetProjectileDir().x, e.GetProjectileDir().y }, 180 - (atan(e.GetProjectileDir().x / e.GetProjectileDir().y) * 180 / 3.1415), 10, 5);
					if (e.GetProjectileDir().x >= 500)
					{
						e.SetProjectileDir({ -500, e.GetProjectileDir().y });
					}
					else
					{
						e.SetProjectileDir({ e.GetProjectileDir().x + 200, e.GetProjectileDir().y });
					}
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
