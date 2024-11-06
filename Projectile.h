#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"


class Projectile : public Entity
{

private:
	static sf::Texture texture_;
	static int counter_;

public:
	Projectile();
};

#endif // PROJECTILE_H
