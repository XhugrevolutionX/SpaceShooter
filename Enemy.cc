
#include "Enemy.h"

void Enemy::Damage(int damage)
{
	hp -= damage;
	if (hp <= 0)
	{
		SetDeath();
	}
}

void Enemy::Refresh(float dt)
{
	shoot_dt_ += dt;
	dir_timer += dt;
	if (shoot_dt_ >= ShootSeparation)
	{
		burst_dt_ += dt;
		if (burst_dt_ >= BurstSeparation)
		{
			wait_shoot = !wait_shoot;
			burst_dt_ = 0;
		}
	}
}

bool Enemy::IsShootReady()
{
	if (shoot_dt_ >= ShootSeparation && wait_shoot)
	{
		if (shoot_dt_ >= ShootSeparation + BurstPeriod)
		{
			shoot_dt_ = 0;
		}
		wait_shoot = !wait_shoot;
		return true;
	}
	return false;
}