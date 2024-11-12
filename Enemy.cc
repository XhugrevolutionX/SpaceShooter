#include "Enemy.h"

int Enemy::counter_ = 0;
std::vector<sf::Texture> Enemy::textures_;

constexpr float kShootPeriod = 0.3f;
constexpr float kBurstPeriod = 0.6f;
void Enemy::SetDeath()
{
	is_dead_ = true;
}

void Enemy::SetRealDeath()
{
	is_really_dead_ = true;
}

Enemy::Enemy(sf::Vector2f dir)
{
	sf::Vector2i pos = { 0,0 };
	sf::Vector2i size = { 64,64 };
	int nb_sprites = 3;

	textures_.resize(nb_sprites);

	for (int i = 0; i < nb_sprites; i++)
	{
		textures_.at(i).loadFromFile("Assets/enemies.png", sf::IntRect(pos.x + i * size.x, pos.y, size.x, size.y));
	}
	sprite_.setTexture(textures_.at(0));
	sprite_.setOrigin(size.x / 2, size.y / 2);

	hitbox.setRadius(textures_.at(0).getSize().y / 4);
	hitbox.setOrigin(hitbox.getRadius(), hitbox.getRadius());
	hitbox.setFillColor(sf::Color::Red);

	direction_ = dir;
	counter_++;
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