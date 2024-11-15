#ifndef ASTEROID_H
#define ASTEROID_H

#include "Entity.h"

class Asteroid : public Entity
{

private:
	static std::vector<sf::Texture> textures_;
	static int counter_;
	int type;

public:
	Asteroid();

	int GetType() { return type; }
	void DeathAnim(float dt_);
	void Rotate(float dt_);

};




#endif // ASTEROID_H
