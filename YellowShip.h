#ifndef YELLOWSHIP_H
#define YELLOWSHIP_H
#include "Enemy.h"

class YellowShip : public Enemy
{
private:
	static int counter_;

	static std::vector<sf::Texture> textures_;


public :

	YellowShip(sf::Vector2f dir);

};



#endif // YELLOWSHIP_H
