#ifndef SHIP_H
#define SHIP_H
#include "vector"
#include "SFML/Graphics.hpp"

class Ship
{
private:
	int hp;
	std::vector<sf::Sprite> sprites;


public:
	void SetHp(int hp_) { hp = hp_; }
	int GetHp() { return hp; }

};

#endif


