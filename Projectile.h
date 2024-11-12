#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"


class Projectile : public Entity
{

private:
	static std::vector<sf::Texture> textures_;
	static int counter_;

public:
	Projectile(int projectiles_type);
	void SetDirection(sf::Vector2f dir) { direction_ = dir; }
	void SetRotation(float angle) { setRotation(angle); }
};

#endif // PROJECTILE_H
