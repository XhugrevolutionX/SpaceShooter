
#include "Enemies.h"

#include <random>

Enemies::Enemies(int type)
{
	textures_.reserve(3);
	sf::Vector2i pos = { 0, 0 };
	sf::Vector2i size = { 64, 64 };

	type_ = type;

	for (int i = 0; i < textures_.capacity(); i++)
	{
		textures_.emplace_back();
		textures_.back().loadFromFile("Assets/enemies"+ std::to_string(type_) +".png", sf::IntRect(pos.x + i * size.x, pos.y, size.x, size.y));
	}

	std::random_device rn_device;
	std::default_random_engine engine(rn_device());
	std::uniform_real_distribution<float> yellow_ship_rng_dir_x(-100, 100);


	switch (type_)
	{
	case 0:

		hp = 3;
		dir_timer_limit = 2.f;
		projectile_dir = { 300, 750 };
		ShootSeparation = 0.75f;
		BurstPeriod = 0.f;
		BurstSeparation = 0.f;
		direction_ = { 100, 200 };
		break;

	case 1:


		hp = 4;
		dir_timer_limit = 0.f;
		projectile_dir = { 0, 750 };
		ShootSeparation = 0.5f;
		BurstPeriod = 0.9f;
		BurstSeparation = 0.3f;
		direction_ = { yellow_ship_rng_dir_x(engine), 200 };
		break;

	case 2:

		hp = 2;
		dir_timer_limit = 0.f;
		projectile_dir = { 300, 750 };
		ShootSeparation = 1.f;
		BurstPeriod = 0.4f;
		BurstSeparation = 0.2f;
		direction_ = { 0, 200 };
		break;

	case 3:

		hp = 4;
		dir_timer_limit = 0.f;
		projectile_dir = { -500, 750 };
		ShootSeparation = 0.4f;
		BurstPeriod = 0.f;
		BurstSeparation = 0.f;
		direction_ = { 0, 200 };
		break;

	default:
		break;
	}

	sprite_.setTexture(textures_.at(0));
	sprite_.setOrigin(size.x / 2, size.y / 2);

	hitbox.setRadius(size.x / 4);
	hitbox.setOrigin(hitbox.getRadius(), hitbox.getRadius());
	hitbox.setFillColor(sf::Color::Red);

}

void Enemies::Damage(int damage)
{
	hp -= damage;
	if (hp <= 0)
	{
		SetDeath();
	}
}

void Enemies::Refresh(float dt)
{
	sprite_.setTexture(textures_.at(state_));
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

bool Enemies::IsShootReady()
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