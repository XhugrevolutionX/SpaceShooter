#include "projectile_manager.h"

#include <complex>

ProjectileManager::ProjectileManager()
{
	sfx.loadFromFile("Assets/laser.mp3");

}
void ProjectileManager::Spawn(sf::Vector2f spawn_position, sf::Vector2f dir)
{

	projectiles_.emplace_back();
	projectiles_.back().SetPosition(spawn_position);
	projectiles_.back().SetDirection(dir);

	sound_projectile.setBuffer(sfx);
	sound_projectile.setVolume(0);
	sound_projectile.play();

}

void ProjectileManager::Refresh(float dt_, const sf::Vector2u& window_size)
{
	//Clean unused projectiles
	auto removed_elt = std::remove_if(projectiles_.begin(), projectiles_.end(), [](const Entity& p) { return p.IsDead(); });
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
				if (p.IsDead())
				{
					player.SetScore(10);
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
					player.SetScore(10);
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
