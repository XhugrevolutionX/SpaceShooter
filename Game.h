#ifndef GAME_H
#define GAME_H

#include "AsteroidManager.h"
#include "EnemyManager.h"
#include "Player.h"
#include "ProjectileManager.h"
#include "DeathManager.h"


class Game
{
private:
	sf::RenderWindow window;
	ProjectileManager player_projectiles_;
	ProjectileManager enemy_projectiles_;
	AsteroidManager asteroids_;
	EnemyManager enemies_;
	DeathManager death_animations_;
	player player_;
	sf::Texture background_stars_texture;
	sf::Texture background_back_texture;
	sf::Sprite background_back;
	sf::Sprite background_stars_1;
	sf::Sprite background_stars_2;

	sf::Music music_;

	sf::Font font;
	sf::Text player_hp_display_;
	sf::Text player_score_display_;

	sf::Clock clock;
	float dt = 0.f;
	float time_played = 0.f;
public:


	Game();
	void Loop();
	void Refresh();
	void CheckCollisions();
	void draw();
	void EndGame();

};

#endif // GAME_H
