#include "DeathManager.h"


DeathManager::DeathManager()
{
	sfx_ship_explosion_.loadFromFile("Assets/explosion.mp3");
	sfx_asteroid_explosion_.loadFromFile("Assets/boom.mp3");
	sfx_player_death_.loadFromFile("Assets/player_dead.mp3");
	sound_.setVolume(75);
}

void DeathManager::Refresh(float dt_, const sf::Vector2u& window_size, std::vector<Enemy>& enemies_, std::vector<Asteroid>& asteroids_, player& player_)
{
	if (player_.IsDead())
	{
		if (!player_.IsReallyDead())
		{
			death_animations_.emplace_back();
			death_animations_.back().Init(ship_death_path, ship_death_nb_textures, player_.GetRotation());
			death_animations_.back().SetPosition(player_.GetPosition());

			sound_.setBuffer(sfx_ship_explosion_);
			sound_.play();

			player_.SetRealDeath();
		}
		if (death_animations_.empty())
		{
			sound_.setBuffer(sfx_player_death_);
			sound_.play();
			player_.set_EndDeath();
		}
	}

	for (Enemy& e : enemies_)
	{
		if (e.IsDead() && !e.IsOffScreen() && !e.IsReallyDead())
		{
			death_animations_.emplace_back();
			death_animations_.back().Init(ship_death_path, ship_death_nb_textures, e.GetRotation());
			death_animations_.back().SetPosition(e.GetPosition());

			sound_.setBuffer(sfx_ship_explosion_);
			sound_.play();

			e.SetRealDeath();
		}
	}


	for (Asteroid& a : asteroids_)
	{
		if (a.IsDead() && !a.IsOffScreen() && !a.IsReallyDead())
		{
			death_animations_.emplace_back();
			if (a.GetType() == 0)
			{
				death_animations_.back().Init(asteroid_death_path, asteroid_death_nb_textures, a.GetRotation());
			}
			else if(a.GetType() == 1)
			{
				death_animations_.back().Init(tiny_asteroid_death_path, tiny_asteroid_death_nb_textures, a.GetRotation());
			}
			death_animations_.back().SetPosition(a.GetPosition());

			sound_.setBuffer(sfx_asteroid_explosion_);
			sound_.play();

			a.SetRealDeath();
		}
	}

	for (DeathAnim& d : death_animations_)
	{
		d.SetDelay(d.GetDelay() + dt_);
		if (d.GetDelay() > 0.1)
		{
			if (d.GetState() < d.GetNbTextures() - 1)
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