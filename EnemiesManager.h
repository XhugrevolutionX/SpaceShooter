#ifndef ENEMIES_MANAGER_H
#define ENEMIES_MANAGER_H

#include "enemy.h"

class EnemiesManager : public sf::Drawable
{
private:
	std::vector<enemy> enemies_;

public:
	EnemiesManager();

	void Spawn(const sf::Vector2u& window_size);

	void Refresh(float dt_, const sf::Vector2u& window_size);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};





#endif // ENEMIES_MANAGER_H
