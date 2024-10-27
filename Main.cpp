#include "SFML/Graphics.hpp"
#include "Player.h"
int main()
{

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Space Shooter !!!");
	sf::Event event;
	sf::Clock clock;
	float dt = 0.0f;

	player test_player;

	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();

		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		//{
		//	test_player.movePlayer(sf::Vector2f(0, -1), dt);
		//}
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		//{
		//	test_player.movePlayer(sf::Vector2f(0, 1), dt);
		//}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			test_player.movePlayer(sf::Vector2f(-1, 0), dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			test_player.movePlayer(sf::Vector2f(1, 0), dt);
		}

		test_player.draw_ship(window, 0);

		window.display();

		dt = clock.restart().asSeconds();
	}
}
