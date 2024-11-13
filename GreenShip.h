#ifndef GREENSHIP_H
#define GREENSHIP_H
#include "Enemy.h"


class GreenShip : public Enemy
{
private:
	static int counter_;

	static std::vector<sf::Texture> textures_;


public :
	GreenShip(sf::Vector2f dir);

};

#endif // GREENSHIP_H

