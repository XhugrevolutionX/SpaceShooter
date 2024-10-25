#include "SFML/Graphics.hpp"
#include "Player.h"
int main()
{

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Space Shooter !!!");
	sf::Event event;
	player test_player;


	test_player.initialize();

	while (window.isOpen())
	{
		window.clear();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		test_player.draw_ship(window, 0);

		window.display();
	}
}
