#include "ProjectileManager.h"

#include <complex>

ProjectileManager::ProjectileManager()
{
	sfx.loadFromFile("Assets/laser.mp3");
	sound_projectile.setBuffer(sfx);
}
void ProjectileManager::Spawn(sf::Vector2f spawn_position, sf::Vector2f dir, float angle, int volume, int projectile_type)
{

	projectiles_.emplace_back(projectile_type);
	projectiles_.back().SetDirection(dir);
	projectiles_.back().SetRotation(angle);

	if (dir.y > 0)
	{
		projectiles_.back().SetPosition({ spawn_position.x, spawn_position.y + (projectiles_.back().HitBox().getSize().y / 2) });
	}
	else
	{
		projectiles_.back().SetPosition({ spawn_position.x, spawn_position.y - (projectiles_.back().HitBox().getSize().y / 2) });
	}


	sound_projectile.setVolume(volume);
	sound_projectile.play();

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

void ProjectileManager::CheckCollisions(std::vector<Enemy>& enemies, player& player, sf::Text& player_score_display)
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
