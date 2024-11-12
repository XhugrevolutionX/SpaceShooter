#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "GreenShip.h"
#include "YellowShip.h"
#include "ProjectileManager.h"

class EnemyManager : public sf::Drawable
{
private:
	std::vector<Enemy> enemies_;
	std::vector<GreenShip> green_ships_;
	std::vector<YellowShip> yellow_ships_;
	float spawn_timer = 0;
public:

	std::vector<Enemy>& GetEntities() { return enemies_; }
	void Refresh(float dt_, const sf::Vector2u& window_size, ProjectileManager& enemy_projectiles_);


protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};


#endif // ENEMYMANAGER_H
