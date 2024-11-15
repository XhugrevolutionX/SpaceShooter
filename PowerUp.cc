#include "PowerUp.h"


PowerUp::PowerUp(int type_)
{
	type = type_;

	switch (type)
	{
	case 0:
		texture_.loadFromFile("Assets/bonus_life.png");
		break;
	case 1:
		texture_.loadFromFile("Assets/bonus_shield.png");
		break;
	default:
		break;
	}

	sprite_.setTexture(texture_);
	sprite_.setOrigin(texture_.getSize().x / 2, texture_.getSize().y / 2);


	hitbox.setRadius(texture_.getSize().y / 2);
	hitbox.setOrigin(hitbox.getRadius(), hitbox.getRadius());
	hitbox.setFillColor(sf::Color::Red);

	direction_ = {0,200};
}
