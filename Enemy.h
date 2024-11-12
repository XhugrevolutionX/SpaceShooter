#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"

class Enemy : public Entity
{

protected:
	int hp = 0;

	int type;

	float shoot_dt_ = 0.f;
	float burst_dt_ = 0.f;
	bool wait_shoot = false;

	float ShootPeriod = 0.f;
	float BurstPeriod = 0.f;

	void SetDeath();
	void SetRealDeath();

public:


	Enemy() = default;
	int GetType() const { return type; }
	void Damage(int damage);
	void Refresh(float dt);
	bool IsShootReady();
};


#endif // ENEMIES_H
