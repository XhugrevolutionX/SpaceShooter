#include "PowerUp.h"

std::vector<sf::Texture> PowerUp::textures_;
PowerUp::PowerUp(int type_)
{
	type = type_;

	textures_.resize(2);

	textures_.at(0).loadFromFile("Assets/bonus_life.png");
	textures_.at(1).loadFromFile("Assets/bonus_shield.png");


	sprite_.setTexture(textures_.at(type_));
	sprite_.setOrigin(textures_.at(type_).getSize().x / 2, textures_.at(type_).getSize().y / 2);
	sprite_.setScale(1.5, 1.5);


	hitbox.setRadius(textures_.at(type_).getSize().y / 2);
	hitbox.setOrigin(hitbox.getRadius(), hitbox.getRadius());
	hitbox.setFillColor(sf::Color::Red);

	direction_ = {0,150};
}
