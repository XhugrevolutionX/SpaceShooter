#include <random>

#include "PowerUpsManager.h"

constexpr float kSpawnPeriod = 5.f;

void PowerUpsManager::Refresh(float dt_, const sf::Vector2u& window_size)
{
	spawn_timer += dt_;
	if (spawn_timer > kSpawnPeriod)
	{
		// Seed with a real random value, if available
		std::random_device rn_device;
		// Choose a random mean between min and max
		std::default_random_engine engine(rn_device());

		std::uniform_real_distribution<float> rng_type(0, 2);
		power_ups_.emplace_back(static_cast<int>(rng_type(engine)));

		std::uniform_real_distribution<float> uniform_dist_x(0, window_size.x);
		power_ups_.back().SetPosition(uniform_dist_x(engine), 0);

		spawn_timer = 0;
	}

	//Clean unused power_ups
	auto removed_elt = std::remove_if(power_ups_.begin(), power_ups_.end(), [](const Entity& e) { return e.IsDead(); });
	if (removed_elt != power_ups_.end())
	{
		power_ups_.erase(removed_elt, power_ups_.end());
	}

	//Move remaining power_ups
	for (PowerUp& p : power_ups_)
	{
		p.Move(dt_, window_size);
	}
}
void PowerUpsManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (PowerUp p : power_ups_)
	{
		target.draw(p);
	}
}