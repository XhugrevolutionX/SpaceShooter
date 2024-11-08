#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"


class Enemy : public Entity
{
private:
	static sf::Texture texture_;
	static int counter_;
	int hp = 5;


	float shoot_dt_ = 0.f;
	float burst_dt_ = 0.f;
	bool wait_shoot = false;
	
	void SetDeath();
public :
	Enemy(sf::Vector2f dir);
	void Damage(int degat);
	void Refresh(float dt);
	bool IsShootReady();
};

#endif // ENEMY_H
