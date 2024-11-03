#ifndef SHIP_H
#define SHIP_H
#include "vector"
#include "SFML/Graphics.hpp"

class ship :  public sf::Drawable, public sf::Transformable
{
private:
	int hp;
	int state = 0;
	std::vector<sf::Sprite> sprites;
	std::vector<sf::Texture> textures;
	sf::CircleShape hitbox;

public:
	void set_hp(int hp_) { hp = hp_; }
	int get_hp() { return hp; }

	void set_state(int state_) { state = state_; }

	int get_state() const { return state; }

	void set_sprites(std::string &texture_path, sf::Vector2i pos, sf::Vector2i size, int nb_sprites);

	std::vector<sf::Sprite> get_sprite() const { return sprites; }

	void set_position(sf::Vector2f pos, int nb_sprites);
	sf::Vector2f get_position() const;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif


