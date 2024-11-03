


#include "EnemiesManager.h"
#include "random"

EnemiesManager::EnemiesManager()
{
	
}

void EnemiesManager::Spawn(const sf::Vector2u& window_size)
{
	sf::Vector2f spawn_pos;

	enemies_.emplace_back();
	enemies_.back().set_position({ 0 + (enemies_.back().get_sprite().at(0).getTexture()->getSize().x / 2) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (window_size.x - (enemies_.back().get_sprite().at(0).getTexture()->getSize().x / 2) - 0 + (enemies_.back().get_sprite().at(0).getTexture()->getSize().x / 2)))) ,-10 },1);

}

void EnemiesManager::Refresh(float dt_, const sf::Vector2u& window_size)
{
	//Clean unused projectiles
	auto removed_elt = std::remove_if(enemies_.begin(), enemies_.end(), [](const enemy& e) { return e.IsDead(); });
	if (removed_elt != enemies_.end())
	{
		enemies_.erase(removed_elt);
	}

	//Move remaining projectiles
	for (enemy& e : enemies_)
	{
		e.Move(dt_, window_size);
	}
}

void EnemiesManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (enemy e : enemies_)
	{
		target.draw(e);
	}
}