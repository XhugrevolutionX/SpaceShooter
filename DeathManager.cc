#include "DeathManager.h"

void DeathManager::Refresh(float dt_, const sf::Vector2u& window_size, std::vector<Enemy> enemies_)
{
	for (Entity& e : enemies_)
	{
		if (e.IsDead())
		{
			if (e.IsFirstDeadLoop())
			{
				death_animations_.emplace_back();
				death_animations_.back().SetPosition(e.GetPosition());
				e.SetFirstDeathLoop();
			}
			else
			{
				if (death_animations_.back().GetState() < 4)
				{
					death_animations_.back().SetState(death_animations_.back().GetState() + 1);
				}
				else
				{
					e.SetRealDeath();
					death_animations_.back().End();
				}
			}
		}
	}

	auto removed_elt = std::remove_if(death_animations_.begin(), death_animations_.end(), [](const DeathAnim& d) { return d.IsFinished(); });
	if (removed_elt != death_animations_.end())
	{
		death_animations_.erase(removed_elt, death_animations_.end());
	}

	for (DeathAnim d : death_animations_)
	{
		d.Refresh();
	}
}



void DeathManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (DeathAnim d : death_animations_)
	{
		target.draw(d);
	}
}