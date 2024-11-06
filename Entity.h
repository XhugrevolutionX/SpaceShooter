#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>


class Entity : public sf::Transformable, public sf::Drawable
{
protected:

	std::vector<sf::Texture> death_animation_;
	sf::Vector2f direction_;
	sf::Sprite sprite_;
	bool is_dead_ = false;

	sf::CircleShape hitbox;


public:
	void Move(float dt, const sf::Vector2u& window_size);
	bool IsDead() const { return is_dead_; }
	void SetDeath() { is_dead_ = true; }
	bool Intersects(sf::FloatRect hitBox_);
	sf::FloatRect HitBox();


protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};


#endif // ENTITY_H
