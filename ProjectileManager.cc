#include "ProjectileManager.h"

#include <complex>
#include <random>

ProjectileManager::ProjectileManager()
{
	sfx.loadFromFile("Assets/laser.mp3");
	sound_projectile.setBuffer(sfx);
}
void ProjectileManager::Spawn(sf::Vector2f spawn_position, sf::Vector2f dir,float volume, int projectile_type)
{

	std::random_device rn_device;
	std::default_random_engine engine(rn_device());
	std::uniform_real_distribution<float> rng_pitch(0.6f, 1.f);

	projectiles_.emplace_back(projectile_type);
	projectiles_.back().SetDirection(dir);

	if (projectile_type >= 2)
	{
		projectiles_.back().SetRotation(180 + (atan(-dir.x / dir.y) * 180 / 3.1415));

	}
	else
	{
		projectiles_.back().SetRotation((atan(-dir.x / dir.y) * 180 / 3.1415));

	}

	if (dir.y > 0)
	{
		projectiles_.back().SetPosition({ spawn_position.x, spawn_position.y + (projectiles_.back().HitBox().getSize().y / 2) });
	}
	else
	{
		projectiles_.back().SetPosition({ spawn_position.x, spawn_position.y - (projectiles_.back().HitBox().getSize().y / 2) });
	}

	if (sound_timer >= sound_timer_limit)
	{
		sound_projectile.setVolume(volume);
		sound_projectile.setPitch(rng_pitch(engine));
		sound_projectile.play();
	}
}

void ProjectileManager::Refresh(float dt_, const sf::Vector2u& window_size)
{
	//Clean unused projectiles
	auto removed_elt = std::remove_if(projectiles_.begin(), projectiles_.end(), [](const Entity& e) { return e.IsDead(); });
	if (removed_elt != projectiles_.end())
	{
		projectiles_.erase(removed_elt, projectiles_.end());
	}

	//Move remaining projectiles
	for (Entity& e : projectiles_)
	{
		e.Move(dt_, window_size);

	}
	sound_timer += dt_;
}

void ProjectileManager::CheckCollisions(std::vector<Asteroid>& asteroids_, player& player, sf::Text& player_score_display)
{
	for (auto& p : projectiles_)
	{
		for (auto& a : asteroids_)
		{
			if (p.IsDead() == false && a.IsDead() == false && p.Intersects(a.HitBox()))
			{
				p.SetDeath();
				a.SetDeath();
				if (a.IsDead())
				{
					player.SetScore(5);
				}
			}
		}
	}

	std::string str_score = std::to_string(player.GetScore());
	str_score.append(" Points");
	player_score_display.setString(str_score);
}

void ProjectileManager::CheckCollisions(std::vector<Enemies>& enemies, player& player, sf::Text& player_score_display)
{
	for (auto& e : enemies)
	{
		for (auto& p : projectiles_)
		{
			if (p.IsDead() == false && e.IsDead() == false && p.Intersects(e.HitBox()))
			{
				p.SetDeath();
				e.Damage(1);
				if (e.IsDead())
				{
					switch (e.GetType())
					{
					case 0:
						player.SetScore(10);
						break;
					case 1:
						player.SetScore(40);
						break;
					case 2:
						player.SetScore(30);
						break;
					case 3:
						player.SetScore(20);
						break;
					default:
						break;
					}

	
				}
			}
		}
	}
	std::string str_score = std::to_string(player.GetScore());
	str_score.append(" Points");
	player_score_display.setString(str_score);
}

void ProjectileManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (Projectile p : projectiles_)
	{
		target.draw(p);
	}
}
