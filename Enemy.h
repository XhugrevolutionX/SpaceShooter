#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"


class Enemy : public Entity
{
private:
	static std::vector<sf::Texture> textures_;
	static int counter_;
	int hp = 5;
	int state_ = 0;


	float shoot_dt_ = 0.f;
	float burst_dt_ = 0.f;
	bool wait_shoot = false;
	
	void SetDeath();
	void SetRealDeath();
public :
	Enemy(sf::Vector2f dir);

	void SetState(int s) { sprite_.setTexture(textures_.at(s)); state_ = s; }

	int GetState() const { return state_; }
	void Damage(int damage);
	void Refresh(float dt);
	bool IsShootReady();
};

#endif // ENEMY_H
