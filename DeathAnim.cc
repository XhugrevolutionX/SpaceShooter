#include "DeathAnim.h"

DeathAnim::DeathAnim()
{
	int nb_sprites_death = 4;
	death_anim_.resize(nb_sprites_death);
	for (int i = 0; i < nb_sprites_death; i++)
	{
		death_anim_.at(i).loadFromFile("Assets/explosion" + std::to_string(i) + ".png");
	}
	sprite_.setTexture(death_anim_.at(0));
	sprite_.setOrigin(sprite_.getTexture()->getSize().x / 2, sprite_.getTexture()->getSize().y / 2);
}

void DeathAnim::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite_);
}