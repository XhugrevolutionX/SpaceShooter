#include "Game.h"


Game::Game()
{

	backgroud_texture.loadFromFile("Assets/Background.png");

	background_1.setTexture(backgroud_texture);
	background_1.setScale(5, 7);
	background_2.setTexture(backgroud_texture);
	background_2.setScale(5, 7);

	window.create(sf::VideoMode(background_1.getGlobalBounds().width, background_1.getGlobalBounds().height), "Space Shooter !!!");

	player.setPosition({ static_cast<float>(window.getSize().x) / 2,static_cast<float>(window.getSize().y / 6) * 5 });

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
}

void Game::Loop()
{
	float laser_cooldown = 0;

	std::string str = std::to_string(player.GetHp());
	str.append(" Hp");
	player_hp_display_.setString(str);

	std::string str_score = std::to_string(player.GetScore());
	str_score.append(" Points");
	player_score_display_.setString(str_score);

	//Game loop
	while (window.isOpen() && !player.IsDead())
	{

		window.clear();

		//Background scrolling
		if(background_1.getPosition().y >= window.getSize().y)
		{
			background_1.setPosition(0, -static_cast<int>(window.getSize().y));
			background_2.setPosition(0, 0);
		}
		else if(background_2.getPosition().y >= window.getSize().y)
		{
			background_2.setPosition(0, -static_cast<int>(window.getSize().y));
			background_1.setPosition(0, 0);
		}

		background_1.setPosition(background_1.getPosition().x, background_1.getPosition().y + 0.2);
		background_2.setPosition(background_2.getPosition().x, background_2.getPosition().y + 0.2);


		player.set_state(0);

		sf::Event event;
		while (window.pollEvent(event))
		{
			//Closing the window
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
		}

		//moving and shooting
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			player.movePlayer(sf::Vector2f(0, -1), dt, window.getSize());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			player.movePlayer(sf::Vector2f(0, 1), dt, window.getSize());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			player.movePlayer(sf::Vector2f(-1, 0), dt, window.getSize());
			player.set_state(1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player.movePlayer(sf::Vector2f(1, 0), dt, window.getSize());
			player.set_state(2);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			player.set_state(0);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && laser_cooldown > 0.25)
		{

			projectiles_.Spawn(player.getPosition());
			laser_cooldown = 0;
		}

		projectiles_.Refresh(dt, window.getSize());
		asteroids_.Refresh(dt, window.getSize());

		CheckCollisions();
		draw();
		
		window.display();

		laser_cooldown += dt;
		dt = clock.restart().asSeconds();
	}
}

void Game::draw()
{
	window.draw(background_1);
	window.draw(background_2);
	window.draw(asteroids_);
	window.draw(projectiles_);
	window.draw(player);
	window.draw(player_hp_display_);
	window.draw(player_score_display_);
}

void Game::CheckCollisions()
{
	projectiles_.CheckAsteroidCollisions(asteroids_.GetEntities(), player, player_score_display_);
	player.CheckAsteroidCollisions(asteroids_.GetEntities(), player_hp_display_);
}
