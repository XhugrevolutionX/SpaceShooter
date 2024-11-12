#include "DeathManager.h"


DeathManager::DeathManager()
{
	sfx.loadFromFile("Assets/explosion.mp3");
	sound_explosion.setBuffer(sfx);
	sound_explosion.setVolume(50);
}

void DeathManager::Refresh(float dt_, const sf::Vector2u& window_size, std::vector<Enemy>& enemies_)
{
	for (Entity& e : enemies_)
	{
		if (e.IsDead() && !e.IsOffScreen() && !e.IsReallyDead())
		{
			death_animations_.emplace_back();
			death_animations_.back().SetPosition(e.GetPosition());

			sound_explosion.play();

			e.SetRealDeath();
		}
	}

	for (DeathAnim& d : death_animations_)
	{
		d.SetDelay(d.GetDelay() + dt_);
		if (d.GetDelay() > 0.1)
		{
			if (d.GetState() < 3)
			{
				d.SetState(d.GetState() + 1);
			}
			else
			{
				d.End();
			}
			d.SetDelay(0);
		}

	}

	auto removed_elt = std::remove_if(death_animations_.begin(), death_animations_.end(), [](const DeathAnim& d) { return d.IsFinished(); });
	if (removed_elt != death_animations_.end())
	{
		death_animations_.erase(removed_elt, death_animations_.end());
	}
}



void DeathManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (DeathAnim d : death_animations_)
	{
		target.draw(d);
	}
}