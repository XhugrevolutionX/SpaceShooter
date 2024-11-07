#include "Entity.h"

Entity::Entity()
{
	int nb_sprites_death = 4;
	death_anim.resize(nb_sprites_death);
	for (int i = 0; i < nb_sprites_death; i++)
	{
		death_anim.at(i).loadFromFile("Assets/explosion" + std::to_string(i) + ".png");
	}
}

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

sf::FloatRect  Entity::HitBox()
{
	sf::FloatRect hit_box = hitbox.getGlobalBounds();
	hit_box.left += getPosition().x;
	hit_box.top += getPosition().y;

	return hit_box;
}

void Entity::SetPosition(float x, float y)
{
	setPosition(x, y);
}

void Entity::SetPosition(sf::Vector2f pos)
{
	setPosition(pos);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite_, states);

	////draw the hitbox
	//target.draw(hitbox, states);

	////draw the hitbox Global bounds
	//sf::RectangleShape border({ hitbox.getGlobalBounds().width , hitbox.getGlobalBounds().height });
	//border.setOrigin(border.getSize().x / 2, border.getSize().y / 2);
	//border.setPosition(getPosition().x, getPosition().y);
	//border.setFillColor(sf::Color::Transparent);
	//border.setOutlineColor(sf::Color::Blue);
	//border.setOutlineThickness(2);
	//target.draw(border);
}
