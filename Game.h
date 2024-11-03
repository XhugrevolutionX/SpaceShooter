#ifndef GAME_H
#define GAME_H

#include "EnemiesManager.h"
#include "Player.h"
#include "projectile_manager.h"


class Game
{
private:
	sf::RenderWindow window;
	ProjectileManager projectiles_;
	EnemiesManager enemies_;
	player player;
	sf::Texture backgroud_texture;
	sf::Sprite background_1;
	sf::Sprite background_2;


	sf::Clock clock;
	float dt = 0.0f;
public:
	Game();
	void Loop();
};

#endif // GAME_H
