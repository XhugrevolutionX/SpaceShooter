#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <random>
#include "ProjectileManager.h"

class EnemyManager : public sf::Drawable
{
private:
	std::vector<Enemies> enemies_;
	float spawn_timer = 0;

public:

	EnemyManager();
	std::vector<Enemies>& GetEntities() { return enemies_; }
	void Refresh(float dt_, const sf::Vector2u& window_size, ProjectileManager& enemy_projectiles_);


protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};


#endif // ENEMYMANAGER_H
