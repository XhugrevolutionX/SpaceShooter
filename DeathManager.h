#ifndef DEATHMANAGER_H
#define DEATHMANAGER_H

#include "SFML/Audio.hpp"
#include "DeathAnim.h"
#include "Enemy.h"
#include "Player.h"

class DeathManager : public sf::Drawable
{
private:
	std::vector<DeathAnim> death_animations_;
	sf::Sound sound_explosion;
	sf::SoundBuffer sfx;
public:

	DeathManager();
	void Refresh(float dt_, const sf::Vector2u& window_size, std::vector<Enemy>& enemies_, player& player_);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // DEATHMANAGER_H
