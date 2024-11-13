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

	float ShootSeparation = 0.f;
	float BurstPeriod = 0.f;
	float BurstSeparation = 0.f;

	sf::Vector2f projectile_dir;

	float dir_timer = 0.f;
	static std::vector<sf::Texture> textures_;
	float dir_timer_limit = 0.f;

public:


	Enemy() = default;
	sf::Vector2f GetProjectileDir() const { return projectile_dir; }
	void SetProjectileDir(sf::Vector2f dir_) { projectile_dir = dir_; }
	int GetType() const { return type; }
	void Damage(int damage);
	void Refresh(float dt);
	bool IsShootReady();

	void ResetTimer() { dir_timer = 0; }
	float GetTimer() const { return dir_timer; }

	float GetTimerLimit() const { return dir_timer_limit; }
};


#endif // ENEMIES_H
