#include "Enemies.h"

int enemies::counter_ = 0;

enemies::enemies()
{

	direction_ = { 0, -200 };
	counter_++;
}
void enemies::Move(float dt, const sf::Vector2u& window_size)
{
	setPosition(getPosition() + direction_ * dt);

	sf::Vector2f pos = getPosition();

	if (pos.x < 0 || pos.x > window_size.x || pos.y < 0 || pos.y > window_size.y)
	{
		is_dead_ = true;
	}
}

void enemies::check_collision(float dt)
{
	
}
