#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>


class Entity : protected sf::Transformable, public sf::Drawable
{
protected:

	sf::Vector2f direction_;
	sf::Sprite sprite_;
	bool is_dead_ = false;
	bool is_really_dead = false;
	bool is_first_dead_loop = true;

	sf::CircleShape hitbox;

	std::vector<sf::Texture> death_anim;


public:
	void Move(float dt, const sf::Vector2u& window_size);
	bool IsDead() const { return is_dead_; }
	bool IsReallyDead() const { return is_really_dead; }
	bool IsFirstDeadLoop() const { return is_first_dead_loop; }
	void SetDeath() { is_dead_ = true; }
	void SetRealDeath() { is_dead_ = true; }
	void SetFirstDeathLoop() { is_first_dead_loop = false; }
	bool Intersects(sf::FloatRect hitBox_);
	sf::FloatRect HitBox();

	void SetPosition(float x, float y);

	void SetPosition(sf::Vector2f pos);

	sf::Vector2f GetPosition() const { return getPosition(); } 


protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};


#endif // ENTITY_H
