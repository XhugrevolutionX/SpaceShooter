#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H

#include "Asteroid.h"
#include "SFML/Audio.hpp"
#include "Projectile.h"
#include <vector>

#include "Enemy.h"
#include "Player.h"


class ProjectileManager : public sf::Drawable
{
private:
	std::vector<Projectile> projectiles_;
	sf::Sound sound_projectile;
	sf::SoundBuffer sfx;

	float sound_timer;
	const float sound_timer_limit = 0.5f;
public:
	ProjectileManager();

	std::vector<Projectile>& GetEntities() { return projectiles_; }
	void Spawn(sf::Vector2f spawn_position, sf::Vector2f dir, float volume, int projectile_type);
	void Refresh(float dt_, const sf::Vector2u& window_size);
	void CheckCollisions(std::vector<Asteroid>& asteroids_, player& player, sf::Text& player_score_display);
	void CheckCollisions(std::vector<Enemy>& enemies, player& player, sf::Text& player_score_display);


protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

#endif // PROJECTILE_MANAGER_H
