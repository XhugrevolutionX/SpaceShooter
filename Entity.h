#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>


class Entity : protected sf::Transformable, public sf::Drawable
{
protected:

	sf::Vector2f direction_;
	sf::Sprite sprite_;
	bool is_dead_ = false;
	bool is_really_dead_ = false;
	bool is_off_screen_ = false;

	sf::CircleShape hitbox;

	std::vector<sf::Texture> death_anim;


public:
	void Move(float dt, const sf::Vector2u& window_size);
	bool IsDead() const { return is_dead_; }
	bool IsReallyDead() const { return is_really_dead_; }
	bool IsOffScreen() const { return is_off_screen_; }
	void SetDeath() { is_dead_ = true; }
	void SetRealDeath() { is_really_dead_ = true; }

	void SetOffScreen() { is_off_screen_ = true; SetDeath(); }
	bool Intersects(sf::FloatRect hitBox_);
	sf::FloatRect HitBox();

	void SetPosition(float x, float y);

	void SetPosition(sf::Vector2f pos);

	sf::Vector2f GetPosition() const { return getPosition(); }

	void SetDir(sf::Vector2f dir) { direction_ = dir; }

	sf::Vector2f GetDir() const { return direction_; }

	float GetRotation() const { return getRotation(); }
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};


#endif // ENTITY_H
