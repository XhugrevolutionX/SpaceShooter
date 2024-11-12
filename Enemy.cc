#include "Enemy.h"

void Enemy::SetDeath()
{
	is_dead_ = true;
}

void Enemy::SetRealDeath()
{
	is_really_dead_ = true;
}

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
	burst_dt_ += dt;
	if (burst_dt_ >= BurstPeriod)
	{
		wait_shoot = !wait_shoot;
		burst_dt_ = 0;
	}
}

bool Enemy::IsShootReady()
{
	if (shoot_dt_ >= ShootPeriod && !wait_shoot)
	{
		shoot_dt_ = 0;
		return true;
	}
	return false;
}