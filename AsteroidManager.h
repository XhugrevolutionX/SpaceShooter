#ifndef ASTEROID_MANAGER_H
#define ASTEROID_MANAGER_H

#include "Asteroid.h"
#include <vector>


class AsteroidManager : public sf::Drawable
{
private:
	std::vector<Asteroid> asteroids_;
	sf::Clock timer_;
	float time_elapsed_ = 0;

public:

	//AsteroidManager();

	void Spawn(const sf::Vector2u& window_size);
	std::vector<Asteroid>& GetEntities() { return asteroids_; }

	void Refresh(float dt_, const sf::Vector2u& window_size);


protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


};

#endif // ASTEROID_MANAGER_H
