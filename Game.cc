#include "Game.h"


Game::Game()
{
	background_stars_texture.loadFromFile("Assets/Background.png");
	background_back_texture.loadFromFile("Assets/bg.png");

	background_stars_1.setTexture(background_stars_texture);
	background_stars_1.setScale(5, 7);
	background_stars_2.setTexture(background_stars_texture);
	background_stars_2.setScale(5, 7);

	background_back.setTexture(background_back_texture);
	background_back.setScale(1.3, 1);

	window.create(sf::VideoMode(background_stars_1.getGlobalBounds().width, background_stars_1.getGlobalBounds().height), "Space Shooter !!!");

	player_.SetPosition({ static_cast<float>(window.getSize().x) / 2,static_cast<float>(window.getSize().y / 6) * 5 });

	background_stars_2.setPosition(0, -static_cast<int>(window.getSize().y));

	if (!font.loadFromFile("Assets/BrownieStencil.ttf"))
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

	music_.openFromFile("Assets/anipatok_game_music_shmup.mp3");
	music_.setLoop(true);
	music_.setVolume(50);
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

	music_.play();
	//Game loop
	
	while (window.isOpen())
	{
		window.clear();
		sf::Event event;
		while (window.pollEvent(event))
		{
			//Closing the window
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				music_.stop();
				window.close();
			}
		}
		if (!player_.is_death_ended())
		{
			//Background scrolling
			if (background_stars_1.getPosition().y >= window.getSize().y)
			{
				background_stars_1.setPosition(0, -static_cast<int>(window.getSize().y));
				background_stars_2.setPosition(0, 0);
			}
			else if (background_stars_2.getPosition().y >= window.getSize().y)
			{
				background_stars_2.setPosition(0, -static_cast<int>(window.getSize().y));
				background_stars_1.setPosition(0, 0);
			}

			background_stars_1.setPosition(background_stars_1.getPosition().x, background_stars_1.getPosition().y + 200 * dt);
			background_stars_2.setPosition(background_stars_2.getPosition().x, background_stars_2.getPosition().y + 200 * dt);


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

				player_projectiles_.Spawn(player_.GetPosition(), { 0, -750 }, 20, 1);
				laser_cooldown = 0;
			}

			Refresh();
			CheckCollisions();
			draw();

			laser_cooldown += dt;
			time_played += dt;
			dt = clock.restart().asSeconds();
		}
		else 
		{
			draw();
			EndGame();
		}

		window.display();
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
	death_animations_.Refresh(dt, window.getSize(), enemies_.GetEntities(), asteroids_.GetEntities(), player_);
	asteroids_.Refresh(dt, window.getSize());
	enemies_.Refresh(dt, window.getSize(), enemy_projectiles_);
}

void Game::draw()
{
	window.draw(background_back);
	window.draw(background_stars_1);
	window.draw(background_stars_2);
	window.draw(asteroids_);
	window.draw(enemies_);
	window.draw(death_animations_);
	window.draw(player_projectiles_);
	window.draw(enemy_projectiles_);
	window.draw(player_);
	window.draw(player_hp_display_);
	window.draw(player_score_display_);
}


void Game::EndGame()
{
	float window_width = window.getSize().x;
	float window_height = window.getSize().y;
	sf::Vector2f rect_size = { window_width / 4, window_height / 6 };

	sf::RectangleShape rect;
	rect.setSize(rect_size);
	rect.setOrigin(rect_size.x / 2, rect_size.y / 2);
	rect.setFillColor(sf::Color::Black);
	rect.setOutlineColor(sf::Color::White);
	rect.setOutlineThickness(1);
	rect.setPosition(window_width / 2, window_height / 2);

	sf::Font font;
	font.loadFromFile("Assets/BrownieStencil.ttf");

	sf::Text game_over;
	sf::Text info;
	std::string info_string;

	game_over.setFont(font);
	info.setFont(font);

	game_over.setCharacterSize(40);
	info.setCharacterSize(20);

	info_string.append("You survived ");
	info_string.append(std::to_string(static_cast<int>(time_played)));
	info_string.append(" seconds\nYou scored ");
	info_string.append(std::to_string(player_.GetScore()));
	info_string.append(" Points");

	game_over.setString("Game Over");
	info.setString(info_string);

	game_over.setOrigin(game_over.getGlobalBounds().width / 2, game_over.getGlobalBounds().height / 2);
	info.setOrigin(info.getGlobalBounds().width / 2, info.getGlobalBounds().height / 2);

	game_over.setPosition({ rect.getPosition().x, rect.getPosition().y - (rect_size.y/4)});
	info.setPosition({ rect.getPosition().x, rect.getPosition().y + (rect_size.y / 4) });

	window.draw(rect);
	window.draw(game_over);
	window.draw(info);
}
