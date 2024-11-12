#include "GreenShip.h"

int GreenShip::counter_ = 0;
std::vector<sf::Texture> GreenShip::textures_;

GreenShip::GreenShip()
{
	sf::Vector2i pos = { 0, 0 };
	sf::Vector2i size = { 64, 64 };
	int nb_sprites = 3;

	textures_.resize(nb_sprites);

	for (int i = 0; i < nb_sprites; i++)
	{
		textures_.at(i).loadFromFile("Assets/enemies.png", sf::IntRect(pos.x + i * size.x, pos.y, size.x, size.y));
	}
	sprite_.setTexture(textures_.at(0));
	sprite_.setOrigin(size.x / 2, size.y / 2);

	hitbox.setRadius(size.x / 4);
	hitbox.setOrigin(hitbox.getRadius(), hitbox.getRadius());
	hitbox.setFillColor(sf::Color::Red);


	hp = 5;
	type = 0;
	ShootPeriod = 0.6f;
	BurstPeriod = 0.3f;

	direction_ = { 0, 200 };
	counter_++;
}