#include "Projectile.h"


int Projectile::counter_ = 0;
std::vector<sf::Texture> Projectile::textures_;
Projectile::Projectile(int projectile_type)
{
	textures_.resize(3);
	textures_.at(0).loadFromFile("Assets/laser_blue.png");
	textures_.at(1).loadFromFile("Assets/laser_red.png");
	textures_.at(2).loadFromFile("Assets/laser_yellow.png");

	sprite_.setTexture(textures_.at(projectile_type));
	sprite_.setOrigin(textures_.at(0).getSize().x / 2, textures_.at(0).getSize().y);

	hitbox.setRadius(textures_.at(0).getSize().y / 4);
	hitbox.setOrigin(hitbox.getRadius(), hitbox.getRadius());
	hitbox.setScale(0.25, 1);
	hitbox.setFillColor(sf::Color::Red);

	counter_++;
}
