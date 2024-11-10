#include "DeathManager.h"

void DeathManager::Refresh(float dt_, const sf::Vector2u& window_size, std::vector<Enemy> enemies_)
{

	for (Entity& e : enemies_)
	{
		if (e.IsDead())
		{
			death_animations_.emplace_back();
			death_animations_.back().SetPosition(e.GetPosition());
			e.SetRealDeath();
		}
	}

	for (DeathAnim& d : death_animations_)
	{
		d.SetDelay(d.GetDelay() + dt_);
		if (d.GetDelay() > 0.5)
		{
			if (d.GetState() < 4)
			{
				d.SetState(d.GetState() + 1);
			}
			else
			{
				d.End();
			}
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