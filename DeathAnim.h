#ifndef DEATHANIM_H
#define DEATHANIM_H
#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


class DeathAnim : public sf::Drawable
{
private:
	std::vector<sf::Texture> death_anim_;
	sf::Sprite sprite_;
	int state = 0;
	bool is_finished = false;

public:
	DeathAnim();
	void SetState(int i) { state = i; }
	void SetPosition(sf::Vector2f pos) { sprite_.setPosition(pos); }
	int GetState() const { return state; }
	bool IsFinished() const {return is_finished;}
	void End() { is_finished = true; }

	void Refresh();


protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // DEATHANIM_H
