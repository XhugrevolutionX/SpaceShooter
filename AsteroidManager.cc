#include "AsteroidManager.h"
#include <random>

constexpr float kSpawnPeriod = 0.75f;
void AsteroidManager::Refresh(float dt_, const sf::Vector2u& window_size)
{
	spawn_timer += dt_;
	if (spawn_timer > kSpawnPeriod)
	{
		asteroids_.emplace_back();

		// Seed with a real random value, if available
		std::random_device rn_device_x;
		// Choose a random mean between min and max
		std::default_random_engine engine_x(rn_device_x());
		std::uniform_real_distribution<float> uniform_dist_x(0, window_size.x);

		asteroids_.back().SetPosition(uniform_dist_x(engine_x), 0);

		spawn_timer = 0;
	}

	//Clean unused asteroids
	auto removed_elt = std::remove_if(asteroids_.begin(), asteroids_.end(), [](const Entity& e) { return e.IsDead(); });
	if (removed_elt != asteroids_.end())
	{
		asteroids_.erase(removed_elt, asteroids_.end());
	}

	//Move remaining asteroids
	for (Asteroid& a : asteroids_)
	{
		a.Rotate(dt_);
		a.Move(dt_, window_size);
	}
}
void AsteroidManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (Asteroid e : asteroids_)
	{
		target.draw(e);
	}
}
