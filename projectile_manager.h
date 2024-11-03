#ifndef PROJECTILE_MANAGER_H
#define PROJECTILE_MANAGER_H

#include "SFML/Audio.hpp"
#include "Projectile.h"

class ProjectileManager : public sf::Drawable
{
private:
	std::vector<Projectile> projectiles_;
	sf::Sound sound_projectile;
	sf::SoundBuffer sfx;
public:
	ProjectileManager();
	void Spawn(sf::Vector2f spawn_position);

	std::vector < Projectile> get_projectiles() { return projectiles_; }

	void Refresh(float dt_, const sf::Vector2u& window_size);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // PROJECTILE_MANAGER_H
