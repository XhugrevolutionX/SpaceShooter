#ifndef ASTEROID_MANAGER_H
#define ASTEROID_MANAGER_H

#include "Asteroid.h"


class AsteroidManager : public sf::Drawable
{
private:
	std::vector<Asteroid> asteroids_;
	sf::Clock timer_;
	float spawn_timer = 0;

public:
	std::vector<Asteroid>& GetEntities() { return asteroids_; }
	void Refresh(float dt_, const sf::Vector2u& window_size);


protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


};

#endif // ASTEROID_MANAGER_H
