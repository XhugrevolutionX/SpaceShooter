#include "Enemy.h"

int Enemy::counter_ = 0;
sf::Texture Enemy::texture_;

constexpr float kShootPeriod = 0.2f;
constexpr float kBurstPeriod = 0.4f;
void Enemy::SetDeath()
{
	is_dead_ = true;
}


Enemy::Enemy()
{
	texture_.loadFromFile("Assets/enemies.png");
	sprite_.setTexture(texture_);
	sprite_.setOrigin(texture_.getSize().x / 2, texture_.getSize().y / 2);

	hitbox.setRadius(texture_.getSize().y / 2);
	hitbox.setOrigin(hitbox.getRadius(), hitbox.getRadius());
	hitbox.setFillColor(sf::Color::Red);

	direction_ = { 0, 150};
	counter_++;
}

void Enemy::Damage(int degat)
{
	hp -= degat;
	if (hp <= 0)
	{
		SetDeath();
	}
}

void Enemy::Refresh(float dt)
{
	shoot_dt_ += dt;
	burst_dt_ += dt;
	if (burst_dt_ >= kBurstPeriod)
	{
		wait_shoot = !wait_shoot;
		burst_dt_ = 0;
	}
}

bool Enemy::IsShootReady() 
{
	if (shoot_dt_ >= kShootPeriod && !wait_shoot)
	{
		shoot_dt_ = 0;
		return true;
	}
	return false;
}