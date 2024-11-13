#include "DeathAnim.h"

void DeathAnim::Init(std::string path, int nb, float rotation)
{
	nb_textures = nb;
	death_anim_.resize(nb_textures);
	for (int i = 0; i < nb_textures; i++)
	{
		death_anim_.at(i).loadFromFile(path + std::to_string(i) + ".png");
	}
	sprite_.setTexture(death_anim_.at(0));
	sprite_.setOrigin(sprite_.getTexture()->getSize().x / 2, sprite_.getTexture()->getSize().y / 2);
	sprite_.setRotation(rotation);
}

void DeathAnim::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite_);
}