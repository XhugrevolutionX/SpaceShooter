#include "Projectile.h"

#include <SFML/Graphics/RenderTarget.hpp>

int Projectile::counter = 0;
sf::Texture Projectile::texture_;

Projectile::Projectile()
{
	texture_.loadFromFile("Assets/Laser.png");
	sprite_.setTexture(texture_);
	setRotation(-45);

	direction_ = { 0, -500 };
	counter++;
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite_, states);
}

void Projectile::Move(float dt)
{
	setPosition(getPosition() + direction_* dt);
}


