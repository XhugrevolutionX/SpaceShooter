#ifndef POWERUP_H
#define POWERUP_H
#include "Entity.h"

class PowerUp : public Entity
{
private:
	int type;
	sf::Texture texture_;
public:

	int GetType() { return type; }
	PowerUp(int);
};



#endif // POWERUP_H
