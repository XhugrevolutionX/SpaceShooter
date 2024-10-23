#include "SFML/Graphics.hpp"
#include "Ship.h"
int main()
{

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Space Shooter !!!");
	sf::Event event;
	Ship testShip;

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

		window.display();
	}
}
