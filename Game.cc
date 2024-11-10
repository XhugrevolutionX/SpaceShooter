#include "Game.h"


Game::Game()
{

	backgroud_texture.loadFromFile("Assets/Background.png");

	background_1.setTexture(backgroud_texture);
	background_1.setScale(5, 7);
	background_2.setTexture(backgroud_texture);
	background_2.setScale(5, 7);

	window.create(sf::VideoMode(background_1.getGlobalBounds().width, background_1.getGlobalBounds().height), "Space Shooter !!!");

	player_.SetPosition({ static_cast<float>(window.getSize().x) / 2,static_cast<float>(window.getSize().y / 6) * 5 });

	background_2.setPosition(0, -static_cast<int>(window.getSize().y));


	if (!font.loadFromFile("Assets\\BrownieStencil.ttf"))
	{

	}

	player_hp_display_.setFont(font);
	player_hp_display_.setPosition(window.getSize().x / 20 * 18, window.getSize().y / 25);
	player_hp_display_.setCharacterSize(25);
	player_hp_display_.setFillColor(sf::Color::White);

	player_score_display_.setFont(font);
	player_score_display_.setPosition(window.getSize().x / 20 * 18, window.getSize().y / 25 * 2);
	player_score_display_.setCharacterSize(25);
	player_score_display_.setFillColor(sf::Color::Red);

	//enemy_.SetPosition(window.getSize().x / 2, 0);
}

void Game::Loop()
{
	float laser_cooldown = 0;

	std::string str = std::to_string(player_.GetHp());
	str.append(" Hp");
	player_hp_display_.setString(str);

	std::string str_score = std::to_string(player_.GetScore());
	str_score.append(" Points");
	player_score_display_.setString(str_score);

	//Game loop
	
	while (window.isOpen() && !player_.IsDead())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			//Closing the window
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
		}
		window.clear();

		//Background scrolling
		if (background_1.getPosition().y >= window.getSize().y)
		{
			background_1.setPosition(0, -static_cast<int>(window.getSize().y));
			background_2.setPosition(0, 0);
		}
		else if (background_2.getPosition().y >= window.getSize().y)
		{
			background_2.setPosition(0, -static_cast<int>(window.getSize().y));
			background_1.setPosition(0, 0);
		}

		background_1.setPosition(background_1.getPosition().x, background_1.getPosition().y + 200 * dt);
		background_2.setPosition(background_2.getPosition().x, background_2.getPosition().y + 200 * dt);


		player_.set_state(0);

		//moving and shooting
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			player_.movePlayer(sf::Vector2f(0, -1), dt, window.getSize());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			player_.movePlayer(sf::Vector2f(0, 1), dt, window.getSize());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			player_.movePlayer(sf::Vector2f(-1, 0), dt, window.getSize());
			player_.set_state(1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player_.movePlayer(sf::Vector2f(1, 0), dt, window.getSize());
			player_.set_state(2);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			player_.set_state(0);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && laser_cooldown > 0.25)
		{

			player_projectiles_.Spawn(player_.GetPosition(), { 0, -750 }, 0, 50);
			laser_cooldown = 0;
		}


		Refresh();

		CheckCollisions();
		draw();

		window.display();

		laser_cooldown += dt;
		dt = clock.restart().asSeconds();
	}
}

void Game::CheckCollisions()
{
	player_projectiles_.CheckCollisions(asteroids_.GetEntities(), player_, player_score_display_);
	player_projectiles_.CheckCollisions(enemies_.GetEntities(), player_, player_score_display_);
}


void Game::Refresh()
{
	player_.Refresh(dt, asteroids_.GetEntities(), enemies_.GetEntities(), enemy_projectiles_.GetEntities(), player_hp_display_);
	player_projectiles_.Refresh(dt, window.getSize());
	enemy_projectiles_.Refresh(dt, window.getSize());
	asteroids_.Refresh(dt, window.getSize());
	enemies_.Refresh(dt, window.getSize(), enemy_projectiles_);
	//death_animations_.Refresh(dt, window.getSize(), enemies_.GetEntities());
}

void Game::draw()
{
	window.draw(background_1);
	window.draw(background_2);
	window.draw(asteroids_);
	window.draw(enemies_);
	//window.draw(death_animations_);
	window.draw(player_projectiles_);
	window.draw(enemy_projectiles_);
	window.draw(player_);
	window.draw(player_hp_display_);
	window.draw(player_score_display_);
}

