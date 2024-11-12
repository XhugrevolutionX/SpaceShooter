#ifndef YELLOWSHIP_H
#define YELLOWSHIP_H
#include "Enemy.h"

class YellowShip : public Enemy
{
private:
	static int counter_;
	int state_ = 0;

	static std::vector<sf::Texture> textures_;


public :
	void SetState(int s) { sprite_.setTexture(textures_.at(s)); state_ = s; }

	int GetState() const { return state_; }
	YellowShip(sf::Vector2f dir);

};



#endif // YELLOWSHIP_H
