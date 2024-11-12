#include "WhiteShip.h"

int WhiteShip::counter_ = 0;
std::vector<sf::Texture> WhiteShip::textures_;

WhiteShip::WhiteShip(sf::Vector2f dir)
{
	sf::Vector2i pos = { 0, 0 };
	sf::Vector2i size = { 64, 64 };
	int nb_sprites = 3;

	textures_.resize(nb_sprites);

	for (int i = 0; i < nb_sprites; i++)
	{
		textures_.at(i).loadFromFile("Assets/enemies4.png", sf::IntRect(pos.x + i * size.x, pos.y, size.x, size.y));
	}
	sprite_.setTexture(textures_.at(0));
	sprite_.setOrigin(size.x / 2, size.y / 2);

	hitbox.setRadius(size.x / 4);
	hitbox.setOrigin(hitbox.getRadius(), hitbox.getRadius());
	hitbox.setFillColor(sf::Color::Red);


	hp = 5;
	type = 3;
	projectile_dir = { -500, 750 };
	ShootSeparation = 0.4f;
	BurstPeriod = 0.f;
	BurstSeparation = 0.f;

	direction_ = dir;
	counter_++;
}
