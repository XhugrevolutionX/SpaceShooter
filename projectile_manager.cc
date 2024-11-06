#include "projectile_manager.h"

#include <complex>


ProjectileManager::ProjectileManager()
{
	sfx.loadFromFile("Assets/laser.mp3");

}
void ProjectileManager::Spawn(sf::Vector2f spawn_position)
{


	projectiles_.emplace_back();
	projectiles_.back().setPosition(spawn_position);

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
		projectiles_.erase(removed_elt);
	}

	//Move remaining projectiles
	for (Entity& e : projectiles_)
	{
		e.Move(dt_, window_size);
	}
}

void ProjectileManager::CheckAsteroidCollisions(std::vector<Asteroid>& asteroids_)
{
	for (auto& p : projectiles_)
	{
		for (auto& a : asteroids_)
		{
			if (p.IsDead() == false && a.IsDead() == false && p.Intersects(a.HitBox()))
			{
				p.SetDeath();
				a.SetDeath();
			}
		}
	}
}

void ProjectileManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (Projectile e : projectiles_)
	{
		target.draw(e);
	}
}
