#ifndef WHITESHIP_H
#define WHITESHIP_H
#include "Enemy.h"

class WhiteShip : public Enemy
{
private:
	static int counter_;

	static std::vector<sf::Texture> textures_;


public:

	WhiteShip(sf::Vector2f dir);
};

#endif // WHITESHIP_H
