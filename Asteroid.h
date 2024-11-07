#ifndef ASTEROID_H
#define ASTEROID_H

#include "Entity.h"

class Asteroid : public Entity
{

private:
	static sf::Texture texture_;
	static int counter_;

public:
	Asteroid();

	void DeathAnim(float dt_);
	void Rotate();

};




#endif // ASTEROID_H
