#ifndef DEATHMANAGER_H
#define DEATHMANAGER_H

#include "SFML/Audio.hpp"
#include "DeathAnim.h"
#include "Enemy.h"
#include "Asteroid.h"
#include "Player.h"

class DeathManager : public sf::Drawable
{
private:
	std::vector<DeathAnim> death_animations_;
	std::string ship_death_path = "Assets/explosion";
	int ship_death_nb_textures = 4;
	std::string asteroid_death_path = "Assets/Asteroid_Death";
	int asteroid_death_nb_textures = 5;
	std::string tiny_asteroid_death_path = "Assets/Small_Asteroid_Death";
	int tiny_asteroid_death_nb_textures = 5;


	sf::Sound sound_;
	sf::SoundBuffer sfx_ship_explosion_;
	sf::SoundBuffer sfx_asteroid_explosion_;
public:

	DeathManager();
	void Refresh(float dt_, const sf::Vector2u& window_size, std::vector<Enemy>& enemies_, std::vector<Asteroid>& asteroids_, player& player_);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // DEATHMANAGER_H
