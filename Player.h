#ifndef PLAYER_H
#define PLAYER_H
#include "Asteroid.h"
#include "Enemy.h"
#include "Projectile.h"

class player : public Entity
{

private:
	int hp = 20;
	int score = 0;
	int state = 0;
	std::vector<sf::Sprite> sprites;
	std::vector<sf::Texture> textures;
	const float speed = 500.0f;

public:

	player();
	void set_state(int state_) { state = state_; }
	int get_state() const { return state; }
	int GetHp() { return hp; }
	void SetScore(int s) { score += s; }
	int GetScore() { return score; }
	void Damage(sf::Text& player_hp_);
	void CheckCollisions(std::vector<Asteroid>& asteroids_, sf::Text& player_hp_);
	void CheckCollisions(std::vector<Enemy>& enemies, sf::Text& player_hp_);
	void CheckCollisions(std::vector<Projectile>& projectiles, sf::Text& player_hp_);
	void movePlayer(sf::Vector2f direction, float dt, const sf::Vector2u& window_size);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


};






#endif
