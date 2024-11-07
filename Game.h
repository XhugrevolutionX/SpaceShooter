#ifndef GAME_H
#define GAME_H

#include "AsteroidManager.h"
#include "Player.h"
#include "projectile_manager.h"


class Game
{
private:
	sf::RenderWindow window;
	ProjectileManager projectiles_;
	AsteroidManager asteroids_;
	player player;
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
	void draw();
	void CheckCollisions();
};

#endif // GAME_H
