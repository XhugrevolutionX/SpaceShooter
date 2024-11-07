#ifndef PROJECTILE_MANAGER_H
#define PROJECTILE_MANAGER_H

#include "Asteroid.h"
#include "SFML/Audio.hpp"
#include "Projectile.h"
#include <vector>
#include "Player.h"


class ProjectileManager : public sf::Drawable
{
private:
	std::vector<Projectile> projectiles_;
	sf::Sound sound_projectile;
	sf::SoundBuffer sfx;
public:
	ProjectileManager();
	void Spawn(sf::Vector2f spawn_position);
	void Refresh(float dt_, const sf::Vector2u& window_size);
	void CheckAsteroidCollisions(std::vector<Asteroid>& asteroids_, player& player, sf::Text& player_score_display);


protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

#endif // PROJECTILE_MANAGER_H
