#include "Game.h"


Game::Game()
{
	window.create(sf::VideoMode(1920, 1080), "Space Shooter !!!");
}

 
void Game::Loop()
{
	bool is_moving = false;
	float laser_counter = 0;
	while (window.isOpen())
	{
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
			player.movePlayer(sf::Vector2f(-1, 0), dt);
			player.draw_ship(window, 1);
			is_moving = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player.movePlayer(sf::Vector2f(1, 0), dt);
			player.draw_ship(window, 2);
			is_moving = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && laser_counter > 0.5)
		{

			projectiles_.Spawn({ player.get_position().x + 10, player.get_position().y - 10});
			laser_counter = 0;
		}


		projectiles_.Refresh(dt);

		if(!is_moving)
		{
			player.draw_ship(window, 0);
		}
		is_moving = false;
		
		
		window.draw(projectiles_);

		window.display();

		laser_counter += dt;
		dt = clock.restart().asSeconds();
	}
}