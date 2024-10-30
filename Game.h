#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"
#include "Player.h"
#include "projectile_manager.h"


class Game
{
private:
	sf::RenderWindow window;
	ProjectileManager projectiles_;
	player player;



	sf::Clock clock;
	float dt = 0.0f;
public:
	Game();
	void Loop();
};

#endif // GAME_H
