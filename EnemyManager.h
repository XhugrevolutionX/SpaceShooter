#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <random>

#include "GreenShip.h"
#include "YellowShip.h"
#include "PurpleShip.h"
#include "WhiteShip.h"
#include "ProjectileManager.h"

class EnemyManager : public sf::Drawable
{
private:
	std::vector<Enemy> enemies_;
	std::vector<GreenShip> green_ships_;
	std::vector<YellowShip> yellow_ships_;
	std::vector<PurpleShip> purple_ships_;
	std::vector<WhiteShip> white_ships_;
	float spawn_timer = 0;

	sf::Vector2f green_ship_dir;
	sf::Vector2f yellow_ship_dir;
	sf::Vector2f purple_ship_dir;
	sf::Vector2f white_ship_dir;


public:

	EnemyManager();
	std::vector<Enemy>& GetEntities() { return enemies_; }
	void Refresh(float dt_, const sf::Vector2u& window_size, ProjectileManager& enemy_projectiles_);


protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};


#endif // ENEMYMANAGER_H
