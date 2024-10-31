#include "Ship.h"

void ship::set_sprite(std::string& texture_path, sf::Vector2i pos, sf::Vector2i size, int nb_sprites)
{
	sprites.resize(nb_sprites);
	textures.resize(nb_sprites);

	for (int i = 0; i < nb_sprites; i++)
	{
		textures.at(i).loadFromFile(texture_path, sf::IntRect(pos.x + i * size.x, pos.y, size.x, size.y));

		sprites.at(i).setTexture(textures.at(i));
		sprites.at(i).setOrigin(size.x/2, size.y/2);
	}

	hitbox.setRadius(size.x / 4);
	hitbox.setOrigin(hitbox.getRadius(), hitbox.getRadius());
	hitbox.setFillColor(sf::Color::Red);
}


void ship::draw_ship(sf::RenderWindow &window, int frame)
{
	window.draw(sprites.at(frame));
	//window.draw(hitbox);
}

void ship::set_position(sf::Vector2f pos, int nb_sprites)
{
	for (int n = 0; n < nb_sprites; n++)
	{
		sprites.at(n).setPosition(pos);
		hitbox.setPosition(pos);
	}
}

sf::Vector2f ship::get_position()
{
	return sprites.at(0).getPosition();
}
