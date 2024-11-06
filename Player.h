#ifndef PLAYER_H
#define PLAYER_H
#include "Projectile.h"
#include "Asteroid.h"

class player : public Entity
{

private:
	int hp = 5;
	int state = 0;
	std::vector<sf::Sprite> sprites;
	std::vector<sf::Texture> textures;
	const float speed = 500.0f;
public:

	player();
	void set_state(int state_) { state = state_; }
	int get_state() const { return state; }

	void Damage();
	void CheckAsteroidCollisions(std::vector<Asteroid>& asteroids_);
	void movePlayer(sf::Vector2f direction, float dt, const sf::Vector2u& window_size);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


};






#endif
