#ifndef SHIP_H
#define SHIP_H
#include "vector"
#include "SFML/Graphics.hpp"

class ship
{
private:
	int hp;
	std::vector<sf::Sprite> sprites;
	std::vector<sf::Texture> textures;
	sf::CircleShape hitbox;

public:
	void set_hp(int hp_) { hp = hp_; }
	int get_hp() { return hp; }

	void set_sprite(std::string &texture_path, sf::Vector2i pos, sf::Vector2i size, int nb_sprites);

	std::vector<sf::Sprite> get_sprite() { return sprites; }

	void draw_ship(sf::RenderWindow &window, int frame);

	void set_position(sf::Vector2f pos, int nb_sprites);
	sf::Vector2f get_position();

};

#endif


