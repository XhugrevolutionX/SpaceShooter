#ifndef PURPLESHIP_H
#define PURPLESHIP_H
#include "Enemy.h"

class PurpleShip : public Enemy
{
private:
	static int counter_;
	int state_ = 0;

	static std::vector<sf::Texture> textures_;


public:
	void SetState(int s) { sprite_.setTexture(textures_.at(s)); state_ = s; }

	int GetState() const { return state_; }
	PurpleShip(sf::Vector2f dir);

};

#endif // PURPLESHIP_H
