#include "AsteroidManager.h"
#include <random>

//AsteroidManager::AsteroidManager()
//{}


void AsteroidManager::Spawn(const sf::Vector2u& window_size)
{
	asteroids_.emplace_back();
	//asteroids_.back().setPosition();
}

void AsteroidManager::Refresh(float dt_, const sf::Vector2u& window_size)
{
	time_elapsed_ += timer_.restart().asSeconds();
	if (time_elapsed_ > 1)
	{
		asteroids_.emplace_back();

		// Seed with a real random value, if available
		std::random_device rn_device_x;
		// Choose a random mean between min and max
		std::default_random_engine engine_x(rn_device_x());
		std::uniform_real_distribution<float> uniform_dist_x(0, window_size.x);

		asteroids_.back().setPosition(uniform_dist_x(engine_x), 0);

		time_elapsed_ = 0;
	}

	//Clean unused projectiles
	auto removed_elt = std::remove_if(asteroids_.begin(), asteroids_.end(), [](const Entity& p) { return p.IsDead(); });
	if (removed_elt != asteroids_.end())
	{
		asteroids_.erase(removed_elt, asteroids_.end());
	}

	//Move remaining projectiles
	for (Asteroid& a : asteroids_)
	{
		a.Rotate();
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
