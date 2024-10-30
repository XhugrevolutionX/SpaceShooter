#include "Game.h"


Game::Game()
{
	
	

	backgroud_texture.loadFromFile("Assets/Background.png");

	background_1.setTexture(backgroud_texture);
	background_1.setScale(5, 7);
	background_2.setTexture(backgroud_texture);
	background_2.setScale(5, 7);

	window.create(sf::VideoMode(background_1.getGlobalBounds().width, background_1.getGlobalBounds().height), "Space Shooter !!!");

	player.set_position({ static_cast<float>(window.getSize().x) / 2,static_cast<float>(window.getSize().y / 6) * 5 }, player.get_sprite().size());

	background_2.setPosition(0, -static_cast<int>(window.getSize().y));
}

 
void Game::Loop()
{
	bool is_moving = false;
	float laser_cooldown = 0;

	while (window.isOpen())
	{
		if(background_1.getPosition().y == window.getSize().y)
		{
			background_1.setPosition(0, -static_cast<int>(window.getSize().y));
			background_2.setPosition(0, 0);
		}
		else if(background_2.getPosition().y == window.getSize().y)
		{
			background_2.setPosition(0, -static_cast<int>(window.getSize().y));
			background_1.setPosition(0, 0);
		}

		background_1.setPosition(background_1.getPosition().x, background_1.getPosition().y + 1);
		background_2.setPosition(background_2.getPosition().x, background_2.getPosition().y + 1);

	



		int ship_frame = 0;
		window.clear();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
		}

		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		//{
		//	player.movePlayer(sf::Vector2f(0, -1), dt);
		//}
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		//{
		//	player.movePlayer(sf::Vector2f(0, 1), dt);
		//}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			player.movePlayer(sf::Vector2f(-1, 0), dt, window.getSize());
			ship_frame = 2;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player.movePlayer(sf::Vector2f(1, 0), dt, window.getSize());
			ship_frame = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && laser_cooldown > 0.5)
		{

			projectiles_.Spawn({ player.get_position().x + 10, player.get_position().y - 10});
			laser_cooldown = 0;
		}

		projectiles_.Refresh(dt, window.getSize());



		window.draw(background_1);
		window.draw(background_2);
		player.draw_ship(window, ship_frame);
		window.draw(projectiles_);


		window.display();

		laser_cooldown += dt;
		dt = clock.restart().asSeconds();
	}
}