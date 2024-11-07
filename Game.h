#ifndef GAME_H
#define GAME_H

#include "AsteroidManager.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Player.h"
#include "projectile_manager.h"


class Game
{
private:
	sf::RenderWindow window;
	ProjectileManager player_projectiles_;
	ProjectileManager enemy_projectiles_;
	AsteroidManager asteroids_;
	EnemyManager enemies_;
	player player_;
	sf::Texture backgroud_texture;
	sf::Sprite background_1;
	sf::Sprite background_2;

	sf::Font font;
	sf::Text player_hp_display_;
	sf::Text player_score_display_;

	sf::Clock clock;
	float dt = 0.0f;
public:


	Game();
	void Loop();

	void Refresh();

	void CheckCollisions();
	void draw();

};

#endif // GAME_H
