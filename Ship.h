#ifndef SHIP_H
#define SHIP_H
#include "vector"
#include "SFML/Graphics.hpp"

class ship
{
private:
	int hp;
	std::vector<sf::Sprite> sprites;

	sf::Texture texture1;
	sf::Texture texture2;
	sf::Texture texture3;

public:
	void set_hp(int hp_) { hp = hp_; }
	int get_hp() { return hp; }

	void set_sprite(std::string &texture1_path);
	void set_sprite(std::string &texture1_path, std::string &texture2_path);
	void set_sprite(std::string &texture1_path, std::string &texture2_path, std::string &texture3_path);

	std::vector<sf::Sprite> get_sprite() { return sprites; }

	void draw_ship(sf::RenderWindow &window, int frame);

	void set_position(sf::Vector2f pos, int nb_sprites);
	sf::Vector2f get_position();

};

#endif


