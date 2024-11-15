#include "EnemyManager.h"
#include "random"

constexpr float kSpawnPeriod = 2.f;

EnemyManager::EnemyManager()
{

	enemies_.reserve(20);

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

			enemies_.emplace_back(0);
			break;

		case 1:

			enemies_.emplace_back(1);
			break;

		case 2:

			enemies_.emplace_back(2);
			break;

		case 3:

			enemies_.emplace_back(3);
			break;

		default:
			break;
		} 

		std::uniform_real_distribution<float> uniform_dist_pos(0, window_size.x);
		enemies_.back().SetPosition(uniform_dist_pos(engine), 0);

		spawn_timer = 0;
	}

	//Clean unused enemies
	auto removed_elt = std::remove_if(enemies_.begin(), enemies_.end(), [](const Enemies& e) { return e.IsReallyDead(); });
	if (removed_elt != enemies_.end())
	{
		enemies_.erase(removed_elt, enemies_.end());
	}

	//Move remaining not dead enemies
	for (Enemies& e : enemies_)
	{
		if (!e.IsDead())
		{
			e.Refresh(dt_);
			e.Move(dt_, window_size);

			switch (e.GetType())
			{
			case 0:
				if (e.GetTimer() > e.GetTimerLimit() || e.GetPosition().x >= window_size.x - e.GetSize().x / 2 || e.GetPosition().x <= 0 + e.GetSize().x / 2)
				{
					e.SetDir({ -e.GetDir().x, e.GetDir().y });
					e.ResetTimer();
				}
			case 1:
				if (e.GetPosition().x >= window_size.x - e.GetSize().x / 2 || e.GetPosition().x <= 0 + e.GetSize().x / 2)
				{
					e.SetDir({-e.GetDir().x, e.GetDir().y});
				}
				break;
			default:
				break;
			}

			if (e.GetDir().x > 0)
			{
				e.SetState(1);
			}
			else if (e.GetDir().x < 0)
			{
				e.SetState(2);
			}
			else
			{
				e.SetState(0);
			}

			if (e.IsShootReady())
			{
				std::random_device rn_device;
				std::default_random_engine engine(rn_device());
				std::uniform_real_distribution<float> enemy_projectiles_angle(-300, 300);

				switch (e.GetType())
				{
				case 0:

					enemy_projectiles_.Spawn(e.GetPosition(), { e.GetProjectileDir().x, e.GetProjectileDir().y }, 10, 2);
					enemy_projectiles_.Spawn(e.GetPosition(), { -e.GetProjectileDir().x, e.GetProjectileDir().y }, 10, 2);

					break;

				case 1:
					e.SetProjectileDir({ enemy_projectiles_angle(engine),e.GetProjectileDir().y });
					enemy_projectiles_.Spawn(e.GetPosition(), { e.GetProjectileDir().x, e.GetProjectileDir().y }, 10, 3);
					break;

				case 2:

					enemy_projectiles_.Spawn(e.GetPosition(), { e.GetProjectileDir().x, e.GetProjectileDir().y }, 10, 4);
					enemy_projectiles_.Spawn(e.GetPosition(), { 0, e.GetProjectileDir().y }, 10, 4);
					enemy_projectiles_.Spawn(e.GetPosition(), { -e.GetProjectileDir().x, e.GetProjectileDir().y }, 10, 4);
					break;

				case 3:

					enemy_projectiles_.Spawn(e.GetPosition(), { e.GetProjectileDir().x, e.GetProjectileDir().y }, 10, 5);
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
	for (Enemies e : enemies_)
	{
		if (!e.IsDead())
		{
			target.draw(e);
		}
	}
}
