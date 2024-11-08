#ifndef DEATHMANAGER_H
#define DEATHMANAGER_H

#include "DeathAnim.h"
#include "Enemy.h"

class DeathManager : public sf::Drawable
{
private:
	std::vector<DeathAnim> death_animations_;

public:

	void Refresh(float dt_, const sf::Vector2u& window_size, std::vector<Enemy> enemies_);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // DEATHMANAGER_H
