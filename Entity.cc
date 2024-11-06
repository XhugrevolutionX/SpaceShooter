#include "Entity.h"

void Entity::Move(float dt, const sf::Vector2u& window_size)
{
	if(!is_dead_)
	{
		setPosition(getPosition() + direction_ * dt);
	}

	sf::Vector2f pos = getPosition();

	sf::Vector2f borders = sf::Vector2f(sprite_.getGlobalBounds().width / 2, sprite_.getGlobalBounds().height / 2);

	if (pos.x < -1 * borders.x || pos.x > window_size.x + borders.x || pos.y < -1 * borders.y || pos.y > window_size.y + borders.y)
	{
		is_dead_ = true;
	}
}

bool Entity::Intersects(sf::FloatRect hitBox_)
{
	return HitBox().intersects(hitBox_);
}

sf::FloatRect Entity::HitBox()
{
	sf::FloatRect hit_box = hitbox.getGlobalBounds();
	hit_box.left += getPosition().x;
	hit_box.top += getPosition().y;

	return hit_box;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite_, states);
	//target.draw(hitbox, states);
}
