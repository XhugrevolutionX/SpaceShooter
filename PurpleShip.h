#ifndef PURPLESHIP_H
#define PURPLESHIP_H
#include "Enemy.h"

class PurpleShip : public Enemy
{
private:
	static int counter_;

	static std::vector<sf::Texture> textures_;

public:

	PurpleShip(sf::Vector2f dir);

};

#endif // PURPLESHIP_H
