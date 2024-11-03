#include "Projectile.h"


int Projectile::counter_ = 0;
sf::Texture Projectile::texture_;

Projectile::Projectile()
{
	texture_.loadFromFile("Assets/Laser.png");
	sprite_.setTexture(texture_);
	setOrigin(get_texture().getSize().x / 2, get_texture().getSize().y / 2);
	sprite_.setRotation(-45);

	hitbox.setRadius(get_texture().getSize().x / 4);
	hitbox.setOrigin(hitbox.getRadius(), hitbox.getRadius());
	hitbox.setScale(1, 2);
	hitbox.setFillColor(sf::Color::Red);


	direction_ = { 0, -500 };
	counter_++;
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite_, states);
	target.draw(hitbox, states);
}

void Projectile::Move(float dt, const sf::Vector2u& window_size)
{
	setPosition(getPosition() + direction_* dt);

	sf::Vector2f pos = getPosition();

	if (pos.x < 0 || pos.x > window_size.x || pos.y < 0 || pos.y > window_size.y)
	{
		is_dead_ = true;
	}
}


