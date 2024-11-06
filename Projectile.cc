#include "Projectile.h"


int Projectile::counter_ = 0;
sf::Texture Projectile::texture_;
Projectile::Projectile()
{
	texture_.loadFromFile("Assets/Laser.png");
	sprite_.setTexture(texture_);
	sprite_.setOrigin(texture_.getSize().x / 2, texture_.getSize().y / 2);

	hitbox.setRadius(texture_.getSize().y / 4);
	hitbox.setOrigin(hitbox.getRadius(), hitbox.getRadius());
	hitbox.setScale(0.5, 2);
	hitbox.setFillColor(sf::Color::Red);

	direction_ = { 0, -750 };
	counter_++;
}
